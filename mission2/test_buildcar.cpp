#include "gmock/gmock.h"
#include "BuildCar.h"

TEST(GroupBuildCar, TC1) {
	CarBuilder carBuilder;

	carBuilder.printQustionForCurStep();

	EXPECT_EQ(30, 30);
}