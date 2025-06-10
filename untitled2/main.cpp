#include <iostream>    // Для std::cout, std::cin, std::endl
#include <fstream>     // Для std::ifstream, std::ofstream (более idiomatic C++ для файлов)
#include <cstring>     // Для strlen, strcspn, strcmp, strcpy
#include <cstdio>      // Для remove (удаление файла)
#include <algorithm>   // Для std::sort
#include <clocale>     // Для setlocale
#include <windows.h>   // Для SetConsoleOutputCP и SetConsoleCP (только для Windows)
#include <limits>      // Для numeric_limits
#include <iomanip>5

// Используем using namespace std; для удобства
using namespace std;

// ГЛОБАЛЬНАЯ КОНСТАНТА: Максимальное количество релизов в массиве
const int MAX_RELEASES = 1500;

// Определение структуры для музыкального релиза (СОХРАНЕНА ИЗ ВАШЕГО ВТОРОГО ПРИМЕРА)
struct music_release {
    int id; // уникальный идентификатор альбома/сингла
    char title[150]; // название альбома/сингла
    char artist[100]; // основной исполнитель/группа
    char genre[50]; // музыкальный жанр (например, "Rock", "Pop", "Electronic")
    int release_year; // год выпуска
    char producer[100]; // имя продюсера/продюсеров (можно указать "Various" если их много или "Self-Produced")
    long long total_streams; // общее количество прослушиваний на всех платформах
    double rating; // средний рейтинг от слушателей (например, от 1.0 до 5.0)
    int track_count; // количество треков в альбоме (для синглов обычно 1)
    char featured_artists[200]; // приглашенные исполнители (если есть, список через запятую, "Нет" если нет)
};

// Прототипы функций
void menu();
void load_data_from_file(music_release *list, int &count); // 1. Загрузка данных
void add_release(music_release *list, int &count, int max_size); // 2. Добавление
void update_release(music_release *list, int count); // 3. Изменение
void delete_release(music_release *list, int &count); // 4. Удаление
void write_data_to_file(music_release *list, int count); // Вспомогательная: запись в файл

// 7 функций на выбор (включая сортировки)
void show_release_by_id(music_release *list, int count); // 5. Поиск и вывод по ID
void find_releases_by_artist(music_release *list, int count); // 6. Поиск релизов по исполнителю
void find_releases_by_genre(music_release *list, int count); // 7. Поиск релизов по жанру
void calculate_average_rating(music_release *list, int count); // 8. Расчет среднего рейтинга
void sort_by_year(music_release *list, int count); // 9. Сортировка по году выпуска (и записать в файл)
void sort_by_streams(music_release *list, int count); // 10. Сортировка по прослушиваниям (и записать в файл)
void show_all_releases(music_release *list, int &count); // 11. Вывод всех релизов

// Вспомогательные функции для сравнения для std::sort
bool compare_releases_by_year(const music_release &a, const music_release &b);
bool compare_releases_by_streams(const music_release &a, const music_release &b);

// Вспомогательная функция для вывода одного релиза (в консоль или файл)
// Используем std::ostream для большей гибкости (cout или файловый поток)
void print_single_release(ostream& os, const music_release* release);

// Вспомогательная функция для проверки корректности вводимых данных
bool is_valid_release_data(const music_release& r);

// Главная функция
int main() {
    // Настройка локали для корректного отображения кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Для функций C-style string и fscanf/fprintf

    menu();
    return 0;
}

