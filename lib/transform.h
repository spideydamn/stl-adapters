#pragma once
#include <iostream>


template<typename Function>
class transform {
public:
    explicit transform(const Function& function): function_(function) {}

    Function GetFunction() const {
        return function_;
    };
private:
    const Function function_;
};


template<typename Iterator, typename Function>
class transform_iterator {
public:
    transform_iterator(const Iterator& structure_iterator, const Function& function) : ptr_(structure_iterator), function_(function) {}

    transform_iterator& operator++() {
        ++ptr_;
        return *this;
    }
    transform_iterator operator++(int) {
        transform_iterator temp(*this);
        ++(*this);
        return temp;
    }

    transform_iterator& operator--() {
        --ptr_;
        return *this;
    }
    transform_iterator operator--(int) {
        transform_iterator temp(*this);
        --(*this);
        return temp;
    }

    bool operator!=(const transform_iterator& other) const {
        return ptr_ != other.ptr_;
    }
    bool operator==(const transform_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    auto operator*() const {
        return function_(*ptr_);
    }
private:
    Iterator ptr_;
    Function function_;
};


template<typename Structure, typename Function>
class transform_view {
public:
    using const_iterator = transform_iterator<typename Structure::const_iterator, Function>;

    transform_view(const Structure& structure, const Function& function):
        begin_(const_iterator(structure.begin(), function)),
        end_(const_iterator(structure.end(), function)) {}

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


template<typename Structure, typename Function>
transform_view<Structure, Function> operator|(const Structure& structure, const transform<Function>& transform) {
    static_assert(std::derived_from<typename Structure::iterator::iterator_category, typename std::forward_iterator_tag> == true, "Invalid iterator type\n");
    return transform_view<Structure, Function>(structure, transform.GetFunction());
}