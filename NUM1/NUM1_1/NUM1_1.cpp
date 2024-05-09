#include "BigInteger.h"
#include "BigRational.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
BigInteger findGCD(BigInteger a, BigInteger b);
template <int N>
class Finite {
private:
    int value;

public:
    Finite(int val)
        : value(val % N)
    {
    }

    int getValue() const { return value; }

    Finite<N> operator+(const Finite<N>& other) const
    {
        return Finite<N>((value + other.value) % N);
    }

    Finite<N> operator-(const Finite<N>& other) const
    {
        return Finite<N>((value - other.value + N) % N);
    }

    Finite<N> operator*(const Finite<N>& other) const
    {
        return Finite<N>((value * other.value) % N);
    }

    bool operator==(const Finite<N>& other) const
    {
        return value == other.value;
    }

    bool operator!=(const Finite<N>& other) const
    {
        return value != other.value;
    }
};

template <unsigned M, unsigned N, typename Field = BigRational>

class Matrix {
private:
public:
    vector<vector<Field>> data;
    // M - кол-во строк
    // N - кол-во столбцов

    // Конструктор единичной матрицы
    Matrix()
    {
        data.resize(M, vector<Field>(N, Field()));
        if (M == N) {
            for (unsigned i = 0; i < N; i++) {
                data[i][i] = Field(1, 1);
            }
        }
    }

    // Конструктор матрицы
    Matrix(const vector<vector<Field>>& vec)
        : data(vec)
    {
    }

    // Сложение
    template <unsigned M2, unsigned N2, typename Field2 = Field>
    Matrix<M, N, Field> addition(const Matrix<M2, N2, Field2>& mat)
    {
        for (unsigned i = 0; i < M; i++) {
            for (unsigned j = 0; j < N; j++) {
                data[i][j] += mat.data[i][j];
            }
        }
        return (*this);
    }

    // Вычитание
    template <unsigned M2, unsigned N2, typename Field2 = Field>
    Matrix<M, N, Field> substraction(const Matrix<M2, N2, Field2>& mat)
    {
        for (unsigned i = 0; i < M; i++) {
            for (unsigned j = 0; j < N; j++) {
                data[i][j] -= mat.data[i][j];
            }
        }
        return (*this);
    }

