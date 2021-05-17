//
//  factorialproviderwidget.h
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef FACTORIALPROVIDERWIDGET_H
#define FACTORIALPROVIDERWIDGET_H

#include "factorialprovider.h"
#include "valueproviderwidget.h"

class FactorialProviderWidget final: public ValueProviderWidget<FactorialProvider> {
    Q_OBJECT

public:
    FactorialProviderWidget(QWidget *parent = nullptr);

private slots:
    void onProgress(double);
    void onPaused();
    void onValueReceived(FactorialProviderValue);
    void onValueReceived(QString);
};

#endif // FACTORIALPROVIDERWIDGET_H
