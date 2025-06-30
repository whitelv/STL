//
//  array.h
//  STL
//
//  Created by Любомир Витвицький on 24.06.2025.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>


template <class T, size_t N>
class Array{
    
public:
    using iterator = T*;


// Element access
public:
    T & at(size_t n);
    const T & at(size_t n)  const;
    T & operator[](size_t n);
    const T & operator[](size_t n) const;
    
    T & front();
    constexpr T & front() const;
    
    T & back();
    constexpr T & back() const;
    
    T * data();
    constexpr T * data() const;

    

 // Capacity
public:
    constexpr bool empty() const;
    constexpr size_t size() const;
    constexpr size_t max_size() const;
    
// Iterators
public:
    iterator begin();
    iterator end();
    constexpr iterator cbegin() const;
    constexpr iterator cend() const;
    
// Operations
public:
    void fill( const T& value);
    void swap(Array & other );
    
    
public:
    T arr[N];
};


template <typename T, size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs){
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

// .at()
template <class T,size_t N>
T & Array<T,N>::at(size_t n){
    if (n > N || n < 0) {
        throw std::out_of_range("Cannot access elements out of Array object");
    }
    return arr[n];
}

template <class T,size_t N>
const T & Array<T,N>::at(size_t n) const{
    if (n > N || n < 0) {
        throw std::out_of_range("Cannot access elements out of Array object");
    }
    return arr[n];
}

// operator[]

template <class T,size_t N>
T & Array<T,N>::operator[](size_t n){
    return arr[n];
}

template <class T,size_t N>
const T & Array<T,N>::operator[](size_t n) const{
    return arr[n];
}


// .front()

template <class T,size_t N>
T & Array<T,N>::front(){
    if (empty()) {
        throw std::out_of_range("Cannot take first element if size is zero");
    }
    return arr[0];
}

template <class T,size_t N>
constexpr T & Array<T,N>::front() const{
    if (empty()) {
        throw std::out_of_range("Cannot take first element if size is zero");
    }
    return arr[0];
}

// .back()

template <class T,size_t N>
T & Array<T,N>::back(){
    if (empty()) {
        throw std::out_of_range("Cannot take first element if size is zero");
    }
    return arr[N - 1];
}

template <class T,size_t N>
constexpr T & Array<T,N>::back() const{
    if (empty()) {
        throw std::out_of_range("Cannot take first element if size is zero");
    }
    return arr[N - 1];
}


// .data()
template <class T,size_t N>
T * Array<T,N>::data() {
    if (empty()) {
        throw std::out_of_range("Cannot take first element if size is zero");
    }
    return &arr[0];
}

template <class T,size_t N>
constexpr T * Array<T,N>::data() const{
    if (empty()) {
        throw std::out_of_range("Cannot take first element if size is zero");
    }
    return &arr[0];
}


// begin
template <class T,size_t N>
Array<T,N>::iterator Array<T,N>::begin(){
    return data();
}

// end
template <class T,size_t N>
Array<T,N>::iterator Array<T,N>::end(){
    return data() + N;
}

// cbegin
template <class T,size_t N>
constexpr Array<T,N>::iterator Array<T,N>::cbegin() const{
    return data();
}

// cend
template <class T,size_t N>
constexpr Array<T,N>::iterator Array<T,N>::cend() const{
    return data() + N;
}


// .empty()

template <class T,size_t N>
constexpr bool Array<T,N>::empty() const{
    return N == 0;
}

// .size()
template <class T,size_t N>
constexpr size_t Array<T,N>::size() const{
    return end() - begin();
}

// .max_size()
template <class T,size_t N>
constexpr size_t Array<T,N>::max_size() const{
    return N;
}


// .fill()
template <class T,size_t N>
void Array<T,N>::fill( const T& value){
    for (size_t i = 0; i < N; i++) {
        arr[i] = value;
    }
}


// .swap()
template <class T,size_t N>
void Array<T,N>::swap(Array & other ){
    if (size() != other.size()) {
        throw std::length_error("Two arrays should be the same size");
    }
    
    T temp{};
    for (size_t i = 0; i < size(); i++) {
        temp = other.arr[i];
        other.arr[i] = arr[i];
        arr[i] = temp;
    }
}

// .get()

template<std::size_t I, class T,size_t N>
T& get(Array<T,N>& a) {
    static_assert(N >= I, "Cannot access elements out of Array object");
    return a.at(I);
}

template<std::size_t I, class T, size_t N>
const T& get(const Array<T,N>& a) {
    static_assert(N >= I, "Cannot access elements out of Array object");
    return a.at(I);
}



#endif
