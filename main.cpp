#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// Task Node structure for Singly Linked List
struct Task {
    string date;
    string description;
    int timeSpent;
    bool isCompleted;
    Task* next;

    // Constructor
    Task(string date, string desc, int time, bool completed)
        : date(date), description(desc), timeSpent(time), isCompleted(completed), next(nullptr) {}
};

class WorkLog {
private:
    Task* head;

    // Helper function to find a task by description
    Task* findTask(string description) {
        Task* current = head;
        while (current != nullptr) {
            if (current->description == description) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    // Constructor
    WorkLog() : head(nullptr) {}

    // Destructor to free memory
    ~WorkLog() {
        Task* current = head;
        while (current != nullptr) {
            Task* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    // 1. Insert a new task
    void insertTask() {
        string date, description;
        int timeSpent;
        char completionChoice;
        bool isCompleted;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n=== Add New Task ===\n";
        cout << "Enter date (YYYY-MM-DD): ";
        getline(cin, date);

        cout << "Enter task description: ";
        getline(cin, description);

        cout << "Enter time spent (in minutes): ";
        while (!(cin >> timeSpent) || timeSpent <= 0) {
            cout << "Invalid input. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Is the task completed? (Y/N): ";
        cin >> completionChoice;
        isCompleted = (toupper(completionChoice) == 'Y');

        Task* newTask = new Task(date, description, timeSpent, isCompleted);

        // If list is empty, make the new task the head
        if (head == nullptr) {
            head = newTask;
            cout << "\nTask added successfully!\n";
            return;
        }

        // Otherwise, add to the end of the list
        Task* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTask;
        cout << "\nTask added successfully!\n";
    }

    // 2. Display all tasks
    void displayAllTasks() {
        if (head == nullptr) {
            cout << "\nNo tasks available.\n";
            return;
        }

        cout << "\n=== All Tasks ===\n";
        cout << left << setw(12) << "Date" << setw(40) << "Description"
            << setw(15) << "Time (mins)" << "Status" << endl;
        cout << string(75, '-') << endl;

        Task* current = head;
        while (current != nullptr) {
            cout << left << setw(12) << current->date
                << setw(40) << (current->description.length() > 37
                    ? current->description.substr(0, 37) + "..."
                    : current->description)
                << setw(15) << current->timeSpent
                << (current->isCompleted ? "Completed" : "Pending") << endl;
            current = current->next;
        }
    }

    // 3. Display completed tasks
    void displayCompletedTasks() {
        if (head == nullptr) {
            cout << "\nNo tasks available.\n";
            return;
        }

        cout << "\n=== Completed Tasks ===\n";
        cout << left << setw(12) << "Date" << setw(40) << "Description"
            << setw(15) << "Time (mins)" << "Status" << endl;
        cout << string(75, '-') << endl;

        Task* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->isCompleted) {
                cout << left << setw(12) << current->date
                    << setw(40) << (current->description.length() > 37
                        ? current->description.substr(0, 37) + "..."
                        : current->description)
                    << setw(15) << current->timeSpent << "Completed" << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No completed tasks found.\n";
        }
    }

    // 4. Display pending tasks
    void displayPendingTasks() {
        if (head == nullptr) {
            cout << "\nNo tasks available.\n";
            return;
        }

        cout << "\n=== Pending Tasks ===\n";
        cout << left << setw(12) << "Date" << setw(40) << "Description"
            << setw(15) << "Time (mins)" << "Status" << endl;
        cout << string(75, '-') << endl;

        Task* current = head;
        bool found = false;

        while (current != nullptr) {
            if (!current->isCompleted) {
                cout << left << setw(12) << current->date
                    << setw(40) << (current->description.length() > 37
                        ? current->description.substr(0, 37) + "..."
                        : current->description)
                    << setw(15) << current->timeSpent << "Pending" << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No pending tasks found.\n";
        }
    }

    // 5. Update task
    void updateTask(string description) {
        Task* taskToUpdate = findTask(description);

        if (taskToUpdate == nullptr) {
            cout << "\nTask not found.\n";
            return;
        }

        int choice;
        cout << "\n=== Update Task ===\n";
        cout << "Task found: " << taskToUpdate->description << endl;
        cout << "1. Update time spent\n";
        cout << "2. Update completion status\n";
        cout << "3. Cancel\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter 1, 2, or 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: {
            int newTime;
            cout << "Current time: " << taskToUpdate->timeSpent << " minutes\n";
            cout << "Enter new time (in minutes): ";

            while (!(cin >> newTime) || newTime <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            taskToUpdate->timeSpent = newTime;
            cout << "Time updated successfully!\n";
            break;
        }
        case 2: {
            char completionChoice;
            cout << "Current status: " << (taskToUpdate->isCompleted ? "Completed" : "Pending") << endl;
            cout << "Mark as " << (taskToUpdate->isCompleted ? "pending" : "completed") << "? (Y/N): ";
            cin >> completionChoice;

            if (toupper(completionChoice) == 'Y') {
                taskToUpdate->isCompleted = !taskToUpdate->isCompleted;
                cout << "Status updated successfully!\n";
            }
            else {
                cout << "Status update cancelled.\n";
            }
            break;
        }
        case 3:
            cout << "Update cancelled.\n";
            break;
        }
    }

    // 6. Mark task as completed
    void markTaskCompleted(string description) {
        Task* taskToMark = findTask(description);

        if (taskToMark == nullptr) {
            cout << "\nTask not found.\n";
            return;
        }

        if (taskToMark->isCompleted) {
            cout << "\nThis task is already marked as completed.\n";
            return;
        }

        taskToMark->isCompleted = true;
        cout << "\nTask marked as completed successfully!\n";
    }

    // 7. Delete task
    void deleteTask(string description) {
        if (head == nullptr) {
            cout << "\nNo tasks available.\n";
            return;
        }

        // If the head needs to be deleted
        if (head->description == description) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "\nTask deleted successfully!\n";
            return;
        }

        // Find the task before the one to be deleted
        Task* current = head;
        while (current->next != nullptr && current->next->description != description) {
            current = current->next;
        }

        // If task was found
        if (current->next != nullptr) {
            Task* temp = current->next;
            current->next = temp->next;
            delete temp;
            cout << "\nTask deleted successfully!\n";
        }
        else {
            cout << "\nTask not found.\n";
        }
    }

    // 8. Search for tasks
    void searchTask(string keyword) {
        if (head == nullptr) {
            cout << "\nNo tasks available.\n";
            return;
        }

        transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

        cout << "\n=== Search Results for '" << keyword << "' ===\n";
        cout << left << setw(12) << "Date" << setw(40) << "Description"
            << setw(15) << "Time (mins)" << "Status" << endl;
        cout << string(75, '-') << endl;

        Task* current = head;
        bool found = false;

        while (current != nullptr) {
            string lowerDate = current->date;
            string lowerDesc = current->description;

            transform(lowerDate.begin(), lowerDate.end(), lowerDate.begin(), ::tolower);
            transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);

            if (lowerDate.find(keyword) != string::npos || lowerDesc.find(keyword) != string::npos) {
                cout << left << setw(12) << current->date
                    << setw(40) << (current->description.length() > 37
                        ? current->description.substr(0, 37) + "..."
                        : current->description)
                    << setw(15) << current->timeSpent
                    << (current->isCompleted ? "Completed" : "Pending") << endl;
                found = true;
            }

            current = current->next;
        }

        if (!found) {
            cout << "No matching tasks found.\n";
        }
    }

    // 9. Calculate total time spent
    void calculateTotalTime() {
        if (head == nullptr) {
            cout << "\nNo tasks available.\n";
            return;
        }

        int totalTime = 0;
        int completedTime = 0;
        int pendingTime = 0;
        int taskCount = 0;

        Task* current = head;

        while (current != nullptr) {
            totalTime += current->timeSpent;
            taskCount++;

            if (current->isCompleted) {
                completedTime += current->timeSpent;
            }
            else {
                pendingTime += current->timeSpent;
            }

            current = current->next;
        }

        cout << "\n=== Time Report ===\n";
        cout << "Total tasks: " << taskCount << endl;
        cout << "Total time spent: " << totalTime << " minutes ("
            << (totalTime / 60) << " hours, " << (totalTime % 60) << " minutes)" << endl;
        cout << "Time on completed tasks: " << completedTime << " minutes" << endl;
        cout << "Time on pending tasks: " << pendingTime << " minutes" << endl;
    }
};

// 10. Menu function
void menu() {
    WorkLog workLog;
    int choice;
    string searchKeyword, taskDescription;

    do {
        cout << "\n==============================\n";
        cout << "  EMPLOYEE WORK LOG SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Add New Task\n";
        cout << "2. Display All Tasks\n";
        cout << "3. Display Completed Tasks\n";
        cout << "4. Display Pending Tasks\n";
        cout << "5. Update Task\n";
        cout << "6. Mark Task as Completed\n";
        cout << "7. Delete Task\n";
        cout << "8. Search Task\n";
        cout << "9. Calculate Total Time\n";
        cout << "0. Exit\n";
        cout << "------------------------------\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 0 || choice > 9) {
            cout << "Invalid choice. Please enter a number between 0 and 9: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            workLog.insertTask();
            break;
        case 2:
            workLog.displayAllTasks();
            break;
        case 3:
            workLog.displayCompletedTasks();
            break;
        case 4:
            workLog.displayPendingTasks();
            break;
        case 5:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEnter task description to update: ";
            getline(cin, taskDescription);
            workLog.updateTask(taskDescription);
            break;
        case 6:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEnter task description to mark as completed: ";
            getline(cin, taskDescription);
            workLog.markTaskCompleted(taskDescription);
            break;
        case 7:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEnter task description to delete: ";
            getline(cin, taskDescription);
            workLog.deleteTask(taskDescription);
            break;
        case 8:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEnter keyword to search (date or description): ";
            getline(cin, searchKeyword);
            workLog.searchTask(searchKeyword);
            break;
        case 9:
            workLog.calculateTotalTime();
            break;
        case 0:
            cout << "\nThank you for using Employee Work Log System!\n";
            break;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            system("clear"); // Use "cls" for Windows
        }

    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
