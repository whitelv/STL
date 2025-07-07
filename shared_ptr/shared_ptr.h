#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cstddef>
#include <utility>

template <class T>
class Shared_ptr
{

    // ** Modifiers
public:
    // * reset
    void reset() noexcept
    {
        delete_object();
        pointer = nullptr;
        strong = nullptr;
    }

    template <class U>
    void reset(U *p)
    {
        delete_object();
        pointer = p;
        *strong = 1;
    }

    // * swap

    void swap(Shared_ptr &r) noexcept
    {
        T *temp = r.pointer;
        size_t *count = r.strong;

        r.pointer = pointer;
        r.strong = strong;
        pointer = temp;
        strong = count;
    }

    // ** Observers
public:
    T *get() const noexcept { return pointer; }
    T &operator*() const noexcept { return *pointer; };
    T *operator->() const noexcept { return pointer; }
    size_t use_count() const noexcept { return strong == nullptr ? 0 : *strong; }
    bool unique() const noexcept { return use_count() == 1; }
    explicit operator bool() const noexcept { return pointer != nullptr; }

    // ** Member functions
public:
    // * Constructor
    Shared_ptr() : pointer{nullptr}, strong{nullptr} {}
    template <class Y>
    explicit Shared_ptr(Y *ptr) : pointer{ptr}, strong{new size_t{1}} {}
    Shared_ptr(const Shared_ptr &x) noexcept : pointer{x.pointer}, strong{x.strong} { *strong += 1; }
    Shared_ptr(Shared_ptr &&x) noexcept : pointer{x.pointer}, strong{x.strong}
    {
        x.pointer = nullptr;
        x.strong = nullptr;
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
        {
            return *this;
        }
        delete_object();
        pointer = x.pointer;
        strong = x.strong;
        *strong += 1;

        return *this;
    }

    Shared_ptr &operator=(Shared_ptr &&x) noexcept
    {
        if (this == &x)
        {
            return *this;
        }
        delete_object();

        pointer = x.pointer;
        strong = x.strong;
        x.pointer = nullptr;
        x.strong = nullptr;

        return *this;
    }

    // ** Helper function
private:
    void delete_object()
    {
        if (strong == nullptr)
            return;

        *strong -= 1;
        if (*strong == 0)
        {
            delete pointer;
            delete strong;
        }
    }
    // ** Class members
private:
    T *pointer;
    size_t *strong;
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