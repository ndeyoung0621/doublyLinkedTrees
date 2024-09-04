#include <iostream>
#include <fstream>
#include <sstream>  // For std::istringstream
#include <string>
#include "linkedList.hpp"
#include <cctype> // For std:isdigit()

using namespace std;

// Function to check if a string is a number
bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


// Function to process each line
bool processLine(const std::string& line, string& streetName, linkedList& dataList) {
    std::istringstream iss(line);
    std::string token;

    // Extract the street name
    if (iss >> streetName) {
        cout << "Street Name: " << streetName << endl;
    } else {
        cerr << "Failed to read street name from line: " << line << endl;
        return false;
    }

    // Extract numbers and add them to the linkedList
    while (iss >> token) {
        if (isNumber(token)) {
            int number = std::stoi(token); // Convert string to integer
            dataList.insert(number); 
            cout << "Number added: " << number << " to Street: " << streetName << endl;
        } else {
            cerr << "Unexpected token: " << token << endl;
            return false;
        }
    }

    return true;
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
        cout << "Line Process Step" << endl;
        processLine(line, streetName, streetData);
    }
}

int main() {

    linkedList Indiana;
    // Open the file
    ifstream file("TreeData.dat");

    // Variables to hold the data
    string streetName;

    // Read and parse the data from the file
    readDataFile(file, streetName, Indiana);

    // Output the results
    if (!streetName.empty()) {
        cout << "Street Name: " << streetName << endl;
        // Checking list contents
        Indiana.printList();
    } else {
        cout << "No street name found." << endl;
    }

    // Close the file
    file.close();

    return 0;
}