#include "BuildCar.h"

void CarBuilder::processCarAssembleStep(int answer) {
    if (answer == 0 && step == Run_Test)
    {
        step = CarType_Q;
    }
    else if (answer == 0 && step >= 1)
    {
        step -= 1;
    }
    else if (step == CarType_Q)
    {
        selectCarType(answer);
        delay(800);
        step = Engine_Q;
    }
    else if (step == Engine_Q)
    {
        selectEngine(answer);
        delay(800);
        step = brakeSystem_Q;
    }
    else if (step == brakeSystem_Q)
    {
        selectbrakeSystem(answer);
        delay(800);
        step = SteeringSystem_Q;
    }
    else if (step == SteeringSystem_Q)
    {
        selectSteeringSystem(answer);
        delay(800);
        step = Run_Test;
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
}

void CarBuilder::selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    int carType = stack[CarType_Q];
    std::cout << "���� Ÿ������ " << CarName[carType] << "�� �����ϼ̽��ϴ�.\n";
}

void CarBuilder::selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    int enginType = stack[Engine_Q];
    std::cout << EnginName[enginType] << " ������ �����ϼ̽��ϴ�.\n";

}

void CarBuilder::selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    int breakSystemType = stack[brakeSystem_Q];
    std::cout << BrakeSystemName[breakSystemType] << "  ������ġ�� �����ϼ̽��ϴ�.\n";
}

void CarBuilder::selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    int steeringSystemType = stack[SteeringSystem_Q];
    std::cout << SteeringSystemName[steeringSystemType] << "������ġ�� �����ϼ̽��ϴ�.\n";
}

void CarBuilder::runProducedCar()
{
    if (isValidCheck() == false)
    {
        step = ProcessStep::ProcessStepInvalid;
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == BROKEN)
        {
            step = ProcessStep::ProcessStepInvalid;
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

bool CarBuilder::isValidCheck()
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

void CarBuilder::printSeletedItems()
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

void CarBuilder::testProducedCar()
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

int CarBuilder::printQustionForCurStep() {
    if (step == CarType_Q) printCarTypeOptions();
    else if (step == Engine_Q) printfEngintTypeOptions();
    else if (step == brakeSystem_Q) printBreakSystemOptions();
    else if (step == SteeringSystem_Q) printSteeringSystemOptions();
    else if (step == Run_Test) printRunTestOptions();

    return step;
}

bool CarBuilder::IsValidType(CarType type) {
	return (type >= 1 && type <= 3);
}
bool CarBuilder::IsValidEngine(Engine engine) {
	return (engine >= 0 && engine <= 4);
}
bool CarBuilder::IsValidBrekeSystem(brakeSystem brake) {
	return (brake >= 0 && brake <= 3);
}
bool CarBuilder::IsValidSteeringSystem(SteeringSystem steering) {
	return (steering >= 0 && steering <= 2);
}

bool CarBuilder::isValidAnswer(int answer) {
    bool valid = false;

    if (step == CarType_Q && (answer >= 1 && answer <= 3)) valid = true;
    if (step == Engine_Q && (answer >= 0 && answer <= 4)) valid = true;
    if (step == brakeSystem_Q && (answer >= 0 && answer <= 3)) valid = true;
    if (step == SteeringSystem_Q && (answer >= 0 && answer <= 2)) valid = true;
    if (step == Run_Test && (answer >= 0 && answer <= 2)) valid = true;

    if (!valid) {
        printErrorMessage();
    }

    return valid;
}

void CarBuilder::printErrorMessage() {
    if( step < errorMessageForInvalidAnswer.size())
        std::cout << errorMessageForInvalidAnswer[step];
    delay(800);
}

void CarBuilder::printCarTypeOptions(void) {
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

void CarBuilder::printfEngintTypeOptions(void) {
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}

void CarBuilder::printBreakSystemOptions() {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void CarBuilder::printSteeringSystemOptions() {
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void CarBuilder::printRunTestOptions() {
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}


void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}