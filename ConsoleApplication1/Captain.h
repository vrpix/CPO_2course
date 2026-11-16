#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "Sportsman.h"
#include "Equipment.h"
#include "Shop.h"

class Captain {

	std::string name;
	std::vector<Sportsman> team;
	std::vector<Equipment> inventory;
	int budget;
	int score = 0;

public:
	Shop shop;

	Captain() {}
	Captain(std::string name, int budget) {
		this->name = name;
		this->budget = budget;
	};

	void save(std::ostream& out) {
		out << name << '%' << budget << '%' << score << '%'
			<< team.size() << '%' << inventory.size() << '%';
		for (auto& s : team)      s.save(out);
		for (auto& e : inventory) e.save(out);
	}

	void load(std::istream& in) {
		std::string token;
		std::vector<std::string> data;
		for (int i = 0; i < 5 && std::getline(in, token, '%'); i++) {
			data.push_back(token);
		}
		name = data[0];
		budget = stoi(data[1]);
		score = stoi(data[2]);
		
		for (int i = 0; i < stoi(data[3]); i++) {
			Sportsman s;
			s.load(in);
			team.push_back(s);
		}
		for (int i = 0; i < stoi(data[4]); i++) {
			Equipment e;
			e.load(in);
			inventory.push_back(e);
		}
	}

