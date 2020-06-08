МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе №4 <br/> по дисциплине "Программирование"
<br/>
​
студента 1 курса группы ИВТ-б-о-192(2)<br/>
Бородаев Виталий Олегович<br/>
направления подготовки 09.03.01 "Информатика и Вычислительная Техника"
<br/>
​
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)<br/></td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>
<p align="center">Симферополь, 2020</p>
<hr>

**Цель:**
1. Закрепить навыки работы с перечислениями;
2. Закрепить навыки работы с структурами;
3. Освоить методы составления многофайловых программ.

**Ход работы:**
Создайть три файла:
1. Файл реализующий игру «Иксики-нолики» используя функции описанные в вспомогательном файле;
2. Вспомогательный файл. Содержит реализацию основных функций игры;
3. Заголовочный файл. Нужен для связи главного и вспомогательного файлов. 
 <br>

Итак, перейдем к выполнению заданий.
1. Главный файл содержащий функцию main(), main.cpp:
```cpp

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

```
<br>

2. Вспомогательный файл содржащий реализацию основных функция supporting.cpp:

```cpp
#include <iostream>
#include "supporting.h"
#include <time.h> 
using namespace std;
Game game;
Game initGame(char userChar) {
	int first = rand() % 2;
	char botChar;
	if (userChar == 'X') botChar = 'O';
	else botChar = 'X';
	game.userChar = userChar;
	game.botChar = botChar;
	if (first == 1) game.isUserTurn = true;
	else game.isUserTurn = false;
	game.status = PLAY;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			game.bord[i][j] = ' ';
		}
	}
	return game;
};

void updateDisplay(const Game game) {
	system("cls");
	cout << " ________________ " << endl;
	cout << "|      0   1   2 |" << endl;
	cout << "| 0 " << " | " << game.bord[0][0] << " | " << game.bord[0][1] << " | " << game.bord[0][2] << " | " << endl;
	cout << "|----------------|" << endl;
	cout << "| 1 " << " | " << game.bord[1][0] << " | " << game.bord[1][1] << " | " << game.bord[1][2] << " | " << endl;
	cout << "|----------------|" << endl;
	cout << "| 2 " << " | " << game.bord[2][0] << " | " << game.bord[2][1] << " | " << game.bord[2][2] << " | " << endl;
	cout << "|________________|" << endl;
};

void botTurn(Game* game) {
	bool empty_box = true;
	int number_user_char;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((game->bord[i][j] == game->userChar) || (game->bord[i][j] == game->botChar)) {
				empty_box = false;
			}
		}
	}
	if (empty_box) {
		game->bord[1][1] = game->botChar; game->isUserTurn = true;
	}
	else {
		for (int i = 0; i < 3; i++) {
			number_user_char = 0;
			if (game->bord[i][0] == game->userChar) {
				number_user_char++;
			}
			if (game->bord[i][1] == game->userChar) {
				number_user_char++;
			}
			if (game->bord[i][2] == game->userChar) {
				number_user_char++;
			}
			if (number_user_char > 1) {
				for (int j = 0; j < 3; j++) {
					if (game->bord[i][j] != game->userChar && game->bord[i][j] != game->botChar) {
						game->bord[i][j] = game->botChar; game->isUserTurn = true;
					}
				}
				break;
			}
		}
		if (game->isUserTurn == false) {
			for (int j = 0; j < 3; j++) {
				number_user_char = 0;
				if (game->bord[0][j] == game->userChar) {
					number_user_char++;
				}
				if (game->bord[1][j] == game->userChar) {
					number_user_char++;
				}
				if (game->bord[2][j] == game->userChar) {
					number_user_char++;
				}
				if (number_user_char > 1) {
					for (int i = 0; i < 3; i++) {
						if ((game->bord[i][j] != game->userChar) && (game->bord[i][j] != game->botChar)) {
							game->bord[i][j] = game->botChar; game->isUserTurn = true;
						}
					}
					break;
				}
			}
		}
		if (game->isUserTurn == false) {//диагональ\

			number_user_char = 0;
			for (int i = 0; i < 3; i++) {
				if (game->bord[i][i] == game->userChar) {
					number_user_char++;
				}
			}
			if (number_user_char > 1) {
				for (int i = 0; i < 3; i++) {
					if (game->bord[i][i] != game->userChar && game->bord[i][i] != game->botChar) {
						game->bord[i][i] = game->botChar;
						game->isUserTurn = true;

					}
				}
			}
		}
		if (game->isUserTurn == false) {//диагонал /
			number_user_char = 0;
			if (game->bord[0][2] == game->userChar) {
				number_user_char++;
			}
			if (game->bord[1][1] == game->userChar) {
				number_user_char++;
			}
			if (game->bord[2][0] == game->userChar) {
				number_user_char++;
			}
			if (number_user_char > 1) {
				if ((game->bord[0][2] != game->userChar) && (game->bord[0][2] != game->botChar) && (game->isUserTurn == false)) {
					game->bord[0][2] = game->botChar; game->isUserTurn = true;
				}
				if ((game->bord[1][1] != game->userChar) && (game->bord[1][1] != game->botChar) && (game->isUserTurn == false)) {
					game->bord[1][1] = game->botChar; game->isUserTurn = true;
				}
				if ((game->bord[2][0] != game->userChar) && (game->bord[2][0] != game->botChar) && (game->isUserTurn == false)) {
					game->bord[2][0] = game->botChar; game->isUserTurn = true;
				}
			}
		}
		if (game->isUserTurn == false) {//рандомный 
			while (true) {
				int i = rand() % 3;
				int j = rand() % 3;
				if ((game->bord[i][j] != game->userChar) && (game->bord[i][j] != game->botChar)) {
					game->bord[i][j] = game->botChar; game->isUserTurn = true; break;
				}
			}

		}

	}

};

void userTurn(Game* game) {
	int i, j;
	while (true) {
		setlocale(LC_ALL, "rus");
		cout << "[строка] "; cin >> i;
		cout << "[столбец] "; cin >> j;
		cout << "\n";
		if ((i >= 0) && (i <= 2) && (j >= 0) && (j <= 2)) {
			if ((game->bord[i][j] != game->userChar) && (game->bord[i][j] != game->botChar)) {
				game->bord[i][j] = game->userChar; game->isUserTurn = false; break;
			}
			else cout << "Неправильный ход " << endl;
		}
		else cout << "Неправильный ход " << endl;
	}
};

bool updateGame(Game* game) {
	bool end = true;
	char Xor0;
	int win;
	if (!game->isUserTurn) Xor0 = game->userChar;
	else Xor0 = game->botChar;
	for (int i = 0; i < 3; i++) {
		win = 0;
		for (int j = 0; j < 3; j++) {
			if (game->bord[i][j] == Xor0) win++;
		}
		if (win == 3) {
			if (!game->isUserTurn) game->status = USER_WIN;
			else game->status = BOT_WIN;
			return end;
		}
	}
	for (int j = 0; j < 3; j++) {
		win = 0;
		for (int i = 0; i < 3; i++) {
			if (game->bord[i][j] == Xor0) win++;
		}
		if (win == 3) {
			if (!game->isUserTurn) game->status = USER_WIN;
			else game->status = BOT_WIN;
			return end;
		}
	}
	win = 0;
	if (game->bord[0][0] == Xor0) {
		win++;
	}
	if (game->bord[1][1] == Xor0) {
		win++;
	}
	if (game->bord[2][2] == Xor0) {
		win++;
	}
	if (win == 3) {
		if (!game->isUserTurn) game->status = USER_WIN;
		else game->status = BOT_WIN; return end;
	}
	win = 0;
	if (game->bord[2][0] == Xor0)  win++;
	if (game->bord[1][1] == Xor0)  win++;
	if (game->bord[0][2] == Xor0)  win++;
	if (win == 3) {
		if (!game->isUserTurn) game->status = USER_WIN;
		else game->status = BOT_WIN; return end;
	}
	win = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((game->bord[i][j] != game->userChar) && (game->bord[i][j] != game->botChar)) {
				win++;
			}
		}
	}
	if (!win) {
		game->status = NOT_WIN;
		return end;
	}
	else end = false;
	return end;
};

```   

3. И наконец заголовочный файл, (для защиты от повторного включения файла использую макрос ```#pragma once```):
```cpp
#pragma once 
enum Status {
	PLAY,         
	USER_WIN,      
	BOT_WIN,       
	NOT_WIN

};
struct Game {

	char bord[3][3];
	bool isUserTurn; 
	char userChar;    
	char botChar;     
	Status status;
};

Game initGame(char userChar);

void updateDisplay(const Game game);

void botTurn(Game* game);

void userTurn(Game* game);

bool updateGame(Game* game);

```
4. А вот и сам результат кода:
<center>
<img src="resources\images\1.PNG"><br/>
Рис. 1. Игра крестики-нолики</center>

**Вывод:** Таким образом все цели и задачи лабораторной работы были выполнены в полном объеме. Были получены навыки работы с перечислениями, структурами. Освоил методы составления многофайловых программ.