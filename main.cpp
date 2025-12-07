#include <iostream>
#include <random>
#include "GameRules.hpp"
#include "SaveManager.hpp"
#include "GameState.hpp"

// randomiser
int randInt(int from, int to) {
    static std::mt19937 rng((unsigned)std::random_device{}());
    std::uniform_int_distribution<int> dist(from, to);
    return dist(rng);
}

// read integer with input validation
int readInt() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите целое число: ";
    }
    return x;
}

// print game state
void printReport(const GameState& gameState) {
    std::cout << "\nМой повелитель, соизволь поведать тебе\n";
    std::cout << "в году " << gameState.year << " твоего высочайшего правления\n";

    if (gameState.deaths > 0)
        std::cout << gameState.deaths << " человек умерли с голоду, ";
    if (gameState.newcomers > 0)
        std::cout << gameState.newcomers << " человек прибыли в наш великий город;\n";
    if (gameState.plague)
        std::cout << "Чума уничтожила половину населения;\n";

    std::cout << "Население города сейчас составляет " << gameState.population << " человек;\n";
    std::cout << "Мы собрали " << gameState.total_harvest
        << " бушелей пшеницы, по " << gameState.harvested_per_acre << " бушеля с акра;\n";
    std::cout << "Крысы истребили " << gameState.rats_ate
        << " бушелей пшеницы, оставив " << gameState.wheat << " бушелей в амбарах;\n";
    std::cout << "Город сейчас занимает " << gameState.city_size << " акров;\n";
    std::cout << "1 акр земли стоит сейчас " << gameState.land_price << " бушель.\n\n";
}

// print initial game state
void printInitReport(const GameState& gameState) {
    std::cout << "\nМой принц, то есть... Мой повелитель. Ваш отец неожиданно скончался на охоте с лордами, поэтому теперь Вы будете править нами, Вашими верными поддаными. Мы надеемся, что при Вашем правлении жизнь станет еще лучше\n";
    std::cout << "Ситуация такова\n";

    std::cout << "Население города сейчас составляет " << gameState.population << " человек;\n";
    std::cout << "На складах имеется " << gameState.wheat << " бушелей пшеницы;\n";
    std::cout << "Город сейчас занимает " << gameState.city_size << " акров;\n";
    std::cout << "1 акр земли стоит сейчас " << gameState.land_price << " бушель.\n\n";
    }

// game year
bool PlayYear(const GameRules& rules, GameState& gameState, bool bPrintInitReport) {
    gameState.land_price = randInt(rules.land_price_min, rules.land_price_max);
    if (bPrintInitReport) printInitReport(gameState);
    else printReport(gameState);

    std::cout << "Что пожелаешь, повелитель?\n";

    int buyLand, sellLand, feedGrain, plantLand;

    // land buying
    while (true) {
        std::cout << "Сколько акров земли повелеваешь купить? ";
        buyLand = readInt();
        if (buyLand < 0) continue;
        if (buyLand * gameState.land_price <= gameState.wheat) break;
        std::cout << "О, повелитель! У нас недостаточно пшеницы!\n";
    }

	// land selling
    while (true) {
        std::cout << "Сколько акров земли повелеваешь продать? ";
        sellLand = readInt();
        if (sellLand < 0) continue;
        if (sellLand <= gameState.city_size) break;
        std::cout << "О, повелитель! У нас нет столько земли!\n";
    }

    gameState.city_size += buyLand - sellLand;
    gameState.wheat -= buyLand * gameState.land_price;
    gameState.wheat += sellLand * gameState.land_price;

	// feeding people
    while (true) {
        std::cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
        feedGrain = readInt();
        if (feedGrain < 0) continue;
        if (feedGrain <= gameState.wheat) break;
        std::cout << "О, повелитель! У нас только " << gameState.wheat << " бушелей пшеницы!\n";
    }

    gameState.wheat -= feedGrain;

	// planting
    while (true) {
        std::cout << "Сколько акров земли повелеваешь засеять? ";
        plantLand = readInt();
        if (plantLand < 0) continue;
        if (plantLand <= gameState.city_size &&
            plantLand <= gameState.population * rules.resident_efficiency &&
            plantLand * rules.seeds_consumption <= gameState.wheat) break;

        std::cout << "О, повелитель, пощади нас! У нас только "
            << gameState.population << " человек, "
            << gameState.wheat << " бушелей пшеницы и "
            << gameState.city_size << " акров земли!\n";
    }

    // decrease in wheat after planting
    gameState.wheat -= int(plantLand * rules.seeds_consumption);

	// harvest
    gameState.harvested_per_acre = randInt(rules.land_efficiency_min, rules.land_efficiency_max);
    gameState.total_harvest = plantLand * gameState.harvested_per_acre;
    gameState.wheat += gameState.total_harvest;

    // rats 
    double maxEat = std::max(rules.rats_consumption_rate_min, 
        rules.rats_consumption_rate_max * gameState.wheat);
    gameState.rats_ate = randInt(rules.rats_consumption_rate_min, (int)maxEat);
    gameState.wheat -= gameState.rats_ate;

	// starvation
    int peopleFed = feedGrain / rules.resident_consumption;
    if (peopleFed >= gameState.population) {
        gameState.deaths = 0;
    }
    else {
        gameState.deaths = gameState.population - peopleFed;
        gameState.population = peopleFed;

        if (gameState.deaths > (gameState.population + gameState.deaths) * rules.death_percentage_for_loss) {
            std::cout << "\nТы допустил гибель народа! Игра окончена.\n";
            return false;
        }
    }

	// newcomers
    int newcomers = gameState.deaths / 2
        + (5 - gameState.harvested_per_acre) * gameState.wheat / 600 + 1;

    if (newcomers < rules.arrivals_number_min) newcomers = rules.arrivals_number_min;
    if (newcomers > rules.arrivals_number_max) newcomers = rules.arrivals_number_max;

    gameState.newcomers = newcomers;
    gameState.population += newcomers;

	// plague
    gameState.plague = (randInt(1, 100) <= rules.plague_probability * 100);
    if (gameState.plague) {
        gameState.population /= 2;
    }

    if (gameState.population <= 0) {
        std::cout << "\nВсе население вымерло. Игра окончена.\n";
        return false;
    }

    gameState.year++;
    return true;
}

