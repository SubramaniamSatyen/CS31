//To deal with warnings
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:6262)

#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;

//Defining constants as outlined in project spec
const int MAX_NUM_MESSAGES = 71;
const int MAX_LENGTH_OF_MESSAGE = 91;
const int ALPHABET_LENGTH = 26;

//Function prototypes (decrypt is only required one)
bool decrypt(const char ciphertext[], const char crib[]);
void clean2D(const char original[], char cleaned[][MAX_LENGTH_OF_MESSAGE], int* length);
void clean3D(const char original[], char cleaned[][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE], int* messages, int meslengths[]);
bool outputMessage(const char encodedLetters[], const char unencodedLetters[], const char ciphertext[]);
bool lenMatch(const char CipherArray[][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE], const char CribArray[][MAX_LENGTH_OF_MESSAGE], int lenCrib, int messageCipher, int wordCipher);
bool createCipherKey(char tempKey[], char tempCorr[], const char CipherArray[][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE], const char CribArray[][MAX_LENGTH_OF_MESSAGE], int lenCrib, int messageCipher, int wordCipher);


int main(){
	//Provided Example 1
	char cipher[MAX_LENGTH_OF_MESSAGE] = "F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n";
	char crib[MAX_LENGTH_OF_MESSAGE] = "   hush???hUSh---     --- until    NovemBER !!  ";
	assert(decrypt(cipher, crib) == true);

	//Provided Example 2
	char cipher1[MAX_LENGTH_OF_MESSAGE * 4] = "Rswjo qgx Tmeuo sgjsy jds vqgf vo jds vqzf xbby.\nUdbyjo iqcju cg wybgj cg jds esjqiqo zqy\nXbg'j rsj jds jsrrsy jycn jds ucrsgj qrqyt.\nZU 31 cu zdqrrsgecge!";
	char crib1[MAX_LENGTH_OF_MESSAGE] = "silent alarm";
	assert(decrypt(cipher1, crib1) == true);

	//Provided Example 3
	char cipher2[MAX_LENGTH_OF_MESSAGE] = "bwra wmwt\nqeirtk spst\n";
	char crib2[MAX_LENGTH_OF_MESSAGE] = "alan turing";
	assert(decrypt(cipher2, crib2) == false);

	//Provided Example 4
	char cipherA[MAX_LENGTH_OF_MESSAGE] = "Kpio't dmpbl-boe-ebhhfs opwfm";
	char cribA[MAX_LENGTH_OF_MESSAGE] = "s cloak and";
	assert(decrypt(cipherA, cribA) == true);

	//Provided Example 5
	char cipherB[MAX_LENGTH_OF_MESSAGE] = "ew'q p-aj";
	char cribB[MAX_LENGTH_OF_MESSAGE] = "dog";
	assert(decrypt(cipherB, cribB) == false);

	//Provided Example 6
	char cipherC[MAX_LENGTH_OF_MESSAGE] = "ew'q p-aj";
	char cribC[MAX_LENGTH_OF_MESSAGE] = "he";
	assert(decrypt(cipherC, cribC) == true);

	//Provided Example 7 (Slightly modified)
	char cipherD[MAX_LENGTH_OF_MESSAGE] = "ew'q p-aa";
	char cribD[MAX_LENGTH_OF_MESSAGE] = "he";
	assert(decrypt(cipherD, cribD) == true);

	//Provided Example 8
	char cipherE[MAX_LENGTH_OF_MESSAGE] = "Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n";
	char cribE[MAX_LENGTH_OF_MESSAGE] = "my secret";
	assert(decrypt(cipherE, cribE) == true);

	//Provided Example 9
	char cipherF[MAX_LENGTH_OF_MESSAGE] = "Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n";
	char cribF[MAX_LENGTH_OF_MESSAGE] = "shadow";
	assert(decrypt(cipherF, cribF) == false);

	//Testing with empty crib 1
	char cipher3[MAX_LENGTH_OF_MESSAGE] = "      \n\n ";
	char crib3[MAX_LENGTH_OF_MESSAGE] = "  ";
	assert(decrypt(cipher3, crib3) == false);

	//Testing with empty crib 2
	char cipher4[MAX_LENGTH_OF_MESSAGE] = "   Hello  asdfjk; 123\n23232No\n 2";
	char crib4[MAX_LENGTH_OF_MESSAGE] = "    ";
	assert(decrypt(cipher4, crib4) == false);

	//Testing with empty ciphertext 1
	char cipher5[MAX_LENGTH_OF_MESSAGE] = "";
	char crib5[MAX_LENGTH_OF_MESSAGE] = "Hello World123???!?1/";
	assert(decrypt(cipher5, crib5) == false);

	//Testing with empty ciphertext 2
	char cipher6[MAX_LENGTH_OF_MESSAGE] = "\n\n\n\n   ";
	char crib6[MAX_LENGTH_OF_MESSAGE] = "";
	assert(decrypt(cipher6, crib6) == false);

	//Testing with crib longer than ciphertext
	char cipher7[MAX_LENGTH_OF_MESSAGE] = "HW";
	char crib7[MAX_LENGTH_OF_MESSAGE] = "1234Hello";
	assert(decrypt(cipher7, crib7) == false);

	//Testing with ciphertext of equal length to the crib 1
	char cipher8[MAX_LENGTH_OF_MESSAGE] = "abccd    ";
	char crib8[MAX_LENGTH_OF_MESSAGE] = "HeLLo         ";
	assert(decrypt(cipher8, crib8) == true);

	//Testing with ciphertext of equal length to the crib 2 (with spaces after)
	char cipher9[MAX_LENGTH_OF_MESSAGE] = "World :)   ";
	char crib9[MAX_LENGTH_OF_MESSAGE] = "WORLd123??  ";
	assert(decrypt(cipher9, crib9) == true);

	//Testing with ciphertext of equal length to the crib 3 (with varied spaces)
	char cipher10[MAX_LENGTH_OF_MESSAGE] = "\n\n   dnskkvwtg";
	char crib10[MAX_LENGTH_OF_MESSAGE] = "   SmALlBeRG!123  ";
	assert(decrypt(cipher10, crib10) == true);

	//Testing with ciphertext of equal length to the crib 4 (with no spaces before or after)
	char cipher11[MAX_LENGTH_OF_MESSAGE] = "dnsk1vwtg";
	char crib11[MAX_LENGTH_OF_MESSAGE] = "SmAL1BeRG";
	assert(decrypt(cipher11, crib11) == true);

	//Testing with ciphertext with two words and of equal length to crib
	char cipher12[MAX_LENGTH_OF_MESSAGE] = "\n\n oTpqwddpT ~[][][][=-=-=-=-]  dnskkvwtg";
	char crib12[MAX_LENGTH_OF_MESSAGE] = "Professor?\n  SmALlBeRG!123  ";
	assert(decrypt(cipher12, crib12) == true);

	//Testing with crib of really long length (that doesn't appear in ciphertext)
	char cipher13[MAX_LENGTH_OF_MESSAGE] = "a";
	char crib13[MAX_LENGTH_OF_MESSAGE * 10] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	assert(decrypt(cipher13, crib13) == false);

	//Testing with crib of really long length (that appears in ciphertext)
	char cipher14[MAX_LENGTH_OF_MESSAGE] = "bcd";
	char crib14[MAX_LENGTH_OF_MESSAGE * 10] = "art aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	assert(decrypt(cipher14, crib14) == false);

	//Testing with ciphertext of maximum length
	char cipher15[MAX_LENGTH_OF_MESSAGE * 2] = "\nI am writing this as a means of testing whether decrypt.cpp works and hopefully it does!!!\n";
	char crib15[MAX_LENGTH_OF_MESSAGE] = "crib";
	assert(decrypt(cipher15, crib15) == true);

	//Testing with ciphertext of maximum length 2 (with identical crib and ciphertext)
	char cipher17[MAX_LENGTH_OF_MESSAGE * 2] = "\nI am writing this as a means of testing whether decrypt.cpp works and hopefully it does!!!\n";
	char crib17[MAX_LENGTH_OF_MESSAGE * 2] = "132321I am writing this as a means of testing whether decrypt.cpp works and hopefully it does!!!";
	assert(decrypt(cipher17, crib17) == true);

	//Testing with ciphertext of maximum length 3 (with identical crib and ciphertext)
	char cipher18[MAX_LENGTH_OF_MESSAGE * 2] = "\naaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nbaasldkjfalkjsdlfkajs;dlkfjas;lkdjfas;dklfja";
	char crib18[MAX_LENGTH_OF_MESSAGE * 2] = "1aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1232-=-=-=][\[]][\';";
	assert(decrypt(cipher18, crib18) == true);

	//Testing with crib of excessive length and maximum ciphertext length (with the full ciphertext present in the crib)
	char cipher19[MAX_LENGTH_OF_MESSAGE * 2] = "\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nbaasldkjfalkjsdlfkajs;dlkfjas;lkdjfas;dklfja";
	char crib19[MAX_LENGTH_OF_MESSAGE * 2] = "1aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1232-=-=-=][\[]][\';";
	assert(decrypt(cipher19, crib19) == false);

	//Testing sample message 1
	char cipher20[MAX_LENGTH_OF_MESSAGE] = "Egrtr Dtllaut!!!!11!11";
	char crib20[MAX_LENGTH_OF_MESSAGE] = "CODed_MESSaGe";
	assert(decrypt(cipher20, crib20) == true);

	//Testing sample message 2
	char cipher21[MAX_LENGTH_OF_MESSAGE * 3] = "\n\t\tMiol ol a ltektm dtllaut egrtr wlofu a eohitk.\n\t\t--Hkgytllgk Ldassztku ol eggs--\n\t\tMiol ol mit tfr gy mit tfegrtr dtllaut";
	char crib21[MAX_LENGTH_OF_MESSAGE] = "Professor Smallberg:)";
	assert(decrypt(cipher21, crib21) == true);

	//Testing sample message 3
	char cipher22[MAX_LENGTH_OF_MESSAGE * 4] = "\nHkgptem 5 ol eggs. Itkt akt lgdt ktalgfl:\n\t-Om eaf iafrst actlgdt lbdzgsl soqt mitlt 1235251!@#$!@#%^$!|\]\\]][:)(:)\n\t-Om itshl wl wfrtklmafr E Lmkoful cioei akt mgmassb \nactlgdt afr fgm lwhtk affgbofu mg wlt am ass";
	char crib22[MAX_LENGTH_OF_MESSAGE] = "Project 500 is cooL!";
	assert(decrypt(cipher22, crib22) == true);

	return 0;
}

