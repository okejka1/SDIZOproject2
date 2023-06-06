#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>

#ifndef SDIZOPROJECT2_FSP_H
#define SDIZOPROJECT2_FSP_H


class FSP {

public:
    const int MAXINT = 2147483647;

    struct listNode{
        listNode *next;
        int vertex;
        int cost;

    };
     long long results[2];
    /*
     result[0] -> Dijkstra's list
     result[1] -> Dijkstra's matrix
     */

    int initialVertex;
    int numOfEdges;
    int numOfVertices;
    double density;

    listNode **adjacency_list;
    listNode *temp;

    int **adjacency_matrix;

    void loadFromFile(std::string fileName);
    void generateRandomGraph(int n, double density);
    void printMatrix();
    void printList();
    void listDijkstra();
    void matrixDijkstra();
    void measureTime(int numOfTests);
};


#endif //SDIZOPROJECT2_FSP_H
