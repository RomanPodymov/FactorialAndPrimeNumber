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

signals:
    void progress(double);
    void valueReceived(FactorialProviderValue);
    void valueReceived(QString);

protected:
    void setupFuture(FactorialProviderValue) override;

private:
    bool preprocessValue(FactorialProviderValue);
};

#endif // FACTORIALPROVIDER_H
