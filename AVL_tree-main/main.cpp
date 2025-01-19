#include "List.h"
#include "AVL2.h"
#include "key.h"

int main() {
    try {
        List list;
        list.fillFromFile("data.txt");

        std::cout << "Список из файла:" << std::endl;

        list.print();

        AVL_tree tree;

        bool h = false;

        Node* current = list.getHead();
        while (current) {

            FIO current2(current->surname, current->name, current->patronymic);

            tree.insert(current2, tree.root, h);

            current = current->next;
        }
        //FIO deletee ("Волошин","Лев","Евгеньевич");
        //tree.delete_data(deletee, tree.root, h);
        std::cout << "\nДанные в AVL-дереве:" << std::endl;
        tree.printt(tree.root);
        std::string surname = "Иванов";
        std::string name = "Сергей";
        std::string patronymic = "Генадьевич";
        FIO fio_to_find(surname, name, patronymic);

        TreeNode* found_node = tree.search(fio_to_find, tree.root);

        if (found_node != nullptr) {
            std::cout << "Найден узел: " << found_node->key.surname << " "
              << found_node->key.name << " " << found_node->key.patronymic << std::endl;
        } else {
            std::cout << "Элемент не найден в дереве." << std::endl;
        }

        tree.printToFile("output.txt");


    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

