//
//  primenumberproviderwidget.cpp
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "primenumberproviderwidget.h"

PrimeNumberProviderWidget::PrimeNumberProviderWidget(QWidget *parent): ValueProviderWidget(parent) {
    QObject::connect(&valueProvider, SIGNAL(progress(double)), this, SLOT(onProgress(double)));
    QObject::connect(&valueProvider, SIGNAL(valueReceived(PrimeNumberProviderOutputValue)), this, SLOT(onValueReceived(PrimeNumberProviderOutputValue)));
    QObject::connect(&valueProvider, SIGNAL(valueReceived(QString)), this, SLOT(onValueReceived(QString)));
}

void PrimeNumberProviderWidget::onProgress(double value) {
    progressBar->setValue(value * progressBarMaxValue);
}

void PrimeNumberProviderWidget::onValueReceived(PrimeNumberProviderOutputValue) {

}

void PrimeNumberProviderWidget::onValueReceived(QString value) {
    textOutput->setText(value);
}
