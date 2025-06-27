#if 1
#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

#include "mission2/BuildCar.h"

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);


std::string getUserAnswer();
bool isExit(std::string userInput);
bool isNumber(std::string str);
bool isValidAnswer(int step, int answer);
void printErrorMessage(int step);
int processCarAssembleStep(int step, int answer);

void printSeletedItems();


void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 2500; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int main()
{
    CarBuilder carBuilder;
    int step;

    while (1)
    {
        carBuilder.printQustionForCurStep();
        std::string userAnswer = getUserAnswer();

        if (isExit(userAnswer)) {
            std::cout << "���̹���\n";
            break;
        }

        if (!isNumber(userAnswer)) {
            std::cout << "ERROR :: ���ڸ� �Է� ����\n";
            delay(800);
            continue;
        }

        int answer = stoi(userAnswer);

        if (!isValidAnswer(step, answer)) {
            printErrorMessage(step);
            delay(800);
            continue;
        }

        step = processCarAssembleStep(step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    int carType = stack[CarType_Q];
    std::cout << "���� Ÿ������ " << CarName[carType] << "�� �����ϼ̽��ϴ�.\n";
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    int enginType = stack[Engine_Q];
    std::cout << EnginName[enginType] << " ������ �����ϼ̽��ϴ�.\n";

}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    int breakSystemType = stack[brakeSystem_Q];
    std::cout << "Brake System : " << BrakeSystemName[breakSystemType] << std::endl;
    std::cout << BrakeSystemName[breakSystemType] << "  ������ġ�� �����ϼ̽��ϴ�.\n";
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    int steeringSystemType = stack[SteeringSystem_Q];
    std::cout << SteeringSystemName[steeringSystemType] << "������ġ�� �����ϼ̽��ϴ�.\n";
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void printSeletedItems()
{
    int carType = stack[CarType_Q];
    std::cout << "Car Type : " << CarName[carType] << std::endl;

    int enginType = stack[Engine_Q];
    std::cout << "Engine : " << EnginName[enginType] << std::endl;

    int breakSystemType = stack[brakeSystem_Q];
    std::cout << "Brake System : " << BrakeSystemName[breakSystemType] << std::endl;

    int steeringSystemType = stack[SteeringSystem_Q];
    std::cout << "SteeringSystem : " << SteeringSystemName[steeringSystemType] << std::endl;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == BROKEN)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            printSeletedItems();
            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}




std::string getUserAnswer() {
    std::cout << "===============================\n";
    std::cout << ("INPUT > ");

    std::string userInput;
    std::cin >> userInput;

    return userInput;
}

bool isExit(std::string userInput) {
    return userInput == "exit";
}

bool isNumber(std::string str) {
    if (str.empty()) return false;

    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isValidAnswer(int step, int answer) {
    if (step == CarType_Q && (answer >= 1 && answer <= 3)) return true;
    if (step == Engine_Q && (answer >= 0 && answer <= 4)) return true;
    if (step == brakeSystem_Q && (answer >= 0 && answer <= 3)) return true;
    if (step == SteeringSystem_Q && (answer >= 0 && answer <= 2)) return true;
    if (step == Run_Test && (answer >= 0 && answer <= 2)) return true;
}

void printErrorMessage(int step) {
    std::cout << errorMessageForInvalidAnswer[step];
}

int processCarAssembleStep(int step, int answer) {
    int nextStep = step;
    if (answer == 0 && step == Run_Test)
    {
        nextStep = CarType_Q;
    }
    else if (answer == 0 && step >= 1)
    {
        nextStep -= 1;
    }
    else if (step == CarType_Q)
    {
        selectCarType(answer);
        delay(800);
        nextStep = Engine_Q;
    }
    else if (step == Engine_Q)
    {
        selectEngine(answer);
        delay(800);
        nextStep = brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
    {
        selectbrakeSystem(answer);
        delay(800);
        nextStep = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(answer);
        delay(800);
        nextStep = Run_Test;
    }
    else if (step == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }

    return nextStep;
}


#endif
#endif