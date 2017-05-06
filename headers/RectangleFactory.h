/*
 * RectangleFactory.h
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#ifndef RECTANGLEFACTORY_H_
#define RECTANGLEFACTORY_H_

#include <string>
#include <vector>
#include <set>

#include "Rectangle2D.h"

using RectIndexes = std::set<int>;
using RectDescr = std::pair<RectIndexes, Rectangle2D>;

class RectangleFactory {
public:
	static void generateRectangles(const std::string&, std::vector<RectDescr>&);

protected:
	RectangleFactory();
	virtual ~RectangleFactory();

protected:
	static std::string m_cRestsTag;
	static std::vector<std::string> m_cRequiredParams;
	static int m_cMaxSize;
};

#endif /* RECTANGLEFACTORY_H_ */
