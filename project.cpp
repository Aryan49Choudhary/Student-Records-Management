#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
public:
    int id;
    string name;

    Student(int id, string name) : id(id), name(name) {}
};

class BSTNode {
public:
    Student* student;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Student* student) : student(student), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Student* student) {
        if (node == nullptr) {
            return new BSTNode(student);
        }
        if (student->id < node->student->id) {
            node->left = insert(node->left, student);
        } else if (student->id > node->student->id) {
            node->right = insert(node->right, student);
        }
        return node;
    }

    BSTNode* deleteNode(BSTNode* root, int id, string name) {
        if (root == nullptr) return root;
        if (id < root->student->id) {
            root->left = deleteNode(root->left, id, name);
        } else if (id > root->student->id) {
            root->right = deleteNode(root->right, id, name);
        } else {
            if (root->student->name != name) return root;

            if (root->left == nullptr) {
                BSTNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BSTNode* temp = root->left;
                delete root;
                return temp;
            }
            BSTNode* temp = minValueNode(root->right);
            root->student = temp->student;
            root->right = deleteNode(root->right, temp->student->id, temp->student->name);
        }
        return root;
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void searchByName(BSTNode* node, string name, vector<Student*>& results) {
        if (node == nullptr) return;
        if (node->student->name == name) {
            results.push_back(node->student);
        }
        searchByName(node->left, name, results);
        searchByName(node->right, name, results);
    }

    BSTNode* search(BSTNode* node, int id, string name) {
        if (node == nullptr || (node->student->id == id && node->student->name == name)) {
            return node;
        }
        if (node->student->id < id) {
            return search(node->right, id, name);
        }
        return search(node->left, id, name);
    }

    void inOrder(BSTNode* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << "ID: " << root->student->id << ", Name: " << root->student->name << endl;
            inOrder(root->right);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(Student* student) {
        root = insert(root, student);
    }

    void deleteStudent(int id, string name) {
        root = deleteNode(root, id, name);
    }

    void searchByName(string name) {
        vector<Student*> results;
        searchByName(root, name, results);
        if (results.empty()) {
            cout << "No students found with name: " << name << endl;
        } else {
            for (Student* student : results) {
                cout << "ID: " << student->id << ", Name: " << student->name << endl;
            }
        }
    }

    Student* search(int id, string name) {
        BSTNode* node = search(root, id, name);
        if (node != nullptr) {
            return node->student;
        }
        return nullptr;
    }

    void display() {
        inOrder(root);
    }
};

class LinkedList {
private:
    struct Node {
        Student* student;
        Node* next;
        Node(Student* student) : student(student), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(Student* student) {
        Node* newNode = new Node(student);
        newNode->next = head;
        head = newNode;
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << "ID: " << current->student->id << ", Name: " << current->student->name << endl;
            current = current->next;
        }
    }

    void searchByName(string name) {
        Node* current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->student->name == name) {
                cout << "ID: " << current->student->id << ", Name: " << current->student->name << endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) {
            cout << "No students found with name: " << name << endl;
        }
    }

    void deleteStudent(int id, string name) {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr && (current->student->id != id || current->student->name != name)) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Student not found." << endl;
            return;
        }
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }
};

int main() {
    BST bst;
    LinkedList list;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add student\n";
        cout << "2. Delete student\n";
        cout << "3. Search student by ID and name\n";
        cout << "4. Search students by name\n";
        cout << "5. Display all students (BST)\n";
        cout << "6. Display all students (Linked List)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name); // To read the whole line including spaces
            Student* student = new Student(id, name);
            bst.insert(student);
            list.insert(student);
        } else if (choice == 2) {
            int id;
            string name;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name); // To read the whole line including spaces
            bst.deleteStudent(id, name);
            list.deleteStudent(id, name);
        } else if (choice == 3) {
            int id;
            string name;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name); // To read the whole line including spaces
            Student* found = bst.search(id, name);
            if (found != nullptr) {
                cout << "Found student - ID: " << found->id << ", Name: " << found->name << endl;
            } else {
                cout << "Student not found." << endl;
            }
        } else if (choice == 4) {
            string name;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name); // To read the whole line including spaces
            cout << "\nStudents with name " << name << " in BST:\n";
            bst.searchByName(name);
            cout << "\nStudents with name " << name << " in Linked List:\n";
            list.searchByName(name);
        } else if (choice == 5) {
            cout << "\nStudents in BST:\n";
            bst.display();
        } else if (choice == 6) {
            cout << "\nStudents in Linked List:\n";
            list.display();
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
