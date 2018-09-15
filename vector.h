//
// Created by Yaroslav239 on 13.09.2018.
//

#ifndef TASK_FOR_EXAM_VECTOR_H
#define TASK_FOR_EXAM_VECTOR_H

#include <iostream>
#include <type_traits>
#include <string>

template<class T, size_t N>
struct arr {
    typedef T * iterator;
    typedef T const * const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

public:
    arr() :size_cur(0),capacity_arr(N) {};

    arr(arr const &other)
        :size_cur(other.size_cur), capacity_arr(other.capacity_arr) {
        for (size_t i = 0; i < size_cur; i++) {
            new(data + i) T(other.data[i]);
        }
    }

    ~arr() {
        for (size_t i = 0; i < size_cur; i++) {
            destroy(i);
        }
        capacity_arr = 0;
        size_cur = 0;
    }

    arr &operator=(arr const &other) {
        for (size_t i = 0; i < size_cur; i++) {
            destroy_const(i);
        }
        for (size_t i = 0; i < other.size_cur; i++) {
            //!!
            auto place = reinterpret_cast<T *>(data) + i;
            new (reinterpret_cast<T *>(data) + i)T(reinterpret_cast<const T *>(other.data)[i]);
        }
        size_cur = other.size_cur;
        return *this;
    }

    ///?????
    iterator insert (const_iterator it, const T &a) {
        if (size_cur != capacity_arr /*&& size_cur > it - (T *) data*/) {
            iterator pos = (T *) data + (it - (T *) data);
            push_back(back());
            for (iterator i = (end() - 1); i != pos; i--) {
                ////?????
//                if (i - 1 > begin() && i < end()) {
                   *i = *(i - 1);
//                }
            }
            //std::cout << std::endl << " pos : "<< (int)(pos - (T*) data) << "; val : " << a << std::endl;
            *(pos) = a;
            return pos;
        } else {
            throw std::length_error("overflow");
        }
    }


    ///?????????????
    iterator erase(const_iterator it) {
        iterator pos = (T *) data + (it - (T *) data);
        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator l, const_iterator r) {
        iterator left = (T *) data + ((T *)l - (T *) data);
        iterator right = (T *) data + ((T *)r - (T *) data);
        iterator ans = left;
        for (;right != end(); right++,left++) {
            ///??????
            //std::cout << 1 << std::endl;
            *left = *right;
        }
        for (size_t i = (size_t)(left - (T *)data); i < size_cur; i++) {
            //std::cout << 2;
            destroy(i);
        }
        size_cur = left - (T *) data;
        return ans;
    }

    void push_back(T const& a) {
        if (size_cur != capacity_arr) {
            new(&data[size_cur])T(a);
            size_cur++;
            return;
        } else {
            throw std::length_error("overflow");
        }
    }

    void pop_back() {
        if (size_cur != 0) {
            size_cur--;
            destroy(size_cur);
        }
    }

    T& back() {
        return *((T*)data + size_cur - 1);
    }

    T const& back() const {
        return *((const T*)data + size_cur - 1);
    }

    T& front() {
        return *((T*)data);
    }

    T const & front() const {
        return data[0];
    }

    size_t size() const {
        return size_cur;
    }

    bool empty() const {
        return size_cur == 0;
    }

    size_t capacity() const {
        return capacity_arr;
    }

    size_t max_size() const {
        return capacity_arr;
    }
    iterator begin() {
        return reinterpret_cast<T*>(data);
    }

    const_iterator begin() const {
        return reinterpret_cast<T const*>(data);
    }

    iterator end() {
        return reinterpret_cast<T*>(data) + size_cur;
    }

    T &operator[](size_t n) {
        return reinterpret_cast<T*>(data)[n];
    }

    T const &operator[](size_t n) const {
        return reinterpret_cast<T const*>(data)[n];
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    const_iterator end() const {
        return reinterpret_cast<T const*>(data) + size_cur;
    }

    void clear() {
        for (size_t i = 0; i < size_cur; ++i) {
            destroy(i);
        }
        size_cur = 0;
    }


private:
    void destroy_const(size_t ind) {
        reinterpret_cast<T const *>(data + ind)->~T();
    }
    void destroy(size_t ind) {
        reinterpret_cast<T *>(data + ind) ->~T();
    }

    typename std::aligned_storage<sizeof(T), alignof(T)>::type data[N];
    size_t size_cur;
    size_t capacity_arr;
};



#endif //TASK_FOR_EXAM_VECTOR_H