/*
Taking a series of messages in a ciphertext and a crib for that ciphertext, searches ciphertext to see if crib exists. If so, 
prints partially decrypted message and returns true, otherwise returns false.
*/
bool decrypt(const char ciphertext[], const char crib[]) {
	//Checking for edgecases of crib length
	if (strlen(crib) == 0 || strlen(ciphertext) == 0) {
		return false;
	}
	//Initalizing holders for processed crib words and number of words
	char CribArray[MAX_NUM_MESSAGES][MAX_LENGTH_OF_MESSAGE] = { {""} };
	int lenCrib;
	//Process crib into cleaned array of C strings (2D character array representing words and characters in words)
	clean2D(crib, CribArray, &lenCrib);
	//If, after cleaning, crib is empty, return false
	if (lenCrib <= 0 || lenCrib >= MAX_LENGTH_OF_MESSAGE) {
		return false;
	}
	//Initializing holders for processed ciphertext, number of messages, and number of words in each message
	char CipherArray[MAX_NUM_MESSAGES][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE] = { {{""}} };
	int numMessages = 0;
	int lenMessages[MAX_NUM_MESSAGES] = { 0 };
	//Process ciphertext into 3D array of C strings (3D character array representing messages, words, and characters in words)
	clean3D(ciphertext, CipherArray, &numMessages, lenMessages);

	//Initializing holders for parallel cipher key
	char encodedLetters[ALPHABET_LENGTH + 1] = "";
	char unencodedLetters[ALPHABET_LENGTH + 1] = "";
	


	//Looping through messages in processed ciphertext looking for match with crib
	for (int i = 0; i < numMessages; i++){
		//Looping through words in each message (no need to check words when length of crib won't fit in rest of message)
		for (int j = 0; j <= lenMessages[i]-lenCrib; j++) {
			//If word's length in ciphertext matches the length of the first word in the crib
			if (strlen(CipherArray[i][j]) == strlen(CribArray[0])) {
				//If length of following words in ciphertext match length of following words in crib
				if (lenMatch(CipherArray, CribArray, lenCrib, i, j)) {
					//Create temporary cipher key to use while verifying crib
					char tempKey[ALPHABET_LENGTH + 1] = "";
					char tempCorr[ALPHABET_LENGTH + 1] = "";
					//If we can create a valid cipher key from this instance of words of matching lengths
					if (createCipherKey(tempKey, tempCorr, CipherArray, CribArray, lenCrib, i, j)) {
						//Save the temporary key as the actual key
						strcpy(encodedLetters, tempKey);
						strcpy(unencodedLetters, tempCorr);
						return outputMessage(encodedLetters, unencodedLetters, ciphertext);
					}
				}
			}
		}
	}
	//Return if possible to print message (and print one first if possible)
	return false;
}

