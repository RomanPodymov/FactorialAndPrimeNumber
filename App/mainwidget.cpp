//
//  mainwidget.cpp
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "mainwidget.h"
#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent): QWidget(parent) {
    rootLayout = new QHBoxLayout;
    setLayout(rootLayout);

    factorialProviderWidget = new FactorialProviderWidget;
    rootLayout->addWidget(factorialProviderWidget);

    primeNumberProviderWidget = new PrimeNumberProviderWidget;
    rootLayout->addWidget(primeNumberProviderWidget);
}

MainWidget::~MainWidget() {
    delete rootLayout;
    delete factorialProviderWidget;
    delete primeNumberProviderWidget;
}
