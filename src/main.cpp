#include <fstream>
#include <sstream>
#include "../include/EmployeeManagementSystem.hpp"
#include "../include/utils.hpp"

int main()
{
	EmployeeManagementSystem system;

	std::ifstream inputFile("data.csv");
	if (!inputFile)
	{
		std::cerr << "Failed to open the file." << std::endl;
		return 1;
	}

	std::vector<Employee *> employeeData;

	std::string line;
	while (getline(inputFile, line))
	{
		std::stringstream ss(line);
		std::string regNum, gender, eduLvl, jobTtl;
		int age, exp, salary;

		if (getline(ss, regNum, ',') &&
			ss >> age && ss.ignore() &&
			getline(ss, gender, ',') &&
			getline(ss, eduLvl, ',') &&
			getline(ss, jobTtl, ',') &&
			ss >> exp && ss.ignore() &&
			ss >> salary)
		{
			Employee *emp = new Employee(regNum, age, gender, eduLvl, jobTtl, exp, salary);
			employeeData.push_back(emp);
		}
		else
		{
			std::cerr << "Invalid data format in the CSV file." << std::endl;
			return 1;
		}
	}

	inputFile.close();

	for (size_t i = 0; i < employeeData.size(); i++)
	{
		system.addEmployee(employeeData[i]);
	}

	int choice;
	std::string regNum1, regNum2;
	std::string regNum, gender, eduLevel, jobTitle;
	int age, yearsExp, salary;
	Employee *newEmployee = nullptr;

	while (true)
	{
		choice = print_menu();
		switch (choice)
		{
		case 1:
			system.printEmployees();
			break;
		case 2:
			std::cout << "Enter registration number: ";
			std::cin >> regNum;
			std::cout << "Enter age: ";
			std::cin >> age;
			std::cout << "Enter gender: ";
			std::cin >> gender;
			std::cout << "Enter education level: ";
			std::cin >> eduLevel;
			std::cout << "Enter job title: ";
			std::cin >> jobTitle;
			std::cout << "Enter years of experience: ";
			std::cin >> yearsExp;
			std::cout << "Enter salary: ";
			std::cin >> salary;
			newEmployee = new Employee(regNum, age, gender, eduLevel, jobTitle, yearsExp, salary);
			system.addEmployee(newEmployee);
			std::cout << "Employee added successfully!" << std::endl;
			break;
		case 3:
			std::cout << "Enter registration number of the employee to be removed: ";
			std::cin >> regNum;
			system.removeEmployee(regNum);
			std::cout << "Employee removed successfully!" << std::endl;
			break;
		case 4:
			int weight;
			std::cout << "Enter registration number of the first employee: ";
			std::cin >> regNum1;
			std::cout << "Enter registration number of the second employee: ";
			std::cin >> regNum2;
			std::cout << "Enter weight of the connection: ";
			std::cin >> weight;
			system.connectEmployees(regNum1, regNum2, weight);
			std::cout << "Employees connected successfully!" << std::endl;
			break;
		case 5:
			std::cout << "Enter registration number of the first employee: ";
			std::cin >> regNum1;
			std::cout << "Enter registration number of the second employee: ";
			std::cin >> regNum2;
			system.disconnectEmployees(regNum1, regNum2);
			std::cout << "Employees disconnected successfully!" << std::endl;
			break;
		case 6:
			std::cout << "Enter registration number of the first employee: ";
			std::cin >> regNum1;
			std::cout << "Enter registration number of the second employee: ";
			std::cin >> regNum2;
			std::cout << std::endl
					  << "Shortest Distance : " << system.shortestDistanceBetweenEmployees(regNum1, regNum2) << std::endl
					  << std::endl;
			break;
		case 7:
			std::cout << "Enter registration number of the starting employee: ";
			std::cin >> regNum;
			system.breadthFirstSearch(regNum);
			break;
		case 8:
			std::cout << "Enter registration number of the starting employee: ";
			std::cin >> regNum;
			system.depthFirstSearch(regNum);
			break;
		case 9:
			system.primMST();
			break;
		case 10:
			std::cout << "Total No. of Employees: " << system.getNumberOfEmployees() << std::endl;
			break;
		case 11:
			std::cout << "Exiting Employee Management System..." << std::endl;
			exit(0);
			break;
		default:
			std::cout << "Invalid choice! Please try again." << std::endl;
			break;
		}
	}

	return 0;
}