#include <iostream>
#include <vector>
#include <string>
#include "connectFour.hpp"

using namespace std;

int current_turn = 1;//1, 2

int main()
{
	connectFour game;
	bool over = false;
	int col;
	coord last_move(-1, -1);
	do {
		cout << "Player {" << current_turn << "}'s turn..." << endl;
		game.print_board();
		cout << "Enter Column to place piece: ";

		cin >> col;

		do 
		{
			last_move = game.drop_piece(current_turn, col);
			if (last_move.first == -1)
			{
				cout << "Invalid move, try a different column: ";
				cin >> col;
			}
		} while (last_move.first == -1);

		over = game.check_for_win(last_move);
		if (!over)
		{
			current_turn = (current_turn == 1 ? 2 : 1);
		}
		system("CLS");//clears console for VS++

	} while (!over);
	cin.ignore();
	cout << "Winner: Player{" << current_turn << "}!" << endl;
	game.print_board();
	cin.get();
	return 0;
}