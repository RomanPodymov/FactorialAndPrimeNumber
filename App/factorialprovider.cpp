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
    IntegerSequence<FactorialProviderValue, qsizetype> factorialSequence(1, value + FactorialProviderValue(1));
    future = QtConcurrent::mappedReduced<FactorialSequenceResult>(factorialSequence.begin(), factorialSequence.end(), [](auto data) {
        return data;
    }, [&](FactorialSequenceResult& result, auto data) {
        if (result.value.isEmpty()) {
            result.value = 1;
        }
        result.value = result.value * data.value;
        const auto position = data.position + 1;
        if (position != result.position) {
            result.position = position;
            const auto progressValue = double(position) / data.maxPosition;
            emit progress(progressValue);
        }
    }, QtConcurrent::ReduceOption::OrderedReduce | QtConcurrent::ReduceOption::SequentialReduce);
    QObject::connect(&watcher, &QFutureWatcher<FactorialSequenceResult>::finished, [&]() {
        emit valueReceived(future.result().value);
    });
    watcher.setFuture(future);
}
