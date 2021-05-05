//
//  mainwidget.cpp
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "biginteger.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent): QWidget(parent) {
    QObject::connect(&factorialProvider, SIGNAL(progress(double)), this, SLOT(onProgress(double)));
    QObject::connect(&factorialProvider, SIGNAL(valueReceived(FactorialProviderValue)), this, SLOT(onValueReceived(FactorialProviderValue)));

    rootLayout = new QHBoxLayout;
    setLayout(rootLayout);

    factorialLayout = new QVBoxLayout;
    rootLayout->addLayout(factorialLayout);

    primeNumberLayout = new QVBoxLayout;
    rootLayout->addLayout(primeNumberLayout);

    textInputFactorial = new QTextEdit;
    factorialLayout->addWidget(textInputFactorial);

    textInputPrimeNumber = new QTextEdit;
    primeNumberLayout->addWidget(textInputPrimeNumber);

    buttonFactorial = new QPushButton("Factorial");
    QObject::connect(buttonFactorial, &QPushButton::pressed, [&]() {
        progressBarFactorial->setValue(0);
        const auto textInputFactorialValue = textInputFactorial->toPlainText();
        factorialProvider.load(FactorialProviderValue(textInputFactorialValue));
    });
    factorialLayout->addWidget(buttonFactorial);

    buttonPrimeNumber = new QPushButton("Prime number");
    QObject::connect(buttonPrimeNumber, &QPushButton::pressed, [&]() {

    });
    primeNumberLayout->addWidget(buttonPrimeNumber);

    progressBarFactorial = new QProgressBar;
    progressBarFactorial->setMinimum(0);
    progressBarFactorial->setMaximum(100);
    factorialLayout->addWidget(progressBarFactorial);

    progressBarPrimeNumber = new QProgressBar;
    progressBarPrimeNumber->setMinimum(0);
    progressBarPrimeNumber->setMaximum(100);
    primeNumberLayout->addWidget(progressBarPrimeNumber);

    textOutputFactorial = new QTextEdit;
    textOutputFactorial->setReadOnly(true);
    factorialLayout->addWidget(textOutputFactorial);

    textOutputPrimeNumber = new QTextEdit;
    textOutputPrimeNumber->setReadOnly(true);
    primeNumberLayout->addWidget(textOutputPrimeNumber);
}

MainWidget::~MainWidget() {
    delete rootLayout;
    delete factorialLayout;
    delete primeNumberLayout;
    delete textInputFactorial;
    delete textInputPrimeNumber;
    delete progressBarFactorial;
    delete progressBarPrimeNumber;
    delete buttonFactorial;
    delete buttonPrimeNumber;
    delete textOutputFactorial;
    delete textOutputPrimeNumber;
}

void MainWidget::onProgress(double value) {
    progressBarFactorial->setValue(value * 100);
}

void MainWidget::onValueReceived(FactorialProviderValue value) {
    textOutputFactorial->setText(value);
}
