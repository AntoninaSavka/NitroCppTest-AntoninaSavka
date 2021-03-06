/*
 * RectangleFactory.h
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#ifndef RECTANGLEFACTORY_H_
#define RECTANGLEFACTORY_H_

#include <string>

#include "Rectangle2D.h"
#include "using.h"

namespace Nitro {

class RectangleFactory {
public:
	virtual ~RectangleFactory();

	static void generateRectangles(const std::string&, RectDescrList&);

protected:
	RectangleFactory();

protected:
	static std::string m_cRectsTag;
	static std::vector<std::string> m_cRequiredParams;
	static unsigned int m_cMaxSize;
};

} // namespace Nitro
#endif /* RECTANGLEFACTORY_H_ */
