/*
 * mail.cpp
 *
 *  Created on: 4 May 2017
 *      Author: asavka
 */

#include <iostream>
#include "RectangleSystemProcessor.h"

int main() {
	try {
		RectangleSystemProcessor rectSystem("testFiles/over_max_and_no_intersections.json");
		std::cout << "Input: " << std::endl;
		rectSystem.printInput();

		rectSystem.findIntersections();

		std::cout << "Intersections: " << std::endl;
		rectSystem.printIntersections();
	} catch (const std::exception&  e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
