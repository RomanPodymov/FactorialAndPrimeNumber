//
//  primenumberprovider.h
//  App
//
//  Created by Roman Podymov on 06/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef PRIMENUMBERPROVIDER_H
#define PRIMENUMBERPROVIDER_H

#include <QFutureWatcher>
#include <QVector>

using PrimeNumberProviderInputValue = qsizetype;
using PrimeNumberProviderOutputValue = QVector<qsizetype>;

class PrimeNumberProvider final: public QObject {
    Q_OBJECT

public:
    void load(PrimeNumberProviderInputValue);

signals:
    void valueReceived(PrimeNumberProviderOutputValue);

private:
    bool isPrimeNumber(PrimeNumberProviderInputValue);

private:
    QFutureWatcher<PrimeNumberProviderOutputValue> watcher;
    QFuture<PrimeNumberProviderOutputValue> future;
};

#endif // PRIMENUMBERPROVIDER_H
