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

using RectIndexes = std::set<int>;
using RectDescr = std::pair<RectIndexes, Rectangle2D>;
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
	void copyToBuffer(const RectDescrList&, int);
	void sortBuffer();
	bool generateIntersections(const RectDescrList&);

	std::string indexToString(const RectIndexes&) const;

private:
	RectDescrList m_inputRects;
	RectDescrList m_intersections;
	RectDescrList m_buffer;
};

#endif /* RECTANGLESYSTEMPROCESSOR_H_ */
