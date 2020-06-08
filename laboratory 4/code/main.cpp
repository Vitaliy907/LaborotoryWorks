#include <iostream>
#include <time.h>
#include "supporting.h" 
using namespace std;
int main() {
	int lot;
	Game game;

	setlocale(LC_ALL, "rus");
	char userChar;
	cout << "ВВедите предпочетаемый вами символ (X или 0) ";
	cin >> userChar;

	game = initGame(userChar);

		while (!updateGame(&game)) {
			if (game.isUserTurn) {
				userTurn(&game);
			}
			else {
				botTurn(&game);
			}
			updateDisplay(game);
		}

	switch (game.status) {
	case USER_WIN: cout << "Вы победили"; break;
	case BOT_WIN: cout << "Bы проиграли"; break;
	case NOT_WIN: cout << "Ничья"; break;
	}
	return 0;
}