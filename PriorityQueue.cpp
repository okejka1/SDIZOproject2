#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int nOfEdges) {
    heap = new Edge[nOfEdges];
    size = 0;
}
PriorityQueue::~PriorityQueue() {
    delete [] heap;
}

PriorityQueue::Edge PriorityQueue::front() {

    return heap[0];
}

void PriorityQueue::push(PriorityQueue::Edge e) {
    {
        int i, parent;
        size++;
        i = size-1;                    // insert i to the last index of the heap
        parent = (i - 1) / 2;
        // parent index

        // looking for a place to insert e to the heap

        while(i!=0 && (heap[parent].weight > e.weight) )
        {
            heap [i] = heap [parent] ;
            i = parent;
            parent = (i - 1) / 2;
        }

        heap[i] = e;                //insertion of an edge to the heap
    }

}

void PriorityQueue::pop() {

    int i, parent;
    Edge e;

    if (size) {
        e = heap[--size];

        i = 0;
        parent = 1;

        while (parent < size) {
            if ((parent + 1 < size) && (heap[parent + 1].weight < heap[parent].weight)) parent++;
            if (e.weight <= heap[parent].weight) break;
            heap[i] = heap[parent];
            i = parent;
            parent = (parent << 1) + 1;
        }

        heap[i] = e;


    }

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





