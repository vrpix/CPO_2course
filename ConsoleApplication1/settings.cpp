#pragma once
#include <iostream>
#include "menu.h"
#include "settings.h"
#include <set>
#include <vector>
#include <format>
#include <fstream>
#include <string>



class Settings {
	int aliveCnt;
	int allCnt;
	std::string complexity;
	std::vector<std::string> names; 

	const std::set<std::string> allNames = {
			"Тарасов",
			"Бобров",
			"Лобановский",
			"Бесков",
			"Романцев",
			"Газзаев",
			"Карпин",
			"Сёмин",
			"Черчесов",
			"Гончаренко",
			"Тихонов",
			"Кварцяный",
			"Хиддинк",
			"Капелло",
			"Моуринью",
			"Гвардиола",
			"Клопп",
			"Анчелотти",
			"Фергюсон",
			"Венгер"
	};

public:
	Settings() {
		std::ifstream file("settings.txt");
		
		if (file.is_open()) {
			// извлекаем данные из файла с настройками
			std::string token;
			std::vector<std::string> data;
			
			while (std::getline(file, token, '%')) {
				data.push_back(token);
			}

			aliveCnt = stoi(data[0]);
			allCnt = stoi(data[1]);
			complexity = data[2];
			for (int i = 3; i < data.size(); i++) {
				names.push_back(data[i]);
			}

		}
		else {
			// выстовляем знаения по умолчанию, если файл с настройками пуст
			aliveCnt = 1;
			allCnt = 2;
			complexity = "Легкий";
			if (allNames.size() >= 2) {
				names = { *allNames.begin(), *std::next(allNames.begin()) };
			}
		}
	};
	// перезаписываем файл с настройками
	~Settings() {
		std::ofstream file("settings.txt", std::ios::out | std::ios::trunc);
		if (!file.is_open()) {
			std::cerr << "File opening error" << std::endl;
			return;
		}

		file << aliveCnt << '%' << allCnt << '%' << complexity;
		for (std::string n : names) {
			file << '%' << n;
		}

		file.close();
	};

	int getAliveCnt() {
		return aliveCnt;
	}

	int getAllCnt() {
		return allCnt;
	}

	std::string getComplexity() {
		return complexity;
	}

	// вывод установленных имен игроков 
	void getNames() {

		for (int i = 1; i <= names.size(); i++) {
			std::cout << "Игрок " << i << ") " << names[i-1] << std::endl;
		}

		std::cout << "\n\t1) Изменить имя" << std::endl;
		std::cout << "\t2) Назад" << std::endl;
		
		short value = 0;
		std::cout << "Выберите пункт: ";
		while (!(std::cin >> value) || value < 0 || value > 2) {
			std::cout << "Ошибка.\nВыберите пункт: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		switch (value) {
		case 1:
			setNames();
			break;
		case 2:
			return;
		}

	}

	// настройка количества игроков
	void setPlayerCnt() {
		std::cout << "Введите количество живых игроков: ";
		while (!(std::cin >> aliveCnt) || aliveCnt <= 0 || aliveCnt > INT_MAX) {
			std::cout << "Ошибка.\nВведите количество живых игроков: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << "Введите количество всех игроков: ";
		while (!(std::cin >> allCnt) || allCnt < aliveCnt || allCnt > INT_MAX) {
			std::cout << "Ошибка.\nВведите количество всех игроков: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		names.clear();
		
		// автоматическое задание имен новым игрокам 
		int len = allNames.size();

		for (int i = 0; i < allCnt; i++) {
			names.push_back(*(std::next(allNames.begin(), i%len)));
		}
	}

	// задание уровня сложности
	void setComplexity() {
		std::cout << "Уровни сложности:\n" << "\t1) Сложный\n" << "\t2) Средний\n" << "\t3) Легкий\n" << "\t4) Назад" << std::endl;
		int value = 0;
		std::cout << "Выбирете уровень сложности: ";
		while (!(std::cin >> value) || value < 1 || value > 4) {
			std::cout << "Ошибка.\nВыбирете уровень сложности: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		switch (value) {
		case 1:
			complexity = "Сложный";
			break;
		case 2:
			complexity = "Средний";
			break;
		case 3:
			complexity = "Легкий";
			break;
		case 4:
			return;
		}
	}

	// изменение имени игрока
	std::string changeName() {

		std::cout << "Доступные имена: " << std::endl;
		
		// вывод предустановленных имен
		int i = 1;
		for (std::string n : allNames) {
			std::cout << '\t' << i << ") " << n << std::endl;
			i++;
		}
		std::cout << '\t' << i << ") " << "Ввести имя" << std::endl;
		std::cout << '\t' << i + 1 << ") " << "Назад" << std::endl;

		int value = 0;
		std::cout << "Выберите имя: ";
		while (!(std::cin >> value) || value < 1 || value > allNames.size() + 2) {
			std::cout << "Ошибка.\nВыберите имя: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		// ввод своего варианта имени с проверкой на наличие спец символа % 
		if (value == allNames.size() + 1) {
			std::string str;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			do {
				std::cout << "Введите имя: ";
				std::getline(std::cin, str);
			} while (str.find('%',0) != std::string::npos);

			return str;
		}

		if (value == allNames.size() + 2) {
			return "";
		}

		// передача предустановленного имени
		return *std::next(allNames.begin(), value-1);
	}
	
	// установка имени игрока 
	void setNames() {
		// перебираем имена игроков
		for (int i = 1; i <= names.size();i++) {
			system("cls");
			
			std::cout << "Игрок " << i << ") " << names[i-1] << std::endl;

			std::cout << "\n\t1) Изменить" << std::endl;
			std::cout << "\t2) Далее" << std::endl;
			std::cout << "\t3) Назад" << std::endl;

			int value = 0;
			std::cout << "Выберите пункт: ";
			while (!(std::cin >> value) || value < 1 || value > 3) {
				std::cout << "Ошибка.\nВыберите пункт: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::string tmp = "";
			switch (value) {
			case 1:
				tmp = changeName();
				if (!tmp.empty()) names[i-1] = tmp;
				break;
			case 2:
				break;
			case 3:
				return;
			}

		}
	}
};

// меню настроек 
void settings() {
	
	Settings setting;
	while (true) {
		system("cls");

		// меню настроек
		std::string menu = std::format(R"(
    ========================================
                                          
                  Настройки          
                                          
       1. Количество игроков:
             Живых: {}
             Всего: {}   
       2. Сложность: {}                  
       3. Имена игроков                       
       4. Назад                            
                                          
    ========================================
    )", setting.getAliveCnt(), setting.getAllCnt(), setting.getComplexity());

		std::cout << menu << std::endl;

		short value = 0;
		std::cout << "Выберите пункт для изменения: ";
		while (!(std::cin >> value) || value < 0 || value > 4) {
			std::cout << "Ошибка.\nВыберите пункт для изменения: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		switch (value) {
		case 1:
			// изменение количества игроков
			setting.setPlayerCnt();
			break;
		case 2:
			// изменение сложности
			setting.setComplexity();
			break;
		case 3:
			// вывод имен игроков
			setting.getNames();
			break;
		case 4:
			// выход в главное меню 
			return;
		}
	}
}