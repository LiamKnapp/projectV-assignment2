#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Pre relase branch created
using namespace std;

#ifdef _DEBUG
#define LOG(x) std::cout << "MACRO: " << x << endl;
#else
#define LOG(x)
#endif // _DEBUG


struct STUDENT_DATA { // Structure to hold student data
    string FirstName;
    string LastName;
};

int main() {

    ifstream StudentDataFile("StudentData.txt"); // Open the StudentData file
    if (!StudentDataFile) { // Check to see if the file had error opening
        cout << "Error opening the file." << endl;
        return 1;
    }

    vector <STUDENT_DATA> studentVector; // Vector to store student data

    int LineNum = 0; // Keep track of the line on the txt file
    string Line;
    while (getline(StudentDataFile, Line)) { // Get the text line by line from the file
        LineNum++; // Increase the line number with each iteration
        size_t commaPos = Line.find(','); // Format the page for the comma seperating the names
        if (commaPos == string::npos) { // Check to see if the line on the file does not have a comma
            cout << "Invalid line format on: " << LineNum << endl; // Error message
            continue;
        }
        else { // If the line has a comma
            if (LineNum > 1) { // Make sure the line on the file isnt the first line for formating
                STUDENT_DATA student; // Create the student class
                student.LastName = Line.substr(0, commaPos); // Populate the lastname in student class from file
                student.FirstName = Line.substr(commaPos + 1); // Populate the first name in student class form file
                studentVector.push_back(student); // Push the student class data into the student data vector space
            }
        }
    }

    StudentDataFile.close(); // Close the file

#ifdef _DEBUG
    cout << "DEBUG Running" << endl;
    // Print the student data vector space
    for (const STUDENT_DATA& student : studentVector) {
         cout << "Last Name: " << student.LastName << ", First Name: " << student.FirstName << endl;
    }
#endif
   
    return 0;
}
