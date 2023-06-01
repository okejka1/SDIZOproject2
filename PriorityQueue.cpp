#include <iostream>
#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int nOfEdges) {
    heap = new Edge[nOfEdges];
    size = 0;
}
PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

PriorityQueue::Edge PriorityQueue::front() {
    return heap[0];
}

void PriorityQueue::push(PriorityQueue::Edge e) {

        size++;
        int i;
        i = size - 1;
        heap[i] = e;

        while (i != 0 && heap[parent(i)].weight > heap[i].weight) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);

        }

    }


    PriorityQueue::Edge PriorityQueue::pop() {

        if (size == 1) {
            size--;
            return heap[0];
        }
        Edge root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;


    }



void PriorityQueue::swap(PriorityQueue::Edge &a, PriorityQueue::Edge &b) {
    Edge temp;
    temp = a;
    a = b;
    b = temp;
}

int PriorityQueue::parent(int i) {
    return (i - 1) / 2;
}

int PriorityQueue::left(int i) {
    return 2 * i + 1;
}

int PriorityQueue::right(int i) {
    return 2 * i + 2;
}

void PriorityQueue::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallestW = i;


    if ((l < size) && (heap[l].weight < heap[i].weight)) {
        smallestW = l;
    } else {
        smallestW = i;
    }
    if ((r < size) && (heap[r].weight < heap[smallestW].weight)) {
        smallestW = r;
    }
    if (i != smallestW) {
        swap(heap[i], heap[smallestW]);
        heapify(smallestW);
    }
}






