#pragma once
#include <iostream>


class keys {};


template<typename Iterator>
class keys_iterator {
public:
    explicit keys_iterator(const Iterator& structure_iterator) : ptr_(structure_iterator) {}

    keys_iterator& operator++() {
        ++ptr_;
        return *this;
    }
    keys_iterator operator++(int) {
        keys_iterator temp(*this);
        ++(*this);
        return temp;
    }

    keys_iterator& operator--() {
        --ptr_;
        return *this;
    }
    keys_iterator operator--(int) {
        keys_iterator temp(*this);
        --(*this);
        return temp;
    }

    bool operator!=(const keys_iterator& other) const {
        return ptr_ != other.ptr_;
    }
    bool operator==(const keys_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    auto operator*() const {
        return ptr_->first;
    }
private:
    Iterator ptr_;
};


template<typename Structure>
class keys_view {
public:
    using const_iterator = keys_iterator<typename Structure::const_iterator>;

    explicit keys_view(const Structure& structure):
            begin_(const_iterator(structure.begin())),
            end_(const_iterator(structure.end())) {}

    const_iterator begin() const {
        return begin_;
    }
    const_iterator end() const {
        return end_;
    }
private:
    const_iterator begin_;
    const_iterator end_;
};


template<typename Structure>
keys_view<Structure> operator|(const Structure& structure, const keys& keys) {
    static_assert(std::derived_from<typename Structure::iterator::iterator_category, typename std::forward_iterator_tag> == true, "Invalid iterator type\n");
    return keys_view<Structure>(structure);
}