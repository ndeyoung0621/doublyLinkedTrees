#include <iostream>
#include <fstream>
#include <sstream>  // For std::istringstream
#include <string>
#include "linkedList.hpp"
#include <cctype>

using namespace std;

// Function to read and parse data from the file
void readDataFile(ifstream &file, string &streetName, int &dataValue) {
    // Check if the file is open before attempting to read
    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return;
    }

    string line;
    if (getline(file, line)) {  // Read a line from the file
        istringstream iss(line);  // Create a string stream to parse the line
        if (!(iss >> streetName >> dataValue)) {  // Extract street name and integer value
            cerr << "Error parsing line: " << line << endl;
        }
    } else {
        cerr << "Error reading line from file." << endl;
    }
}

void processLine(const std::string& line) {
    std::istringstream iss(line);
    std::string checkVal;
    
    while (iss >> checkVal) {
        // Check if the token is a number
        if (isdigit(checkVal[0])) {
            cout << checkVal << " is a digit" << std::endl;
        } else {
            cout << checkVal << " is a string" << std::endl;
        }
    }
}


int main() {

    // Open the file
    ifstream file("TreeData.dat");

    // Variables to hold the data
    string streetName;
    int dataValue;

    // Read and parse the data from the file
    readDataFile(file, streetName, dataValue);

    // Output the results
    if (!streetName.empty()) {
        cout << "Street Name: " << streetName << endl;
    } else {
        cout << "No street name found." << endl;
    }
    
    linkedList Indiana;
    Indiana.insert(dataValue);
    Indiana.printList();

    // Close the file
    file.close();

    return 0;
}