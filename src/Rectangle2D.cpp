/*
 * Rectangle2D.cpp
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#include "Rectangle2D.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Rectangle2D::Rectangle2D(int x, int y, int w, int h) {
	setTopLeft(x, y);
	setWidth(w);
	setHeight(h);
}

Rectangle2D::Rectangle2D(const Point2D& topLeft, const Point2D& bottomRight) {
	setTopLeft(topLeft);
    setWidth(bottomRight.getX() - topLeft.getX());
    setHeight(bottomRight.getY() - topLeft.getY());
}

Rectangle2D::~Rectangle2D() {
	// TODO Auto-generated destructor stub
}

Point2D Rectangle2D::getTopLeft() const {
	return this->top;
}

Point2D Rectangle2D::getTopRight() const {
	return Point2D(top.getX() + getWidth(), top.getY());
}

Point2D Rectangle2D::getBottomLeft() const {
	return Point2D(top.getX(), top.getY() + getHeight());
}

Point2D Rectangle2D::getBottomRight() const {
	return Point2D(top.getX() + getWidth(), top.getY() + getHeight());
}


int Rectangle2D::getWidth() const {
	return this->width;
}

int Rectangle2D::getHeight() const {
	return this->height;
}

void Rectangle2D::setTopLeft(int x, int y) {
	this->top.setX(x);
	this->top.setY(y);
}

void Rectangle2D::setTopLeft(const Point2D& point) {
	this->top.setX(point.getX());
	this->top.setY(point.getY());
}

void Rectangle2D::setWidth(int w) {
	if (w <= 0) {
		throw std::invalid_argument("ERROR: Rectangle width has to be positive integer");
	} else {
		this->width = w;
	}
}

void Rectangle2D::setHeight(int h) {
	if (h <= 0) {
		throw std::invalid_argument("ERROR: Rectangle height has to be positive integer");
	} else {
		this->height = h;
	}
}

bool Rectangle2D::intersectWith(const Rectangle2D& rect) const {
	bool isAnyCommonPoint = (isPointInRectangle(rect.getTopLeft()) ||
			isPointInRectangle(rect.getTopRight()) ||
			isPointInRectangle(rect.getBottomLeft()) ||
			isPointInRectangle(rect.getBottomRight()));
	if (!isAnyCommonPoint) {
		return false;
	}

	IntersectionPoints commonPoints = getIntersectionPoints(rect);
	bool isWidthPositive = (commonPoints.second.getX() - commonPoints.first.getX()) > 0;
	bool isHeightPositive = (commonPoints.second.getY() - commonPoints.first.getY()) > 0;
	return isWidthPositive && isHeightPositive;
}

Rectangle2D Rectangle2D::getIntersection(const Rectangle2D& rect) const {
	IntersectionPoints commonPoints = getIntersectionPoints(rect);

    // here exception could be thrown by constructor.
	// code, that requested new intersection is responsible to catch it
	return Rectangle2D(commonPoints.first, commonPoints.second);
}

std::string Rectangle2D::toString() const {
	std::string message;
	message.append(getTopLeft().toString());
	message.append(", w=");
	message.append(std::to_string(getWidth()));
	message.append(", h=");
	message.append(std::to_string(getHeight()));
	message.append(".");
	return message;
}

bool Rectangle2D::operator< (const Rectangle2D& rect) const {
	return (this->getTopLeft() < rect.getTopLeft());
}

bool Rectangle2D::isPointInRectangle(const Point2D& point) const {
	Point2D&& topLeft = getTopLeft();
	Point2D&& bottomRight = getBottomRight();

	return (point.getX() >= topLeft.getX()) && (point.getX() <= bottomRight.getX())
			&& (point.getY() >= topLeft.getY()) && (point.getY() <= bottomRight.getY());
}

IntersectionPoints Rectangle2D::getIntersectionPoints(const Rectangle2D& rect) const {
	Point2D newTopLeft;
	newTopLeft.setX(std::max(this->getTopLeft().getX(), rect.getTopLeft().getX()));
	newTopLeft.setY(std::max(this->getTopLeft().getY(), rect.getTopLeft().getY()));

	Point2D newBottomRight;
	newBottomRight.setX(std::min(this->getBottomRight().getX(), rect.getBottomRight().getX()));
	newBottomRight.setY(std::min(this->getBottomRight().getY(), rect.getBottomRight().getY()));

	return IntersectionPoints(newTopLeft, newBottomRight);
}
