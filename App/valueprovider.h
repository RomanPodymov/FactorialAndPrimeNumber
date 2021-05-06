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

template <typename ValueType>
struct SequenceResult {
    SequenceResult(): value(ValueType()), position(0) { }

    ValueType value;
    qsizetype position;
};

template <typename InputValueType, typename SequenceResultType>
class ValueProvider: public QObject {

public:
    virtual void load(InputValueType) = 0;

protected:
    QFutureWatcher<SequenceResultType> watcher;
    QFuture<SequenceResultType> future;
};

#endif // VALUEPROVIDER_H
