#include "Chat.h"

// Функция для вывода всех сообщений из общего чата
void Chat::Print_All_message() {
    std::vector<std::string> messages;
    std::string line;

    std::ifstream all_message("All_message.txt");
    if (!all_message.is_open()) {
        std::cerr << "Ошибка: файл не удалось открыть" << std::endl;
        return;
    }

    while (getline(all_message, line)) {
        messages.push_back(line);
    }
    all_message.close();

    if (messages.empty()) {
        std::cout << "Нет сообщений в общем чате." << std::endl;
    }
    else {
        for (const auto& message : messages) {
            std::cout << message << std::endl;
        }
    }
}

// Функция для отправки сообщения всем пользователям
void Chat::Send_All_message() {
    std::string line;

    std::cout << "Введите сообщение всем пользователям: ";
    std::cin.ignore();
    std::getline(std::cin, line);

    std::ofstream out_message("All_message.txt", std::ios::app);
    if (!out_message.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл" << std::endl;
        return;
    }

    out_message << line << std::endl;
    out_message.close();
}

// Отправка сообщения конкретному пользователю
void Chat::Send_message(const std::string& fromUser, const std::string& toUser) {
    std::string message_text;
    std::cout << "Введите сообщение: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
    std::getline(std::cin, message_text);

    // Получение текущего времени
    time_t now = time(0);
    tm ltm; // Объявляем объект tm, а не указатель
    localtime_s(&ltm, &now); // Используем безопасную версию localtime_s

    // Формируем строку с датой и временем
    std::ostringstream dateTime;
    dateTime << std::setw(2) << std::setfill('0') << ltm.tm_mday << "/"
        << std::setw(2) << std::setfill('0') << ltm.tm_mon + 1 << "/"
        << ltm.tm_year + 1900 << " "
        << std::setw(2) << std::setfill('0') << ltm.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << ltm.tm_min;

    // Формируем имя файла на основе логинов отправителя и получателя
    std::string filename = "chat_" + (fromUser < toUser ? fromUser + "_" + toUser : toUser + "_" + fromUser) + ".txt";

    // Открываем файл для записи
    std::ofstream chat_file(filename, std::ios::app);
    if (!chat_file.is_open()) {
        std::cerr << "Ошибка: файл чата не удалось открыть!" << std::endl;
        return;
    }

    // Записываем сообщение в файл с датой и временем
    chat_file << "[" << dateTime.str() << "] " << fromUser << ": " << message_text << std::endl;
    chat_file.close();

    std::cout << "Сообщение отправлено!" << std::endl;
}

// Чтение сообщений между двумя пользователями
void Chat::Read_message(const std::string& fromUser, const std::string& toUser) {
    std::string filename = "chat_" + (fromUser < toUser ? fromUser + "_" + toUser : toUser + "_" + fromUser) + ".txt";

    std::ifstream chat_file(filename);
    if (!chat_file.is_open()) {
        std::cerr << "Чат с этим пользователем пуст или файл не найден." << std::endl;
        return;
    }

    std::string line;
    std::cout << "Чат с пользователем " << toUser << ":" << std::endl;
    while (getline(chat_file, line)) {
        std::cout << line << std::endl;
    }
    chat_file.close();
}

void Chat::ShowUserChats(const std::string& current_user) {
    // Папка, где хранятся файлы чатов
    std::string chat_directory = ".";  // В текущей папке

    bool found = false;

    std::cout << "Ваши чаты:" << std::endl;

    // Проходим по всем файлам в директории
    for (const auto& entry : fs::directory_iterator(chat_directory)) {
        std::string filename = entry.path().filename().string();

        // Проверяем, что файл начинается с "chat_" и содержит имя текущего пользователя
        if (filename.find("chat_") == 0 &&
            (filename.find(current_user + "_") != std::string::npos || filename.find("_" + current_user) != std::string::npos)) {

            found = true;
            std::cout << "Чат: " << filename << std::endl;

            // Открываем файл чата для чтения
            std::ifstream chat_file(entry.path());
            if (!chat_file.is_open()) {
                std::cerr << "Ошибка: не удалось открыть файл чата " << filename << std::endl;
                continue;
            }

            std::string line;
            while (getline(chat_file, line)) {
                std::cout << line << std::endl;
            }

            chat_file.close();
            std::cout << "-----------------------" << std::endl;
        }
    }

    if (!found) {
        std::cout << "У вас пока нет сообщений." << std::endl;
    }
}

// Выбор пользователя для отправки сообщения
void Chat::User_Choice(const std::string& current_user) {
    std::vector<std::string> users;
    std::ifstream name("user_info.txt");
    if (!name.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(name, line)) {
        users.push_back(line);
    }
    name.close();

    if (users.empty()) {
        std::cerr << "Ошибка: список пользователей пуст." << std::endl;
        return;
    }

    std::cout << "Доступные пользователи:" << std::endl;

    size_t i = 1;
    for (const auto& user : users) {
        std::cout << i << ". " << user << std::endl;
        i++;
    }

    size_t choice;
    std::cout << "Выберите пользователя для чата (1 - " << users.size() << "): ";
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > users.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Ошибка: такого пользователя не существует." << std::endl;
        return;
    }

    std::string selectedUser = users[choice - 1];
    std::cout << "Вы выбрали пользователя: " << selectedUser << std::endl;

    // Чтение существующих сообщений
    Read_message(current_user, selectedUser);

    // Отправка нового сообщения
    Send_message(current_user, selectedUser);
}
