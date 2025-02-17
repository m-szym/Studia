#include "MinHeapQueue.h"

bool operator<(MinHeapNode n1, MinHeapNode n2)
{
    return n1.getDistance() < n2.getDistance();
}

void MinHeapQueue::enque(int arrIndex, int dist)
{
    queueSize++;

    arr[queueSize].setDistance(dist);
    arr[queueSize].setIndex(arrIndex);
}

int MinHeapQueue::top()
{
    int minDistance = INT_MAX;
    int topIndex = -1;

    for (int i = 0; i <= queueSize; i++) 
    {
        if (minDistance > arr[i].getDistance()) 
        {
            minDistance = arr[i].getDistance();
            topIndex = i;
        }
    }
    return topIndex;
}

void MinHeapQueue::deque()
{
    int topIndex = top();

    for (int i = topIndex; i < queueSize; i++) 
    {
        arr[i] = arr[i + 1];
    }

    queueSize--;
}
