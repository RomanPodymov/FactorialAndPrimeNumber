//
//  mainwidget.h
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "factorialproviderwidget.h"
#include "primenumberproviderwidget.h"
#include <QWidget>
#include <QPointer>

class MainWidget final: public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QPointer<QHBoxLayout> rootLayout;
    QPointer<FactorialProviderWidget> factorialProviderWidget;
    QPointer<PrimeNumberProviderWidget> primeNumberProviderWidget;
};

#endif // MAINWIDGET_H
