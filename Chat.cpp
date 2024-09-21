#include "Chat.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <ctime>
#include <vector>

namespace fs = std::filesystem;

Menu menu;

// Функция для вывода всех сообщений из общего чата
void Chat::PrintAllMessages() const {
    menu.ClearScreen();
    std::ifstream all_message("All_message.txt");
    if (!all_message) {
        std::cerr << "Ошибка: файл с сообщениями не найден." << std::endl;
        return;
    }

    std::string line;
    bool isEmpty = true;
    while (std::getline(all_message, line)) {
        std::cout << line << std::endl;
        isEmpty = false;
    }

    if (isEmpty) {
        std::cout << "Нет сообщений в общем чате." << std::endl;
    }
}

// Функция для отправки сообщения всем пользователям
void Chat::SendMessageToAll() {
    std::string message;
    std::cout << "Введите сообщение для всех пользователей: ";
    std::cin.ignore(); // Игнорируем оставшуюся новую строку после предыдущего ввода
    std::getline(std::cin, message);

    std::ofstream out_message("All_message.txt", std::ios::app);
    if (!out_message) {
        std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
        return;
    }

    out_message << message << std::endl;
    std::cout << "Сообщение отправлено всем пользователям!" << std::endl;
}

// Отправка сообщения конкретному пользователю
void Chat::SendMessage(const std::string& sender, const std::string& receiver) {
    std::string message_text;
    std::cout << "Введите сообщение: ";
    std::cin.ignore();
    std::getline(std::cin, message_text);

    std::ostringstream dateTime;
    std::time_t now = std::time(nullptr);
    std::tm local_tm;
    localtime_s(&local_tm, &now);  // Используем localtime_s для безопасного получения локального времени
    dateTime << std::put_time(&local_tm, "%d/%m/%Y %H:%M");

    std::string filename = "chat_" + sender + "_" + receiver + ".txt";

    std::ofstream chat_file(filename, std::ios::app);
    if (!chat_file) {
        std::cerr << "Ошибка: не удалось открыть файл чата." << std::endl;
        return;
    }

    chat_file << "[" << dateTime.str() << "] " << sender << ": " << message_text << std::endl;
    std::cout << "Сообщение отправлено!" << std::endl;
}


// Чтение сообщений между двумя пользователями
void Chat::ReadMessages(const std::string& user1, const std::string& user2) const {
    std::string filename = "chat_" + user1 + "_" + user2 + ".txt";

    std::ifstream chat_file(filename);
    if (!chat_file) {
        std::cerr << "Чат с пользователем " << user2 << " пуст или файл не найден." << std::endl;
        return;
    }

    std::cout << "Чат с пользователем " << user2 << ":" << std::endl;
    std::string line;
    while (std::getline(chat_file, line)) {
        std::cout << line << std::endl;
    }
}

// Отображение всех чатов текущего пользователя
void Chat::ShowUserChats(const std::string& current_user) const {
    menu.ClearScreen();
    std::string chat_directory = ".";
    bool found = false;

    std::cout << "Ваши чаты:" << std::endl;

    for (const auto& entry : fs::directory_iterator(chat_directory)) {
        std::string filename = entry.path().filename().string();

        if (filename.find("chat_") == 0 &&
            (filename.find(current_user + "_") != std::string::npos ||
                filename.find("_" + current_user) != std::string::npos)) {
            found = true;
            std::cout << "Чат: " << filename << std::endl;

            std::ifstream chat_file(entry.path());
            if (!chat_file) {
                std::cerr << "Ошибка: не удалось открыть файл чата." << std::endl;
                continue;
            }

            std::string line;
            while (std::getline(chat_file, line)) {
                std::cout << line << std::endl;
            }

            std::cout << "-----------------------" << std::endl;
        }
    }

    if (!found) {
        std::cout << "У вас пока нет сообщений." << std::endl;
    }
}

// Выбор пользователя для отправки сообщения
void Chat::UserChoice(const std::string& current_user) {
    std::vector<std::string> users;
    std::ifstream user_file("user_info.txt");

    if (!user_file) {
        std::cerr << "Ошибка: не удалось открыть файл с пользователями." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(user_file, line)) {
        users.push_back(line);
    }

    if (users.empty()) {
        std::cerr << "Ошибка: список пользователей пуст." << std::endl;
        return;
    }

    std::cout << "Доступные пользователи:" << std::endl;
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << i + 1 << ". " << users[i] << std::endl;
    }

    int choice;
    std::cout << "Выберите пользователя для чата (1 - " << users.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(users.size())) {
        std::cerr << "Ошибка: некорректный выбор." << std::endl;
        return;
    }
    menu.ClearScreen();
    std::string selected_user = users[choice - 1];
    std::cout << "Вы выбрали пользователя: " << selected_user << std::endl;

    ReadMessages(current_user, selected_user);
    SendMessage(current_user, selected_user);
}