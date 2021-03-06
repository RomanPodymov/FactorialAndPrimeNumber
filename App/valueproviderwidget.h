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
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QPointer>

enum ValueProviderUIState { iddle, running, pausing, paused, resuming, cancelling };

#define CONNECT_VALUE_PROVIDER_WIDGET_SLOTS(VALUE_RECEIVED_TYPE) \
    QObject::connect(valueProvider, SIGNAL(progress(double)), this, SLOT(onProgress(double))); \
    QObject::connect(valueProvider, SIGNAL(paused()), this, SLOT(onPaused())); \
    QObject::connect(valueProvider, SIGNAL(resumed()), this, SLOT(onResumed())); \
    QObject::connect(valueProvider, SIGNAL(canceled()), this, SLOT(onCanceled())); \
    QObject::connect(valueProvider, SIGNAL(valueReceived(VALUE_RECEIVED_TYPE)), this, SLOT(onValueReceived(VALUE_RECEIVED_TYPE))); \
    QObject::connect(valueProvider, SIGNAL(valueReceived(QString)), this, SLOT(onValueReceived(QString)));

template <typename ValueProviderType>
class ValueProviderWidget: public QWidget {

public:
    ValueProviderWidget(QString title, QWidget *parent = nullptr): QWidget(parent),
        valueProviderUIState(iddle) {
        rootLayout = new QGridLayout;
        setLayout(rootLayout);

        groupBoxLayout = new QVBoxLayout;

        groupBox = new QGroupBox(title);
        rootLayout->addWidget(groupBox);
        groupBox->setLayout(groupBoxLayout);

        textInput = new QTextEdit;
        groupBoxLayout->addWidget(textInput);

        buttonsLayout = new QHBoxLayout;
        groupBoxLayout->addLayout(buttonsLayout);

        buttonRun = new QPushButton(QWidget::tr("Run"));
        QObject::connect(buttonRun, &QPushButton::pressed, [&]() {
            run();
        });
        buttonsLayout->addWidget(buttonRun);

        buttonCancel = new QPushButton(QWidget::tr("Cancel"));
        QObject::connect(buttonCancel, &QPushButton::pressed, [&]() {
            setupValueProviderUIState(cancelling);
            valueProvider->cancel();
        });
        buttonsLayout->addWidget(buttonCancel);

        buttonPause = new QPushButton(QWidget::tr("Pause"));
        QObject::connect(buttonPause, &QPushButton::pressed, [&]() {
            setupValueProviderUIState(pausing);
            valueProvider->pause();
        });
        buttonsLayout->addWidget(buttonPause);

        buttonResume = new QPushButton(QWidget::tr("Resume"));
        QObject::connect(buttonResume, &QPushButton::pressed, [&]() {
            setupValueProviderUIState(resuming);
            valueProvider->resume();
        });
        buttonsLayout->addWidget(buttonResume);

        progressBar = new QProgressBar;
        progressBar->setMinimum(0);
        progressBar->setMaximum(progressBarMaxValue);
        groupBoxLayout->addWidget(progressBar);

        textOutput = new QTextEdit;
        textOutput->setReadOnly(true);
        groupBoxLayout->addWidget(textOutput);

        setupValueProviderUIState(std::nullopt);
    }

    ~ValueProviderWidget() {
        delete valueProvider;
        delete rootLayout;
        delete groupBoxLayout;
        delete groupBox;
        delete textInput;
        delete progressBar;
        delete buttonsLayout;
        delete buttonRun;
        delete buttonCancel;
        delete buttonPause;
        delete buttonResume;
        delete textOutput;
    }

protected:
    virtual void run() {
        setupValueProviderUIState(running);
        textInput->setReadOnly(true);
        textOutput->setText("");
        progressBar->setValue(0);
        const auto textInputValue = textInput->toPlainText();
        valueProvider->load(textInputValue);
    }

