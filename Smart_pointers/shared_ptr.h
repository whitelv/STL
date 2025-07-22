#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cstddef>
#include <utility>
#include "control.h"
#include <iostream>

template <class T>
class Weak_ptr;

template <class T>
class Shared_ptr
{
    friend class Weak_ptr<T>;
    // ** Modifiers
public:
    // * reset
    void reset() noexcept
    {
        delete_object();
        pointer = nullptr;
        control = nullptr;
    }

    template <class U>
    void reset(U *p)
    {
        delete_object();
        pointer = p;
        control = new control_block<T>{1, 0, pointer};
    }

    // * swap
    void swap(Shared_ptr &r) noexcept
    {
        T *temp = r.pointer;
        control_block<T> *c = r.control;

        r.pointer = pointer;
        r.control = control;
        pointer = temp;
        control = c;
    }

    // ** Observers
public:
    T *get() const noexcept { return pointer; }
    T &operator*() const noexcept { return *pointer; };
    T *operator->() const noexcept { return pointer; }
    size_t use_count() const noexcept { return control == nullptr ? 0 : control->strong; }
    bool unique() const noexcept { return use_count() == 1; }
    explicit operator bool() const noexcept { return pointer != nullptr; }

    // ** Member functions
public:
    // * Constructor
    Shared_ptr() : pointer{nullptr}, control{nullptr} {}
    explicit Shared_ptr(T *ptr) : pointer{ptr}, control{new control_block<T>{1, 0, pointer}} {}
    Shared_ptr(const Shared_ptr &x) noexcept : pointer{x.pointer}, control{x.control}
    {
        if (control == nullptr)
            return;
        control->strong++;
    }
    Shared_ptr(Shared_ptr &&x) noexcept : pointer{x.pointer}, control{x.control}
    {
        x.pointer = nullptr;
        x.control = nullptr;
    }
    explicit Shared_ptr(const Weak_ptr<T> &r) : pointer(r.control->pointer), control(r.control)
    {
        if (control == nullptr)
            return;
        control->strong++;
    }

    // * Destructor
    ~Shared_ptr()
    {
        delete_object();
    }

    // * Assignment operator
    Shared_ptr &operator=(const Shared_ptr &x) noexcept
    {
        if (this == &x)
            return *this;

        delete_object();
        pointer = x.pointer;
        control = x.control;
        if (control != nullptr)
            control->strong++;

        return *this;
    }

    Shared_ptr &operator=(Shared_ptr &&x) noexcept
    {
        if (this == &x)
            return *this;

        delete_object();

        pointer = x.pointer;
        control = x.control;
        x.pointer = nullptr;
        x.control = nullptr;

        return *this;
    }

    // ** Helper function
private:
    void delete_object()
    {
        if (control == nullptr)
            return;

        control->strong--;
        if (control->strong == 0)
        {
            std::cout << "pointer deleted" << std::endl;
            delete pointer;
        }
        if (control->strong == 0 && control->weak == 0)
        {
            std::cout << "control deleted" << std::endl;
            delete control;
        }
    }

    // ** Class members
private:
    T *pointer;
    control_block<T> *control;
};

// ** Non-member functions
template <class T, class... Args>
Shared_ptr<T> make_shared(Args &&...args)
{
    return Shared_ptr<T>(new T{std::forward<Args>(args)...});
}

template <class T, class U>
bool operator==(const Shared_ptr<T> &lhs, const Shared_ptr<U> &rhs) noexcept
{
    return lhs.get() == rhs.get();
}

#endif