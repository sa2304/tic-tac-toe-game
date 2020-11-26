#include <algorithm>
#include <iostream>
#include <vector>

static const size_t ROWLENGTH = 3;
static const size_t COLUMNLENGTH = 3;

enum class Player {
  A, B
};

//------------------------------------------------------------------------------
std::istream & ReadMove(std::istream & is, std::vector<int> & move) {
  char bracket, comma;
  is >> bracket >> move[0] >> comma >> move[1] >> bracket;

  return is;
}

//------------------------------------------------------------------------------
std::istream & ReadAllMoves(std::istream & is, std::vector<std::vector<int>> & moves) {
  char bracket, comma;
  std::cin >> bracket;
  do {
    std::vector<int> move = {0,0};
    ReadMove(std::cin, move);
    // FIXME Use emplace to avoid copying
    moves.push_back(move);
    std::cin >> comma;

//    std::clog << "row = " << move.row
//              << ", column = " << move.column
//              << std::endl;
  } while (',' == comma);

  return is;
}

//------------------------------------------------------------------------------
bool isPlayerMove(Player player, size_t move_idx) {
  return ( Player::A == player && move_idx % 2 == 0 )
      || ( Player::B == player && move_idx % 2 );
}

//------------------------------------------------------------------------------
bool isRowFilled(size_t rownum, const std::vector<std::vector<int>> & moves,
                 Player player) {
  size_t row_items_count = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if ( isPlayerMove(player, i)
         && moves.at(i).at(0) == rownum ) {
        ++row_items_count;
    }
  }

  return row_items_count == ROWLENGTH;
}

//------------------------------------------------------------------------------
bool isColumnFilled(size_t colnum, const std::vector<std::vector<int>> & moves,
                    Player player) {
  size_t column_items_count = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if (isPlayerMove(player, i)
        && moves.at(i).at(1) == colnum) {
      ++column_items_count;
    }
  }

  return column_items_count == COLUMNLENGTH;
}

//------------------------------------------------------------------------------
bool isTopLeftDiagonalFilled(const std::vector<std::vector<int>> & moves, Player player) {
  size_t diag_cells_filled = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if (isPlayerMove(player, i)) {
      const std::vector<int> & cell = moves.at(i);
      const std::vector<int> cell00 = {0,0};
      const std::vector<int> cell11 = {1,1};
      const std::vector<int> cell22 = {2,2};
      if ( cell == cell00
           || cell == cell11
           || cell == cell22) {
        ++diag_cells_filled;
      }
    }
  }

  return COLUMNLENGTH == diag_cells_filled;
}

//------------------------------------------------------------------------------
bool isBottomLeftDiagonalFilled(const std::vector<std::vector<int>> & moves, Player player) {
  size_t diag_cells_filled = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if (isPlayerMove(player, i)) {
      const std::vector<int> & cell = moves.at(i);
      const std::vector<int> cell20 = {2,0};
      const std::vector<int> cell11 = {1,1};
      const std::vector<int> cell02 = {0,2};
      if ( cell == cell20
           || cell == cell11
           || cell == cell02 ) {
        ++diag_cells_filled;
      }
    }
  }
  return COLUMNLENGTH == diag_cells_filled;
}

//------------------------------------------------------------------------------
bool allBoardFilled(const std::vector<std::vector<int>> & moves) {
  return moves.size() == ROWLENGTH * COLUMNLENGTH;
}

//------------------------------------------------------------------------------
bool isWinner(const std::vector<std::vector<int>> & moves, Player player) {
  return isRowFilled(0, moves, player)
      || isRowFilled(1, moves, player)
      || isRowFilled(2, moves, player)
      || isColumnFilled(0, moves, player)
      || isColumnFilled(1, moves, player)
      || isColumnFilled(2, moves, player)
      || isTopLeftDiagonalFilled(moves, player)
      || isBottomLeftDiagonalFilled(moves, player);
}

//------------------------------------------------------------------------------
bool isWinnerA(const std::vector<std::vector<int>> & all_moves) {
  return isWinner(all_moves, Player::A);
}

//------------------------------------------------------------------------------
bool isWinnerB(const std::vector<std::vector<int>> & all_moves) {
  return isWinner(all_moves, Player::B);
}

//------------------------------------------------------------------------------
std::vector<std::vector<int>> ReadMovesFromVectorOfIntegers(const std::vector<std::vector<int>> & coordinates) {
  std::vector<std::vector<int>> moves;
  for (const std::vector<int> & xy : coordinates ) {
    moves.push_back(std::vector<int>(xy.at(0), xy.at(1)));
  }

  return moves;
}

//------------------------------------------------------------------------------
std::string checkBoard(const std::vector<std::vector<int>> & all_moves) {
  std::string answer;

  if (isWinnerA(all_moves)) {
    answer = "A";
  } else if (isWinnerB(all_moves)) {
    answer = "B";
  } else if (allBoardFilled(all_moves)) {
    answer =  "Draw";
  } else {
    answer = "Pending";
  }

  return answer;
}

//------------------------------------------------------------------------------
int main() {
  std::vector<std::vector<int>> moves;
  ReadAllMoves(std::cin, moves);
//  std::clog << moves.size() << " moves were made" << std::endl;
  std::cout << checkBoard(moves) << std::endl;
}