    void setupValueProviderUIState(std::optional<ValueProviderUIState> nextValueProviderUIState) {
        const auto previousValueProviderUIState = nextValueProviderUIState;
        if (nextValueProviderUIState) {
            valueProviderUIState = nextValueProviderUIState.value();
        }
        switch (valueProviderUIState) {
            case ValueProviderUIState::iddle: {
                setOtherButtonsDisabledAndHidden({buttonRun}, false);
                break;
            }

            case ValueProviderUIState::running: {
                setOtherButtonsDisabledAndHiddenWhenRunning(false);
                break;
            }

            case ValueProviderUIState::pausing: {
                setOtherButtonsDisabledAndHiddenWhenRunning(true);
                break;
            }

            case ValueProviderUIState::paused: {
                setOtherButtonsDisabledAndHiddenWhenPaused(false);
                break;
            }

            case ValueProviderUIState::resuming: {
                setOtherButtonsDisabledAndHiddenWhenPaused(true);
                break;
            }

            case ValueProviderUIState::cancelling: {
                if (previousValueProviderUIState == running || previousValueProviderUIState == pausing) {
                    setOtherButtonsDisabledAndHiddenWhenRunning(true);
                } else if (previousValueProviderUIState == paused || previousValueProviderUIState == resuming) {
                    setOtherButtonsDisabledAndHiddenWhenPaused(true);
                } else {
                    setOtherButtonsDisabled({});
                }
                break;
            }
        }
    }

    void onProgressDefault(double value) {
        if (valueProviderUIState == running) {
            progressBar->setValue(value * progressBarMaxValue);
        }
    }

    void onPausedDefault() {
        setupValueProviderUIState(paused);
    }

    void onResumedDefault() {
        setupValueProviderUIState(running);
    }

    void onCanceledDefault() {
        valueProvider->watcher.disconnect();
        valueProvider->disconnect();
        disconnect();
        delete valueProvider;
        progressBar->setValue(0);
        textInput->setReadOnly(false);
        setupValueProviderUIState(iddle);
    }

    void onValueReceivedDefault(QString value) {
        textInput->setReadOnly(false);
        textOutput->setText(value);
        setupValueProviderUIState(iddle);
    }

private:
    QVector<QPointer<QPushButton>> allButtons() const {
        return {
            buttonRun,
            buttonCancel,
            buttonPause,
            buttonResume
        };
    }

    void setOtherButtonsDisabled(QVector<QPointer<QPushButton>> exceptButtons) {
        const auto allButtonsValue = allButtons();
        for (const auto& button : allButtonsValue) {
            if (exceptButtons.contains(button)) {
                button->setDisabled(false);
            } else {
                button->setDisabled(true);
            }
        }
    }

    void setOtherButtonsHidden(QVector<QPointer<QPushButton>> exceptButtons) {
        const auto allButtonsValue = allButtons();
        for (const auto& button : allButtonsValue) {
            if (exceptButtons.contains(button)) {
                button->setHidden(false);
            } else {
                button->setHidden(true);
            }
        }
    }

    void setOtherButtonsDisabledAndHidden(QVector<QPointer<QPushButton>> exceptButtons, bool disableAll) {
        if (disableAll) {
            setOtherButtonsDisabled({});
        } else {
            setOtherButtonsDisabled(exceptButtons);
        }
        setOtherButtonsHidden(exceptButtons);
    }

    void setOtherButtonsDisabledAndHiddenWhenRunning(bool disableAll) {
        setOtherButtonsDisabledAndHidden({buttonPause, buttonCancel}, disableAll);
    }

    void setOtherButtonsDisabledAndHiddenWhenPaused(bool disableAll) {
        setOtherButtonsDisabledAndHidden({buttonResume, buttonCancel}, disableAll);
    }

protected:
    QPointer<ValueProviderType> valueProvider;
    ValueProviderUIState valueProviderUIState;
    const int progressBarMaxValue = 100;

protected:
    QPointer<QGridLayout> rootLayout;
    QPointer<QVBoxLayout> groupBoxLayout;
    QPointer<QGroupBox> groupBox;
    QPointer<QTextEdit> textInput;
    QPointer<QProgressBar> progressBar;
    QPointer<QHBoxLayout> buttonsLayout;
    QPointer<QPushButton> buttonRun;
    QPointer<QPushButton> buttonCancel;
    QPointer<QPushButton> buttonPause;
    QPointer<QPushButton> buttonResume;
    QPointer<QTextEdit> textOutput;
};

#endif // VALUEPROVIDERWIDGET_H
