
#include "FSP.h"
#include "MinHeap.h"

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
            adjacency_list = new listNode *[numOfVertices]; // initialization of adjacency list
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

                    temp = new listNode; // creating new listNode to adjacency list -> vertex v1
                    temp->vertex = v2; // setting a vertex to v2
                    temp->next = adjacency_list[v1];
                    temp->cost = weight;
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
            std::cout << " " << temp->vertex << " <" << temp->cost << ">, ";
            temp = temp->next;
        }

    }

}

void FSP::listDijkstra() {
    int *cost_of_path = new int[numOfVertices]; // Wynikowa tablica kosztow
    int *predecessors = new int[numOfVertices]; // Poprzednicy
    bool *QS = new bool[numOfVertices];       // visited
    int *S = new int [ numOfVertices ];       // Stos do wypisywania wynikow
    int sptr = 0;

    MinHeap minHeap(numOfVertices);

    for (int i = 0; i < numOfVertices; i++) {
        cost_of_path[i] = MAXINT;
        predecessors[i] = -1;
        QS[i] = false;
    }

    cost_of_path[initialVertex] = 0;
    for(int i = 0; i < numOfVertices; i++) {
        minHeap.insert(i, cost_of_path[i]);
    }

    // Rozpocznij algorytm
    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin().vertex;
        temp = adjacency_list[u];
        QS[u] = true;

        while(temp) {
            if (cost_of_path[temp->vertex] > cost_of_path[u] + temp->cost){
                cost_of_path[temp->vertex] = cost_of_path[u] + temp->cost;
                predecessors[temp->vertex] = u;
                minHeap.decreaseKey(temp->vertex, cost_of_path[temp->vertex]);
            }
            temp = temp->next;
        }
    }
    std::cout << "\n\nPrinting the shortest paths:\n";
    // Gotowe, wyświetlamy wyniki
    for (int i = 0; i < numOfVertices; i++) {
        std::cout << i << ": ";

        // Ścieżkę przechodzimy od końca ku początkowi,
        // Zapisując na stosie kolejne wierzchołki

        for (int j = i; j > -1; j = predecessors[j])
            S[sptr++] = j;

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while (sptr)
            std::cout << S[--sptr] << " ";

        // Na końcu ścieżki wypisujemy jej koszt

        std::cout << "$" << cost_of_path[i];
        std::cout << "\n";
    }

    // Usuwamy tablice dynamiczne

    delete[] cost_of_path;
    delete[] predecessors;
    delete[] QS;
    delete[] S;
}

void FSP::matrixDijkstra() {
    int *cost_of_path = new int[numOfVertices]; // Wynikowa tablica kosztow
    int *predecessors = new int[numOfVertices]; // Poprzednicy
    bool *QS = new bool[numOfVertices];       // visited
    int *S = new int [ numOfVertices ];       // Stos do wypisywania wynikow
    int sptr = 0;

    MinHeap minHeap(numOfVertices);

    for (int i = 0; i < numOfVertices; i++) {
        cost_of_path[i] = MAXINT;
        predecessors[i] = -1;
        QS[i] = false;
    }

    cost_of_path[initialVertex] = 0;
    for(int i = 0; i < numOfVertices; i++) {
        minHeap.insert(i, cost_of_path[i]);
    }

    // Rozpocznij algorytm
    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin().vertex;
        QS[u] = true;

        for(int v = 0; v < numOfVertices; v++)
            if (cost_of_path[v] > cost_of_path[u] + adjacency_matrix[u][v]) {
                cost_of_path[v] = cost_of_path[u] + adjacency_matrix[u][v];
                predecessors[v] = u;
                minHeap.decreaseKey(v, cost_of_path[v]);
            }

    }
    // Gotowe, wyświetlamy wyniki
    for (int i = 0; i < numOfVertices; i++) {
        std::cout << i << ": ";

        // Ścieżkę przechodzimy od końca ku początkowi,
        // Zapisując na stosie kolejne wierzchołki

        for (int j = i; j > -1; j = predecessors[j])
            S[sptr++] = j;

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while (sptr)
            std::cout << S[--sptr] << " ";

        // Na końcu ścieżki wypisujemy jej koszt

        std::cout << "$" << cost_of_path[i];
        std::cout << "\n";
    }

    // Usuwamy tablice dynamiczne

    delete[] cost_of_path;
    delete[] predecessors;
    delete[] QS;
    delete[] S;

}
