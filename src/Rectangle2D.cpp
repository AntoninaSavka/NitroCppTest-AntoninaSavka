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

using Nitro::Point2D;
using Nitro::Rectangle2D;

/*****************************************************************************/
/*                    Constructors and destructors                           */
/*****************************************************************************/
/*
 * Rectangle2D default constructor - creates empty rectangle and represent
 * logic of null_object
 */
Rectangle2D::Rectangle2D() {

}

/*
 * Rectangle2D constructor that creates rectangle from top left point
 * coordinates, width and height.
 * (x,y)
 *    . -------------- width
 *    |
 *    |
 *    |
 *    height
 *
 * @parameter ids        - set with rectangle id or intersecting
 *                         rectangles ids (e.g {3} for origin rectangle and
 *                         {3,4} for intersection of rectangles 3 and 4)
 * @parameter x - coordinate x of top left corner
 * @parameter y - coordinate y of top left corner
 * @parameter w - rectangle width
 * @parameter h - rectangle height
 */
Rectangle2D::Rectangle2D(const RectIndexes& ids, int x, int y, int w, int h): m_top(x, y) {
	setIds(ids);
	setWidth(w);
	setHeight(h);
}

/*
 * Rectangle2D constructor that creates rectangle from top left and
 * bottom right points
 * topLeft
 *    . -------------- .
 *    |	               |
 *    |                |
 *    . -------------- .
 *                   bottomRight
 *
 * @parameter ids        - set with rectangle id or intersecting
 *                         rectangles ids (e.g {3} for origin rectangle and
 *                         {3,4} for intersection of rectangles 3 and 4)
 * @parameter topLeft    - top left corner point
 * @parameter bottomLeft - bottom right corner point
 */
Rectangle2D::Rectangle2D(const RectIndexes& ids, const Point2D& topLeft, const Point2D& bottomRight) {
	setIds(ids);
	setTopLeft(topLeft);
    setWidth(bottomRight.getX() - topLeft.getX());
    setHeight(bottomRight.getY() - topLeft.getY());
}

/*
 * Rectangle2D Default destructor
 */
Rectangle2D::~Rectangle2D() {
}


/*****************************************************************************/
/*                               PUBLIC METHODS                              */
/*****************************************************************************/
/*                             Getters and setters                           */
/*****************************************************************************/
/*
 *
 */
const RectIndexes& Rectangle2D::getIds() const {
	return m_rectIds;
}

/*
 * Get rectangle top left corner point
 * @return - top left corner point
 */
Point2D Rectangle2D::getTopLeft() const {
	return this->m_top;
}

/*
 * Get rectangle top right corner point
 * @return - top right corner point
 */
Point2D Rectangle2D::getTopRight() const {
	return Point2D(m_top.getX() + getWidth(), m_top.getY());
}

/*
 * Get rectangle bottom left corner point
 * @return - bottom left corner point
 */
Point2D Rectangle2D::getBottomLeft() const {
	return Point2D(m_top.getX(), m_top.getY() + getHeight());
}

/*
 * Get rectangle bottom right corner point
 * @return - bottom right corner point
 */
Point2D Rectangle2D::getBottomRight() const {
	return Point2D(m_top.getX() + getWidth(), m_top.getY() + getHeight());
}

/*
 * Get rectangle width
 * @return - rectangle width
 */
int Rectangle2D::getWidth() const {
	return this->m_width;
}

/*
 * Get rectangle height
 * @return - rectangle height
 */
int Rectangle2D::getHeight() const {
	return this->m_height;
}

/*
 * Set rectangle id or intersecting rectangles ids.
 * If passed set of ids is empty - rectangle will be invalid
 * @parameter ids - set of rectangle id or intersecting rectangles ids
 *                  (e.g {3} for origin rectangle and {3,4} for intersection
 *                  of rectangles 3 and 4)
 */
void Rectangle2D::setIds(const RectIndexes& ids) {
	m_rectIds.clear();
	m_rectIds.insert(ids.begin(), ids.end());
}


/*
 * Set rectangle top left corner point
 * @parameter x - top left coordinate x
 * @parameter y - top left coordinate y
 */
void Rectangle2D::setTopLeft(int x, int y) {
	this->m_top.setX(x);
	this->m_top.setY(y);
}

/*
 * Set rectangle top left corner point
 * @parameter point - top left coordinate point
 */
void Rectangle2D::setTopLeft(const Point2D& point) {
	this->m_top.setX(point.getX());
	this->m_top.setY(point.getY());
}

/*
 * Set rectangle width. If passed width is not positive value
 * then width be set to 0 and rectangle will be invalid
 * @parameter w - width value
 *
 */
