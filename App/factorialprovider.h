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

struct FactorialSequenceResult: public SequenceResult<FactorialProviderValue> { };

class FactorialProvider final: public ValueProvider<FactorialProviderValue, FactorialSequenceResult> {
    Q_OBJECT

public:
    void load(FactorialProviderValue) override;

signals:
    void progress(double);
    void valueReceived(FactorialProviderValue);

private:
    bool preprocessValue(FactorialProviderValue);
};

#endif // FACTORIALPROVIDER_H
