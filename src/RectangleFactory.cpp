/*
 * RectangleFactory.cpp
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#include "RectangleFactory.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

std::string RectangleFactory::m_cRestsTag = "rects";
std::vector<std::string> RectangleFactory::m_cRequiredParams = {"x", "y", "w", "h"};

RectangleFactory::RectangleFactory() {
	// TODO Auto-generated constructor stub

}

RectangleFactory::~RectangleFactory() {
	// TODO Auto-generated destructor stub
}


void RectangleFactory::generateRectangles(const std::string& jsonFileName, std::vector<RectDescr>& outputList) {
    using boost::property_tree::ptree;

    try {
        std::ifstream jsonFile(jsonFileName);
        ptree pt;
    	read_json(jsonFile, pt);

        for (auto & array_element: pt) {
        	auto rects = array_element.second.get_child_optional(m_cRestsTag);
        	if ( !rects ) {
        		throw std::domain_error("ERROR: no '" + m_cRestsTag + "' tag found in json file");
        	}

			for (auto &recParameters: rects.get()) {
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
				try {
					Rectangle2D newRect (x, y, width, height);
					outputList.push_back(RectDescr(std::to_string(outputList.size() + 1), newRect));
				} catch (const std::invalid_argument& e) {
					std::cout << "WARNING: rectangle (" << x << ", " << y << "), w=" << width << ", h=" << height
							<< " will be ignored. Reason: " << e.what() << std::endl;
				}
			}
        }

    } catch (const boost::property_tree::json_parser_error& e) {
		throw std::invalid_argument("ERROR: invalid json. REASON: " + e.message());
	} catch (const boost::property_tree::ptree_bad_data& e) {
		throw std::invalid_argument("ERROR: invalid value for rectangle parameter. Only integer value is acceptable");
	}

}
