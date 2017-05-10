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
		Nitro::RectangleSystemProcessor rectSystem("testFiles/input.json");
		if (rectSystem.isEmpty()) {
			std::cerr << "No rectangles found" << std::endl;
			return 1;
		}

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
/*#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
	return 0;
}*/
