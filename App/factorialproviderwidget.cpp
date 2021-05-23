//
//  factorialproviderwidget.cpp
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "factorialproviderwidget.h"

FactorialProviderWidget::FactorialProviderWidget(QWidget *parent): ValueProviderWidget(FactorialProviderWidget::tr("Factorial"), parent) {
    CONNECT_VALUE_PROVIDER_WIDGET_SLOTS(FactorialProviderValue)
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

void FactorialProviderWidget::onCanceled() {
    onCanceledDefault();
}

void FactorialProviderWidget::onValueReceived(FactorialProviderValue) {

}

void FactorialProviderWidget::onValueReceived(QString value) {
    onValueReceivedDefault(value);
}
