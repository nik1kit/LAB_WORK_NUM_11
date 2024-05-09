#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class BigInteger {
private:
    string numBI; // �����
    bool negaFlag; // ������� �������� ������

public:
    // ������������
    BigInteger();
    BigInteger(int numBI);
    BigInteger(long long numBi);
    BigInteger(string numBi);
    ~BigInteger();

    // ���������
    static const BigInteger ZERO_BI;
    static const BigInteger ONE_BI;
    static const BigInteger TEN_BI;
    static const BigInteger NONE_BI;

    // ��������
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

    // ���������� � ����������� ��������� � ���������
    BigInteger& operator++(); // ����
    BigInteger operator++(int); // ����
    BigInteger& operator--(); // ����
    BigInteger operator--(int); // ����

    // ��������� ���������
    bool operator==(const BigInteger& numTmp) const;
    bool operator!=(const BigInteger& numTmp) const;
    bool operator<(const BigInteger& numTmp) const;
    bool operator>(const BigInteger& numTmp) const;
    bool operator<=(const BigInteger& numTmp) const;
    bool operator>=(const BigInteger& numTmp) const;

    // 4. ����� � ����� � ���� �� ������
    friend ostream& operator<<(ostream& out, const BigInteger& numTmp)
    {
        out << numTmp.toString();
        return out;
    }
    friend istream& operator>>(istream& in, const BigInteger& numTmp) { }
    void setNum(string tmpBI) { numBI = tmpBI; }

    // ����� toString
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

    // ���. ��������
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
