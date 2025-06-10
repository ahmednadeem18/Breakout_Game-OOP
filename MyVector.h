#pragma once
#pragma once
#include <iostream>
using namespace std;

template <class type>
class MyVector {
private:
    type* arr;
    int len;
    int cap;

    void double_cap() {
        this->cap = this->cap * 2 + 1;
        type* newArr = new type[this->cap];
        for (int i = 0; i < this->len; i++) {
            newArr[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = newArr;
    }


public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector(int count, type value);
    ~MyVector();

    MyVector& operator=(const MyVector& other);
    const type& operator[](int index) const;
    type& operator[](int index);
    bool operator==(const MyVector& other) const;
    bool operator!=(const MyVector& other) const;
    MyVector operator+(const MyVector& other) const;
    MyVector& operator+=(const MyVector& other);

    void push(type value);
    void pop();
    void insert_at(int index, type value);
    void delete_at(int index);
    void reserve(int new_cap);
    void clear();
    void swap(MyVector& other);
    void shrink_to_fit();
    void reverse();
    bool empty() const;
    int size() const;
    type& at(int index);
    const type& at(int index) const;
    type& front();
    const type& front() const;
    type& back();
    const type& back() const;
    int find(type value) const;
    void display();



};

template <class type>
MyVector<type>::MyVector() : len(0), cap(1) {
    arr = new type[cap];
    
}

template <class type>
MyVector<type>::MyVector(const MyVector& other) : len(other.len), cap(other.cap) {
    arr = new type[cap];
    for (int i = 0; i < other.len; i++) {
        arr[i] = other.arr[i];
    }
}

template <class type>
MyVector<type>::MyVector(int count, type value) : len(count), cap(count) {
    arr = new type[cap];
    for (int i = 0; i < len; i++) {
        arr[i] = value;
    }
}

template <class type>
MyVector<type>::~MyVector() {
    delete[] arr;
}

template <class type>
MyVector<type>& MyVector<type>::operator=(const MyVector& other) {
    if (this == &other) {
        return *this;
    }
    delete[] arr;
    len = other.len;
    cap = other.cap;
    arr = new type[cap];
    for (int i = 0; i < len; i++) {
        arr[i] = other.arr[i];
    }
    return *this;
}

template <class type>
const type& MyVector<type>::operator[](int index) const {
    if (index > -1 && index < len)
        return arr[index];
    throw out_of_range("Invalid index");
}

template <class type>
type& MyVector<type>::operator[](int index) {
    if (index > -1 && index < len)
        return arr[index];
    throw out_of_range("Invalid index");
}

template <class type>
bool MyVector<type>::operator==(const MyVector& other) const {
    if (len != other.len)
        return false;
    for (int i = 0; i < len; i++) {
        if (arr[i] != other.arr[i])
            return false;
    }
    return true;
}

template <class type>
bool MyVector<type>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template <class type>
MyVector<type> MyVector<type>::operator+(const MyVector& other) const {
    MyVector<type> resArr = *this;
    for (int i = 0; i < other.len; i++) {
        if (resArr.len == resArr.cap)
            resArr.double_cap();
        resArr.arr[resArr.len] = other.arr[i];
        resArr.len++;
    }
    return resArr;
}

template <class type>
MyVector<type>& MyVector<type>::operator+=(const MyVector& other) {
    for (int i = 0; i < other.len; i++) {
        if (len == cap)
            double_cap();
        arr[len++] = other.arr[i];
    }
    return *this;
}

template <class type>
void MyVector<type>::push(type value) {
    if (len == cap)
        double_cap();
   
    arr[len] = value;
    len++;
}

template <class type>
void MyVector<type>::pop() {
    if (len > 0) {
        len--;
    }
}

template <class type>
void MyVector<type>::insert_at(int index, type value) {
    if (len == cap)
        double_cap();
    for (int i = len; i > index; i--)
        arr[i] = arr[i - 1];
    arr[index] = value;
    len++;
}

template <class type>
void MyVector<type>::delete_at(int index) {
    for (int i = index; i < len - 1; i++)
        arr[i] = arr[i + 1];
    len--;
}

template <class type>
void MyVector<type>::reserve(int new_cap) {
    if (new_cap == cap) return;
    if (new_cap > cap) {
        type* newArr = new type[new_cap];
        for (int i = 0; i < len; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        cap = new_cap;
    }
    else {
        throw out_of_range("LESS cap THAN THE ACTUAL ONE");
    }
}

template <class type>
void MyVector<type>::clear() {
    len = 0;
    delete[] arr;
    arr = new type[len];
}

template <class type>
void MyVector<type>::swap(MyVector& other) {
    MyVector<type> temp = *this;
    *this = other;
    other = temp;
}

template <class type>
void MyVector<type>::shrink_to_fit() {
    cap = len;
    type* newArr = new type[cap];
    for (int i = 0; i < len; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}

template <class type>
void MyVector<type>::reverse() {
    int p1 = 0, p2 = len - 1;
    while (p1 < p2) {
        type temp = arr[p1];
        arr[p1] = arr[p2];
        arr[p2] = temp;
        p1++;
        p2--;
    }
}

template <class type>
bool MyVector<type>::empty() const {
    return len == 0;
}

template <class type>
int MyVector<type>::size() const {
    return len;
}

template <class type>
type& MyVector<type>::at(int index) {
    return arr[index];
}

template <class type>
const type& MyVector<type>::at(int index) const {
    return arr[index];
}

template <class type>
type& MyVector<type>::front() {
    return arr[0];
}

template <class type>
const type& MyVector<type>::front() const {
    return arr[0];
}

template <class type>
type& MyVector<type>::back() {
    return arr[len - 1];
}

template <class type>
const type& MyVector<type>::back() const {
    return arr[len - 1];
}

template <class type>
int MyVector<type>::find(type value) const {
    for (int i = 0; i < len; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

template <class type>
void MyVector<type>::display() {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

