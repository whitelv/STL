#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <type_traits>

template <typename T>
class Unique_ptr
{

    // ** Member functions
public:
    // * constructor
    Unique_ptr() : ptr(nullptr) {}
    explicit Unique_ptr(T *p) noexcept : ptr{p} {}
    Unique_ptr(const Unique_ptr &u) = delete;
    Unique_ptr(Unique_ptr &&u) : ptr{u.ptr} { u.ptr = nullptr; }

    // * destructor
    ~Unique_ptr()
    {
        if (ptr != nullptr)
            delete ptr;
    }

    // * assignment operator
    Unique_ptr &operator=(const Unique_ptr &) = delete;
    Unique_ptr &operator=(Unique_ptr &&r) noexcept
    {
        if (this == &r)
            return *this;

        delete ptr;
        ptr = r.ptr;
        r.ptr = nullptr;
        return *this;
    }

    // ** Modifiers
public:
    // * release()
    T *release() noexcept
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // * reset
    void reset(T *p = nullptr) noexcept
    {
        if (ptr == p)
            return;
        delete ptr;
        ptr = p;
    }

    // * swap
    void swap(Unique_ptr &other) noexcept
    {
        T *temp = other.ptr;
        other.ptr = ptr;
        ptr = temp;
    }

    // ** Observers
public:
    // * get()
    T *get() const noexcept { return ptr; }

    // *bool
    explicit operator bool() const noexcept { return ptr != nullptr; }

    // ** Single-object version, unique_ptr<T>
public:
    typename std::add_lvalue_reference<T>::type operator*() const
        noexcept(noexcept(*std::declval<T *>()))
    {
        return *ptr;
    }

    T *operator->() const noexcept
    {
        return ptr;
    }

private:
    T *ptr;
};

// ** Non-member functions
template< class T, class... Args >
constexpr Unique_ptr<T> make_unique( Args&&... args ){
    return  Unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif