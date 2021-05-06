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
    IntegerSequence<PrimeNumberProviderInputValue, qsizetype> numbersSequence(1, value + PrimeNumberProviderInputValue(1));
    future = QtConcurrent::mappedReduced<PrimeNumberProviderOutputValue>(numbersSequence.begin(), numbersSequence.end(), [](auto data) {
        return data;
    }, [&](PrimeNumberProviderOutputValue& result, auto data) {
        if (isPrimeNumber(data.value)) {
            result.append(data.value);
        }
    }, QtConcurrent::ReduceOption::OrderedReduce | QtConcurrent::ReduceOption::SequentialReduce);
    QObject::connect(&watcher, &QFutureWatcher<PrimeNumberProviderOutputValue>::finished, [&]() {
        emit valueReceived(future.result());
    });
    watcher.setFuture(future);
}

bool PrimeNumberProvider::isPrimeNumber(PrimeNumberProviderInputValue value) {
    for (auto i = 1; i <= value; ++i) {
        if (value % i == 0 && i != 1 && i != value) {
            return false;
        }
    }
    return true;
}
