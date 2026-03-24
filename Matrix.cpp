#include "Matrix.hpp"

Matrix2::Matrix2()
{
    this->cords[0] = 0;
    this->cords[1] = 0;
    this->cords[2] = 0;
    this->cords[3] = 0;
}

Matrix2::~Matrix2() {}

Matrix2::Matrix2(double a00, double a01, double a10, double a11)
{
    this->cords[0] = a00;
    this->cords[1] = a01;
    this->cords[2] = a10;
    this->cords[3] = a11;
}

Matrix2 Matrix2::operator+(const Matrix2& other)
{
    Matrix2 wyn;
    wyn.cords[0] = this->cords[0] + other.cords[0];
    wyn.cords[1] = this->cords[1] + other.cords[1];
    wyn.cords[2] = this->cords[2] + other.cords[2];
    wyn.cords[3] = this->cords[3] + other.cords[3];
    return wyn;
}

Matrix2 Matrix2::operator-(const Matrix2& other)
{
    Matrix2 wyn;
    wyn.cords[0] = this->cords[0] - other.cords[0];
    wyn.cords[1] = this->cords[1] - other.cords[1];
    wyn.cords[2] = this->cords[2] - other.cords[2];
    wyn.cords[3] = this->cords[3] - other.cords[3];
    return wyn;
}

Matrix2 Matrix2::operator*(const Matrix2& other)
{
    Matrix2 wyn;
    wyn.cords[0] = (other.cords[0]*this->cords[0])+(other.cords[2]*this->cords[1]);
    wyn.cords[1] = (other.cords[1]*this->cords[0])+(other.cords[3]*this->cords[1]);
    wyn.cords[2] = (other.cords[0]*this->cords[2])+(other.cords[2]*this->cords[3]);
    wyn.cords[3] = (other.cords[1]*this->cords[2])+(other.cords[3]*this->cords[3]);
    return wyn;
}

Matrix2& Matrix2::operator=(const Matrix2& other)
{
    for(short i=0;i<4;i++) {this->cords[i] = other.cords[i];}
    return *this;
}

double Matrix2::get(short i) const
{
    return this->cords[i];
}

Matrix::Matrix()
{
    this->cords[0] = {0,0,0,0};
    this->cords[1] = {0,0,0,0};
    this->cords[2] = {0,0,0,0};
    this->cords[3] = {0,0,0,0};
}

Matrix::~Matrix() {}

Matrix& Matrix::operator=(const Matrix& other)
{
    for(short i=0;i<4;i++)
    {
        for(short j=0;j<4;j++)
        {
            this->cords[i][j] = other.cords[i][j];
        }
    }
    return *this;
}


//zachciało mi się bawić się w optymalność i sztraseny jakieś pisać.......ehhhhhhhhhhhhhhhhhhhh
Matrix Matrix::operator*(const Matrix& other)
{
    Matrix2 A11(this->cords[0][0], this->cords[0][1], this->cords[1][0], this->cords[1][1]);
    Matrix2 A12(this->cords[0][2], this->cords[0][3], this->cords[1][2], this->cords[1][3]);
    Matrix2 A21(this->cords[2][0], this->cords[2][1], this->cords[3][0], this->cords[3][1]);
    Matrix2 A22(this->cords[2][2], this->cords[2][3], this->cords[3][2], this->cords[3][3]);

    Matrix2 B11(other.cords[0][0], other.cords[0][1], other.cords[1][0], other.cords[1][1]);
    Matrix2 B12(other.cords[0][2], other.cords[0][3], other.cords[1][2], other.cords[1][3]);
    Matrix2 B21(other.cords[2][0], other.cords[2][1], other.cords[3][0], other.cords[3][1]);
    Matrix2 B22(other.cords[2][2], other.cords[2][3], other.cords[3][2], other.cords[3][3]);

    Matrix2 C11,C12,C21,C22;

    C11 = ((A11+A22)*(B11+B22))+(A22*(B21-B11))-((A11+A12)*B22)+((A12-A22)*(B21+B22));
    C12 = (A11*(B12-B22))+((A11+A12)*B22);
    C21 = ((A21+A22)*B11)+(A22*(B21-B11));
    C22 = ((A11+A22)*(B11+B22))-((A21+A22)*B11)+(A11*(B12-B22))+((A21-A11)*(B11+B12));

    Matrix wyn;
    wyn.cords[0][0] = C11.get(0);
    wyn.cords[0][1] = C11.get(1);
    wyn.cords[1][0] = C11.get(2);
    wyn.cords[1][1] = C11.get(3);

    wyn.cords[0][2] = C12.get(0);
    wyn.cords[0][3] = C12.get(1);
    wyn.cords[1][2] = C12.get(2);
    wyn.cords[1][3] = C12.get(3);

    wyn.cords[2][0] = C21.get(0);
    wyn.cords[2][1] = C21.get(1);
    wyn.cords[3][0] = C21.get(2);
    wyn.cords[3][1] = C21.get(3);

    wyn.cords[2][2] = C22.get(0);
    wyn.cords[2][3] = C22.get(1);
    wyn.cords[3][2] = C22.get(2);
    wyn.cords[3][3] = C22.get(3);

    return wyn;
}

void Matrix::zeroize()
{
    for(short i=0;i<4;i++)
    {
        for(short j=0;j<4;j++)
        {
            this->cords[i][j] = 0.0;
        }
    }
}

void Matrix::setRotX(double alfa)
{
    this->zeroize();
    this->cords[0][0] = 1.0;
    this->cords[3][3] = 1.0;
    this->cords[1][1] = cos(alfa);
    this->cords[1][2] = -sin(alfa);
    this->cords[2][1] = sin(alfa);
    this->cords[2][2] = cos(alfa);
}

void Matrix::setRotY(double alfa)
{
    this->zeroize();
    this->cords[0][0] = cos(alfa);
    this->cords[2][2] = cos(alfa);
    this->cords[1][1] = 1.0;
    this->cords[3][3] = 1.0;
    this->cords[0][2] = sin(alfa);
    this->cords[2][0] = -sin(alfa);
}

void Matrix::setRotZ(double alfa)
{
    this->zeroize();
    this->cords[0][0] = cos(alfa);
    this->cords[2][2] = 1.0;
    this->cords[1][1] = cos(alfa);
    this->cords[3][3] = 1.0;
    this->cords[0][1] = -sin(alfa);
    this->cords[1][0] = sin(alfa);
}

void Matrix::setTranslate(double tx, double ty, double tz)
{
    this->zeroize();
    for(short i=0;i<4;i++)
    {
        this->cords[i][i] = 1.0;
    }
    this->cords[0][3] = tx;
    this->cords[1][3] = ty;
    this->cords[2][3] = tz;
}

double Matrix::get(short i, short j) const
{
    return this->cords[i][j];
}

Vector4 Matrix::operator*(const Vector4& other)
{
    Vector4 wyn;
    wyn.setX(other.getX()*this->cords[0][0]+other.getY()*this->cords[0][1]+other.getZ()*this->cords[0][2]+other.getT()*this->cords[0][3]);
    wyn.setY(other.getX()*this->cords[1][0]+other.getY()*this->cords[1][1]+other.getZ()*this->cords[1][2]+other.getT()*this->cords[1][3]);
    wyn.setZ(other.getX()*this->cords[2][0]+other.getY()*this->cords[2][1]+other.getZ()*this->cords[2][2]+other.getT()*this->cords[2][3]);
    wyn.setT(other.getX()*this->cords[3][0]+other.getY()*this->cords[3][1]+other.getZ()*this->cords[3][2]+other.getT()*this->cords[3][3]);
    return wyn;
}