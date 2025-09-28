#include <iostream>
#include <vector>
#include <string>
#include <fstream> // File handling
using namespace std;

// ================= Student Class =================
class Student {
public:
    string name;
    int roll;
    float marks;

    Student(string n, int r, float m) {
        name = n;
        roll = r;
        marks = m;
    }
};

// ================ Student Manager Class ================
class StudentManager {
private:
    vector<Student> students; // সব student save হবে এখানে

    // File থেকে student load করা
    void loadFromFile() {
        ifstream file("students.txt");
        if(!file) return; // File না থাকলে skip
        string n;
        int r;
        float m;
        while(file >> n >> r >> m) {
            Student s(n,r,m);
            students.push_back(s);
        }
        file.close();
    }

    // File এ সব student save করা
    void saveToFile() {
        ofstream file("students.txt");
        for(auto s : students) {
            file << s.name << " " << s.roll << " " << s.marks << endl;
        }
        file.close();
    }

public:
    StudentManager() {
        loadFromFile(); // program start হলে file থেকে load
    }

    void addStudent() {
        string name;
        int roll;
        float marks;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Roll: ";
        cin >> roll;
        cout << "Enter Marks: ";
        cin >> marks;

        Student s(name, roll, marks);
        students.push_back(s);
        saveToFile(); // File update
        cout << "Student added successfully!\n";
    }

    void displayStudents() {
        if(students.empty()) {
            cout << "No students found.\n";
            return;
        }

        cout << "\n===== Student List =====\n";
        for(auto s : students) {
            cout << "Name: " << s.name
                 << ", Roll: " << s.roll
                 << ", Marks: " << s.marks << endl;
        }
    }

    void searchStudent() {
        int r;
        cout << "Enter Roll to search: ";
        cin >> r;

        for(auto s : students) {
            if(s.roll == r) {
                cout << "Found! Name: " << s.name
                     << ", Marks: " << s.marks << endl;
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void updateStudent() {
        int r;
        cout << "Enter Roll to update: ";
        cin >> r;

        for(auto &s : students) {
            if(s.roll == r) {
                cout << "Enter new Name: ";
                cin >> s.name;
                cout << "Enter new Marks: ";
                cin >> s.marks;
                saveToFile(); // File update
                cout << "Updated successfully!\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }
};

// =================== Main Function ===================
int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.displayStudents(); break;
            case 3: manager.searchStudent(); break;
            case 4: manager.updateStudent(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while(choice != 0);

    return 0;
}
