#include <algorithm>
#include <iostream>
#include <vector>

static const size_t ROWLENGTH = 3;
static const size_t COLUMNLENGTH = 3;

enum class Player {
  A, B
};

struct Move {
  Move(size_t row, size_t column)
    : row(row),
      column(column)
  {}

  size_t row = 0;
  size_t column = 0;
};

//------------------------------------------------------------------------------
bool operator ==(const Move & lhs, const Move rhs) {
  return lhs.row == rhs.row
      && lhs.column == rhs.column;
}

//------------------------------------------------------------------------------
std::istream & ReadMove(std::istream & is, Move & move) {
  char bracket, comma;
  is >> bracket >> move.row >> comma >> move.column >> bracket;

  return is;
}

//------------------------------------------------------------------------------
std::istream & ReadAllMoves(std::istream & is, std::vector<Move> & moves) {
  char bracket, comma;
  std::cin >> bracket;
  do {
    Move move(0,0);
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
bool isRowFilled(size_t rownum, const std::vector<Move> & moves,
                 Player player) {
  size_t row_items_count = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if ( isPlayerMove(player, i)
         && moves.at(i).row == rownum ) {
        ++row_items_count;
    }
  }

  return row_items_count == ROWLENGTH;
}

//------------------------------------------------------------------------------
bool isColumnFilled(size_t colnum, const std::vector<Move> & moves,
                    Player player) {
  size_t column_items_count = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if (isPlayerMove(player, i)
        && moves.at(i).column == colnum) {
      ++column_items_count;
    }
  }

  return column_items_count == COLUMNLENGTH;
}

//------------------------------------------------------------------------------
bool isTopLeftDiagonalFilled(const std::vector<Move> & moves, Player player) {
  size_t diag_cells_filled = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if (isPlayerMove(player, i)) {
      const Move & cell = moves.at(i);
      if ( cell == Move(0,0)
           || cell == Move(1,1)
           || cell == Move(2,2)) {
        ++diag_cells_filled;
      }
    }
  }

  return COLUMNLENGTH == diag_cells_filled;
}

//------------------------------------------------------------------------------
bool isBottomLeftDiagonalFilled(const std::vector<Move> & moves, Player player) {
  size_t diag_cells_filled = 0;
  for (size_t i = 0; i < moves.size(); ++i) {
    if (isPlayerMove(player, i)) {
      const Move & cell = moves.at(i);
      if ( cell == Move(2,0)
           || cell == Move(1,1)
           || cell == Move(0,2) ) {
        ++diag_cells_filled;
      }
    }
  }
  return COLUMNLENGTH == diag_cells_filled;
}

//------------------------------------------------------------------------------
bool allBoardFilled(const std::vector<Move> & moves) {
  return moves.size() == ROWLENGTH * COLUMNLENGTH;
}

//------------------------------------------------------------------------------
bool isWinner(const std::vector<Move> & moves, Player player) {
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
bool isWinnerA(const std::vector<Move> & all_moves) {
  return isWinner(all_moves, Player::A);
}

//------------------------------------------------------------------------------
bool isWinnerB(const std::vector<Move> & all_moves) {
  return isWinner(all_moves, Player::B);
}

//------------------------------------------------------------------------------
std::vector<Move> ReadMovesFromVectorOfIntegers(const std::vector<std::vector<int>> & coordinates) {
  std::vector<Move> moves;
  for (const std::vector<int> & xy : coordinates ) {
    moves.push_back(Move(xy.at(0), xy.at(1)));
  }

  return moves;
}

//------------------------------------------------------------------------------
std::string checkBoard(const std::vector<Move> & all_moves) {
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
  std::vector<Move> moves;
  ReadAllMoves(std::cin, moves);
//  std::clog << moves.size() << " moves were made" << std::endl;
  std::cout << checkBoard(moves) << std::endl;
}
