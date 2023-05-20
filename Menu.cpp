
#include "Menu.h"
#include "MST/MST.h"

void Menu::MenuMST() {

    MST mst;
    std::string fileName;

    int val;
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
                break;
            case 2: //
                break;
            case 3: //
                break;
            case 4: //
                break;
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

}

