#include<iostream>
#include"MyStr.h"

int MyStr::str_len(const char* Arr) {
	int i = 0;
	for (i = 0; Arr[i] != '\0'; i++) {}
	return i;
}

MyStr::MyStr() {
	this->cap = 1;
	this->len = 0;
	this->charString = new char[this->cap];
}

MyStr::MyStr(const char* Arr) {
	this->cap = str_len(Arr);
	this->len = str_len(Arr);
	this->charString = new char[this->cap];
	for (int i = 0; i < this->len; i++) {
		this->charString[i] = Arr[i];
	}
}

MyStr::MyStr(char* _MyStr) {
	this->len = str_len(_MyStr);
	this->cap = str_len(_MyStr);
	this->charString = new char[this->cap] {'\0'};
	for (int i = 0; i < this->len; i++) {
		this->charString[i] = _MyStr[i];
	}
	if (len == cap)
		*this = RegrowArr();
	this->charString[len] = { '\0' };
}
// Parameterized Constructor 2
MyStr::MyStr(int size, int _cap) {
	this->len = size;
	this->cap = _cap;
	this->charString = new char[this->cap] {'\0'};
	this->charString[this->len] = '\0';
}
//Copy Constructor
MyStr::MyStr(const MyStr& _str) {
	this->len = _str.len;
	this->cap = _str.cap;
	this->charString = new char[_str.cap + 1] {'\0'};
	for (int i = 0; i < this->len; i++) {
		this->charString[i] = _str.charString[i];
	}
	this->charString[this->len] = '\0';
}

// int to string constructor
MyStr::MyStr(char a, int size) {
	this->len = size;
	this->cap = size;
	this->charString = new char[this->cap] {'\0'};
	for (int i = 0; i < this->len; i++) {
		this->charString[i] = a;
	}
}
// itos Constructor
MyStr::MyStr(int num) {
	this->len = 0;
	this->cap = 0;
	this->charString = new char[this->cap + 1] {'\0'};
	*this = IntToString(num);
}

//----------------------Operators---------------------------
// Assignment Operator
MyStr& MyStr::operator=(const MyStr& right) {
	if (this == &right) {
		return *this;
	}
	delete[] this->charString;
	this->len = right.len;
	this->cap = right.cap;
	this->charString = new char[this->cap + 1];
	for (int i = 0; i < this->len; i++) {
		this->charString[i] = right.charString[i];
	}
	this->charString[this->len] = '\0';
	return *this;
}

//index Operators
const char MyStr::operator [] (int index) const {
	if (index > -1 && index < len)
		return *(this->charString + index);
	throw::out_of_range("invlaid data accez");
}
char& MyStr::operator [] (int index) {
	if (index > -1 && index < len)
		return *(this->charString + index);
	throw::out_of_range("invlaid data accez");
}
//Eqaulity Operator
bool MyStr::operator == (const MyStr& str) const {
	if (this->len != str.len)
		return false;

	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] != str.charString[i])
			return false;
	}
	return true;
}
char* MyStr::ToCharArray() const {
	char* result = new char[this->len + 1];
	for (size_t i = 0; i < this->len; i++) {
		result[i] = this->charString[i];
	}
	result[this->len] = '\0';
	return result;
}

//less then check Operator
bool MyStr::operator<(const MyStr& str) const {
	for (int i = 0; i < this->len && i < str.len; i++) {
		if (this->charString[i] < str.charString[i]) {
			return true;
		}
		if (this->charString[i] > str.charString[i]) {
			return false;
		}
	}
	if (this->len < str.len) {
		return true;
	}
	return false;
}
//Greater then check Operator
bool MyStr::operator>(const MyStr& str) const {
	for (int i = 0; i < this->len && i < str.len; i++) {
		if (this->charString[i] > str.charString[i]) {
			return true;
		}
		if (this->charString[i] < str.charString[i]) {
			return false;
		}
	}
	if (this->len > str.len) {
		return true;
	}
	return false;
}


//----------------------------Functions--------------------------

//              ---Searching Functions---

int MyStr::FindFirst(const char& a)const {
	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] == a) {
			return i;
		}
	}
	return -1;
}
int MyStr::FindLast(const char& a)const {
	for (int i = len - 1; i > -1; i--) {
		if (charString[i] == a) {
			return i;
		}
	}
	return -1;
}
int* MyStr::FindAll(const char& a, int& size) {
	size = 0;
	int* count = new int[size];
	for (int i = this->len - 1; i > -1; i--) {
		if (this->charString[i] == a) {
			count = regrowInt(count, size);
			count[size - 1] = i;
		}
	}
	return count;
}
int* MyStr::SearchAllSubstrings(const char* subStr, int& count) {
	int sublen = str_len(subStr);
	count = 0;
	int* indices = new int [count] {};
	bool flag = false;
	int existence = 0;
	int k = 0;
	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] == subStr[k]) {
			existence++;
			k++;
			if (existence == sublen) {
				indices = regrowInt(indices, count);
				indices[count - 1] = i - sublen + 1;
			}
		}
		else {
			k = 0;
			existence = 0;
		}
	}
	return indices;
}
int MyStr::SubStrSearchFirst(const char* subStr) {
	int sublen = str_len(subStr);
	if (sublen > this->len)
		return -1;
	int existence = 0;
	int k = 0;
	for (int i = 0; i < this->len; i++) {
		if (charString[i] == subStr[k]) {
			existence++;
			k++;
			if (existence == sublen) {
				return i - sublen + 1;
			}
		}
		else {
			k = 0;
			existence = 0;
		}
	}
	return -1;
}
int MyStr::SubStrSearchLast(const char* subStr) {
	int sublen = str_len(subStr);
	if (sublen > this->len)
		return -1;
	int existence = 0;
	int k = sublen - 1;
	for (int i = this->len - 1; i >= 0; i--) {
		if (charString[i] == subStr[k]) {
			existence++;
			k--;
			if (existence == sublen) {
				return i;
			}
		}
		else {
			k = sublen - 1;
			existence = 0;
		}
	}
	return -1;
}

