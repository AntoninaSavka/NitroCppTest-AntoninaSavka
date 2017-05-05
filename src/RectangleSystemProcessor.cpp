/*
 * RectangleSystemProcessor.cpp
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include <iterator>

#include "RectangleSystemProcessor.h"
#include "RectangleFactory.h"

RectangleSystemProcessor::RectangleSystemProcessor(const std::string& filePath) {
	RectangleFactory::generateRectangles(filePath, m_inputRects);

}

RectangleSystemProcessor::~RectangleSystemProcessor() {
	// TODO Auto-generated destructor stub
}


void RectangleSystemProcessor::printInput() const {
	for (auto& rect: m_inputRects) {
		std::cout << "\t" << rect.first <<": Rectangle at " << rect.second.toString() << std::endl;
	}
}

void RectangleSystemProcessor::printIntersections() const {
	for (auto& rect: m_intersections) {
		std::cout << "\tBetween rectangle " << rect.first <<" at " << rect.second.toString() << std::endl;
	}
}


void RectangleSystemProcessor::findIntersections() {
	cleaupIntersections();

	copyToBuffer(m_inputRects, m_inputRects.begin());

	bool intersectionExists = true;
	while (intersectionExists) {
		RectDescrList::const_iterator lastElemIt = m_intersections.begin() + m_intersections.size();

		sortBuffer();
		intersectionExists = generateIntersections(m_buffer);
		copyToBuffer(m_intersections, lastElemIt);
	}
}

/*****************************************************************************/
/*                               Private members                             */
/*****************************************************************************/
void RectangleSystemProcessor::cleaupIntersections(){
	m_intersections.clear();
}

void RectangleSystemProcessor::cleanupBuffer() {
	m_buffer.clear();
}

void RectangleSystemProcessor::copyToBuffer(const RectDescrList& rects, RectDescrList::const_iterator startIt) {
	cleanupBuffer();
	for (auto it = startIt; it != rects.end(); ++it) {
		m_buffer.push_back(*it);
	}
	std::cout << "Buffer size: " << m_buffer.size() << std::endl;
}

void RectangleSystemProcessor::sortBuffer() {
    if (m_buffer.size() > 0) {
    	m_buffer.sort([](const RectDescr& rect1, const RectDescr& rect2){return rect1.second < rect2.second;});
    }
}

bool RectangleSystemProcessor::generateIntersections(const RectDescrList& rects) {
	bool intersectionFound = false;
	for (auto cRectMainIt = rects.begin(); cRectMainIt != rects.end(); ++cRectMainIt) {
		for (auto cRectCompareIt = std::next(cRectMainIt); cRectCompareIt != rects.end(); ++cRectCompareIt) {
			if (cRectMainIt->second.intersectWith(cRectCompareIt->second)) {
				try {
					Rectangle2D intersection = cRectMainIt->second.getIntersection(cRectCompareIt->second);
					std::string intersectioId = cRectMainIt->first + " & " + cRectCompareIt->first;
					m_intersections.push_back(RectDescr(intersectioId, intersection));
					intersectionFound = true;
					std::cout << "intersection: " << intersection.toString() << std::endl;
				} catch (const std::invalid_argument& e) {
					std::cerr << "WARRNING: invalid intersection detected: " << e.what() << std::endl;
				}
			}
		}
	}

	return intersectionFound;
}

