//
//  factorialprovider.cpp
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "factorialprovider.h"
#include <QFuture>
#include <QtConcurrent>

void FactorialProvider::load(FactorialProviderValue value) {
    VALUE_PROVIDER_LOAD(FactorialSequenceResult, value)
}

void FactorialProvider::load(QString value) {
    load(FactorialProviderValue(value));
}

void FactorialProvider::cancel() {
    ValueProvider::cancel();
    emit canceled();
}

bool FactorialProvider::preprocessValue(FactorialProviderValue value) {
    if (value == FactorialProviderValue(0)) {
        emit progress(1.0);
        emit valueReceived(FactorialProviderValue(1));
        return true;
    }
    return false;
}

void FactorialProvider::setupFuture(FactorialProviderValue value) { 
    integerSequence = new IntegerSequence<FactorialProviderValue, qsizetype>(1, value + FactorialProviderValue(1));
    future = QtConcurrent::mappedReduced<FactorialSequenceResult>(integerSequence->begin(), integerSequence->end(), [](auto data) {
        return data;
    }, [&](FactorialSequenceResult& result, auto data) {
        if (result.value.isEmpty()) {
            result.value = 1;
        }
        result.value = result.value * data.value;
        if (!integerSequence->canceled) {
            EMIT_PROGRESS(data, result)
        }
    }, QtConcurrent::ReduceOption::OrderedReduce | QtConcurrent::ReduceOption::SequentialReduce);
}

QString FactorialProvider::stringValue(FactorialProviderValue value) {
    return QString(value);
}
