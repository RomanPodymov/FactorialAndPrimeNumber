//
//  factorialprovider.h
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef FACTORIALPROVIDER_H
#define FACTORIALPROVIDER_H

#include <QFutureWatcher>

using FactorialProviderValue = qlonglong;

class FactorialProvider final: public QObject {
    Q_OBJECT

public:
    void load(FactorialProviderValue);

signals:
    void progress(double);
    void valueReceived(FactorialProviderValue);

private:
    QFutureWatcher<FactorialProviderValue> watcher;
    QFuture<FactorialProviderValue> future;
};

#endif // FACTORIALPROVIDER_H
