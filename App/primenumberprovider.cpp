//
//  primenumberprovider.cpp
//  App
//
//  Created by Roman Podymov on 06/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "integersequence.h"
#include "primenumberprovider.h"
#include <QFuture>
#include <QtConcurrent>

void PrimeNumberProvider::load(PrimeNumberProviderInputValue value) {
    setupFuture(value);
    QObject::connect(&watcher, &QFutureWatcher<PrimeNumberSequenceResult>::finished, [&]() {
        emit valueReceived(future.result().value);
        QString result;
        for (const auto& number : future.result().value) {
            result += QString::number(number);
            result += " ";
        }
        emit valueReceived(result);
    });
    QObject::connect(&watcher, &QFutureWatcher<PrimeNumberSequenceResult>::suspended, [&]() {
        emit paused();
    });
    QObject::connect(&watcher, &QFutureWatcher<PrimeNumberSequenceResult>::resumed, [&]() {
        emit resumed();
    });
    QObject::connect(&watcher, &QFutureWatcher<PrimeNumberSequenceResult>::canceled, [&]() {
        emit canceled();
    });
    watcher.setFuture(future);
}

void PrimeNumberProvider::load(QString value) {
    load(PrimeNumberProviderInputValue(value.toUInt()));
}

void PrimeNumberProvider::setupFuture(PrimeNumberProviderInputValue value) {
    IntegerSequence<PrimeNumberProviderInputValue, qsizetype> numbersSequence(1, value + PrimeNumberProviderInputValue(1));
    future = QtConcurrent::mappedReduced<PrimeNumberSequenceResult>(numbersSequence.begin(), numbersSequence.end(), [](auto data) {
        return data;
    }, [&](PrimeNumberSequenceResult& result, auto data) {
        if (isPrimeNumber(data.value)) {
            result.value.append(data.value);
        }
        EMIT_PROGRESS(data, result)
    }, QtConcurrent::ReduceOption::OrderedReduce | QtConcurrent::ReduceOption::SequentialReduce);
}

bool PrimeNumberProvider::isPrimeNumber(PrimeNumberProviderInputValue value) {
    for (auto i = 1; i <= value; ++i) {
        if (value % i == 0 && i != 1 && i != value) {
            return false;
        }
    }
    return true;
}
