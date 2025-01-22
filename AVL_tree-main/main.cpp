#include "List.h"
#include "AVL2.h"
#include "key.h"

int main() {
    int count = 0;
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
        FIO fio_to_delete("Иванов","Иван","Иванович");
        //TreeNode* roottt = tree.findtroot();
        //std::cout<<roottt->key.name;
        tree.printt(tree.root);
        tree.delete_data(fio_to_delete, tree.root, h);
        std::cout<<"\n";
        std::cout<<"После удаления\n";
        std::cout<<"\n";
        tree.printt(tree.root);
        std::cout<<"\n";
        //TreeNode* roottt = tree.findtroot();
        std::cout<<tree.root->key.name;
        std::string surname = "Смирнова";
        std::string name = "Анна";
        std::string patronymic = "Павловна";
        FIO fio_to_find(surname, name, patronymic);

        TreeNode* found_node = tree.search(fio_to_find, tree.root);

        if (found_node != nullptr) {
            std::cout<<"\nРещультат поиска.";
            std::cout << "Найден узел: " << found_node->key.surname << " "
              << found_node->key.name << " " << found_node->key.patronymic << std::endl;
        } else {
            std::cout<<"\nРезультат поиска."<<"\n";
            std::cout << "Элемент не найден в дереве." << std::endl;
        }
        tree.printToFile("output.txt");


    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
/*
Иванов Иван Иванович
Смирнова Анна Павловна
Петров
Сидоров Иванов
123 Иван Иванович
Пивов Иван Иванович
Кузнецов Олег Петрович
@@@ Иван Иванович
Еремина Лариса !#$% некорректные символы
Денисов Денис Денисович
                                
Иванов Иван Иванович Иванов

*/
/*
Иванов Иван Иванович
Смирнова Анна Павловна
Петров
Сидоров Иванов
123 Иван Иванович
Пивов Иван Иванович
Кузнецов Олег Петрович
Йованов Арсений Петрович
*/
/*
Иванов Иван Иванович
Смирнова Анна Павловна
Пивов Иван Иванович
Кузнецов Олег Петрович
Йованов Арсений Петрович
Йагнатов Иван ИВанович
Зимин Николай Иванович
*/