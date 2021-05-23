//
//  primenumberproviderwidget.h
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef PRIMENUMBERPROVIDERWIDGET_H
#define PRIMENUMBERPROVIDERWIDGET_H

#include "primenumberprovider.h"
#include "valueproviderwidget.h"

class PrimeNumberProviderWidget final: public ValueProviderWidget<PrimeNumberProvider> {
    Q_OBJECT

public:
    PrimeNumberProviderWidget(QWidget *parent = nullptr);

private slots:
    void onProgress(double);
    void onPaused();
    void onResumed();
    void onCanceled();
    void onValueReceived(PrimeNumberProviderOutputValue);
    void onValueReceived(QString);
};

#endif // PRIMENUMBERPROVIDERWIDGET_H
