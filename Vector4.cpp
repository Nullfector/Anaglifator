#include "Vector4.hpp"
#include <SFML/System.hpp>

Vector4::Vector4() : cords{ 0,0,0,1.0 } {}

Vector4::~Vector4() {}

double Vector4::getX() const { return this->cords[0]; }
double Vector4::getY() const { return this->cords[1]; }
double Vector4::getZ() const { return this->cords[2]; }

Vector4& Vector4::operator=(const Vector4& other)
{
	this->cords = { other.getX(), other.getY(), other.getZ(), 1.0 };
	return *this;
}


Vector4& Vector4::setX(double x)
{
	this->cords[0] = x;
	return *this;
}

Vector4& Vector4::setY(double y)
{
	this->cords[1] = y;
	return *this;
}

Vector4& Vector4::setZ(double z)
{
	this->cords[2] = z;
	return *this;
}

Vector4& Vector4::setT(double t)
{
	this->cords[3] = t;
	return *this;
}

sf::Vector2f Vector4::project(double width, double height, double fov, double viewerDistance) const {
	double zDepth = viewerDistance + this->getZ();
	if (zDepth < 0.1) zDepth = 0.1;
	double factor = fov / zDepth;

	double projectedX = this->getX() * factor + (width / 2.0);
	double projectedY = this->getY() * factor + (height / 2.0);

	return sf::Vector2f(projectedX, projectedY);

}


double Vector4::getT() const { return this->cords[3]; }
