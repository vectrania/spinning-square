#include <iostream>
#include <math.h>
#include <unistd.h>
using namespace std;

#define BOARDSIZE 40
char board[BOARDSIZE][BOARDSIZE * 2];
int SIZE = BOARDSIZE / 2;

int calcY(float a) {
	return sin(a) * SIZE;
}

int calcX(float a) {
	return cos(a) * SIZE;
}

struct point {
	float x;
	float y;
} no1, no2, no3, no4;

void connPoint(float ax, float bx, float ay, float by)
  {
	  float longX = (float)(bx - ax);
	  float longY = (float)(by - ay);
	  float x = ax, y = ay;
	  float steps = max(abs(longX), abs(longY));
	  float x_increase = longX / steps;
	  float y_increase = longY / steps;
	  for (float i = 0; i <= steps; ++i) {
	    int roundX = round(x);
	  	int roundY = round(y);
      if (roundX >= 0 && roundX < BOARDSIZE * 2 && roundY >= 0 && roundY < BOARDSIZE)
	  		board[roundY][roundX] = '#';
	  	x += x_increase;
	  	y += y_increase;
	  }
  }


void side() {
  connPoint(no1.x, no3.x, no1.y, no3.y);
  connPoint(no1.x, no4.x, no1.y, no4.y);
  connPoint(no3.x, no2.x, no3.y, no2.y);
  connPoint(no2.x, no4.x, no2.y, no4.y);
	return;
}

int main() {
	float turn = 0.0;
	while (true) {
		cout << "\033[2J\033[1;1H";
		for (int i = 0; i < BOARDSIZE; ++i) {
			for (int j = 0; j < BOARDSIZE * 2; ++j) {
				board[i][j] = ' ';
			}
		}
		// board[SIZE][BOARDSIZE] = '@';
		no1.x = calcX(turn) + SIZE;
		no1.y = calcY(turn) + SIZE;
		no1.x *= 2;

		no2.x = SIZE - calcX(turn);
		no2.y = SIZE - calcY(turn);
		no2.x *= 2;

		no3.x = SIZE + calcX(turn + M_PI / 2);
		no3.y = calcY(turn + M_PI / 2) + SIZE;
		no3.x *= 2;

		no4.x = SIZE - calcX(turn + M_PI / 2);
		no4.y = SIZE - calcY(turn + M_PI / 2);
		no4.x *= 2;
    
    int rno1x = round(no1.x);
    int rno1y = round(no1.y);
    int rno2x = round(no2.x);
    int rno2y = round(no2.y);
    int rno3x = round(no3.x);
    int rno3y = round(no3.y);
    int rno4x = round(no4.x);
    int rno4y = round(no4.y);

		board[rno1y][rno1x] = '#';
		board[rno2y][rno2x] = '#';
		board[rno3y][rno3x] = '#';
		board[rno4y][rno4x] = '#';
		
		side();

		turn -= 0.01;
		if (turn <= 0.0)
			turn = 90;
		if (turn > 90)
			turn = 0.1;
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE * 2; ++j) {
				cout << board[i][j];
			}
			cout << '\n';
		}
		usleep(10000);
	}
}
