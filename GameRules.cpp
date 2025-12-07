#pragma once
#include "GameRules.hpp"
#include <fstream>
#include <sstream>

void GameRules::FillRulesFieldByName(const std::string& key, const std::string& value) {
	if (key == "initial_population") initial_population = std::stoi(value);
	else if (key == "initial_wheat") initial_wheat = std::stoi(value);
	else if (key == "initial_city_size") initial_city_size = std::stoi(value);

	else if (key == "land_price_min") land_price_min = std::stoi(value);
	else if (key == "land_price_max") land_price_max = std::stoi(value);

	else if (key == "resident_consumption") resident_consumption = std::stoi(value);
	else if (key == "resident_efficiency") resident_efficiency = std::stoi(value);

	else if (key == "rounds_number") rounds_number = std::stoi(value);
	else if (key == "seeds_consumption") seeds_consumption = std::stof(value);
	else if (key == "plague_probability") plague_probability = std::stof(value);

	else if (key == "land_efficiency_min") land_efficiency_min = std::stoi(value);
	else if (key == "land_efficiency_max") land_efficiency_max = std::stoi(value);

	else if (key == "rats_consumption_rate_min") rats_consumption_rate_min = std::stof(value);
	else if (key == "rats_consumption_rate_max") rats_consumption_rate_max = std::stof(value);

	else if (key == "arrivals_number_min") arrivals_number_min = std::stoi(value);
	else if (key == "arrivals_number_max") arrivals_number_max = std::stoi(value);

	else if (key == "death_percentage_for_loss") death_percentage_for_loss = std::stof(value);

	else if (key == "dead_percentage_lower_limit_bad") dead_percentage_lower_limit_bad = std::stoi(value);
	else if (key == "lands_per_resident_bad") lands_per_resident_bad = std::stoi(value);
	else if (key == "dead_percentage_lower_limit_ok") dead_percentage_lower_limit_ok = std::stoi(value);
	else if (key == "lands_per_resident_ok") lands_per_resident_ok = std::stoi(value);
	else if (key == "dead_percentage_lower_limit_good") dead_percentage_lower_limit_good = std::stoi(value);
	else if (key == "lands_per_resident_good") lands_per_resident_good = std::stoi(value);
}

bool GameRules::IsRulesFilled() {
	if (initial_population == -1 or initial_wheat == -1 or initial_city_size == -1 or
		land_price_min == -1 or land_price_max == -1 or
		resident_consumption == -1 or resident_efficiency == -1 or
		rounds_number == -1 or seeds_consumption == -1 or plague_probability == -1 or
		land_efficiency_min == -1 or land_efficiency_max == -1 or
		rats_consumption_rate_min == -1 or rats_consumption_rate_max == -1 or
		arrivals_number_min == -1 or arrivals_number_max == -1 or
		death_percentage_for_loss == -1 or
		dead_percentage_lower_limit_bad == -1 or lands_per_resident_bad == -1 or
		dead_percentage_lower_limit_ok == -1 or lands_per_resident_ok == -1 or
		dead_percentage_lower_limit_good == -1 or lands_per_resident_good == -1) {
		return false;
	}

	return true;
}

bool GameRules::LoadRules(const std::string& filename) {
	std::ifstream game_rules(filename);
	if (!game_rules) {
		return false;
	}

	std::string rule;
	while (std::getline(game_rules, rule)) {
		if (rule.empty()) continue;

		std::stringstream ss(rule);
		std::string key, value;
		if (std::getline(ss, key, '=') && std::getline(ss, value)) {
			FillRulesFieldByName(key, value);
		}
	}

	return true;
}