/*
This function takes a 3D character array representing a series of words in a series of messages, and a 2D crib, knowing that a series 
of words in the two have equal lengths, and attempts to create a cipher key that works for those words in the ciphertext and the crib.
Returns true and stores the key in provided arrays if successful, and returns false if unsuccessful. 
*/
bool createCipherKey(char tempKey[], char tempCorr[], const char CipherArray[][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE], const char CribArray[][MAX_LENGTH_OF_MESSAGE], int lenCrib, int messageCipher, int wordCipher) {
	//Looping through each word in length of the crib and character in word of crib
	for (int k = 0; k < lenCrib; k++) {
		for (int l = 0; l < strlen(CribArray[k]); l++) {
			//If crib character has already been added to cipher key
			if (strchr(tempCorr, CribArray[k][l]) != nullptr) {
				//If character in cipher does not match the value we have said it should in our key, our key is invalid
				if (CipherArray[messageCipher][wordCipher + k][l] != tempKey[strchr(tempCorr, CribArray[k][l]) - tempCorr]) {
					return false;
				}
				//If characters match, keep creating key
				else {
					continue;
				}
			}
			//If cipher has letter already added to cipher key
			else if (strchr(tempKey, CipherArray[messageCipher][wordCipher + k][l]) != nullptr) {
				//If character in crib does not match the value we have said it should in our key, our key is invalid
				if (CribArray[k][l] != tempCorr[strchr(tempKey, CipherArray[messageCipher][wordCipher + k][l]) - tempKey]) {
					return false;
				}
				//If characters match, keep creating key
				else {
					continue;
				}
			}
			//If crib character hasn't been added to key, add the crib character and corresponding cipher character to key.
			else {
				strncat(tempKey, &CipherArray[messageCipher][wordCipher + k][l], 1);
				strncat(tempCorr, &CribArray[k][l], 1);
			}
		}
	}
	return true;
}

