//
// Created by mhajd on 28.05.2023.
//

#ifndef SDIZOPROJECT2_MINHEAP_H
#define SDIZOPROJECT2_MINHEAP_H


class minHeap {
public:

    struct Node {
        int vertex;
        int distance; // priority key in our priority queue
    };

    int *heap; // pointer to an  array of heap elements
    int size; // current size of a heap
    int capacity;
    int *positions; //

    minHeap(int nOfVertices);

    ~minHeap();

    int parent(int i);

    int left(int i);

    int right(int i);

    void swap(int &a, int &b);

    void heapifyDown(int i);

    void heapifyUp(int i);

    int extractMin();

    void insert(int vertex);

    bool isEmpty();


};


#endif //SDIZOPROJECT2_MINHEAP_H
