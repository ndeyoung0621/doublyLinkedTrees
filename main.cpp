#include <iostream>
#include <fstream>
#include <sstream>  // For std::istringstream
#include <string>
#include "linkedList.hpp"
#include <cctype> // For std:isdigit()

using namespace std;

//Having all nonspecific helper files in main is not best practice but is in place
//for this project due to three allocated files and naming conventions being forced

// Function to check if a string is a number
bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Function to check if a specific string is present in the line
bool containsString(const std::string& line, const std::string& searchStr) {
    return line.find(searchStr) != std::string::npos;
}

// Function to process each line
void processLine(const std::string& line, string& streetName, linkedList& dataList) {
    std::istringstream iss(line);
    std::string token;

    cout << "Street Name: " << streetName << endl;

    // Extract numbers and add them to the linkedList
    while (iss >> token) {
        if (isNumber(token)) {
            int number = std::stoi(token); // Convert string to integer
            dataList.insert(number); 
            cout << "Number added: " << number << " to Street: " << streetName << endl;
        } 
    }
}

// Function to read and parse data from the file
void readDataFile(ifstream &file, string &streetName, linkedList &streetData) {
    // Check if the file is open before attempting to read
    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return;
    }

    string line;

    while(getline(file, line)) {  // Read a line from the file
        if(containsString(line, streetName)) {
            cout << "Line Process Step" << endl;
            processLine(line, streetName, streetData);
        }
    }
}

// Function to check if a string is valid (contains only alphabetic characters and spaces)
bool isValidStreetName(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
    }
    return true;
}

string userInteractionLoop() {
    std::string choice;
    bool validInput = false;

    while (!validInput) {
        cout << "Which street would you like to view the data on? \nEnter a full street name: ";
        std::getline(cin, choice);

        // Check if the input is a valid street name
        if (choice.empty() || !isValidStreetName(choice)) {
            cout << "Invalid input. Please enter a valid street name containing only alphabetic characters and spaces." << endl;
        } else {
            validInput = true;
            cout << "You chose: " << choice << endl;
        }
    }

    return choice;
}

int main() {

    string userChoice = userInteractionLoop();

    linkedList Indiana;
    
    // Open the file
    ifstream file("TreeData.dat");

    // Read and parse the data from the file
    readDataFile(file, userChoice, Indiana);
    
    // Close the file
    file.close();

    return 0;
}