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

char userInteractionLoop() {
    char choice;
    bool validInput = false;

    while (!validInput) {
        cout << "Which street would you like to view the data on? \nEnter a single letter: ";
        cin >> choice;

        // Check if input is a single letter
        if (cin.fail() || !isalpha(choice) || cin.get() != '\n') {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a single letter." << endl;
        } else {
            validInput = true;
            cout << "You chose: " << choice << endl;
        }
    }

    return choice;
}

int main() {

    userInteractionLoop();

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
        
    } else {
        cout << "No street name found." << endl;
    }

    // Close the file
    file.close();

    return 0;
}