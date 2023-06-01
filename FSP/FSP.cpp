
#include "FSP.h"
#include "minHeap.h"

void FSP::loadFromFile(std::string fileName) {
    int v1, v2, weight;
    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {

        file >> numOfEdges >> numOfVertices >> initialVertex;
        if (file.fail()) {
            std::cout << "File error - READ INITIAL PARAMETERS\n";
            file.close();
        } else {
            adjacency_list = new Node *[numOfVertices]; // initialization of adjacency list
            adjacency_matrix = new int *[numOfVertices]; // initialization of adjacency matrix;

            for (int i = 0; i < numOfVertices; i++) {
                adjacency_matrix[i] = new int[numOfVertices];
                adjacency_list[i] = NULL; // Initially each node is null
                for (int j = 0; j < numOfVertices; j++) {
                    adjacency_matrix[i][j] = 0; // 0 -> no relation between vertices
                }
            }

            for (int i = 0; i < numOfEdges; i++) {
                file >> v1 >> v2 >> weight;
                if (file.fail()) {
                    std::cout << "File error - READ DATA\n";
                    break;
                } else {
                    adjacency_matrix[v1][v2] = weight;

                    temp = new Node; // creating new Node to adjacency list -> vertex v1
                    temp->neighbour = v2; // setting a neighbour to v2
                    temp->next = adjacency_list[v1];
                    temp->weight = weight;
                    adjacency_list[v1] = temp;

                }

            }
            file.close();
        }
    } else
        std::cout << "File error - OPEN\n";

}

void FSP::generateRandomGraph(int n, double density) {

}

void FSP::printMatrix() {
    std::cout << "\n====== Adjacency matrix ======\n\n  ";

    for (int i = 0; i < numOfVertices; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < numOfVertices; i++) {
        std::cout << i << " ";
        for (int j = 0; j < numOfVertices; j++) {
            std::cout << adjacency_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

}

void FSP::printList() {
    std::cout << "\n====== Adjacency list ======\n";

    for (int i = 0; i < numOfVertices; i++) {
        std::cout << "\n" << i << ": ";
        temp = adjacency_list[i];
        while (temp) {
            std::cout << " " << temp->neighbour << " <" << temp->weight << ">, ";
            temp = temp->next;
        }

    }

}

void FSP::listDijkstra() {

    bool *QS;
    int *d;
    int *p;

    d = new int[numOfVertices];      //
    p = new int[numOfVertices];      // Tablica poprzedników
    QS = new bool[numOfVertices];    // Zbiory Q i S


    for (int i = 0; i < numOfVertices; i++) // initialization of dynamic arrays
    {
        d[i] = MAXINT;
        p[i] = -1;
        QS[i] = false;
    }

    d[initialVertex] = 0;

    minHeap heap(numOfVertices);

    for (int i = 0; i < numOfVertices; i++) {
        heap.insert(i);
    }

    while (!heap.isEmpty()) {
        int u = heap.extractMin();

        QS[u] = true;

        while (temp) {
            if (!QS[temp->neighbour] && (d[temp->neighbour] > d[u] + temp->weight)) {
                d[temp->neighbour] = d[u] + temp->weight;
                p[temp->neighbour] = u;
                heap.decreaseKey(temp->neighbour);
            }

        }

    }

}



