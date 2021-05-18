//
//  valueprovider.h
//  App
//
//  Created by Roman Podymov on 06/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef VALUEPROVIDER_H
#define VALUEPROVIDER_H

#include <QFutureWatcher>

#define EMIT_PROGRESS(data, result) \
    const auto position = data.position + 1; \
    if (position != result.position) { \
        result.position = position; \
        const auto progressValue = double(position) / data.maxPosition; \
        emit progress(progressValue); \
    }

template <typename ValueType>
struct SequenceResult {
    SequenceResult(): value(ValueType()), position(0) { }

    ValueType value;
    qsizetype position;
};

template <typename InputValueType, typename OutputValueType>
class ValueProvider: public QObject {

public:
    virtual void load(InputValueType) = 0;
    virtual void load(QString) = 0;
    void pause() {
        future.suspend();
    }
    void resume() {
        future.resume();
    }

protected:
    virtual void setupFuture(InputValueType) = 0;

protected:
    QFutureWatcher<SequenceResult<OutputValueType>> watcher;
    QFuture<SequenceResult<OutputValueType>> future;
};

#endif // VALUEPROVIDER_H
