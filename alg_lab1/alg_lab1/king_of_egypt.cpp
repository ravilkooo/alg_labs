#include "king_of_egypt.h"
#include "utils.h"

#define CSI "\x1B["
#define red_col_begin CSI "31m"
#define grn_col_begin CSI "32m"
#define yell_col_begin CSI "33m"
#define blue_col_begin CSI "34m"
#define col_end "\033[0m"

Gamedata g_gamedata;

void LaunchGame()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // menu and prepare (load/init) data
    if (!LaunchMainMenu())
    {
        return;
    }
    
    ShowIntroGameState();

    // game loop
    for (; g_gamedata.year < 11;)
    {
        if (!UpdateGame())
            break;
        g_gamedata.year++;
        SaveGame();

        // exit or continue
        LaunchLocalMenu();
    }
    

    // game results
    if (g_gamedata.year == 11)
        ShowGameScore();

}

bool LaunchMainMenu() {
    std::cout << yell_col_begin <<
        "                              A \n"
        "       .-.                   /_\\ \n"
        "      '   `          :      /_|_\\ \n"
        "      `._.'         :::    /|__|_\\ \n"
        "                   ::.::  /|_|__|_\\      :\n"
        "                  ::.:.::/__|_|__|_\\    :.:\n"
        "                 :..:.:./_|__|__|__|\\  :.:.:\n"
        "                :.:..:./|__|___|__|__\\:.:..::\n"
        " ..............::..:../__|___|__|___|_\\..:..::................\n"
        "    ..........:..:..:/_|__|___|___|___|\\:..:..::::::::::::::::::::\n"
        "::::::::::::::.:..:./___|___|___|___|___\\....................\n"
        "        .........../..!...!...!...!...!..\\...............\n"
        "............................................................\n"
        "    ..................Правитель Египта........................\n"
        "............................................................\n\n" grn_col_begin
        "                   Добро пожаловать в игру!\n\n" col_end;

    // load/new
    bool game_is_started = false;
    while (!game_is_started) {
        std::string choice;

        std::cout << grn_col_begin "* Начать новую игру (" yell_col_begin "N" grn_col_begin ")\n"
            << "* Загрузить предыдущую игру (" yell_col_begin "L" grn_col_begin ")\n"
            << "* Выйти из игры (" yell_col_begin "E" grn_col_begin ")" col_end "\n>" yell_col_begin;
        std::cin >> choice;

        if (choice == "L") {
            if (!LoadGame()) {
                std::cout << red_col_begin "Не удалось загрузить игру.\n" col_end;
            }
            else
            {
                // load game
                //std::cout << col_end "Игра успешно загружена!\n";
                game_is_started = true;

            }
        }
        else if (choice == "N") {
            // new game
            game_is_started = true;
            InitNewGame();
        }
        else if (choice == "E") {
            std::cout << col_end;
            return false;
        }

        std::cout << col_end CSI "3J" << CSI "19;0H" << CSI "J" << std::flush;


        if (choice != "N" && choice != "L") {
            std::cout << red_col_begin "Некорректный ввод - выберите ещё раз.\n" col_end;
        }
    }

    std::cout << CSI "3J" << CSI "H" << CSI "J" << std::flush;

    return true;
}

void ShowIntroGameState() {
    std::cout << "Могущественный фараон, сын богов и повелитель земель,\n"
        << "начинается "
        << yell_col_begin << g_gamedata.year << col_end " год Вашего правления.\n"
        << "Услышь мой доклад о благосостоянии твоего царства.\n";

    std::cout << "  Население Ваших земель составляет "
        << yell_col_begin << g_gamedata.population << col_end " человек.\n"
        << "  Запасы продовольствия состовляют "
        << yell_col_begin << g_gamedata.bushels << col_end " бушелей.\n"
        << "  В Вашей власти сейчас находится "
        << yell_col_begin << g_gamedata.acres << col_end " акров земли.\n"
        << "  Цена 1 акра земли сейчас "
        << yell_col_begin << g_gamedata.acre_price << col_end " бушелей.\n\n\n\n\n";
}

bool SaveGame() {
    std::ofstream out_file("last_save");

    if (!out_file) {
        return false;
    }

    try {
        out_file << g_gamedata.year << std::endl;
        out_file << g_gamedata.population << std::endl;
        out_file << g_gamedata.bushels << std::endl;
        out_file << g_gamedata.acres << std::endl;
        out_file << g_gamedata.acre_price << std::endl;

        for (int i = 0; i < 10; ++i) {
            out_file << g_gamedata.starve_to_death_statistic[i] << std::endl;
        }
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "SaveGame error: " << e.what() << "\n";
        return false;
    }
    
    //out_file.close();
    return true;
}

