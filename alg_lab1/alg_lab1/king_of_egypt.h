#pragma once

#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>

// Основная информация об игре
struct Gamedata {
	int year;
	int population;
	int bushels;
	int acres;
	int acre_price;
	double starve_to_death_statistic[10];

	//time_t game_start_time;
};

bool LaunchMainMenu();

void InitNewGame();
void LaunchGame();

void ShowIntroGameState();

void LaunchLocalMenu();

bool UpdateGame();

bool SaveGame();
bool LoadGame();

void CorrectInputHandler(int& var);

void ShowGameScore();