#include <iostream>
#include <string>

using namespace std;

// Define the structure for a student node in a doubly linked list
struct Student {
	int id;             // Student ID
	string name;         // Student name
	char sex;            // Student sex (M/F)
	int age;             // Student age
	char grade;          // Student grade
	string department;    // Student department
	float gpa;           // Student GPA
	Student *next;       // Pointer to the next student node
	Student *prev;       // Pointer to the previous student node
};

// Define the class for Circular Doubly Linked List
class CircularDoublyLinkedList {
	private:
		Student *head;         // Pointer to the head of the list

	public:
		// Constructor to initialize the head pointer
		CircularDoublyLinkedList() {
			head = nullptr; // Initialize the head to null, indicating an empty list
		}

		// Function to create a new student node
		Student *createStudent(int id, string name, char sex, int age, char grade, string department, float gpa) {
			Student *newStudent = new Student(); // Allocate memory for a new student node
			newStudent->id = id;                 // Assign the provided ID
			newStudent->name = name;             // Assign the provided name
			newStudent->sex = sex;               // Assign the provided sex
			newStudent->age = age;               // Assign the provided age
			newStudent->grade = grade;           // Assign the provided grade
			newStudent->department = department; // Assign the provided department
			newStudent->gpa = gpa;               // Assign the provided GPA
			newStudent->next = nullptr;          // Initialize the 'next' pointer to null
			newStudent->prev = nullptr;          // Initialize the 'prev' pointer to null
			return newStudent;                   // Return the newly created student node
		}

		// Function to insert a student at the beginning of the list
		void insertAtBeginning(int id, string name, char sex, int age, char grade, string department, float gpa) {
			Student *newStudent = createStudent(id, name, sex, age, grade, department, gpa); // Create a new student node

			if (head == nullptr) { // If the list is empty
				head = newStudent;       // Make the new student the head
				newStudent->next = head; // Point the new student's 'next' to itself
				newStudent->prev = head; // Point the new student's 'prev' to itself (circular)
			} else { // If the list is not empty
				newStudent->next = head;       // New node's 'next' points to the current head
				newStudent->prev = head->prev; // New node's 'prev' points to the last node
				head->prev->next = newStudent; // Last node's 'next' points to the new node
				head->prev = newStudent;       // Current head's 'prev' points to the new node
				head = newStudent;             // Update the head to the new student
			}
			cout << "Student inserted at the beginning." << endl;
		}

		// Function to insert a student at the end of the list
		void insertAtEnd(int id, string name, char sex, int age, char grade, string department, float gpa) {
			Student *newStudent = createStudent(id, name, sex, age, grade, department, gpa); // Create a new student node

			if (head == nullptr) { // If the list is empty
				head = newStudent;       // Make the new student the head
				newStudent->next = head; // Point the new student's 'next' to itself
				newStudent->prev = head; // Point the new student's 'prev' to itself (circular)
			} else { // If the list is not empty
				newStudent->next = head;       // New node's 'next' points to the head
				newStudent->prev = head->prev; // New node's 'prev' points to the current last node
				head->prev->next = newStudent; // Current last node's 'next' points to the new node
				head->prev = newStudent;       // Head's 'prev' is updated to the new last node
			}
			cout << "Student inserted at the end." << endl;
		}

		// Function to insert a student at a specific position
		void insertAtPosition(int position, int id, string name, char sex, int age, char grade, string department, float gpa) {
			if (position <= 0) { // If the position is invalid
				cout << "Invalid position. Position should be greater than 0." << endl;
				return;
			}
			if (position == 1) { // If the position is the beginning
				insertAtBeginning(id, name, sex, age, grade, department, gpa);
				return;
			}

			Student *newStudent = createStudent(id, name, sex, age, grade, department, gpa); // Create a new student node
			Student *current = head;   // Start from the head
			int count = 1;         // Initialize a counter for the current position

			while (current != nullptr && count < position - 1) { // Traverse to the node before the desired position
				current = current->next;
				count++;
				if (current == head && count < position - 1) { // Handle cases where the position is out of bounds
					cout << "Position exceeds the length of the list." << endl;
					delete newStudent; // Clean up allocated memory
					return;
				}
			}

			if (current == nullptr || current->next == head) { // If the previous node is null or we reached the end (before target)
				cout << "Position exceeds the length of the list." << endl;
				delete newStudent; // Clean up allocated memory
				return;
			}

			newStudent->next = current->next; // New node's 'next' points to the node at the desired position
			newStudent->prev = current;      // New node's 'prev' points to the previous node
			current->next->prev = newStudent; // Node at desired position's 'prev' points to the new node
			current->next = newStudent;      // Previous node's 'next' points to the new node
			cout << "Student inserted at position " << position << "." << endl;
		}

