#pragma once
#include <iostream>
#include <stdexcept>
#include "Graphs.h"

using namespace std;

template <typename T>
class MinHeapPriorityQueue {
private:
    int MAX_SIZE;
    T* heap;
    int size{};

    void heapifyUp() {
        int index = size - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown() {
        int index = 0;
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < size && heap[leftChild] < heap[smallest]) {
                smallest = leftChild;
            }

            if (rightChild < size && heap[rightChild] < heap[smallest]) {
                smallest = rightChild;
            }

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    MinHeapPriorityQueue(int MAX_SIZE) : size(0) {
        this->MAX_SIZE = MAX_SIZE;
        heap = new T[MAX_SIZE];
    }

    // Insert an element into the priority queue
    void push(T element) {
        if (size >= MAX_SIZE) {
            //cout << "Priority Queue is Full" << endl; 
            //<<-- yahan pe continuously repeated times iss e ye print kia tha console pe 
            //tabhi i added just return statement
            return;
        }
        else {
            heap[size] = element;
            size++;
            heapifyUp();
        }
    }

    // Remove and return the smallest element from the priority queue
    T pop() {
        if (size == 0) {
            cout << "Priority Queue is Empty" << endl;
        }
        else {
            T top = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapifyDown();
            return top;
        }
    }

    // Get the size of the priority queue
    int getSize() const {
        return size;
    }
};

