#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "Captain.h"
#include "Sportsman.h"

class Competition {
	std::string name;
	int teamSize;

public:
	Competition(std::string name, int teamSize) :name(name), teamSize(teamSize) {};

		int playerScore(Sportsman& s) {
		return s.getStrength() * 0.25 + s.getStamina() * 0.30
				+ s.getIntellect() * 0.15 + s.getSkill() * 0.3;
	}

	int calculateScore(std::vector<Sportsman>& team) {
		if (team.empty()) return 0;
		int score = 0;
		for (Sportsman& s : team) {
			score += playerScore(s);
		}
		return score;
	}
	

	void startCompetition(Captain* players, int playersCnt) {
		
		std::vector<std::pair<Captain*, int>> score;
		score.resize(playersCnt);
		for (int i = 0; i < playersCnt; i++) {
			score[i] = { &players[i], calculateScore(players[i].selectTeam(teamSize)) };
			players[i].updateScore(score[i].second);
		}
		std::sort(score.begin(), score.end(), [](const auto& a, const auto& b) {
			return a.second > b.second;
			});

		system("cls");
		std::cout << name << std::endl;
		std::cout << "Победители: " << std::endl;
		for (int i = 0; i < score.size() ; i++) {
			if (score[i].second == 0) {
				score[i].first->getName(); std::cout << ": дисквалифицирован\n";
				continue;
			}
			std::cout << i + 1 << " место: "; score[i].first->getName();
			std::cout << "счёт: " << score[i].second << std::endl;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}
};