		// Function to delete a student from the beginning of the list
		void deleteAtBeginning() {
			if (head == nullptr) { // If the list is empty
				cout << "List is empty. Cannot delete." << endl;
				return;
			}
			Student *temp = head; // Store the current head
			if (head->next == head) { // If there is only one node
				head = nullptr; // Set head to null
				delete temp;    // Delete the only node
			} else { // If there are more than one nodes
				head = head->next;       // Move the head to the next node
				head->prev = temp->prev; // Update the new head's 'prev' to the old last node
				temp->prev->next = head; // Update the old last node's 'next' to the new head
				delete temp;             // Delete the old head
			}
			cout << "Student deleted from the beginning." << endl;
		}

		// Function to delete a student from the end of the list
		void deleteAtEnd() {
			if (head == nullptr) { // If the list is empty
				cout << "List is empty. Cannot delete." << endl;
				return;
			}
			if (head->next == head) { // If there is only one node
				delete head; // Delete the head
				head = nullptr;  // Set head to null
				return;
			}
			Student *temp = head->prev; // Get the last node (pointed to by head's prev)
			head->prev = temp->prev;    // Update head's prev to the second last node
			temp->prev->next = head;    // Update the second last node's next to head
			delete temp;                // Delete the last node
			cout << "Student deleted from the end." << endl;
		}

		// Function to delete a student at a specific position
		void deleteAtPosition(int position) {
			if (head == nullptr) { // If the list is empty
				cout << "List is empty. Cannot delete." << endl;
				return;
			}
			if (position <= 0) { // If the position is invalid
				cout << "Invalid position. Position should be greater than 0." << endl;
				return;
			}
			if (position == 1) { // If the position is the beginning
				deleteAtBeginning();
				return;
			}

			Student *current = head; // Start from the head
			int count = 1;         // Initialize a counter for the current position

			while (current != nullptr && count < position) { // Traverse to the node at the desired position
				current = current->next;
				if (current == head && count < position) { // Handle cases where the position is out of bounds
					cout << "Position exceeds the length of the list." << endl;
					return;
				}
				count++;
			}

			if (current == nullptr
			        || current == head) { // If the current node is null or we looped back to head (position out of bounds)
				cout << "Position exceeds the length of the list." << endl;
				return;
			}

			current->prev->next = current->next; // Update the previous node's 'next'
			current->next->prev = current->prev; // Update the next node's 'prev'
			delete current;                      // Delete the node at the specified position
			cout << "Student deleted from position " << position << "." << endl;
		}

		// Function to search for a student by ID
		void searchStudentById(int searchId) {
			if (head == nullptr) {
				cout << "List is empty. Cannot search." << endl;
				return;
			}
			Student *current = head;
			do {
				if (current->id == searchId) {
					cout << "\nStudent Found (by ID):" << endl;
					cout << "ID: " << current->id << endl;
					cout << "Name: " << current->name << endl;
					cout << "Sex: " << current->sex << endl;
					cout << "Age: " << current->age << endl;
					cout << "Grade: " << current->grade << endl;
					cout << "Department: " << current->department << endl;
					cout << "GPA: " << current->gpa << endl;
					cout << "---" << endl;
					return; // Student found, exit the function
				}
				current = current->next;
			} while (current != head);
			cout << "Student with ID " << searchId << " not found." << endl;
		}

