#include "../include/io_hw.h"
#include "stm32f10x.h"

void displaySea(void)
{
		//Cant display the sea on our hardware
}

void powerPeripherals()
{
	//RCC->APB2ENR |= 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	
	
}

//all the configurations for switches and LEDs
void configureIO()
{
	GPIOA->CRL |=  GPIO_CRL_MODE5_0 |  GPIO_CRL_MODE5_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF5_0 &~ GPIO_CRL_CNF5_1;
	
	GPIOA->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | 			//led a
								GPIO_CRL_MODE1 	 | GPIO_CRL_MODE4   |				//led b and c
								GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1 |				//led d
								GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1;				//led f
	
	GPIOA->CRL &= ~GPIO_CRL_CNF0_0 &~ GPIO_CRL_CNF0_1 
							&~ GPIO_CRL_CNF1   &~ GPIO_CRL_CNF4
							&~ GPIO_CRL_CNF6   &~ GPIO_CRL_CNF7;
	
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;				//led g
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0 &~ GPIO_CRH_CNF9_1;
	
	GPIOB->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | 			//led e
								GPIO_CRL_MODE1   | GPIO_CRL_CNF4_0  |
								GPIO_CRL_CNF6_0  | GPIO_CRL_MODE7;
	
	GPIOB->CRL &= ~GPIO_CRL_CNF0_0 &~ GPIO_CRL_CNF0_1 
							&~ GPIO_CRL_CNF1   &~ GPIO_CRL_MODE4 &~ GPIO_CRL_CNF4_1 &~ GPIO_CRL_CNF6_1 
							&~ GPIO_CRL_MODE6  &~ GPIO_CRL_CNF7;
	
	GPIOB->CRH |=  GPIO_CRH_CNF8_0 | GPIO_CRH_CNF8_0;
	GPIOB->CRH &= ~GPIO_CRH_MODE8 &~ GPIO_CRH_CNF8_1 &~ GPIO_CRH_MODE9 &~ GPIO_CRH_CNF9_1;
	
	GPIOC->CRH 	|= GPIO_CRH_CNF13_0;
	GPIOC->CRH &= ~GPIO_CRH_CNF13_1;
	
}

//function for the delay between each display
void delay()
{
	unsigned volatile int c, d;
   
   for (c = 1; c <= 3000; c++)
	{
		for (d = 1; d <= 3000; d++)
       {
			 }
	}
}

//a boolean function to check if the first switch has been flicked on or not
bool switchFlicked1()
{ 
	bool on = false; 
		int temp = (GPIOB->IDR & 0x00000010);
    if(temp == 0x00000010)
    {
			on = true; 
    }
    else
    {
			on = false; 
		}
		return on;
}

//a boolean function to check if the second switch has been flicked on or not
bool switchFlicked2()
{
	bool on = false; 
	int temp = (GPIOB->IDR & 0x00000040);
	if(temp == 0x00000040)
	{
		on = true;
	}
	else
	{
		on = false; 
	}
	return on;
}

//a boolean function to check if the third switch has been flicked on or not
bool switchFlicked3()
{
	bool on = false; 
	int temp = (GPIOB->IDR & 0x00000200);
	if(temp == 0x00000200)
	{
		on = true;
	}
	else
	{
		on = false; 
	}
	return on;
}

//a boolean function to check if the fourth switch has been flicked on or not
bool switchFlicked4()
{
	bool on = false; 
	int temp = (GPIOB->IDR & 0x00000100);
	if(temp == 0x00000100)
	{
		on = true;
	}
	else
	{
		on = false; 
	}
	return on;
}

//a boolean function to check if the blue USER button on the NUCLEO board has been pressed or not
bool acceptInput()
{
	bool accept = false; 
	int temp = (GPIOC->IDR & 0x00002000);
	if(temp == 0x00002000)
	{
		accept = true;
	}
	else
	{
		accept = false; 
	}
	return accept;
}

