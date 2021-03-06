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
#include "valueprovider.h"

using FactorialProviderValue = BigInteger<int>;
using FactorialSequenceResult = SequenceResult<FactorialProviderValue>;

class FactorialProvider final: public ValueProvider<FactorialProviderValue, FactorialProviderValue> {
    Q_OBJECT

public:
    void load(FactorialProviderValue) override;
    void load(QString) override;
    void cancel() override;

signals:
    void progress(double);
    void paused();
    void resumed();
    void canceled();
    void valueReceived(FactorialProviderValue);
    void valueReceived(QString);

protected:
    bool preprocessValue(FactorialProviderValue) override;
    void setupFuture(FactorialProviderValue) override;
    QString stringValue(FactorialProviderValue) override;
};

#endif // FACTORIALPROVIDER_H
