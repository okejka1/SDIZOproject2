
#ifndef SDIZOPROJECT2_MST_H
#define SDIZOPROJECT2_MST_H


#include <string>
#include <iostream>
#include <fstream>

class MST {

public:

    struct Node{
        Node *next;
        int neighbour;
        int weight;

    };

//    struct Edge{
//        int v1, v2, weight;
//    };

    int numOfEdges;
    int numOfVertexes;

    Node **adjacency_list;
    Node *temp;

    int **adjacency_matrix;
    int costMST;






    void loadFromFile(std::string fileName);
    void printMatrix();
    void printList();
    void primList();
    void primMatrix();



};


#endif //SDIZOPROJECT2_MST_H
