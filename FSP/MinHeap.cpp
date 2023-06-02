#include <iostream>
#include "MinHeap.h"


MinHeap::MinHeap(int capacity) {
    this->capacity = capacity;
    heap = new Node[capacity];
    positions = new int[capacity];
    size = 0;
}

MinHeap::~MinHeap() {
    delete[] heap;
    delete[] positions;
    size = 0;
}

int MinHeap::parent(int i) {
    return (i - 1) / 2;
}

int MinHeap::left(int i) {
    return 2 * i + 1;
}

int MinHeap::right(int i) {
    return 2 * i + 2;
}

void MinHeap::swap(MinHeap::Node &a, MinHeap::Node &b) {
    std::swap(a, b);
    int tmp = positions[a.vertex];
    positions[a.vertex] = positions[b.vertex];
    positions[b.vertex] = tmp;
}

void MinHeap::heapifyUp(int i) {
    while (i != 0 && heap[parent(i)].distance > heap[i].distance) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::heapifyDown(int i) {
    int l = left(i);
    int r = right(i);
    int smallestD = i;

    if ((l < size) && (heap[l].distance < heap[i].distance)) {
        smallestD = l;
    } else {
        smallestD = i;
    }

    if (r < size && heap[r].distance < heap[smallestD].distance) {
        smallestD = r;
    }

    if (i != smallestD) {
        swap(heap[i], heap[smallestD]);
        heapifyDown(smallestD);
    }
}

void MinHeap::insert(int vertex, int distance) {
    int i = size;
    heap[i] = Node(vertex, distance);
    positions[heap[i].vertex] = size;
    size++;

    heapifyUp(i);
}

MinHeap::Node MinHeap::extractMin() {
    Node minNode = heap[0];
    heap[0] = heap[size - 1];
    positions[heap[0].vertex] = 0;
    size--;
    heapifyDown(0);

    return minNode;
}

void MinHeap::decreaseKey(int vertex, int distance) {
    int i = positions[vertex];
    heap[i].distance = distance;

    heapifyUp(i);
}

bool MinHeap::isEmpty() {
    if(size == 0)
        return true;
    else
        return false;
}


void MinHeap::print() {
    std::cout << "---------\n";
    std::cout << "   Heap\n";
    for (int i=0; i<size; i++){
        std::cout << i << ". (" << heap[i].vertex << ", " << heap[i].distance << ")\n";
    }
    std::cout << "---------\n";
}

#include <cmath>

void MinHeap::pretty_print() {
    std::cout << "-----\n";
    for (int i=0; i<size; i++){
        std::cout << "(" << i << ", " << positions[i] << ") ";
    }
    std::cout << "\n-----\n";
    int power = 0;
    int cnt = 0;
    for (int i = 0; i < size; i++){
        std::cout << "(" << heap[i].vertex << ", " << heap[i].distance << ") ";
        cnt++;
        if (cnt >= pow(2, power)){
            std::cout << "\n";
            power++;
            cnt = 0;
        }
    }
    std::cout << "\n-----\n";
}