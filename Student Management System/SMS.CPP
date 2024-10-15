#include <iostream>
#include <iomanip>  
#include <string>

using namespace std;

struct Student {
    int id;
    string name;
    int rollNumber;
    int age;
    string course;
    Student* next;  
};


void insertStudent(Student*& head);
void searchStudent(Student* head);
void countStudents(Student* head);
void updateStudent(Student* head);
void deleteStudent(Student*& head);
void showAllStudents(Student* head);
void sortStudentsByRollNumber(Student*& head);
void menu();


void swapStudents(Student* a, Student* b);

int main() {
    Student* head = nullptr;  
    int choice;

    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertStudent(head);
                break;
            case 2:
                searchStudent(head);
                break;
            case 3:
                countStudents(head);
                break;
            case 4:
                updateStudent(head);
                break;
            case 5:
                deleteStudent(head);
                break;
            case 6:
                showAllStudents(head);
                break;
            case 7:
                sortStudentsByRollNumber(head);
                showAllStudents(head);  
                break;
            case 8:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}


void menu() {
    cout << "\n--- Student Management System ---\n";
    cout << "1. Insert Student\n";
    cout << "2. Search Student\n";
    cout << "3. Count Students\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Show All Students\n";
    cout << "7. Sort Students by Roll Number\n";
    cout << "8. Exit\n";
}


void insertStudent(Student*& head) {
    int id, rollNumber;
    
    
    cout << "Enter student ID: ";
    cin >> id;
    

    Student* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Error: ID " << id << " is already taken.\n";
            return;  
        }
        temp = temp->next;
    }
    
    cout << "Enter student roll number: ";
    cin >> rollNumber;
    
    
    temp = head;  
    while (temp != nullptr) {
        if (temp->rollNumber == rollNumber) {
            cout << "Error: Roll number " << rollNumber << " is already taken.\n";
            return;  
        }
        temp = temp->next;
    }
    
    
    Student* newStudent = new Student;
    newStudent->id = id;
    newStudent->rollNumber = rollNumber;
    
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent->name);
    cout << "Enter student age: ";
    cin >> newStudent->age;
    cout << "Enter student course: ";
    cin.ignore();
    getline(cin, newStudent->course);
    
    newStudent->next = nullptr;

    if (head == nullptr) {
        head = newStudent;
    } else {
        temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }

    cout << "Student added successfully.\n";
}

void searchStudent(Student* head) {
    int id;
    cout << "Enter student ID to search: ";
    cin >> id;

    Student* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Student found: \n";
            cout << "ID: " << temp->id << ", Name: " << temp->name
                 << ", Roll Number: " << temp->rollNumber
                 << ", Age: " << temp->age << ", Course: " << temp->course << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Student with ID " << id << " not found.\n";
}


void countStudents(Student* head) {
    int count = 0;
    Student* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    cout << "Total number of students: " << count << endl;
}


void updateStudent(Student* head) {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    Student* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, temp->name);
            cout << "Enter new roll number: ";
            cin >> temp->rollNumber;
            cout << "Enter new age: ";
            cin >> temp->age;
            cout << "Enter new course: ";
            cin.ignore();
            getline(cin, temp->course);
            cout << "Student record updated successfully.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Student with ID " << id << " not found.\n";
}


void deleteStudent(Student*& head) {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    if (head == nullptr) {
        cout << "No students to delete.\n";
        return;
    }

    
    if (head->id == id) {
        Student* temp = head;
        head = head->next;
        delete temp;
        cout << "Student record deleted successfully.\n";
        return;
    }

    Student* temp = head;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Student with ID " << id << " not found.\n";
    } else {
        Student* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Student record deleted successfully.\n";
    }
}


void showAllStudents(Student* head) {
    if (head == nullptr) {
        cout << "No students to show.\n";
        return;
    }

    cout << "\n--- All Students ---\n";
    cout << setw(10) << left << "ID"
         << setw(20) << left << "Name"
         << setw(15) << left << "Roll Number"
         << setw(5) << left << "Age"
         << setw(15) << left << "Course" << endl;
    cout << string(65, '-') << endl;

    Student* temp = head;
    while (temp != nullptr) {
        cout << setw(10) << left << temp->id
             << setw(20) << left << temp->name
             << setw(15) << left << temp->rollNumber
             << setw(5) << left << temp->age
             << setw(15) << left << temp->course << endl;
        temp = temp->next;
    }
}


void sortStudentsByRollNumber(Student*& head) {
    if (head == nullptr || head->next == nullptr) {
        cout << "Not enough students to sort.\n";
        return;
    }

    bool swapped;
    Student* temp;
    Student* lastPtr = nullptr;

    do {
        swapped = false;
        temp = head;

        while (temp->next != lastPtr) {
            if (temp->rollNumber > temp->next->rollNumber) {
                swapStudents(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
        lastPtr = temp;
    } while (swapped);

    cout << "Students sorted by roll number successfully.\n";
}


void swapStudents(Student* a, Student* b) {
    swap(a->id, b->id);
    swap(a->name, b->name);
    swap(a->rollNumber, b->rollNumber);
    swap(a->age, b->age);
    swap(a->course, b->course);
}


