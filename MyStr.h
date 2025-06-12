#ifndef MyStr_H
#define MyStr_H
#include<iostream>
using namespace std;

class MyStr {
private:
	int len;
	int cap;
	char* charString;
	int str_len(const char* Arr);
public:
	
	MyStr();
	// coverstion Constructor
	MyStr(const char* Arr);
	// Parameterized Constructor 1
	MyStr(char* _MyStr);
	// Parameterized Constructor 2
	MyStr(int size, int _cap);
	MyStr(const MyStr& _str);
	// int to string constructor
	MyStr(char a, int size);
	// itos Constructor
	MyStr(int num);

	// Assignment Operator
	MyStr& operator=(const MyStr& right);
	//index Operators
	const char operator [] (int index) const;
	char& operator [] (int index);
	//Eqaulity Operator
	bool operator == (const MyStr& str) const;
	char* ToCharArray() const;
	//less then check Operator
	bool operator<(const MyStr& str) const;
	//Greater then check Operator
	bool operator>(const MyStr& str) const;


	int FindFirst(const char& a)const;
	int FindLast(const char& a)const;
	int* FindAll(const char& a, int& size);
	int* SearchAllSubstrings(const char* subStr, int& count);
	int SubStrSearchFirst(const char* subStr);
	int SubStrSearchLast(const char* subStr);



	MyStr& removeCharFirst(const char& a);
	MyStr& removeCharLast(const char& a);
	MyStr& removeAllChar(const char& a);


	friend MyStr operator + (MyStr s1, MyStr s2);
	MyStr& AppendArray(const MyStr& str);



	MyStr& InsertChar(const char& a, const int& index);
	MyStr& InsertCharString(const char* arr, const int& index);


	MyStr& toLower();
	MyStr& toUpper();


	 // function with the prototype
	MyStr& Trimm();


	//              ---Splitting Functions---
	bool isPresent(const char& ch, const char* chArr) const;
	MyStr* split(const char& ch, int& count);
	MyStr* Tokenize(const char* chArr, int& count);

	//              ---Regrow Functions---
	MyStr RegrowArr();
	int* regrowInt(int* arr, int& size);
	//              ---Friend Functions---
	friend ostream& operator << (ostream& os, const MyStr& _str);
	friend istream& operator >> (istream& os, MyStr& str);



	//              ---Other Functions---

	void clear();
	bool isAvail(const char& ch) const;
	int StringToInt();
	MyStr IntToString(int num);
	void ReplaceFirst(char c);
	const char charstring(int i);
	MyStr& operator=(const char* right);
	void convertionToChar(const int num, char arr[]);

	void display() const;

	~MyStr();
};

#endif

