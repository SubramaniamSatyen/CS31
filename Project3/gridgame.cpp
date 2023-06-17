#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include "grid.h"
using namespace std;

//Required function prototypes
bool hasCorrectForm(string plan);
int determineSafeDistance(int r, int c, char dir, int maxSteps);
int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps);

//Used, but not required function prototypes
int checkPlanPortion(string plan, int position);
int calculateDistance(int r, int c, int horStep, int verStep);
bool inGrid(int r, int c);
int move(int& sr, int& sc, int rowMov, int colMov);
char changeDirection(char next, char current, int& rowMov, int& colMov);
int getDistanceToTravel(string plan, int index);


int main()
{	
	//Setting size and walls of game, drawing (for visual aid)
	
	setSize(25, 30);
	setWall(1, 4);
	setWall(2, 2);
	setWall(3, 2);
	draw(1, 1, 3, 4);   

	//Assertions to test "hasCorrectForm" required function
	assert(hasCorrectForm("1R") == true); //Testing one digit, one letter
	assert(hasCorrectForm("R") == true); //Testing no digits, one letter
	assert(hasCorrectForm("LL") == true); //Testing no digits, two letters
	assert(hasCorrectForm("99l") == true); //Testing two digits, one letter
	assert(hasCorrectForm("256R") == false); //Testing three digits, one letter
	assert(hasCorrectForm("0L0L0L0L") == true); //Testing multiple plan portions
	assert(hasCorrectForm("12R34L56R78L9R") == true); //Testing multiple plan portions
	assert(hasCorrectForm("123456789") == false); //Testing no turn directions
	assert(hasCorrectForm("1are2ell") == false); //Testing other letters
	assert(hasCorrectForm("1a2b3c") == false); //Testing other letters
	assert(hasCorrectForm("") == true); //Testing empty string
	assert(hasCorrectForm("Hello, my name is program") == false); //Testing three digits, one letter
	assert(hasCorrectForm("5rL00L0R09R7L") == true); //Provided example 1
	assert(hasCorrectForm("42l") == true); //Provided example 2
	assert(hasCorrectForm("1Rx2L") == false); //Provided example 3
	assert(hasCorrectForm("L2") == false); //Provided example 4
	assert(hasCorrectForm("144R") == false); //Provided example 5
	assert(hasCorrectForm("1R+2L") == false); //Provided example 6
	assert(hasCorrectForm("N144") == false); //Provided example 7
	assert(hasCorrectForm("w2+n3") == false); //Provided example 8
	assert(hasCorrectForm("LL2R2r2L1R") == true); //Provided example 9
	assert(hasCorrectForm("144R") == false); //Provided example 10
	assert(hasCorrectForm("2R1r") == true); //Provided example 11
	assert(hasCorrectForm("1Lx") == false); //Provided example 12
	
	//Assertions to test "determineSafeDistance" required function
	assert(determineSafeDistance(26, 1, 'E', 1) == -1); //Testing out of grid
	assert(determineSafeDistance(0, 0, 'e', 1) == -1); //Testing out of grid
	assert(determineSafeDistance(2, 2, 's', 9999999) == -1); //Testing at a wall
	assert(determineSafeDistance(1, 4, 'E', 1) == -1); //Testing wall boundary
	assert(determineSafeDistance(1, 1, 'e', -1) == -1); //Testing negative max steps
	assert(determineSafeDistance(1, 1, 'M', 1) == -1); //Testing negative max steps
	assert(determineSafeDistance(1, 1, 'E', 2) == 2); //Testing starting in corner
	assert(determineSafeDistance(1, 1, 'e', 1) == 1); //Testing maxSteps
	assert(determineSafeDistance(25, 30, 'E', 1) == 0); //Testing starting next to wall
	assert(determineSafeDistance(25, 30, 'w', 40) == 29); //Testing starting in corner
	assert(determineSafeDistance(25, 30, 'W', 1) == 1); //Testing maxSteps
	assert(determineSafeDistance(3, 1, 'N', 2) == 2); //Provided example 1
	assert(determineSafeDistance(1, 1, 'N', 2) == 0); //Provided example 2

	//Assertions to test "obeyPlan" required function
	int len;
	len = -999;
	assert(obeyPlan(0, 9999, 3, 4, 's', "R", len) == 2 && len == -999); //Invalid starting point (out of range)
	len = -999;
	assert(obeyPlan(1, 1, 2, 2, 's', "L", len) == 2 && len == -999); //Invalid end point (wall)
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'q', "RR", len) == 2 && len == -999); //Invalid direction
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'w', "123456789", len) == 2 && len == -999); //Invalid string
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'E', "N144", len) == 2 && len == -999); //Invalid string
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'E', "", len) == 1 && len == 0); //Part of a valid path
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'E', "2R2R", len) == 0 && len == 4); //Valid path
	len = -999;
	assert(obeyPlan(5, 10, 10, 20, 'e', "2RLRLR3L2R", len) == 1 && len == 7); //Part of a valid path
	len = -999;
	assert(obeyPlan(7, 8, 9, 10, 'n', "2L2L2L2L2L2L", len) == 1 && len == 12); //Part of a valid path
	len = -999;
	assert(obeyPlan(12, 12, 13, 13, 's', "1L1L", len) == 0 && len == 2); //Part of a valid path
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'E', "2R1R", len) == 1 && len == 3); //Part of a valid path
	len = -999;
	assert(obeyPlan(1, 1, 3, 3, 'E', "3R1R", len) == 3 && len == 2); //Path that runs into a wall
	len = -999;
	assert(obeyPlan(3, 1, 3, 4, 's', "LL2R2r2L1R", len) == 0 && len == 7); //Provided example 1
	len = -999;
	assert(obeyPlan(3, 1, 3, 4, 'N', "1Lx", len) == 2 && len == -999); //Provide example 2
	len = -999; 
	assert(obeyPlan(2, 4, 1, 1, 'w', "3R1L", len) == 3 && len == 1); //Provided example 3


	setSize(2, 2);
	setWall(2, 1);
	draw(1, 1, 2, 2);
	len = -999;
	assert(obeyPlan(1, 1, 2, 2, 'W', "RRRL1R1R", len) == 0 && len == 2); //Valid path
	len = -999;
	assert(obeyPlan(2, 1, 2, 2, 'e', "3R1L", len) == 2 && len == -999); //Invalid starting point (wall)
	len = -999;
	assert(obeyPlan(2, 2, 1, 1, 'n', "1L1L", len) == 0 && len == 2); //Valid path
	len = -999;
	assert(obeyPlan(2, 2, 1, 1, 'n', "2R1R", len) == 3 && len == 1); //Path that runs into a wall


	//Message to confirm program completion
	cerr << "Everything's Done :)";
	
}
/*
obeyPlan is essentially supposed to take in the starting point (sr, sc), the ending point (er, ec), the starting direction (dir),
a proposed navigational plan, and a pass by reference parameter nsteps. It returns 2 if invalid input, 1 if the plan works but 
doesn't get to the end, 0 if the plan works to the end of the maze, and 3 if the plan works part of the way, but runs into an issue.
*/
int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps) {
	//Checking if inputted values are valid, if not returning 2
	if (!inGrid(sr, sc) || !inGrid(er, ec) || isWall(sr, sc) || isWall(er, ec) || !hasCorrectForm(plan)
		|| !(tolower(dir) == 'n' || tolower(dir) == 'e' || tolower(dir) == 'w' || tolower(dir) == 's')) {
		return 2;
	}
	//Setting nsteps to zero before incrementing, setting position (in the string plan) to zero before incrementing
	nsteps = 0;
	int pos = 0;
	//Setting horizontal and vertical movement values, with 1 referring to increasing (east and south) and -1 referring to decreasing
	//(north and west)
	int rowMov = 0;
	int colMov = 0;
	if (tolower(dir) == 'n') {
		rowMov = -1;
	}
	else if (tolower(dir) == 's') {
		rowMov = 1;
	}
	else if (tolower(dir) == 'e') {
		colMov = 1;
	}
	else if (tolower(dir) == 'w') {
		colMov = -1;
	}

	//Incrementing through the plan
	while (pos < plan.size()) {
		char next = plan[pos];
		//If the current value is a digit, move the car
		if (isdigit(next)) {
			int travelDistance = getDistanceToTravel(plan, pos);
			//Moves the number of steps calculated in travelDistance and increment nsteps
			for (int j = 0; j < travelDistance; j++) {
				//If step is invalid (there is a wall or out of bounds) then return 3
				if (!inGrid(sr + rowMov, sc + colMov) || isWall(sr + rowMov, sc + colMov)) {
					return 3;
				}
				move(sr, sc, rowMov, colMov);
				nsteps++;
			}
			//Increment pos by the number of characters in the travelDistance
			pos += checkPlanPortion(plan, pos) - 1;
		}
		//If the current value is 'r' or 'l', change the direction
		else if (tolower(next) == 'r' || tolower(next) == 'l') {
			dir = changeDirection(next, dir, rowMov, colMov);
			pos++;
		}
	}
	//Finally, since the car completed the plan, evaluate if the car made it to the end or not and return 0 or 1 respectively.
	if (sr == er && sc == ec) {
		return 0;
	}
	return 1;
}

