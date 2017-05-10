/*
 * RectangleFactory.cpp
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#include "RectangleFactory.h"

#include <iostream>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

using Nitro::RectangleFactory;

/*****************************************************************************/
/*                              STATIC PARAMETERS                            */
/*****************************************************************************/
/*
 * m_cRectsTag       - name of tag in json that detects array of rectangles
 *                     descriptions
 * m_cRequiredParams - name of tags that are required to be present in json to
 *                     create rectangle
 * m_cMaxSize        - max number of rectangles that could be read from json
 */
std::string RectangleFactory::m_cRectsTag = "rects";
std::vector<std::string> RectangleFactory::m_cRequiredParams = {"x", "y", "w", "h"};
unsigned int RectangleFactory::m_cMaxSize = 10;


/*****************************************************************************/
/*                    Constructors and destructors                           */
/*****************************************************************************/
RectangleFactory::RectangleFactory() {
}

RectangleFactory::~RectangleFactory() {
}

/*
 * Read rectangles from json file into vector
 * NOTE: this method has side effect - it clean up passed vector before
 * put json rectangles into it
 *
 * @param jsonFileName - path to json file with rectangles
 * @param outputList   - reference to vector where rectangles has to be stored
 * @throws std::invalid_argument exception in cases:
 *    - file doesn't exist
 *    - json format is invalid
 *    - required top level parameter wasn't found
 *    - rectangle parameter is not integer value
 */
void RectangleFactory::generateRectangles(const std::string& jsonFileName,
		                                  RectDescrList& outputList) {
    using boost::property_tree::ptree;

    try {
        std::ifstream jsonFile(jsonFileName);
        ptree pt;
    	read_json(jsonFile, pt);

    	outputList.clear();
    	bool isFull = false;
        for (auto & array_element: pt) {
        	auto rects = array_element.second.get_child_optional(m_cRectsTag);
        	if ( !rects ) {
        		throw std::domain_error("ERROR: no '" + m_cRectsTag + "' tag found in json file");
        	}

			for (auto &recParameters: rects.get()) {
	        	if (outputList.size() >= m_cMaxSize) {
					isFull = true;
					break;
				}

				// validation
				for (auto & parameter: m_cRequiredParams) {
					auto paramValue = recParameters.second.get_child_optional(parameter);
					if ( !paramValue ) {
						std::cout << "WARNING: parameter '" << parameter << "' is missed. This rectangle will be ignored" << std::endl;
						continue;
					}
				}

				int x = recParameters.second.get_child("x").get_value<int>();
				int y = recParameters.second.get_child("y").get_value<int>();
				int width = recParameters.second.get_child("w").get_value<int>();
				int height = recParameters.second.get_child("h").get_value<int>();

				auto newIndexSet = std::initializer_list<unsigned long>{outputList.size() + 1};
				auto newRectPtr = std::make_shared<Rectangle2D>(newIndexSet, x, y, width, height);
				if (newRectPtr->isValid()) {
					outputList.emplace_back(newRectPtr);
				} else {
					std::cout << "WARNING: rectangle (" << x << ", " << y << "), w=" << width << ", h=" << height
												<< " is invalid and will be ignored" << std::endl;
				}
			}

			if (isFull) {
				std::cout << "WARNING: only first " << m_cMaxSize << " rectangles can be processed. Rest of rectangles will be ignored." << std::endl;
				break;
			}
        }

    } catch (const boost::property_tree::json_parser_error& e) {
		throw std::invalid_argument("ERROR: invalid json. REASON: invalid file path or required top level element \"" + m_cRectsTag + "\" not found.");
	} catch (const boost::property_tree::ptree_bad_data& e) {
		throw std::invalid_argument("ERROR: invalid value for rectangle parameter. Only integer value is acceptable");
	}

}
