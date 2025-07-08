#ifndef WEAK_PTR_H
#define WEAK_PTR_H
#include "control.h"
#include "shared_ptr.h"

template <typename T>
class Weak_ptr
{
    friend class Shared_ptr<T>;

    // ** Observers
public:
    size_t use_count() const noexcept { return control == nullptr ? 0 : control->strong; }
    bool expired() const noexcept { return use_count() == 0; }
    Shared_ptr<T> lock() const noexcept { return expired() ? Shared_ptr<T>() : Shared_ptr<T>(*this); }

    // ** Modifiers
public:
    void reset() noexcept
    {
        delete_object();
        control = nullptr;
    }

    void swap(Weak_ptr &r) noexcept
    {
        control_block<T> *temp = r.control;
        r.control = control;
        control = temp;
    }

public:
    // * Constructor
    constexpr Weak_ptr() noexcept : control{nullptr} {};
    Weak_ptr(const Shared_ptr<T> &r) noexcept : control{r.control}
    {
        if (control == nullptr)
            return;
        control->weak++;
    }
    Weak_ptr(const Weak_ptr &r) noexcept : control{r.control}
    {
        if (control == nullptr)
            return;
        control->weak++;
    }
    Weak_ptr(Weak_ptr &&r) noexcept : control{r.control} { r.control = nullptr; }

    // * Destructor
    ~Weak_ptr()
    {
        delete_object();
    }

    // * Assignment operator
    Weak_ptr &operator=(const Shared_ptr<T> &r) noexcept
    {
        delete_object();
        control = r.control;
        if (control != nullptr)
            control->weak++;
        return *this;
    }

    Weak_ptr &operator=(const Weak_ptr &r) noexcept
    {
        if (this == &r)
            return *this;

        delete_object();
        control = r.control;
        if (control != nullptr)
            control->weak++;

        return *this;
    }

    Weak_ptr &operator=(Weak_ptr &&r) noexcept
    {
        if (this == &r)
            return *this;

        delete_object();
        control = r.control;
        r.control = nullptr;
        return *this;
    }

    // ** Helper function
private:
    void delete_object()
    {
        if (control == nullptr)
            return;

        if (control->strong == 0 && control->weak == 1)
        {
            std::cout << "control deleted" << std::endl;
            delete control;
            return;
        }
        control->weak--;
    }

private:
    control_block<T> *control;
};

#endif