void LaunchLocalMenu(){
    std::string choice = ".";
    while (choice != "Y" && choice != "N") {

        std::cout << col_end red_col_begin << "[ Выйти из игры? " yell_col_begin "Y" red_col_begin "/" yell_col_begin "N" red_col_begin " ]"
            << col_end << "\n>" yell_col_begin;
        std::cin >> choice;
        if (choice == "Y") {
            std::cout << col_end;
            return;
        }

        std::cout << CSI "3J" << CSI "12;0H" << CSI "J" << std::flush;

        if (choice != "N" && choice != "Y") {
            std::cout << red_col_begin "Некорректный ввод - выберите ещё раз.\n" col_end;
        }
    }

    std::cout << col_end CSI "3J" << CSI "12;0H" << CSI "J" << std::flush;
}

bool UpdateGame() {
    // decision
    std::cout << "\nВаше Величество,\n"
        << "Позвольте обсудить важные аспекты управления вашими владениями.\n"
        << "Позвольте мне задать несколько вопросов, чтобы лучше понять Ваши намерения:\n";

    int buy_acres;
    int sell_acres;
    int feed_bushels;
    int plant_acres;

    while (true) {
        std::cout << "  Какое количество акров земли Вы намерены приобрести\n"
            << "  для расширения ваших владений?\n  >" << yell_col_begin;
        // добавить обработку ввода
        CorrectInputHandler(buy_acres);

        std::cout << col_end "  Какое количество акров земли Вы намерены продать?\n  >" << yell_col_begin;
        CorrectInputHandler(sell_acres);

        std::cout << col_end "  Какое количество бушелей пшеницы Вы хотите выделить\n"
            << "  для обеспечения продовольствием нашего народа?\n  >" << yell_col_begin;
        CorrectInputHandler(feed_bushels);

        std::cout << col_end "  Сколько акров земли, по Вашему мнению,\n"
            << "  необходимо засеять пшеницей в этом году?\n  >" << yell_col_begin;
        CorrectInputHandler(plant_acres);

        std::cout << col_end CSI "3J" << CSI "14;0H" << CSI "J" << std::flush;

        if ((buy_acres >= 0 && buy_acres * g_gamedata.acre_price <= g_gamedata.bushels)
            && (sell_acres >= 0 && sell_acres <= g_gamedata.acres + buy_acres)
            && (feed_bushels >= 0 && feed_bushels <= g_gamedata.bushels + (sell_acres - buy_acres) * g_gamedata.acre_price)
            && (plant_acres >= 0 && plant_acres <= g_gamedata.acres + buy_acres - sell_acres
                && plant_acres <= (g_gamedata.bushels + (sell_acres - buy_acres) * g_gamedata.acre_price) * 2
                && plant_acres <= g_gamedata.population * 10))
            break;
        else
            std::cout << "  Ваше царство не может позволить себе такой план.\n"
            << "  В Вашем распоряжение только "
            yell_col_begin << g_gamedata.population << col_end << " человек, "
            yell_col_begin << g_gamedata.bushels << col_end << " бушелей пшеницы и "
            yell_col_begin << g_gamedata.acres << col_end << " акров земли.\n";

    }

    std::cout << CSI "3J" << CSI "H" << CSI "J" << std::flush;

    // annual routine
    g_gamedata.acres += buy_acres;
    g_gamedata.bushels -= buy_acres * g_gamedata.acre_price;

    g_gamedata.acres -= sell_acres;
    g_gamedata.bushels += sell_acres * g_gamedata.acre_price;

    g_gamedata.bushels -= feed_bushels;
    g_gamedata.bushels -= plant_acres / 2;

    //int collected_bushels = rand() % (5 * plant_acres + 1) + plant_acres;
    int collected_bushels_per_acre = rand() % 6 + 1;
    g_gamedata.bushels += collected_bushels_per_acre * plant_acres;

    int rat_bushels = int(0.07 * (rand() * 1. / RAND_MAX) * g_gamedata.bushels);
    g_gamedata.bushels -= rat_bushels;
    
    int prev_population = g_gamedata.population;

    g_gamedata.population = std::min(feed_bushels / 20, g_gamedata.population);

    int starve_to_death_population = prev_population - g_gamedata.population;
    g_gamedata.starve_to_death_statistic[g_gamedata.year - 1] = starve_to_death_population * 1. / prev_population;

    if (starve_to_death_population > 0.45 * prev_population) {
        // THE END! (STARVING)
        // 
        std::cout << "  Великий правитель, принятые вами решения привели к непоправимым последствиям.\n"
            "  " yell_col_begin << starve_to_death_population << col_end " человек умерло от голода.\n"
            "  Царство пришло в упадок, народ не годует, повсюду ходят слухи о грядущим бунте против Вас.\n"
            "  Дабы сберечь Вашу жизнь, вам стоит добровольно снять полномочия правителя...\n" red_col_begin
            "                           Вы проиграли!\n\n" col_end;
        return false;
    }

    // заметка clamp
    int newcomers = std::max(0,
        std::min(starve_to_death_population / 2 + (5 - collected_bushels_per_acre) * g_gamedata.bushels / 600 + 1, 50));
    g_gamedata.population += newcomers;

    // plague
    bool plague = false;
    if (rand() * 1. / RAND_MAX < 0.15) {
        g_gamedata.population /= 2;
        plague = true;
    }

    g_gamedata.acre_price = rand() % 10 + 17;

    // report
    std::cout << "Могущественный фараон, сын богов и повелитель земель,\n"
        << "прошёл " << yell_col_begin << g_gamedata.year << col_end " год вашего правления.\n"
        << "Услышь мой доклад о благосостоянии твоего царства.\n";

    std::cout << "  " << yell_col_begin << starve_to_death_population << col_end " человек умерло с голоду.\n  "
        << yell_col_begin << newcomers << col_end " человек прибыло в Ваше царство.\n";
    if (plague) {
        std::cout << "  К несчастью, половину жителей Вашего царства сразила чума.\n";
    }
    std::cout << "  Население Ваших земель составляет " << yell_col_begin << g_gamedata.population << col_end " человек.\n"
        << "  Его силами было собрано " << yell_col_begin << collected_bushels_per_acre * plant_acres << col_end
        << " бушелей пшеницы, по " << yell_col_begin << collected_bushels_per_acre << col_end " бушеля с акра.\n"
        << "  Крысы уничтожили " << yell_col_begin << rat_bushels << col_end " бушелей пшеницы.\n"
        << "  Запасы продовольствия состовляют " << yell_col_begin << g_gamedata.bushels << col_end " бушелей.\n"
        << "  В Вашей власти сейчас находится " << yell_col_begin << g_gamedata.acres << col_end " акров земли.\n"
        << "  Цена 1 акра земли сейчас " << yell_col_begin << g_gamedata.acre_price << col_end " бушелей.\n\n";

    return true;

}

