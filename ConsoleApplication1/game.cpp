#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include <stdarg.h>
#include <algorithm>

#include "save.h"
#include "game.h"
#include "Competition.h"



void game(Captain* players, int bots, int playersCnt, int curDay) {
	srand(time(NULL));
	
	Save save;
	Competition competition = { "Финальное соревнование", -1 };

	const int DAY = 2;
	const int HOUR = 8;

	for (int k = curDay; k < DAY; k++) {
		system("cls");
		std::cout << "День: " << k + 1 << std::endl;
		std::cout << "Для выход из игры нажмите q\n";
		save.autoSave(playersCnt, bots, k, players);
		char ch = ' ';
		if (save.isAvailable()) {
			std::cout << "Нажмите s для сохранения\n";
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get(ch);
		if (ch == 's') save.userSave(playersCnt, bots, k, players);
		else if (ch == 'q') return;

		int i = 0;
		for (; i < playersCnt - bots; i++) {
			for (int j = 0; j < HOUR;) {
				system("cls");
				std::cout << "Игрок: "; players[i].getName();
				std::cout << "Бюджет: " << players[i].getBudget() << std::endl;
				std::cout << std::endl;
				std::cout << "День: " << k + 1 << std::endl;
				std::cout << "Время: " << 9 + j << ":00" << std::endl;
				std::cout << "1) Вывести характеристики игроков\n";
				std::cout << "2) Вывести характеристики команды\n";
				std::cout << "3) Начать тренировку\n";
				std::cout << "4) Перейти в магазин\n";
				
				short val = 0;
				std::cout << "\nВыберите пункт: ";
				while (!(std::cin >> val) || val < 0 || val > 4) {
					std::cout << "\nОшибка\nВыберите пункт: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				switch (val) {
				case 1:
					players[i].printTeam();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					break;
				case 2:
					players[i].printSpecific();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					break;
				case 3:
					if (players[i].teamSize() <= 0) {
						std::cout << "В вашей команде нет спортсменов\n";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cin.get();
						break;
					}
					players[i].printSpecific();

					{
						int spent = players[i].availableTrain(j);
						if (spent > 0) j += spent;
						else {
							std::cout << "Тренировка невозможна (нет времени или энергии)\n";
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cin.get();
						}
					}
					break;
				case 4:
					players[i].shop.menu(players[i]);
					break;
				}
			}
		}
		for (; i < playersCnt; i++) {
			for (int j = 0; j < HOUR;) {
				players[i].shop.randSportsman(players[i]);
				int spent = players[i].availableTrain(j, 1);
				if (spent <= 0) break;
				j += spent;
			}
		}
		//заработок капитанов 
		for (int a = 0; a < playersCnt; a++) {
			players[a].updateBudget(players[a].teamSize() * 100);
		}
	}
	
	competition.startCompetition(players, playersCnt);

	delete[] players;
}