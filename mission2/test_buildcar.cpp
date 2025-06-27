#include "gmock/gmock.h"
#include "BuildCar.h"

TEST(GroupBuildCar, TC_PrintAllCase) {
	CarBuilder carBuilder;

	int curStep = 0;
	int userAnswer = 1;

	curStep = carBuilder.printQustionForCurStep();
	EXPECT_EQ(CarType_Q, curStep);

	
	carBuilder.processCarAssembleStep(userAnswer);
	curStep = carBuilder.printQustionForCurStep();
	EXPECT_EQ(Engine_Q, curStep);

	carBuilder.processCarAssembleStep(userAnswer);
	curStep = carBuilder.printQustionForCurStep();
	EXPECT_EQ(brakeSystem_Q, curStep);

	carBuilder.processCarAssembleStep(userAnswer);
	curStep = carBuilder.printQustionForCurStep();
	EXPECT_EQ(SteeringSystem_Q, curStep);

	carBuilder.processCarAssembleStep(userAnswer);
	curStep = carBuilder.printQustionForCurStep();
	EXPECT_EQ(Run_Test, curStep);
}

TEST(GroupBuildCar, TC_ValidInputCase) {
	CarBuilder carBuilder;

	int curStep = CarType_Q;
	int userAnswer = 1;

	bool isValid = false;

	carBuilder.SetCurProcess(CarType_Q);
	isValid = carBuilder.isValidAnswer(1);
	EXPECT_EQ(true, isValid);
	isValid = carBuilder.isValidAnswer(3);
	EXPECT_EQ(true, isValid);

	carBuilder.SetCurProcess(Engine_Q);
	isValid = carBuilder.isValidAnswer(0);
	EXPECT_EQ(true, isValid);
	isValid = carBuilder.isValidAnswer(4);
	EXPECT_EQ(true, isValid);

	carBuilder.SetCurProcess(brakeSystem_Q);
	isValid = carBuilder.isValidAnswer(0);
	EXPECT_EQ(true, isValid);
	isValid = carBuilder.isValidAnswer(3);
	EXPECT_EQ(true, isValid);

	carBuilder.SetCurProcess(SteeringSystem_Q);
	isValid = carBuilder.isValidAnswer(0);
	EXPECT_EQ(true, isValid);
	isValid = carBuilder.isValidAnswer(2);
	EXPECT_EQ(true, isValid);

	carBuilder.SetCurProcess(Run_Test);
	isValid = carBuilder.isValidAnswer(0);
	EXPECT_EQ(true, isValid);
	isValid = carBuilder.isValidAnswer(2);
	EXPECT_EQ(true, isValid);
}


TEST(GroupBuildCar, TC_InvalidInputCase) {
	CarBuilder carBuilder;

	int curStep = 0;
	int userAnswer = 1;

	bool isValid = false;
	carBuilder.SetCurProcess(CarType_Q);
	isValid = carBuilder.isValidAnswer(4);
	EXPECT_EQ(false, isValid);

	carBuilder.SetCurProcess(Engine_Q);
	isValid = carBuilder.isValidAnswer(5);
	EXPECT_EQ(false, isValid);

	carBuilder.SetCurProcess(brakeSystem_Q);
	isValid = carBuilder.isValidAnswer(4);
	EXPECT_EQ(false, isValid);

	carBuilder.SetCurProcess(SteeringSystem_Q);
	isValid = carBuilder.isValidAnswer(3);
	EXPECT_EQ(false, isValid);

	carBuilder.SetCurProcess(Run_Test);
	isValid = carBuilder.isValidAnswer(3);
	EXPECT_EQ(false, isValid);

}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep1) {
	CarBuilder carBuilder;

	ProcessStep preStep = Run_Test;
	int userAnswer = 0;

	carBuilder.SetCurProcess(preStep);
	carBuilder.processCarAssembleStep(0);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(CarType_Q, curStep);

}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep2) {
	CarBuilder carBuilder;

	int userAnswer = 0;

	carBuilder.SetCurProcess(brakeSystem_Q);
	int preStep = carBuilder.GetCurProcess();
	carBuilder.processCarAssembleStep(0);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(preStep-1, curStep);

}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_RunTest1) {
	CarBuilder carBuilder;

	int userAnswer = 1;

	carBuilder.SetCurProcess(Run_Test);
	carBuilder.processCarAssembleStep(userAnswer);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(Run_Test, curStep);

}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_RunTest2) {
	CarBuilder carBuilder;

	int userAnswer = 2;

	carBuilder.SetCurProcess(Run_Test);
	int preStep = carBuilder.GetCurProcess();
	carBuilder.processCarAssembleStep(userAnswer);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(Run_Test, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_NormalCase) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(SEDAN);
	carBuilder.processCarAssembleStep(GM);
	carBuilder.processCarAssembleStep(MANDO);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(Run_Test, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_ErrorCase1) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(SEDAN);
	carBuilder.processCarAssembleStep(GM);
	carBuilder.processCarAssembleStep(CONTINENTAL);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_ErrorCase2) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(SUV);
	carBuilder.processCarAssembleStep(TOYOTA);
	carBuilder.processCarAssembleStep(CONTINENTAL);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_ErrorCase3) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(TRUCK);
	carBuilder.processCarAssembleStep(WIA);
	carBuilder.processCarAssembleStep(CONTINENTAL);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_ErrorCase4) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(TRUCK);
	carBuilder.processCarAssembleStep(TOYOTA);
	carBuilder.processCarAssembleStep(MANDO);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_ErrorCase5) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(TRUCK);
	carBuilder.processCarAssembleStep(TOYOTA);
	carBuilder.processCarAssembleStep(BOSCH_B);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_runProducedCar_ErrorCase6) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(SEDAN);
	carBuilder.processCarAssembleStep(BROKEN);
	carBuilder.processCarAssembleStep(MANDO);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Run);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_testProducedCar1) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(SEDAN);
	carBuilder.processCarAssembleStep(GM);
	carBuilder.processCarAssembleStep(CONTINENTAL);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Test);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}

TEST(GroupBuildCar, TC_ProcessCarAssembleStep_testProducedCar2) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(SUV);
	carBuilder.processCarAssembleStep(TOYOTA);
	carBuilder.processCarAssembleStep(MANDO);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Test);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}
TEST(GroupBuildCar, TC_ProcessCarAssembleStep_testProducedCar3) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(TRUCK);
	carBuilder.processCarAssembleStep(WIA);
	carBuilder.processCarAssembleStep(MANDO);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Test);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}
TEST(GroupBuildCar, TC_ProcessCarAssembleStep_testProducedCar4) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(TRUCK);
	carBuilder.processCarAssembleStep(GM);
	carBuilder.processCarAssembleStep(BOSCH_B);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Test);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}
TEST(GroupBuildCar, TC_ProcessCarAssembleStep_testProducedCar5) {
	CarBuilder carBuilder;

	carBuilder.processCarAssembleStep(TRUCK);
	carBuilder.processCarAssembleStep(GM);
	carBuilder.processCarAssembleStep(MANDO);
	carBuilder.processCarAssembleStep(MOBIS);
	carBuilder.processCarAssembleStep(Do_Test);
	int curStep = carBuilder.GetCurProcess();
	EXPECT_EQ(ProcessStepInvalid, curStep);
}