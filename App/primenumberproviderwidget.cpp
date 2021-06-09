//
//  primenumberproviderwidget.cpp
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "primenumberproviderwidget.h"

PrimeNumberProviderWidget::PrimeNumberProviderWidget(QWidget *parent): ValueProviderWidget(PrimeNumberProviderWidget::tr("Prime numbers"), parent) {

}

void PrimeNumberProviderWidget::run() {
    valueProvider = new PrimeNumberProvider();
    CONNECT_VALUE_PROVIDER_WIDGET_SLOTS(PrimeNumberProviderOutputValue)
    ValueProviderWidget::run();
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

void PrimeNumberProviderWidget::onCanceled() {
    onCanceledDefault();
}

void PrimeNumberProviderWidget::onValueReceived(PrimeNumberProviderOutputValue) {

}

void PrimeNumberProviderWidget::onValueReceived(QString value) {
    onValueReceivedDefault(value);
}
