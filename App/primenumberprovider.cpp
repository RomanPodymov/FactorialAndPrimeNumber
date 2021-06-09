//
//  primenumberprovider.cpp
//  App
//
//  Created by Roman Podymov on 06/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "primenumberprovider.h"
#include <QFuture>
#include <QtConcurrent>

void PrimeNumberProvider::load(PrimeNumberProviderInputValue value) {
    VALUE_PROVIDER_LOAD(PrimeNumberSequenceResult, value)
}

void PrimeNumberProvider::load(QString value) {
    load(PrimeNumberProviderInputValue(value.toUInt()));
}

void PrimeNumberProvider::cancel() {
    ValueProvider::cancel();
    emit canceled();
}

void PrimeNumberProvider::setupFuture(PrimeNumberProviderInputValue value) {
    integerSequence = new IntegerSequence<PrimeNumberProviderInputValue, qsizetype>(1, value + PrimeNumberProviderInputValue(1));
    future = QtConcurrent::mappedReduced<PrimeNumberSequenceResult>(integerSequence->begin(), integerSequence->end(), [](auto data) {
        return data;
    }, [&](PrimeNumberSequenceResult& result, auto data) {
        if (isPrimeNumber(data.value)) {
            result.value.append(data.value);
        }
        if (!integerSequence->canceled) {
            EMIT_PROGRESS(data, result)
        }
    }, QtConcurrent::ReduceOption::OrderedReduce | QtConcurrent::ReduceOption::SequentialReduce);
}

QString PrimeNumberProvider::stringValue(PrimeNumberProviderOutputValue value) {
    QString result;
    for (const auto& number : value) {
        result += QString::number(number);
        result += " ";
    }
    return result;
}

bool PrimeNumberProvider::isPrimeNumber(PrimeNumberProviderInputValue value) {
    for (auto i = 1; i <= value; ++i) {
        if (value % i == 0 && i != 1 && i != value) {
            return false;
        }
    }
    return true;
}