void DisplayMainMenu() {
	std::cout << "1. Начать игру\n";
	std::cout << "2. Загрузить игру\n";
	std::cout << "3. Выйти из игры\n";
}

void InitializeGameState(GameState& gameState, const GameRules& gameRules) {
    gameState.year = 1;
    gameState.population = gameRules.initial_population;
    gameState.wheat = gameRules.initial_wheat;
    gameState.city_size = gameRules.initial_city_size;
}

int main() {
	setlocale(LC_ALL, "Russian");

	GameRules rules;
	rules.LoadRules("game_rules.txt");

	if (!rules.IsRulesFilled()) {
		std::cerr << "Error reading the rules file\n";
		return 1;
	}

	GameState gameState;
	SaveManager saveManager("game_save.txt");

	// game session loop
	int command = 0;
	while (true) {
		// main menu
		while (true) {
			DisplayMainMenu();
			std::cin >> command;

			if (command == 1) {
				break;
			}
			else if (command == 2) {
				gameState = saveManager.LoadGame();
				if (IsFilled(gameState)) {
					std::cout << "Сохранение загружено\n";
					break;
				}
				else {
					std::cout << "Не найдено валидных сохранений\n";
				}
			}
			else if (command == 3) {
				return 0;
			}
			else {
				std::cout << "Неправильная команда\n";
			}
		}

        int totalStarved = 0;
		// game loop
        if (command != 2) {
            InitializeGameState(gameState, rules);
            if (!PlayYear(rules, gameState, true)) {
                totalStarved += gameState.deaths;
                goto results;
            }

            totalStarved += gameState.deaths;
            saveManager.SaveGame(gameState);
        }
		while (gameState.year <= 10) {
            if (!PlayYear(rules, gameState, false)) {
                totalStarved += gameState.deaths;
                break;
            }

            totalStarved += gameState.deaths;

            saveManager.SaveGame(gameState); 
		}

        results:
        // percentage of deaths from starvation
        double StarvatedPercentage = (double)totalStarved / (100.0 * gameState.year) * 100.0;

        // acres per citizen
        double AcrePerCitizen = (double)gameState.city_size / gameState.population;

        std::cout << "\n=== Итоги Вашего правления ===\n";
        std::cout << "Среднегодовой процент смертности от голода: " << StarvatedPercentage << "%\n";
        std::cout << "Акров земли на одного жителя: " << AcrePerCitizen << "\n";

        if (StarvatedPercentage > 33.0 && AcrePerCitizen < 7.0) {
            std::cout << "Из-за вашей некомпетентности народ изгнал вас из города. Теперь вы вынуждены влачить жалкое существование в изгнании\n";
        }
        else if (StarvatedPercentage > 10.0 && AcrePerCitizen < 9.0) {
            std::cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем\n";
        }
        else if (StarvatedPercentage > 3.0 && AcrePerCitizen < 10.0) {
            std::cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова\n";
        }
        else {
            std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше\n";
        }
	}

	return 0;
}