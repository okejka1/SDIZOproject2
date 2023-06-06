
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


    for (int i = 0; i < numOfVertices; i++) {
        adjacency_matrix[i] = new int[numOfVertices];
        for (int j = 0; j < numOfVertices; j++) {
            adjacency_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < numOfVertices - 1; i++) {              // creating spanning tree to make sure that there is no isolated vertex
        int randWeight = rand() % 100 + 1;

        adjacency_matrix[i][i + 1] = randWeight;

        listNode *newNode1 = new listNode;
        newNode1->cost = randWeight;
        newNode1->vertex = i + 1;
        newNode1->next = adjacency_list[i];
        adjacency_list[i] = newNode1;

    }

    for (int i = 0; i < numOfEdges - numOfVertices - 1; i++) {

        int randWeight = (rand() % 100) + 1;
        int randV1 = rand() % numOfVertices;
        int randV2 = rand() % numOfVertices;
        bool tryAgain = false;

        do {
            tryAgain = false;
            if (randV1 != randV2 && adjacency_matrix[randV1][randV2] == 0) {

                adjacency_matrix[randV1][randV2] = randWeight;


                listNode *newNode = new listNode;
                newNode->cost = randWeight;
                newNode->vertex = randV2;
                newNode->next = adjacency_list[randV1];
                adjacency_list[randV1] = newNode;


            } else {
                srand(time(NULL));
                randV1 = rand() % numOfVertices;
                randV2 = rand() % numOfVertices;
                tryAgain = true;

            }
        } while (tryAgain);

    }
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
    int *cost_of_path = new int[numOfVertices]; // an array that stores cost of path to each vertex
    int *predecessors = new int[numOfVertices]; // an array that stores information about predecessors of the shortest path
    bool *considered = new bool[numOfVertices]; // an array that stores information whether vertex was visited or not


    MinHeap minHeap(numOfVertices); // creating our priority queue

    for (int i = 0; i < numOfVertices; i++) { // setting initial parameters to our dynamic arrays
        cost_of_path[i] = MAXINT;
        predecessors[i] = -1;
        considered[i] = false;
    }

    cost_of_path[initialVertex] = 0; // change of cost of path for initial vertex

    // inserting all the vertices into minHeap
    for (int i = 0; i < numOfVertices; i++) {
        minHeap.insert(i, cost_of_path[i]);
    }

    // start of actual algorithm
    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin().vertex; // getting the vertex with the smallest distance
        temp = adjacency_list[u];           // choosing in adjacency list
        considered[u] = true;                       // mark it as considered

        while (temp) { // update of neighbours of u
            if (cost_of_path[temp->vertex] > cost_of_path[u] + temp->cost) {
                cost_of_path[temp->vertex] = cost_of_path[u] + temp->cost; // update of cost for neighbour in an array
                predecessors[temp->vertex] = u; // setting u as predecessor of neighbour
                minHeap.decreaseKey(temp->vertex,cost_of_path[temp->vertex]); // update of distance in heap for neigbour
            }
            temp = temp->next;
        }
    }

    // output of results
    std::cout << "\n\nPrinting the shortest paths (LIST)\n";

    for (int i = 0; i < numOfVertices; i++) {
        std::cout << i << ": ";

        int j = i;
        while (j != -1) {
            std::cout << j << " ";
            j = predecessors[j];
        }

        std::cout << "$" << cost_of_path[i] << "\n";

    }

    //delete of dynamic arrays
    delete[] cost_of_path;
    delete[] predecessors;
    delete[] considered;
}

void FSP::matrixDijkstra() {
    int *cost_of_path = new int[numOfVertices]; // an array that stores cost of path to each vertex
    int *predecessors = new int[numOfVertices]; // an array that stores information about predecessors of the shortest path
    bool *considered = new bool[numOfVertices]; // an array that stores information whether vertex was visited or not

    MinHeap minHeap(numOfVertices);

    for (int i = 0; i < numOfVertices; i++) {
        cost_of_path[i] = MAXINT;
        predecessors[i] = -1;
        considered[i] = false;
    }

    cost_of_path[initialVertex] = 0;
    for (int i = 0; i < numOfVertices; i++) {
        minHeap.insert(i, cost_of_path[i]);
    }

    // start of the algorithm
    while (!minHeap.isEmpty()) {
        int u = minHeap.extractMin().vertex; // getting the vertex with the smallest distance
        considered[u] = true; // visited
        // update of neighbours and their costs
        for (int v = 0; v < numOfVertices; v++)
            if (adjacency_matrix[u][v] != 0) { // if there is an edge
                if (cost_of_path[v] > cost_of_path[u] + adjacency_matrix[u][v]) {
                    cost_of_path[v] = cost_of_path[u] + adjacency_matrix[u][v]; // update of cost in an array
                    predecessors[v] = u; // setting u as predecessor of v
                    minHeap.decreaseKey(v, cost_of_path[v]); // update in heap for changed vertices
                }
            }

    }

    std::cout << "\n\nPrinting the shortest paths (MATRIX)\n";

    for (int i = 0; i < numOfVertices; i++) { // for each vertex
        std::cout << i << ": ";

        int j = i;
        while (j != -1) {
            std::cout << j << " ";
            j = predecessors[j];
        }

        std::cout << "$" << cost_of_path[i] << "\n";
    }


    delete[] cost_of_path;
    delete[] predecessors;
    delete[] considered;


}

void FSP::measureTime(int numOfTests) {
    std::ofstream file;

    Timer timer;
    file.open("..\\FSP\\test_results_fsp.txt");
    if (file.is_open()) {
        file << "FSP tests\n";
        file << "Dijkstra list | Dijkstra matrix\n";
        double list[3] = {0.2, 0.6, 0.99};
        for (int i = 10; i <= 40; i += 5) {
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