//              ---Removing Functions---

MyStr& MyStr::removeCharFirst(const char& a) {
	int index;
	index = FindFirst(a);
	if (index == -1)
		return *this;
	for (int i = index; i < this->len - 1; i++) {
		this->charString[i] = this->charString[i + 1];
	}
	this->charString[this->len - 1] = '\0';
	this->len--;
	return *this;
}
MyStr& MyStr::removeCharLast(const char& a) {
	int index = FindLast(a);
	if (index == -1)
		return *this;
	for (int i = index; i < this->len - 1; i++) {
		this->charString[i] = this->charString[i + 1];
	}
	this->charString[this->len - 1] = '\0';
	this->len--;
	return *this;
}

MyStr& MyStr::removeAllChar(const char& a) {
	int size = 0;
	int* indexArr = FindAll(a, size);
	for (int i = 0; i < size; i++) {
		*this = removeCharFirst(a);
		this->len--;
	}
	return *this;
}

//              ---String Concatenation---

MyStr operator+(MyStr s1, MyStr s2) {

	MyStr concatArr(s1.len + s2.len, s1.len + s2.len + 1);
	int i = 0;
	for (i = 0; i < s1.len; i++)
		concatArr.charString[i] = s1.charString[i];
	for (int j = 0; j < s2.len; i++, j++)
		concatArr.charString[i] = s2.charString[j];
	return concatArr;
}
MyStr& MyStr::AppendArray(const MyStr& str) {
	int i = 0;
	for (int j = 0; j < str.len; i++, j++) {
		if (this->len == cap)
			*this = RegrowArr();
		charString[len] = str.charString[j];
		this->len++;
	}
	return *this;
}

//              ---Inserting Functions---

MyStr& MyStr::InsertChar(const char& a, const int& index) {
	if (this->cap == this->len) {
		*this = RegrowArr();
		this->len++;
	}
	for (int i = this->len; i > index; i--) {
		this->charString[i + 1] = this->charString[i];
	}
	this->charString[index] = a;
	return *this;
}
MyStr& MyStr::InsertCharString(const char* arr, const int& index) {
	this->len = this->len + str_len(arr);
	while (this->cap <= this->len) {
		*this = RegrowArr();
	}
	for (int i = this->len - str_len(arr); i >= index; i--) {

		this->charString[i + str_len(arr)] = charString[i];
	}
	int k = 0;
	for (int i = index; i < index + str_len(arr); i++) {
		this->charString[i] = arr[k];
		k++;
	}
	return *this;
}

//              ---Special Functions---

MyStr& MyStr::toLower() {
	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] >= 'A' && this->charString[i] <= 'Z') {
			this->charString[i] = this->charString[i] + 32;
		}
	}
	return *this;
}
MyStr& MyStr::toUpper() {
	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] >= 'a' && this->charString[i] <= 'z') {
			this->charString[i] = this->charString[i] - 32;
		}
	}
	return *this;
}

//              ---Trim Functions---

MyStr& MyStr::Trimm() {
	for (int i = 0; i < this->len; i++) {
		if ((this->charString[i] >= 'a' && this->charString[i] <= 'z') ||
			(this->charString[i] >= 'A' && this->charString[i] <= 'Z')) {
			break;
		}
		for (int j = i; j < this->len - 1; j++) {
			this->charString[j] = this->charString[j + 1];
		}
		this->len--;
		i--;
	}

	for (int i = this->len - 1; i >= 0; i--) {
		if ((this->charString[i] >= 'a' && this->charString[i] <= 'z') ||
			(this->charString[i] >= 'A' && this->charString[i] <= 'Z')) {
			break;
		}
		this->len--;
	}
	charString[this->len] = '\0';
	return *this;
}

//              ---Splitting Functions---