void Rectangle2D::setWidth(int w) {
	this->m_width = (w > 0) ? w : 0;
}

/*
 * Set rectangle height. If passed height is not positive value
 * then width be set to 0 and rectangle will be invalid
 * @parameter h - height value
 */
void Rectangle2D::setHeight(int h) {
	this->m_height = (h > 0)? h : 0;
}

bool Rectangle2D::isValid() const
{
	return (m_height) > 0 && (m_width > 0) && !m_rectIds.empty();
}


/*****************************************************************************/
/*                                 Intersection                              */
/*****************************************************************************/
/*
 * Check whether this rectangle has intersection with passed rectangle.
 *
 * @algorithm      - rectangle intersects with another rectangle if any of
 *                   passed rectangle is inside this rectangle and rectangles
 *                   have common area (if rectangles intersect only on an edge
 *                   assume that they do not intersect at all).
 *                   NOTE: Algorithm assumes that this rectangles is less than
 *                   passed one (see operator < description)
 *
 * @parameter rect - rectangle with which intersection has to be detected
 * @return         - true if this rectangle has intersection with passed one
 */
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


/*
 * Get rectangle of intersection this rectangle with passed one.
 *
 * @parameter rect - rectangle with which intersection area has to be detected
 * @return         - intersection are rectangle
 */
Rectangle2D Rectangle2D::getIntersection(const Rectangle2D& rect) const {
	RectIndexes newIds;
	newIds.insert(getIds().begin(), getIds().end());
	newIds.insert(rect.getIds().begin(), rect.getIds().end());
	IntersectionPoints commonPoints = getIntersectionPoints(rect);

	return Rectangle2D(newIds, commonPoints.first, commonPoints.second);
}

/*****************************************************************************/
/*                        Convertors and operators                           */
/*****************************************************************************/
/*
 * Represent this rectangle geometry as string description
 * @return - string description of rectangle with information about top left
 *           corner coordinates, width and height
 */
std::string Rectangle2D::descToString() const {
	std::string message;
	message.append(getTopLeft().toString());
	message.append(", w=");
	message.append(std::to_string(getWidth()));
	message.append(", h=");
	message.append(std::to_string(getHeight()));
	message.append(".");
	return message;
}

/*
 * Represent rectangle ids as string value
 * @param indexSet - set of single or intersecting rectangles ids
 * @return         - string with rectangle/intersection ids
 */
std::string Rectangle2D::idsToString() const {
	std::string message;
	unsigned int pos = 0;
	for (const auto idx: getIds()) {
		message.append(std::to_string(idx));
		if (pos < getIds().size() - 1) {
			message.append(" and ");
		}
		++pos;
	}

	return message;
}

/*
 * Overload operator "less than"
 * @parameter rect - rectangle with which current one has to be compared
 * @return - true if this rectangle top left point is less than top left
 *           point of passed rectangle else return false
 */
bool Rectangle2D::operator< (const Rectangle2D& rect) const {
	return (this->getTopLeft() < rect.getTopLeft());
}


/*****************************************************************************/
/*                             PROTECTED METHODS                             */
/*****************************************************************************/
/*
 * Detect whether passed point is inside current rectangle, including edges
 * @parameter point - point that has to be validated
 * @return          - true if point is inside this rectangle or on it's edges
 */
bool Rectangle2D::isPointInRectangle(const Point2D& point) const {
	Point2D&& topLeft = getTopLeft();
	Point2D&& bottomRight = getBottomRight();

	return (point.getX() >= topLeft.getX()) && (point.getX() <= bottomRight.getX())
			&& (point.getY() >= topLeft.getY()) && (point.getY() <= bottomRight.getY());
}

/*
 * Detect top left and right bottom points of rectangles intersection
 * @parameter rect - rectangle for which intersection points with this rectangle
 *                   has to be detected
 * @return         - pair of intersection's top left and bottom right points
 */
IntersectionPoints Rectangle2D::getIntersectionPoints(const Rectangle2D& rect) const {
	Point2D newTopLeft;
	newTopLeft.setX(std::max(this->getTopLeft().getX(), rect.getTopLeft().getX()));
	newTopLeft.setY(std::max(this->getTopLeft().getY(), rect.getTopLeft().getY()));

	Point2D newBottomRight;
	newBottomRight.setX(std::min(this->getBottomRight().getX(), rect.getBottomRight().getX()));
	newBottomRight.setY(std::min(this->getBottomRight().getY(), rect.getBottomRight().getY()));

	return IntersectionPoints(newTopLeft, newBottomRight);
}
