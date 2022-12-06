#include "stdbool.h"

void displaySea(void);

//configuration functions 

void powerPeripherals(void);
void configureIO(void);
void turnOnLED(void);
void delay(void);

//the switch functions

bool switchFlicked1(void);
bool switchFlicked2(void);
bool switchFlicked3(void);
bool switchFlicked4(void);

//accept input function from the blue USER button on the NUCLEO board

bool acceptInput(void);

//all of the functions below make the segment display display things

int segmentDisplay(void);

void TurnAOn(bool);
void TurnBOn(bool);
void TurnCOn(bool);
void TurnDOn(bool);
void TurnEOn(bool);
void TurnFOn(bool);
void TurnGOn(bool);

void displayZero(void);
void displayOne(void);
void displayTwo(void);
void displayThree(void);
void displayFour(void);
void displayFive(void);
void displaySix(void);
void displaySeven(void);
void displayEight(void);
void displayNine(void);
void displayTen(void);
void displayEleven(void);
void displayTwelve(void);
void displayThirteen(void);
void displayFourteen(void);
void displayFifteen(void);

void displayHit(void);
void displayBlank(void);
void displayMiss(void);
void displayG(void);
void displayR(void);
