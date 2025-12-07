#pragma once
#include <string>

class GameRules {

public:
	void FillRulesFieldByName(const std::string& key, const std::string& value);
	bool IsRulesFilled();
	bool LoadRules(const std::string& filename);

	// Initial parameters
	int initial_population = -1;
	int initial_wheat = -1;
	int initial_city_size = -1;

	// Land price parameters
	int land_price_min = -1;
	int land_price_max = -1;

	// Resident parameters
	int resident_consumption = -1;
	int resident_efficiency = -1;

	int rounds_number = -1;

	// Land efficiency parameters
	int land_efficiency_min = -1;
	int land_efficiency_max = -1;

	// New arrivals parameters
	int arrivals_number_min = -1;
	int arrivals_number_max = -1;

	// Final assessment borders
	int dead_percentage_lower_limit_bad = -1;
	int lands_per_resident_bad = -1;
	int dead_percentage_lower_limit_ok = -1;
	int lands_per_resident_ok = -1;
	int dead_percentage_lower_limit_good = -1;
	int lands_per_resident_good = -1;

	// Other parameters
	float seeds_consumption = -1;
	float plague_probability = -1;
	float rats_consumption_rate_min = -1;
	float rats_consumption_rate_max = -1;
	float death_percentage_for_loss = -1;
};