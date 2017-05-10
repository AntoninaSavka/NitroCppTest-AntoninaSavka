/*
 * Point2D.cpp
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#include "Point2D.h"

using Nitro::Point2D;

/*****************************************************************************/
/*                    Constructors and destructors                           */
/*****************************************************************************/
/*
 * Point2D Default constructor Constructor: init point with coordinates (0,0)
 */
Point2D::Point2D() {
}


/*
 * Point2D Constructor: init point with coordinates (x,y)
 * @parameter x - coordinate x
 * @parameter y - coordinate y
 */
Point2D::Point2D(int x, int y): m_x(x), m_y(y) {
}

/*
 * Point2D Default Destructor
 */
Point2D::~Point2D() {
}


/*****************************************************************************/
/*                               PUBLIC METHODS                              */
/*****************************************************************************/
/*                             Getters and setters                           */
/*****************************************************************************/
/*
 * Get point x coordinate
 * @return - point x coordinate
 */
int Point2D::getX() const {
	return this->m_x;
}

/*
 * Get point y coordinate
 * @return - point y coordinate
 */
int Point2D::getY() const {
	return this->m_y;
}

/*
 * Set point x coordinate
 * @parameter x - point x coordinate
 */
void Point2D::setX(int x) {
	this->m_x = x;
}

/*
 * Set point y coordinate
 * @parameter y - point y coordinate
 */
void Point2D::setY(int y) {
	this->m_y = y;
}


/*****************************************************************************/
/*                        Convertors and operators                           */
/*****************************************************************************/
/*
 * Represent Point2D as string
 * @return - string with point coordinates set, e.g. "(3,7)"
 */
std::string Point2D::toString() const {
	std::string message;
	message.append("(");
	message.append(std::to_string(getX()));
	message.append(",");
	message.append(std::to_string(getY()));
	message.append(")");
	return message;
}


/*
 * Overload operator "less than"
 * @parameter point - point with which current one has to be compared
 * @return:
 * 		- true if this->x value is less than point.x
 * 		- true if this->x value is equal to point.x and this->y less than point.y
 * 		- else return false
 */
bool Point2D::operator<(const Point2D& point) const {
	if (this->getX() < point.getX()) {
		return true;
	} else if (this->getX() == point.getX()) {
		return (this->getY() < point.getY());
	} else {
		return false;
	}
}

/*
 * Overload operator "equal"
 */
bool Point2D::operator==(const Point2D& point) const {
	return getX() == point.getX() && getY() == point.getY();
}
