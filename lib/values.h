#pragma once
#include <iostream>


class values {};


template<typename Iterator>
class values_iterator {
public:
    explicit values_iterator(const Iterator& structure_iterator) : ptr_(structure_iterator) {}

    values_iterator& operator++() {
        ++ptr_;
        return *this;
    }
    values_iterator operator++(int) {
        values_iterator temp(*this);
        ++(*this);
        return temp;
    }

    values_iterator& operator--() {
        --ptr_;
        return *this;
    }
    values_iterator operator--(int) {
        values_iterator temp(*this);
        --(*this);
        return temp;
    }

    bool operator!=(const values_iterator& other) const {
        return ptr_ != other.ptr_;
    }
    bool operator==(const values_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    auto operator*() const {
        return ptr_->second;
    }
private:
    Iterator ptr_;
};


template<typename Structure>
class values_view {
public:
    using const_iterator = values_iterator<typename Structure::const_iterator>;

    explicit values_view(const Structure& structure):
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
values_view<Structure> operator|(const Structure& structure, const values& values) {
    static_assert(std::derived_from<typename Structure::iterator::iterator_category, typename std::forward_iterator_tag> == true, "Invalid iterator type\n");
    return values_view<Structure>(structure);
}