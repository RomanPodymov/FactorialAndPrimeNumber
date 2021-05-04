//
//  factorialprovider.cpp
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "factorialprovider.h"
#include "integersequence.h"
#include <QFuture>
#include <QtConcurrent>

void FactorialProvider::load(FactorialProviderValue value) {
    IntegerSequence<FactorialProviderValue> factorialSequence(1, value + 1);
    future = QtConcurrent::mappedReduced<FactorialProviderValue>(factorialSequence.begin(), factorialSequence.end(), [](IntegerSequence<FactorialProviderValue>::ConstIterator::Data data) {
        return data;
    }, [&](FactorialProviderValue &result, IntegerSequence<FactorialProviderValue>::ConstIterator::Data data) {
        if (result == 0) {
            result = 1;
        }
        result *= data.value;
        const auto progressValue = double(data.position + 1) / data.maxPosition;
        emit progress(progressValue);
    });
    QObject::connect(&watcher, &QFutureWatcher<FactorialProviderValue>::finished, [&]() {
        emit valueReceived(future.result());
    });
    watcher.setFuture(future);
}
