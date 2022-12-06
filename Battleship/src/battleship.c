#include "../include/battleship.h"
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#ifdef HARDWARE
#include "../include/io_hw.h"
#else
#include "../include/io.h"
#endif

void setupShips(void);

//set the vessels to 5 of them
static struct Vessel vessels[5];

int main()
{
	//set startGame to true, meaning that the game is going
	bool startGame = true;
	
	//call all the congiration functions
	powerPeripherals();
	configureIO();
	
	//call the setupShips to setup all the ships for the field
	setupShips();
	
	//input it for the coords to go into
	int input = 0;
	//the xCord refers to the value of the column
	int xCord = 0;
	//the yCord refers to the value of the row
	int yCord = 0;
	bool hit = false;
	
	//turn on green LED on the NUCLEO board 
	GPIOA->ODR |= GPIO_ODR_ODR5;
	//while the game is going, keep repeating the inputs. 
	while(startGame)
	{
		//set the hit to false each time it goes through the loop
		hit = false; 
		
		//displays the following E (enter) R (row)
		displayFourteen();
		delay();
		displayR();
		delay();
		while(acceptInput())
		{
			//get the input for row
			input = segmentDisplay();
		}
		//insert the input from the seven segment display into the yCord (column)
		yCord = input;
		displayBlank();
		delay();
		
		//displays the following E (enter) C (column)
		displayFourteen();
		delay();
		displayTwelve();
		delay();
		while(acceptInput())
		{
			//get the input for column
			input = segmentDisplay();
		}
		//insert the input from the seven segment display into the xCord (row)
		xCord = input;
		displayBlank();
		delay();

		//for loop to go through all the vessels
		for(int x = 0; x < 5; x++)
		{
			//for loop to go through all the vessel locations
			for(int y = 0; y < 5; y++)
			{
				//if the vessel[x].vesselLocations[y]'s row is equal to yCord AND vessel[x].vesselLocations[y]'s column is equal to xCord
				if(vessels[x].vesselLocations[y].r == yCord && vessels[x].vesselLocations[y].c == xCord)
				{
					//set hit to true
					hit = true;
					//set the vessel[x].hits[y] to true
					vessels[x].hits[y] = true;
					//display that the ship has been hit
					displayHit();
					//delay it
					delay();
					
					//if all the hits on vessel[x] are true, then THAT vessel is sunk
					if(vessels[x].hits[0] == true && vessels[x].hits[1] == true && vessels[x].hits[2] == true && vessels[x].hits[3] == true && vessels[x].hits[4] == true)
					{
						//set that certain vessel's sunk bool to true
						vessels[x].sunk = true;
						//display 5 to show that it has sunk
						displayFive();
						//delay it
						delay();
					}
					
					//if all the vessels in the game have been sunk, set startGame to false which means GAME OVER
					if(vessels[0].sunk == true && vessels[1].sunk == true && vessels[2].sunk == true && vessels[3].sunk == true && /*(*/vessels[4].sunk == true)
					{
						startGame = false;
						//turn off the green LED on the NUCLEO board, meaning that the game is off
						GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR5;
						//display the first G in GG
						displayG();
						//delay 
						delay();
						//display a blank segment display 
						displayBlank();
						//delay the second display
						delay();
						//display the second G in GG
						displayG();
						//delay and then blank.
						delay();
						displayBlank();
					}
					//break the loop
					break;
				}
			}
		}	
		//if the hit was false, then display a "No hit"
		if(hit == false)
		{
			//display the miss
			displayMiss();
			delay();
		}
	}
	return 0;
}

