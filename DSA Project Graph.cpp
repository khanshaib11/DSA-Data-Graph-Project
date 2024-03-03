#include <iostream>
#include <queue>
#include <deque>
#include <fstream> 
#include <sstream> 
using namespace std;

const int MAX_EMPLOYEES = 200;

struct Employee {
    string registrationNumber;
    int age;
    string gender;
    string educationLevel;
    string jobTitle;
    int yearsOfExperience;
    int salary;
    Employee* next;

    Employee(string regNum, int empAge, string empGender, string eduLvl, string jobTtl, int exp, int empSalary) {
        registrationNumber = regNum;
        age = empAge;
        gender = empGender;
        educationLevel = eduLvl;
        jobTitle = jobTtl;
        yearsOfExperience = exp;
        salary = empSalary;
        next = NULL;
    }
};

class EmployeeManagementSystem {
private:
    int adjacencyMatrix[MAX_EMPLOYEES][MAX_EMPLOYEES];
    Employee* employees[MAX_EMPLOYEES];
    int numEmployees;

public:
    EmployeeManagementSystem() {
        for (int i = 0; i < MAX_EMPLOYEES; i++) {
            employees[i] = NULL;
            for (int j = 0; j < MAX_EMPLOYEES; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
        numEmployees = 0;
    }

    void addEmployee(Employee* employee) {
        if (numEmployees < MAX_EMPLOYEES) {
            employees[numEmployees++] = employee;
        }
    }

    void removeEmployee(string registrationNumber) {
        int index = findEmployeeIndex(registrationNumber);
        if (index != -1) {
            delete employees[index];
            employees[index] = NULL;

            for (int i = 0; i < MAX_EMPLOYEES; i++) {
                adjacencyMatrix[index][i] = 0;
                adjacencyMatrix[i][index] = 0;
            }
        }
    }

    void connectEmployees(string registrationNumber1, string registrationNumber2, int weight) {
        int index1 = findEmployeeIndex(registrationNumber1);
        int index2 = findEmployeeIndex(registrationNumber2);
        if (index1 != -1 && index2 != -1) {
            adjacencyMatrix[index1][index2] = weight;
            adjacencyMatrix[index2][index1] = weight;
        }
    }

    void disconnectEmployees(string registrationNumber1, string registrationNumber2) {
        int index1 = findEmployeeIndex(registrationNumber1);
        int index2 = findEmployeeIndex(registrationNumber2);
        if (index1 != -1 && index2 != -1) {
            adjacencyMatrix[index1][index2] = 0;
            adjacencyMatrix[index2][index1] = 0;
        }
    }

    int findEmployeeIndex(string registrationNumber) {
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i] != NULL && employees[i]->registrationNumber == registrationNumber) {
                return i;
            }
        }
        return -1;
    }
    
    int getNumberOfEmployees() {
        int count = 0;
        for (int i = 0; i < MAX_EMPLOYEES; i++) {
            if (employees[i] != NULL) {
                count++;
            }
        }
        return count;
    }

    Employee* findEmployee(string registrationNumber) {
        int index = findEmployeeIndex(registrationNumber);
        if (index != -1) {
            return employees[index];
        }
        return NULL;
    }

    void printEmployees() {
        for (int i = 0; i < MAX_EMPLOYEES; i++) {
            if (employees[i] != NULL) {
                cout << "Employee: " << employees[i]->registrationNumber << endl;
                cout << "Age: " << employees[i]->age << endl;
                cout << "Gender: " << employees[i]->gender << endl;
                cout << "Education Level: " << employees[i]->educationLevel << endl;
                cout << "Job Title: " << employees[i]->jobTitle << endl;
                cout << "Years of Experience: " << employees[i]->yearsOfExperience << endl;
                cout << "Salary: " << employees[i]->salary << endl;
                cout << endl;
            }
        }
    }

    int shortestDistanceBetweenEmployees(string regNum1, string regNum2) {
        int index1 = findEmployeeIndex(regNum1);
        int index2 = findEmployeeIndex(regNum2);
        if (index1 != -1 && index2 != -1) {
            int distance[MAX_EMPLOYEES];
            bool visited[MAX_EMPLOYEES];

            for (int i = 0; i < MAX_EMPLOYEES; i++) {
                distance[i] = 9999;
                visited[i] = false;
            }

            distance[index1] = 0;

            for (int i = 0; i < MAX_EMPLOYEES - 1; i++) {
                int minDistance = 9999;
                int minIndex = -1;
                for (int j = 0; j < MAX_EMPLOYEES; j++) {
                    if (!visited[j] && distance[j] <= minDistance) {
                        minDistance = distance[j];
                        minIndex = j;
                    }
                }

                visited[minIndex] = true;

                for (int j = 0; j < MAX_EMPLOYEES; j++) {
                    if (!visited[j] && adjacencyMatrix[minIndex][j] != 0 && distance[minIndex] != 9999 &&
                        distance[minIndex] + adjacencyMatrix[minIndex][j] < distance[j]) {
                        distance[j] = distance[minIndex] + adjacencyMatrix[minIndex][j];
                    }
                }
            }

            return distance[index2];
        }

        return -1;
    }

    void breadthFirstSearch(string registrationNumber) {
        int index = findEmployeeIndex(registrationNumber);
        if (index != -1) {
            bool visited[MAX_EMPLOYEES];
            for (int i = 0; i < MAX_EMPLOYEES; i++) {
                visited[i] = false;
            }

            queue<int> employeeQueue;
            employeeQueue.push(index);
            visited[index] = true;

            cout << "BFS Traversal starting from " << registrationNumber << ": ";
            while (!employeeQueue.empty()) {
                int currentIndex = employeeQueue.front();
                employeeQueue.pop();
                cout << employees[currentIndex]->registrationNumber << " ";

                for (int i = 0; i < MAX_EMPLOYEES; i++) {
                    if (!visited[i] && adjacencyMatrix[currentIndex][i] != 0) {
                        employeeQueue.push(i);
                        visited[i] = true;
                    }
                }
            }
            cout << endl;
        }
    }

    void depthFirstSearch(string registrationNumber) {
        int index = findEmployeeIndex(registrationNumber);
        if (index != -1) {
            bool visited[MAX_EMPLOYEES];
            for (int i = 0; i < MAX_EMPLOYEES; i++) {
                visited[i] = false;
            }

            deque<int> employeeStack;
            employeeStack.push_back(index);

            cout << "DFS Traversal starting from " << registrationNumber << ": ";
            while (!employeeStack.empty()) {
                int currentIndex = employeeStack.back();
                employeeStack.pop_back();

                if (!visited[currentIndex]) {
                    cout << employees[currentIndex]->registrationNumber << " ";
                    visited[currentIndex] = true;
                }

                for (int i = 0; i < MAX_EMPLOYEES; i++) {
                    if (!visited[i] && adjacencyMatrix[currentIndex][i] != 0) {
                        employeeStack.push_back(i);
                    }
                }
            }
            cout << endl;
        }
    } 
    
    int findMinKey(int key[], bool mstSet[]){
	    int minKey = 9999;
	    int minIndex = -1;
	
	    for (int v = 0; v < MAX_EMPLOYEES; v++)
	    {
	        if (!mstSet[v] && key[v] < minKey)
	        {
	            minKey = key[v];
	            minIndex = v;
	        }
	    }
	
	    return minIndex;
	}

    
    void primMST(){
	    int parent[MAX_EMPLOYEES];
	    int key[MAX_EMPLOYEES];
	    bool mstSet[MAX_EMPLOYEES];
	
	    for (int i = 0; i < MAX_EMPLOYEES; i++)
	    {
	        key[i] = 9999;
	        mstSet[i] = false;
	    }
	
	    key[0] = 0;
	    parent[0] = -1;
	
	    for (int count = 0; count < MAX_EMPLOYEES - 1; count++)
	    {
	        int u = findMinKey(key, mstSet);
	        mstSet[u] = true;
	
	        for (int v = 0; v < MAX_EMPLOYEES; v++)
	        {
	            if (adjacencyMatrix[u][v] != 0 && !mstSet[v] && adjacencyMatrix[u][v] < key[v])
	            {
	                parent[v] = u;
	                key[v] = adjacencyMatrix[u][v];
	            }
	        }
	    }
	
	    cout << "Minimum Cost Spanning Tree (MST):" << endl;
	    for (int i = 1; i < MAX_EMPLOYEES; i++)
	    {
	        cout << employees[parent[i]]->registrationNumber << " - " << employees[i]->registrationNumber << endl;
	    }
	}

};

