#include "minHeap.h"

minHeap::minHeap(int nOfVertices) {
    heap = new int[nOfVertices];
    size = 0;
}

minHeap::~minHeap() {
    delete[] heap;
    size = 0;
}

    int minHeap::parent(int i) {
        return (i - 1) / 2;
    }

    int minHeap::left(int i) {
        return 2 * i + 1;
    }

    int minHeap::right(int i) {
        return 2 * i + 2;
    }

void minHeap::swap(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void minHeap::heapifyDown(int i) {
    int l = left(i);
    int r = right(i);
    int smallestW = i;


    if ((l < size) && (heap[l] < heap[i])) {
        smallestW = l;
    } else {
        smallestW = i;
    }
    if ((r < size) && (heap[r] < heap[smallestW])) {
        smallestW = r;
    }
    if (i != smallestW) {
        swap(heap[i], heap[smallestW]);
        heapifyDown(smallestW);
    }

}

void minHeap::heapifyUp(int i) {
    while (i != 0 && heap[parent(i)] > heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }

}

int minHeap::extractMin() {
    if (size == 1) {
        size--;
        return heap[0];
    }
    int root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return root;
}

void minHeap::insert(int vertex) {
    heap[size] = vertex;
//    pos[vertex] = size;
    heapifyUp(size);
    size++;
}

bool minHeap::isEmpty() {
    if (size == 0)
        return true;
    else
        return false;
}





