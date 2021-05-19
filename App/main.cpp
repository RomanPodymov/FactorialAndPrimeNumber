//
//  main.cpp
//  App
//
//  Created by Roman Podymov on 29/04/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#include "mainwidget.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    if (!translator.load(":/translations/strings")) {
        exit(EXIT_FAILURE);
    }
    a.installTranslator(&translator);

    MainWidget w;
    w.show();

    return a.exec();
}
