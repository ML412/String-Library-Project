#include "stdafx.h"
#include "cString.h"

cString::cString() //default constructor
{
	_s1 = new char[1000];
	cout << "Default constructor executed." << endl;
}
cString::cString(char* str) //overloaded constructor that takes a char pointer 
{
	_s1 = new char[1000];
	int len = strlen(str);
	for (int i = 0; i <= len; i++)
	{
		_s1[i] = str[i];
	}
	cout << "Object initiated with an existing string" << endl;
}
cString::cString(cString& cpy) //copy constructor
{
     _s1 = new char[1000]; 
	strcpy_s(_s1, 1000, cpy._s1);
	
	cout << "Copy constructor executed." << endl;
}
cString::~cString() //destructor
{
	delete[] _s1; 
	cout << "Default destructor executed." << endl;
}
int cString::Stringlen() //function which returns the length of the string stored in the cString objects private data 
{
	char* p, *np;
	int len = 0;
	p = strtok_s(_s1, "\0", &np);
	while (p != NULL) //run through the tokens and increase len by the number of chars in a token until the pos is NULL
	{
		int tokenlen = strlen(p);
		len += tokenlen;
		p = strtok_s(NULL, " ", &np);
	}
	return len; 
}
void cString::findandreplace() //this function replaces a word (and all occurences of that word) in a string with a new word
{
	int stringlen = strlen(_s1);
	char searchbuff[20];
	char repbuff[20]; 
	char temp[1000]; 
	int wordCount = 0; 

	cout << "Which word would you like to replace?" << endl;
	cin.getline(searchbuff, 20);
	cin.clear();
	cout << "What word would you like to replace it with?" << endl;
	cin.getline(repbuff, 20);
	cin.clear();

	for (int i = 0; _s1[i] != '\0'; i++) 
	{
		if (strstr(&_s1[i], searchbuff) == &_s1[i])
		{
			wordCount++;
		}
	}
	for (int i = 0; i <= 1000; i++) 
	{
		memset(temp, 0, 1);
	}

	char *pos, *nextpos; 
	pos = strtok_s(_s1, " ", &nextpos); 
	strcpy_s(temp, 1000, ""); 
	while (pos != NULL) //loop to parse the string
	{
		if (strcmp(pos, searchbuff) == 0) //if pos == word to be replaced
		{
			strcat_s(temp, 1000, repbuff); //replace word with replaceword word
			strcat_s(temp, 1000, " "); 
		}
		else if (strcmp(pos, searchbuff) != 0) //if pos != word to be replaced
		{
			strcat_s(temp, 1000, pos); //strcat the token into the string
			strcat_s(temp, 1000, " "); 
		}
		pos = strtok_s(NULL, " ", &nextpos); 
	}
	cout << "Replaced " << wordCount << " instances of that word in the string" << endl;
	strcpy_s(_s1, 1000, temp); //write new string to objects private data
}
void cString::removefromString() //this function removes a range of words between the minpos and the maxpos (it doesnt work if you dont input a maxpos)
{
	int stringlen = strlen(_s1); 
	char firstword[20]; 
	char lastword[20]; 
	char temp[1000]; 
	int removelen, newstringlen; 
	
	cout << "Input the range of words to be removed from the string by inputting the first word to be removed and the last." << endl;
	cout << "The current string is as follows: " << endl;
	cout << "Current stringlen = " << stringlen << endl;
	cout << _s1 << endl;
	cout << "First word to be removed?" << endl;
	cin.getline(firstword, 20);
	cin.clear();
	cout << "Last word to be removed?" << endl; 
	cin.getline(lastword, 20);
	cin.clear();

	char* path; 
	path = new char[stringlen];
	for (int i = 0; i <= stringlen; i++) //this is probably redundant 
	{ //copy the contents of _s1[i] into path[i] for use in strtok_s() 
		path[i] = _s1[i]; 
	}

	char* pos, *nextpos; 
	int arrpos = 0; //arrpos is an integer used to track the position of the pointer in a char array
	int minpos, maxpos; //minpos is the point in the array which indicates the beginning of the range of words to be removed and maxpos indicates the last point
	pos = strtok_s(path, " ", &nextpos); 
	while (pos != NULL) //if p is minpos or p is maxpos do not memcpy anything into the string
	{
		int tokenlen = strlen(pos); //tokenlen is the length of the token and is used to increment arrpos
		if (strcmp(pos, firstword) == 0) //if the token equals the first word to be removed, we set minpos as the arrpos - 1 
		{ 
			minpos = arrpos - 1;
		}
		else if (strcmp(pos, lastword) == 0) //if token equals the last word to be removed, we set maxpos = arrpos + the strlen of the lastword buffer
		{
			maxpos = (arrpos + strlen(lastword));
		}
		pos = strtok_s(NULL, " ", &nextpos);
		arrpos += tokenlen + 1; //increment arrpos by the length of the token + 1
	}
	
	removelen = (maxpos - minpos) + 1; //removelen is an integer used to calculate the length of the range of words to be removed
	newstringlen = stringlen - removelen; //newstringlen is used to print the length of the new string to the console for troubleshooting
	//all of these cout statements were used for writing the function and tracking the logic
	cout << "First word detected at index = " << minpos << endl;
	cout << "Last word detected at index = " << maxpos << endl;
	cout << "maxlen - minlen = " << removelen << endl;
	cout << "The new string will be " << newstringlen << " characters long." << endl;
	
	for (int i = 0; i <= stringlen; i++) //I fill temp with whitespace so I do not have to strcat_s whitespace after each write to the string
	{
		memcpy(&temp[i], " ", newstringlen); 
	}

	for (int i = 0; i <= stringlen; i++) //this loop is where the magic of this function happens
	{
		if (i < minpos || i >= maxpos) //conditional statement that runs through the private data before the minpos and after the maxpos
		{
			temp[i] = _s1[i]; //temp[i] = whatever _s1[i] is before the minpos and after the maxpos
		}

		else if (i >= minpos && i <= maxpos) //this conditional statement is used to remove whitespace between the minpos and maxpos
		{
			int subtraction = removelen - 1; //integer used to keep track of how much whitespace is being removed
			while (subtraction != 0) //this loop writes what is in _s1[maxpos] into the temp[minpos] and it runs into removelen has expired
			{ //this loop removes the huge chunk of whitespace that would otherwise be there
				temp[minpos++] = _s1[maxpos++];
				subtraction--;
				i++;
			}
			i += 1; 
		}
		else if (i > maxpos) //write the remainder of the string into temp
		{
			int subtraction = removelen - 1;
			while (subtraction != 0) //here the remainder of _s1 is written into the maxpos of temp
			{
				temp[maxpos++] = _s1[maxpos++];
				subtraction--;
			}
		}
	}
	
	for (int i = 0; i <= strlen(temp); i++) //copy the new string back into the private data of the object (could probably just use strcpy_s but this was more fun)
	{
		_s1[i] = temp[i];
	}
}
void cString::insertString(char* ptr) //this function inserts the contents of a string into an existing string at a specified point
{
	int oldstringlen = strlen(_s1);
	int addlen = strlen(ptr);
	int insertChoice = 0; 
	int wordCount = 0; 
	char ip[20]; 
	char temp2[1000], temp3[1000]; 
	cout << "The current string is: " << _s1 << endl;
	cout << "Please input the word you wish to use as the insertion point for the new string" << endl;
	cin.getline(ip, 20);
	cin.clear();
	cout << "Enter 1 to insert the string for all occurences or 2 for the first occurence" << endl;
	cin >> insertChoice;
	cout << "oldstring = " << oldstringlen << " and addlen = " << addlen << endl;
	strcpy_s(temp2, 1000, ptr);
	for (int i = 0; _s1[i] != '\0'; i++) //this loop parses the private data until the null terminator and keeps track of how many occurences of the insertion word there are
	{
		if (strstr(&_s1[i], ip) == &_s1[i])
		{
			wordCount++;
		}
	}
	for (int i = 0; i <= 1000; i++) //this loop fills temp3 will the null terminator character
	{
		memset(temp3, 0, 1);
	}

	if (insertChoice == 1) //to insert in all occurences
	{
		char* pos, *nextpos; 
		pos = strtok_s(_s1, " ", &nextpos); 
		strcpy_s(temp3, 1000, ""); 
		while (pos != NULL) //parse the string until pos reaches the end
		{
			if (strcmp(pos, ip) != 0) //if pos does not equal the insertion point, strcat pos into the buffer
			{
				strcat_s(temp3, 1000, pos);
				strcat_s(temp3, 1000, " ");
			}
			else if (strcmp(pos, ip) == 0) //if pos does equal the insertion point...
			{
				strcat_s(temp3, 1000, ip); //strcat the insertion word into temp3
				strcat_s(temp3, 1000, " "); 
				strcat_s(temp3, 1000, temp2); 
				strcat_s(temp3, 1000, " "); 
			}
			pos = strtok_s(NULL, " ", &nextpos);
		}
	}
	
	else if (insertChoice == 2) //insert once
	{
		char* pos, *nextpos; 
		int subcount = wordCount; //subcount is an integer use to ensure that the new string is inserted only once
		pos = strtok_s(_s1, " ", &nextpos); 
		strcpy_s(temp3, 1000, ""); 
		while (pos != NULL) //parse the string until pos reaches the end
		{
			if (strcmp(pos, ip) != 0) //if pos does not equal the insertion point, strcat pos into the buffer
			{
				strcat_s(temp3, 1000, pos);
				strcat_s(temp3, 1000, " ");
			}
			else if (strcmp(pos, ip) == 0) //if pos does equal the insertion point...
			{
				if (subcount >= wordCount) //this conditional statement can only be true for the first write of temp2 into temp3
				{
					strcat_s(temp3, 1000, ip); //strcat the insertion point into temp3
					strcat_s(temp3, 1000, " "); 
					strcat_s(temp3, 1000, temp2); //add the new string to temp3
					strcat_s(temp3, 1000, " "); 
					subcount--; //subcount now equals the word count and this statement can not be true again
				}
				else if (subcount < wordCount) //subcount is now less than wordCount
				{
					strcat_s(temp3, 1000, pos); //strcat the token into temp3
					strcat_s(temp3, 1000, " "); 
				}
			}
			pos = strtok_s(NULL, " ", &nextpos);
		}
	}
	strcpy_s(_s1, 1000, temp3); //copy the new string into the objects private data
}
void cString::insertString(cString obj) //this function inserts the contents of a string into an existing string at a specified point
{
	int oldstringlen = strlen(_s1);
	int addlen = strlen(obj._s1); 
	int insertChoice = 0; 
	int wordCount = 0; 
	char ip[20]; 
	char temp2[1000], temp3[1000]; 
	cout << "The current string is: " << _s1 << endl;
	cout << "Please input the word you wish to use as the insertion point for the new string" << endl;
	cin.getline(ip, 20);
	cin.clear();
	cout << "Enter 1 to insert the string for all occurences or 2 for the first occurence" << endl;
	cin >> insertChoice;
	cout << "oldstring = " << oldstringlen << " and addlen = " << addlen << endl;
	strcpy_s(temp2, 1000, obj._s1);
	for (int i = 0; _s1[i] != '\0'; i++) //this loop parses the private data until the null terminator and keeps track of how many occurences of the insertion word there are
	{
		if (strstr(&_s1[i], ip) == &_s1[i])
		{
			wordCount++;
		}
	}
	for (int i = 0; i <= 1000; i++) //this loop fills temp3 will the null terminator character
	{
		memset(temp3, 0, 1);
	}

	if (insertChoice == 1) //to insert in all occurences
	{
		char* pos, *nextpos; 
		pos = strtok_s(_s1, " ", &nextpos); 
		strcpy_s(temp3, 1000, ""); 
		while (pos != NULL) 
		{
			if (strcmp(pos, ip) != 0) //if pos does not equal the insertion point, strcat pos into the buffer
			{
				strcat_s(temp3, 1000, pos);
				strcat_s(temp3, 1000, " ");
			}
			else if (strcmp(pos, ip) == 0) //if pos does equal the insertion point...
			{
				strcat_s(temp3, 1000, ip); //strcat the insertion word into temp3
				strcat_s(temp3, 1000, " "); 
				strcat_s(temp3, 1000, temp2); //strcat the string to be inserted into temp3
				strcat_s(temp3, 1000, " "); 
			}
			pos = strtok_s(NULL, " ", &nextpos);
		}
	}

	else if (insertChoice == 2) //insert once
	{
		char* pos, *nextpos; 
		int subcount = wordCount; //subcount is an integer use to ensure that the new string is inserted only once
		pos = strtok_s(_s1, " ", &nextpos); 
		strcpy_s(temp3, 1000, ""); 
		while (pos != NULL) //parse the string until pos reaches the end
		{
			if (strcmp(pos, ip) != 0) //if pos does not equal the insertion point, strcat pos into the buffer
			{
				strcat_s(temp3, 1000, pos);
				strcat_s(temp3, 1000, " ");
			}
			else if (strcmp(pos, ip) == 0) //if pos does equal the insertion point...
			{
				if (subcount >= wordCount) //this conditional statement can only be true for the first write of temp2 into temp3
				{
					strcat_s(temp3, 1000, ip); //strcat the insertion point into temp3
					strcat_s(temp3, 1000, " "); 
					strcat_s(temp3, 1000, temp2); //add the new string to temp3
					strcat_s(temp3, 1000, " "); 
					subcount--; //subcount now equals the word count and this statement can not be true again
				}
				else if (subcount < wordCount) //subcount is now less than wordCount
				{
					strcat_s(temp3, 1000, pos); //strcat the token into temp3
					strcat_s(temp3, 1000, " "); 
				}
			}
			pos = strtok_s(NULL, " ", &nextpos);
		}
	}
	strcpy_s(_s1, 1000, temp3); //copy the new string into the objects private data
}
void cString::ReverseString() //function to reverse the order of the characters in an objects private data
{
	int stringlen = strlen(_s1); 
	char temp1[1000], temp2[1000]; 
	strcpy_s(temp1, 1000, _s1); 
	int maxpos = stringlen; 
	memset(temp2, 0, 1000); 
	for (int i = 0; i < maxpos; i++) 
	{
		temp2[i] = temp1[stringlen - 1]; 
		stringlen--; 
	}
	strcpy_s(_s1, 1000, temp2); //copy the reversed string back into the objects private data
}
cString cString::operator+(cString obj) //for str3 = str1 + str2 and str + char array
{
	cString sum; 
	int len = strlen(this->_s1) + strlen(obj._s1) + 1; 
	sum._s1 = new char[len+1]; 
    strcpy_s(sum._s1, len + 1, this->_s1); 
	strcat_s(sum._s1, len + 1, " "); 
	strcat_s(sum._s1, len + 1, obj._s1); 
	return sum;
}
cString cString::operator=(cString& cpy) //overloaded = operator to set one cString equal to another cString
{
	int len = strlen(cpy._s1); 
	for (int i = 0; i <= len; i++) 
	{
		 *(this->_s1 + i) = *(cpy._s1 + i); 
	}
	return *this; 
}
bool cString::operator==(cString cpy) //overloaded == operator 
{
	int stringlen = strlen(this->_s1); 
	int cpylen = strlen(cpy._s1);
	int wordDiff = 0;
	char temp1[1000]; 
	char temp2[1000];  
	char wordlist[1000]; 
	strcpy_s(temp1, 1000, this->_s1); 
	strcpy_s(temp2, 1000, cpy._s1); 
	
	char *pos, *nextpos; 
	char *pos2, *nextpos2;
	pos = strtok_s(temp1, " ", &nextpos); 
	pos2 = strtok_s(temp2, " ", &nextpos2);
	strcpy_s(wordlist, 1000, ""); 
	while (pos != NULL && pos2 != NULL) 
	{
		if (strcmp(pos, pos2) != 0) //if pos != pos2, strcat the word from pos2 into the wordlist and increase the integer for the number of different words
		{
			strcat_s(wordlist, 1000, pos2);
			strcat_s(wordlist, 1000, " ");
			wordDiff++;
		}
		pos = strtok_s(NULL, " ", &nextpos);
		pos2 = strtok_s(NULL, " ", &nextpos2);
	}
	cout << "Found " << wordDiff << " differeces in words in these two strings" << endl;
	char *pos3, *nextpos3; //for use with another strtok_s
	pos3 = strtok_s(wordlist, " ", &nextpos3);
	cout << "The following words were not contained in the SAME POSITION as the 'this' string:" << endl;
	while (pos3 != NULL)
	{
		cout << pos3 << endl; 
		pos3 = strtok_s(NULL, " ", &nextpos3);
	}
	if (strcmp(this->_s1, cpy._s1) == 0) 
	{
		return true;
	}
	else
	{
		return false;
	}
}


