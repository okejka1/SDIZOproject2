#ifndef SDIZOPROJECT2_MINHEAP_H
#define SDIZOPROJECT2_MINHEAP_H


class MinHeap {

public:


    struct Node {
        int vertex;
        int distance; // priority key in our priority queue
    };

    Node *heap; // a heap of nodes (vertexes with distances)
    int size; // current size of a heap
    int capacity; // maximal capacity of a heap
    int *positions; // array to store the position of vertices in the heap


    MinHeap(int capacity);
    ~MinHeap();

    int parent(int i);

    int left(int i);

    int right(int i);

    void swap(Node &a, Node &b);

    void heapifyUp(int i);

    void heapifyDown(int i);

    void print();

    void pretty_print();

    Node extractMin();

    void decreaseKey(int vertex, int distance);

    bool isEmpty();


    void insert(int vertex, int distance);
};


#endif //SDIZOPROJECT2_MINHEAP_H
