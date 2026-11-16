#pragma once
#include <iostream>
#include <fstream>
#include "save.h"
#include "game.h"

void load_game() {
	std::ifstream file("save.txt");

	Captain* players; 
	int bots; 
	int playersCnt;
	int curDay;

	if (file.is_open()) {
		// извлекаем данные из файла с настройками
		std::string token;

		std::vector<std::string> data;
		for (int i = 0; i < 3 && std::getline(file, token, '%'); i++) {
			data.push_back(token);
		}
		playersCnt = stoi(data[0]);
		bots = stoi(data[1]);
		curDay = stoi(data[2]);

		players = new Captain[playersCnt];
		for (int i = 0; i < playersCnt; i++) {
			players[i].load(file);
		}

		game(players, bots, playersCnt, curDay);
	}
	else {
		std::cout << "Нет сохраненной игры\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}
}