    template <unsigned M2, unsigned N2, typename Field2 = Field>
    bool operator==(const Matrix<M2, N2, Field2>& other) const
    {
        if (M != M2 || N != N2) {
            return false;
        }

        for (unsigned i = 0; i < M; ++i) {
            for (unsigned j = 0; j < N; ++j) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    // Оператор +=
    template <unsigned M2, unsigned N2, typename Field2 = Field>
    Matrix<M, N, Field> operator+=(const Matrix<M2, N2, Field2>& mat)
    {
        if ((M != M2) || (N != N2)) {
            for (unsigned i = 0; i < M; i++) {
                for (unsigned j = 0; j < N; j++) {
                    data[i][j] = Field(1, 0);
                }
            }
            return (*this);
        }
        Matrix<M, N, Field> res = this->addition(mat);
        return res;
    }

    // Оператор -=
    template <unsigned M2, unsigned N2, typename Field2 = Field>
    Matrix<M, N, Field> operator-=(const Matrix<M2, N2, Field2>& mat)
    {
        if ((M != M2) || (N != N2)) {
            for (unsigned i = 0; i < M; i++) {
                for (unsigned j = 0; j < N; j++) {
                    data[i][j] = Field(1, 0);
                }
            }
            return (*this);
        }
        Matrix<M, N, Field> res = this->substraction(mat);
        return res;
    }

    // Оператор *= BigRational
    Matrix<M, N, Field> operator*=(Field& scalar)
    {
        for (unsigned i = 0; i < M; ++i) {
            for (unsigned j = 0; j < N; ++j) {
                data[i][j] *= scalar;
            }
        }
        return (*this);
    }

    // Умножение на матрицу и оператор *=
    template <unsigned M2, unsigned N2, typename Field2 = Field>
    Matrix<M, N, Field> operator*=(const Matrix<M2, N2, Field2>& mat)
    {
        if (N != M2) {
            for (unsigned i = 0; i < M; i++) {
                for (unsigned j = 0; j < N; j++) {
                    data[i][j] = BigRational(1, 0);
                }
            }
            return (*this);
        }

        vector<vector<Field>> listR(M, vector<Field>(N2, Field(0, 1)));
        for (unsigned i = 0; i < N; i++) {
            for (unsigned j = 0; j < M2; j++) {
                for (unsigned k = 0; k < M; k++) {
                    listR[i][j] += this->data[i][k] * mat.data[k][j];
                }
            }
        }

        Matrix<M, N2, Field> res(listR);
        (*this) = res;
        return (*this);
    }

    // Поиск определителя
    Field det()
    {
        if (N != M) {
            throw std::logic_error("Вычисление определитея НЕ КВАДРАТНОЙ матрицы");
            // return Field(1, 0);
        }

        if (M == 1) {
            return (*this).data[0][0];
        } else if (M == 2) {
            return (*this).data[0][0] * (*this).data[1][1] - (*this).data[1][0] * (*this).data[0][1];
        } else {
            Field determinant(1, 1);
            for (unsigned i = 0; i < N; i++) {
                int tmp = i;
                for (unsigned j = i + 1; j < N; j++) {
                    if ((*this).data[j][i].absolute() > (*this).data[tmp][i].absolute()) {
                        tmp = j;
                    }
                }

                if (tmp != i) {
                    swap((*this).data[i], (*this).data[tmp]);
                    determinant *= Field(-1, 1);
                }

                if ((*this).data[i][i] == Field(0, 1)) {
                    return Field(0, 1);
                }

                determinant *= (*this).data[i][i];
                for (unsigned j = i + 1; j < N; j++) {
                    Field factor = (*this).data[j][i] / (*this).data[i][i];
                    for (int k = i + 1; k < N; k++) {
                        (*this).data[j][k] -= factor * (*this).data[i][k];
                    }
                }
            }

            return determinant;
        }
    }

    // Транспонирование матрицы
    void transpose()
    {
        vector<vector<Field>> list(N, vector<Field>(M, Field(0, 1)));
        Matrix<N, M, Field> res(list);

        for (unsigned i = 0; i < M; i++) {
            for (unsigned j = 0; j < N; j++) {
                res.data[j][i] = (*this).data[i][j];
            }
        }

        res.print();
    }

    // След матрицы
    //  это сумма элементов матрицы, стоящих на главной диагонали.
    Field trace()
    {
        if (N != M) {
            return Field(1, 0);
        }

        Field sum(0, 1);
        for (unsigned i = 0; i < N; i++) {
            sum += (*this).data[i][i];
        }
        return sum;
    }

    void swapB(int row1, int row2, int col)
    {
        for (int i = 0; i < col; i++) {
            Field temp = (*this).data[row1][i];
            (*this).data[row1][i] = (*this).data[row2][i];
            (*this).data[row2][i] = temp;
        }
    }

    // Ранг матрицы
    int rank()
    {
        Matrix<M, N, Field> mat = (*this);
        int rank = N;

        for (int row = 0; row < rank; row++) {
            if ((*this).data[row][row] != BigRational(0, 1)) {
                for (int col = 0; col < M; col++) {
                    if (col != row) {
                        Field mult = mat.data[col][row] / mat.data[row][row];
                        for (int i = 0; i < rank; i++)
                            mat.data[col][i] -= mult * mat.data[row][i];
                    }
                }
            } else {
                bool reduce = true;
                for (int i = row + 1; i < M; i++) {
                    if (mat.data[i][row] != Field(0, 1)) {
                        swapB(row, i, rank);
                        reduce = false;
                        break;
                    }
                }
                if (reduce) {
                    rank--;
                    for (int i = 0; i < M; i++)
                        mat.data[i][row] = mat.data[i][rank];
                }
                row--;
            }
        }
        return rank;
    }

    // Обращение матрицы
    Matrix<M, N, Field> inverted()
    {
        Field deter = (*this).det();
        if ((N != M) || (deter == Field(0, 1))) {
            for (unsigned i = 0; i < M; i++) {
                for (unsigned j = 0; j < N; j++) {
                    data[i][j] = Field(1, 0);
                }
            }
            return (*this);
        }

        vector<vector<Field>> list(M, vector<Field>(N * 2, Field(0, 1)));
        for (unsigned i = 0; i < M; i++) {
            for (unsigned j = 0; j < N; j++) {
                list[i][j] = (*this).data[i][j];
            }
            for (unsigned j = N; j < N * 2; j++) {
                if (j == (i + N)) {
                    list[i][j] = Field(1, 1);
                }
            }
        }

        for (unsigned i = N - 1; i > 0; i--) {
            if (list[i - 1][0] < list[i][0]) {
                vector<Field> tmp = list[i];
                list[i] = list[i - 1];
                list[i - 1] = tmp;
            }
        }

        for (unsigned i = 0; i < N; i++) {
            for (unsigned j = 0; j < N; j++) {
                if (j != i) {
                    Field temp = list[j][i] / list[i][i];
                    for (unsigned k = 0; k < N * 2; k++) {
                        list[j][k] -= list[i][k] * temp;
                    }
                }
            }
        }
        for (unsigned i = 0; i < N; i++) {
            Field t = list[i][i];
            for (int j = 0; j < 2 * N; j++) {
                list[i][j] = list[i][j] / t;
            }
        }

        for (unsigned i = 0; i < M; i++) {
            for (unsigned j = N; j < N * 2; j++) {
                (*this).data[i][j - N] = list[i][j];
            }
        }

        return (*this);
    }

    // Возвращение из обратной матрицы
    Matrix<M, N, Field> invert()
    {
        return (*this).inverted();
    }

    // Получение строки
    vector<Field> getRow(unsigned m)
    {
        if (m < 0 || m >= M) {
            return vector<Field>(N, Field(1, 0));
        }

        vector<Field> res(N, Field(0, 1));
        for (unsigned i = 0; i < N; i++) {
            res[i] = (*this).data[m][i];
        }
        return res;
    }

    // Получение столбца
    vector<Field> getColumn(unsigned n)
    {
        if (n < 0 || n >= N) {
            return vector<Field>(M, Field(1, 0));
        }

        vector<Field> res(M, Field(0, 1));
        for (unsigned i = 0; i < M; i++) {
            res[i] = (*this).data[i][n];
        }

        return res;
    }

    // оператор для доступа к элементам матрицы
    vector<Field>& operator[](unsigned i)
    {
        return data[i];
    }

    const vector<Field>& operator[](unsigned i) const
    {
        return data[i];
    }

    // Вывод матрицы
    void print()
    {
        BigRational result;
        for (unsigned i = 0; i < M; i++) {
            for (unsigned j = 0; j < N; j++) {
                BigRational number = data[i][j];
                BigInteger numer = number.get_numerator();
                BigInteger denom = number.get_denominator();
                bool flag = number.get_negFlag();
                BigInteger gcd = findGCD(numer, denom);
                BigRational res(numer / gcd, denom / gcd);
                result = (flag ? res.negate() : res);
                cout << result << ' ';
            }
            cout << '\n';
        }
    }
};

template <int N, typename Field = BigRational>
class SquareMatrix : public Matrix<N, N> {
public:
    vector<vector<Field>> data;
    SquareMatrix()
        : Matrix<N, N, Field>()
    {
    }
    SquareMatrix(vector<vector<Field>>& vec)
        : data(vec)
    {
    }
    // using используется для наследования методов из базового класса Matrix
    using Matrix<N, N, Field>::transpose;
    using Matrix<N, N, Field>::print;
    using Matrix<N, N, Field>::trace;
    using Matrix<N, N, Field>::rank;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Finite<5> a(7);
    Finite<5> b(3);
    Finite<5> c = a + b;
    // cout << c.getValue() << endl;

    vector<vector<BigRational>> vec = { { BigRational(2, 4),
                                            BigRational(1, 2) },
        { BigRational(1, 3),
            BigRational(1, 3) } };

    vector<vector<BigRational>> vec2 = {
        { BigRational(2, 1),
            BigRational(1, 2) },
        { BigRational(3, 4),
            BigRational(1, 3) }
    };

    vector<vector<BigRational>> vec3 = {
        { BigRational(1, 2),
            BigRational(1, 2) },
        { BigRational(1, 3),
            BigRational(1, 3) },
        { BigRational(1, 4),
            BigRational(1, 4) },
    };

    Matrix<2, 2, BigRational> matA(vec);
    Matrix<2, 2, BigRational> matС(vec);
    Matrix<2, 2, BigRational> matB(vec2);
    Matrix<3, 2, BigRational> matD(vec3);
    Matrix<2, 2> list, res;
    // matA.print();
    cout << "Изначальная матрица A:\n";
    matA.print();
    cout << '\n';

    cout << "Единичная матрица Е:\n";
    list.print();
    cout << '\n';

    cout << "A += E\n";
    matA += list;
    matA.print();
    cout << '\n';

    cout << "(A + E) -= E\n";
    matA -= list;
    matA.print();
    cout << '\n';

    cout << "Умножение матрицы А на скаляр: ";
    BigRational scalar(5, 1), scalar2(1, 5);
    cout << scalar << '\n';
    matA *= scalar;
    matA.print();
    matA *= scalar2;
    cout << '\n';

    cout << "Изначальная матрица B:\n";
    matB.print();
    cout << '\n';
    cout << "Умножение матрицы А на B:\n";
    matA *= matB;
    matA.print();
    cout << '\n';

    // Для теста Exeption при вызове определителя не квадратной матрицы
    // BigRational test = matD.det();

    BigRational detA = matС.det(), detB = matB.det();
    cout << "Определитель матрицы A: " << detA << '\n';
    cout << "Определитель матрицы B: " << detB << "\n\n";

    BigRational traceA = matС.trace(), traceB = matB.trace();
    cout << "След матрицы A: " << traceA << '\n';
    cout << "След матрицы B: " << traceB << "\n\n";

    cout << "Матрица после транспонирования:\n";
    matD.transpose();
    cout << '\n';
    matD.print();
    cout << '\n';

    int rank = matB.rank();
    cout << "Ранг матрицы B: " << rank << "\n\n";

    cout << "Искомая матрица B:\n";
    Matrix<2, 2, BigRational> copy_matB(vec2);
    matB.print();
    cout << "Обратная матрица B:\n";
    matB.inverted();
    matB.print();

    cout << "Обратная дважды матрица B:\n";
    matB.invert();
    matB.print();
    cout << '\n';

    vector<BigRational> row0 = matD.getRow(0);
    vector<BigRational> col0 = matD.getColumn(0);
    matD.print();
    cout << "Вывод первой (нулевой) строки из D:\n";
    for (int i = 0; i < row0.size(); i++) {
        cout << row0[i] << ' ';
    }
    cout << "\nВывод первого (нулевого) столбца из D:\n";
    for (int i = 0; i < col0.size(); i++) {
        cout << col0[i] << ' ';
    }
    cout << "\n\n";

    cout << "Первый по строке, первый по столбцу элемент D: " << matD[1][1] << "\n\n";

    vector<vector<BigRational>> tmp = { { BigRational(1, 1) } };
    SquareMatrix<1, BigRational> A(tmp);
    A.print();

    cout << (matA == matB);

    return 0;
}