// Меню программы
void menu() {
    music_release releases[MAX_RELEASES]; // Массив релизов
    int current_release_count = 0; // Текущее количество релизов

    while (true) {
        cout << "--- Управление Музыкальными Релизами ---" << endl;
        cout << "Загружено релизов: " << current_release_count << endl;
        cout << "0. Выход из программы" << endl;
        cout << "1. Загрузить данные из файла (input.txt)" << endl;
        cout << "2. Добавить новый музыкальный релиз" << endl;
        cout << "3. Изменить информацию о релизе по ID" << endl;
        cout << "4. Удалить релиз по ID" << endl;
        cout << "5. Показать информацию о релизе по ID" << endl;
        cout << "6. Найти релизы по исполнителю" << endl;
        cout << "7. Найти релизы по жанру" << endl;
        cout << "8. Посчитать средний рейтинг всех релизов" << endl;
        cout << "9. Отсортировать релизы по году выпуска (и записать в файл)" << endl;
        cout << "10. Отсортировать релизы по общему количеству прослушиваний (и записать в файл)" << endl;
        cout << "11. Показать все загруженные релизы (и записать в файл)" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Введите ваш выбор: ";

        int choice;
        // Проверка на корректный ввод числа
        while (!(cin >> choice)) {
            cout << "Некорректный ввод. Пожалуйста, введите число: ";
            cin.clear(); // Сброс флагов ошибок ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера после cin >> choice

        switch (choice) {
            case 0:
                cout << "Завершение программы." << endl;
                return;
            case 1:
                load_data_from_file(releases, current_release_count);
                break;
            case 2:
                add_release(releases, current_release_count, MAX_RELEASES);
                break;
            case 3:
                update_release(releases, current_release_count);
                break;
            case 4:
                delete_release(releases, current_release_count);
                break;
            case 5:
                show_release_by_id(releases, current_release_count);
                break;
            case 6:
                find_releases_by_artist(releases, current_release_count);
                break;
            case 7:
                find_releases_by_genre(releases, current_release_count);
                break;
            case 8:
                calculate_average_rating(releases, current_release_count);
                break;
            case 9:
                sort_by_year(releases, current_release_count);
                break;
            case 10:
                sort_by_streams(releases, current_release_count);
                break;
            case 11:
                show_all_releases(releases, current_release_count);
                break;
            default:
                cout << "Некорректный выбор. Пожалуйста, попробуйте еще раз." << endl;
        }
        cout << "\n";
    }
}

// 1. Загрузка данных в массив из файла
void load_data_from_file(music_release *list, int &count) {
    ifstream file("input.txt"); // Используем C++ потоки
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла input.txt. Убедитесь, что файл существует." << endl;
        count = 0;
        return;
    }

    count = 0;
    string line;
    music_release temp_release;

    cout << "Загрузка данных из input.txt..." << endl;

    // Читаем данные блоками по 10 строк (согласно структуре)
    while (getline(file, line)) { // ID
        try {
            temp_release.id = stoi(line); // Преобразуем строку в int
        } catch (const std::exception& e) {
            cerr << "Ошибка чтения ID: " << e.what() << " в строке: " << line << endl;
            // Пропускаем оставшиеся 9 строк, чтобы перейти к следующей потенциальной записи
            for (int i = 0; i < 9; ++i) {
                if (!getline(file, line)) break;
            }
            continue;
        }

        if (!getline(file, line)) { cerr << "Ошибка чтения названия." << endl; break; }
        strncpy(temp_release.title, line.c_str(), sizeof(temp_release.title) - 1);
        temp_release.title[sizeof(temp_release.title) - 1] = '\0';

        if (!getline(file, line)) { cerr << "Ошибка чтения исполнителя." << endl; break; }
        strncpy(temp_release.artist, line.c_str(), sizeof(temp_release.artist) - 1);
        temp_release.artist[sizeof(temp_release.artist) - 1] = '\0';

        if (!getline(file, line)) { cerr << "Ошибка чтения жанра." << endl; break; }
        strncpy(temp_release.genre, line.c_str(), sizeof(temp_release.genre) - 1);
        temp_release.genre[sizeof(temp_release.genre) - 1] = '\0';

        if (!getline(file, line)) { cerr << "Ошибка чтения года выпуска." << endl; break; }
        try {
            temp_release.release_year = stoi(line);
        } catch (const std::exception& e) {
            cerr << "Ошибка чтения года выпуска: " << e.what() << " в строке: " << line << endl;
            // Пропускаем оставшиеся 5 строк
            for (int i = 0; i < 5; ++i) {
                if (!getline(file, line)) break;
            }
            continue;
        }

        if (!getline(file, line)) { cerr << "Ошибка чтения продюсера." << endl; break; }
        strncpy(temp_release.producer, line.c_str(), sizeof(temp_release.producer) - 1);
        temp_release.producer[sizeof(temp_release.producer) - 1] = '\0';

        if (!getline(file, line)) { cerr << "Ошибка чтения прослушиваний." << endl; break; }
        try {
            temp_release.total_streams = stoll(line); // string to long long
        } catch (const std::exception& e) {
            cerr << "Ошибка чтения прослушиваний: " << e.what() << " в строке: " << line << endl;
            // Пропускаем оставшиеся 3 строки
            for (int i = 0; i < 3; ++i) {
                if (!getline(file, line)) break;
            }
            continue;
        }

        if (!getline(file, line)) { cerr << "Ошибка чтения рейтинга." << endl; break; }
        try {
            temp_release.rating = stod(line); // string to double
        } catch (const std::exception& e) {
            cerr << "Ошибка чтения рейтинга: " << e.what() << " в строке: " << line << endl;
            // Пропускаем оставшиеся 2 строки
            for (int i = 0; i < 2; ++i) {
                if (!getline(file, line)) break;
            }
            continue;
        }

        if (!getline(file, line)) { cerr << "Ошибка чтения количества треков." << endl; break; }
        try {
            temp_release.track_count = stoi(line);
        } catch (const std::exception& e) {
            cerr << "Ошибка чтения количества треков: " << e.what() << " в строке: " << line << endl;
            // Пропускаем оставшуюся 1 строку
            if (!getline(file, line)) break;
            continue;
        }

        if (!getline(file, line)) { cerr << "Ошибка чтения приглашенных исполнителей." << endl; break; }
        strncpy(temp_release.featured_artists, line.c_str(), sizeof(temp_release.featured_artists) - 1);
        temp_release.featured_artists[sizeof(temp_release.featured_artists) - 1] = '\0';

        if (count < MAX_RELEASES) {
            list[count] = temp_release;
            count++;
        } else {
            cerr << "Внимание: Достигнуто максимальное количество релизов (" << MAX_RELEASES << "). Дальнейшие записи игнорируются." << endl;
            break;
        }
    }

    file.close();
    cout << "Загружено " << count << " записей." << endl;
}

