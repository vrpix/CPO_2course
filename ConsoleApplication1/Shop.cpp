#include "Shop.h"
#include "Captain.h"

int shopMenu() {
	system("cls");
	std::cout << "1) Спортсмены\n";
	std::cout << "2) Оборудование и экипировка\n";
	std::cout << "3) Продать спортсмена\n";
	std::cout << "4) Продолжить\n";

	short value = 0;
	std::cout << "Выбирете пункт меню: " << std::endl;
	while (!(std::cin >> value) || value < 1 || value > 4) {
		std::cout << "Ошибка.\nВыбирете пункт меню: " << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return value;
}

void Shop::menu(Captain& cap) {
	
	while (true) {
		int value = shopMenu();

		switch (value) {
		case 1:
			avalibaleSportmans(cap);
			break;
		case 2:
			avalibaleEquipment(cap);
			break;
		case 3:
			cap.saleSportsman();
			break;
		case 4:
			return;
		}
	}
}

void Shop::getSportsman(Sportsman s) {
	sportsmans.push_back(s);
}

void Shop::randSportsman(Captain& cap) {
	int tmp = rand() % sportsmans.size();
	for (int i = 0; sportsmans[tmp].getPrice() > cap.getBudget(); i++) {
		if (i >= sportsmans.size() || sportsmans.empty()) return;
		tmp = rand() % sportsmans.size();
	}
	cap.addSportsman(sportsmans[tmp]);
	cap.updateBudget(-sportsmans[tmp].getPrice());
	sportsmans.erase(sportsmans.begin() + tmp);
}

void Shop::avalibaleSportmans(Captain& cap) {
	for (int i = 0; i < sportsmans.size() || i < 0;) {
		system("cls");
	
		cap.printBudget(); std::cout << std::endl;
		sportsmans[i].printSpecific();

		std::cout << "1) Купить\n";
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
			if (cap.updateBudget(-sportsmans[i].getPrice())) {
				cap.addSportsman(sportsmans[i]);
				sportsmans.erase(sportsmans.begin() + i);
				return;
			}
			else {
				std::cout << "Недостаточно средств\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.get();
			}
			break;
		case 2:
			i++;
			break;
		case 3:
			if (i > 0) i--;
			break;
		case 4:
			cap.printBudget();
			cap.printSpecific();
			break;
		case 5:
			return;
		}
	}
}

void Shop::avalibaleEquipment(Captain& cap) {
	const int SPACE = 30;
	for (int i = 0; i < equipment.size();) {
		system("cls");
		
		cap.printBudget(); std::cout << std::endl;
		std::cout << std::left << std::setw(SPACE) << equipment[i].getName() << std::endl;
		equipment[i].getSpecific();
		std::cout << std::left << std::setw(SPACE) << "Стоимость: " << equipment[i].getPrice() << std::endl;

		std::cout << "1) Купить\n";
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
			if (cap.updateBudget(-equipment[i].getPrice())) {
				cap.addEquipment(equipment[i]);
				equipment.erase(equipment.begin() + i);
				return;
			}
			else {
				std::cout << "Недостаточно средств\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.get();
			}
			break;
		case 2:
			i++;
			break;
		case 3:
			if (i > 0) i--;
			break;
		case 4:
			cap.printBudget();
			cap.printSpecific();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			break;
		case 5:
			return;
		}
	}
}