/*
This function assumes that a given word in the ciphertext matches the length of the first word in the crib, and verifies that the lengths
of the following words in the crib match the lengths of the following words in the ciphertext, within the same message of the ciphertext
*/
bool lenMatch(const char CipherArray[][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE], const char CribArray[][MAX_LENGTH_OF_MESSAGE], int lenCrib, int messageCipher, int wordCipher) {
	//Looping through length of crib
	for (int k = 1; k < lenCrib; k++) {
		//If length of a word in crib doesn't match corresponding length of word in ciphertext, return false
		if (strlen(CipherArray[messageCipher][wordCipher + k]) != strlen(CribArray[k])) {
			return false;
		}
	}
	return true;
}

/*
This function, given a cipher key and the ciphertext, prints the partially decoded ciphertext and returns true. 
If the key is empty, prints false.
*/
bool outputMessage(const char encodedLetters[], const char unencodedLetters[], const char ciphertext[]) {
	//If a cipher key was created, output partially decoded result and return true
	if (strlen(encodedLetters) > 0) {
		for (int i = 0; i < strlen(ciphertext); i++) {
			//Initialize char to output as lowercase ciphertext character
			char out = tolower(ciphertext[i]);
			//If the key specifies decoded value for current character, set output to decoded value
			if (strchr(encodedLetters, out) != nullptr) {
				out = toupper(unencodedLetters[strchr(encodedLetters, out) - encodedLetters]);
			}
			cout << out;
		}
		return true;
	}
	return false;
}

