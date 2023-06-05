#include <iomanip>
#include <queue>
#include "MST.h"
#include "../PriorityQueue.h"
#include "../Timer.h"


void MST::loadFromFile(std::string fileName) {

    int v1, v2, weight;
    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {

        file >> numOfEdges >> numOfVertices;
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
                    adjacency_matrix[v2][v1] = weight;

                    temp = new listNode; // creating new listNode to adjacency list -> vertex v1
                    temp->vertex = v2; // setting a vertex to v2
                    temp->next = adjacency_list[v1];
                    temp->cost = weight;
                    adjacency_list[v1] = temp;

                    temp = new listNode;
                    temp->vertex = v1;
                    temp->next = adjacency_list[v2];
                    temp->cost = weight;
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

void MST::printList() {
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

void MST::primList() {


    PriorityQueue pq(numOfEdges); // initialization of priority queue (based on binary minimum heap)
    PriorityQueue::Edge edge{};
    int v = 0; //initial vertex
    costMST = 0; // initial cost of MST

    bool *visited = new bool[numOfVertices]; //  table of bool values (define whether vertex was already visited or not)
    auto *mst = new PriorityQueue::Edge[numOfVertices - 1]; // actual minimum spanning tree

    for (int i = 0; i < numOfVertices; i++) // all vertices not visited
        visited[i] = false;

    visited[v] = true;


    for (int i = 0; i < numOfVertices - 1; i++) {
        temp = adjacency_list[v];


        while (temp) {
            if (!visited[temp->vertex])    // if vertex in NOT visited
            {
                edge.v1 = v;                // creating an edge
                edge.v2 = temp->vertex;
                edge.weight = temp->cost;
                pq.push(edge);            // insertion to the priority queue
            }
            temp = temp->next; // going to the next neighbours of temp

        }
        do {
            edge = pq.front();
            pq.pop();                     // extracting egde from priority queue
        } while (visited[edge.v2]);        // checking if vertex 2 is already visited  yes then it means vertex is already in mst if not end of while loop

        visited[edge.v2] = true;     // vertex as visited
        v = edge.v2;                    // setting v2 as next vertex to search for smallest cost

        mst[i] = edge;                 // adding the edge to the mst
        costMST += edge.weight;

    }
    std::cout << "\n***Prim's algorithm for list***\n";
    for (int i = 0; i < numOfVertices - 1; i++) {
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

    bool *visited = new bool[numOfVertices];
    auto *mst = new PriorityQueue::Edge[numOfVertices - 1]; // actual minimum spanning tree

    for (int i = 0; i < numOfVertices; i++)
        visited[i] = false;

    visited[v] = true;

    for (int i = 0; i < numOfVertices - 1; i++) { // in each iteration one edge is added to mst

        for (int j = 0; j < numOfVertices; j++) {


            if (!visited[j] &&
                adjacency_matrix[v][j] != 0) { // if vertex j is not visited and its weigh diffrent then 0
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
        v = edge.v2;                 // setting v2 as next vertex to search for smallest cost

        mst[i] = edge;              // adding the edge to the mst
        costMST += edge.weight;

    }
    std::cout << "\n***Prim's algorithm for matrix***\n";
    for (int i = 0; i < numOfVertices - 1; i++) {
        std::cout << mst[i].v1 << "-" << mst[i].v2 << ":<" << mst[i].weight << ">\n";
    }
    std::cout << "\n\n" << "Minimal Spanning Tree Weight = " << costMST << "\n";
    delete[] visited;
    delete[] mst;
}
void MST::generateRandomGraph(int n, double d){
    // input check
    if (n <= 0 || d <= 0 || d > 1) {
        std::cout << "\nINCORRECT INPUT\n";
        return;
    }

    // initialization of graph's data
    numOfVertices = n;
    density = d;
    numOfEdges = (density * numOfVertices * (numOfVertices - 1)) / 2;
    int maxEdges = ((numOfVertices) * (numOfVertices - 1)) / 2;

    //Initialization of graph representatives
    adjacency_list = new listNode *[numOfVertices];
    adjacency_matrix = new int *[numOfVertices];



    if (d > 0.5) {

        for (int i = 0; i < numOfVertices; i++) {
            adjacency_matrix[i] = new int[numOfVertices];             // second dimension of matrix
            adjacency_list[i] = NULL;
            for (int j = 0; j < numOfVertices; j++) {
                if (i == j) {
                    adjacency_matrix[i][j] = 0;                        // diagonal = 0
                } else {
                    adjacency_matrix[i][j] = -1;                          // no relations between vertices
                }
            }
        }


        /// LOSUJE PUSTE KRAWEDZI I WSTAWIAM TAM 0
        std::cout << maxEdges << " " << numOfEdges;
        for (int i = 0; i < maxEdges - numOfEdges; i++) {
            int randV1 = rand() % numOfVertices;
            int randV2 = rand() % numOfVertices;
            bool tryAgain = false;
            do {
                tryAgain = false;
                if (randV1 != randV2 &&
                    adjacency_matrix[randV1][randV2] == -1) {

                    adjacency_matrix[randV1][randV2] = 0;
                    adjacency_matrix[randV2][randV1] = 0;


                } else {
                    srand(time(NULL));
                    randV1 = rand() % numOfVertices;
                    randV2 = rand() % numOfVertices;
                    tryAgain = true;

                }
            } while (tryAgain);
        }




        // generating
        for (int x = 0; x < numOfVertices; x++) {
            for (int y = 0; y < x; y++) {

                int randWeight = rand() % 100 + 1;

                if (adjacency_matrix[x][y] != 0) {
                    adjacency_matrix[x][y] = randWeight;
                    adjacency_matrix[y][x] = randWeight;

                    listNode *newNode1 = new listNode;                           // wstawiam do listy
                    newNode1->cost = randWeight;
                    newNode1->vertex = x;
                    newNode1->next = adjacency_list[y];
                    adjacency_list[y] = newNode1;

                    listNode *newNode2 = new listNode;                           // wstawiam do listy
                    newNode2->cost = randWeight;
                    newNode2->vertex = y;
                    newNode2->next = adjacency_list[x];
                    adjacency_list[x] = newNode2;


                }
            }


        }

    } else { // generating graph for density <= 0.5

        // initialization of graph representatives
        for (int i = 0; i < numOfVertices; i++) {
            adjacency_matrix[i] = new int[numOfVertices];
            adjacency_list[i] = NULL;
            for (int j = 0; j < numOfVertices; j++) {
                adjacency_matrix[i][j] = 0;
            }
        }
        // making sure that of the vertices are connected and there is no isolated vertex in the graph
        for (int i = 0; i < numOfVertices - 1; i++) {
            int randWeight = rand() % 100 + 1;

            adjacency_matrix[i][i + 1] = randWeight;
            adjacency_matrix[i + 1][i] = randWeight;

            listNode *newNode1 = new listNode;
            newNode1->cost = randWeight;
            newNode1->vertex = i + 1;
            newNode1->next = adjacency_list[i];
            adjacency_list[i] = newNode1;

            listNode *newNode2 = new listNode;
            newNode2->cost = randWeight;
            newNode2->vertex = i;
            newNode2->next = adjacency_list[i + 1];
            adjacency_list[i + 1] = newNode2;
        }


        // generating random Edges with random weights
        for (int i = 0; i < numOfEdges-numOfVertices-1; i++) {

            int randWeight = rand() % 100 + 1;
            int randV1 = rand() % numOfVertices;
            int randV2 = rand() % numOfVertices;
            bool tryAgain = false;

            do {
                tryAgain = false;
                if (randV1 != randV2 && adjacency_matrix[randV1][randV2] == 0) {                    // losuje do czasu gdy wylosuja sie dwa rozne

                    adjacency_matrix[randV1][randV2] = randWeight;         //wstawiam do macierzy
                    adjacency_matrix[randV2][randV1] = randWeight;


                    listNode *newNode1 = new listNode;                           // wstawiam do listy
                    newNode1->cost = randWeight;
                    newNode1->vertex = randV2;
                    newNode1->next = adjacency_list[randV1];
                    adjacency_list[randV1] = newNode1;

                    listNode *newNode2 = new listNode;                           // wstawiam do listy
                    newNode2->cost = randWeight;
                    newNode2->vertex = randV1;
                    newNode2->next = adjacency_list[randV2];
                    adjacency_list[randV2] = newNode2;

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


    std::cout << "\n\n";
}




void MST::measureTime(int numOfTests) {
    std::ofstream file;

    Timer timer;
    file.open("..\\MST\\test_results_mst.txt");
    if (file.is_open()) {
        file << "MST tests\n";
        file << "Prim list | Prim matrix\n";
        double list[3] = {0.2,0.6, 0.99};
        for (int i = 10; i <= 70; i += 10) {
            for (double localDensity : list) {
                file << "\n\nTEST->(NUMBER OF VERTICES: " << i << ", DENSITY: " << localDensity << ")\n";
                generateRandomGraph(i, localDensity);

                for(long & result : results){ // reset of previous data measurements
                    result = 0;
                }


                for(int p = 0; p < numOfTests; p++){ // PRIM LIST
                    timer.startTime();
                    this->primList();
                    timer.stopTime();
                    results[0] += timer.nanoMeasuredTime();
                }

                file << "adjacency_list: " << results[0]/numOfTests << " [ns]\n";

                for(long & result : results){ // reset of previous data measurements
                    result = 0;
                }

                for(int p  = 0; p < numOfTests; p++){ // PRIM LIST
                    timer.startTime();
                    this->primMatrix();
                    timer.stopTime();
                    results[1] += timer.nanoMeasuredTime();
                }
                file << "adjacency_matrix: " << results[1]/numOfTests << " [ns]\n";

            }


        }


    }

}