//the following is what displays and returns the respective number on the Seven Segment Display
int segmentDisplay()
{
	int number = 0;
    if(switchFlicked1() == true && switchFlicked2() == false && switchFlicked3() == false && switchFlicked4() == false) //1
    {
			displayOne();
			number = 1;
			return number;
    }
		else if(switchFlicked1() == false && switchFlicked2() == true && switchFlicked3() == false && switchFlicked4() == false) //2
		{
			displayTwo();
			number = 2;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == true && switchFlicked3() == false && switchFlicked4() == false) //3
		{
			displayThree();
			number = 3;
			return number;
		}
		else if(switchFlicked1() == false && switchFlicked2() == false && switchFlicked3() == true && switchFlicked4() == false) //4
		{
			displayFour();
			number = 4;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == false && switchFlicked3() == true && switchFlicked4() == false) //5
		{
			displayFive();
			number = 5;
			return number;
		}
		else if(switchFlicked1() == false && switchFlicked2() == true && switchFlicked3() == true && switchFlicked4() == false) //6
		{
			displaySix();
			number = 6;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == true && switchFlicked3() == true && switchFlicked4() == false) //7
		{
			displaySeven();
			number = 7;
			return number;
		}
		else if(switchFlicked1() == false && switchFlicked2() == false && switchFlicked3() == false && switchFlicked4() == true) //8
		{
			displayEight();
			number = 8;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == false && switchFlicked3() == false && switchFlicked4() == true) //9
		{
			displayNine();
			number = 9;
			return number;
		}
		else if(switchFlicked1() == false && switchFlicked2() == true && switchFlicked3() == false && switchFlicked4() == true)//10
		{
			displayTen();
			number = 10;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == true && switchFlicked3() == false && switchFlicked4() == true)//11
		{
			displayEleven();
			number = 11;
			return number;
		}
		else if(switchFlicked1() == false && switchFlicked2() == false && switchFlicked3() == true && switchFlicked4() == true)//12
		{
			displayTwelve();
			number = 12;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == false && switchFlicked3() == true && switchFlicked4() == true)//13
		{
			displayThirteen();
			number = 13;
			return number;
		}
		else if(switchFlicked1() == false && switchFlicked2() == true && switchFlicked3() == true && switchFlicked4() == true)//14
		{
			displayFourteen();
			number = 14;
			return number;
		}
		else if(switchFlicked1() == true && switchFlicked2() == true && switchFlicked3() == true && switchFlicked4() == true)//15
		{
			displayFifteen();
			number = 15;
			return number;
		}
    else	//0
    {
			displayZero();
			number = 0;
			return number;
    }
}

//below are the functions to display each number from 0 to 15
void displayZero(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(false);
}

void displayOne(void)
{
	TurnAOn(false);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(false);
	TurnFOn(false);
	TurnGOn(false);
}

void displayTwo(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(false);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(false);
	TurnGOn(true);
}

void displayThree(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(false);
	TurnFOn(false);
	TurnGOn(true);
}

void displayFour(void)
{
	TurnAOn(false);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(false);
	TurnFOn(true);
	TurnGOn(true);
}

void displayFive(void)
{
	TurnAOn(true);
	TurnBOn(false);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(false);
	TurnFOn(true);
	TurnGOn(true);
}

void displaySix(void)
{
	TurnAOn(true);
	TurnBOn(false);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}

void displaySeven(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(false);
	TurnFOn(false);
	TurnGOn(false);
}

void displayEight(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}

void displayNine(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(false);
	TurnFOn(true);
	TurnGOn(true);
}

void displayTen(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}

void displayEleven(void)
{
	TurnAOn(false);
	TurnBOn(false);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}

void displayTwelve(void)
{
	TurnAOn(true);
	TurnBOn(false);
	TurnCOn(false);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(false);
}

void displayThirteen(void)
{
	TurnAOn(false);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(false);
	TurnGOn(true);
}

void displayFourteen(void)
{
	TurnAOn(true);
	TurnBOn(false);
	TurnCOn(false);
	TurnDOn(true);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}

void displayFifteen(void)
{
	TurnAOn(true);
	TurnBOn(false);
	TurnCOn(false);
	TurnDOn(false);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}
void displayHit(void)
{
	TurnAOn(false);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(true);
}
void displayBlank(void)
{
	TurnAOn(false);
	TurnBOn(false);
	TurnCOn(false);
	TurnDOn(false);
	TurnEOn(false);
	TurnFOn(false);
	TurnGOn(false);
}
void displayMiss(void)
{
	TurnAOn(false);
	TurnBOn(false);
	TurnCOn(true);
	TurnDOn(false);
	TurnEOn(true);
	TurnFOn(false);
	TurnGOn(true);
}
void displayG(void)
{
	TurnAOn(true);
	TurnBOn(true);
	TurnCOn(true);
	TurnDOn(true);
	TurnEOn(false);
	TurnFOn(true);
	TurnGOn(true);
}
void displayR(void)
{
	TurnAOn(true);
	TurnBOn(false);
	TurnCOn(false);
	TurnDOn(false);
	TurnEOn(true);
	TurnFOn(true);
	TurnGOn(false);
}

//below are all the functions to turn on each light of the Seven Segment Display, from A to G
void TurnAOn(bool on)
{
	if(on == true)
	{
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR0;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_ODR0;
	}
}

void TurnBOn(bool on)
{
	if(on == true)
	{
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR1;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_ODR1;
	}
}

void TurnCOn(bool on)
{
	if(on == true)
	{
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR4;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_ODR4;
	}
}

void TurnDOn(bool on)
{
	if(on == true)
	{
		GPIOB->ODR &= (uint32_t) ~GPIO_ODR_ODR0;
	}
	else
	{
		GPIOB->ODR |= GPIO_ODR_ODR0;
	}
}

void TurnEOn(bool on)
{
	if(on == true)
	{
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR6;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_ODR6;
	}
}

void TurnFOn(bool on)
{
	if(on == true)
	{
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR7;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_ODR7;
	}
}

void TurnGOn(bool on)
{
	if(on == true)
	{
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR9;
	}
	else
	{
		GPIOA->ODR |= GPIO_ODR_ODR9;
	}
}
