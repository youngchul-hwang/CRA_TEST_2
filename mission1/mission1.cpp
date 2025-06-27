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
    "ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n",
    "ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n",
    "ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n",
    "ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n",
    "ERROR :: Run 또는 Test 중 하나를 선택 필요\n"
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
            std::cout << "바이바이\n";
            break;
        }
        
        if (!isNumber(userAnswer)) {
            std::cout << "ERROR :: 숫자만 입력 가능\n";
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
    std::cout << "차량 타입으로 " << CarName[carType] << "을 선택하셨습니다.\n";
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    int enginType = stack[Engine_Q];
    std::cout << EnginName[enginType] <<" 엔진을 선택하셨습니다.\n";

}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    int breakSystemType = stack[brakeSystem_Q];
    std::cout << "Brake System : " << BrakeSystemName[breakSystemType] << std::endl;
    std::cout << BrakeSystemName[breakSystemType] << "  제동장치를 선택하셨습니다.\n";
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    int steeringSystemType = stack[SteeringSystem_Q];
    std::cout << SteeringSystemName[steeringSystemType] << "조향장치를 선택하셨습니다.\n";
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
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == BROKEN)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            printSeletedItems();
            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
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
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void printfEngintTypeOptions(void) {
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void printBreakSystemOptions() {
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void printSteeringSystemOptions() {
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void printRunTestOptions() {
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
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