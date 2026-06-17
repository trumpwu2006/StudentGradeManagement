#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Required for std::sort and std::find_if
#include <iomanip>   // Required for std::setw and layout formatting

using namespace std;

// Define the Student structure as required by the assignment spec
struct Student {
    string id;
    string name;
    int score;
};

// ============================================================================
// Section V: Template Function Extension Challenge (Fixed Task)
// ============================================================================
// Generic function to return the maximum of two values of the same type
template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// Generic function to return the minimum of two values of the same type
template <class T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}
// ============================================================================

// Global container: vector to store all student records
vector<Student> students;

// Function 1: Add new student data
void addStudent() {
    Student s;
    cout << "Enter ID: ";
    cin >> s.id;
    
    // Check if the student ID already exists using std::find_if and a Lambda expression
    auto it = find_if(students.begin(), students.end(), [&](const Student& st) {
        return st.id == s.id;
    });

    // Reject the addition if a duplicate ID is found
    if (it != students.end()) {
        cout << "[Error] Student ID already exists. Registration rejected.\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Score: ";
    cin >> s.score;
    
    students.push_back(s);
    cout << "[Success] Student added successfully.\n";
}

// Function 2: List all students
void listAllStudents() {
    if (students.empty()) {
        cout << "[Info] No student records found.\n";
        return;
    }
    
    // Format the output layout cleanly using std::setw
    cout << "-----------------------------------\n";
    cout << left << setw(10) << "ID" << setw(15) << "Name" << "Score\n";
    cout << "-----------------------------------\n";
    for (const auto& s : students) {
        cout << left << setw(10) << s.id << setw(15) << s.name << s.score << "\n";
    }
    cout << "-----------------------------------\n";
}

// Function 3: Sort students by score (Highest to Lowest)
void sortByScore() {
    if (students.empty()) {
        cout << "[Info] No student data available to sort.\n";
        return;
    }
    
    // Sorting utilizing the exact Lambda expression from the assignment specification
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
    });
    
    cout << "[Success] Students sorted by score in descending order.\n";
}

// Function 4: Search for a student by ID
void searchById() {
    string target_id;
    cout << "Enter ID to search: ";
    cin >> target_id;

    // Linearly search the vector for the matching ID
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) {
        return s.id == target_id;
    });

    if (it != students.end()) {
        cout << "[Found] ID: " << it->id << ", Name: " << it->name << ", Score: " << it->score << "\n";
    } else {
        cout << "[Not Found] No student found with ID: " << target_id << "\n";
    }
}

// Function 5: Show statistics (Integrating the Template Functions)
void showStatistics() {
    if (students.empty()) {
        cout << "[Info] No student data available to calculate statistics.\n";
        return;
    }

    int total_score = 0;
    int max_s = students[0].score;
    int min_s = students[0].score;
    int pass_count = 0;
    int fail_count = 0;

    for (const auto& s : students) {
        total_score += s.score;
        
        // CRITICAL: Calling the custom Template Functions here as required by Section V
        max_s = getMax(max_s, s.score); 
        min_s = getMin(min_s, s.score);

        if (s.score >= 60) {
            pass_count++;
        } else {
            fail_count++;
        }
    }

    // Calculate the class average grade
    double average = static_cast<double>(total_score) / students.size();

    // Display the statistical summary report
    cout << "--- Statistics ---\n";
    cout << "Average Score : " << fixed << setprecision(2) << average << "\n";
    cout << "Max Score     : " << max_s << " (Calculated via template getMax)\n";
    cout << "Min Score     : " << min_s << " (Calculated via template getMin)\n";
    cout << "Pass Count    : " << pass_count << "\n";
    cout << "Fail Count    : " << fail_count << "\n";
    cout << "------------------\n";
}

// Main Function: Program Entry Point and Menu System Interface
int main() {
    int choice;
    do {
        // Standard interactive command-line interface menu options
        cout << "\n=== Student Grade Management ===\n";
        cout << "1. Add student\n";
        cout << "2. List all students\n";
        cout << "3. Sort by score\n";
        cout << "4. Search by id\n";
        cout << "5. Show statistics\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: listAllStudents(); break;
            case 3: sortByScore(); break;
            case 4: searchById(); break;
            case 5: showStatistics(); break;
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "[Error] Invalid selection! Please choose a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}