#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Pre relase branch created
using namespace std;


#ifdef PRE_RELEASE
#define LOG(x) cout << "PRE-RELEASE: " << x << endl;
const string DataFileName = "StudentData_Emails1.txt";
struct STUDENT_DATA { // Structure to hold student data
    string FirstName;
    string LastName;
    string Email;
};
#else
#define LOG(x) cout << "MACRO: " << x << endl;
const string DataFileName = "StudentData.txt";
struct STUDENT_DATA { // Structure to hold student data
    string FirstName;
    string LastName;
};
#endif
#define LOG(x)


int main() {

#ifdef PRE_RELEASE

    cout << "PRE RELEASE Running" << endl;
#else
    cout << "STANDARD Running" << endl;
#endif
    ifstream StudentDataFile(DataFileName); // Open the StudentData file
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

#ifdef PRE_RELEASE

        size_t commaPos2 = Line.find(',', commaPos + 1);
#endif
        if (commaPos == string::npos) { // Check to see if the line on the file does not have a comma
            cout << "Invalid line format on: " << LineNum << endl; // Error message
            continue;
        }
        else { // If the line has a comma
            STUDENT_DATA student; // Create the student class
            if (LineNum > 1) { // Make sure the line on the file isnt the first line for formating
#ifdef PRE_RELEASE
                student.LastName = Line.substr(0, commaPos);
                student.FirstName = Line.substr(commaPos + 2, commaPos2 - commaPos - 2);
                student.Email = Line.substr(commaPos2 + 2);
                studentVector.push_back(student); // Push the student class data into the student data vector space
#else
                student.LastName = Line.substr(0, commaPos); // Populate the lastname in student class from file
                student.FirstName = Line.substr(commaPos + 2); // Populate the first name in student class form file
                studentVector.push_back(student); // Push the student class data into the student data vector space
#endif
            }
        }
    }

    StudentDataFile.close(); // Close the file
    LineNum = 0;

#ifdef _DEBUG
#ifdef PRE_RELEASE
    // Print the student data vector space
    for (const STUDENT_DATA& student : studentVector) {
        cout << "Last Name: " << student.LastName << ", First Name: " << student.FirstName << ", Email: " << student.Email << endl;
    }

#else
    cout << "DEBUG Running" << endl;
    // Print the student data vector space
    for (const STUDENT_DATA& student : studentVector) {
        cout << "Last Name: " << student.LastName << ", First Name: " << student.FirstName << endl;
    }
#endif
#endif
   
    return 0;
}
