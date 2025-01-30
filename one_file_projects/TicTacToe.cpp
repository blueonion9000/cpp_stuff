#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>

#define BOARD_SIZE 3;

constexpr char ERASE_SEQ[] = "\033[2J\033[1;1H";
constexpr std::size_t kBoardSize = BOARD_SIZE;
constexpr unsigned char kPlayerA = 'x';
constexpr unsigned char kPlayerB = 'o';

using Board = std::array<std::array<unsigned char, kBoardSize>, kBoardSize>;

bool CheckWin(const Board &gb, const unsigned char &p);
bool CheckDraw(const Board &gb);
void DrawBoard(std::ostream &os, const Board &gb);
void InitBoard(Board &gb);

int main(int argc, char **argv)
{
  Board game_board;
  InitBoard(game_board);
  unsigned char current_player = kPlayerA;
  while (true) {
    int input_x = 0, input_y = 0;
    while (true) {
      std::cout << ERASE_SEQ;
      DrawBoard(std::cout, game_board);
      std::cout << '\n';
      std::cout << "Enter coords for player [" << current_player << "] (row, column): ";
      std::cin >> input_y >> input_x;
      input_x -= 1; // Make input 0-based for array
      input_y -= 1;
      if ((input_x < 0 || input_y > game_board.size() - 1) || (input_y < 0 || input_y > game_board.size() - 1) ||
          game_board[input_y][input_x] != ' ') {
        std::cout << "Invalid coords, try again.\n";
      } else {
        game_board[input_y][input_x] = current_player;
        break;
      }
    }

    if (CheckWin(game_board, current_player)) {
      std::cout << ERASE_SEQ;
      DrawBoard(std::cout, game_board);
      std::cout << "Player [" << current_player << "] won!\n";
      break;
    }
    if (CheckDraw(game_board)) {
      std::cout << ERASE_SEQ;
      DrawBoard(std::cout, game_board);
      std::cout << "Draw!\n";
      break;
    }

    current_player = current_player == kPlayerA ? kPlayerB : kPlayerA;
  }

  return EXIT_SUCCESS;
}

bool CheckWin(const Board &gb, const unsigned char &p)
{
  const std::size_t sz = gb.size();

  // Check rows and columns
  for (std::size_t row = 0; row < sz; ++row) {
    bool row_win = true;
    bool col_win = true;
    for (std::size_t col = 0; col < sz; ++col) {
      if (gb[row][col] != p)
        row_win = false;
      if (gb[col][row] != p)
        col_win = false;
    }
    if (row_win || col_win)
      return true;
  }

  // Check diagonals
  bool diag_nw_win = true;
  bool diag_sw_win = true;
  for (std::size_t row = 0; row < sz; ++row) {
    if (gb[row][row] != p)
      diag_nw_win = false;
    if (gb[row][sz - row - 1] != p)
      diag_sw_win = false;
  }
  if (diag_nw_win || diag_sw_win)
    return true;

  return false;
}

bool CheckDraw(const Board &gb)
{
  for (const auto &row : gb)
    for (const auto &cell : row)
      if (cell == ' ')
        return false;

  return true;
}

// Draws board with grid and indexes
// Crude implementation, I know :p
void DrawBoard(std::ostream &os, const Board &gb)
{
  const std::size_t sz = gb.size();

  for (std::size_t row = 0; row < sz; ++row) {
    if (row == 0) {
      std::cout << "   ";
      for (std::size_t col = 0; col < sz; ++col) {
        std::cout << ' ' << col + 1 << ' ';
        if (col < sz - 1)
          os << ' ';
      }
      std::cout << '\n';
    }
    std::cout << ' ' << row + 1 << ' ';
    for (std::size_t col = 0; col < sz; ++col) {
      os << ' ' << gb[row][col] << ' ';
      if (col < sz - 1)
        os << '|';
    }
    os << '\n';
    if (row < sz - 1)
      os << "   ";
    for (std::size_t col = 0; col < sz; ++col) {
      if (row < sz - 1) {
        os << "---";
        if (col < sz - 1)
          os << '+';
      }
    }
    if (row < sz - 1)
      os << '\n';
    std::flush(os);
  }
}

void InitBoard(Board &gb)
{
  for (auto &row : gb) {
    for (auto &c : row) {
      c = ' ';
    }
  }
}
