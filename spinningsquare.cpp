// Im just a noob programer, but nothing can stop me coding ;]

#include <iostream>
#include <math.h>
#include <unistd.h>
#include <cstring>
using namespace std;

#define BOARDSIZE 60 // Kích thước đồ thị
char buffer[BOARDSIZE][BOARDSIZE * 2]; // Mảng 2 chiều biểu thị đồ thị để in ra màn hình console
int SIZE = BOARDSIZE / 2; // Kích thước hình vuông



int calcY(float t) {
	return sin(t) * SIZE;
	// Tính Y:
	// Gọi đường thẳng nối từ tâm O đồ thị đến một đỉnh của hình vuông là OA
	//     số đo góc tạo bởi OA và trục hoành là T
	// Khi có OA (có độ dài là SIZE) và góc T thì có thể dùng tỉ số lượng giác sau:
	//
	// sin(góc) = cạnh đối (chính là Y) / cạnh huyền (đường thẳng từ tâm đến đỉnh)
	//   	      
	// hay:
	// 	    
	// sin(T) = Y / OA
	//
	// => Y = sin(T) * OA
	// Giả sử góc T là 30 độ:
	// Thay T = 30, OA = SIZE vào biểu thức trên:
	// 	Y = sin(30) * (BOARDSIZE / 2)
	// 	Y = 0.5 * 30
	// 	Y = 15
	// Vậy Y = 15
}

int calcX(float t) {
	return cos(t) * SIZE;
	// Tính X:
	// Gọi đường thẳng nối từ tâm O đồ thị đến một đỉnh của hình vuông là OA
	//     số đo góc tạo bởi OA và trục hoành là T
	// Khi có OA (có độ dài là SIZE) và góc T thì có thể dùng tỉ số lượng giác sau:
	//			
	// cos(góc) = cạnh kề (chính là X) / cạnh huyền (đường thẳng từ tâm đến đỉnh)
	//   	      
	// hay:
	// 	    
	// cos(T) = X / OA
	// 
	// => X = cos(T) * OA
	// Giả sử góc T là 30 độ:
	// Thay T = 30, OA = SIZE vào biểu thức trên:
	// 	Y = cos(30) * (BOARDSIZE / 2)
	// 	    sqrt(3)
	// 	Y = -------  * 30
	// 	       3
	// 	Y ~ 25.98
	// Vậy Y ~ 25.98
}

struct point {
	float x;
	float y;
} no1, no2, no3, no4; // Tạo 4 đỉnh của hình vuông

void connPoint(float ax, float bx, float ay, float by) // Nối 2 điểm a b lại sử dụng DDA
{
	float longX = (float)(bx - ax); // Tính khoảng cách X 2 điểm
	float longY = (float)(by - ay); // Tính khoảng cách Y 2 điểm
	float steps = max(abs(longX), abs(longY)); // Tìm số bước
	float x_increase = longX / steps; // Tính các bậc thang X
	float y_increase = longY / steps; // Tính các bậc thang Y
	for (float i = 0; i <= steps; ++i) {
		int roundX = round(ax); // Làm tròn X tránh lỗi khi gán vào mảng buffer
		int roundY = round(ay); // Làm tròn Y tránh lỗi khi gán vào mảng buffer
		buffer[roundY][roundX] = '#';
		ax += x_increase; // Thêm 1 bậc thang cho X
		ay += y_increase; // Thêm 1 bậc thang cho Y
	}
}


void side() { // Nối các điểm lại
	connPoint(no1.x, no3.x, no1.y, no3.y); // Nối 1 - 3
	connPoint(no1.x, no4.x, no1.y, no4.y); // Nối 1 - 4
	connPoint(no3.x, no2.x, no3.y, no2.y); // Nối 3 - 2
	connPoint(no2.x, no4.x, no2.y, no4.y); // Nối 2 - 3
	// Nối đường chéo
	connPoint(no1.x, no2.x, no1.y, no2.y); // Nối 1 - 2
  	connPoint(no3.x, no4.x, no3.y, no4.y); // Nối 3 - 4
	return;
}

int main() {
	float turn = 0.0;
	while (true) {
		cout << "\033[2J\033[1;1H";
		memset(buffer, ' ', sizeof(buffer)); // Làm sạch mảng mỗi lần lặp với ký tự ' '
		
		// Tính vị trí x, y điểm 1
		no1.x = calcX(turn) + SIZE;
		no1.y = calcY(turn) + SIZE;
		no1.x *= 2;

		// Tính vị trí x, y điểm 2
		no2.x = SIZE - calcX(turn);
		no2.y = SIZE - calcY(turn);
		no2.x *= 2;

		// Tính vị trí x, y điểm 3
		no3.x = SIZE + calcX(turn + M_PI / 2); // M_PI là số PI, 1 PI = 90 độ, không biết tại sao lại vậy nhưng stackoverflow nói vậy thì kệ
		no3.y = calcY(turn + M_PI / 2) + SIZE;
		no3.x *= 2;

		// Tính vị trí x, y điểm 4
		no4.x = SIZE - calcX(turn + M_PI / 2);
		no4.y = SIZE - calcY(turn + M_PI / 2);
		no4.x *= 2;
		
		// Làm tròn để tránh lỗi khi gán # cho mảng buffer để hiển thị
		int rno1x = round(no1.x);
		int rno1y = round(no1.y);
		int rno2x = round(no2.x);
		int rno2y = round(no2.y);
		int rno3x = round(no3.x);
    		int rno3y = round(no3.y);
    		int rno4x = round(no4.x);
		int rno4y = round(no4.y);

		buffer[rno1y][rno1x] = '#';
		buffer[rno2y][rno2x] = '#';
		buffer[rno3y][rno3x] = '#';
		buffer[rno4y][rno4x] = '#';
		
		side(); // Nối các điểm lại
		
		// Cho hình vuông quay theo chiều kim đồng hồ
		turn += 0.01;
		if (turn >= M_PI)
			turn = 0.1;
		
		// In buffer
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE * 2; ++j) {
				cout << buffer[i][j];
			}
			cout << '\n';
		}

		cout << turn << '\n'; // In số góc hiện tại
		usleep(10000); // Delay xíu cho đừng quay nhanh quá
	}
}




// Vậy thôi ;]
