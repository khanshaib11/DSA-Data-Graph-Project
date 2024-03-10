#include "../include/utils.hpp"

int print_menu() {
    int choice;
    std::cout << "\n========== Main Menu ==========" << std::endl;
    std::cout << "1. Print Employees" << std::endl;
    std::cout << "2. Add Employee" << std::endl;
    std::cout << "3. Remove Employee" << std::endl;
    std::cout << "4. Connect Employees" << std::endl;
    std::cout << "5. Disconnect Employees" << std::endl;
    std::cout << "6. Shortest Distance Between Employees" << std::endl;
    std::cout << "7. Perform BFS Traversal" << std::endl;
    std::cout << "8. Perform DFS Traversal" << std::endl;
    std::cout << "9. Find Minimum Spanning Tree using Prim's Algorithm" << std::endl;
    std::cout << "10. Total No. of Employees"<<std::endl;
    std::cout << "11. Exit" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}