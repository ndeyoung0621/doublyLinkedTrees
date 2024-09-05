#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "linkedList.hpp"
#include <cctype> // For std::isdigit()

//note: ranged based for loops are an extension from the stdlib,
//they are in place for simplicity but should an error arise,
//current version is -Wc++11-ext

using namespace std;

// Helper function to check if a string is a number
bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Function to get the street name from a line (assuming it's the first word)
std::string getStreetName(const std::string& line) {
    istringstream iss(line);
    std::string streetName;
    iss >> streetName; // Extract the first word as the street name
    return streetName;
}

// Function to process each line and add numbers to the appropriate linkedList
void processLine(const std::string& line, linkedList& dataList) {
    istringstream iss(line);
    std::string token;

    // Process the line to extract and insert numbers into the linked list
    while (iss >> token) {
        if (isNumber(token)) {
            int number = std::stoi(token); // Convert string to integer
            dataList.insert(number);       // Insert into linked list
        }
    }
}

// Function to read and process data from the file
void writeDataFile(std::ifstream& file, std::map<std::string, linkedList>& linkedLists) {
    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::string streetName = getStreetName(line);

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
bool isValidStreetName(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
    }
    return true;
}

// User interaction loop for selecting a street name
std::string userInteractionLoop() {
    std::string choice;
    bool validInput = false;

    while (!validInput) {
        cout << "Which street would you like to view the data on? Type \"exit\" at any time to quit the program. \nEnter a full lowercase street name: ";
        std::getline(cin, choice);

        // Check if the input is a valid street name
        if (choice.empty() || !isValidStreetName(choice)) {
            cout << "Invalid input. Please enter a valid street name containing only lowercase alphabetic characters." << endl;
        } else {
            validInput = true;
            cout << "You chose: " << choice << endl;
        }
    }

    return choice;
}


int main() {

    // Map to store linkedList objects for each street
    std::map<std::string, linkedList> linkedLists;

    // Open the file
    ifstream file("TreeData.dat");

    // Read and parse the data from the file into the map
    writeDataFile(file, linkedLists);

    // Close the file after processing
    file.close();

    bool running = true;

    //infinite loop to run until program is manually quit
    while(running) {
        // User selects the street to view
        string userChoice = userInteractionLoop();

        // Print the data from the selected street, if it exists
        if (userChoice == "exit" || userChoice == "Exit") {
            running = false;
        } else if (linkedLists.find(userChoice) != linkedLists.end()) {
            cout << "Data for " << userChoice << ":" << endl;
            linkedLists[userChoice].printList(); // Assuming printList is a method in your linkedList class
        } else {
            cout << "No data found for the selected street: " << userChoice << endl;
        }
    }

    return 0;
}