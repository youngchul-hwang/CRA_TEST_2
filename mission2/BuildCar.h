#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

#define CLEAR_SCREEN "\033[H\033[2J"

enum ProcessStep
{
    CarType_Q = 1,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
    ProcessStepInvalid
 };

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK,
    CarTypeCount
};
const std::vector<std::string> CarName = {
    "NONE", "SEDAN", "SUV", "TRUCK"
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN,
    EnginCount
};
const std::vector<std::string> EnginName = {
    "NONE", "GM", "WIA", "BROKEN"
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    brakeSystemCount
};
const std::vector<std::string> BrakeSystemName = {
    "NONE", "MANDO", "CONTINENTAL", "BOSCH_B"
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    SteeringSystemCount

};
const std::vector<std::string> SteeringSystemName = {
    "NONE", "BOSCH_S", "MOBIS"
};

enum RunTestOPtion
{
    Do_Run = 1,
    Do_Test
};

const std::vector< std::string> errorMessageForInvalidAnswer = {
    "ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n",
    "ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n",
    "ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n",
    "ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n",
    "ERROR :: Run 또는 Test 중 하나를 선택 필요\n"
};

void delay(int ms);

class CarBuilder {
public:
    CarBuilder() : step{ CarType_Q }, stack{ 0, } {};
	~CarBuilder() = default;

    int printQustionForCurStep();
    bool isValidAnswer(int answer);
    void processCarAssembleStep(int answer);

    void SetCurProcess(ProcessStep step_) { step = step_; }
    int GetCurProcess() { return step; }

private:
	bool IsValidType(CarType type);
	bool IsValidEngine(Engine engine);
	bool IsValidBrekeSystem(brakeSystem brake);
	bool IsValidSteeringSystem(SteeringSystem steering);
    bool isValidCheck();

    void printCarTypeOptions(void);
    void printfEngintTypeOptions(void);
    void printBreakSystemOptions(void);
    void printSteeringSystemOptions(void);
    void printRunTestOptions(void);

    void selectCarType(int answer);
    void selectEngine(int answer);
    void selectbrakeSystem(int answer);
    void selectSteeringSystem(int answer);

    void runProducedCar();
    void testProducedCar();
   
    void printSeletedItems();
    void printErrorMessage();

private:
    int step;
    int stack[10];

private:

};
