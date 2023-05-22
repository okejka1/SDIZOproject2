

#ifndef SDIZOPROJECT2_PRIORITYQUEUE_H
#define SDIZOPROJECT2_PRIORITYQUEUE_H


class PriorityQueue {



public:
    struct Edge {
        int v1, v2, weight;
    };

    Edge *heap;
    int parent(int i);

    int left(int i);

    int right(int i);
    int size;

    PriorityQueue(int n);

    ~PriorityQueue();

    Edge front();

    void push(Edge e);

    Edge pop();
    void swap(Edge &a, Edge &b);
    void heapify(int i);



};


#endif //SDIZOPROJECT2_PRIORITYQUEUE_H
