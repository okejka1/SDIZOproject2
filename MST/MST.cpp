#include <iomanip>
#include <queue>
#include "MST.h"
#include "../PriorityQueue.h"


void MST::loadFromFile(std::string fileName) {

    int v1, v2, weight;
    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {

        file >> numOfEdges >> numOfVertexes;
        if (file.fail()) {
            std::cout << "File error - READ INITIAL PARAMETERS\n";
            file.close();
        } else {
            adjacency_list = new Node *[numOfVertexes]; // initialization of adjacency list
            adjacency_matrix = new int *[numOfVertexes]; // initialization of adjacency matrix;

            for (int i = 0; i < numOfVertexes; i++) {
                adjacency_matrix[i] = new int[numOfVertexes];
                adjacency_list[i] = NULL; // Initially each node is null
                for (int j = 0; j < numOfVertexes; j++) {
                    adjacency_matrix[i][j] = 0; // 0 -> no relation between vertexes
                }
            }

            for (int i = 0; i < numOfEdges; i++) {
                file >> v1 >> v2 >> weight;
                if (file.fail()) {
                    std::cout << "File error - READ DATA\n";
                    break;
                } else {
                    adjacency_matrix[v1][v2] = weight;
                    adjacency_matrix[v2][v1] = weight;

                    temp = new Node; // creating new Node to adjacency list -> vertex v1
                    temp->neighbour = v2; // setting a neighbour to v2
                    temp->next = adjacency_list[v1];
                    temp->weight = weight;
                    adjacency_list[v1] = temp;

                    temp = new Node;
                    temp->neighbour = v1;
                    temp->next = adjacency_list[v2];
                    temp->weight = weight;
                    adjacency_list[v2] = temp;

                }

            }
            file.close();
        }
    } else
        std::cout << "File error - OPEN\n";

}

void MST::printMatrix() {

    std::cout << "\n====== Adjacency matrix ======\n\n  ";


    for (int i = 0; i < numOfVertexes; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < numOfVertexes; i++) {
        std::cout << i << " ";
        for (int j = 0; j < numOfVertexes; j++) {
            std::cout << adjacency_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

}

void MST::printList() {
    std::cout << "\n====== Adjacency list ======\n";

    for (int i = 0; i < numOfVertexes; i++) {
        std::cout << "\n" << i << ": ";
        temp = adjacency_list[i];
        while (temp) {
            std::cout << " " << temp->neighbour << " <" << temp->weight << ">, ";
            temp = temp->next;
        }

    }

}

void MST::primList() {


    PriorityQueue pq(numOfEdges); // initialization of priority queue (based on binary minimum heap)
    PriorityQueue::Edge edge{};
    int v = 0; //initial vertex
    costMST = 0; // initial cost of MST

    bool *visited = new bool[numOfVertexes]; //  table of bool values (define whether vertex was already visited or not)
    auto *mst = new PriorityQueue::Edge[numOfVertexes - 1]; // actual minimum spanning tree

    for (int i = 0; i < numOfVertexes; i++) // all vertexes not visited
        visited[i] = false;

    visited[v] = true;


    for (int i = 0; i < numOfVertexes - 1; i++) {
        temp = adjacency_list[v];


        while (temp) {
            if (!visited[temp->neighbour])    // if neighbour in NOT visited
            {
                edge.v1 = v;                // creating an edge
                edge.v2 = temp->neighbour;
                edge.weight = temp->weight;
                pq.push(edge);            // insertion to the priority queue
            }
            temp = temp->next; // going to the next neighbours of temp

        }
        do {
            edge = pq.front();
            pq.pop();                     // extracting egde from priority queue
        } while (visited[edge.v2]);        // checking if vertex 2 is already visited  yes then it means vertex is already in mst if not end of while loop

        visited[edge.v2] = true;     // vertex as visited
        v = edge.v2;                    // setting v2 as next vertex to search for smallest weight

        mst[i] = edge;                 // adding the edge to the mst
        costMST += edge.weight;

    }
    std::cout << "\n***Prim's algorithm for list***\n";
    for (int i = 0; i < numOfVertexes - 1; i++) {
        std::cout << mst[i].v1 << "-" << mst[i].v2 << ":<" << mst[i].weight << ">\n";
    }
    std::cout << "\n\n" << "Minimal Spanning Tree Weight = " << costMST;
    delete[] visited;
    delete[] mst;
}

void MST::primMatrix() {
    PriorityQueue pq(numOfEdges);
    PriorityQueue::Edge edge{};
    int v = 0; //initial vertex
    costMST = 0;

    bool *visited = new bool[numOfVertexes];
    auto *mst = new PriorityQueue::Edge[numOfVertexes - 1]; // actual minimum spanning tree

    for (int i = 0; i < numOfVertexes; i++)
        visited[i] = false;

    visited[v] = true;

    for (int i = 0; i < numOfVertexes - 1; i++) {

        for (int j = 0; j < numOfVertexes; j++) {


            if (!visited[j] && adjacency_matrix[v][j] != 0) { // if vertex is not visited and its weigh diffrent then 0
                edge.v1 = v;
                edge.v2 = j;
                edge.weight = adjacency_matrix[v][j];
                pq.push(edge); //add to priority queue
            }
        }
        do {
            edge = pq.front();
            pq.pop();                // extracting an egde from priority queue
        } while (visited[edge.v2]);  // checking if vertex 2 is already visited  yes then it means vertex is already in mst if not end of while loop

        visited[edge.v2] = true;     // v2 as visited
        v = edge.v2;                 // setting v2 as next vertex to search for smallest weight

        mst[i] = edge;              // adding the edge to the mst
        costMST += edge.weight;

    }
    std::cout << "\n***Prim's algorithm for matrix***\n";
    for (int i = 0; i < numOfVertexes - 1; i++) {
        std::cout << mst[i].v1 << "-" << mst[i].v2 << ":<" << mst[i].weight << ">\n";
    }
    std::cout << "\n\n" << "Minimal Spanning Tree Weight = " << costMST;
    delete[] visited;
    delete[] mst;
}











