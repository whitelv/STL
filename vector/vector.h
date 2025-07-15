#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <initializer_list>
#include <stdio.h>
#include <cmath>
#include <type_traits>
#include <utility>
#include <cstring>

template <class T>
class Vector{
    
public:
    using iterator = T *;
    using const_iterator = const T *;
    
    // CONSTRUCTORS
public:
    
    // default constructor
    Vector() : vec(nullptr), size(0), capacity(0) {};
    
    // fill constructor
    Vector(size_t size, const T & val) : size(size), capacity(size){
        vec = new T[capacity];
        fill(size, val);
    };
    // range constructor
    Vector(iterator first, iterator last) : size(last - first), capacity(size){
        if (capacity > 0) {
            vec = new T[capacity];
            if (std::is_trivially_copyable_v<T>) {
                std::memcpy(vec, first, size * sizeof(T));
            }else{
                for (size_t i = 0; i < size; i++) {
                    vec[i] = *(first + i);
                }
            }
        }else{
            vec = nullptr;
        }
        
    };
    // copy constructor
    Vector(const Vector & v) : size(v.size), capacity(v.size){
        if(capacity > 0){
            vec = new T[capacity];
            if (std::is_trivially_copyable_v<T>) {
                std::memcpy(vec, v.vec, size * sizeof(T));
            }else{
                for (size_t i = 0; i < size; ++i) {
                    vec[i] = v.vec[i];
                }
            }
        }else{
            vec = nullptr;
        }
    }
    // move constructor
    Vector(Vector && v) : vec(v.vec), size(v.size), capacity(v.capacity){
        v.vec = nullptr;
        v.size = v.capacity = 0;
    }
    // initializer list constructor
    Vector(const std::initializer_list<T> & il) : size(il.size()), capacity(il.size()){
        if(capacity > 0){
            vec = new T[capacity];
            size_t i = 0;
            if (std::is_trivially_copyable_v<T>) {
                std::memcpy(vec, il.begin(), size * sizeof(T));
            }
            else{
                for (const auto &x : il) {
                    vec[i++] = x;
                }
            }
        }else{
            vec = nullptr;
        }
    }
    
    // destructor
    ~Vector(){
        if (vec != nullptr) {
            delete [] vec;
        }
    }
    
    // operator=
    Vector & operator=( const Vector& other ){
        if(this == &other){
            return *this;
        }
        if (vec != nullptr) {
            delete [] vec;
        }
        size = capacity = other.size;
        if (capacity > 0){
            vec = new T[capacity];
            if (std::is_trivially_copyable_v<T>) {
                std::memcpy(vec, other.vec, size * sizeof(T));
            }else{
                for (int i = 0; i < size; i++) {
                    vec[i] = other.vec[i];
                }
            }
        }else{
            vec = nullptr;
        }
        return  * this;
    }
    
    Vector & operator=(Vector&& other){
        if(this == &other){
            return *this;
        }
        if (vec != nullptr) {
            delete [] vec;
        }
        size = other.size;
        capacity = other.capacity;
        
        vec = other.vec;
        
        other.vec = nullptr;
        other.size = other.capacity = 0;
        return *this;
    }
    
    Vector & operator=(const std::initializer_list<T> & il){
        if (vec != nullptr) {
            delete [] vec;
        }
        size = il.size();
        capacity = il.size();
        if(capacity > 0){
            vec = new T[capacity];
            if (std::is_trivially_copyable_v<T>) {
                std::memcpy(vec, il.begin(), size * sizeof(T));
            }else{
                size_t i = 0;
                for (const auto &x : il) {
                    vec[i++] = x;
                }
            }
        }else{
            vec = nullptr;
        }
        return *this;
    }
    
    
    // assign()
    void assign(size_t count, const T& value ){
        clear();
        size = count;
        adjust_storage(size);
        fill(size, value);
    }
    
    void assign(iterator first, iterator last){
        clear();
        if(last > first){
            size = last - first;
            adjust_storage(size);
            fill(first, size);
        }else{
            size = 0;
        }
    }
    
    void assign(std::initializer_list<T> il ){
        clear();
        size = il.size();
        if (size > 0){
            adjust_storage(size);
            fill(il.begin(), size);
        }
    }
    
    
    //    Element access
    
    T & at(size_t pos){
        if(pos >= size || pos < 0){
            throw std::out_of_range("position must be less than size");
        }
        return vec[pos];
    }
    
    const T & at(size_t pos) const{
        if(pos >= size || pos < 0){
            throw std::out_of_range("position must be less than size");
        }
        return vec[pos];
    }
    
