
#include "FSP.h"
#include "MinHeap.h"
#include "../Timer.h"

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

void FSP::generateRandomGraph(int n, double d) {
    // input check
    if (n <= 0 || d <= 0 || d > 1) {
        std::cout << "\nINCORRECT INPUT\n";
        return;
    }

    // initialization of graph's data
    numOfVertices = n;
    density = d;
    numOfEdges = (density * numOfVertices * (numOfVertices - 1));

    //Initialization of graph representatives
    adjacency_list = new listNode *[numOfVertices];
    adjacency_matrix = new int *[numOfVertices];


        /// TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
        for (int i = 0; i < numOfVertices; i++) {
            adjacency_matrix[i] = new int[numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
            adjacency_list[i] = NULL;
            for (int j = 0; j < numOfVertices; j++) {
                adjacency_matrix[i][j] = 0;                           // ustawiam w macierzy na brak relacji pomiedzy wierzcholkami
            }
        }
        for (int i = 0; i < numOfVertices - 1; i++) {
            int randWeight = rand() % 100 + 1;

            adjacency_matrix[i][i + 1] = randWeight;

            listNode *newNode1 = new listNode;
            newNode1->cost = randWeight;
            newNode1->vertex = i + 1;
            newNode1->next = adjacency_list[i];
            adjacency_list[i] = newNode1;

        }


        // generating graph for density <= 0.5
        for (int i = 0; i < numOfEdges - numOfVertices - 1; i++) {

            int randWeight = (rand() % 100) + 1;
            int randV1 = rand() % numOfVertices;
            int randV2 = rand() % numOfVertices;
            bool tryAgain = false;

            do {
                tryAgain = false;
                if (randV1 != randV2 && adjacency_matrix[randV1][randV2] ==
                                        0) {                    // losuje do czasu gdy wylosuja sie dwa rozne

                    adjacency_matrix[randV1][randV2] = randWeight;         //wstawiam do macierzy


                    listNode *newNode = new listNode;                           // wstawiam do listy
                    newNode->cost = randWeight;
                    newNode->vertex = randV2;
                    newNode->next = adjacency_list[randV1];
                    adjacency_list[randV1] = newNode;


                    std::cout << "\n Wstawiono. V1: " << randV1 << " V2:" << randV2 << " waga:" << randWeight;

                } else {
                    srand(time(NULL));
                    randV1 = rand() % numOfVertices;
                    randV2 = rand() % numOfVertices;
                    tryAgain = true;

                }
            } while (tryAgain);                 // do skutku probuje na nowo wygenerowac krawedzi

        }
    }


//    std::cout << "\n\n";
//}



//void FSP::generateRandomGraph(int n, double d) {
//    // input check
//    if (n <= 0 || d <= 0 || d > 1) {
//        std::cout << "\nINCORRECT INPUT\n";
//        return;
//    }
//
//    // initialization of graph's data
//    numOfVertices = n;
//    density = d;
//    numOfEdges = density * numOfVertices * (numOfVertices - 1);
//    int maxEdges = (numOfVertices * (numOfVertices - 1));
//
//    //Initialization of graph representatives
//    adjacency_list = new listNode *[numOfVertices];
//    adjacency_matrix = new int *[numOfVertices];
//
//    if (d > 0.5) {
//        for (int i = 0; i < numOfVertices; i++) {
//            adjacency_matrix[i] = new int[numOfVertices]();
//            adjacency_list[i] = nullptr;
//            for (int j = 0; j < numOfVertices; j++) {
//                if (i == j) {
//                    adjacency_matrix[i][j] = 0;
//                } else {
//                    adjacency_matrix[i][j] = -1;
//                }
//            }
//        }
//
//        for (int i = 0; i < maxEdges - numOfEdges; i++) {
//            int randV1 = rand() % numOfVertices;
//            int randV2 = rand() % numOfVertices;
//            bool tryAgain = false;
//            do {
//                tryAgain = false;
//                if (randV1 != randV2 &&
//                    adjacency_matrix[randV1][randV2] == -1) {
//                    int randWeight = rand() % 100 + 1;
//                    adjacency_matrix[randV1][randV2] = randWeight;
//                    adjacency_matrix[randV2][randV1] = randWeight;
//
//                    listNode *newNode = new listNode;
//                    newNode->cost = randWeight;
//                    newNode->vertex = randV2;
//                    newNode->next = adjacency_list[randV1];
//                    adjacency_list[randV1] = newNode;
//
//                    newNode = new listNode;
//                    newNode->cost = randWeight;
//                    newNode->vertex = randV1;
//                    newNode->next = adjacency_list[randV2];
//                    adjacency_list[randV2] = newNode;
//                } else {
//                    srand(time(NULL));
//                    randV1 = rand() % numOfVertices;
//                    randV2 = rand() % numOfVertices;
//                    tryAgain = true;
//                }
//            } while (tryAgain);
//        }
//    } else {
//        for (int i = 0; i < numOfVertices; i++) {
//            adjacency_matrix[i] = new int[numOfVertices]();
//            adjacency_list[i] = nullptr;
//            for (int j = 0; j < numOfVertices; j++) {
//                adjacency_matrix[i][j] = 0;
//            }
//        }
//        for (int i = 0; i < numOfVertices - 1; i++) {
//            int randWeight = rand() % 100 + 1;
//            adjacency_matrix[i][i + 1] = randWeight;
//            adjacency_matrix[i + 1][i] = randWeight;
//
//            listNode *newNode = new listNode;
//            newNode->cost = randWeight;
//            newNode->vertex = i + 1;
//            newNode->next = adjacency_list[i];
//            adjacency_list[i] = newNode;
//
//            newNode = new listNode;
//            newNode->cost = randWeight;
//            newNode->vertex = i;
//            newNode->next = adjacency_list[i + 1];
//            adjacency_list[i + 1] = newNode;
//        }
//
//        for (int i = 0; i < numOfEdges - numOfVertices - 1; i++) {
//            int randWeight = rand() % 100 + 1;
//            int randV1 = rand() % numOfVertices;
//            int randV2 = rand() % numOfVertices;
//            bool tryAgain = false;
//
//            do {
//                tryAgain = false;
//                if (randV1 != randV2 && adjacency_matrix[randV1][randV2] == 0) {
//                    adjacency_matrix[randV1][randV2] = randWeight;
//                    adjacency_matrix[randV2][randV1] = randWeight;
//
//                    listNode *newNode = new listNode;
//                    newNode->cost = randWeight;
//                    newNode->vertex = randV2;
//                    newNode->next = adjacency_list[randV1];
//                    adjacency_list[randV1] = newNode;
//
//                    newNode = new listNode;
//                    newNode->cost = randWeight;
//                    newNode->vertex = randV1;
//                    newNode->next = adjacency_list[randV2];
//                    adjacency_list[randV2] = newNode;
//
//                    std::cout << "\n Wstawiono. V1: " << randV1 << " V2:" << randV2 << " waga:" << randWeight;
//                } else {
//                    srand(time(NULL));
//                    randV1 = rand() % numOfVertices;
//                    randV2 = rand() % numOfVertices;
//                    tryAgain = true;
//                }
//            } while (tryAgain);
//        }
//    }
//
//    std::cout << "\n\n";
//}



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
    int *cost_of_path = new int[numOfVertices]; // an array that stores cost of path to each vertex
    int *predecessors = new int[numOfVertices]; // an array that stores information about predecessors of the shortest path
    bool *QS = new bool[numOfVertices];       // an array that stores information whether vertex was visited or not
    int *S = new int[numOfVertices];       // stack which helps with an output of the algorithm
    int sptr = 0; // stack pointer

    MinHeap minHeap(numOfVertices); // creating our priority queue

    for (int i = 0; i < numOfVertices; i++) { // setting initial parameters to our dynamic arrays
        cost_of_path[i] = MAXINT;
        predecessors[i] = -1;
        QS[i] = false;
    }

    cost_of_path[initialVertex] = 0; // change of cost of path for initial vertex

    // inserting all the vertices into minHeap
    for (int i = 0; i < numOfVertices; i++) {
        minHeap.insert(i, cost_of_path[i]);
    }

    // start of actual algorithm
    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin().vertex;
        temp = adjacency_list[u];
        QS[u] = true;

        while (temp) {
            if (cost_of_path[temp->vertex] > cost_of_path[u] + temp->cost) {
                cost_of_path[temp->vertex] = cost_of_path[u] + temp->cost;
                predecessors[temp->vertex] = u;
                minHeap.decreaseKey(temp->vertex, cost_of_path[temp->vertex]);
            }
            temp = temp->next;
        }
    }
    std::cout << "\n\nPrinting the shortest paths (LIST)\n";
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
    int *S = new int[numOfVertices];       // Stos do wypisywania wynikow
    int sptr = 0;

    MinHeap minHeap(numOfVertices);

    for (int i = 0; i < numOfVertices; i++) {
        cost_of_path[i] = MAXINT;
        predecessors[i] = -1;
        QS[i] = false;
    }

    cost_of_path[initialVertex] = 0;
    for (int i = 0; i < numOfVertices; i++) {
        minHeap.insert(i, cost_of_path[i]);
    }

    // start of the algorithm
    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin().vertex; // getting the vertex with the smallest distance
        QS[u] = true; // visited

        for (int v = 0; v < numOfVertices; v++)
            if (adjacency_matrix[u][v] != 0) {
                if (cost_of_path[v] > cost_of_path[u] + adjacency_matrix[u][v]) {
                    cost_of_path[v] = cost_of_path[u] + adjacency_matrix[u][v];
                    predecessors[v] = u;
                    minHeap.decreaseKey(v, cost_of_path[v]);
                }
            }

    }

    std::cout << "\n\nPrinting the shortest paths (MATRIX)\n";
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

