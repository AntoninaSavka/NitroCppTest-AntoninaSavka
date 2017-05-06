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
#include <algorithm>

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
		std::cout << "\t" << indexToString(rect.first) <<": Rectangle at " << rect.second.toString() << std::endl;
	}
}

void RectangleSystemProcessor::printIntersections() const {
	for (auto& rect: m_intersections) {
		std::cout << "\tBetween rectangle " << indexToString(rect.first) <<" at " << rect.second.toString() << std::endl;
	}
}


void RectangleSystemProcessor::findIntersections() {
	cleaupIntersections();

	copyToBuffer(m_inputRects, 0);

	bool intersectionExists = true;
	while (intersectionExists) {
		int startIndex = m_intersections.size();

		sortBuffer();
		intersectionExists = generateIntersections(m_buffer);
		copyToBuffer(m_intersections, startIndex);
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

void RectangleSystemProcessor::copyToBuffer(const RectDescrList& rects, int startIndex) {
	cleanupBuffer();
	m_buffer.insert(m_buffer.begin(), rects.begin() + startIndex, rects.end());
}

void RectangleSystemProcessor::sortBuffer() {
    if (m_buffer.size() > 0) {
    	std::sort(m_buffer.begin(), m_buffer.end(), [](const RectDescr& rect1, const RectDescr& rect2){return rect1.second < rect2.second;});
    }
}

bool RectangleSystemProcessor::generateIntersections(const RectDescrList& rects) {
	bool intersectionFound = false;
	for (auto cRectMainIt = rects.begin(); cRectMainIt != rects.end(); ++cRectMainIt) {
		for (auto cRectCompareIt = std::next(cRectMainIt); cRectCompareIt != rects.end(); ++cRectCompareIt) {
			//check whether intersection already exists
			RectIndexes newIntersectionId;
			newIntersectionId.insert(cRectMainIt->first.begin(), cRectMainIt->first.end());
			newIntersectionId.insert(cRectCompareIt->first.begin(), cRectCompareIt->first.end());

			auto foundIt = std::find_if(m_intersections.begin(), m_intersections.end(),
					[&newIntersectionId](const RectDescr& rectDesc)->bool {return rectDesc.first == newIntersectionId;});
			if (foundIt != m_intersections.end()) {
				continue;
			}

			if (cRectMainIt->second.intersectWith(cRectCompareIt->second)) {
				try {
					Rectangle2D intersection = cRectMainIt->second.getIntersection(cRectCompareIt->second);
					m_intersections.push_back(RectDescr(newIntersectionId, intersection));
					intersectionFound = true;
				} catch (const std::invalid_argument& e) {
					std::cerr << "WARRNING: invalid intersection detected: " << e.what() << std::endl;
				}
			}
		}
	}

	return intersectionFound;
}


std::string RectangleSystemProcessor::indexToString(const RectIndexes& indexSet) const {
	std::string message;
	int pos = 0;
	for (const auto idx: indexSet) {
		message.append(std::to_string(idx));
		if (pos < indexSet.size() - 1) {
			message.append(" and ");
		}
		++pos;
	}

	return message;
}
