#pragma once
#include "Vector4.hpp"
//#include "Vector4.cpp"
#include <cmath>

using coordinates = std::array<std::array<double, 4>, 4>;

class Matrix2 //to jest czysto pomocnicze - dla algorytmu starssena, czyli nie używać tego raczej
{
	std::array<double, 4> cords;
public:
	Matrix2();
	Matrix2(double a00, double a01, double a10, double a11);
	~Matrix2();
	Matrix2 operator+(const Matrix2& other);
	Matrix2 operator-(const Matrix2& other);
	Matrix2 operator*(const Matrix2& other);
	Matrix2& operator=(const Matrix2& other);
	double get(short i) const;
};

class Matrix
{
	coordinates cords; //zawartość matrycy
public:
	Matrix(); //konstruktor
	~Matrix(); //destruktor
	Matrix operator*(const Matrix& other); //mnożenie macierzy (sztrasen głupi ;_;)
	Vector4 operator*(const Vector4& other); //mnożenie macierzy z wektorem
	Matrix& operator=(const Matrix& other); //przypisywanie

	void zeroize(); //wszędzie zera
	void setRotX(double alfa); //rotacjax
	void setRotY(double alfa); //rotacjay
	void setRotZ(double alfa); //rotacjaz
	void setTranslate(double tx, double ty, double tz); //logistyka

	double get(short i, short j) const; //wyciąganie elementu (samemu raczej nie dotykać)

};
