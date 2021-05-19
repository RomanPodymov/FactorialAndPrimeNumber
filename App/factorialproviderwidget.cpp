//
//  factorialproviderwidget.cpp
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "factorialproviderwidget.h"

FactorialProviderWidget::FactorialProviderWidget(QWidget *parent): ValueProviderWidget("Factorial", parent) {
    QObject::connect(&valueProvider, SIGNAL(progress(double)), this, SLOT(onProgress(double)));
    QObject::connect(&valueProvider, SIGNAL(paused()), this, SLOT(onPaused()));
    QObject::connect(&valueProvider, SIGNAL(resumed()), this, SLOT(onResumed()));
    QObject::connect(&valueProvider, SIGNAL(valueReceived(FactorialProviderValue)), this, SLOT(onValueReceived(FactorialProviderValue)));
    QObject::connect(&valueProvider, SIGNAL(valueReceived(QString)), this, SLOT(onValueReceived(QString)));
}

void FactorialProviderWidget::onProgress(double value) {
    onProgressDefault(value);
}

void FactorialProviderWidget::onPaused() {
    onPausedDefault();
}

void FactorialProviderWidget::onResumed() {
    onResumedDefault();
}

void FactorialProviderWidget::onValueReceived(FactorialProviderValue) {

}

void FactorialProviderWidget::onValueReceived(QString value) {
    onValueReceivedDefault(value);
}
