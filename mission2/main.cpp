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

#include "BuildCar.h"

std::string getUserAnswer();
bool isExit(std::string userInput);
bool isNumber(std::string str);

int main()
{
    CarBuilder carBuilder;
    int step = 0;

    while (1)
    {
        carBuilder.printQustionForCurStep();
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

        if (!carBuilder.isValidAnswer(answer)) {
            continue;
        }

        carBuilder.processCarAssembleStep(answer);
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

#endif
#endif