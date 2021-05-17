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
using PrimeNumberSequenceResult = SequenceResult<PrimeNumberProviderOutputValue>;

class PrimeNumberProvider final: public ValueProvider<PrimeNumberProviderInputValue, PrimeNumberProviderOutputValue> {
    Q_OBJECT

public:
    void load(PrimeNumberProviderInputValue) override;
    void load(QString) override;

signals:
    void progress(double);
    void paused();
    void valueReceived(PrimeNumberProviderOutputValue);
    void valueReceived(QString);

protected:
    void setupFuture(PrimeNumberProviderInputValue) override;

private:
    bool isPrimeNumber(PrimeNumberProviderInputValue);
};

#endif // PRIMENUMBERPROVIDER_H