MyStr* MyStr::split(const char& ch, int& count) {
	count = 1;
	bool flag = false;
	int a = this->len;
	for (int i = 0; i < this->len; i++) {
		if (charString[i] == ch) {
			flag = false;
		}
		else if (!flag) {
			count++;
			flag = true;
		}
	}
	MyStr* splitArr = new MyStr[count];
	for (int i = 0; i < count; i++) {
		splitArr[i].charString = new char[100] {'\0'};
	}
	int index = 0;
	int k = 0;

	for (int i = 0; i < this->len; i++) {
		if (charString[i] != ch) {
			flag = false;
			splitArr[index].len++;
			splitArr[index].cap++;
			splitArr[index].charString[k] = this->charString[i];
			splitArr[index].charString[k + 1] = '\0';
			k++;
		}
		else {
			k = 0;
			if (!flag) {
				index++;
				flag = true;
			}
		}
	}
	return splitArr;
}
MyStr* MyStr::Tokenize(const char* chArr, int& count) {
	count = 0;
	bool flag = false;

	for (int i = 0; i < this->len; i++) {
		if (isPresent(charString[i], chArr)) {
			flag = false;
		}
		else if (!flag) {
			count++;
			flag = true;
		}
	}
	MyStr* splitArr = new MyStr[count];
	for (int i = 0; i < count; i++) {
		splitArr[i].charString = new char[100] {'\0'};
	}
	int index = 0;
	int k = 0;
	for (int i = 0; i < this->len; i++) {
		if (isPresent(charString[i], chArr)) {
			if (k > 0) {
				splitArr[index].charString[k] = '\0';
				index++;
				k = 0;
			}
		}
		else {
			splitArr[index].len++;
			splitArr[index].cap++;
			splitArr[index].charString[k] = charString[i];
			k++;
		}
	}
	return splitArr;
}
bool MyStr::isPresent(const char& ch, const char* chArr) const {
	for (int i = 0; chArr[i] != '\0'; i++) {
		if (ch == chArr[i])
			return true;
	}
	return false;
}

MyStr MyStr::RegrowArr() {
	MyStr _str{ *this };
	_str.len = this->len;
	_str.cap = 2 * (this->len) + 1;
	delete[] _str.charString;
	_str.charString = new char[_str.cap + 1] {'\0'};
	for (int i = 0; i < this->len; i++) {
		_str.charString[i] = this->charString[i];
	}
	_str.charString[this->len] = '\0';
	return _str;
}
int* MyStr::regrowInt(int* arr, int& size) {
	int* newArr = new int[size + 1];
	for (int i = 0; i < size; i++) {
		newArr[i] = arr[i];
	}
	size++;
	delete[] arr;
	return newArr;
}
void MyStr::display() const {
	for (int i = 0; i < len; i++) {
		cout << charString[i];
	}
}

//              ---Friend Functions---
ostream& operator << (ostream& os, const MyStr& _str) {
	for (int i = 0; i < _str.len; i++) {
		os << _str.charString[i];
	}
	return os;
}

//              ---Other Functions---

void MyStr::clear() {

	delete[] this->charString;
	this->len = 0;
	this->cap = 0;
	this->charString = nullptr;
}
bool MyStr::isAvail(const char& ch) const {
	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] == ch)
			return true;
	}
	return false;
}
int MyStr::StringToInt() {
	int n = 0;
	int sum = 0;
	bool flag = false;
	for (int i = 0; i < this->len; i++) {
		if (this->charString[i] == '-') {
			flag = true;
			i++;
		}
		n = this->charString[i] - '0';
		sum = sum * 10 + n;
	}
	if (flag) {
		sum = sum * -1;
	}
	return sum;
}
MyStr MyStr::IntToString(int num) {

	while (num != 0) {
		if (this->len == this->cap) {
			*this = RegrowArr();
		}

		int n = num % 10;
		this->charString[len] = n + '0';
		num /= 10;
		this->len++;
	}
	int templen = this->len;
	for (int i = 0; i < templen; i++) {
		int temp = charString[i];
		charString[i] = charString[templen - 1];
		charString[templen - 1] = temp;
		templen--;
	}
	charString[this->len] = '\0';
	return *this;
}
void MyStr::ReplaceFirst(char c) {
	this->charString[0] = c;
}


MyStr::~MyStr() {

	delete[] this->charString;
}
istream& operator >> (istream& os, MyStr& str) {
	if (str.charString != nullptr) {
		delete[] str.charString;

	}
	str.charString = new char[50] {'\0'};
	os >> str.charString;
	str.len = str.str_len(str.charString);
	int a = str.len;
	str.cap = str.len;
	return os;
}
void MyStr::convertionToChar(const int num, char arr[]) {
	int temp = num;
	int digits = 0;

	if (temp == 0) {
		arr[0] = '0';
		arr[1] = '\0';
		return;
	}
	while (temp > 0) {
		temp /= 10;
		digits++;
	}
	arr[digits] = '\0';
	temp = num;
	while (temp > 0) {
		arr[--digits] = (temp % 10) + '0';
		temp /= 10;
	}
}

const char MyStr::charstring(int i) {
	return charString[i];

}

MyStr& MyStr::operator=(const char* right) {
	if (this->charString == right) {
		return *this;
	}
	delete[] this->charString;
	this->len = str_len(right);
	this->cap = this->len;
	this->charString = new char[this->cap + 1];
	for (size_t i = 0; i < this->len; ++i) {
		this->charString[i] = right[i];
	}
	this->charString[this->len] = '\0';

	return *this;
}






