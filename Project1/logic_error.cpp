// Code for Project 1
// Report survey results

#include <iostream>
using namespace std;

int main()
{
	int numberSurveyed;
	int likeInPerson;
	int likeAtHome;

	cout << "How many students were surveyed? ";
	cin >> numberSurveyed;
	cout << "How many of them prefer being at school in person? ";
	cin >> likeInPerson;
	cout << "How many of them would rather do school from home? ";
	cin >> likeAtHome;
	
	//Changed 100.0 to 1000.0 for pctLikeInPerson and 100.0 to 10.0 to pctLikeAtHome to make next two printed lines wrong
	double pctLikeInPerson = 1000.0 * likeInPerson / numberSurveyed;
	double pctLikeAtHome = 10.0 * likeAtHome / numberSurveyed;

	cout.setf(ios::fixed);
	cout.precision(1);

	cout << endl;
	cout << pctLikeInPerson << "% prefer being at school in person." << endl;
	cout << pctLikeAtHome << "% prefer doing school from home." << endl;

	//Flipped ">" to "<" to make last line always wrong
	if (likeInPerson < likeAtHome)
		cout << "More students like being at school in person than doing school at home." << endl;
	else
		cout << "More students like doing school from home than being at school in person." << endl;
}