/*
 * RectangleSystemProcessor.h
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#ifndef RECTANGLESYSTEMPROCESSOR_H_
#define RECTANGLESYSTEMPROCESSOR_H_

#include <vector>
#include <set>

#include "Rectangle2D.h"
#include "using.h"

namespace Nitro {


class RectangleSystemProcessor {
public:
	RectangleSystemProcessor();
	RectangleSystemProcessor(const std::string&);
	virtual ~RectangleSystemProcessor();

	void printInput() const;
	void printIntersections() const;

	bool fillSystem(const std::string&);
	bool isEmpty() const;
	const RectDescrList& findIntersections();

private:
	void cleaupIntersections();
	void cleanupBuffer();
	void copyToBuffer(const RectDescrList&, int);
	void sortBuffer();
	bool generateIntersections(const RectDescrList&);

	std::string indexToString(const RectIndexes&) const;

private:
	RectDescrList m_inputRects;
	RectDescrList m_intersections;
	RectDescrList m_buffer;
};

} //namespace Nitro

#endif /* RECTANGLESYSTEMPROCESSOR_H_ */
