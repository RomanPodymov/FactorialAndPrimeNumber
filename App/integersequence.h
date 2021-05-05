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

template <typename T, typename Size>
class IntegerSequence final {

public:
    class ConstIterator final {

    public:
        struct Data;

        typedef Size difference_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef Data value_type;
        typedef Data& reference;
        typedef Data* pointer;

        struct Data {
            Data(T value, Size position, Size maxPosition): value(value),
                position(position),
                maxPosition(maxPosition) {

            }

            T value;
            Size position;
            Size maxPosition;
        };

        ConstIterator(T value, Size position, Size maxPosition) : data(value, position, maxPosition) { }
        ConstIterator operator++() {
            ConstIterator i = *this;
            data = Data(data.value + T(1), data.position + 1, data.maxPosition);
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
