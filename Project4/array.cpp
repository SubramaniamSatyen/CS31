#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//Required function prototypes
int reduplicate(string a[], int n);
int locate(const string a[], int n, string target);
int locationOfMax(const string a[], int n);
int circleLeft(string a[], int n, int pos);
int enumerateRuns(const string a[], int n);
int flip(string a[], int n);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int locateAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);


int main()
{
    /*
    Testing reduplicate function
    */
    //Testing one element
    string reduplicate1[1] = { "Professor_Smallberg" };
    assert(reduplicate(reduplicate1, 1) == 1);
    cerr << (reduplicate1[0] == "Professor_SmallbergProfessor_Smallberg") << endl;
    //Testing smaller length of array
    string reduplicate2[4] = { "a", "b", "c", "d"};
    assert(reduplicate(reduplicate2, 2) == 2);
    cerr << (reduplicate2[0] == "aa") << endl;
    cerr << (reduplicate2[1] == "bb") << endl;
    //Testing length of zero
    string reduplicate3[4] = { "a", "b", "c", "d" };
    assert(reduplicate(reduplicate3, 0) == 0);
    cerr << (reduplicate3[0] == "a") << endl;
    //Testing bad argument (negative length)
    string reduplicate4[4] = { "a", "b", "c", "d" };
    assert(reduplicate(reduplicate3, -42) == -1);
    cerr << (reduplicate3[0] == "a") << endl;
    
    /*
    Testing locate function
    */
    string locateArray[10] = { "a", "b", "c", "1", "2", "3", "Satyen", "Project4", "Professor", "Smallberg" };
    //Testing smaller length of array
    assert(locate(locateArray, 5, "2") == 4);
    //Testing full length of array
    assert(locate(locateArray, 10, "2") == 4);
    //Testing array of length 0
    assert(locate(locateArray, 0, "2") == -1);
    //Testing invalid input (negative length)
    assert(locate(locateArray, -99, "2") == -1);
    //Testing string that is not present
    assert(locate(locateArray, 5, "Hello World") == -1);
    //Testing full length of array
    assert(locate(locateArray, 10, "Project4") == 7);

    /*
    Testing locationOfMax function
    */
    string locationOfMax1[7] = { "a", "b", "c", "d", "e", "a", "e"};
    //Testing invalid input (negative length)
    assert(locationOfMax(locationOfMax1, -1) == -1);
    //Testing array of length 0
    assert(locationOfMax(locationOfMax1, 0) == -1);
    //Testing smaller length of array
    assert(locationOfMax(locationOfMax1, 3) == 2);
    //Testing full length of array
    assert(locationOfMax(locationOfMax1, 7) == 4);
    //Testing full length of array
    string locationOfMax2[3] = { "Large", "Larger", "Largest" };
    assert(locationOfMax(locationOfMax1, 3) == 2);

    /*
    Testing circleLeft function
    */
    //Testing invalid input (negative length)
    string circleLeft1[5] = { "a", "b", "c", "d", "e" };
    assert(circleLeft(circleLeft1, 5, 3) == 3);
    //cerr << circleLeft1[3] << endl << circleLeft1[4];
    //Testing array of length 0
    string circleLeft2[5] = { "a", "b", "c", "d", "e" };
    assert(circleLeft(circleLeft2, 0, 0) == -1);
    //Testing n smaller than pos
    assert(circleLeft(circleLeft2, 42, 43) == -1);
    //Testing full length of array
    string circleLeft3[5] = { "a", "b", "c", "d", "e" };
    assert(circleLeft(circleLeft3, 5, 0) == 0);
    //Testing with array of length 1
    string circleLeft4[1] = { "I'm an array" };
    assert(circleLeft(circleLeft4, 1, 0) == 0);

    /*
    Testing enumerateRuns function
    */
    string enumerateRunsArray[10] = { "a", "a", "b", "b", "b", "c", "d", "d", "D", "e" };
    //Testing with array of length 0
    assert(enumerateRuns(enumerateRunsArray, 0) == 0);
    //Testing invalid input (negative length)
    assert(enumerateRuns(enumerateRunsArray, -21) == -1);
    //Testing with part of an array
    assert(enumerateRuns(enumerateRunsArray, 5) == 2);
    //Testing with full array
    assert(enumerateRuns(enumerateRunsArray, 10) == 6);

    /*
    Testing flip function
    */
    string flip1[4] = { "1", "2", "3", "4" };
    //Testing with array of length 0
    assert(flip(flip1, 0) == 0);
    //Testing with invalid input (negative length)
    assert(flip(flip1, -999) == -1);
    //Testing with part of array
    assert(flip(flip1, 3) == 3);
    //cerr << flip1[1] << " " << flip1[2] << endl;
    //Testing with full array
    string flip2[4] = { "1", "2", "3", "4" };
    assert(flip(flip2, 4) == 4);
    //cerr << flip2[1] << " " << flip2[2] << endl;

    /*
    Testing locateDifference function
    */
    string locateDifferenceArray1[5] = { "Hello", "My", "Name", "Is", "Satyen" };
    string locateDifferenceArray2[3] = { "Hello", "My", "Satyen" };
    //Testing with arrays of length 0
    assert(locateDifference(locateDifferenceArray1, 0, locateDifferenceArray2, 0) == 0);
    //Testing with full arrays
    assert(locateDifference(locateDifferenceArray1, 5, locateDifferenceArray2, 3) == 2);
    //Testing with invalid input (negative length)
    assert(locateDifference(locateDifferenceArray1, -1, locateDifferenceArray2, 3) == -1);
    //Testing with invalid input (negative length)
    assert(locateDifference(locateDifferenceArray1, -1, locateDifferenceArray2, -999) == -1);
    //Testing with identical arrays
    assert(locateDifference(locateDifferenceArray1, 2, locateDifferenceArray2, 2) == 2);
    //Testing with short arrays of different size
    assert(locateDifference(locateDifferenceArray1, 3, locateDifferenceArray2, 2) == 2);

    /*
    Testing subsequence function
    */
    string subsequence1[5] = { "Hello", "My", "Name", "Is", "Satyen" };
    string subsequence2[3] = { "Name", "Is", "Satyen" };
    //Testing with arrays of length 0
    assert(subsequence(subsequence1, 0, subsequence2, 0) == 0);
    //Testing with invalid input (negative length)
    assert(subsequence(subsequence1, 0, subsequence2, -99) == -1);
    //Testing with full arrays
    assert(subsequence(subsequence1, 5, subsequence2, 3) == 2);
    //Testing Subsequence not present
    assert(subsequence(subsequence1, 4, subsequence2, 3) == -1);
    //Testing part of subsequence array and full searching array
    assert(subsequence(subsequence1, 5, subsequence2, 2) == 2);

    /*
    Testing locateAny function
    */
    string locateAny1[6] = { "a", "b", "c", "d", "e", "f" };
    string locateAny2[6] = { "g", "B", "ee", "c", "e", "f" };
    //Testing with arrays of length 0 
    assert(locateAny(locateAny1, 0, locateAny2, 0) == -1);
    //Testing with invalid input (negative length)
    assert(locateAny(locateAny1, -1, locateAny2, 0) == -1);
    //Testing with full arrays
    assert(locateAny(locateAny1, 6, locateAny2, 6) == 2);
    //Testing with partial arrays
    assert(locateAny(locateAny1, 4, locateAny2, 4) == 2);
    //Testing subsequence not present
    assert(locateAny(locateAny1, 6, locateAny2, 2) == -1);
    //Testing with empty array 
    assert(locateAny(locateAny1, 6, locateAny2, 0) == -1);


    /*
    Testing separate function
    */
    string separate1[7] = { "a", "d", "e", "c", "b", "f", "g" };
    //Testing with array of length 0
    assert(separate(separate1, 0, "String") == 0);
    //Testing with invalid input (negative length)
    assert(separate(separate1, -34, "a") == -1);
    //Testing with full array
    assert(separate(separate1, 7, "b") == 1);
    //cerr << separate1[1] << " " << separate1[3];
    //Testing with value not present in array
    assert(separate(separate1, 7, "aa") == 1);
    //Testing with value not present in array, greater than all array values
    assert(separate(separate1, 7, "zz") == 7);

    /*
    Tests Provided within project spec
    */
    string stuff[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
    assert(locate(stuff, 6, "cous") == 2);
    assert(reduplicate(stuff, 6) == 6 && stuff[0] == "mahimahi" && stuff[5] == "murmur");
    string cast[6] = { "elsa", "ariel", "mulan", "tiana", "belle", "moana" };
    assert(locationOfMax(cast, 6) == 3);
    string folks[5] = { "moana", "elsa", "ariel", "raya", "mulan" };
    assert(circleLeft(folks, 5, 1) == 1 && folks[4] == "elsa");
    string d[9] = {"belle", "merida", "raya", "raya", "tiana", "tiana", "tiana", "raya", "raya"};
    assert(enumerateRuns(d, 9) == 5);
    string roles[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
    assert(flip(roles, 4) == 4 && roles[0] == "belle" && roles[3] == "merida");
    string moreRoles[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
    string group[5] = { "merida", "raya", "elsa", "", "belle" };
    assert(locateDifference(moreRoles, 6, group, 5) == 2);
    assert(locateDifference(moreRoles, 2, group, 1) == 1);
    string names[10] = { "moana", "mulan", "raya", "tiana", "merida" };
    string names1[10] = { "mulan", "raya", "tiana" };
    assert(subsequence(names, 5, names1, 3) == 1);
    string names2[10] = { "moana", "tiana" };
    assert(subsequence(names, 4, names2, 2) == -1);
    string set1[10] = { "elsa", "merida", "tiana", "mulan" };
    assert(locateAny(names, 6, set1, 4) == 1);
    string set2[10] = { "belle", "ariel" };
    assert(locateAny(names, 6, set2, 2) == -1);
    string secondCast[6] = { "elsa", "ariel", "mulan", "belle", "tiana", "moana" };
    assert(separate(secondCast, 6, "merida") == 3);
    //for (int i = 0; i < 6; i++) {
    //    cerr << secondCast[i] << " ";
    //}
    //cerr << endl;
    string thirdCast[4] = { "mulan", "tiana", "ariel", "raya" };
    //for (int i = 0; i < 4; i++) {
    //    cerr << thirdCast[i] << " ";
    //}
    //cerr << endl;
    separate(thirdCast, 4, "raya");
    assert(separate(thirdCast, 4, "raya") == 2);


    /*
    Incomplete set of tests provided at end of project spec
    */
    string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
    assert(locate(h, 7, "belle") == 5);
    assert(locate(h, 7, "ariel") == 2);
    assert(locate(h, 2, "ariel") == -1);
    assert(locationOfMax(h, 7) == 3);

    string g[4] = { "moana", "mulan", "belle", "raya" };
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");

    string c[4] = { "ma", "can", "tu", "do" };
    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

    string e[4] = { "ariel", "tiana", "", "belle" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d2[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
    assert(enumerateRuns(d2, 5) == 2);

    string f[3] = { "tiana", "ariel", "raya" };
    assert(locateAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana");

    assert(separate(h, 7, "elsa") == 3);
    
    //Message to confirm tests ran successfully. 
    cout << "All tests succeeded :)" << endl;
}

/*
This function duplicates all elements within the specified array for the specified size, returns size.
*/
int reduplicate(string a[], int n) {
    //Checking for bad arguments
    if (n < 0) {
        return -1;
    }
    //loops through array a, appending each item onto itself, "reduplicating" it
    for (int i = 0; i < n; i++) {   
        a[i] += a[i];
    }
    return n;
}

/*
This function locates a provided string within a provided array of provided length. Returns -1 if no string exists as requested but
also returns -1 if provided a negative n value (bad argument). 
*/
int locate(const string a[], int n, string target) {
    //Loops through array a, comparing each item to the target
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

/*
This function finds the first location of the largest string using > and < operations, returning -1 if string does not exist. 
Function also returns -1 if provided negative n as requested (bad argument).
*/
int locationOfMax(const string a[], int n) {
    //Checking for bad argument AND checking for examining zero elements of the array (meaning string isn't present)
    if (n <= 0) {
        return -1;
    }
    //Initializing the max and the index of max (pos) to the first element of the array
    int pos = 0;
    string max = a[0];
    //Looping through array starting at the second element (if it exists)
    for (int i = 1; i < n; i++) {
        //If current value is larger than max, set max and index of max (pos) to current value
        if (a[i] > max) {
            pos = i;
            max = a[i];
        }
    }
    return pos;
}

/*
This function moves the element at a specified position, shifting the following elements to the left, before replacing the final element
with the element that used to be at the specified position. Returns the initial position of the "circled" element.
*/
int circleLeft(string a[], int n, int pos) {
    //Checking for bad arguments
    if (pos < 0 || pos >= n || n < 0) {
        return -1;
    }
    //Stores element to be "circled" for later use
    string temp = a[pos];
    //Loops through array starting at the specified position, shifting elements to left
    for (int i = pos; i < n-1; i++) {
        a[i] = a[i + 1];
    }
    //Sets final element to the "circled" value
    a[n - 1] = temp;
    return pos;
}

/*
This function returns the number of sequences of consecutive unique items in the provided array
*/
int enumerateRuns(const string a[], int n) {
    //Checking for bad arguments
    if (n < 0) {
        return -1;
    }
    //Checking for edge case of 0 passed as array length
    else if (n == 0) {
        return 0;
    }

    //Initalizes current value to first value and count of sequences of consecutive unique items to 1
    int count = 1;
    string last = a[0];
    //Loops through array, comparing each item to previous
    for (int i = 1; i < n; i++) {
        //If item is different from previous, increment count and update current string
        if (a[i] != last) {
            count++;
            last = a[i];
        }
    }
    return count;
}

/*
This function reverses the order of the provided array for the provided length.
*/
int flip(string a[], int n) {
    //Checking for bad arguments
    if (n < 0) {
        return -1;
    }
    string temp;
    //Loops through array, swapping corresponding elements. 
    for (int i = 0; i < n/2; i++) {
        temp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = temp;
    }
    return n;
}

/*
This function identifies the first index that is not equal between two provided arrays with provided lengths
*/
int locateDifference(const string a1[], int n1, const string a2[], int n2) {
    //Checking for bad arguments
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    //Setting the distince to search to the smaller array size
    int dis = n1;
    if (n2 < n1) {
        dis = n2;
    }
    //Incrementing through arrays in parallel
    for (int i = 0; i < dis; i++) {
        //If array elements are not the same, return the index
        if (a1[i] != a2[i]) {
            return i;
        }
    }
    //Return the length of the shortest array (corresonding to the next index of the larger array, which is a different value)
    return dis;
}

/*
This function takes a provided array, and searches a second array to see if the elements of the first array appear consecutively in it.
Returns the starting index of the sequence if it exists, otherwise returns -1.
*/
int subsequence(const string a1[], int n1, const string a2[], int n2) {
    //Checking for bad arguments AND if the desired sequence is longer than the first array
    if (n1 < 0 || n2 < 0 || n1 < n2) {
        return -1;
    }
    //If desired sequence has length 0, return position 0
    if (n2 == 0) {
        return 0;
    }
    //Looping through the first array until the desired sequence cannot fit, searching for a match
    for (int i = 0; i < n1 - n2 +1; i++) {
        if (a1[i] == a2[0]) {
            bool seq = true;
            //Looping through the provided sequence and array in parallel, breaking the loop if an element doesn't match 
            for (int j = 1; j < n2; j++) {
                if (a1[i + j] != a2[j]) {
                    seq = false;
                    break;
                }
            }
            //If all elements matched return the index
            if (seq) {
                return i;
            }
        }
    }
    return -1;
}


/*
Returns the smallest index in the first provided array in which an element of the second provide array exists. Otherwise returns -1.
Both array's lengths have been provided.
*/
int locateAny(const string a1[], int n1, const string a2[], int n2) {
    //Looping through each element in the second array for each element in the first array and comparing. If a match, return index.
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) {
                return i;
            }
        }
    }
    //Return statement catches bad arguments, as well as if no elements match
    return -1;
}

/*
For a provided separator string, moves all elements that are less than that string to the left side of where the separator would be
placed in the array, and moves all elements that are greater than the string to the right side of where the separator would be
in the array.
*/
int separate(string a[], int n, string separator) {
    //Checking for bad arguments
    if (n < 0) {
        return -1;
    }

    //Loops through the provided array, moving the largest string to the last position of the array each iteration,
    //effectively sorting it
    string temp;
    for (int i = n-1; i >=0; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] >= a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    //Loops through the provided array, now sorted, finding where the separator would be indexed
    for (int i = 0; i < n; i++) {
        if (separator <= a[i]) {
            return i;
        }
    }
    return n;
}

