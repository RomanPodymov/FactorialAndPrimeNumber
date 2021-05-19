//
//  primenumberproviderwidget.cpp
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "primenumberproviderwidget.h"

PrimeNumberProviderWidget::PrimeNumberProviderWidget(QWidget *parent): ValueProviderWidget("Prime number", parent) {
    QObject::connect(&valueProvider, SIGNAL(progress(double)), this, SLOT(onProgress(double)));
    QObject::connect(&valueProvider, SIGNAL(paused()), this, SLOT(onPaused()));
    QObject::connect(&valueProvider, SIGNAL(resumed()), this, SLOT(onResumed()));
    QObject::connect(&valueProvider, SIGNAL(valueReceived(PrimeNumberProviderOutputValue)), this, SLOT(onValueReceived(PrimeNumberProviderOutputValue)));
    QObject::connect(&valueProvider, SIGNAL(valueReceived(QString)), this, SLOT(onValueReceived(QString)));
}

void PrimeNumberProviderWidget::onProgress(double value) {
    onProgressDefault(value);
}

void PrimeNumberProviderWidget::onPaused() {
    onPausedDefault();
}

void PrimeNumberProviderWidget::onResumed() {
    onResumedDefault();
}

void PrimeNumberProviderWidget::onValueReceived(PrimeNumberProviderOutputValue) {

}

void PrimeNumberProviderWidget::onValueReceived(QString value) {
    onValueReceivedDefault(value);
}
