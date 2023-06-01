
#include "Menu.h"
#include "MST/MST.h"
#include "FSP/FSP.h"

void Menu::MenuMST() {

    MST mst = * new MST();;
    std::string fileName;


    int option = -1;


    do {
        std::cout << "\n==== TABLE MENU ====\n";
        std::cout << "1.Load your structure from file\n";
        std::cout << "2.Generate the structure\n";
        std::cout << "3.Display the structure\n";
        std::cout << "4.Algorithm 1 - Prim's algorithm\n";
        std::cout << "5.Algorithm 2 - Kruskal's algorithm\n";
        std::cout << "6.Exit\n";

        std::cin.clear();
        fflush(stdin);

        std::cin >> option;


        switch (option) {

            case 1: // loading from a file
                std::cout << "Enter your file name:";
                std::cin >> fileName;
                fileName = "..\\Input\\" + fileName;
                mst.loadFromFile(fileName);
                mst.printMatrix();
                mst.printList();
                break;
            case 2: // generating a random graph
                break;
            case 3: // display of matrix and list
                mst.printMatrix();
                mst.printList();
                break;
            case 4: // Prim's algorithm
                mst.primList();
                mst.primMatrix();
                mst.printMatrix();
                mst.printList();
            case 5: //
                break;
            case 6: // exit
                break;
            default:
                std::cout << "Input error!\n";
                break;
        }
    } while (option != 6);
}


void Menu::MenuFSP() {

    FSP fsp = * new FSP();;
    std::string fileName;


    int option = -1;


    do {
        std::cout << "\n==== TABLE MENU ====\n";
        std::cout << "1.Load your structure from file\n";
        std::cout << "2.Generate the structure\n";
        std::cout << "3.Display the structure\n";
        std::cout << "4.Algorithm 1 - Dijkstra''s algorithm\n";
        std::cout << "5.Algorithm 2 - Bellman - Ford algorithm\n";
        std::cout << "6.Exit\n";

        std::cin.clear();
        fflush(stdin);

        std::cin >> option;


        switch (option) {

            case 1: // loading from a file
                std::cout << "Enter your file name:";
                std::cin >> fileName;
                fileName = "..\\Input\\" + fileName;
                fsp.loadFromFile(fileName);
                fsp.printMatrix();
                fsp.printList();
                break;
            case 2: // generating a random graph
                break;
            case 3: // display of graph's representation
                fsp.printMatrix();
                fsp.printList();
                break;
            case 4: // Dijkstra's algorithm

            case 5: //
                break;
            case 6: // exit
                break;
            default:
                std::cout << "Input error!\n";
                break;
        }
    } while (option != 6);

}

