//
//  integersequence.h
//  App
//
//  Created by Roman Podymov on 03/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef INTEGERSEQUENCE_H
#define INTEGERSEQUENCE_H

#include <iterator>

template <typename T>
class IntegerSequence final {

public:
    class ConstIterator final {

    public:
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;

        ConstIterator(T value) : value(value) { }
        ConstIterator operator++() { ConstIterator i = *this; value++; return i; }
        const T& operator*() { return value; }
        bool operator!=(const ConstIterator& rhs) { return value != rhs.value; }

    private:
        T value;
    };

    IntegerSequence(T min, T max) : min(min), max(max) { }

    ConstIterator begin() const {
        return ConstIterator(min);
    }

    ConstIterator end() const {
        return ConstIterator(max);
    }

private:
    T min;
    T max;
};

#endif // INTEGERSEQUENCE_H
