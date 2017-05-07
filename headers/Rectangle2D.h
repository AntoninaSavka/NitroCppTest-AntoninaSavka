/*
 * Rectangle2D.h
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#ifndef RECTANGLE2D_H_
#define RECTANGLE2D_H_

#include <string>
#include <set>
#include "Point2D.h"

using IntersectionPoints = std::pair<Point2D, Point2D>;
using RectIndexes = std::set<unsigned long>;

class Rectangle2D {
public:
	Rectangle2D(const RectIndexes&, int, int, int, int);
	Rectangle2D(const RectIndexes&, const Point2D&, const Point2D&);
	virtual ~Rectangle2D();

	const RectIndexes& getIds() const;
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

	std::string descToString() const;
	std::string idsToString() const;

	bool operator< (const Rectangle2D& rect) const;

protected:
	void setIds(const RectIndexes&);

	bool isPointInRectangle(const Point2D&) const;
	IntersectionPoints getIntersectionPoints(const Rectangle2D&) const;

protected:
	RectIndexes m_rectIds;
	Point2D m_top;
	int m_width, m_height;
};

#endif /* RECTANGLE2D_H_ */
