#include "../header/I2P2_Vector.h"
#include <iostream>

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
        return size_;
    }


    void Vector::clear() { // reallocation is not garanteed
        delete begin_;
        begin_ = nullptr;
        end_ = nullptr;
        last_ = nullptr;
    }
    bool Vector::empty() const {
        return size_ == 0;
    }
    void Vector::erase(const_iterator pos) {
        std::cout << (*pos); //reference to value_type
        // list have iterator to node??

        if(pos < begin() || pos >= end()) {
            return;
        }

        for(const_iterator it = pos; it != end(); ++it) {
            // ?
        }
        last_--;
        size_--;
    }
    void Vector::erase(const_iterator begin, const_iterator end) {

    }
    void Vector::insert(const_iterator pos, size_type count, const_reference val) {

    }
    void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end) {

    }
    void Vector::pop_back() {

    }
    void Vector::pop_front() {

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
