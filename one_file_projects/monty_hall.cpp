#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>

constexpr std::size_t n_doors = 3;
unsigned door_number = 1;
unsigned game_count = 0, win_count = 0;

struct GameDoor {
  GameDoor() : number(this->door_number++) {};
  unsigned number;
  bool is_chosen = false;
  bool has_prize = false;
  static unsigned door_number;

  void PrepareForNextGame()
  {
    is_chosen = false;
    has_prize = false;
  }
};

unsigned GameDoor::door_number = 1;

void InitializeRandomness();

int main(void)
{
  InitializeRandomness();
  using DoorArray = std::array<GameDoor, n_doors>;
  DoorArray doors;
  auto GetRandIndex = [doors]() { return std::rand() % doors.size(); };
  unsigned player_choice;

  // Game loop
  while (true) {
    ++::game_count;

    // Randomly select winning door
    doors[rand() % doors.size()].has_prize = true;

    // Prompt user for input
    std::cout << "Pick a door (1-" << doors.size() << "): ";
    std::cin >> player_choice;

    if (player_choice >= 1 && player_choice <= doors.size()) { // If legit input
      player_choice -= 1;                                      // 1-based index => 0-based index
      doors[player_choice].is_chosen = true;
      const GameDoor *door_reveal, *door_last_chance;
      if (doors[player_choice].has_prize) {
        // If player's chosen the right door - randomly choose door to reveal
        while (true) {
          auto i = GetRandIndex();
          if (doors[i].is_chosen)
            continue;
          door_reveal = &doors.at(i);
          break;
        }

        // Last available door will be offered
        for (const auto &door : doors) {
          if (&door != door_reveal && !door.is_chosen) {
            door_last_chance = &door;
          }
        }
        // If player's chosen a door with no prize
      } else {
        for (const auto &door : doors) {
          if (!door.is_chosen) {
            // Another door with no prize will be revealed
            if (!door.has_prize)
              door_reveal = &door;
            // Door with prize will be offered
            else
              door_last_chance = &door;
          }
        }
      }

      // "Last chance"
      std::cout << "Host opens the door number " << door_reveal->number << ".\n";
      std::cout << "\"Nothing here. I'm giving you last chance to change your "
                   "mind.\"\n";
      std::cout << "Switch to door number " << door_last_chance->number << "?: ";
      for (char c, e = 0; std::cin >> c;) { // char 'e' for exit condition
        switch (std::tolower(c)) {
        case 'y':
          player_choice = door_last_chance->number;
          player_choice -= 1; // doorNo is 1-based index
        case 'n':
          e = 1;              // if y or n -- break out of loop
        default:
          break;
        }
        if (e)
          break;
      }

      // Win / lose
      if (doors[player_choice].has_prize == true) {
        ++::win_count;
        std::cout << "You won!";
      } else
        std::cout << "You lose.";
      std::cout << " Win rate: " << static_cast<double>(::win_count) / ::game_count << " (W/(W+L): " << ::win_count
                << "/" << ::game_count << ")\n"
                << std::endl;
      for (auto &door : doors)
        door.PrepareForNextGame();
    } else { // If input > 3 or input < 1
      std::cout << "STOP" << std::endl;
      return EXIT_SUCCESS;
    }
  }
}

void InitializeRandomness()
{
  std::srand(static_cast<unsigned int>(std::time(0)));
  std::rand();
}
