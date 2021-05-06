//
//  mainwidget.h
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "factorialprovider.h"
#include "primenumberprovider.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QPointer>

class MainWidget final: public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void onFactorialProgress(double);
    void onFactorialValueReceived(FactorialProviderValue);
    void onPrimeNumberProgress(double);
    void onPrimeNumberValueReceived(PrimeNumberProviderOutputValue);

private:
    QPointer<QHBoxLayout> rootLayout;
    QPointer<QVBoxLayout> factorialLayout;
    QPointer<QVBoxLayout> primeNumberLayout;
    QPointer<QTextEdit> textInputFactorial;
    QPointer<QTextEdit> textInputPrimeNumber;
    QPointer<QProgressBar> progressBarFactorial;
    QPointer<QProgressBar> progressBarPrimeNumber;
    QPointer<QPushButton> buttonFactorial;
    QPointer<QPushButton> buttonPrimeNumber;
    QPointer<QTextEdit> textOutputFactorial;
    QPointer<QTextEdit> textOutputPrimeNumber;

private:
    FactorialProvider factorialProvider;
    PrimeNumberProvider primeNumberProvider;
    const int progressBarMaxValue = 100;
};

#endif // MAINWIDGET_H
