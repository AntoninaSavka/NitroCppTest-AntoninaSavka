/*
 * Point2D.h
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#ifndef POINT2D_H_
#define POINT2D_H_

#include <string>

namespace Nitro {

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
	bool operator==(const Point2D&) const;

protected:
	int m_x={0};
	int m_y={0};
};

} //namespace Nitro
#endif /* POINT2D_H_ */
