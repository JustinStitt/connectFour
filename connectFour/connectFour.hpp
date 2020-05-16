#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using matrix = vector<vector<int>>;
using coord = pair<int, int>;//x,y
/*
	connect four dimensions
	6 rows 7 cols (6x7)
*/
const size_t ROWS = 6;
const size_t COLS = 7;

class connectFour
{
private:
	matrix board;
	void gen_board(matrix& _board);

	int left_count(const matrix& _board, coord move, int pn);
	int right_count(const matrix& _board, coord move, int pn);

public:
	connectFour();
	void print_board(matrix& _board);
	void print_board() { print_board(this->board); }
	coord drop_piece(matrix& _board,int player_num, int col);
	coord drop_piece(int _player_num, int col)
	{
		coord move = drop_piece(this->board, _player_num, col);
		if (move.first == -1)
			return coord(-1, -1);
		return move;
	}
	bool check_for_win(matrix& _board, coord move);

	bool check_for_win(coord move)
	{
		return check_for_win(this->board, move);
	}
};

connectFour::connectFour()
{
	gen_board(this->board);	
}

void connectFour::gen_board(matrix& _board)
{
	_board.clear();
	for (int r{}; r < ROWS; ++r)
	{
		_board.push_back({});
		for (int c{}; c < COLS; ++c)
		{
			_board[r].push_back(0);
		}
	}
}

coord connectFour::drop_piece(matrix& _board, int player_num, int col)
{
	for (int x = ROWS - 1; x >= 0; --x)
	{
		if (_board[x][col] == 0)//valid move
		{
			_board[x][col] = player_num;
			return coord(x, col);
		}
	}
	cout << "Invalid Move" << endl;
	return coord(-1,-1);//invalid move
}


//recursive helpers for check_for_win

int connectFour::left_count(const matrix& _board, coord move, int _player_num)
{
	if (move.second < 0 || _board[move.first][move.second] != _player_num)
		return 0;
	int _left = move.second - 1;

	return 1 + left_count(_board, coord(move.first, _left), _player_num);
}

int connectFour::right_count(const matrix& _board, coord move, int _player_num)
{
	if ( move.second > COLS - 1 || _board[move.first][move.second] != _player_num)
		return 0;
	int _right = move.second + 1;

	return 1 + right_count(_board, coord(move.first, _right), _player_num);
}

//end recursive helpers


bool connectFour::check_for_win(matrix& _board, coord move)
{
	/*
		check the move to see if it validated a win condition
	*/
	//we never have to check above our move, because it is impossible for the most recent move to have a piece above it
	
	int move_height = ROWS - move.first;
	int _player_num = _board[move.first][move.second];
	/*
		for vertical behaviour check 3 pieces below move
	*/
	if (move_height >= 4)
	{
		int count = 0;
		for (int x = move.first; x < ROWS; ++x)
		{
			if (_board[x][move.second] == _player_num)
				++count;
		}
		if (count >= 4)
			return true;
	}
	/*
		for horizontal behaviour check left_count and right_count, if >= 4 then valid win
	*/
	coord left_start(move.first, move.second - 1);
	coord right_start(move.first, move.second + 1);
	int count = left_count(_board, left_start, _player_num) + right_count(_board, right_start, _player_num);
	if(count >= 3 )
		return true;
	
	/*
		for diagnol behaviour check check top-left to bottom-right
		then check top-right to bottom-left
	*/
	//TL to BR
	for (int x{}; x < ROWS - 3; ++x)
	{
		for (int y{}; y < COLS - 3; ++y)
		{
			if (_board[x][y] == _player_num &&
				_board[x + 1][y + 1] == _player_num &&
				_board[x + 2][y + 2] == _player_num &&
				_board[x + 3][y + 3] == _player_num)
				return true;
		}
	}
	//TR to BL
	for (int x{}; x < ROWS - 3; ++x)
	{
		for (int y = COLS - 1; y > 3; --y)
		{
			if (_board[x][y] == _player_num &&
				_board[x + 1][y - 1] == _player_num &&
				_board[x + 2][y - 2] == _player_num &&
				_board[x + 3][y - 3] == _player_num)
				return true;
		}
	}
	return false;
}


void connectFour::print_board(matrix& _board)
{
	for (const vector<int>& row : _board)
	{
		for (const int& val : row)
		{
			cout << "  " << val;
		}
		cout << endl;
	}
}