    T & operator[](size_t pos){
        return vec[pos];
    }
    
    const T & operator[](size_t pos) const{
        return vec[pos];
    }
    
    T & front(){
        if (empty()) {
            throw std::out_of_range("Size must be bigger than 0");
        }
        return vec[0];
    }
    
    const T & front() const{
        if (empty()) {
            throw std::out_of_range("Size must be bigger than 0");
        }
        return vec[0];
    }
    
    T & back(){
        if (empty()) {
            throw std::out_of_range("Size must be bigger than 0");
        }
        return vec[size - 1];
    }
    
    const T & back() const{
        if (empty()) {
            throw std::out_of_range("Size must be bigger than 0");
        }
        return vec[size - 1];
    }
    
    T* data(){
        if (empty()) {
            throw std::out_of_range("Size must be bigger than 0");
        }
        return vec;
    }
    
    const T* data() const{
        if (empty()) {
            throw std::out_of_range("Size must be bigger than 0");
        }
        return vec;
    }
    
    
    //    iterators
    iterator begin(){
        return vec;
    }
    
    const_iterator cbegin() const{
        return vec;
    }
    
    
    iterator end(){
        return vec + size;
    }
    
    const_iterator  cend() const{
        return vec;
    }
    
    
    
    
    // Capacity
    
    bool empty() const{
        return size == 0;
    }
    
    size_t Size() const{
        return size;
    }
    
    size_t max_size() const{
        return SIZE_MAX / sizeof(T);
    }
    
    
    
    //    reserve
    void reserve(size_t new_cap ){
        if (new_cap > capacity) {
            reallocate(new_cap);
        }
    }
    
    //    shrink_to_fit
    void shrink_to_fit(){
        if (size == 0) {
            delete [] vec;
            vec = nullptr;
            capacity = 0;
        }
        if (capacity > size) {
            reallocate(size);
        }
    }
    
    //    capacity()
    size_t Capacity() const {
        return capacity;
    }
    
    
    
    //  Modifiers
    
    
    //   clear()
    void clear(){
        for (size_t i = 0; i < size; ++i) {
            vec[i].~T();
        }
        size = 0;
    }
    
    //    push_back()
    void push_back( const T& value ){
        if(size == capacity){
            reallocate(capacity == 0 ? 1 : capacity * 2);
            
        }
        vec[size++] = value;
        
    }
    
    void push_back( const T&& value ){
        if(size == capacity){
            reallocate(capacity == 0 ? 1 : capacity * 2);
        }
        vec[size++] = std::move(value);
    }
    
    
    // pop_back()
    void pop_back(){
        if (empty()) {
            return;
        }
        vec[--size].~T();
    }
    
    // insert
    iterator insert(const_iterator pos, const T& value ){
        size_t index = pos - vec;
        
        if (index < 0 || index > size) {
            return nullptr;
        }
        
        shift_to_right(index, 1);
        
        vec[index] = value;
        size++;
        
        return vec + index;
    }
    
    iterator insert(const_iterator pos, const T&& value ){
        size_t index = pos - vec;
        
        if (index < 0 || index > size) {
            return nullptr;
        }
        
        shift_to_right(index, 1);
        
        vec[index] = value;
        size++;
        
        return vec + index;
    }
    
    
    
    iterator insert( const_iterator pos, size_t count, const T& value ){
        size_t index = pos - vec;
        
        if (index < 0 || index > size) {
            return nullptr;
        }
        
        shift_to_right(index, count);
        
        for (size_t i = index; i < index + count; i++) {
            vec[i] = value;
        }
        size += count;
        return vec + index;
    }
    
    
    iterator insert( const_iterator pos, iterator first, iterator last ){
        size_t index = pos - vec;
        
        if (index < 0 || index > size) {
            return nullptr;
        }
        
        size_t count = last  - first;
        
        shift_to_right(index, count);
        
        size_t i = index;
        for (iterator it = first; it < last; it++) {
            vec[i++] = *it;
        }
        size += count;
        return vec + index;
    }
    
    iterator insert( const_iterator pos, std::initializer_list<T> il){
        size_t index = pos - vec;
        
        if (index < 0 || index > size) {
            return nullptr;
        }
        
        size_t count = il.size();
        
        shift_to_right(index, count);
        
        size_t i = 0;
        for (const T& val : il) {
            vec[index + i++] = val;
        }
        
        size += count;
        return vec + index;
    }
    
