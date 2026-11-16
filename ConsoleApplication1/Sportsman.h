#pragma once
#include <map>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <iomanip>
#include <algorithm>

class Sportsman {
	std::string name;
	int strength;
	int stamina;
	int intellect;
	int skill;
	int energy;
	int price;
	int potential;

public:
	Sportsman() {};
	Sportsman(std::string name, int strength, int stamina, int intellect, int skill, int potential, int price) {
		this->name = name;
		this->strength = strength;
		this->stamina = stamina;
		this->intellect = intellect;
		this->skill = skill;
		this->energy = 100;
		this->price = price;
		this->potential = potential;
	};

	void save(std::ostream& out) const {
		out << name << '%'
			<< strength << '%' << stamina << '%'
			<< intellect << '%' << skill << '%'
			<< energy << '%' << price << '%'
			<< potential << '%';
	}

	void load(std::istream& in) {
		std::string token;
		std::vector<std::string> data;
		for (int i = 0; i < 8 && std::getline(in, token, '%'); i++) {
			data.push_back(token);
		}
		name = data[0];
		strength = stoi(data[1]);
		stamina = stoi(data[2]);
		intellect = stoi(data[3]);
		skill = stoi(data[4]);
		energy = stoi(data[5]);
		price = stoi(data[6]);
		potential = stoi(data[7]);
	}

	int getStrength() {
		return strength;
	}

	int getStamina() {
		return stamina;
	}

	int getIntellect() {
		return intellect;
	}

	int getSkill() {
		return skill;
	}

	int getEnergy() {
		return energy;
	}

	int getPrice() {
		return price;
	}

	void updateEnergy(int val) {
		energy = std::clamp(energy + val, 0, 100);
	}

	int curPrise(int count, ...) {
		if (count <= 0) return 0;
		va_list args;
		va_start(args, count);

		int gain = 0;
		for (int i = 0; i < count; i++) {
			gain += va_arg(args, int);
		}
		va_end(args);
		return gain * 100;
	}

	// расчет результата тренировки 
	int train(int current, int bonus, int base, int energy) {
		if (this->energy < energy) return -1;

		double energyFactor;
		if (this->energy >= 70)      energyFactor = 1.0;
		else if (this->energy >= 50) energyFactor = 0.85;
		else if (this->energy >= 30) energyFactor = 0.6;
		else if (this->energy >= 10) energyFactor = 0.3;
		else                   energyFactor = 0.0;

		return std::max(0, (int)floor(base * (1 - (double)current / potential) * bonus * energyFactor));
	}

	// бег
	int running(std::map<std::string, int>* bonus) {
		int baf = bonus && bonus->contains("stamina") ? bonus->at("stamina") : 1;
		int addStamina = train(stamina, baf, 4, 1);
		baf = bonus && bonus->contains("skill") ? bonus->at("skill") : 1;
		int addSkill = train(skill, baf, 2, 1);

		if (addSkill == -1 || addStamina == -1) return 0;

		updateEnergy(-10);

		stamina += addStamina;
		skill += addSkill;
		price += curPrise(2, addStamina, addSkill);
		return 1;
	}
	// силовая тренировка
	int weight(std::map<std::string, int>* bonus) {
		int baf = bonus && bonus->contains("strength") ? bonus->at("strength") : 1;
		int addStrength = train(strength, baf, 6, 1);

		if (addStrength == -1) return 0;

		updateEnergy(-18);

		strength += addStrength;
		price += curPrise(1, addStrength);
		return 1;
	}
	// анализ игр
	int gameAnalysis(std::map<std::string, int>* bonus) {
		int baf = bonus && bonus->contains("intellect") ? bonus->at("intellect") : 1;
		int addIntellect = train(intellect, baf, 4, 2);
		baf = bonus && bonus->contains("skill") ? bonus->at("skill") : 1;
		int addSkill = train(skill, baf, 3, 2);

		if (addIntellect == -1 || addSkill == -1) return 0;

		updateEnergy(-5);

		intellect += addIntellect;
		skill += addSkill;
		price += curPrise(2, addSkill, addIntellect);
		return 2;
	}
	//отдых
	int timeout(int dayTime) {
		if (dayTime + 1 > 8) return 0;
		updateEnergy(15);
		return 1;
	}
	// восстановление
	int rest(int dayTime) {
		if (dayTime < 0 || dayTime > 8) return 0;
		int gain = 105 * (8 - dayTime) / (14 - dayTime);
		updateEnergy(gain);
		return 8 - dayTime;
	}

	void printSpecific() {
		const int SPACE = 30;

		std::cout << std::left << std::setw(SPACE) << "Имя:" << name << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Сила: " << strength << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Выносливость: " << stamina << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Интеллект: " << intellect << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Техника: " << skill << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Энергия: " << energy << std::endl;
		std::cout << std::left << std::setw(SPACE) << "Стоимость: " << price << std::endl;
	}
};