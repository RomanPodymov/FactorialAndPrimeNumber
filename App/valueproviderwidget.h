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
        QObject::connect(buttonPause, &QPushButton::pressed, [&]() {
            valueProviderUIState = pausing;
            setupValueProviderUIState();
            valueProvider.pause();
        });
        rootLayout->addWidget(buttonPause);

        buttonResume = new QPushButton("Resume");
        QObject::connect(buttonResume, &QPushButton::pressed, [&]() {

        });
        rootLayout->addWidget(buttonResume);

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
        delete buttonResume;
        delete textOutput;
    }

protected:
    void setupValueProviderUIState() {
        switch (valueProviderUIState) {
            case ValueProviderUIState::iddle: {
                setOtherButtonsDisabledAndHidden(buttonRun);
                break;
            }

            case ValueProviderUIState::running: {
                setOtherButtonsDisabledAndHidden(buttonPause);
                break;
            }

            case ValueProviderUIState::pausing: {
                setOtherButtonsDisabled(std::nullopt);
                setOtherButtonsHidden(buttonPause);
                break;
            }

            case ValueProviderUIState::paused: {
                setOtherButtonsDisabledAndHidden(buttonResume);
                break;
            }
        }
    }

private:
    QVector<QPointer<QPushButton>> allButtons() {
        return {
            buttonRun,
            buttonPause,
            buttonResume
        };
    }

    void setOtherButtonsDisabled(std::optional<QPointer<QPushButton>> exceptButton) {
        const auto allButtonsValue = allButtons();
        for (const auto& button : allButtonsValue) {
            if (exceptButton && exceptButton == button) {
                button->setDisabled(false);
            } else {
                button->setDisabled(true);
            }
        }
    }

    void setOtherButtonsHidden(std::optional<QPointer<QPushButton>> exceptButton) {
        const auto allButtonsValue = allButtons();
        for (const auto& button : allButtonsValue) {
            if (exceptButton && exceptButton == button) {
                button->setHidden(false);
            } else {
                button->setHidden(true);
            }
        }
    }

    void setOtherButtonsDisabledAndHidden(std::optional<QPointer<QPushButton>> exceptButton) {
        setOtherButtonsDisabled(exceptButton);
        setOtherButtonsHidden(exceptButton);
    }

protected:
    ValueProviderType valueProvider;
    ValueProviderUIState valueProviderUIState;
    const int progressBarMaxValue = 100;

protected:
    QPointer<QVBoxLayout> rootLayout;
    QPointer<QTextEdit> textInput;
    QPointer<QProgressBar> progressBar;
    QPointer<QPushButton> buttonRun;
    QPointer<QPushButton> buttonPause;
    QPointer<QPushButton> buttonResume;
    QPointer<QTextEdit> textOutput;
};

#endif // VALUEPROVIDERWIDGET_H