/*
This function takes the string and the index of the number of steps to take and returns an integer of that number of steps from the string
*/
int getDistanceToTravel(string plan, int index) {
	//Gets the number of digits in the integer value of steps (by looking at the plan portion size and subtracting the letter at the end)
	int digitsInDistance = checkPlanPortion(plan, index) - 1;
	int travelDistance = 0;
	//Initiallizing multiplier (which will be used to account for "tens" digit)
	int multiplier = 1;
	for (int i = digitsInDistance - 1; i >= 0; i--) {
		//Takes the right most digit character of the number of steps and calculates the numerical value of it (by looking at the difference
		//in character values)
		int num = plan[index + i] - '0';
		travelDistance += num * multiplier;
		multiplier *= 10;
	}
	return travelDistance;
}

/*
This function is pretty simple: it essentially increments the position by the direction the car is facing
*/
int move(int& sr, int& sc, int rowMov, int colMov) {
	sr += rowMov;
	sc += colMov;
	return 0;
}

/*
This function gets the current direction, the proposed change in direction, and changes row and column movement values accordingly
*/
char changeDirection(char next, char current, int& rowMov, int&colMov) {
	//First looks at indicated direction, then, based off of current direction, changes values accordingly and returns the new direction.
	if (tolower(next) == 'r') {
		if (tolower(current) == 'n') {
			rowMov = 0;
			colMov = 1;
			return 'e';
		}
		else if (tolower(current) == 'e') {
			rowMov = 1;
			colMov = 0;
			return 's';
		}
		else if (tolower(current) == 's') {
			rowMov = 0;
			colMov = -1;
			return 'w';
		}
		else if (tolower(current) == 'w') {
			rowMov = -1;
			colMov = 0;
			return 'n';
		}
	}
	else {
		if (tolower(current) == 'n') {
			rowMov = 0;
			colMov = -1;
			return 'w';
		}
		else if (tolower(current) == 'w') {
			rowMov = 1;
			colMov = 0;
			return 's';
		}
		else if (tolower(current) == 's') {
			rowMov = 0;
			colMov = 1;
			return 'e';
		}
		else if (tolower(current) == 'e') {
			rowMov = -1;
			colMov = 0;
			return 'n';
		}
	}
	return 'n';
}

