//Thomas Cooper
//3/12/2017
//Module 2 program 3

//preprocessor
#include <stdio.h>
#include <cstdbool>

//function prototypes
void drawMenu();
int isFull(int seatArray[]);
void seating(int firstOrEcon, int seatArray[]);
void boardingPass(int seatNumber);

//main
int main(void)
{
	//datatypes
	int menuSelection, seat[10] = { 0 };
	//full 0 = available seats, 1 = first is full, 2 = econ is full, 3 = all is full
	int full = 0;
	char decision = 'n';
	bool repeat = true;
	
	//loop to keep assigning seats
	while (repeat)
	{
		//check to determine which parts of the plane are full
		full = isFull(seat);

		//if the whole plane (all elements of array are set to 1) the program says it's full and exits the program
		//this was put first so that when the program loops it can run this segment first before doing anything else
		if (full == 3)
		{
			puts("All seats have been reserved. The next flight is in 3 hours.");
			return 0;
		}

		//this function writes the simple menu to the screen
		drawMenu();

		//captures the menu selection so the program knows if first class or economy was selected
		scanf_s("%d", &menuSelection);

		//start of run for first class selection
		if (menuSelection == 1)
		{
			//if first class is full then the program offers to change to economy.
			//if the user does not want to change to economy then they are informed of the wait
			if (full == 1)
			{
				printf_s("%s", "\nFirst Class is full. Would you like to change to Economy? y/n: ");
				scanf_s(" %c", &decision, 1);

				if (decision == 'y')
					menuSelection = 2;
				else
					puts("The next flight leaves in 3 hours.");
			}//end if first class is full

			//as long as first class or the plane is not full the seating assignment function is run
			if (full != 1 && full != 3)
			{
				seating(menuSelection, seat);
			}
		}
		
		//economy is structured the same way that first class is with everything switched so if needed to upgrade to first class it can do so.
		if (menuSelection == 2)
		{
			if (full == 2)
			{
				printf_s("%s", "\nEconomy is full. Would you like to upgrade to First Class? y/n: ");
				scanf_s(" %c", &decision, 1);

				if (decision == 'y')
					menuSelection = 1;
				else
					puts("The next flight leaves in 3 hours.");
			}//end if economy is full

			if (full != 2 && full != 3)
			{
				seating(menuSelection, seat);
			}
		}

		//check to see if the user would like to continue assigning seats
		puts("Would you like to go again? y/n: ");
		scanf_s(" %c", &decision, 1);
		if (decision == 'n')
			repeat = false;

	}//end repeat
	
}//end main

//simple function to print the menu to the screen
void drawMenu()
{
	puts("\nPlease make your selection");
	puts("1. First Class");
	puts("2. Economy");
}

//funtion to check if the plane is full. Seperate checks are performed to determine if first class, economy, or both are full
int isFull(int seatArray[])
{
	int fullNum = 0, first = 0, econ = 0;

	for (int i = 0; i < 10; i++)
	{
		if (i < 5)
		{
			first += seatArray[i];
		}
		if (i >= 5)
		{
			econ += seatArray[i];
		}
	}

	if (first == 5)
		fullNum += 1;
	if (econ == 5)
		fullNum += 2;

	return fullNum;
}

//function to run through the array and determine which seats are available. When the seat is found the loop stops searching and
//passes the value to the boarding pass function
void seating(int firstOrEcon, int seatArray[])
{
	int i;
	bool search = true;
	//firstclass
	if (firstOrEcon == 1)
	{
		for (i = 0;search == true && i < 5; i++)
		{
			if (seatArray[i] == 0)
			{
				seatArray[i] = 1;
				search = false;
			}
		}//end for
	}
	//economy
	if (firstOrEcon == 2)
	{
		for (i = 5;search == true && i < 10; i++)
		{
			if (seatArray[i] == 0)
			{
				seatArray[i] = 1;
				search = false;
			}
		}//end for
	}

	boardingPass(i);
}

//simple function to print the boarding pass to the screen with the ticket type and the seat number
void boardingPass(int seatNumber)
{
	if (seatNumber < 6)
	{
		puts("Boarding Pass:");
		printf_s("Your \"First Class\" ticket is assigned to seat %d\n", seatNumber);
	}

	if (seatNumber >= 6)
	{
		puts("Boarding Pass:");
		printf_s("Your \"Economy\" ticket is assigned to seat %d\n", seatNumber);
	}
}