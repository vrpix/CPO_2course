#pragma once
#include <iostream>
#include "menu.h"
#include "about.h"

void about() {
	std::cout << R"(
Выполнил: Зеленов Дмитрий
Вариант: 7
Название игры : «Соревнования армий»
Версия: 5
)";

	short value = 0;
	std::cout << "Введите 4 для возвращения в меню: " << std::endl;
	while (!(std::cin >> value) && value != 4) {
		std::cout << "Ошибка.\nВведите 4 для возвращения в меню: " << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}