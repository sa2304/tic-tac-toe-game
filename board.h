#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

static const size_t ROWLENGTH = 3;
static const size_t COLUMNLENGTH = 3;

struct Board {
  struct Move {
    Move(size_t row, size_t column)
      : row(row),
        column(column)
    {}

    size_t row = 0;
    size_t column = 0;
  };


  struct Cell {
    enum class State {
      Open = 0,
      X,
      O
    } state = State::Open;
  };

  Cell::State otherPlayer(Cell::State player);

  Cell::State getCellState(size_t row, size_t column);

  void setCellState(size_t row, size_t column, Cell::State state);

  bool isRowFilled(size_t row, Cell::State player);

  bool isColumnFilled(size_t column, Cell::State player);

  bool isTopLeftDiagonalFilled(Cell::State player);

  bool isBottomLeftDiagonalFilled(Cell::State player);

  bool isWinner(Cell::State player);

  bool isWinnerX();

  bool isWinnerO();

  std::vector<Cell> possibleMoves();

  enum class GameState {
    Pending = 0,
    winX,
    winO,
    Draw
  };

  GameState checkGameState();

  static Board Create(const std::vector<Move> & moves);


  std::vector<Cell> cells = std::vector<Cell>(9);
};


std::ostream & operator<<(std::ostream & os, const Board & board);


#endif // BOARD_H