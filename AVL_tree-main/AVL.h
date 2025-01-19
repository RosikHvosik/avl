#include <string>
#include <iostream>
#include <algorithm>

struct TreeNode {
    std::string surname;
    std::string name;
    std::string patronymic;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& surname, const std::string& name, const std::string& patronymic)
        : surname(surname), name(name), patronymic(patronymic), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    TreeNode* root;

    int getHeight(TreeNode* node) const {
        return node ? node->height : 0;
    }

    int getBalance(TreeNode* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    TreeNode* rotateRight(TreeNode* rotatingNode) {
        TreeNode* newRoot = rotatingNode->left;
        TreeNode* middleSubtree = newRoot->right;

        newRoot->right = rotatingNode;
        rotatingNode->left = middleSubtree;

        rotatingNode->height = std::max(getHeight(rotatingNode->left), getHeight(rotatingNode->right)) + 1;
        newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    TreeNode* rotateLeft(TreeNode* rotatingNode) {
        TreeNode* newRoot = rotatingNode->right;
        TreeNode* middleSubtree = newRoot->left;

        newRoot->left = rotatingNode;
        rotatingNode->right = middleSubtree;

        rotatingNode->height = std::max(getHeight(rotatingNode->left), getHeight(rotatingNode->right)) + 1;
        newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    TreeNode* insert(TreeNode* node, const std::string& surname, const std::string& name, const std::string& patronymic) {
        if (!node)
            return new TreeNode(surname, name, patronymic);

        if (surname < node->surname || (surname == node->surname && name < node->name) || 
            (surname == node->surname && name == node->name && patronymic < node->patronymic)) {
            node->left = insert(node->left, surname, name, patronymic);
        } else if (surname > node->surname || (surname == node->surname && name > node->name) || 
                   (surname == node->surname && name == node->name && patronymic > node->patronymic)) {
            node->right = insert(node->right, surname, name, patronymic);
        } else {
            std::cerr << "Дубликат: " << surname << " " << name << " " << patronymic << std::endl;
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && surname < node->left->surname)
            return rotateRight(node);

        if (balance < -1 && surname > node->right->surname)
            return rotateLeft(node);

        if (balance > 1 && surname > node->left->surname) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && surname < node->right->surname) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inOrder(TreeNode* node) const {
        if (node) {
            inOrder(node->right);
            std::cout << node->surname << " " << node->name << " " << node->patronymic << std::endl;
            inOrder(node->left);
        }
    }

    void clear(TreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(const std::string& surname, const std::string& name, const std::string& patronymic) {
        root = insert(root, surname, name, patronymic);
    }

    void print() const {
        inOrder(root);
    }
};
