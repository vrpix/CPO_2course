#pragma once
#include <vector>
#include <iostream>
#include <limits>

#include "Sportsman.h"
#include "Equipment.h"

class Captain;

class Shop {
	std::vector<Sportsman> sportsmans {
		{"Эррион Найтон", 50, 85, 55, 75, 92, 12000},
		{"Коннор Бедард", 60, 75, 70, 80, 94, 15000},
		{"Карлос Насар", 90, 70, 50, 80, 85, 18000},
		{"Ламин Ямаль", 55, 80, 75, 85, 96, 20000},
		{"Киллиан Мбаппе", 70, 90, 80, 92, 96, 45000},
		{"Лука Дончич", 75, 85, 95, 90, 97, 42000},
		{"Александр Овечкин", 85, 80, 75, 90, 95, 40000},
		{"Юлимар Рохас", 65, 85, 70, 95, 96, 38000},
		{"Усэйн Болт", 70, 95, 60, 90, 99, 60000},
		{"Леброн Джеймс", 90, 88, 95, 92, 98, 65000},
		{"Пеле", 75, 85, 90, 98, 99, 70000},
		{"Уэйн Гретцки ", 70, 80, 98, 97, 99, 68000},
		{"Василий Алексеев", 99, 80, 60, 85, 98, 60000},
	};

	std::vector<Equipment> equipment {
		{"Кроссовки «Bolt»", {{"stamina", 20}, {"skill", 10}}, 40, 2200},
		{"Шиповки «Fastest Man»", {{"stamina", 10}, {"skill", 25}}, 35, 3000},
		{"Бутсы «Yamal»", {{"stamina", 10}, {"skill", 15}}, 45, 2800},
		{"Коньки «Great One»", {{"stamina", 10}, {"skill", 20}}, 35, 3200},
		{"Кроссовки «Air Jordan»", {{"stamina", 15}, {"skill", 15}}, 50, 3500},
		{"Компрессионный костюм «Athlete»", {{"stamina", 12}, {"skill", 12}}, 35, 1800},
		{"Пояс штангиста «Alekseev»", {{"strength", 30}}, 50, 2800},
		{"Шлем «Hockey Legend»", {{"strength", 15}, {"skill", 10}}, 40, 2400},
		{"Щитки «Basketball Pro»", {{"stamina", 15}, {"skill", 10}}, 40, 2200},
		{"Штанга «Titan»", {{"strength", 38}}, 100, 5500},
		{"Беговая дорожка «Marathon»", {{"stamina", 30}}, 80, 4500},
		{"Универсальный тренажёр «Olympus»", {{"stamina", 15}, {"skill", 15},{"intellect", 15}, {"strength", 15}}, 80, 7500},
		{"Пульсометр «Rhythm»", {{"stamina", 10}, {"intellect", 10}}, 80, 1800},
		{"Тактическая доска «Scheme»", {{"intellect", 22}}, 100, 1200},
		{"Планшет аналитика «Forecast»", {{"skill", 10}, {"intellect", 30}}, 60, 4200},
		{"Умные очки «Vector»", {{"skill", 12}, {"intellect", 18}}, 50, 3400},
		{"Браслет «Balance»", {{"stamina", 5}, {"intellect", 5}}, 50, 900},
	};

public:
	Shop() {}

	void menu(Captain& cap);
	void saleSportsman(Captain& cap);
	void avalibaleSportmans(Captain& cap);
	void avalibaleEquipment(Captain& cap);
	void getSportsman(Sportsman s);
	void randSportsman(Captain& cap);
};