void ShowGameScore() {
    double p_score = 0;
    for (int i = 0; i < 10; i++)
    {
        p_score += g_gamedata.starve_to_death_statistic[i];
    }
    p_score = p_score / 10;
    double l_score = g_gamedata.acres * 1. / g_gamedata.population;
    std::cout << "P = " << p_score * 100 << "% \n";
    std::cout << "L = " << l_score << "\n";

    // Оценка результатов
    if (p_score > 0.33 && l_score < 7) {
        std::cout << "Из-за вашей " red_col_begin "некомпетентности в управлении" col_end ", народ восстал, и вы были изгнаны из своих городов.\n"
            "Теперь вы скитаетесь по пустыне, как заблудший странник.\n";
    }
    else if (p_score > 0.10 && l_score < 9) {
        std::cout << "Вы правили " yell_col_begin "с железной рукой" col_end ", подобно Рамзесу или Тутанхамону.\n"
            "Народ вздохнул с облегчением, но никто не желает видеть Вас вновь на троне.\n";
    }
    else if (p_score > 0.03 && l_score < 10) {
        std::cout << "Вы справились " grn_col_begin "довольно неплохо" col_end ", у Вас, конечно, есть недоброжелатели,\n"
            "но многие жаждут видеть Вас снова в роли фараона.\n";
    }
    else {
        std::cout << blue_col_begin "Фантастика!" col_end " Ваши достижения сравнимы с великими строителями пирамид и мудрецами древности.\n";
    }
}

bool LoadGame() {
    std::ifstream in_file("last_save");

    if (!in_file) {
        return false;
    }
    try {
        in_file >> g_gamedata.year;
        in_file >> g_gamedata.population;
        in_file >> g_gamedata.bushels;
        in_file >> g_gamedata.acres;
        in_file >> g_gamedata.acre_price;

        for (int i = 0; i < 10; ++i) {
            in_file >> g_gamedata.starve_to_death_statistic[i];
        }
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "LoadGame error: " << e.what() << "\n";
        return false;
    }

    //in_file.close();

    return true;
}

void InitNewGame() {
    g_gamedata = { 1, 100, 2800, 1000, rand() % 10 + 17, { 0,0,0,0,0,0,0,0,0,0 } };
}

void CorrectInputHandler(int& var) {
    std::string s;
    std::cin >> s;
  
    while (!is_number(s)) {

        std::cout << CSI "3J" << CSI "1F" << CSI "J" << std::flush;
        std::cout << col_end red_col_begin "Пожалуйста, используйте язык математики доступный нашим писарям." col_end "  >" << yell_col_begin;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> s;
    }
    var = atoi(s.c_str());
}