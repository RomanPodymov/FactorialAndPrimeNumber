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
        struct Data;

        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef Data value_type;
        typedef Data& reference;
        typedef Data* pointer;

        struct Data {
            Data(T value, difference_type position, difference_type maxPosition): value(value),
                position(position),
                maxPosition(maxPosition) {

            }

            T value;
            difference_type position;
            difference_type maxPosition;
        };

        ConstIterator(T value, difference_type position, difference_type maxPosition) : data(value, position, maxPosition) { }
        ConstIterator operator++() {
            ConstIterator i = *this;
            data = Data(data.value + 1, data.position + 1, data.maxPosition);
            return i;
        }
        reference& operator*() { return data; }
        bool operator!=(const ConstIterator& rhs) { return data.position != rhs.data.position; }

    private:
        Data data;
    };

    IntegerSequence(T min, T max) : min(min), max(max) { }

    ConstIterator begin() const {
        return ConstIterator(min, 0, max - min);
    }

    ConstIterator end() const {
        return ConstIterator(max, max - min, max - min);
    }

private:
    T min;
    T max;
};

#endif // INTEGERSEQUENCE_H
