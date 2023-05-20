#include <iostream>
#include "Menu.h"

int main() {
    Menu menu;
    int option = -1;
    std::cout << "Structures of algorithms and computational complexity - Mikolaj Hajder 264478" << std::endl;

    do {
        std::cout << "\n==== MAIN MENU ====\n";
        std::cout << "1.Minimum spanning tree (Prim's algorithm, Kruskal's algorithm) \n";
        std::cout << "2.Finding the shortest path in a graph (Dijkstra's Algorithm)\n";
        std::cout << "3.Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        std::cin.clear();
        fflush(stdin);

        switch (option) {
            case 1:
                menu.MenuMST();
                break;
            case 2:
                menu.MenuFSP();
                break;
            case 3:
                break;
            default:
                std::cout << "Input error! - make sure to choose an option available from the main menu!\n ";
                break;
        }
    } while (option != 3);
    return 0;
}