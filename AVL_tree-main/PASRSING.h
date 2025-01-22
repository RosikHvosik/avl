#include <string>
#include <sstream>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <tuple>

// Удаление лишних пробелов
std::wstring trim(const std::wstring& str) {
    size_t start = str.find_first_not_of(L" \t");
    size_t end = str.find_last_not_of(L" \t");
    return (start == std::wstring::npos) ? L"" : str.substr(start, end - start + 1);
}

// Проверка, является ли символ русской буквой
bool isRussianLetter(wchar_t ch) {
    return (ch >= L'А' && ch <= L'Я') ||  // А-Я
           (ch >= L'а' && ch <= L'я') ||  // а-я
           (ch == L'Ё') || (ch == L'ё');  // Ё и ё
}

// Проверка валидности имени
bool isValidNamePart(const std::wstring& part) {
    if (part.size() < 2) {
        return false;
    }

    for (wchar_t ch : part) {
        if (!isRussianLetter(ch)) {
            return false;
        }
    }
    return true;
}

std::wstring stringToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes(str);
}

std::string wstringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstr);
}

std::tuple<std::string, std::string, std::string> parseFullName(const std::string& line) {
    std::wstring wline = stringToWstring(line);
    std::wistringstream wiss(wline);

    std::wstring surname, name, patronymic;

    if (!(wiss >> surname >> name >> patronymic)) {
        throw std::runtime_error("Ошибка разбора строки: должно быть ровно три слова (ФИО).");
    }

    surname = trim(surname);
    name = trim(name);
    patronymic = trim(patronymic);

    if (!isValidNamePart(surname)) {
        throw std::runtime_error("Некорректная фамилия: " + wstringToString(surname) +
                                 ". Должна содержать только русские буквы и быть не короче 2 символов.");
    }
    if (!isValidNamePart(name)) {
        throw std::runtime_error("Некорректное имя: " + wstringToString(name) +
                                 ". Должна содержать только русские буквы и быть не короче 2 символов.");
    }
    if (!isValidNamePart(patronymic)) {
        throw std::runtime_error("Некорректное отчество: " + wstringToString(patronymic) +
                                 ". Должна содержать только русские буквы и быть не короче 2 символов.");
    }

    // Преобразуем обратно в std::string для совместимости с остальным кодом
    return {wstringToString(surname), wstringToString(name), wstringToString(patronymic)};
}
