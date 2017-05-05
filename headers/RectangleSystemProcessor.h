/*
 * RectangleSystemProcessor.h
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#ifndef RECTANGLESYSTEMPROCESSOR_H_
#define RECTANGLESYSTEMPROCESSOR_H_

#include <vector>

#include "Rectangle2D.h"

using RectDescr = std::pair<std::string, Rectangle2D>;
using RectDescrList = std::vector<RectDescr>;

class RectangleSystemProcessor {
public:
	RectangleSystemProcessor(const std::string&);
	virtual ~RectangleSystemProcessor();

	void printInput() const;
	void printIntersections() const;
	void sort();

	void findIntersections();

private:
	void cleaupIntersections();
	void cleanupBuffer();
	void copyToBuffer(const RectDescrList&, RectDescrList::const_iterator);
	void sortBuffer();
	bool generateIntersections(const RectDescrList&);

private:
	RectDescrList m_inputRects;
	RectDescrList m_intersections;
	RectDescrList m_buffer;
};

#endif /* RECTANGLESYSTEMPROCESSOR_H_ */