    // emplace()
    template< class... Args >
    iterator emplace( const_iterator pos, Args&&... args ){
        size_t index = pos - vec;
        
        if (index < 0 || index > size) {
            return nullptr;
        }
        
        shift_to_right(index, 1);
        
        new (vec + index) T(std::forward<Args>(args)...);
        size++;
        return vec + index;
    }
    
    
    template< class... Args >
    void emplace_back( Args&&... args ){
        if(size == capacity){
            reallocate(capacity == 0 ? 1 : capacity * 2);
        }
        new (vec + size) T(std::forward<Args>(args)...);
        size++;
    }
    
    
    // erase()
    
    iterator erase( iterator pos ){
        if (pos < begin() || pos >= end()) {
            return end();
        }
        
        size_t index = pos - vec;
        
        shift_to_left(index, 1);
            
        size--;
        return (index < size) ? (begin() + index) : end();
    }
    
    iterator erase( const_iterator first, const_iterator last ){
        if (first < begin() || last > end() || first > last) {
               return end();
        }
        
        size_t index = first - vec;
        size_t count = last - first;
        
        if (count == 0) {
            return begin() + index;
        }
        
        shift_to_left(index, count);
        
        size -= count;
        return (index < size) ? (begin() + index) : end();
    }


    
    void swap(Vector& other ){
        T * temp = vec;
        vec = other.vec;
        other.vec = temp;
        
        std::size_t tmp_size = size;
        size = other.size;
        other.size = tmp_size;
        
        std::size_t tmp_cap = capacity;
        capacity = other.capacity;
        other.capacity = tmp_cap;
    }
    
    void resize( size_t count ){
        if (count == size) {
            return;
        }
        
        if(size > count) {
            for (size_t i = count; i < size; i++) {
                vec[i].~T();
            }
            size = count;
            
        }
        else if (count > size){
            if (count > capacity) {
                reallocate(count);

            }
            for (size_t i = size; i < count; i++) {
                new (vec + i) T();
            }
            size = count;
        }
    }
    
    void resize( size_t count , const T & value ){
        if (count == size) {
            return;
        }
        
        if(size > count) {
            for (size_t i = count; i < size; i++) {
                vec[i].~T();
            }
            size = count;
            
        }
        else if (count > size){
            if (count > capacity) {
                reallocate(count);
            }
            
            for (size_t i = size; i < count; i++) {
                new (vec + i) T(value);
            }
            size = count;
        }
        
    }

    
private:
    void fill(size_t size, const T & val){
        for (size_t i = 0; i < size; i++) {
            vec[i] = val;
        }
    }
    template <typename U>
    void fill(U first, size_t size){
        for (size_t i = 0; i < size; i++) {
            vec[i] = *(first + i);
        }
    }
    
    void adjust_storage(size_t size){
        if (size > capacity) {
            if (vec != nullptr) {
                delete [] vec;
            }
            capacity = size;
            vec = new T[capacity];
        }
    }
    
    void reallocate(size_t new_cap) {
        T* temp = new T[new_cap];
        
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(temp, vec, sizeof(T) * size);
        } else if constexpr (std::is_move_constructible_v<T>) {
            for (size_t i = 0; i < size; ++i) {
                temp[i] = std::move(vec[i]);
            }
        } else {
            for (size_t i = 0; i < size; ++i) {
                temp[i] = vec[i];
            }
        }

        delete[] vec;
        vec = temp;
        capacity = new_cap;
    }
    
    void shift_to_right(size_t index, size_t count){
        if (size + count > capacity) {
            reallocate(size + count);
        }
        
        if constexpr(std::is_trivially_copyable_v<T>) {
            size_t elements = (size - index) * sizeof(T);
            std::memmove(vec + index + count, vec + index, elements);
        }
        else if constexpr (std::is_move_constructible_v<T>){
            for (size_t i = size; i > index; i--) {
                vec[i + count - 1] = std::move(vec[i - 1]);
            }
        }else{
            for (size_t i = size - 1; i > index; i--) {
                vec[i + count - 1] = vec[i - 1];
            }
        }
    }
    
    void shift_to_left(size_t index, size_t count){
        for (size_t i = 0; i < count; i++) {
            vec[index + i].~T();
        }
        
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::size_t bytes = (size - index - count) * sizeof(T);
            std::memmove(vec + index, vec + index + count, bytes);
        }else{
            for (size_t i = index; i < size - count; i++) {
                if constexpr(std::is_move_constructible_v<T>) {
                    vec[i] = std::move(vec[i + count]);
                }else{
                    vec[i] = vec[i + count];
                }
                
            }
            for (size_t i = size - count; i < size; ++i) {
                vec[i].~T();
            }
        }
        
    }
    

public:
    T * vec;
    size_t size;
    size_t capacity;
    static const int reallocate_index = 2;
};


#endif
