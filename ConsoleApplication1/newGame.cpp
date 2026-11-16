#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include "newGame.h"
#include "game.h"

struct GetSettings {
	int aliveCnt = -1;
	int allCnt = -1;
	std::string complexity;
	std::vector<std::string> names;
};
GetSettings uploadSettings(std::string fileName) {
	GetSettings setting;
	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Ошибка загрузки файла настроек\n";
		exit(-1);
	}

	std::string token;
	std::vector<std::string> data;

	while (std::getline(file, token, '%')) {
		data.push_back(token);
	}

	setting.aliveCnt = stoi(data[0]);
	setting.allCnt = stoi(data[1]);
	setting.complexity = data[2];
	for (int i = 3; i < data.size(); i++) {
		setting.names.push_back(data[i]);
	}

	return setting;
}
void newGame() {
	Captain* players;
	int bots;

	GetSettings s = uploadSettings("settings.txt");
	bots = s.allCnt - s.aliveCnt;
	players = new Captain[s.allCnt];

	if (s.aliveCnt < 0) {
		std::cout << "Ошибка загрузки настроек\n";
		exit(-1);
	}

	int budget = 0;
	if (s.complexity == "Легкий") {
		budget = 40000;
	}
	else if (s.complexity == "Средний") {
		budget = 20000;
	}
	else {
		budget = 12000;
	}

	int i = 0;
	for (; i < s.aliveCnt; i++) {
		std::cout << "Игрок" << i + 1 << ") " << s.names[i] << std::endl;
		players[i] = { s.names[i], budget };
	}

	for (; i < s.allCnt; i++) {
		std::cout << "Бот" << i + 1 << ") " << s.names[i] << std::endl;
		players[i] = { s.names[i], budget };
	}

	game(players, bots, s.allCnt, 0);
}

