#pragma once
#include <array>
#include <SFML/System.hpp>

class Vector4
{
	std::array<double, 4> cords; //koordynaty
public:
	Vector4(); //konstruktor
	~Vector4(); //destruktor
	Vector4& operator=(const Vector4& other); //przypisywanie

	Vector4& setX(double x); //ustawianie x
	Vector4& setY(double y); //ustawianie y
	Vector4& setZ(double z); //ustawianie z
	Vector4& setT(double t); //ustawianie t (używane w jednym miejscu - normalnie nie dotykamy jeśli nie chcemy nic zepsuć)
	sf::Vector2f Vector4::project(double width, double height, double fov, double viewerDistance) const;
	double getX() const; //wyciąganie x
	double getY() const; //wyciąganie y
	double getZ() const; //wyciąganie z
	double getT() const; //wyciąganie t (też raczej nie używać samemu)
};