		// Function to display all students in the list
		void displayStudents() {
			if (head == nullptr) { // If the list is empty
				cout << "List is empty." << endl;
				return;
			}
			Student *current = head; // Start from the head
			cout << "\nStudent Records:" << endl;
			do {
				cout << "ID: " << current->id << endl;
				cout << "Name: " << current->name << endl;
				cout << "Sex: " << current->sex << endl;
				cout << "Age: " << current->age << endl;
				cout << "Grade: " << current->grade << endl;
				cout << "Department: " << current->department << endl;
				cout << "GPA: " << current->gpa << endl;
				cout << "---" << endl;
				current = current->next; // Move to the next node
			} while (current != head); // Continue until we reach the head again (circular list)
		}
};

int main() {
	CircularDoublyLinkedList studentList; // Create an instance of the CircularDoublyLinkedList class
	int choice;                                   // Variable to store user's choice
	int id, age, searchId;                        // Variables to store student ID, age, and search ID
	char sex, grade;                              // Variables to store student sex and grade
	string name, department;                      // Variables to store student name and department
	float gpa;                                    // Variable to store student GPA
	int position;                                   // Variable to store the position for insertion/deletion

	do {
		cout << "\nCircular Doubly Linked List Operations:" << endl;
		cout << "1. Insert at the Beginning" << endl;
		cout << "2. Insert at the End" << endl;
		cout << "3. Insert at a Specific Position" << endl;
		cout << "4. Delete from the Beginning" << endl;
		cout << "5. Delete from the End" << endl;
		cout << "6. Delete from a Specific Position" << endl;
		cout << "7. Display Students" << endl;
		cout << "8. Search Student by ID" << endl; // New option for searching by ID
		cout << "9. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice; // Get user's choice

		switch (choice) {
			case 1: // Insert at the Beginning
				cout << "Enter Student ID: ";
				cin >> id;
				cout << "Enter Student Name: ";
				cin >> name;
				cout << "Enter Student Sex (M/F): ";
				cin >> sex;
				cout << "Enter Student Age: ";
				cin >> age;
				cout << "Enter Student Grade: ";
				cin >> grade;
				cout << "Enter Student Department: ";
				cin >> department;
				cout << "Enter Student GPA: ";
				cin >> gpa;
				studentList.insertAtBeginning(id, name, sex, age, grade, department, gpa);
				break;

			case 2: // Insert at the End
				cout << "Enter Student ID: ";
				cin >> id;
				cout << "Enter Student Name: ";
				cin >> name;
				cout << "Enter Student Sex (M/F): ";
				cin >> sex;
				cout << "Enter Student Age: ";
				cin >> age;
				cout << "Enter Student Grade: ";
				cin >> grade;
				cout << "Enter Student Department: ";
				cin >> department;
				cout << "Enter Student GPA: ";
				cin >> gpa;
				studentList.insertAtEnd(id, name, sex, age, grade, department, gpa);
				break;

			case 3: // Insert at a Specific Position
				cout << "Enter the position to insert at: ";
				cin >> position;
				cout << "Enter Student ID: ";
				cin >> id;
				cout << "Enter Student Name: ";
				cin >> name;
				cout << "Enter Student Sex (M/F): ";
				cin >> sex;
				cout << "Enter Student Age: ";
				cin >> age;
				cout << "Enter Student Grade: ";
				cin >> grade;
				cout << "Enter Student Department: ";
				cin >> department;
				cout << "Enter Student GPA: ";
				cin >> gpa;
				studentList.insertAtPosition(position, id, name, sex, age, grade, department, gpa);
				break;

			case 4: // Delete from the Beginning
				studentList.deleteAtBeginning();
				break;

			case 5: // Delete from the End
				studentList.deleteAtEnd();
				break;

			case 6: // Delete from a Specific Position
				cout << "Enter the position to delete from: ";
				cin >> position;
				studentList.deleteAtPosition(position);
				break;

			case 7: // Display Students
				studentList.displayStudents();
				break;

			case 8: // Search Student by ID
				cout << "Enter the Student ID to search: ";
				cin >> searchId;
				studentList.searchStudentById(searchId);
				break;

			case 9: // Exit
				cout << "Exiting program." << endl;
				break;

			default: // Invalid choice
				cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 9); // Continue the loop until the user chooses to exit

	return 0; // Indicate successful program execution
}