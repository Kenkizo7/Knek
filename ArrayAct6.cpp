#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

struct Student {
    int id;
    string name;
    float gpa;
};

void displayMenu() {
    cout << "Menu:\n";
    cout << "[1] Add Student\n";
    cout << "[2] Edit Student\n";
    cout << "[3] Delete Student\n";
    cout << "[4] View Students\n";
    cout << "[5] Exit Program\n";
    cout << "Select option: ";
}

void clearScreen() {
    system("cls"); 
}

void editStudent(vector<Student>& students, int id) {
    auto it = find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
    if (it == students.end()) {
        cout << "Student ID not found.\n";
        return;
    }

    cout << "Enter new name (" << it->name << "): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, it->name);

    cout << "Enter new GPA (" << it->gpa << "): ";
    float gpa;
    while (!(cin >> gpa)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter new GPA (" << it->gpa << "): ";
    }
    it->gpa = gpa;

    cout << "Student updated successfully.\n";
}

void editStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records to edit.\n";
        return;
    }

    int id;
    cout << "Enter Student ID to edit: ";
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter Student ID: ";
    }

    editStudent(students, id);
}

void addStudent(vector<Student>& students) {
    Student newStudent;

    cout << "Enter Student ID: ";
    while (!(cin >> newStudent.id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter Student ID: ";
    }

    auto it = find_if(students.begin(), students.end(), [newStudent](const Student& s) { return s.id == newStudent.id; });
    if (it != students.end()) {
        char choice;
        cout << "Student ID already exists. Edit this student? (Y/N): ";
        cin >> choice;
        if (toupper(choice) == 'Y') {
            editStudent(students, newStudent.id);
        } else {
            cout << "Add operation cancelled.\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Student Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newStudent.name);

    cout << "Enter Student GPA: ";
    while (!(cin >> newStudent.gpa)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter Student GPA: ";
    }

    students.push_back(newStudent);
    cout << "Student added successfully.\n";
}

void deleteStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records to delete.\n";
        return;
    }

    int id;
    cout << "Enter Student ID to delete: ";
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter Student ID: ";
    }

    auto it = find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
    if (it == students.end()) {
        cout << "Student ID not found.\n";
        return;
    }

    char confirm;
    cout << "Are you sure you want to delete student " << id << "? (Y/N): ";
    cin >> confirm;
    if (toupper(confirm) == 'Y') {
        students.erase(it);
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records to view.\n";
        return;
    }

    cout << "Viewing options:\n";
    cout << "[1] Alphabetically by name\n";
    cout << "[2] By GPA (ascending)\n";
    cout << "Select option: ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option. Select 1 or 2: ";
    }

    vector<Student> sortedStudents = students;

    if (choice == 1) {
        sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
            return a.name < b.name;
        });
        cout << "Students sorted alphabetically:\n";
    } else {
        sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
            return a.gpa < b.gpa;
        });
        cout << "Students sorted by GPA (ascending):\n";
    }

    for (const auto& s : sortedStudents) {
        cout << "ID: " << s.id << "\tName: " << s.name << "\tGPA: " << s.gpa << endl;
    }
}

int main() {
    vector<Student> students;
    int choice;

    do {
        displayMenu();
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        clearScreen();

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                editStudent(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                viewStudents(students);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

        if (choice != 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            clearScreen();
        }
    } while (choice != 5);

    return 0;
}