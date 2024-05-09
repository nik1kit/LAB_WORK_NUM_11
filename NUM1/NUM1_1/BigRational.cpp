#include "BigRational.h"
#include "BigInteger.h"

istream& operator>>(istream& in, BigRational& tmp)
{
    string num;
    in >> num;

    string resNum = "", resDet = "1";
    bool flag = true;
    for (char& c : num) {
        if (c == '.') {
            flag = false;
        }
        else {
            if (flag) {
                resNum += c;
            }
            else {
                resNum += c;
                resDet += '0';
            }
        }
    }

    tmp.setNum(resNum, resDet);
    return in;
}
// Константы "0", "1", "10"
const BigRational BigRational::ZERO_BR = BigRational("0", "1");
const BigRational BigRational::ONE_BR = BigRational("1", "1");
const BigRational BigRational::NONE_BR = BigRational("NONE_BR", "NONE_BR");

BigRational::BigRational()
    : numeratorBR("0")
    , denominatorBR("1")
    , negaFlag(false)
{
}
// Конструктор с double-переменной
BigRational::BigRational(int num, int den)
    : negaFlag((num < 0 && den > 0) || (num > 0 && den < 0))
{
    string strNum = to_string(num),
        strDen = to_string(den);

    if (den < 0 && num > 0) {
        strDen.erase(0, 1);
        strNum = '-' + strNum;
    }
    else if (den < 0 && num < 0) {
        strDen.erase(0, 1);
        strNum.erase(0, 1);
    }
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    if (strDen == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = strNum, denominatorBR = strDen;
    }
}
// Конструктор с long double-переменной
BigRational::BigRational(long long num, long long den)
    : negaFlag((num < 0 && den > 0) || (num > 0 && den < 0))
{
    string strNum = to_string(num),
        strDen = to_string(den);

    if (den < 0 && num > 0) {
        strDen.erase(0, 1);
        strNum = '-' + strNum;
    }
    else if (den < 0 && num < 0) {
        strDen.erase(0, 1);
        strNum.erase(0, 1);
    }

    if (negaFlag) {
        strNum.erase(0, 1);
    }
    if (strDen == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = strNum, denominatorBR = strDen;
    }
}
// Конструктор с BigInteger-переменной
BigRational::BigRational(BigInteger num, BigInteger den)
    : negaFlag((num < 0 && den > 0) || (num > 0 && den < 0))
{
    string strNum = num.toString(),
        strDen = den.toString();

    if (den < 0 && num > 0) {
        strDen.erase(0, 1);
        strNum = '-' + strNum;
    }
    else if (den < 0 && num < 0) {
        strDen.erase(0, 1);
        strNum.erase(0, 1);
    }
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    if (strDen == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = strNum, denominatorBR = strDen;
    }
}
// Конструктор с string-переменной
BigRational::BigRational(string num, string den)
    : negaFlag((num[0] == '-' && den[0] != '-') || (num[0] != '-' && den[0] == '-'))
{
    if (den[0] == '-' && num[0] != '-') {
        den.erase(0, 1);
        num = '-' + num;
    }
    else if (den[0] == '-' && num[0] == '-') {
        den.erase(0, 1);
        den.erase(0, 1);
    }
    if (negaFlag) {
        num.erase(0, 1);
    }
    while (num[0] == '0' && num.length() != 1) {
        num.erase(0, 1);
    }

    if (den == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = num, denominatorBR = den;
    }
}
// Деструктор
BigRational::~BigRational() { }
int BigRational::compare(const BigRational& numTmp) const
{
    int result;

    BigRational n1(this->numeratorBR, this->denominatorBR), n2 = numTmp;
    n1.negaFlag = this->negaFlag;

    if (n1.negaFlag && !n2.negaFlag) {
        // Случай -А, +Б
        result = -1;
    }
    else if (!n1.negaFlag && n2.negaFlag) {
        // Случай +А, -Б
        result = 1;
    }
    else {
        // Случай +A, +B || -A, -B
        BigInteger num1 = this->numeratorBR,
            den1 = this->denominatorBR,
            num2 = numTmp.numeratorBR,
            den2 = numTmp.denominatorBR, resNum1, resNum2;

        resNum1 = num1 * den2, resNum2 = num2 * den1;
        string resNumStr1 = resNum1.toString(),
            resNumStr2 = resNum2.toString();

        if (resNumStr1.length() < resNumStr2.length()) {
            result = -1;
        }
        else if (resNumStr1.length() > resNumStr2.length()) {
            result = 1;
        }
        else {
            bool flagPo = !this->negaFlag;
            if (resNumStr1 < resNumStr2) {
                result = (flagPo ? -1 : 1);
            }
            else if (resNumStr1 > resNumStr2) {
                result = (flagPo ? 1 : -1);
            }
            else {
                result = 0;
            }
        }
    }
    return result;
}

