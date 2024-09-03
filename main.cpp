#include <iostream>
#include <fstream>
#include <sstream>  // For std::istringstream
#include <string>   

using namespace std;

void readDataFile(ifstream &file, string &streetName, int &dataValue) { 
    //this file reads the data from TreeData.dat, separates it, and returns it as streetName and dataValue
        string line;

        getline(file, line);  

        istringstream iss(line);  

        iss >> streetName >> dataValue;
            
}

int main() {
    ifstream file("TreeData.dat");  // Open the file
    string streetName;
    int dataValue;

    readDataFile(file, streetName, dataValue);  // Pass file stream and variables to the function

    cout << "Street Name: " << streetName << endl;  // Output the street name
    cout << "Data Value: " << dataValue << endl;    // Output the integer value

    file.close();  // Close the file
    return 0;
}
