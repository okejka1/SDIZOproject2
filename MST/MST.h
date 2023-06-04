#ifndef SDIZOPROJECT2_MST_H
#define SDIZOPROJECT2_MST_H


#include <string>
#include <iostream>
#include <fstream>

class MST {

public:

    struct listNode{
        listNode *next;
        int vertex;
        int cost;

    };
    long results[2];

    /*
     result[0] -> prim's list
     result[1] -> prim's matrix
     */

    int numOfEdges;
    int numOfVertices;
    double density;

    listNode **adjacency_list;
    listNode *temp;

    int **adjacency_matrix;
    int costMST;






    void loadFromFile(std::string fileName);
    void generateRandomGraph(int n, double density);
    void printMatrix();
    void printList();
    void primList();
    void primMatrix();
    void measureTime(int numOfTests);



};


#endif //SDIZOPROJECT2_MST_H
