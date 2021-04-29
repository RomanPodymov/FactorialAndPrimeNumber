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
    QVector<FactorialProviderValue> arr;
    for (FactorialProviderValue i = 1; i < value; i++) {
        arr.append(i);
    }
    future = QtConcurrent::mappedReduced<FactorialProviderValue>(arr, [](FactorialProviderValue number) {
        return number;
    }, [](FactorialProviderValue &result, FactorialProviderValue currentNumber) {
        if (result == 0) {
            result = currentNumber;
        } else {
            result *= currentNumber;
        }
    });
    QObject::connect(&watcher, &QFutureWatcher<FactorialProviderValue>::finished, [&]() {
        emit valueReceived(future.result());
    });
    watcher.setFuture(future);
}
