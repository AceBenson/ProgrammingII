#include "../header/I2P2_Vector.h"
#include <iostream>
#include <algorithm>

namespace I2P2
{
    /* Your definition for the Vector class goes here */
    Vector::~Vector() {
        clear();
    }
    Vector::Vector() {
        begin_ = nullptr;
        end_ = nullptr;
        last_ = nullptr;
    }
    Vector::Vector(const Vector &rhs) : Vector() {
        reserve(rhs.size());

        int sz = rhs.size();
        for(int i=0; i<sz; ++i) {
            begin_[i] = rhs.begin_[i];
        }
        last_ = begin_ + sz;
    }
    Vector& Vector::operator=(const Vector &rhs) {
        if(this != &rhs) {
            if(begin_ != nullptr) {
                this->~Vector();
            }

            new (this) Vector(rhs);
        }
        return *this;
    }
    iterator Vector::begin() {
        vector_iterator vi(begin_);
        return iterator(&vi);
    }
    const_iterator Vector::begin() const {
        vector_iterator vi(begin_);
        return const_iterator(&vi);
    }
    iterator Vector::end() {
        vector_iterator vi(last_+1);
        return iterator(&vi);
    }
    const_iterator Vector::end() const {
        vector_iterator vi(last_+1);
        return const_iterator(&vi);
    }
    reference Vector::front() {
        return *begin_;
    }
    const_reference Vector::front() const {
        return *begin_;
    }
    reference Vector::back() {
        return *last_;
    }
    const_reference Vector::back() const {
        return *last_;
    }

    reference Vector::operator[](size_type pos) {
        return begin_[pos];
    }
    const_reference Vector::operator[](size_type pos) const {
        return begin_[pos];
    }
    size_type Vector::capacity() const {
        return end_-begin_;
    }
    size_type Vector::size() const {
        return last_-begin_;
    }


    void Vector::clear() { // reallocation is not garanteed
        delete begin_;
        begin_ = nullptr;
        end_ = nullptr;
        last_ = nullptr;
    }
    bool Vector::empty() const {
        return size() == 0;
    }
    void Vector::erase(const_iterator pos) {
        // get pos from iterator
        // &(*pos) // this is pointer to data
        const_iterator it(&vector_iterator(begin_));
        size_type posNum = pos - it;

        size_type i, sz = size();

        for(i = posNum; i<sz-1; ++i) {
            begin_[i] = begin_[i+1];
        }
        last_--;
    }
    void Vector::erase(const_iterator begin, const_iterator end) {
        const_iterator it(&vector_iterator(begin_));
        size_type beginNum = begin - it;
        size_type endNum = end - it;
        size_type length = endNum - beginNum;

        size_type i, sz = size();

        for(i = beginNum; i<sz-length; ++i) {
            begin_[i] = begin_[i+length];
        }
        last_ -= length;
    }
    void Vector::insert(const_iterator pos, size_type count, const_reference val) {
        const_iterator it(&vector_iterator(begin_));
        size_type posNum = pos - it;

        size_type cap = capacity();
        size_type i, sz = size();

        if(cap < sz + count ) {
            cap = std::max((cap+count), (3*cap));
            reserve(cap);
        }

        for(i=sz-1+count; i>=posNum+count; --i) {
            begin_[i] = begin_[i-count];
        }

        for(i=posNum; i<posNum+count; ++i) {
            begin_[i] = val;
        }

        last_ += count;
    }
    void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end) {
        const_iterator it(&vector_iterator(begin_));
        size_type posNum = pos - it;
        size_type beginNum = begin - it;
        size_type endNum = end - it;
        size_type length = endNum - beginNum;

        size_type cap = capacity();
        size_type i, sz = size();

        if(cap < sz + length ) {
            cap = std::max((cap+length), (3*cap));
            reserve(cap);
        }

        for(i=sz-1+length; i>=posNum+length; --i) {
            begin_[i] = begin_[i-length];
        }

        for(i=posNum; i<posNum+length; ++i) {
            begin_[i] = *(begin_+i-posNum);
        }

        last_ += length;
    }
    void Vector::pop_back() {
        last_--;
    }
    void Vector::pop_front() {
        size_type i, sz = size();

        for(i = 0; i<sz-1; ++i) {
            begin_[i] = begin_[i+1];
        }

        last_--;
    }
    void Vector::push_back(const_reference val) {
        
    }
    void Vector::push_front(const_reference val) {

    }
    void Vector::reserve(size_type new_capacity) {

    }
    void Vector::shrink_to_fit() {

    }

} // namespace I2P2
