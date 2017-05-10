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

using IntersectionPoints = std::pair<Nitro::Point2D, Nitro::Point2D>;
using RectIndexes = std::set<unsigned long>;

namespace Nitro {

class Rectangle2D {
public:
	Rectangle2D();
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

	void setIds(const RectIndexes&);
	void setTopLeft(int, int);
	void setTopLeft(const Point2D&);
	void setWidth(int);
	void setHeight(int);

	bool isValid() const;

	bool intersectWith(const Rectangle2D&) const;
	Rectangle2D getIntersection(const Rectangle2D&) const;

	std::string descToString() const;
	std::string idsToString() const;

	bool operator< (const Rectangle2D& rect) const;

protected:
	bool isPointInRectangle(const Point2D&) const;
	IntersectionPoints getIntersectionPoints(const Rectangle2D&) const;

protected:
	RectIndexes m_rectIds;
	Point2D m_top;
	int m_width={0}, m_height={0};
};

} //namespace Nitro
#endif /* RECTANGLE2D_H_ */
