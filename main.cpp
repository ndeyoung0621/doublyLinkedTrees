#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "linkedList.hpp"
#include <cctype> // For std::isdigit()

//note: ranged based for loops are an extension from the stdlib,
//they are in place for simplicity but should an error arise,
//current version of c++ is -Wc++14

using namespace std;

// Helper function to check if a string is a number
bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
} 

// Function to get the street name from a line (assuming it's the first word)
string getStreetName(const string& line) {
    istringstream iss(line);
    string streetName;
    //instead of using a checker this function assumes the street name is the first item in the string stream
    iss >> streetName; // Extract the first word as the street name, 
    return streetName;
}

// Function to process each line and add numbers to the appropriate linkedList
void processLine(const string& line, linkedList& dataList) {
    istringstream iss(line);
    string token;

    // Process the line to extract and insert numbers into the linked list
    while (iss >> token) {
        if (isNumber(token)) {
            int number = stoi(token); // Convert string to integer
            dataList.insert(number);  // Insert into linked list
        }
    }
}

// Function to read and process data from the file
void writeDataFile(ifstream& file, map<string, linkedList>& linkedLists) {
    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string streetName = getStreetName(line);

        // Check if the linkedList for this street already exists, if not create one
        if (linkedLists.find(streetName) == linkedLists.end()) {
            cout << "Creating linkedList for street: " << streetName << endl;
            linkedLists[streetName] = linkedList(); // Create and store new linkedList
        }

        // Process the line and add numbers to the linkedList associated with the street
        processLine(line, linkedLists[streetName]);
    }
}

// Function to check if a string is valid (contains only alphabetic characters and spaces)
bool isValidStreetName(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

// User interaction loop for selecting a street name
string userInteractionLoop() {
    string choice;

    // Ask the user for a street name
    cout << "Which street would you like to view the data on? Type \"exit\" at any time to quit the program. \nEnter a full lowercase street name: ";
    getline(cin, choice);

    return choice;
}

int main() {
    // Map to store linkedList objects for each street
    map<string, linkedList> linkedLists;

    // Open the file
    ifstream file("TreeData.dat");

    // Read and parse the data from the file into the map
    writeDataFile(file, linkedLists);

    // Close the file after processing
    file.close();

    bool running = true;

    // Infinite loop to run until the program is manually quit
    while (running) {
        // User selects the street to view
        string userChoice = userInteractionLoop();

        // Check if the user wants to exit
        if (userChoice == "exit" || userChoice == "Exit") {
            running = false;
            cout << "Exiting program." << endl;

        // Check if the street exists in the map
        } else if (linkedLists.find(userChoice) != linkedLists.end()) {
            cout << "Data for " << userChoice << ":" << endl;

            // Print the list of data for the selected street
            linkedLists[userChoice].printList();  

            // Ask if the user wants to traverse the list
            string navigateChoice;
            cout << "Would you like to traverse through the blocks of " << userChoice << "? (y/n): ";
            cin >> navigateChoice;
            cin.ignore();  // Clear newline after 'cin'

            // Cout to confirm user choice
            cout << "User chose: " << navigateChoice << endl;

            if (navigateChoice == "y" || navigateChoice == "Y") {
                cout << "Starting traversal..." << endl;
                linkedLists[userChoice].navigateList();  // Call navigateList to traverse the blocks
            } else {
                cout << "Not traversing the list." << endl;
            }

        // Handle case when no data exists for the selected street
        } else {
            cout << "No data found for the selected street: " << userChoice << endl;
        } 
    }

    return 0;
}