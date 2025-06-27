#include "BuildCar.h"

void CarBuilder::printQustionForCurStep() {

}

bool CarBuilder::AssembleCar(CarType type, Engine engine,brakeSystem brake, SteeringSystem steering) {
	if (!IsValidParameters(type, engine, brake, steering)) return false;
    if (!IsValidItemSet(type, engine, brake, steering)) return false;


}
bool CarBuilder::IsValidItemSet(CarType type, Engine engine,
	brakeSystem brake, SteeringSystem steering) {
    if (type == SEDAN && brake == CONTINENTAL)
    {
        return false;
    }
    else if (type == SUV && engine == TOYOTA)
    {
        return false;
    }
    else if (type == TRUCK && engine == WIA)
    {
        return false;
    }
    else if (type == TRUCK && brake == MANDO)
    {
        return false;
    }
    else if (brake == BOSCH_B && steering != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

bool CarBuilder::IsValidParameters(
	CarType type, Engine engine,
	brakeSystem brake, SteeringSystem steering) {
	return IsValidType(type)
		&& IsValidEngine(engine)
		&& IsValidBrekeSystem(brake)
		&& IsValidSteeringSystem(steering);
	
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