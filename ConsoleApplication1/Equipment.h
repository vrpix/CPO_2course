#pragma once
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

class Equipment {
	std::string name;
	std::map<std::string, int> bonus;
	int state;
	int price;

public:
	Equipment(){}
	Equipment(std::string name, const std::map<std::string, int>& bonus, int state, int price) :
		name(name),
		bonus(bonus),
		state(state),
		price(price) {
	}

	void save(std::ostream& out) {
		out << name << '%' << state << '%' << price << '%'
			<< bonus.size() << '%';
		for (std::pair<std::string, int> el: bonus)
			out << el.first << '%' << el.second << '%';
	}

	void load(std::istream& in) {
		std::string token;
		std::vector<std::string> data;
		for (int i = 0; i < 4 && std::getline(in, token, '%'); i++) {
			data.push_back(token);
		}
		name = data[0];
		state = stoi(data[1]);
		price = stoi(data[2]);
		
		for (int i = 0; i < stoi(data[3]); i++) {
			std::getline(in, token, '%');
			std::string key = token;
			std::getline(in, token, '%');
			std::string val = token;
			bonus[key] = stoi(val);
		}
	}

	std::map<std::string, int>* use() {
		if (!state) return nullptr;
		if(updateState(-10)) return &bonus;
		return nullptr;
	}

	void getSpecific() {
		short SPACE = 30;
		std::cout << std::left << std::setw(SPACE) << "\tСила: " << (bonus.contains("strength") ? bonus.at("strength") : 0) << std::endl;
		std::cout << std::left << std::setw(SPACE) << "\tВыносливость: " << (bonus.contains("stamina") ? bonus.at("stamina") : 0) << std::endl;
		std::cout << std::left << std::setw(SPACE) << "\tИнтеллект: " << (bonus.contains("intellect") ? bonus.at("intellect") : 0) << std::endl;
		std::cout << std::left << std::setw(SPACE) << "\tТехника: " << (bonus.contains("skill") ? bonus.at("skill") : 0) << std::endl;
	}

	int getPrice() {
		return price;
	}

	int getState() {
		return state;
	}

	std::string getName() {
		return name;
	}

	int updateState(int val) {
		state = std::max(0, state + val);
		return state;
	}
};