#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Structure to store course information
struct Course {
    string name;
    int credits;
    double gradePoints;
};

// Function to convert grade to grade points
double convertGradeToPoints(const string &grade) {
    if (grade == "A+" || grade == "A") return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B") return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C") return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D+") return 1.3;
    if (grade == "D") return 1.0;
    if (grade == "F") return 0.0;
    cout << "Invalid grade entered. Defaulting to 0.0." << endl;
    return 0.0;
}

// Class to store semester information and calculate GPA
class Semester {
private:
    vector<Course> courses;
    int totalCredits;
    double totalGradePoints;

public:
    Semester() : totalCredits(0), totalGradePoints(0.0) {}

    void addCourse(const string &name, int credits, const string &grade) {
        double gradePoints = convertGradeToPoints(grade);
        Course course = {name, credits, gradePoints};
        courses.push_back(course);
        totalCredits += credits;
        totalGradePoints += credits * gradePoints;
    }

    double calculateGPA() const {
        if (totalCredits == 0) return 0.0;
        return totalGradePoints / totalCredits;
    }

    int getTotalCredits() const {
        return totalCredits;
    }

    double getTotalGradePoints() const {
        return totalGradePoints;
    }

    void displayCourses() const {
        for (size_t i = 0; i < courses.size(); ++i) {
            cout << "Course: " << courses[i].name 
                 << ", Credits: " << courses[i].credits 
                 << ", Grade Points: " << courses[i].gradePoints << endl;
        }
    }
};

// Class to calculate CGPA over multiple semesters
class CGPACalculator {
private:
    vector<Semester> semesters;

public:
    void addSemester(const Semester &semester) {
        semesters.push_back(semester);
    }

    double calculateCGPA() const {
        int totalCredits = 0;
        double totalGradePoints = 0.0;
        for (size_t i = 0; i < semesters.size(); ++i) {
            totalCredits += semesters[i].getTotalCredits();
            totalGradePoints += semesters[i].getTotalGradePoints();
        }
        if (totalCredits == 0) return 0.0;
        return totalGradePoints / totalCredits;
    }

    void displayAllCourses() const {
        for (size_t i = 0; i < semesters.size(); ++i) {
            cout << "Semester " << i + 1 << ":" << endl;
            semesters[i].displayCourses();
        }
    }
};

int main() {
    CGPACalculator cgpaCalculator;
    char choice;

    do {
        Semester semester;
        int numCourses;
        cout << "Enter the number of courses for this semester: ";
        cin >> numCourses;
        cin.ignore(); // To ignore any leftover newline character

        for (int i = 0; i < numCourses; ++i) {
            string courseName;
            int credits;
            string grade;

            cout << "Enter course " << i + 1 << " name: ";
            getline(cin, courseName);
            cout << "Enter course " << i + 1 << " credits: ";
            while (!(cin >> credits)) {
                cout << "Invalid input. Please enter an integer for credits: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(); // To ignore newline character after entering credits

            cout << "Enter course " << i + 1 << " grade (e.g., A, B+, C-): ";
            getline(cin, grade);

            semester.addCourse(courseName, credits, grade);
        }

        cgpaCalculator.addSemester(semester);

        cout << "Do you want to add another semester? (y/n): ";
        cin >> choice;
        cin.ignore(); // To ignore newline character after entering choice

    } while (choice == 'y' || choice == 'Y');

    cgpaCalculator.displayAllCourses();
    cout << "Cumulative GPA (CGPA): " << cgpaCalculator.calculateCGPA() << endl;

    return 0;
}

