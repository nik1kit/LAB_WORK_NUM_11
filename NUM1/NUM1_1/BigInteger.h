#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class BigInteger {
private:
    string numBI; // Число
    bool negaFlag; // Наличие унарного минуса

public:
    // Конструкторы
    BigInteger();
    BigInteger(int numBI);
    BigInteger(long long numBi);
    BigInteger(string numBi);
    ~BigInteger();

    // Константы
    static const BigInteger ZERO_BI;
    static const BigInteger ONE_BI;
    static const BigInteger TEN_BI;
    static const BigInteger NONE_BI;

    // Операции
    BigInteger operator+(const BigInteger& numTmp);
    BigInteger& operator+=(const BigInteger& numTmp);
    BigInteger operator-(const BigInteger& numTmp);
    BigInteger& operator-=(const BigInteger& numTmp);
    BigInteger operator*(const BigInteger& numTmp);
    BigInteger& operator*=(const BigInteger& numTmp);
    BigInteger operator/(const BigInteger& numTmp);
    BigInteger& operator/=(const BigInteger& numTmp);
    BigInteger operator%(const BigInteger& numTmp);

    BigInteger addition(const BigInteger& numTmp) const;
    BigInteger substraction(const BigInteger& numTmp) const;
    BigInteger multiplication(const BigInteger& numTmp) const;
    BigInteger division(const BigInteger& numTmp) const;
    BigInteger modulus(const BigInteger& numTmp) const;

    // Префиксный и постфискный инкремент и декремент
    BigInteger& operator++(); // преф
    BigInteger operator++(int); // пост
    BigInteger& operator--(); // преф
    BigInteger operator--(int); // пост

    // Операторы сравнения
    bool operator==(const BigInteger& numTmp) const;
    bool operator!=(const BigInteger& numTmp) const;
    bool operator<(const BigInteger& numTmp) const;
    bool operator>(const BigInteger& numTmp) const;
    bool operator<=(const BigInteger& numTmp) const;
    bool operator>=(const BigInteger& numTmp) const;

    // 4. Вывод в поток и ввод из потока
    friend ostream& operator<<(ostream& out, const BigInteger& numTmp)
    {
        out << numTmp.toString();
        return out;
    }
    friend istream& operator>>(istream& in, const BigInteger& numTmp) { }
    void setNum(string tmpBI) { numBI = tmpBI; }

    // Метод toString
    string toString() const
    {
        if (numBI == "0") {
            return "0";
        }

        string s = "";
        if (negaFlag) {
            s = "-";
        }
        return s + numBI;
    };

    // Доп. операции
    int compare(const BigInteger& numTmp) const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigInteger& numTmp);
    BigInteger findGCD(BigInteger a, BigInteger b);

    BigInteger negate() const;
    BigInteger absolute() const;

    explicit operator bool() const
    {
        return (numBI.front() != '0');
    }
};

#endif // BIGINTEGER_H
