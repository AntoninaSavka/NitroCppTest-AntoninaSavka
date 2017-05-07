/*
 * Point2D.h
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#ifndef POINT2D_H_
#define POINT2D_H_

#include <string>

class Point2D {
public:
	Point2D();
	Point2D(int, int);
	virtual ~Point2D();

	int getX() const;
	int getY() const;

	void setX(int);
	void setY(int);

	std::string toString() const;

	bool operator<(const Point2D&) const;

protected:
	int m_x;
	int m_y;
};

#endif /* POINT2D_H_ */
