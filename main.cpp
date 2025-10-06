#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct GameRules {
	int initial_population = -1;
	int initial_wheat = -1;
	int initial_city_size = -1;

	int land_price_min = -1;
	int land_price_max = -1;
	
	int resident_consumption = -1;
	int resident_efficiency = -1;
	
	int rounds_number = -1;
	
	int land_efficiency_min = -1;
	int land_efficiency_max = -1;
	
	int arrivals_number_min = -1;
	int arrivals_number_max = -1;	

	int dead_percentage_lower_limit_bad = -1;
	int lands_per_resident_bad = -1;
	int dead_percentage_lower_limit_ok = -1;
	int lands_per_resident_ok = -1;
	int dead_percentage_lower_limit_good = -1;
	int lands_per_resident_good = -1;

	float seeds_consumption = -1;
	float plague_probability = -1;
	float rats_consumption_rate_min = -1;
	float rats_consumption_rate_max = -1;
	float death_percentage_for_loss = -1;

};

void fillRulesFieldByName(GameRules& rules, const std::string& key, const std::string& value) {
	if (key == "initial_population") rules.initial_population = std::stoi(value);
	else if (key == "initial_wheat") rules.initial_wheat = std::stoi(value);
	else if (key == "initial_city_size") rules.initial_city_size = std::stoi(value);

	else if (key == "land_price_min") rules.land_price_min = std::stoi(value);
	else if (key == "land_price_max") rules.land_price_max = std::stoi(value);

	else if (key == "resident_consumption") rules.resident_consumption = std::stoi(value);
	else if (key == "resident_efficiency") rules.resident_efficiency = std::stoi(value);

	else if (key == "rounds_number") rules.rounds_number = std::stoi(value);
	else if (key == "seeds_consumption") rules.seeds_consumption = std::stof(value);
	else if (key == "plague_probability") rules.plague_probability = std::stof(value);

	else if (key == "land_efficiency_min") rules.land_efficiency_min = std::stoi(value);
	else if (key == "land_efficiency_max") rules.land_efficiency_max = std::stoi(value);

	else if (key == "rats_consumption_rate_min") rules.rats_consumption_rate_min = std::stof(value);
	else if (key == "rats_consumption_rate_max") rules.rats_consumption_rate_max = std::stof(value);

	else if (key == "arrivals_number_min") rules.arrivals_number_min = std::stoi(value);
	else if (key == "arrivals_number_max") rules.arrivals_number_max = std::stoi(value);

	else if (key == "death_percentage_for_loss") rules.death_percentage_for_loss = std::stof(value);

	else if (key == "dead_percentage_lower_limit_bad") rules.dead_percentage_lower_limit_bad = std::stoi(value);
	else if (key == "lands_per_resident_bad") rules.lands_per_resident_bad = std::stoi(value);
	else if (key == "dead_percentage_lower_limit_ok") rules.dead_percentage_lower_limit_ok = std::stoi(value);
	else if (key == "lands_per_resident_ok") rules.lands_per_resident_ok = std::stoi(value);
	else if (key == "dead_percentage_lower_limit_good") rules.dead_percentage_lower_limit_good = std::stoi(value);
	else if (key == "lands_per_resident_good") rules.lands_per_resident_good = std::stoi(value);
}

bool isRulesFilled(const GameRules& rules) {
	if (rules.initial_population == -1 or rules.initial_wheat == -1 or rules.initial_city_size == -1 or
		rules.land_price_min == -1 or rules.land_price_max == -1 or
		rules.resident_consumption == -1 or rules.resident_efficiency == -1 or
		rules.rounds_number == -1 or rules.seeds_consumption == -1 or rules.plague_probability == -1 or
		rules.land_efficiency_min == -1 or rules.land_efficiency_max == -1 or
		rules.rats_consumption_rate_min == -1 or rules.rats_consumption_rate_max == -1 or
		rules.arrivals_number_min == -1 or rules.arrivals_number_max == -1 or
		rules.death_percentage_for_loss == -1 or
		rules.dead_percentage_lower_limit_bad == -1 or rules.lands_per_resident_bad == -1 or
		rules.dead_percentage_lower_limit_ok == -1 or rules.lands_per_resident_ok == -1 or
		rules.dead_percentage_lower_limit_good == -1 or rules.lands_per_resident_good == -1) {
		return false;
	}

	return true;
}

bool loadRules(GameRules& rules, const std::string& filename) {
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
			fillRulesFieldByName(rules, key, value);
		}
	}

	return true;
}

int main() {
	GameRules rules;
	loadRules(rules, "game_rules.txt");

	if (!isRulesFilled(rules)) {
		std::cerr << "Error reading the rules file\n";
		return 1;
	}

	std::cout << "HEllo";

	return 0;
}