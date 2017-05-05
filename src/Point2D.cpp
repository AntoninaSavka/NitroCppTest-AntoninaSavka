/*
 * Point2D.cpp
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#include "Point2D.h"

Point2D::Point2D() {
	setX(0);
	setY(0);
}

Point2D::Point2D(int x, int y) {
	setX(x);
	setY(y);
}


Point2D::~Point2D() {
	// TODO Auto-generated destructor stub
}

int Point2D::getX() const {
	return this->x;
}

int Point2D::getY() const {
	return this->y;
}

void Point2D::setX(int x) {
	this->x = x;
}

void Point2D::setY(int y) {
	this->y = y;
}

std::string Point2D::toString() const {
	std::string message;
	message.append("(");
	message.append(std::to_string(getX()));
	message.append(",");
	message.append(std::to_string(getY()));
	message.append(")");
	return message;
}

bool Point2D::operator<(const Point2D& point) const {
	if (this->getX() < point.getX()) {
		return true;
	} else if (this->getX() == point.getX()) {
		return (this->getY() < point.getY());
	} else {
		return false;
	}
}
