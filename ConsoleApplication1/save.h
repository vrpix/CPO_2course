#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include "Captain.h"

class Captain;

using Clock = std::chrono::steady_clock;


class Save {
	Clock::time_point lastSave;

	static constexpr std::chrono::minutes AUTOSAVE_INTERVAL{ 30 };
	static constexpr std::chrono::seconds MANUAL_COOLDOWN{ 60 };

public:
	Save() {
		lastSave = std::chrono::steady_clock::now();
	}

	bool isAvailable() {
		return Clock::now() - lastSave >= MANUAL_COOLDOWN;
	}

	void saveToFile(int alleCnt, int bots, int curDay, Captain* players) {
		std::ofstream file;
		file.open("save.txt", std::ios::out | std::ios::trunc);

		if (!file.is_open()) {
			std::cerr << "File opening error" << std::endl;
			return;
		}

		file << alleCnt << '%' << bots << '%' << curDay << '%';
		for (int i = 0; i < alleCnt; i++) {
			players[i].save(file);
		}

		file.close();
		lastSave = Clock::now();
		std::cout << "Игра сохранена\n";
	}
	void userSave(int alleCnt, int bots, int curDay, Captain* players) {
		if (Clock::now() - lastSave >= MANUAL_COOLDOWN) {
			saveToFile(alleCnt, bots, curDay, players);
		}
	}
	void autoSave(int alleCnt, int bots, int curDay, Captain* players) {
		if (Clock::now() - lastSave >= AUTOSAVE_INTERVAL) {
			saveToFile(alleCnt, bots, curDay, players);
		}
	}
};

void load_game();