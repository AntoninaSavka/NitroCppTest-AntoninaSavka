/*
 * Rectangle2D.h
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#ifndef RECTANGLE2D_H_
#define RECTANGLE2D_H_

#include <string>
#include "Point2D.h"

using IntersectionPoints = std::pair<Point2D, Point2D>;

class Rectangle2D {
public:
	Rectangle2D(int, int, int, int);
	Rectangle2D(const Point2D&, const Point2D&);
	virtual ~Rectangle2D();

	Point2D getTopLeft() const;
	Point2D getTopRight() const;
	Point2D getBottomLeft() const;
	Point2D getBottomRight() const;
	int getWidth() const;
	int getHeight() const;

	void setTopLeft(int, int);
	void setTopLeft(const Point2D&);
	void setWidth(int);
	void setHeight(int);

	bool intersectWith(const Rectangle2D&) const;
	Rectangle2D getIntersection(const Rectangle2D&) const;

	std::string toString() const;

	bool operator< (const Rectangle2D& rect) const;

protected:
	bool isPointInRectangle(const Point2D&) const;
	IntersectionPoints getIntersectionPoints(const Rectangle2D&) const;

protected:
	Point2D top;
	int width, height;
};

#endif /* RECTANGLE2D_H_ */
