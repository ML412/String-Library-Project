#pragma once
#include "stdafx.h"
/* This is a custom string library that was written as a school project in the Computer Programming II elective of the Electronic Engineering Technology program at
NSCC. This class was taught using C++ and explored Object Oriented Programming with some GUI programming at the end. */

class cString
{
public:
	cString(); //default constructor 
	cString(char*); //overloaded constructor that takes a char pointer
	cString(cString&); //copy constructor
	~cString(); //destructor
	int Stringlen(); //function which returns an integer containing the total number of chars in a string
	void findandreplace(); //this function replaces a word (and all occurences of that word) in a string with a new word
	void removefromString(); //has to remove a RANGE of words (will fail if you only input minpos)
	void insertString(char*); //you said that returning void and just changing the string is fine
	void insertString(cString); //you said that returning void and just changing the string is fine
	void ReverseString(); //student choice
	cString operator+(cString); //for str3 = str1 + str2 and str + char array
	cString operator=(cString&); //overloaded = operator
	bool operator==(cString); //overloaded == operator
	friend cString operator+(char*, cString); //overloaded + operator to add a cString object to a char array
	friend ostream& operator<<(ostream&, cString&); //overloaded function to output a string using cout <<
	friend istream& operator>>(istream&, cString&); //overloaded function to input a string using cin >>
	
private:
	char* _s1;
};

