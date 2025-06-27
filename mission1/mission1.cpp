#if 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

void printCarTypeOptions(void);
void printfEngintTypeOptions(void);
void printBreakSystemOptions(void);
void printSteeringSystemOptions(void);
void printRunTestOptions(void);
void printQustionForCurStep(int step);

std::string getUserAnswer();
bool isExit(std::string userInput);
bool isNumber(std::string str);
bool isValidAnswer(int step, int answer);
void printErrorMessage(int step);
int processCarAssembleStep(int step, int answer);

void printSeletedItems();

const std::vector< std::function<void(void)>> printQuestions = {
    printCarTypeOptions,
    printfEngintTypeOptions,
    printBreakSystemOptions,
    printSteeringSystemOptions,
    printRunTestOptions
};

const std::vector< std::string> errorMessageForInvalidAnswer = {
    "ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n",
    "ERROR :: ������ 1 ~ 4 ������ ���� ����\n",
    "ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n",
    "ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n",
    "ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n"
};

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
    int step = CarType_Q;

    while (1)
    {
        printQustionForCurStep(step);  
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
    std::cout << EnginName[enginType] <<" ������ �����ϼ̽��ϴ�.\n";

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

void printQustionForCurStep(int step) {
    printQuestions[step]();
}

void printCarTypeOptions(void) {
    printf(CLEAR_SCREEN);

    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void printfEngintTypeOptions(void) {
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}

void printBreakSystemOptions() {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void printSteeringSystemOptions() {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void printRunTestOptions() {
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
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