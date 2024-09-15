#include "Chat.h"

// Функция для вывода всех сообщений из общего чата
void Chat::Print_All_message() {
    vector<string> messages;
    string line;

    ifstream all_message("All_message.txt");
    if (!all_message.is_open()) {
        cerr << "Ошибка: файл не удалось открыть" << endl;
        return;
    }

    while (getline(all_message, line)) {
        messages.push_back(line);
    }
    all_message.close();

    if (messages.empty()) {
        cout << "Нет сообщений в общем чате." << endl;
    }
    else {
        for (const auto& message : messages) {
            cout << message << endl;
        }
    }
}

// Функция для отправки сообщения всем пользователям
void Chat::Send_All_message() {
    string line;

    cout << "Введите сообщение всем пользователям: ";
    cin.ignore();
    getline(cin, line);

    ofstream out_message("All_message.txt", ios::app);
    if (!out_message.is_open()) {
        cerr << "Ошибка: не удалось открыть файл" << endl;
        return;
    }

    out_message << line << endl;
    out_message.close();
}

// Отправка сообщения конкретному пользователю
void Chat::Send_message(const string& sender, const string& receiver) {
    string message_text;
    cout << "Введите сообщение: ";
    cin.ignore();
    getline(cin, message_text);

    // Получение текущего времени
    time_t now = time(0);
    tm* ltm = localtime(&now);

    // Формируем строку с датой и временем
    ostringstream dateTime;
    dateTime << std::setw(2) << setfill('0') << ltm->tm_mday << "/"
        << std::setw(2) << setfill('0') << ltm->tm_mon + 1 << "/"
        << ltm->tm_year + 1900 << " "
        << std::setw(2) << setfill('0') << ltm->tm_hour << ":"
        << std::setw(2) << setfill('0') << ltm->tm_min;

    // Формируем имя файла на основе логинов отправителя и получателя
    string filename = "chat_" + sender + "_" + receiver + ".txt";

    // Открываем файл для записи
    ofstream chat_file(filename, ios::app);
    if (!chat_file.is_open()) {
        cerr << "Ошибка: файл чата не удалось открыть!" << endl;
        return;
    }

    // Записываем сообщение в файл с датой и временем
    chat_file << "[" << dateTime.str() << "] " << sender << ": " << message_text << endl;
    chat_file.close();

    cout << "Сообщение отправлено!" << endl;
}

// Чтение сообщений между двумя пользователями
void Chat::Read_message(const string& user1, const string& user2) {
    string filename = "chat_" + user1 + "_" + user2 + ".txt";

    ifstream chat_file(filename);
    if (!chat_file.is_open()) {
        cerr << "Чат с этим пользователем пуст или файл не найден." << endl;
        return;
    }

    string line;
    cout << "Чат с пользователем " << user2 << ":" << endl;
    while (getline(chat_file, line)) {
        cout << line << endl;
    }
    chat_file.close();
}

void Chat::ShowUserChats(const string& current_user)
{
    // Папка, где хранятся файлы чатов
    string chat_directory = ".";  // В текущей папке

    bool found = false;

    cout << "Ваши чаты:" << endl;

    // Проходим по всем файлам в директории
    for (const auto& entry : fs::directory_iterator(chat_directory)) {
        string filename = entry.path().filename().string();

        // Проверяем, что файл начинается с "chat_" и содержит имя текущего пользователя
        if (filename.find("chat_") == 0 &&
            (filename.find(current_user + "_") != string::npos || filename.find("_" + current_user) != string::npos)) {

            found = true;
            cout << "Чат: " << filename << endl;

            // Открываем файл чата для чтения
            ifstream chat_file(entry.path());
            if (!chat_file.is_open()) {
                cerr << "Ошибка: не удалось открыть файл чата " << filename << endl;
                continue;
            }

            string line;
            while (getline(chat_file, line)) {
                cout << line << endl;
            }

            chat_file.close();
            cout << "-----------------------" << endl;
        }
    }

    if (!found) {
        cout << "У вас пока нет сообщений." << endl;
    }
}

// Выбор пользователя для отправки сообщения
void Chat::User_Choice(const string& current_user) {
    vector<string> users;
    ifstream name("user_info.txt");
    if (!name.is_open()) {
        cerr << "Ошибка: не удалось открыть файл!" << endl;
        return;
    }

    string line;
    while (getline(name, line)) {
        users.push_back(line);
    }
    name.close();

    if (users.empty()) {
        cerr << "Ошибка: список пользователей пуст." << endl;
        return;
    }

    cout << "Доступные пользователи:" << endl;

    int i = 1;
    for (const auto& user : users) {
        cout << i << ". " << user << endl;
        i++;
    }

    int choice;
    cout << "Выберите пользователя для чата (1 - " << users.size() << "): ";
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > users.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка: такого пользователя не существует." << endl;
        return;
    }

    string selectedUser = users[choice - 1];
    cout << "Вы выбрали пользователя: " << selectedUser << endl;

    // Чтение существующих сообщений
    Read_message(current_user, selectedUser);

    // Отправка нового сообщения
    Send_message(current_user, selectedUser);
}
