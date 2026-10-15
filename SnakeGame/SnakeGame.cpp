#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <Windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score = 0;
int tailX[width * height], tailY[width * height];
int nTail = 0;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void HideCursor() {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void SpawnFruit() {
	if (nTail >= width * height - 1) {
		gameOver = true;
		return;
	}
	bool valid;
	do {
		valid = true;
		fruitX = rand() % width;
		fruitY = rand() % height;
		if (fruitX == x && fruitY == y) {
			valid = false;
		}
		for (int k = 0; k < nTail; k++) {
			if (tailX[k] == fruitX && tailY[k] == fruitY) {
				valid = false;
				break;
			}
		}
	} while (!valid);
}

void Setup() {
	srand((unsigned)time(0));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	score = 0;
	SpawnFruit();
}

void Draw() {
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) {
				cout << "#";
			}

			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
						break;
					}
				}
				if (!print) {
					cout << " ";
				}
			}

			if (j == width - 1) {
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic() {
	if (nTail > 0) {
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;

		tailX[0] = x;
		tailY[0] = y;

		for (int i = 1; i < nTail; i++) {
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
	}

	switch (dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}

	if (x >= width || x < 0 || y >= height || y < 0) {
		gameOver = true;
		return;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
			return;
		}
	}
	if (x == fruitX && y == fruitY) {
		nTail++;
		score += 10;
		SpawnFruit();
	}
}

int main() {
	HideCursor();
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(100);
	}

	COORD pos = { 0, (SHORT)(height + 4) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "Game Over! Final score: " << score << endl;
	cout << "Press any key to exit..." << endl;
	while (_kbhit()) _getch();
	_getch();
}