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
    if (preprocessValue(value)) {
        return;
    }
    setupFuture(value);
    QObject::connect(&watcher, &QFutureWatcher<FactorialSequenceResult>::finished, [&]() {
        emit valueReceived(future.result().value);
        emit valueReceived(QString(future.result().value));
    });
    QObject::connect(&watcher, &QFutureWatcher<FactorialSequenceResult>::suspended, [&]() {
        emit paused();
    });
    watcher.setFuture(future);
}

void FactorialProvider::load(QString value) {
    load(FactorialProviderValue(value));
}

void FactorialProvider::setupFuture(FactorialProviderValue value) { 
    IntegerSequence<FactorialProviderValue, qsizetype> factorialSequence(1, value + FactorialProviderValue(1));
    future = QtConcurrent::mappedReduced<FactorialSequenceResult>(factorialSequence.begin(), factorialSequence.end(), [](auto data) {
        return data;
    }, [&](FactorialSequenceResult& result, auto data) {
        if (result.value.isEmpty()) {
            result.value = 1;
        }
        result.value = result.value * data.value;
        EMIT_PROGRESS(data, result)
    }, QtConcurrent::ReduceOption::OrderedReduce | QtConcurrent::ReduceOption::SequentialReduce);
}

bool FactorialProvider::preprocessValue(FactorialProviderValue value) {
    if (value == FactorialProviderValue(0)) {
        emit progress(1.0);
        emit valueReceived(FactorialProviderValue(1));
        return true;
    }
    return false;
}