/*
This function takes a C String and converts it to a 3D character array with dimensions representing message number, word number,
and character number. The function also stores the number of messages and the lengths of each message in provided parameters.
*/
void clean3D(const char original[], char cleaned[][MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE], int* messages, int meslengths[]) {
	//Initalize holder variables and number of messages
	char temp[MAX_LENGTH_OF_MESSAGE][MAX_LENGTH_OF_MESSAGE] = { {""} };
	int mesChar = 0;
	*messages = 0;
	//Looping through raw message, writing message into a 2D array
	for (int i = 0; i < strlen(original); i++) {
		//If new line character, start writing to the next row and increment the number of messages by 1
		if (original[i] == '\n') {
			temp[*messages][mesChar] = '\0';
			meslengths[*messages] = mesChar;
			mesChar = 0;
			*messages += 1;
		}
		//Write next character to current row of character array
		else {
			temp[*messages][mesChar] = original[i];
			mesChar++;
		}
	}
	//If string does not end with a \n, 
	if (original[strlen(original) - 1] != '\n') {
		temp[*messages][mesChar] = '\0';
		meslengths[*messages] = mesChar;
		mesChar = 0;
		*messages += 1;
	}
	//Looping through messages using same function used to clean crib to clean each bessage
	for (int i = 0; i < *messages; i++) {
		clean2D(temp[i], cleaned[i], &meslengths[i]);
	}
}

/*
This function takes a C String representing a series of words, and returns a 2D array separating each word to a new dimension of the
array. Removes all non-alphabetic characters and converts all characters to lowercase. Stores the number of words in a provided integer.
*/
void clean2D(const char original[], char cleaned[][MAX_LENGTH_OF_MESSAGE], int* length) {
	int row = 0;
	//If first character is a letter, add it lowercase to the cleaned array
	if (isalpha(original[0])) {
		char c = tolower(original[0]);
		strncat(cleaned[row], &c, 1);
	}
	//Looping through the rest of the provided array (crib or message)
	for (int i = 1; i < strlen(original); i++) {
		//Adds character to current string if it is a letter
		if (isalpha(original[i])) {

			//If the crib contains a series of 90 alphabetic characters set the length to an invalid size
			if (strlen(cleaned[row]) == 90) {
				*length = -1;
				return;
			}
			char c = tolower(original[i]);
			strncat(cleaned[row], &c, 1);
		}
		//Moves to the next row of the array, the next string, if the last letter was a letter and current is not a letter
		else if (isalpha(original[i - 1])) {
			row++;
		}
	}
	//Assigns the length of the array to the row number or row number plus one depending on if process ends on empty space or letter
	*length = row;
	if (strlen(original) > 0) {
		if (isalpha(original[strlen(original) - 1])) {
			*length = row + 1;
		}
	}
}