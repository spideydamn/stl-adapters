#pragma once
#include <iostream>


class reverse {};


template<typename Iterator>
class reverse_iterator {
public:
    explicit reverse_iterator(const Iterator& structure_iterator) : ptr_(structure_iterator) {}

    reverse_iterator& operator++() {
        --ptr_;
        return *this;
    }
    reverse_iterator operator++(int) {
        reverse_iterator temp(*this);
        --(*this);
        return temp;
    }

    reverse_iterator& operator--() {
        ++ptr_;
        return *this;
    }
    reverse_iterator operator--(int) {
        reverse_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator!=(const reverse_iterator& other) const {
        return ptr_ != other.ptr_;
    }
    bool operator==(const reverse_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    auto operator*() const {
        return *ptr_;
    }
private:
    Iterator ptr_;
};


template<typename Structure>
class reverse_view {
public:
    using const_iterator = reverse_iterator<typename Structure::const_iterator>;

    explicit reverse_view(const Structure& structure):
            begin_(const_iterator(--structure.end())),
            end_(const_iterator(--structure.begin())) {}

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
reverse_view<Structure> operator|(const Structure& structure, const reverse& reverse) {
    static_assert(std::derived_from<typename Structure::iterator::iterator_category, typename std::forward_iterator_tag> == true, "Invalid iterator type\n");
    return reverse_view<Structure>(structure);
}