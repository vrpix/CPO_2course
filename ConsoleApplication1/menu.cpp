#pragma once
#include <iostream>
#include "menu.h"
#include "settings.h"
#include "newGame.h"
#include "save.h"
#include "about.h"
#include <string>


void call_menu() {
    const short START_GAME = 1;
    const short LOAD_GAME = 2;
    const short SETTINGS = 3;
    const short ABOUT_GAME = 4;
    const short END_GAME = 5;

    short value = 0;

    const std::string menu = R"(
    ========================================
                                           
               Соревнования армий          
                                           
        1. Начать игру                     
        2. Загрузить игру                  
        3. Настройки                       
        4. О программе                     
        5. Выход                           
                                           
    ========================================
    )";

    while (true)
    {
        system("cls");

        std::cout << menu << std::endl;

        std::cout << "Выберите пункт меню: " << std::endl;
        while (!(std::cin >> value) || value < 1 || value > 5) {
            std::cout << "Ошибка.\nВыберите пункт меню: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        system("cls");
        switch (value) {
        case START_GAME:
            newGame();
            break;
        case LOAD_GAME:
            load_game();
            break;
        case SETTINGS:
            settings();
            break;
        case ABOUT_GAME:
            about();
            break;
        case END_GAME:
            exit(0);
        }
    }
}