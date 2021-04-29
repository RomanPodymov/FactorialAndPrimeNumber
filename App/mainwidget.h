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
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QPointer>

class MainWidget final: public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void onValueReceived(FactorialProviderValue);

private:
    QPointer<QHBoxLayout> rootLayout;
    QPointer<QVBoxLayout> factorialLayout;
    QPointer<QVBoxLayout> primeNumberLayout;
    QPointer<QTextEdit> textInputFactorial;
    QPointer<QTextEdit> textInputPrimeNumber;
    QPointer<QPushButton> buttonFactorial;
    QPointer<QPushButton> buttonPrimeNumber;
    QPointer<QTextEdit> textOutputFactorial;
    QPointer<QTextEdit> textOutputPrimeNumber;

private:
   FactorialProvider factorialProvider;
};

#endif // MAINWIDGET_H
