#include <iostream>
#include <string>
using namespace std;

int main() {
	//Defining constants as outlined in spec
	const int LUX_CHARGE = 71;
	const int NON_LUX_CHARGE = 43;
	const double FIRST_RATE = 0.27;
	const double OTHER_SECOND_RATE = 0.21;
	const double WINTER_SECOND_RATE = 0.27;
	const double FINAL_RATE = 0.17;

	//Defining variables to recieve user input and hold calculated value
	int inital_odo;
	int final_odo;
	int distance;
	int rental_days;
	string customer_name;
	string luxury;
	int month;
	double calculated_price;


	//Getting Odometer start from user
	cout << "Odometer at start: ";
	cin >> inital_odo;
	cin.ignore(10000, '\n');
	
	//Getting Odometer final from user
	cout << "Odometer at end: ";
	cin >> final_odo;
	cin.ignore(10000, '\n');

	//Asking rental days
	cout << "Rental days: ";
	cin >> rental_days;
	cin.ignore(10000, '\n');

	//Reading in Customer Name
	cout << "Customer name: ";
	getline(cin, customer_name);

	//Asking whether luxury car
	cout << "Luxury car? (y/n): ";
	getline(cin, luxury);

	//Asking about month of rental start
	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;
	cin.ignore(10000, '\n');

	//print out "---"
	cout << "---" << endl;

	//setting output precision for dollar price
	cout.setf(ios::fixed);
	cout.precision(2);

	//Starting odometer cannot be less than zero
	if (inital_odo < 0) {
		cout << "The starting odometer reading must not be negative." << endl;
		return 1;
	}

	//Final odometer cannot be less than starting odometer
	else if (final_odo - inital_odo < 0) {
		cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
		return 1;
	}

	//Throws error for non positive rental days
	else if (rental_days <= 0) {
		cout << "The number of rental days must be positive." << endl;
		return 1;
	}

	//Throws error for empty customer string
	else if (customer_name.length() < 1) {
		cout << "You must enter a customer name." << endl;
		return 1;
	}

	//Throws error for unacceptable luxury value
	else if (luxury != "y" && luxury != "n") {
		cout << "You must enter y or n." << endl;
		return 1;
	}

	//Throws error for invalid month
	else if (month < 1 || month > 12) {
		cout << "The month number must be in the range 1 through 12." << endl;
		return 1;
	}
	//Proceeds to calculate the price
	else {
		//Calculates the distance traveled
		distance = final_odo - inital_odo;
		if (luxury == "y") {
			//After determining luxury or not, determines the different rates to apply depending on the distance traveled
			if (distance <= 100) {
				calculated_price = LUX_CHARGE * rental_days + FIRST_RATE * distance;
			}
			else if (month == 12 || month <= 3) {
				if (distance <= 500) {
					calculated_price = LUX_CHARGE * rental_days + FIRST_RATE * 100 + WINTER_SECOND_RATE * (distance - 100);
				}
				else if (distance > 500) {
					calculated_price = LUX_CHARGE * rental_days + FIRST_RATE * 100 + WINTER_SECOND_RATE * 400 + FINAL_RATE * (distance - 500);
				}
			}
			else if (month > 3) {
				if (distance <= 500) {
					calculated_price = LUX_CHARGE * rental_days + FIRST_RATE * 100 + OTHER_SECOND_RATE * (distance - 100);
				}
				else if (distance > 500) {
					calculated_price = LUX_CHARGE * rental_days + FIRST_RATE * 100 + OTHER_SECOND_RATE * 400 + FINAL_RATE * (distance - 500);
				}
			}
		}
		//else luxury == 'n'
		else {
			//If not luxury, determines which rates to apply depending on the distance traveled
			if (distance <= 100) {
				calculated_price = NON_LUX_CHARGE * rental_days + FIRST_RATE * distance;
			}
			else if (month == 12 || month <= 3) {
				if (distance <= 500) {
					calculated_price = NON_LUX_CHARGE * rental_days + FIRST_RATE * 100 + WINTER_SECOND_RATE * (distance - 100);
				}
				else if (distance > 500) {
					calculated_price = NON_LUX_CHARGE * rental_days + FIRST_RATE * 100 + WINTER_SECOND_RATE * 400 + FINAL_RATE * (distance - 500);
				}
			}
			else if (month > 3) {
				if (distance <= 500) {
					calculated_price = NON_LUX_CHARGE * rental_days + FIRST_RATE * 100 + OTHER_SECOND_RATE * (distance - 100);
				}
				else if (distance > 500) {
					calculated_price = NON_LUX_CHARGE * rental_days + FIRST_RATE * 100 + OTHER_SECOND_RATE * 400 + FINAL_RATE * (distance - 500);
				}
			}
		}
		//Final output
		cout << "The rental charge for " << customer_name << " is $" << calculated_price << endl;
	}
}