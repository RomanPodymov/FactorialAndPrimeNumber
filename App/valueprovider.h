//
//  valueprovider.h
//  App
//
//  Created by Roman Podymov on 06/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef VALUEPROVIDER_H
#define VALUEPROVIDER_H

#include "integersequence.h"
#include <QFutureWatcher>

#define EMIT_PROGRESS(data, result) \
    const auto position = data.position + 1; \
    if (position != result.position) { \
        result.position = position; \
        const auto progressValue = double(position) / data.maxPosition; \
        emit progress(progressValue); \
    }

#define VALUE_PROVIDER_LOAD(SEQUENCE_RESULT_TYPE, value) \
    if (preprocessValue(value)) { \
        return; \
    } \
    setupFuture(value); \
    QObject::connect(&watcher, &QFutureWatcher<SEQUENCE_RESULT_TYPE>::finished, [&]() { \
        if (!integerSequence->canceled) { \
            emit valueReceived(future.result().value); \
            emit valueReceived(stringValue(future.result().value)); \
        } \
    }); \
    QObject::connect(&watcher, &QFutureWatcher<SEQUENCE_RESULT_TYPE>::suspended, [&]() { \
        emit paused(); \
    }); \
    QObject::connect(&watcher, &QFutureWatcher<SEQUENCE_RESULT_TYPE>::resumed, [&]() { \
        emit resumed(); \
    }); \
    QObject::connect(&watcher, &QFutureWatcher<SEQUENCE_RESULT_TYPE>::canceled, [&]() { \
        emit canceled(); \
    }); \
    watcher.setFuture(future);

template <typename ValueType>
struct SequenceResult {
    SequenceResult(): value(ValueType()), position(0) { }

    ValueType value;
    qsizetype position;
};

template <typename InputValueType, typename OutputValueType>
class ValueProvider: public QObject {

public:
    ~ValueProvider() {
        if (!integerSequence->canceled) {
            cancelDefault();
        }
        delete integerSequence;
    }
    virtual void load(InputValueType) = 0;
    virtual void load(QString) = 0;
    void pause() {
        future.suspend();
    }
    void resume() {
        future.resume();
    }
    virtual void cancel() {
        cancelDefault();
    }

protected:
    virtual bool preprocessValue(InputValueType) { return false; }
    virtual void setupFuture(InputValueType) = 0;
    virtual QString stringValue(OutputValueType) = 0;

private:
    void cancelDefault() {
        integerSequence->cancel();
        if (future.isSuspended()) {
            resume();
        }
        future.waitForFinished();
    }

public:
    QFutureWatcher<SequenceResult<OutputValueType>> watcher;

protected:
    QFuture<SequenceResult<OutputValueType>> future;
    IntegerSequence<InputValueType, qsizetype>* integerSequence;
};

#endif // VALUEPROVIDER_H