BigInteger findGCD(BigInteger a, BigInteger b)
{
    if (b == BigInteger("0")) {
        return a;
    }
    else if (a == BigInteger("0")) {
        return b;
    }
    return findGCD(b, a % b);
}

// Сложение
BigRational BigRational::addition(const BigRational& numTmp) const
{
    BigRational result;
    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        if (numTmp != ONE_BR && (*this) != ONE_BR) {
            return NONE_BR;
        }
    }

    // Случай (-A) + B
    if (this->negaFlag && !numTmp.negaFlag) {
        result = numTmp.substraction(negate());
    }
    // Случай A + (-B)
    else if (!this->negaFlag && numTmp.negaFlag) {
        result = substraction(numTmp.negate());
    }
    // Случай A + B || -(A) + (-B)
    else {
        BigInteger num1 = this->numeratorBR,
            den1 = this->denominatorBR,
            num2 = numTmp.numeratorBR,
            den2 = numTmp.denominatorBR, resDen, resNum;

        if (den1 != den2) {
            BigInteger multNum1 = num1 * den2,
                multNum2 = num2 * den1;

            resDen = den1 * den2;
            resNum = multNum1 + multNum2;
        }
        else {
            resDen = den1;
            resNum = num1 + num2;
        }
        BigInteger gcd = findGCD(resNum, resDen);
        BigRational res(resNum / gcd, resDen / gcd);
        result = res;
        result = (this->negaFlag ? result.negate() : result);
    }

    return result;
}
BigRational BigRational::substraction(const BigRational& numTmp) const
{
    BigRational result;

    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        if (numTmp != ONE_BR && (*this) != ONE_BR) {
            return NONE_BR;
        }
    }

    // Случай(-A) - (+B)
    if (this->negaFlag && !numTmp.negaFlag) {
        result = addition(numTmp.negate());
    }
    // Случай (+A) - (-B)
    else if (!this->negaFlag && numTmp.negaFlag) {
        result = addition(numTmp.negate());
    }
    // Случай (+A) - (+B) || (-A) - (-B)
    else {
        BigInteger num1 = this->numeratorBR,
            den1 = this->denominatorBR,
            num2 = numTmp.numeratorBR,
            den2 = numTmp.denominatorBR, resDen, resNum;

        if (den1 != den2) {
            BigInteger multNum1 = num1 * den2,
                multNum2 = num2 * den1;

            resDen = den1 * den2;
            resNum = multNum1 - multNum2;
        }
        else {
            resDen = den1;
            resNum = num1 - num2;
        }
        BigInteger gcd = findGCD(resNum, resDen);
        BigRational res(resNum / gcd, resDen / gcd);
        result = res;
        result = (this->negaFlag ? result.negate() : result);
    }
    return result;
}
// Умножение
BigRational BigRational::multiplication(const BigRational& numTmp) const
{
    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        if (numTmp != ONE_BR && (*this) != ONE_BR) {
            return NONE_BR;
        }
    }

    BigInteger num1 = this->numeratorBR,
        den1 = this->denominatorBR,
        num2 = numTmp.numeratorBR,
        den2 = numTmp.denominatorBR, resDen, resNum;

    resNum = num1 * num2;
    resDen = den1 * den2;

    BigRational result(resNum, resDen);

    if ((this->isNegative() && numTmp.isPositive()) || (numTmp.isNegative() && this->isPositive())) {
        result.negaFlag = true;
    }
    else {
        result.negaFlag = false;
    }

    return result;
}
// Деление
BigRational BigRational::division(const BigRational& numTmp) const
{
    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        if (numTmp != ONE_BR && (*this) != ONE_BR) {
            return NONE_BR;
        }
    }

    BigInteger num1 = this->numeratorBR,
        den1 = this->denominatorBR,
        num2 = numTmp.numeratorBR,
        den2 = numTmp.denominatorBR, resDen, resNum;

    resNum = num1 * den2;
    resDen = den1 * num2;

    BigRational result(resNum, resDen);

    if ((this->isNegative() && numTmp.isPositive()) || (numTmp.isNegative() && this->isPositive())) {
        result.negaFlag = true;
    }
    else {
        result.negaFlag = false;
    }

    return result;
}
BigRational BigRational::negate() const
{
    string num = this->numeratorBR;
    if (!this->negaFlag) {
        num.insert(0, 1, '-');
    }
    BigRational res(num, this->denominatorBR);

    return res;
}

