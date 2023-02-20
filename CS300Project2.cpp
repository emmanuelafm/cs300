//============================================================================
// Name        : CS300Project2.cpp
// Author      : Emmanuela Filev-Mihalak
// Version     : 1.0
// Description : CS300 Project Two
//============================================================================

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <utility>

using namespace std;

// basic course structure with required variables
struct Course {
    string courseId;
    string name;
    vector<string> prerequisites;
};

vector<Course> loadCourses(string fileName) {
    cout << "Loading file " << fileName << endl;

    ifstream inputFile(fileName);
    string currentLine;
    char delimiterChar = ','; 

    vector<Course> courses;
    vector<string> tokens;
    vector<string> prereqs;

    // inspects current line of file
    while (getline(inputFile, currentLine)) {

        stringstream s_stream(currentLine);

        // test stringstream
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, delimiterChar);
            tokens.push_back(substr);
        }

        // make new course object
        Course course;

        // put courseId and name into temporary tokens vector, add rest of line elements to prerequisites vector
        for (int i = 0; i < tokens.size(); ++i) {
  
            if (i == 0) {
                course.courseId = tokens.at(i);
            }
            if (i == 1) {
                course.name = tokens.at(i);
            }
            else {
                course.prerequisites.push_back(tokens.at(i));
            }
        }
        courses.push_back(course);
        // clear temp vector
        tokens.clear();

    }
    cout << courses.size() << " courses loaded\n" << endl;

    return courses;
}

void displayCourses(Course course) {
    // prints all courses
    cout << course.courseId << ", ";
    cout << course.name << ", ";
    for (int i = 0; i < course.prerequisites.size(); ++i) {
        cout << course.prerequisites.at(i) << ", ";
    }
    cout << endl;
}

int partition(vector<Course>& courses, int begin, int end) {
    //set low and high equal to begin and end
    int low = begin;
    int high = end;
    // pick the middle element as pivot point
    string pivot = courses[low + (high - low) / 2].courseId;
    while (low < high) {
        while (courses[low].courseId.compare(pivot) > 0) {
            ++low;
        }
        while (courses[high].courseId.compare(pivot) < 0) {
            --high;
        }
        if (low < high) {
            swap(courses.at(low), courses.at(high));
            ++low;
            --high;
        }
    }
    return high;
}

void quickSort(vector<Course>& courses, int begin, int end) {
    //set mid equal to 0
    int mid = 0;

    /* Base case: If there are 1 or zero courses to sort,
     partition is already sorted otherwise if begin is greater
     than or equal to end then return*/
    if (begin >= end) {
        return;
    }

    /* Partition courses into low and high such that
 midpoint is location of last element in low */
    mid = partition(courses, begin, end);

    // recursively sort
    quickSort(courses, begin, mid);
    quickSort(courses, mid + 1, end);

}

int main(int argc, char* argv[]) {
    // process command line arguments
    string fileName;
    switch (argc) {
    case 2:
        fileName = argv[1];
        break;
    default:
        fileName = "course_info.txt";
    }

    int choice = 0;
    string idEntry; 
    vector<Course> courses;
    Course course;

    cout << "Welcome to the course planner.\n\n" << endl;

    while (choice != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cin >> choice;
        
        switch (choice) {

        case 1:
            // call loadCourses
            courses = loadCourses(fileName); 
            break;

        case 2:
            // quicksort and print
            quickSort(courses, 0, courses.size() - 1);

            // Print sorted data
            for (int i = 0; i < courses.size(); i++) {
                cout << courses[i].courseId << ", ";
                cout << courses[i].name << ", ";
                cout << endl;
            }
            cout << endl;

            break;

        case 3:
            cout << "What course do you want to know about? " << endl;
            cin >> idEntry; 
            // search for one course and print
            for (int i = 0; i < courses.size(); i++) {
                if (idEntry == courses[i].courseId) {
                    cout << courses[i].courseId << ", ";
                    cout << courses[i].name << ", ";
                    for (int j = 0; j < courses[i].prerequisites.size(); ++j) {
                        cout << courses[i].prerequisites[j] << ", ";
                    }
                    cout << endl;
                }
                else {
                    continue;
                }
                cout << endl;
            }
            break;
        }
    }

}