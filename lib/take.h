#pragma once
#include <iostream>


class take {
public:
    explicit take(unsigned long long position): position_(position) {}

    [[nodiscard]] unsigned long long GetPosition() const {
        return position_;
    };
private:
    const unsigned long long position_;
};


template<typename Structure>
class take_view {
public:
    using const_iterator = Structure::const_iterator;

    take_view(const Structure& structure, unsigned long long position):
            begin_(const_iterator(structure.begin())),
            end_(const_iterator(structure.begin())) {
        for (unsigned long long _ = 0; _ < position; ++_) {
            ++end_;
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


template<typename Structure>
take_view<Structure> operator|(const Structure& structure, const take& take) {
    static_assert(std::derived_from<typename Structure::iterator::iterator_category, typename std::forward_iterator_tag> == true, "Invalid iterator type\n");
    return take_view<Structure>(structure, take.GetPosition());
}