int main() {
    EmployeeManagementSystem system;
    
    ifstream inputFile("data.csv");
    if (!inputFile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    vector<Employee*> employeeData;

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string regNum, gender, eduLvl, jobTtl;
        int age, exp, salary;

        if (getline(ss, regNum, ',') &&
            ss >> age && ss.ignore() &&
            getline(ss, gender, ',') &&
            getline(ss, eduLvl, ',') &&
            getline(ss, jobTtl, ',') &&
            ss >> exp && ss.ignore() &&
            ss >> salary)
        {
            Employee* emp = new Employee(regNum, age, gender, eduLvl, jobTtl, exp, salary);
            employeeData.push_back(emp);
        } else {
            cerr << "Invalid data format in the CSV file." << endl;
            return 1;
        }
    }

    inputFile.close();

    for (size_t i = 0; i < employeeData.size(); i++) {
        system.addEmployee(employeeData[i]);
    }

	int choice;
	string regNum1, regNum2;
	string regNum, gender, eduLevel, jobTitle; int age, yearsExp, salary;
	
	while (true) {
        cout << "\n========== Main Menu ==========" << endl;
	    cout << "1. Print Employees" << endl;
	    cout << "2. Add Employee" << endl;
	    cout << "3. Remove Employee" << endl;
	    cout << "4. Connect Employees" << endl;
	    cout << "5. Disconnect Employees" << endl;
	    cout << "6. Shortest Distance Between Employees" << endl;
	    cout << "7. Perform BFS Traversal" << endl;
	    cout << "8. Perform DFS Traversal" << endl;
	    cout << "9. Find Minimum Spanning Tree using Prim's Algorithm" << endl;
	    cout << "10. Total No. of Employees"<<endl;
	    cout << "11. Exit" << endl;
        cout << "===============================" << endl;
	    cout << "Enter your choice: ";
	    cin >> choice;
	
	    if (choice == 1) {
	        system.printEmployees();
	    } else if (choice == 2) {
	        cout << "Enter registration number: ";
	        cin >> regNum;
	        cout << "Enter age: ";
	        cin >> age;
	        cout << "Enter gender: ";
	        cin >> gender;
	        cout << "Enter education level: ";
	        cin >> eduLevel;
	        cout << "Enter job title: ";
	        cin >> jobTitle;
	        cout << "Enter years of experience: ";
	        cin >> yearsExp;
	        cout << "Enter salary: ";
	        cin >> salary;
	        Employee* newEmployee = new Employee(regNum, age, gender, eduLevel, jobTitle, yearsExp, salary);
	        system.addEmployee(newEmployee);
	        cout << "Employee added successfully!" << endl;
	    } else if (choice == 3) {
	        cout << "Enter registration number of the employee to be removed: ";
	        cin >> regNum;
	        system.removeEmployee(regNum);
	        cout << "Employee removed successfully!" << endl;
	    } else if (choice == 4) {
	        int weight;
	        cout << "Enter registration number of the first employee: ";
	        cin >> regNum1;
	        cout << "Enter registration number of the second employee: ";
	        cin >> regNum2;
	        cout << "Enter weight of the connection: ";
	        cin >> weight;
	        system.connectEmployees(regNum1, regNum2, weight);
	        cout << "Employees connected successfully!" << endl;
	    } else if (choice == 5) {
	        cout << "Enter registration number of the first employee: ";
	        cin >> regNum1;
	        cout << "Enter registration number of the second employee: ";
	        cin >> regNum2;
	        system.disconnectEmployees(regNum1, regNum2);
	        cout << "Employees disconnected successfully!" << endl;
	    } else if (choice == 6) {
	        cout << "Enter registration number of the first employee: ";
	        cin >> regNum1;
	        cout << "Enter registration number of the second employee: ";
	        cin >> regNum2;
	        cout<<endl<<"Shortest Distance : "<<system.shortestDistanceBetweenEmployees(regNum1, regNum2)<<endl<<endl;
	    } else if (choice == 7) {
	        cout << "Enter registration number of the starting employee: ";
	        cin >> regNum;
	        system.breadthFirstSearch(regNum);
	    } else if (choice == 8) {
	        cout << "Enter registration number of the starting employee: ";
	        cin >> regNum;
	        system.depthFirstSearch(regNum);
	    } else if (choice == 9) {
	        system.primMST();
	    } else if(choice == 10){
	    	cout<<"Total No. of Employees : "<<system.getNumberOfEmployees()<<endl;
		} else if (choice == 11) {
	        cout << "Exiting Employee Management System..." << endl;
	        exit(0);
	    } else {
	        cout << "Invalid choice! Please try again." << endl;
	    }
	}


    return 0;
}

