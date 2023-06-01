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

    struct Node{
        Node *next;
        int neighbour;
        int weight;

    };

    int initialVertex;
    int numOfEdges;
    int numOfVertices;
    double density;

    Node **adjacency_list;
    Node *temp;

    int **adjacency_matrix;
    int shortestPath;


    void loadFromFile(std::string fileName);
    void generateRandomGraph(int n, double density);
    void printMatrix();
    void printList();
    void listDijkstra();
    void matrixDijkstra();



};


#endif //SDIZOPROJECT2_FSP_H
