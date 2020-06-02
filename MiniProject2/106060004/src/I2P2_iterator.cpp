#include "../header/I2P2_iterator.h"

namespace I2P2
{
    /* Your definition for the iterator class goes here */

    // 1. "class" const_iterator
    // destructor
    const_iterator::~const_iterator() {
        delete p_;
        p_ = nullptr;
    }
    // default constructor
    const_iterator::const_iterator() {
        p_ = nullptr;
    }
    // copy constructor
    const_iterator::const_iterator(const const_iterator &rhs) : p_(rhs.p_->clone()) {}
    // constructor
    const_iterator::const_iterator(iterator_impl_base *p) : p_(p->clone()) {}
    
    // operators
    // operator = 
    const_iterator &const_iterator::operator=(const const_iterator &rhs) {
        // maybe?
        p_ = rhs.p_->clone();
        return *this;
    }
    // operator ++x
    const_iterator &const_iterator::operator++() {
        ++*p_;
        return *this;
    }
    // operator x++
    const_iterator const_iterator::operator++(int val) {
        const_iterator temp = *this; //copy constrctor?
        ++*p_;
        return temp;
    }
    // operator --x
    const_iterator &const_iterator::operator--() {
        --*p_;
        return *this;
    }
    // operator x--
    const_iterator const_iterator::operator--(int) {
        const_iterator temp = *this;
        --*p_;
        return temp;
    }
    // operator +=
    const_iterator &const_iterator::operator+=(difference_type offset) {
        while(offset--) {
            ++*p_;
        }
        return *this;
    }
    // operator +
    const_iterator const_iterator::operator+(difference_type offset) const {
        const_iterator it(p_);
        while(offset--) {
            ++it;
        }
        return it;
    }
    // operator -=
    const_iterator &const_iterator::operator-=(difference_type offset) {
        while(offset--) {
            --*p_;
        }
        return *this;
    }
    // operator -
    const_iterator const_iterator::operator-(difference_type offset) const {
        const_iterator it(p_);
        while(offset--) {
            --it;
        }
        return it;
    }
    // operator - (return std::ptrdiff_t)
    const_iterator::difference_type const_iterator::operator-(const const_iterator &rhs) const {
        return (*p_) - *(rhs.p_);
    }
    // operator ->
    const_iterator::pointer const_iterator::operator->() const {
        return (*p_).operator->();
    }
    // operator *
    const_iterator::reference const_iterator::operator*() const {
        return *(*p_);
    }
    // operator []
    const_iterator::reference const_iterator::operator[](difference_type offset) const {
        return (*p_)[0];
    }
    // operator compare
    bool const_iterator::operator==(const const_iterator &rhs) const {
        return (*p_) == *(rhs.p_);
    }
    bool const_iterator::operator!=(const const_iterator &rhs) const {
        return (*p_) != *(rhs.p_);
    }
    bool const_iterator::operator<(const const_iterator &rhs) const {
        return (*p_) < *(rhs.p_);
    }
    bool const_iterator::operator>(const const_iterator &rhs) const {
        return (*p_) > *(rhs.p_);
    }
    bool const_iterator::operator<=(const const_iterator &rhs) const {
        return (*p_) <= *(rhs.p_);
    }
    bool const_iterator::operator>=(const const_iterator &rhs) const {
        return (*p_) >= *(rhs.p_);
    }

    // 2. "class" iterator
    iterator::iterator() {
        p_ = nullptr;
    }
    iterator::iterator(iterator_impl_base *p) {
        this->p_ = p->clone();
    }
    iterator::iterator(const iterator &rhs) {
        this->p_ = rhs.p_->clone();
    }
    iterator &iterator::operator++() {
        ++*p_;
        return *this;
    }
    iterator iterator::operator++(int) {
        iterator temp = *this;
        ++*p_;
        return temp;
    }
    iterator &iterator::operator--() {
        --*p_;
        return *this;
    }
    iterator iterator::operator--(int) {
        iterator temp = *this;
        --*p_;
        return temp;
    }
    iterator &iterator::operator+=(difference_type offset) {
        while(offset--) {
            ++*p_;
        }
        return *this;
    }
    iterator iterator::operator+(difference_type offset) const {
        iterator it(p_);
        while(offset--) {
            ++it;
        }
        return it;
    }
    iterator &iterator::operator-=(difference_type offset) {
        while(offset--) {
            --*p_;
        }
        return *this;
    }
    iterator iterator::operator-(difference_type offset) const {
        iterator it(p_);
        while(offset--) {
            --it;
        }
        return it;
    }
    iterator::difference_type iterator::operator-(const iterator &rhs) const {
        return (*p_) - *(rhs.p_);
    }
    iterator::pointer iterator::operator->() const {
        return (*p_).operator->();
    }
    iterator::reference iterator::operator*() const {
        return *(*p_);
    }
    iterator::reference iterator::operator[](difference_type offset) const {
        return (*p_)[0];
    }

    // 3. "class" vector_iterator
    
    // 4. "class" list_iterator


} // namespace I2P2
