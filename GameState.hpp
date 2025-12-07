#pragma once

struct GameState {
	int year = -1;

	int population = -1;
	int wheat = -1;
	int city_size = -1;

	int deaths = -1;
	int newcomers = -1;
	bool plague = false;

	int harvested_per_acre = -1;
	int total_harvest = -1;
	int rats_ate = -1;

	int land_price = -1;
};

inline bool IsFilled(const GameState& state) {
	if (state.year == -1 or state.population == -1 or state.wheat == -1 or
		state.city_size == -1) {
		return false;
	}

	return true;
}