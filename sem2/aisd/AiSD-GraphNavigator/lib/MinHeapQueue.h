#pragma once
#include <climits>


const int MAX_INDEX = INT_MAX;

class MinHeapNode {
private:
    int distance;
    int arrIndex;

public:
    MinHeapNode(int i = -1, int d = MAX_INDEX) {
        distance = d;
        arrIndex = i;
    }

    void setNode(int i, int d) {
        this->distance = d;
        this->arrIndex = i;
    }

    int getDistance() {
        return distance;
    }

    int getIndex() {
        return arrIndex;
    }

    void setDistance(int d) {
        distance = d;
    }

    void setIndex(int i) {
        arrIndex = i;
    }
};

bool operator<(MinHeapNode node1, MinHeapNode node2);

class MinHeapQueue {
private:
    MinHeapNode* arr;
    int queueSize;
    
public:
    MinHeapQueue(int size = 0) {
        arr = new MinHeapNode[size];
        queueSize = -1;
    }

    ~MinHeapQueue() {
        delete[] arr;
    }

    MinHeapNode& operator[](int index) {
        return arr[index];
    }

    void enque(int arrIndex, int dist);
    int top();
    void deque();

    int getQueueSize() {
        return queueSize;
    }
};
