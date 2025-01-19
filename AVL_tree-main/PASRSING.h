#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>
#include <cctype>
#include <algorithm>


std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}


bool isValidNamePart(const std::string& part) {
    if (part.size() < 2) {
        return false; 
    }
    for (unsigned char ch : part) {
        if (!std::isalpha(ch)) {
            return false; 
        }
    }
    return true;
}

std::tuple<std::string, std::string, std::string> parseFullName(const std::string& line) {
    std::istringstream iss(line);
    std::string surname, name, patronymic;

    if (!(iss >> surname >> name >> patronymic)) {
        throw std::runtime_error("Ошибка разбора строки: должно быть ровно три слова (ФИО): " + line);
    }

    surname = trim(surname);
    name = trim(name);
    patronymic = trim(patronymic);

    if (!isValidNamePart(surname)) {
        throw std::runtime_error("Некорректная фамилия: " + surname + ". Должна содержать только буквы и быть не короче 2 символов.");
    }
    if (!isValidNamePart(name)) {
        throw std::runtime_error("Некорректное имя: " + name + ". Должна содержать только буквы и быть не короче 2 символов.");
    }
    if (!isValidNamePart(patronymic)) {
        throw std::runtime_error("Некорректное отчество: " + patronymic + ". Должна содержать только буквы и быть не короче 2 символов.");
    }

    return {surname, name, patronymic};
}
