#include "../include/EmployeeManagementSystem.hpp"

EmployeeManagementSystem::EmployeeManagementSystem()
{
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        employees[i] = nullptr;
        for (int j = 0; j < MAX_EMPLOYEES; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }
    numEmployees = 0;
}

EmployeeManagementSystem::~EmployeeManagementSystem()
{
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i] != nullptr)
        {
            delete employees[i];
        }
    }
}

void EmployeeManagementSystem::addEmployee(Employee *employee)
{
    if (numEmployees < MAX_EMPLOYEES)
    {
        employees[numEmployees++] = employee;
    }
}

void EmployeeManagementSystem::removeEmployee(std::string registrationNumber)
{
    int index = findEmployeeIndex(registrationNumber);
    if (index != -1)
    {
        delete employees[index];
        employees[index] = nullptr;

        for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            adjacencyMatrix[index][i] = 0;
            adjacencyMatrix[i][index] = 0;
        }
    }
}

void EmployeeManagementSystem::connectEmployees(std::string registrationNumber1, std::string registrationNumber2, int weight)
{
    int index1 = findEmployeeIndex(registrationNumber1);
    int index2 = findEmployeeIndex(registrationNumber2);
    if (index1 != -1 && index2 != -1)
    {
        adjacencyMatrix[index1][index2] = weight;
        adjacencyMatrix[index2][index1] = weight;
    }
}

void EmployeeManagementSystem::disconnectEmployees(std::string registrationNumber1, std::string registrationNumber2)
{
    int index1 = findEmployeeIndex(registrationNumber1);
    int index2 = findEmployeeIndex(registrationNumber2);
    if (index1 != -1 && index2 != -1)
    {
        adjacencyMatrix[index1][index2] = 0;
        adjacencyMatrix[index2][index1] = 0;
    }
}

int EmployeeManagementSystem::findEmployeeIndex(std::string registrationNumber)
{
    for (int i = 0; i < numEmployees; i++)
    {
        if (employees[i] != nullptr && employees[i]->registrationNumber == registrationNumber)
        {
            return i;
        }
    }
    return -1;
}

int EmployeeManagementSystem::getNumberOfEmployees()
{
    int count = 0;
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i] != nullptr)
        {
            count++;
        }
    }
    return count;
}

Employee *EmployeeManagementSystem::findEmployee(std::string registrationNumber)
{
    int index = findEmployeeIndex(registrationNumber);
    if (index != -1)
    {
        return employees[index];
    }
    return nullptr;
}

void EmployeeManagementSystem::printEmployees()
{
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i] != nullptr)
        {
            std::cout << "Employee: " << employees[i]->registrationNumber << std::endl;
            std::cout << "Age: " << employees[i]->age << std::endl;
            std::cout << "Gender: " << employees[i]->gender << std::endl;
            std::cout << "Education Level: " << employees[i]->educationLevel << std::endl;
            std::cout << "Job Title: " << employees[i]->jobTitle << std::endl;
            std::cout << "Years of Experience: " << employees[i]->yearsOfExperience << std::endl;
            std::cout << "Salary: " << employees[i]->salary << std::endl;
            std::cout << std::endl;
        }
    }
}

int EmployeeManagementSystem::shortestDistanceBetweenEmployees(std::string regNum1, std::string regNum2)
{
    int index1 = findEmployeeIndex(regNum1);
    int index2 = findEmployeeIndex(regNum2);
    if (index1 != -1 && index2 != -1)
    {
        int distance[MAX_EMPLOYEES];
        bool visited[MAX_EMPLOYEES];

        for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            distance[i] = 9999;
            visited[i] = false;
        }

        distance[index1] = 0;

        for (int i = 0; i < MAX_EMPLOYEES - 1; i++)
        {
            int minDistance = 9999;
            int minIndex = -1;
            for (int j = 0; j < MAX_EMPLOYEES; j++)
            {
                if (!visited[j] && distance[j] <= minDistance)
                {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }

            visited[minIndex] = true;

            for (int j = 0; j < MAX_EMPLOYEES; j++)
            {
                if (!visited[j] && adjacencyMatrix[minIndex][j] != 0 && distance[minIndex] != 9999 &&
                    distance[minIndex] + adjacencyMatrix[minIndex][j] < distance[j])
                {
                    distance[j] = distance[minIndex] + adjacencyMatrix[minIndex][j];
                }
            }
        }

        return distance[index2];
    }

    return -1;
}

void EmployeeManagementSystem::breadthFirstSearch(std::string registrationNumber)
{
    int index = findEmployeeIndex(registrationNumber);
    if (index != -1)
    {
        bool visited[MAX_EMPLOYEES];
        for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            visited[i] = false;
        }

        std::queue<int> employeeQueue;
        employeeQueue.push(index);
        visited[index] = true;

        std::cout << "BFS Traversal starting from " << registrationNumber << ": ";
        while (!employeeQueue.empty())
        {
            int currentIndex = employeeQueue.front();
            employeeQueue.pop();
            std::cout << employees[currentIndex]->registrationNumber << " ";

            for (int i = 0; i < MAX_EMPLOYEES; i++)
            {
                if (!visited[i] && adjacencyMatrix[currentIndex][i] != 0)
                {
                    employeeQueue.push(i);
                    visited[i] = true;
                }
            }
        }
        std::cout << std::endl;
    }
}

void EmployeeManagementSystem::depthFirstSearch(std::string registrationNumber)
{
    int index = findEmployeeIndex(registrationNumber);
    if (index != -1)
    {
        bool visited[MAX_EMPLOYEES];
        for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            visited[i] = false;
        }

        std::deque<int> employeeStack;
        employeeStack.push_back(index);

        std::cout << "DFS Traversal starting from " << registrationNumber << ": ";
        while (!employeeStack.empty())
        {
            int currentIndex = employeeStack.back();
            employeeStack.pop_back();

            if (!visited[currentIndex])
            {
                std::cout << employees[currentIndex]->registrationNumber << " ";
                visited[currentIndex] = true;
            }

            for (int i = 0; i < MAX_EMPLOYEES; i++)
            {
                if (!visited[i] && adjacencyMatrix[currentIndex][i] != 0)
                {
                    employeeStack.push_back(i);
                }
            }
        }
        std::cout << std::endl;
    }
}

int EmployeeManagementSystem::findMinKey(int key[], bool mstSet[])
{
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

void EmployeeManagementSystem::primMST()
{
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

    std::cout << "Minimum Cost Spanning Tree (MST):" << std::endl;
    for (int i = 1; i < MAX_EMPLOYEES; i++)
    {
        std::cout << employees[parent[i]]->registrationNumber << " - " << employees[i]->registrationNumber << std::endl;
    }
}