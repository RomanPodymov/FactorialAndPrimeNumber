//
//  biginteger.h
//  App
//
//  Created by Roman Podymov on 04/05/2021.
//  Copyright © 2021 FactorialAndPrimeNumber. All rights reserved.
//

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <QVector>
#include <QString>

template <typename T>
class BigInteger final {

public:
    BigInteger() { }
    BigInteger(T digit): digits({digit}) { }
    BigInteger(QString stringValue) {
        QVector<T> nextDigits;
        for (auto i = 0; i < stringValue.count(); ++i) {
            const auto subString = stringValue.mid(i, 1);
            nextDigits.append(subString.toInt());
        }
        digits = nextDigits;
    }

    BigInteger operator+(BigInteger const& rhs) const {
        BigInteger result;
        int sumOverflow = 0;
        for (auto i = digits.count() - 1, j = rhs.digits.count() - 1; i >= 0 || j >= 0; --i, --j) {
            const auto digitValue = i >= 0 ? digits[i] : 0;
            const auto rhsDigitValue = j >= 0 ? rhs.digits[j] : 0;
            const auto digitSum = digitValue + rhsDigitValue + sumOverflow;
            result.digits.insert(0, digitSum % 10);
            sumOverflow = digitSum >= 10 ? 1 : 0;
        }
        if (sumOverflow != 0) {
            result.digits.insert(0, 1);
        }
        return result;
    }

    BigInteger operator-(BigInteger const& rhs) const {
        BigInteger result;
        int diffShortfall = 0;
        for (auto i = digits.count() - 1, j = rhs.digits.count() - 1; i >= 0 || j >= 0; --i, --j) {
            const auto digitValue = i >= 0 ? digits[i] : 0;
            const auto rhsDigitValue = j >= 0 ? rhs.digits[j] : 0;
            const auto digitDiff = digitValue - rhsDigitValue - diffShortfall;
            result.digits.insert(0, digitDiff >= 0 ? digitDiff : digitDiff + 10);
            diffShortfall = digitDiff >= 0 ? 0 : 1;
        }
        return result;
    }

    BigInteger operator*(BigInteger const& rhs) const {
        BigInteger result(0);
        for (BigInteger i = 0; i != *this; i = i + 1) {
            result = result + rhs;
        }
        return result;
    }

    bool operator==(BigInteger const& rhs) const {
        if (digits.count() != rhs.digits.count()) {
            return false;
        }
        for (auto i = 0; i < digits.count(); ++i) {
            if (digits[i] != rhs.digits[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(BigInteger const& rhs) const {
        return !(*this == rhs);
    }

    QString toString() {
        QString result;
        for (const auto& digit : digits) {
            result += QString::number(digit);
        }
        return result;
    }

    qsizetype toNumber() {
        qsizetype result = 0;
        for (auto i = digits.count() - 1; i >= 0; --i) {
            result += digits[i] * pow(10, digits.count() - i - 1);
        }
        return result;
    }

    bool isEmpty() {
        return digits.isEmpty();
    }

private:
    QVector<T> digits;
};

#endif // BIGINTEGER_H
