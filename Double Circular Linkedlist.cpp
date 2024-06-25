#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    string name;
    int age;
    Student* next;
    Student* prev;

    Student(string n, int a) : name(n), age(a), next(nullptr), prev(nullptr) {}
};

class DoublyCircularLinkedList {
private:
    Student* head;

public:
    DoublyCircularLinkedList() : head(nullptr) {}

    void insertAtStart(string name, int age) {
        Student* newStudent = new Student(name, age);
        if (head == nullptr) {
            head = newStudent;
            head->next = head;
            head->prev = head;
        } else {
            Student* tail = head->prev;
            newStudent->next = head;
            newStudent->prev = tail;
            tail->next = newStudent;
            head->prev = newStudent;
            head = newStudent;
        }
    }

    void insertAtEnd(string name, int age) {
        Student* newStudent = new Student(name, age);
        if (head == nullptr) {
            head = newStudent;
            head->next = head;
            head->prev = head;
        } else {
            Student* tail = head->prev;
            tail->next = newStudent;
            newStudent->prev = tail;
            newStudent->next = head;
            head->prev = newStudent;
        }
    }

    void insertAtPosition(string name, int age, int position) {
        if (position == 1) {
            insertAtStart(name, age);
            return;
        }
        Student* newStudent = new Student(name, age);
        Student* temp = head;
        for (int i = 1; i < position - 1 && temp->next != head; ++i) {
            temp = temp->next;
        }
        if (temp->next == head && position != 2) {
            cout << "Position out of range" << endl;
            delete newStudent;
            return;
        }
        newStudent->next = temp->next;
        newStudent->prev = temp;
        temp->next->prev = newStudent;
        temp->next = newStudent;
    }

    void traverse() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        Student* temp = head;
        do {
            cout << "Name: " << temp->name << ", Age: " << temp->age << endl;
            temp = temp->next;
        } while (temp != head);
    }

    void deleteAtStart() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Student* tail = head->prev;
        Student* temp = head;
        head = head->next;
        tail->next = head;
        head->prev = tail;
        delete temp;
    }

    void deleteAtEnd() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Student* tail = head->prev;
        tail->prev->next = head;
        head->prev = tail->prev;
        delete tail;
    }

    void deleteAtPosition(int position) {
        if (position == 1) {
            deleteAtStart();
            return;
        }
        Student* temp = head;
        for (int i = 1; i < position && temp->next != head; ++i) {
            temp = temp->next;
        }
        if (temp->next == head && position != 2) {
            cout << "Position out of range" << endl;
            return;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    int length() {
        if (head == nullptr) {
            return 0;
        }
        int count = 0;
        Student* temp = head;
        do {
            ++count;
            temp = temp->next;
        } while (temp != head);
        return count;
    }

    void searchByName(string name) {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        Student* temp = head;
        do {
            if (temp->name == name) {
                cout << "Student found: " << temp->name << ", Age: " << temp->age << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Student not found" << endl;
    }

    void editAge(string name, int newAge) {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        Student* temp = head;
        do {
            if (temp->name == name) {
                temp->age = newAge;
                cout << "Age updated for " << temp->name << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Student not found" << endl;
    }

    void sortByAge() {
        if (head == nullptr || head->next == head) {
            return;
        }
        bool swapped;
        do {
            swapped = false;
            Student* temp = head;
            do {
                Student* nextNode = temp->next;
                if (temp->age > nextNode->age) {
                    swap(temp->name, nextNode->name);
                    swap(temp->age, nextNode->age);
                    swapped = true;
                }
                temp = nextNode;
            } while (temp->next != head);
        } while (swapped);
    }
};

int main() {
    DoublyCircularLinkedList list;
    int choice, age, position;
    string name;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Insert at the beginning" << endl;
        cout << "2. Insert at the end" << endl;
        cout << "3. Insert at a specific position" << endl;
        cout << "4. Traverse" << endl;
        cout << "5. Delete from the start" << endl;
        cout << "6. Delete from the end" << endl;
        cout << "7. Delete from a specific position" << endl;
        cout << "8. Length of the list" << endl;
        cout << "9. Search by name" << endl;
        cout << "10. Edit age" << endl;
        cout << "11. Sort by age" << endl;
        cout << "12. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name and age: ";
                cin >> name >> age;
                list.insertAtStart(name, age);
                break;
            case 2:
                cout << "Enter name and age: ";
                cin >> name >> age;
                list.insertAtEnd(name, age);
                break;
            case 3:
                cout << "Enter position: ";
                cin >> position;
                cout << "Enter name and age: ";
                cin >> name >> age;
                list.insertAtPosition(name, age, position);
                break;
            case 4:
                list.traverse();
                break;
            case 5:
                list.deleteAtStart();
                break;
            case 6:
                list.deleteAtEnd();
                break;
            case 7:
                cout << "Enter position: ";
                cin >> position;
                list.deleteAtPosition(position);
                break;
            case 8:
                cout << "Length of the list: " << list.length() << endl;
                break;
            case 9:
                cout << "Enter name to search: ";
                cin >> name;
                list.searchByName(name);
                break;
            case 10:
                cout << "Enter name and new age: ";
                cin >> name >> age;
                list.editAge(name, age);
                break;
            case 11:
                list.sortByAge();
                break;
            case 12:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
