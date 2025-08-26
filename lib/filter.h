#pragma once
#include <iostream>


template<typename Function>
class filter {
public:
    explicit filter(const Function& function): function_(function) {}

    Function GetFunction() const {
        return function_;
    };
private:
    const Function function_;
};


template<typename Iterator, typename Function>
class filter_iterator {
public:
    filter_iterator(const Iterator& structure_iterator, const Iterator &end, const Function& function) : ptr_(structure_iterator), end_(end), function_(function) {}

    filter_iterator& operator++() {
        ++ptr_;
        while (ptr_ != end_ && !function_(*ptr_)) {
            ++ptr_;
        }
        return *this;
    }
    filter_iterator operator++(int) {
        filter_iterator temp(*this);
        ++(*this);
        return temp;
    }

    filter_iterator& operator--() {
        --ptr_;
        while (ptr_ != end_ && !function_(*ptr_)) {
            --ptr_;
        }
        return *this;
    }
    filter_iterator operator--(int) {
        filter_iterator temp(*this);
        --(*this);
        return temp;
    }

    bool operator!=(const filter_iterator& other) const {
        return ptr_ != other.ptr_;
    }
    bool operator==(const filter_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    auto operator*() const {
        return *ptr_;
    }
private:
    Iterator ptr_;
    Iterator end_;
    Function function_;
};


template<typename Structure, typename Function>
class filter_view {
public:
    using const_iterator = filter_iterator<typename Structure::const_iterator, Function>;

    filter_view(const Structure& structure, const Function& function):
            begin_(const_iterator(structure.begin(), structure.end(), function)),
            end_(const_iterator(structure.end(), structure.end(), function)) {
        while (begin_ != end_ && !function(*begin_)) {
            ++begin_;
        }
    }

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
filter_view<Structure, Function> operator|(const Structure& structure, const filter<Function>& filter) {
    static_assert(std::derived_from<typename Structure::iterator::iterator_category, typename std::forward_iterator_tag> == true, "Invalid iterator type\n");
    return filter_view<Structure, Function>(structure, filter.GetFunction());
}