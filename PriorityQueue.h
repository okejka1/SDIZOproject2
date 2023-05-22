

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

    void pop();


};


#endif //SDIZOPROJECT2_PRIORITYQUEUE_H