// 2. Добавление нового музыкального релиза
void add_release(music_release *list, int &count, int max_size) {
    if (count >= max_size) {
        cout << "База данных заполнена. Невозможно добавить новый релиз." << endl;
        return;
    }

    music_release new_release;
    new_release.id = (count > 0) ? (list[count - 1].id + 1) : 1;

    cout << "Введите название: ";
    cin.getline(new_release.title, sizeof(new_release.title));

    cout << "Введите исполнителя: ";
    cin.getline(new_release.artist, sizeof(new_release.artist));

    cout << "Введите жанр: ";
    cin.getline(new_release.genre, sizeof(new_release.genre));

    cout << "Введите год выпуска: ";
    while (!(cin >> new_release.release_year) || new_release.release_year < 1900 || new_release.release_year > 2025) {
        cout << "Некорректный год. Введите число от 1900 до 2025: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите продюсера: ";
    cin.getline(new_release.producer, sizeof(new_release.producer));

    cout << "Введите общее количество прослушиваний: ";
    while (!(cin >> new_release.total_streams) || new_release.total_streams < 0) {
        cout << "Некорректное количество прослушиваний. Введите неотрицательное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите рейтинг (от 1.0 до 5.0): ";
    while (!(cin >> new_release.rating) || new_release.rating < 1.0 || new_release.rating > 5.0) {
        cout << "Некорректный рейтинг. Введите число от 1.0 до 5.0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите количество треков: ";
    while (!(cin >> new_release.track_count) || new_release.track_count <= 0) {
        cout << "Некорректное количество треков. Введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите приглашенных исполнителей ('Нет', если нет): ";
    cin.getline(new_release.featured_artists, sizeof(new_release.featured_artists));

    // Валидация перед добавлением
    if (is_valid_release_data(new_release)) {
        list[count] = new_release;
        count++;
        cout << "Релиз успешно добавлен. ID: " << new_release.id << endl;
        write_data_to_file(list, count);
    } else {
        cout << "Ошибка: Введены некорректные данные для нового релиза. Добавление отменено." << endl;
    }
}

// 3. Изменение информации о релизе
void update_release(music_release *list, int count) {
    cout << "Введите ID релиза, который нужно изменить: ";
    int target_id;
    while (!(cin >> target_id)) {
        cout << "Некорректный ввод. Пожалуйста, введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int found_index = -1;
    for (int i = 0; i < count; i++) {
        if (list[i].id == target_id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        cout << "Релиз с ID " << target_id << " не найден." << endl;
        return;
    }

    music_release temp_release = list[found_index]; // Временно сохраняем для валидации

    cout << "Найден релиз: " << list[found_index].title << " - " << list[found_index].artist << endl;
    cout << "Введите новые данные (оставьте пустым для сохранения текущего значения):" << endl;

    char buffer[200]; // Буфер для чтения временных строк

    cout << "Новое название (текущее: " << temp_release.title << "): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strcpy(temp_release.title, buffer);

    cout << "Новый исполнитель (текущее: " << temp_release.artist << "): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strcpy(temp_release.artist, buffer);

    cout << "Новый жанр (текущее: " << temp_release.genre << "): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strcpy(temp_release.genre, buffer);

    cout << "Новый год выпуска (текущее: " << temp_release.release_year << "): ";
    if (cin.peek() != '\n') { // Проверяем, есть ли что-то, кроме новой строки
        int year_input;
        if (cin >> year_input && year_input >= 1900 && year_input <= 2025) {
            temp_release.release_year = year_input;
        } else {
            cout << "Некорректный год. Значение не изменено." << endl;
            cin.clear();
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Новый продюсер (текущее: " << temp_release.producer << "): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strcpy(temp_release.producer, buffer);

    cout << "Новое количество прослушиваний (текущее: " << temp_release.total_streams << "): ";
    if (cin.peek() != '\n') {
        long long streams_input;
        if (cin >> streams_input && streams_input >= 0) {
            temp_release.total_streams = streams_input;
        } else {
            cout << "Некорректное количество прослушиваний. Значение не изменено." << endl;
            cin.clear();
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Новый рейтинг (от 1.0 до 5.0) (текущее: " << temp_release.rating << "): ";
    if (cin.peek() != '\n') {
        double rating_input;
        if (cin >> rating_input && rating_input >= 1.0 && rating_input <= 5.0) {
            temp_release.rating = rating_input;
        } else {
            cout << "Некорректный рейтинг. Значение не изменено." << endl;
            cin.clear();
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Новое количество треков (текущее: " << temp_release.track_count << "): ";
    if (cin.peek() != '\n') {
        int track_input;
        if (cin >> track_input && track_input > 0) {
            temp_release.track_count = track_input;
        } else {
            cout << "Некорректное количество треков. Значение не изменено." << endl;
            cin.clear();
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Новые приглашенные исполнители (текущее: " << temp_release.featured_artists << ") ('Нет', если нет): ";
    cin.getline(buffer, sizeof(buffer));
    if (strlen(buffer) > 0) strcpy(temp_release.featured_artists, buffer);


    // Валидация обновленных данных
    if (is_valid_release_data(temp_release)) {
        list[found_index] = temp_release; // Если валидация прошла, сохраняем изменения
        cout << "Информация о релизе ID " << target_id << " успешно обновлена." << endl;
        write_data_to_file(list, count);
    } else {
        cout << "Ошибка: Введены некорректные данные. Изменения не сохранены." << endl;
    }
}

// 4. Удаление информации о релизе
void delete_release(music_release *list, int &count) {
    cout << "Введите ID релиза, который нужно удалить: ";
    int target_id;
    while (!(cin >> target_id)) {
        cout << "Некорректный ввод. Пожалуйста, введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int found_index = -1;
    for (int i = 0; i < count; i++) {
        if (list[i].id == target_id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        cout << "Релиз с ID " << target_id << " не найден." << endl;
        return;
    }

    for (int i = found_index; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    count--;
    cout << "Релиз ID " << target_id << " успешно удален." << endl;

    write_data_to_file(list, count);
}

// Вспомогательная функция: запись всех данных в файл (переделано на C++ потоки)
void write_data_to_file(music_release *list, int count) {
    ofstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла input.txt для записи." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        file << list[i].id << endl;
        file << list[i].title << endl;
        file << list[i].artist << endl;
        file << list[i].genre << endl;
        file << list[i].release_year << endl;
        file << list[i].producer << endl;
        file << list[i].total_streams << endl;
        file << fixed << setprecision(1) << list[i].rating << endl; // Форматирование рейтинга
        file << list[i].track_count << endl;
        file << list[i].featured_artists;
        if (i < count - 1) { // Добавляем перевод строки, если это не последний элемент
            file << endl;
        }
    }
    file.close();
    cout << "Данные успешно сохранены в input.txt." << endl;
}

// Вспомогательная функция для вывода одного релиза в файл или на экран
void print_single_release(ostream& os, const music_release* release) {
    os << "ID: " << release->id << endl;
    os << "Название: " << release->title << endl;
    os << "Исполнитель: " << release->artist << endl;
    os << "Жанр: " << release->genre << endl;
    os << "Год выпуска: " << release->release_year << endl;
    os << "Продюсер: " << release->producer << endl;
    os << "Всего прослушиваний: " << release->total_streams << endl;
    os << "Рейтинг: " << fixed << setprecision(1) << release->rating << endl;
    os << "Количество треков: " << release->track_count << endl;
    os << "Приглашенные исполнители: " << release->featured_artists << endl;
    os << "----------------------------------------" << endl;
}

// 5. Поиск и вывод информации о релизе по ID
void show_release_by_id(music_release *list, int count) {
    cout << "Введите ID релиза для просмотра: ";
    int target_id;
    while (!(cin >> target_id)) {
        cout << "Некорректный ввод. Пожалуйста, введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream out_file("output_show_by_id.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_show_by_id.txt." << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (list[i].id == target_id) {
            print_single_release(out_file, &list[i]);
            found = true;
            break;
        }
    }

    if (!found) {
        out_file << "Релиз с ID " << target_id << " не найден." << endl;
        cout << "Релиз с ID " << target_id << " не найден." << endl;
    } else {
        cout << "Информация о релизе ID " << target_id << " записана в output_show_by_id.txt" << endl;
    }
    out_file.close();
}

// 6. Поиск релизов по исполнителю
void find_releases_by_artist(music_release *list, int count) {
    char search_artist[100];
    cout << "Введите имя исполнителя для поиска: ";
    cin.getline(search_artist, sizeof(search_artist));

    ofstream out_file("output_find_by_artist.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_find_by_artist.txt." << endl;
        return;
    }

    bool found_any = false;
    out_file << "Релизы исполнителя '" << search_artist << "':" << endl;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].artist, search_artist) == 0) {
            print_single_release(out_file, &list[i]);
            found_any = true;
        }
    }

    if (!found_any) {
        out_file << "Релизы исполнителя '" << search_artist << "' не найдены." << endl;
        cout << "Релизы исполнителя '" << search_artist << "' не найдены." << endl;
    } else {
        cout << "Результаты поиска по исполнителю '" << search_artist << "' записаны в output_find_by_artist.txt" << endl;
    }
    out_file.close();
}

// 7. Поиск релизов по жанру
void find_releases_by_genre(music_release *list, int count) {
    char search_genre[50];
    cout << "Введите жанр для поиска: ";
    cin.getline(search_genre, sizeof(search_genre));

    ofstream out_file("output_find_by_genre.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_find_by_genre.txt." << endl;
        return;
    }

    bool found_any = false;
    out_file << "Релизы жанра '" << search_genre << "':" << endl;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].genre, search_genre) == 0) {
            print_single_release(out_file, &list[i]);
            found_any = true;
        }
    }

    if (!found_any) {
        out_file << "Релизы жанра '" << search_genre << "' не найдены." << endl;
        cout << "Релизы жанра '" << search_genre << "' не найдены." << endl;
    } else {
        cout << "Результаты поиска по жанру '" << search_genre << "' записаны в output_find_by_genre.txt" << endl;
    }
    out_file.close();
}

// 8. Расчет среднего рейтинга всех релизов
void calculate_average_rating(music_release *list, int count) {
    ofstream out_file("output_average_rating.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_average_rating.txt." << endl;
        return;
    }

    if (count == 0) {
        out_file << "Нет данных для расчета среднего рейтинга." << endl;
        cout << "Нет данных для расчета среднего рейтинга." << endl;
        out_file.close();
        return;
    }

    double total_rating_sum = 0.0;
    for (int i = 0; i < count; i++) {
        total_rating_sum += list[i].rating;
    }
    double average_rating = total_rating_sum / count;

    out_file << "Общее количество релизов: " << count << endl;
    out_file << "Сумма рейтингов: " << fixed << setprecision(2) << total_rating_sum << endl;
    out_file << "Средний рейтинг всех релизов: " << fixed << setprecision(2) << average_rating << endl;

    cout << "Средний рейтинг всех релизов (" << fixed << setprecision(2) << average_rating << ") записан в output_average_rating.txt" << endl;
    out_file.close();
}

// 9. Сортировка по году выпуска
bool compare_releases_by_year(const music_release &a, const music_release &b) {
    return a.release_year < b.release_year;
}

void sort_by_year(music_release *list, int count) {
    music_release temp_list[MAX_RELEASES];
    for (int i = 0; i < count; ++i) {
        temp_list[i] = list[i];
    }

    std::sort(temp_list, temp_list + count, compare_releases_by_year);

    ofstream out_file("output_sorted_by_year.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_sorted_by_year.txt." << endl;
        return;
    }

    out_file << "--- Релизы, отсортированные по году выпуска (по возрастанию) ---\n";
    for (int i = 0; i < count; i++) {
        print_single_release(out_file, &temp_list[i]);
    }
    out_file.close();
    cout << "Релизы отсортированы по году выпуска и записаны в output_sorted_by_year.txt" << endl;
}

// 10. Сортировка по количеству прослушиваний
bool compare_releases_by_streams(const music_release &a, const music_release &b) {
    return a.total_streams > b.total_streams; // По убыванию
}

void sort_by_streams(music_release *list, int count) {
    music_release temp_list[MAX_RELEASES];
    for (int i = 0; i < count; ++i) {
        temp_list[i] = list[i];
    }

    std::sort(temp_list, temp_list + count, compare_releases_by_streams);

    ofstream out_file("output_sorted_by_streams.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_sorted_by_streams.txt." << endl;
        return;
    }

    out_file << "--- Релизы, отсортированные по общему количеству прослушиваний (по убыванию) ---\n";
    for (int i = 0; i < count; i++) {
        print_single_release(out_file, &temp_list[i]);
    }
    out_file.close();
    cout << "Релизы отсортированы по прослушиваниям и записаны в output_sorted_by_streams.txt" << endl;
}

// 11. Вывод всех загруженных релизов
void show_all_releases(music_release *list, int &count) {
    ofstream out_file("output_all_releases.txt");
    if (!out_file.is_open()) {
        cerr << "Ошибка открытия файла output_all_releases.txt." << endl;
        return;
    }

    if (count == 0) {
        out_file << "Нет загруженных релизов." << endl;
        cout << "Нет загруженных релизов для вывода." << endl;
        out_file.close();
        return;
    }

    out_file << "--- Все загруженные музыкальные релизы (" << count << ") ---\n";
    for (int i = 0; i < count; i++) {
        print_single_release(out_file, &list[i]);
    }
    out_file.close();
    cout << "Все релизы записаны в output_all_releases.txt" << endl;
}

// Вспомогательная функция для проверки корректности вводимых данных
bool is_valid_release_data(const music_release& r) {
    if (r.release_year < 1900 || r.release_year > 2025) {
        cerr << "Ошибка валидации: Год выпуска должен быть между 1900 и 2025." << endl;
        return false;
    }
    if (r.total_streams < 0) {
        cerr << "Ошибка валидации: Количество прослушиваний не может быть отрицательным." << endl;
        return false;
    }
    if (r.rating < 1.0 || r.rating > 5.0) {
        cerr << "Ошибка валидации: Рейтинг должен быть от 1.0 до 5.0." << endl;
        return false;
    }
    if (r.track_count <= 0) {
        cerr << "Ошибка валидации: Количество треков должно быть положительным." << endl;
        return false;
    }
    if (strlen(r.title) == 0 || strlen(r.artist) == 0 || strlen(r.genre) == 0) {
        cerr << "Ошибка валидации: Название, исполнитель и жанр не могут быть пустыми." << endl;
        return false;
    }
    return true;
}