void setupShips(void)
{
	//initialises all the Vessles from the 1990 version of Battleship
	strcpy(vessels[0].name, "Carrier");
	vessels[0].sunk = false;
	vessels[0].length = 5;
	vessels[0].vesselLocations[0].c = 2;
	vessels[0].vesselLocations[0].r = 5;
	vessels[0].vesselLocations[1].c = 2;
	vessels[0].vesselLocations[1].r = 6;
	vessels[0].vesselLocations[2].c = 2;
	vessels[0].vesselLocations[2].r = 7;
	vessels[0].vesselLocations[3].c = 2;
	vessels[0].vesselLocations[3].r = 8;
	vessels[0].vesselLocations[4].c = 2;
	vessels[0].vesselLocations[4].r = 9;
	vessels[0].hits[0] = false;
	vessels[0].hits[1] = false;
	vessels[0].hits[2] = false;
	vessels[0].hits[3] = false;
	vessels[0].hits[4] = false;
	
	strcpy(vessels[1].name, "Battleship");
	vessels[1].sunk = false;
	vessels[1].length = 4;
	vessels[1].vesselLocations[0].c = 4;
	vessels[1].vesselLocations[0].r = 5;
	vessels[1].vesselLocations[1].c = 5;
	vessels[1].vesselLocations[1].r = 5;
	vessels[1].vesselLocations[2].c = 6;
	vessels[1].vesselLocations[2].r = 5;
	vessels[1].vesselLocations[3].c = 7;
	vessels[1].vesselLocations[3].r = 5;
	vessels[1].vesselLocations[4].c = 11;
	vessels[1].vesselLocations[4].r = 11;
	vessels[1].hits[0] = false;
	vessels[1].hits[1] = false;
	vessels[1].hits[2] = false;
	vessels[1].hits[3] = false;
	vessels[1].hits[4] = true;
	
	strcpy(vessels[2].name, "Cruiser");
	vessels[2].sunk = false;
	vessels[2].length = 3;
	vessels[2].vesselLocations[0].c = 8;
	vessels[2].vesselLocations[0].r = 7;
	vessels[2].vesselLocations[1].c = 8;
	vessels[2].vesselLocations[1].r = 8;
	vessels[2].vesselLocations[2].c = 8;
	vessels[2].vesselLocations[2].r = 9;
	vessels[2].vesselLocations[3].c = 11;
	vessels[2].vesselLocations[3].r = 11;
	vessels[2].vesselLocations[4].c = 11;
	vessels[2].vesselLocations[4].r = 11;
	vessels[2].hits[0] = false;
	vessels[2].hits[1] = false;
	vessels[2].hits[2] = false;
	vessels[2].hits[3] = true;
	vessels[2].hits[4] = true;
	
	strcpy(vessels[3].name, "Submarine");
	vessels[3].sunk = false;
	vessels[3].length = 3;
	vessels[3].vesselLocations[0].c = 5;
	vessels[3].vesselLocations[0].r = 3;
	vessels[3].vesselLocations[1].c = 6;
	vessels[3].vesselLocations[1].r = 3;
	vessels[3].vesselLocations[2].c = 7;
	vessels[3].vesselLocations[2].r = 3;
	vessels[3].vesselLocations[3].c = 11;
	vessels[3].vesselLocations[3].r = 11;
	vessels[3].vesselLocations[4].c = 11;
	vessels[3].vesselLocations[4].r = 11;
	vessels[3].hits[0] = false;
	vessels[3].hits[1] = false;
	vessels[3].hits[2] = false;
	vessels[3].hits[3] = true;
	vessels[3].hits[4] = true;
	
	strcpy(vessels[4].name, "Destroyer");
	vessels[4].sunk = false;
	vessels[4].length = 2;
	vessels[4].vesselLocations[0].c = 2;
	vessels[4].vesselLocations[0].r = 2;
	vessels[4].vesselLocations[1].c = 2;
	vessels[4].vesselLocations[1].r = 3;
	vessels[4].vesselLocations[2].c = 11;
	vessels[4].vesselLocations[2].r = 11;
	vessels[4].vesselLocations[3].c = 11;
	vessels[4].vesselLocations[3].r = 11;
	vessels[4].vesselLocations[4].c = 11;
	vessels[4].vesselLocations[4].r = 11;
	vessels[4].hits[0] = false;
	vessels[4].hits[1] = false;
	vessels[4].hits[2] = true;
	vessels[4].hits[3] = true;
	vessels[4].hits[4] = true;
}
