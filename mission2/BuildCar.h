#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

#define CLEAR_SCREEN "\033[H\033[2J"

enum QuestionType
{
    CarType_Q = 0,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};
const std::vector<std::string> CarName = {
    "NONE", "SEDAN", "SUV", "TRUCK"
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN
};
const std::vector<std::string> EnginName = {
    "NONE", "GM", "WIA", "BROKEN"
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};
const std::vector<std::string> BrakeSystemName = {
    "NONE", "MANDO", "CONTINENTAL", "BOSCH_B"
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};
const std::vector<std::string> SteeringSystemName = {
    "NONE", "BOSCH_S", "MOBIS"
};

const std::vector< std::string> errorMessageForInvalidAnswer = {
"ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n",
"ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n",
"ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n",
"ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n",
"ERROR :: Run 또는 Test 중 하나를 선택 필요\n"
};

class CarBuilder {
public:
	CarBuilder() = default;
	~CarBuilder() = default;

    void printQustionForCurStep();

	bool AssembleCar(
		CarType type, Engine engine, 
		brakeSystem brake, SteeringSystem steering);

private:
	bool IsValidParameters(
		CarType type, Engine engine,
		brakeSystem brake, SteeringSystem steering);
	bool IsValidItemSet(CarType type, Engine engine,
		brakeSystem brake, SteeringSystem steering);

	bool IsValidType(CarType type);
	bool IsValidEngine(Engine engine);
	bool IsValidBrekeSystem(brakeSystem brake);
	bool IsValidSteeringSystem(SteeringSystem steering);

    void printCarTypeOptions(void);
    void printfEngintTypeOptions(void);
    void printBreakSystemOptions(void);
    void printSteeringSystemOptions(void);
    void printRunTestOptions(void);

private:
    int step;

private:



};