	int teamSize() {
		return team.size();
	}
	void getName() {
		std::cout << name << std::endl;
	}
	void printBudget() {
		std::cout << "Текущий бюджет: " << budget;
	}
	int getBudget() {
		return budget;
	}
	bool updateBudget(int count) {
		if (budget + count < 0) {
			return 0;
		}
		budget += count;
		return 1;
	}
	void updateScore(int score) {
		this->score += score;
	}
	void addSportsman(Sportsman s) {
		team.push_back(s);
	}
	bool saleSportmans(int i) {
		if (i >= team.size() || i < 0) {
			return 0;
		}
		budget += team[i].getPrice();
		team.erase(team.begin() + i);
		return 1;
	}
	void saleSportsman() {
		for (int i = 0; i < team.size();) {
			system("cls");
			int price = team[i].getPrice();
			std::cout << "Стоимость: " << price << std::endl;
			team[i].printSpecific();


			std::cout << "1) Продать\n";
			std::cout << "2) Далее\n";
			std::cout << "3) Назад\n";
			std::cout << "4) Текущие характеристики команды\n";
			std::cout << "5) Выход\n";

			short value = 0;
			std::cout << "Выбирете спортсмена: " << std::endl;
			while (!(std::cin >> value) || value < 1 || value > 5) {
				std::cout << "Ошибка.\nВыбирете спортсмена:: " << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			switch (value) {
			case 1:
				shop.getSportsman(team[i]);
				updateBudget(price);
				team.erase(team.begin() + i);
				break;
			case 2:
				i++;
				break;
			case 3:
				if (i > 0) i--;
				break;
			case 4:
				printBudget();
				printSpecific();
				break;
			case 5:
				return;
			}
		}
	}
	void addEquipment(Equipment e) {
		inventory.push_back(e);
	}
	std::vector<Sportsman>& selectTeam(int count) {
		if (count < 0) return team;
		else if (count > teamSize()) {
			std::cout << "Недостаточно игроков в команде. Автоматическое поражение.\n";
			static std::vector<Sportsman> emptyVector;
			return emptyVector;
		}

		std::vector<Sportsman> selected;
		int selectedCnt = 0;
		for (int i = 0; selectedCnt != count;) {
			system("cls");

			team[i].printSpecific();
			std::cout << "1) Выбрать\n";
			std::cout << "2) Далее\n";
			std::cout << "3) Назад\n";

			short value = 0;
			std::cout << "Введите номер пункта: " << std::endl;
			while (!(std::cin >> value) || value < 1 || value > 3) {
				std::cout << "Ошибка.\nВведите номер пункта: " << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			switch (value) {
			case 1:
				selected.push_back(team[i]);
				i = (i + 1) % (int)team.size();
				selectedCnt++;
				break;
			case 2:
				i = (i + 1) % (int)team.size();
				break;
			case 3:
				i = (i - 1 + team.size()) % team.size();
				break;
			}
		}
		return selected;
	}
	std::map<std::string, int>* useEquipment() {
		if (inventory.empty()) return nullptr;
		system("cls");
		std::cout << "Доступное оборудование:\n";
		std::cout << "1) Пропустить\n";
		int i = 0;
		for (; i < inventory.size(); i++) {
			std::cout << i + 2 << ") " << inventory[i].getName() << std::endl;
			std::cout << std::setw(30) << std::left << "\tПрочность: " << inventory[i].getState() << std::endl;
			inventory[i].getSpecific();
		}

		short value = 0;
		std::cout << "Введите номер пункта: " << std::endl;
		while (!(std::cin >> value) || value < 1 || value > inventory.size() + 1) {
			std::cout << "Ошибка.\nВведите номер пункта: " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (value == 1) return nullptr;

		std::map<std::string, int>* res = inventory[value - 2].use();
		if (!res) {
			inventory.erase(inventory.begin() + (value - 2));
		}
		return res;
	}
	// выводит каждого игрока
	void printTeam() {
		for (Sportsman s : team) {
			system("cls");

			s.printSpecific();
			std::cout << std::endl;

			std::cout << "1) Далее" << std::endl;
			std::cout << "2) Назад" << std::endl;

			short value = 0;
			std::cout << "Введите номер пункта: " << std::endl;
			while (!(std::cin >> value) || value < 1 || value > 2) {
				std::cout << "Ошибка.\nВведите номер пункта: " << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			switch (value) {
			case 1:
				break;
			case 2:
				return;
			}
		}
	}
	void printSpecific() {

		int strength = 0, stamina = 0, intellect = 0, skill = 0, salary = 0;
		for (Sportsman& s : team) {
			strength += s.getStrength();
			stamina += s.getStamina();
			intellect += s.getIntellect();
			skill += s.getSkill();
		}

		const int SPACE = 30;

		std::cout << std::left << std::setw(SPACE) << "Сила: " << strength << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Выносливость: " << stamina << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Интеллект: " << intellect << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Техника: " << skill << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Энергия: " << (team.empty() ? 0 : team[0].getEnergy()) << std::endl;

	}
	int trainPrefix() {
		if (team.empty()) {
			return -1;
		}

		int teamEnergy = 100;
		for (Sportsman& s : team) {
			teamEnergy = std::min(teamEnergy, s.getEnergy());
		}
		int prefix = 0;

		if (teamEnergy >= 10) {
			prefix = 0;
		}
		else if (teamEnergy >= 5) {
			prefix = 1;
		}
		else {
			prefix = 2;
		}
		return prefix;
	}
	int TrainMenu(int dayTime) {
		int teamEnergy = team[0].getEnergy();

		short prefix = -1;
		if (teamEnergy >= 18) {
			std::cout
				<< "\n1) Силовая тренировка"
				<< "\n\tДлительность: 1ч \n\tРасход энергии: 18\n\tУлучшение силы"
				<< "\n2) Бег"
				<< "\n\tДлительность: 1ч \n\tРасход энергии: 10\n\tУлучшение выносливости"
				<< "\n3) Анализ игр"
				<< "\n\tДлительность: 2ч \n\tРасход энергии: 5\n\tУлучшение интеллект"
				<< "\n4) Отдых"
				<< "\n\tДлительность: 1ч \n\tВосстановление энергии: 15"
				<< "\n5) Восстановление"
				<< "\n\tДлительность: " << 8 - dayTime << "ч\n";
			prefix = -1;
		}
		else if (teamEnergy >= 10) {
			std::cout
				<< "\n1) Бег"
				<< "\n\tДлительность: 1ч \n\tРасход энергии: 10\n\tУлучшение выносливости"
				<< "\n\tДлительность: 1ч \n\tРасход энергии: 10\n\tУлучшение выносливости"
				<< "\n2) Анализ игр"
				<< "\n\tДлительность: 2ч \n\tРасход энергии: 5\n\tУлучшение интеллект"
				<< "\n3) Отдых"
				<< "\n\tДлительность: 1ч \n\tВосстановление энергии: 15"
				<< "\n4) Восстановление"
				<< "\n\tДлительность: " << 8 - dayTime << "ч\n";
			prefix = 0;
		}
		else if (teamEnergy >= 5) {
			std::cout
				<< "\n1) Анализ игр"
				<< "\n\tДлительность: 2ч \n\tРасход энергии: 5\n\tУлучшение интеллект"
				<< "\n2) Отдых"
				<< "\n\tДлительность: 1ч \n\tВосстановление энергии: 15"
				<< "\n3) Восстановление"
				<< "\n\tДлительность: " << 8 - dayTime << "ч\n";
			prefix = 1;
		}
		else {
			std::cout
				<< "\n1) Отдых"
				<< "\n\tДлительность: 1ч \n\tВосстановление энергии: 15"
				<< "\n2) Восстановление"
				<< "\n\tДлительность: " << 8 - dayTime << "ч\n";
			prefix = 2;
		}

		short val = 0;
		std::cout << "\nВыберите тренировку: ";
		while (!(std::cin >> val) || val < 1 || val > 4 - prefix) {
			std::cout << "\nОшибка\nВыберите тренировку: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return val + prefix;
	}
	int availableTrain(int dayTime, bool bot = 0) {
		
		int (Sportsman:: * train[])(std::map<std::string, int>*) = { &Sportsman::weight, &Sportsman::running, &Sportsman::gameAnalysis };
		
		if (team.empty()) {
			std::cout << "У вас нет спортсменов. Посетите магазин\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			return 0;
		}

		int val = 0;
		if (!bot) val = TrainMenu(dayTime);
		else val = (trainPrefix() + 1) + rand() % (4 - trainPrefix());

		int time = -1;
		if (val < 3) {
			auto bonus = useEquipment();
			for (Sportsman& s : team) {
				time = (s.*train[val])(bonus);
				if (time == 0) return  0;
			}
		}
		else {

			int(Sportsman:: * rest)(int) = nullptr;
			switch (val) {
			case 3:
				rest = &Sportsman::timeout;
				break;
			case 4:
				rest = &Sportsman::rest;
				break;
			}

			for (Sportsman& s : team) {
				time = (s.*rest)(dayTime);
				if (time == 0) return  0;
			}
		}
		return time;
	}
};