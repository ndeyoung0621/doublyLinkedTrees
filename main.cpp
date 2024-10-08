#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "linkedList.hpp"
#include <cctype> // For std::isdigit()

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
    iss >> streetName; // Extract the first word as the street name
    return streetName;
}

// Function to process each line and add numbers to the appropriate linkedList
void processLine(const string& line, linkedList& dataList) {
    istringstream iss(line);
    string token;

    while (iss >> token) {
        if (isNumber(token)) {
            int number = stoi(token); // Convert string to integer
            dataList.insert(number);  // Insert into linked list
        }
    }
}

// Function to read and process data from the file
void writeFromDataFile(ifstream& file, map<string, linkedList>& linkedLists) {
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

//method to write all of the mapped lists back to the data file after the program is done (all data entered)
void writeBackToFile(const map<string, linkedList>& linkedLists, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open the file for writing!" << endl;
        return;
    }

    for (const auto& entry : linkedLists) {
        file << entry.first; 
        Node* current = entry.second.getHead(); 
        while (current != nullptr) {
            file << " " << current->data; 
            current = current->next;
        }
        file << endl; 
    }

    file.close();
    cout << "Data written back to " << filename << endl;
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

//A loop that is always running until exited, handles user input
void userInteractionLoop(map<string, linkedList>& linkedLists) {
    bool running = true;

    while (running) {
        string choice;
        cout << "Would you like to view all data, zoom in on a street, insert data, or exit? (all/street name/insert/exit): ";
        getline(cin, choice);

        if (choice == "exit") {
            running = false;
            cout << "Exiting program." << endl;
        } else if (choice == "insert") {
            string streetName;
            cout << "Enter the street name: ";
            getline(cin, streetName);

            // Validate street name
            if (!isValidStreetName(streetName)) {
                cout << "Invalid street name." << endl;
                continue;
            }

            int treeCount;
            cout << "Enter the number of trees: ";
            cin >> treeCount;
            cin.ignore(); // Clear newline character

            // Insert data into the linked list
            if (linkedLists.find(streetName) == linkedLists.end()) {
                linkedLists[streetName] = linkedList();
            }
            linkedLists[streetName].insert(treeCount);

            cout << "Data inserted for " << streetName << "." << endl;

        } else if (choice == "all" || choice == "All") {
            // Iterate over the map and print each street's linked list
            for (const auto& entry : linkedLists) {
                cout << "Street: " << entry.first << endl;
                entry.second.printList();  // Print the linked list for the street
            }
        } else if (linkedLists.find(choice) != linkedLists.end()) {
            string navigateChoice;
            cout << "Would you like to traverse through the blocks of " << choice << "? (y/n): ";
            cin >> navigateChoice;
            cin.ignore();  // Clear newline after 'cin'

            cout << "User chose: " << navigateChoice << endl;

            if (navigateChoice == "y" || navigateChoice == "Y") {
                cout << "Starting traversal..." << endl;
                linkedLists[choice].navigateList();  // Call navigateList to traverse the blocks
            } else {
                cout << "Not traversing the list." << endl;
            }
        } else {
            cout << "No data found for the selected street: " << choice << endl;
        }
    }
}

//structural proceedings
int main() {
    map<string, linkedList> linkedLists;

    ifstream file("TreeData.dat");

    writeFromDataFile(file, linkedLists);

    file.close();

    userInteractionLoop(linkedLists);

    writeBackToFile(linkedLists, "TreeData.dat");

    return 0;
}