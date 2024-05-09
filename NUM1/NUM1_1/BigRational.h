#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H

#include "BigInteger.h" // Подключаем класс BigInteger
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class BigRational {
private:
    string numeratorBR; // Числитель числа
    string denominatorBR; // Знаменатель числа
    bool negaFlag; // Наличие унарного минуса

public:
    // Конструкторы
    BigRational();
    BigRational(int numeratorBR, int denominatorBR);
    BigRational(long long numeratorBR, long long denominatorBR);
    BigRational(string numeratorBR, string denominatorBR);
    BigRational(BigInteger numeratorBR, BigInteger denominatorBR);
    ~BigRational();

    BigInteger get_numerator() {
        return numeratorBR;
    }

    BigInteger get_denominator() {
        return denominatorBR;
    }

    bool get_negFlag() {
        return negaFlag;
    }

    // Константы
    static const BigRational ZERO_BR;
    static const BigRational ONE_BR;
    static const BigRational NONE_BR;

    // Операции
    BigRational operator+(const BigRational& numTmp);
    BigRational& operator+=(const BigRational& numTmp);
    BigRational operator-(const BigRational& numTmp);
    BigRational& operator-=(const BigRational& numTmp);
    BigRational operator*(const BigRational& numTmp);
    BigRational& operator*=(const BigRational& numTmp);
    BigRational operator/(const BigRational& numTmp);
    BigRational& operator/=(const BigRational& numTmp);

    BigRational addition(const BigRational& numTmp) const;
    BigRational substraction(const BigRational& numTmp) const;
    BigRational multiplication(const BigRational& numTmp) const;
    BigRational division(const BigRational& numTmp) const;

    // Операторы сравнения
    bool operator==(const BigRational& numTmp) const;
    bool operator!=(const BigRational& numTmp) const;
    bool operator<(const BigRational& numTmp) const;
    bool operator>(const BigRational& numTmp) const;
    bool operator<=(const BigRational& numTmp) const;
    bool operator>=(const BigRational& numTmp) const;

    // 4. Вывод в поток и ввод из потока
    friend ostream& operator<<(ostream& out, const BigRational& numTmp)
    {
        out << numTmp.toString();
        return out;
    }
    friend istream& operator>>(istream& in, const BigRational& numTmp) { }
    void setNum(string numeratorTmpBR, string denominatorTmpBR)
    {
        numeratorBR = numeratorTmpBR;
        denominatorBR = denominatorTmpBR;
    }

    // Метод toString
    string toString() const
    {
        if (numeratorBR == "0") {
            return "0/1";
        }
        string res = "";
        if (negaFlag) {
            res = "-";
        }
        res += numeratorBR + '/' + denominatorBR;
        return res;
    };

    // Доп. операции
    int compare(const BigRational& numTmp) const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigRational& numTmp);
    string asDecimal(int precision = 0);
    string toString();
    double toDouble();
    BigRational negate() const;
    BigRational absolute() const;
};

#endif // BIGRATIONAL_H
