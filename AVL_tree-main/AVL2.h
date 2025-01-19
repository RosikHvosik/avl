#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "key.h"

struct TreeNode {
		FIO key;
    int count;
		int bal;
    TreeNode* left;
    TreeNode* right;

		 TreeNode(const FIO& fio, int count, int bal, TreeNode* left, TreeNode* right) : key(fio), count(1), bal(0), left(nullptr), right(nullptr){}
};
//h параметр который будет отвечать за увеличилось дерево или нет 

class AVL_tree{
	public:
	TreeNode* root;
	AVL_tree() : root(nullptr){}

	~AVL_tree(){
		clear(root);
	}

		void clear(TreeNode* node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

	void insert(FIO fio, TreeNode*& p, bool& h) {
		//TreeNode* p1 = new TreeNode(fio, 1, 0, nullptr, nullptr);
		//TreeNode* p2 = new TreeNode(fio, 1, 0, nullptr, nullptr);
		TreeNode* p1;
		TreeNode* p2;
		if (p == nullptr){
			p = new TreeNode(fio, 1, 0, nullptr, nullptr);
			h = true;
		}
		else if(p->key > fio){
			insert (fio, p->left, h);
			if (h){
				if(p->bal == 1){
					p->bal = 0;
					h= false;
				}
				else if (p->bal == 0){
					p->bal = -1;
				}
				//значит баланс в вершине -1
				else{
					p1 = p->left;
					if (p1->bal == -1){//LL rotation
						p->left = p1->right;
						p1->right = p;
						p->bal = 0;
						p = p1;
					}
					else{//LR rotation
						p2 = p1->right;
						p1->right = p2->left;
						p2->left = p1;
						p->left = p2->right;
						p2->right = p;
						if(p2->bal == -1){p->bal = 1;}
						else{p->bal = 0;}
						if (p2->bal == 1){p1->bal = -1;}
						else{p1->bal = 0;}
						p = p2;
					}
					p->bal = 0;
					h = false;
				}
			}
		}
		else if(p->key < fio){
			insert (fio, p->right, h);
			if (h){
				if (p->bal == -1) {p->bal=0; h=false;}
				else if(p->bal == 0){p->bal = 1;}
				else {
					p1= p->right;
					if (p1->bal == 1){//RR rotation
						p->right = p1->left;
						p1->left = p;
						p->bal = 0;
						p = p1;
					}
					else{//RL rotation
						p2 = p1->left;
						p1->left = p2->right;
						p2->right = p1;
						p->right = p2->left;
						p2->left = p;
						if (p2->bal == 1){p->bal = -1;}
						else{p->bal = 0;}
						if(p2->bal == -1){p1->bal = 1;}
						else{p1->bal = 0;}
						p = p2;
					}
					p->bal =0;
					h= false;
				}
			}
			else p->count++;
		}
	}

	void balanceL(TreeNode*& p, bool& h){
		TreeNode* p1;
		TreeNode* p2;
		// уменьшается левая ветвь
		if (p->bal == -1){p->bal = 0;}
		else if(p->bal == 0){
			p->bal = 1;
			h = false;
			}
		// bal = 1 остался только такой вариант
		else{
			p1 = p->right;
			if(p1->bal >= 0){//rr rotation once
				p->right = p1->left;
				p1->left = p;
				if (p1->bal == 0){
					p->bal = 1;
					p1->bal = -1;
					h = false;
				}
				else{
					p->bal = 0;
					p1->bal = 0;
				}
				p = p1;
			}
			else{
				p2=p1->left;
				p1->left = p2->right;
				p2->right = p1;
				p->right = p2->left;
				p2->left = p;
				if (p2->bal == 1){p->bal = -1;} else{ p->bal = 0;}
				if (p2->bal == -1){p1->bal = 1;} else{p1->bal = 0;}
				p = p2;
				p2->bal = 0;
			}
		}
	}

	void balanceR(TreeNode*& p, bool& h){
		TreeNode* p1;
		TreeNode* p2;
		// уменьшается левая ветвь
		if (p->bal == 1){p->bal = 0;}
		else if(p->bal == 0){
			p->bal = -1;
			h = false;
			}
		// bal = -1 остался только такой вариант
		else{
			p1 = p->left;
			if(p1->bal <= 0){//rr rotation once
				p->left = p1->right;
				p1->right = p;
				if (p1->bal == 0){
					p->bal = -1;
					p1->bal = 1;
					h = false;
				}
				else{
					p->bal = 0;
					p1->bal = 0;
				}
				p = p1;
			}
			else{
				p2=p1->right;
				p1->right = p2->left;
				p2->left = p1;
				p->left = p2->right;
				p2->right = p;
				if (p2->bal == -1){p->bal = 1;} else{ p->bal = 0;}
				if (p2->bal == 1){p1->bal = -1;} else{p1->bal = 0;}
				p = p2;
				p2->bal = 0;
			}
		}
	}

	void delete_data(FIO fio, TreeNode*& p, bool& h) {
        if (p == nullptr) {
            std::cout << "Элемент не найден в дереве\n";
            return;
        }

        
        if (fio < p->key) {
            delete_data(fio, p->left, h);
            if (h) {
                balanceR(p, h);
            }
        } else if (fio > p->key) {
            delete_data(fio, p->right, h);
            if (h) {
                balanceL(p, h);
            }
        } else {  
            delete_node(p, h);
        }
    }

    // Удаление узла
    void delete_node(TreeNode*& p, bool& h) {
        TreeNode* q;
        if (p->left == nullptr && p->right == nullptr) {  // Узел — лист
            delete p;
            p = nullptr;
            h = true;
        }
        else if (p->left == nullptr) {  // Один потомок
            q = p;
            p = p->right;
            delete q;
            h = true;
        }
        else if (p->right == nullptr) {  // Один потомок
            q = p;
            p = p->left;
            delete q;
            h = true;
        }
        else {  // Два потомка
            q = p->right;
            while (q->left != nullptr) {
                q = q->left;  // Находим минимальный элемент в правом поддереве
            }
            p->key = q->key;
            delete_data(q->key, p->right, h);  
            if (h) {
                balanceR(p, h);
            }
        }
    }


	void inOrder(TreeNode* node) const {
        if (node) {
            inOrder(node->right);
            std::cout << node->key.surname << " " << node->key.name << " " << node->key.patronymic << std::endl;
            inOrder(node->left);
        }
    }
	void inOrder(TreeNode* node, std::ofstream& outFile) const {
    if (node) {
        inOrder(node->right, outFile);  
        outFile << node->key.surname << " " << node->key.name << " " << node->key.patronymic << std::endl;  
        inOrder(node->left, outFile);   
    }
	}

	void printToFile(const std::string& filename) const {
    std::ofstream outFile(filename);  
    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для записи!" << std::endl;
        return;
    }
    inOrder(root, outFile);  
    outFile.close();  
	}

	
	void print() const {
        inOrder(root);
    }
	void printt(TreeNode* node, int depth = 0) const {
    if (node != nullptr) {
        printt(node->right, depth + 1);
        
        std::cout << std::string(depth * 4, ' ')
                  << node->key.surname << " "
                  << node->key.name << " "
                  << node->key.patronymic << " "
                  << "(bal=" << node->bal << ")" << std::endl;

        printt(node->left, depth + 1);
    }
	}

	TreeNode* search(const FIO& fio, TreeNode* p) const {
    if (p == nullptr) {
        return nullptr;
    }
    
    if (fio == p->key) {
      return p;
    }
    else if (fio < p->key) {
      return search(fio, p->left);
    }
    else {
      return search(fio, p->right);
    }
	}
}; 