//
//  primenumberprovider.h
//  App
//
//  Created by Roman Podymov on 06/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef PRIMENUMBERPROVIDER_H
#define PRIMENUMBERPROVIDER_H

#include "valueprovider.h"
#include <QVector>

using PrimeNumberProviderInputValue = qsizetype;
using PrimeNumberProviderOutputValue = QVector<qsizetype>;

struct PrimeNumberSequenceResult: public SequenceResult<PrimeNumberProviderOutputValue> { };

class PrimeNumberProvider final: public ValueProvider<PrimeNumberProviderInputValue, PrimeNumberSequenceResult> {
    Q_OBJECT

public:
    void load(PrimeNumberProviderInputValue) override;

signals:
    void progress(double);
    void valueReceived(PrimeNumberProviderOutputValue);

protected:
    void setupFuture(PrimeNumberProviderInputValue) override;

private:
    bool isPrimeNumber(PrimeNumberProviderInputValue);
};

#endif // PRIMENUMBERPROVIDER_H