BigRational BigRational::absolute() const
{
    return (isPositive() ? (*this) : negate());
}

bool BigRational::isPositive() const
{
    return !this->negaFlag;
}

bool BigRational::isNegative() const
{
    return this->negaFlag;
}

void BigRational::swap(BigRational& numTmp)
{
    BigRational tmp = (*this);
    (*this) = numTmp;
    numTmp = tmp;
}
// Сложение
BigRational BigRational::operator+(const BigRational& numTmp)
{
    return this->addition(numTmp);
}
BigRational& BigRational::operator+=(const BigRational& numTmp)
{
    (*this) = addition(numTmp);
    return (*this);
}
// Разность
BigRational BigRational::operator-(const BigRational& numTmp)
{
    return this->substraction(numTmp);
}
BigRational& BigRational::operator-=(const BigRational& numTmp)
{
    (*this) = substraction(numTmp);
    return (*this);
}
// Умножение
BigRational BigRational::operator*(const BigRational& numTmp)
{
    return this->multiplication(numTmp);
}
BigRational& BigRational::operator*=(const BigRational& numTmp)
{
    (*this) = multiplication(numTmp);
    return (*this);
}
// Деление
BigRational BigRational::operator/(const BigRational& numTmp)
{
    return this->division(numTmp);
}
BigRational& BigRational::operator/=(const BigRational& numTmp)
{
    (*this) = division(numTmp);
    return (*this);
}
// Операторы сравнения
bool BigRational::operator==(const BigRational& numTmp) const
{
    bool equal = (compare(numTmp) == 0);
    return equal;
}
bool BigRational::operator!=(const BigRational& numTmp) const
{
    bool different = (compare(numTmp) != 0);
    return different;
}
bool BigRational::operator<(const BigRational& numTmp) const
{
    bool less = (compare(numTmp) == -1);
    return less;
}
bool BigRational::operator>(const BigRational& numTmp) const
{
    bool more = (compare(numTmp) == 1);
    return more;
}
bool BigRational::operator<=(const BigRational& numTmp) const
{
    int cmp = compare(numTmp);
    return (cmp == -1) || (cmp == 0);
}
bool BigRational::operator>=(const BigRational& numTmp) const
{
    int cmp = compare(numTmp);
    return (cmp == 0) || (cmp == 1);
}
string BigRational::asDecimal(int precision)
{
    string resultMainPart = "", resFracPart = "";
    BigInteger num(this->numeratorBR), den(this->denominatorBR);
    BigInteger absNum = num.absolute();
    vector<BigInteger> list;

    if (num < BigInteger(0)) {
        resultMainPart = "-";
    }
    resultMainPart += (absNum / den).toString();

    BigInteger fractionalPart = absNum % den;
    if (fractionalPart == BigInteger(0)) {
        return resultMainPart;
    }

    if (fractionalPart != BigInteger(0)) {
        resultMainPart += ".";
        list.push_back(fractionalPart);
    }

    bool flag = false;
    for (int i = 0; i < precision; i++) {
        fractionalPart *= 10;
        resFracPart += (fractionalPart / den).toString();
        fractionalPart = fractionalPart % den;

        if (fractionalPart == 0) {
            break;
        }

        list.push_back(resFracPart);
    }
    return resultMainPart + resFracPart;
}
string BigRational::toString()
{
    string res = this->asDecimal(5);
    return res;
}
double BigRational::toDouble()
{
    string str = this->asDecimal(5);

    double result = 0.0;
    double fraction = 1.0;
    bool isNegative = false;

    size_t index = 0;
    if (str[0] == '-') {
        isNegative = true;
        index = 1;
    }
    while (isdigit(str[index])) {
        result = result * 10 + (str[index] - '0');
        index++;
    }
    if (str[index] == '.') {
        index++;
        while (isdigit(str[index])) {
            fraction /= 10;
            result = result + (str[index] - '0') * fraction;
            index++;
        }
    }
    if (isNegative) {
        result *= -1;
    }

    return result;
}