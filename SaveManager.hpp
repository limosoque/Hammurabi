#pragma once
#include <string>

struct GameState;

class SaveManager {

public:
	SaveManager() : filePath("game_save.txt") {};
	SaveManager(const std::string& path) : filePath(path) {};

	bool SaveGame(const GameState& gameState);
	GameState LoadGame();

	void FillGameStateFieldByName(GameState& state, const std::string& key, const std::string& value);

private:
	// Game state variables names
	std::string year = "year";
	std::string population = "population";
	std::string wheat =	"wheat";
	std::string city_size = "city_size";
	std::string deaths = "deaths";
	std::string newcomers = "newcomers";

	std::string filePath;
};