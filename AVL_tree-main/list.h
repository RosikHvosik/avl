#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "PASRSING.h" // Убедитесь, что имя файла корректное

struct Node {
    std::string surname;
    std::string name;
    std::string patronymic;
    Node* next;

    Node(std::string surname, std::string name, std::string patronymic) 
        : surname(std::move(surname)), name(std::move(name)), patronymic(std::move(patronymic)), next(nullptr) {}
};

class List {
public:
    Node* head;

    List() : head(nullptr) {}

    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void add(const std::string& surname, const std::string& name, const std::string& patronymic) {
        if (surname.empty() || name.empty() || patronymic.empty()) {
            throw std::invalid_argument("ФИО не может содержать пустые части.");
        }

        Node* newNode = new Node(surname, name, patronymic);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void fillFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Ошибка открытия файла: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            try {
                auto [surname, name, patronymic] = parseFullName(line);
                add(surname, name, patronymic);
            } catch (const std::exception& ex) {
                std::cerr << "Ошибка в строке: \"" << line << "\" - " << ex.what() << std::endl;
            }
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->surname << " " << current->name << " " << current->patronymic << std::endl;
            current = current->next;
        }
    }

    Node* pop() {
        if (head == nullptr) return nullptr;
        Node* temp = head;
        head = head->next;
        temp->next = nullptr;
        return temp;
    }

    Node* getHead() const {
        return head;
    }
};
