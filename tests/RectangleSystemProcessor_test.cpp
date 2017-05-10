/*
 * RectangleSystemProcessor_test.cpp
 *
 *  Created on: 5 May 2017
 *      Author: asavka
 */

#include "gtest/gtest.h"
#include "RectangleSystemProcessor.h"

class RectangleSystemProcessorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(RectangleSystemProcessorTest, emptyCase){
	Nitro::RectangleSystemProcessor rectSystem("testFiles/empty.json");

	ASSERT_TRUE(rectSystem.isEmpty());
}


TEST_F(RectangleSystemProcessorTest, inOrderCase){
	Nitro::RectangleSystemProcessor rectSystem("testFiles/input.json");

	auto intersections = rectSystem.findIntersections();
	rectSystem.printIntersections();
	ASSERT_EQ(intersections.size(), 1);

	auto rectPtr = *intersections.begin();
	ASSERT_EQ(*rectPtr, Nitro::Rectangle2D({2,3}, 140, 250, 230, 100));
	ASSERT_NO_THROW();
}

TEST_F(RectangleSystemProcessorTest, complicatedCase){
	Nitro::RectangleSystemProcessor rectSystem("testFiles/complicated.json");

	auto intersections = rectSystem.findIntersections();
	rectSystem.printIntersections();
	ASSERT_EQ(intersections.size(), 5);

	RectDescrList testVector;
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
		(std::initializer_list<unsigned long>{2,3}, 40, 68, 207, 29));
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
		(std::initializer_list<unsigned long>{1,3}, 230, 17, 17, 63));
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
			(std::initializer_list<unsigned long>{1,2}, 230, 68, 67, 12));
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
			(std::initializer_list<unsigned long>{1,5}, 300, -15, 45, 65));
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
				(std::initializer_list<unsigned long>{1,2,3}, 230, 68, 17, 12));

	for  (const auto& rectPtr: intersections) {
		const auto& foundIt = std::find_if(testVector.begin(), testVector.end(),
				[&rectPtr](const Rectangle2DPtr& ptr){return *ptr == *rectPtr;});
		ASSERT_TRUE(foundIt != intersections.end());
	}
	ASSERT_NO_THROW();
}

TEST_F(RectangleSystemProcessorTest, edgeCase){
	Nitro::RectangleSystemProcessor rectSystem("testFiles/edge.json");

	auto intersections = rectSystem.findIntersections();
	rectSystem.printIntersections();
	ASSERT_EQ(intersections.size(), 3);

	RectDescrList testVector;
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
		(std::initializer_list<unsigned long>{3,4}, 40, 40, 10, 10));
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
		(std::initializer_list<unsigned long>{1,4}, 40, 40, 20, 10));
	testVector.emplace_back(std::make_shared<Nitro::Rectangle2D>
			(std::initializer_list<unsigned long>{2,4}, 50, 50, 10, 10));

	for  (const auto& rectPtr: intersections) {
		const auto& foundIt = std::find_if(testVector.begin(), testVector.end(),
				[&rectPtr](const Rectangle2DPtr& ptr){return *ptr == *rectPtr;});
		ASSERT_TRUE(foundIt != intersections.end());
	}
	ASSERT_NO_THROW();
}