/*
This function takes a proposed plan and verifies that the plan is a valid one (syntactically not for the specific grid)
*/
bool hasCorrectForm(string plan) {
	int pos = 0;
	while (pos < plan.size()) {
		//Check each plan portion and move to the next one
		int portionLength = checkPlanPortion(plan, pos);
		if (portionLength == -1) {
			return false;
		}
		pos += portionLength;
	}
	return true;
}
/*
This function takes the full plan and the starting index of a plan portion as parameters and returns the length of the plan portion,
returning -1 if the portion is invalid. 
*/
int checkPlanPortion(string fullPlan, int position) {
	//Checks if first character is digit, if so checks the next character, if not checks if character is 'l' or 'r'
	if (isdigit(fullPlan[position]) && position + 1 < fullPlan.size()) {
		//Checks if the second character is a digit, i f so checks the next character if not checks if the character is 'l' or 'r'
		if (isdigit(fullPlan[position + 1]) && position + 2 < fullPlan.size()) {
			//Character must be 'l' or 'r' to be valid, so checks that. If not, return -1
			if (tolower(fullPlan[position + 2]) == 'r' || tolower(fullPlan[position + 2]) == 'l') {
				return 3;
			}
			return -1;
		}
		else if (tolower(fullPlan[position + 1]) == 'r' || tolower(fullPlan[position + 1]) == 'l') {
			return 2;
		}
		return -1;
	}
	else if (tolower(fullPlan[position]) == 'r' || tolower(fullPlan[position]) == 'l') {
		return 1;
	}
	return -1;
}

/*
Function takes a point and a direction, as well as a proposed number of steps, and determines how many steps can be made from the point
in the given direction. If the number exceeds the proposed number of steps, returns the proposed number, otherwise returns the maximum
number of steps. If an invalid
*/
int determineSafeDistance(int r, int c, char dir, int maxSteps) {
	int trueMax = -1;
	//If input is invalid, return -1. If the direction is not 'n', 'e', 'w', or 's', function returns -1 in the last line of the function
	//instead of here (to reduce redundancy of checking character multiple times).
	if (!inGrid(r, c) || isWall(r, c) || maxSteps < 0) {
		return trueMax;
	}
	//Checks the provided direction and stores a calculated distance in trueMax using a series of if and else if statements
	if (tolower(dir) == 'w') {
		trueMax = calculateDistance(r, c, -1, 0);
	}
	else if (tolower(dir) == 'e') {
		trueMax = calculateDistance(r, c, 1, 0);
	}
	else if (tolower(dir) == 'n') {
		trueMax = calculateDistance(r, c, 0, -1);
	}
	else if (tolower(dir) == 's') {
		trueMax = calculateDistance(r, c, 0, 1);
	}
	//If the maximum amount of steps is greater than the proposed number of steps, return the proposed steps
	if (trueMax > maxSteps) {
		return maxSteps;
	}
	return trueMax;
}

/*
This function calculates the max number of steps from a provided point you can take in a particular direction (detailed by the horizontal
step and the vertical step values provided.
*/
int calculateDistance(int r, int c, int horStep, int verStep) {
	//If the point is not in the grid or is a wall, return -1
	if (!inGrid(r, c) || isWall(r, c)) {
		return -1;
	}
	//Intializing count and moving the c and r values to the next point (a point which we will check the validity of before incrementing)
	int count = 0;
	c += horStep;
	r += verStep;
	//Continue moving while in the grid
	while (inGrid(r, c)) {
		//If this point is a wall stop moving
		if (isWall(r, c)) {
			break;
		}
		count++;
		c += horStep;
		r += verStep;
	}
	return count;
}

/*
Simple function to check whether a provided point is within the grid
*/
bool inGrid(int r, int c) {
	return !(r <= 0 || c <= 0 || r > getRows() || c > getCols());
}
