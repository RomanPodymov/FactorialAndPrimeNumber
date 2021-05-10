//
//  valueproviderwidget.h
//  App
//
//  Created by Roman Podymov on 10/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef VALUEPROVIDERWIDGET_H
#define VALUEPROVIDERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QPointer>

enum ValueProviderUIState { iddle, running, pausing, paused };

template <typename ValueProviderType>
class ValueProviderWidget: public QWidget {

public:
    ValueProviderWidget(QWidget *parent = nullptr): QWidget(parent),
        valueProviderUIState(iddle) {
        rootLayout = new QVBoxLayout;
        setLayout(rootLayout);

        textInput = new QTextEdit;
        rootLayout->addWidget(textInput);

        buttonRun = new QPushButton("Get value");
        QObject::connect(buttonRun, &QPushButton::pressed, [&]() {
            valueProviderUIState = running;
            setupValueProviderUIState();
            textOutput->setText("");
            progressBar->setValue(0);
            const auto textInputValue = textInput->toPlainText();
            valueProvider.load(textInputValue);
        });
        rootLayout->addWidget(buttonRun);

        buttonPause = new QPushButton("Pause");
        rootLayout->addWidget(buttonPause);

        progressBar = new QProgressBar;
        progressBar->setMinimum(0);
        progressBar->setMaximum(progressBarMaxValue);
        rootLayout->addWidget(progressBar);

        textOutput = new QTextEdit;
        textOutput->setReadOnly(true);
        rootLayout->addWidget(textOutput);

        setupValueProviderUIState();
    }

    ~ValueProviderWidget() {
        delete rootLayout;
        delete textInput;
        delete progressBar;
        delete buttonRun;
        delete buttonPause;
        delete textOutput;
    }

protected:
    void setupValueProviderUIState() {
        switch (valueProviderUIState) {
            case ValueProviderUIState::iddle: {
                buttonRun->setHidden(false);
                buttonPause->setHidden(true);
                break;
            }

            case ValueProviderUIState::running: {
                buttonRun->setHidden(true);
                buttonPause->setHidden(false);
                break;
            }

            case ValueProviderUIState::pausing: {
                break;
            }

            case ValueProviderUIState::paused: {
                break;
            }
        }
    }

protected:
    ValueProviderType valueProvider;
    const int progressBarMaxValue = 100;

protected:
    QPointer<QVBoxLayout> rootLayout;
    QPointer<QTextEdit> textInput;
    QPointer<QProgressBar> progressBar;
    QPointer<QPushButton> buttonRun;
    QPointer<QPushButton> buttonPause;
    QPointer<QTextEdit> textOutput;

private:
    ValueProviderUIState valueProviderUIState;
};

#endif // VALUEPROVIDERWIDGET_H
