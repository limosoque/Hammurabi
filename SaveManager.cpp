#include "SaveManager.hpp"
#include <fstream>
#include <sstream>
#include "GameState.hpp"

bool SaveManager::SaveGame(const GameState& gameState)
{
	std::ofstream save_file(filePath);
	if (!save_file) {
		return false;
	}

	save_file << year << "=" << gameState.year << '\n'
			<< population << "=" << gameState.population << '\n'
			<< wheat << "=" << gameState.wheat << '\n'
			<< city_size << "=" << gameState.city_size << '\n'
			<< deaths << "=" << gameState.deaths << '\n'
			<< newcomers << "=" << gameState.newcomers << '\n';

	return true;
}

GameState SaveManager::LoadGame()
{
	GameState state;

	std::ifstream save_file(filePath);
	if (!save_file) {
		return state;
	}

	std::string row;
	while (std::getline(save_file, row)) {
		if (row.empty()) continue;

		std::stringstream ss(row);
		std::string key, value;
		if (std::getline(ss, key, '=') && std::getline(ss, value)) {
			FillGameStateFieldByName(state, key, value);
		}
	}

	return state;
}


void SaveManager::FillGameStateFieldByName(GameState& state, const std::string& key, const std::string& value) {
	if (key == year) state.year = std::stoi(value);
	else if (key == population) state.population = std::stoi(value);
	else if (key == wheat) state.wheat = std::stoi(value);
	else if (key == city_size) state.city_size = std::stoi(value);
	else if (key == deaths) state.deaths = std::stoi(value);
	else if (key == newcomers) state.newcomers = std::stoi(value);
}