void FSP::measureTime(int numOfTests) {
    std::ofstream file;

    Timer timer;
    file.open("..\\FSP\\test_results_fsp.txt");
    if (file.is_open()) {
        file << "FSP tests\n";
        file << "Dijkstra list | Dijkstra matrix\n";
        double list[3] = {0.2, 0.6, 0.99};
        for (int i = 50; i <=60; i += 10) {
            for (double localDensity: list) {
                initialVertex = 0;
                file << "\n\nTEST->(NUMBER OF VERTICES: " << i << ", DENSITY: " << localDensity << ")\n";
                generateRandomGraph(i, localDensity);

                for (long long &result: results) { // reset of previous data measurements
                    result = 0;
                }

                for (int p = 0; p < numOfTests; p++) { // PRIM LIST
                    timer.startTime();
                    this->listDijkstra();
                    timer.stopTime();
                    results[0] += timer.nanoMeasuredTime();
                }

                file << "adjacency_list: " << results[0] / numOfTests << " [ns]\n";

                for (long long &result: results) { // reset of previous data measurements
                    result = 0;
                }

                for (int p = 0; p < numOfTests; p++) { // PRIM LIST
                    timer.startTime();
                    this->matrixDijkstra();
                    timer.stopTime();
                    results[1] += timer.nanoMeasuredTime();
                }
                file << "adjacency_matrix: " << results[1] / numOfTests << " [ns]\n";

            }


        }


    }

}
