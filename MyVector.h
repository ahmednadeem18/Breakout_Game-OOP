#ifndef MYVECTOR_H
#define MYVECTOR_H

template <class T>
class MyVector {
private:
    T* data;
    int size;
    int capacity;

    void resizeCapacity() {
        this->capacity = this->capacity * 2 + 1;
        T* newData = new T[this->capacity];
        for (int i = 0; i < this->size; i++) {
            newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
    }

public:
    MyVector() : size(0), capacity(250) {
        data = new T[capacity];
    }

    ~MyVector() {
        delete[] data;
    }

    void pushBack(T value) {
        if (size == capacity) resizeCapacity();
        data[size++] = value;
    }

    void popBack() {
        if (size > 0) size--;
    }

    void removeAt(int index) {
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void clear() {
        size = 0;
    }

    T& at(int index) {
        return data[index];
    }

    const T& at(int index) const {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

#endif