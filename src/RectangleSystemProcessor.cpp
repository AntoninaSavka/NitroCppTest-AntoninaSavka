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

using Nitro::RectangleSystemProcessor;

/*****************************************************************************/
/*                    Constructors and destructors                           */
/*****************************************************************************/
/*
 * RectangleSystemProcessor default constructor
 */
RectangleSystemProcessor::RectangleSystemProcessor() {

}

/*
 * RectangleSystemProcessor constructor that generate array of rectangles from
 * json file
 * @parameter filePath - path to json file with rectangles description
 *                       Required file format example:
 * [
 *   {
 *    "rects": [
 *        {"x": 100, "y": 100, "w": 500, "h": 500 },
 *        {"x": 120, "y": 120, "w": 400, "h": 400 }
 *    ]
 *   }
 * ]
 */
RectangleSystemProcessor::RectangleSystemProcessor(const std::string& filePath) {
	fillSystem(filePath);
}

/*
 * RectangleSystemProcessor default destructor
 */
RectangleSystemProcessor::~RectangleSystemProcessor() {
}


/*****************************************************************************/
/*                             PUBLIC METHODS                                */
/*****************************************************************************/
/*                        Converters and operators                           */
/*****************************************************************************/
/*
 * Print out input rectangles
 */
void RectangleSystemProcessor::printInput() const {
	for (auto& rect: m_inputRects) {
		std::cout << "\t" << rect->idsToString() <<": Rectangle at " << rect->descToString() << std::endl;
	}
}

/*
 * Print out intersection rectangles
 */
void RectangleSystemProcessor::printIntersections() const {
	for (auto& rect: m_intersections) {
		std::cout << "\tBetween rectangle " << rect->idsToString() <<" at " << rect->descToString() << std::endl;
	}
}


/*****************************************************************************/
/*                           Functional methods                              */
/*****************************************************************************/
/*
 * Read rectangles from json file. If system already contains rectangles, they
 * will be replaced with new set of rectangles. If method fails to read
 * rectangles from file - rectangles system will be empty
 * @parameter filePath - path to json file with rectangles description
 *                       Required file format example:
 * [
 *   {
 *    "rects": [
 *        {"x": 100, "y": 100, "w": 500, "h": 500 },
 *        {"x": 120, "y": 120, "w": 400, "h": 400 }
 *    ]
 *   }
 * ]
 * @return - true if at least one rectangle was successfully read from file
 */
bool RectangleSystemProcessor::fillSystem(const std::string& jsonFilePath) {
	m_inputRects.clear();
	m_intersections.clear();

	try {
		RectangleFactory::generateRectangles(jsonFilePath, m_inputRects);
	} catch (const std::invalid_argument& e) {
		std::cerr << "ERROR: failed to read rectangles from \"" << jsonFilePath << "\"" << std::endl;
		std::cerr << e.what() << std::endl;

		m_inputRects.clear();
	}
	return !m_inputRects.empty();
}

/*
 * Check whether rectangle system is empty.
 * System is empty if it wasn't initted or filled with rectangles
 * @return - true if system contains rectangles
 */
bool RectangleSystemProcessor::isEmpty() const {
	return m_inputRects.empty();
}

/*
 * Find intersection between all original rectangles
 * @algorithm - take copy  of original rectangles (do not damage origin
 *              rectangles order). Find intersections between each pare of
 *              rectangles and repeat the same for each pare of found
 *              rectangles
 */
const RectDescrList& RectangleSystemProcessor::findIntersections() {
	cleaupIntersections();

	copyToBuffer(m_inputRects, 0);

	bool intersectionExists = true;
	while (intersectionExists) {
		int startIndex = m_intersections.size();

		sortBuffer();
		intersectionExists = generateIntersections(m_buffer);
		copyToBuffer(m_intersections, startIndex);
	}

	return m_intersections;
}


/*****************************************************************************/
/*                             PRIVATE METHODS                               */
/*****************************************************************************/
/*
 * Cleanup rectangles intersections
 */
void RectangleSystemProcessor::cleaupIntersections(){
	m_intersections.clear();
}

/*
 * Cleanup rectangles buffer
 */
void RectangleSystemProcessor::cleanupBuffer() {
	m_buffer.clear();
}

/*
 * Copy rectangles to buffer
 */
void RectangleSystemProcessor::copyToBuffer(const RectDescrList& rects, int startIndex) {
	cleanupBuffer();
	m_buffer.insert(m_buffer.begin(), rects.begin() + startIndex, rects.end());
}

/*
 * Sort rectangles in buffer based by rectangles
 */
void RectangleSystemProcessor::sortBuffer() {
    if (m_buffer.size() > 0) {
    	std::sort(m_buffer.begin(), m_buffer.end(),
    			[](const Rectangle2DPtr& rect1, const Rectangle2DPtr& rect2)
    			{return *rect1 < *rect2;});
    }
}

/*
 * Generate intersections between rectangles
 * @parameter rects - rectangles for which intersections have to be found
 */
bool RectangleSystemProcessor::generateIntersections(const RectDescrList& rects) {
	bool intersectionFound = false;
	for (auto cRectMainIt = rects.begin(); cRectMainIt != rects.end(); ++cRectMainIt) {
		for (auto cRectCompareIt = std::next(cRectMainIt); cRectCompareIt != rects.end(); ++cRectCompareIt) {
			//check whether intersection already exists
			RectIndexes newIntersectionId;
			newIntersectionId.insert((*cRectMainIt)->getIds().begin(), (*cRectMainIt)->getIds().end());
			newIntersectionId.insert((*cRectCompareIt)->getIds().begin(), (*cRectCompareIt)->getIds().end());

			auto foundIt = std::find_if(m_intersections.begin(), m_intersections.end(),
					[&newIntersectionId](const Rectangle2DPtr& rectDescPtr)->bool
					    {return rectDescPtr->getIds() == newIntersectionId;});
			if (foundIt != m_intersections.end()) {
				continue;
			}

			// intersection doesn't exists, so check where they really intersect
			// if yes - add to intersections
			if ((*cRectMainIt)->intersectWith(*(*cRectCompareIt))) {
				Rectangle2D intersection = (*cRectMainIt)->getIntersection(*(*cRectCompareIt));
				if (intersection.isValid()) { // insert only valid intersections
					Rectangle2DPtr intersectionPtr = std::make_shared<Rectangle2D>(intersection);
					m_intersections.emplace_back(intersectionPtr);
					intersectionFound = true;
				}
			}
		}
	}

	return intersectionFound;
}
