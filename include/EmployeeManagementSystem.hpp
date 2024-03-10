#ifndef EMPLOYEE_MANAGEMENT_SYSTEM_HPP
#define EMPLOYEE_MANAGEMENT_SYSTEM_HPP

#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include "params.hpp"

struct Employee {
    std::string registrationNumber;
    int age;
    std::string gender;
    std::string educationLevel;
    std::string jobTitle;
    int yearsOfExperience;
    int salary;
    Employee* next;

    Employee(std::string regNum, int empAge, std::string empGender,
                std::string eduLvl,
                std::string jobTtl,
                int exp, int empSalary) {
        registrationNumber = regNum;
        age = empAge;
        gender = empGender;
        educationLevel = eduLvl;
        jobTitle = jobTtl;
        yearsOfExperience = exp;
        salary = empSalary;
        next = nullptr;
    }
};

class EmployeeManagementSystem
{
private:
    int adjacencyMatrix[MAX_EMPLOYEES][MAX_EMPLOYEES];
    Employee *employees[MAX_EMPLOYEES];
    int numEmployees;

public:
    EmployeeManagementSystem();
    ~EmployeeManagementSystem();
    
    void addEmployee(Employee *employee);
    
    void removeEmployee(std::string registrationNumber);
    
    void connectEmployees(std::string registrationNumber1,
                            std::string registrationNumber2, int weight);
    
    void disconnectEmployees(std::string registrationNumber1,
                                std::string registrationNumber2);
    
    int findEmployeeIndex(std::string registrationNumber);
    
    int getNumberOfEmployees();
    
    Employee *findEmployee(std::string registrationNumber);
    
    void printEmployees();
    
    int shortestDistanceBetweenEmployees(std::string regNum1, std::string regNum2);
    
    void breadthFirstSearch(std::string registrationNumber);
    
    void depthFirstSearch(std::string registrationNumber);
    
    int findMinKey(int key[], bool mstSet[]);
    
    void primMST();
};

#endif