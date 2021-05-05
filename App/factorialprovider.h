//
//  factorialprovider.h
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef FACTORIALPROVIDER_H
#define FACTORIALPROVIDER_H

#include "biginteger.h"
#include <QFutureWatcher>

using FactorialProviderValue = BigInteger<int>;

struct FactorialSequenceResult {
    FactorialSequenceResult(): value(FactorialProviderValue()), position(0) { }

    FactorialProviderValue value;
    qsizetype position;
};

class FactorialProvider final: public QObject {
    Q_OBJECT

public:
    void load(FactorialProviderValue);

signals:
    void progress(double);
    void valueReceived(FactorialProviderValue);

private:
    QFutureWatcher<FactorialSequenceResult> watcher;
    QFuture<FactorialSequenceResult> future;
};

#endif // FACTORIALPROVIDER_H
