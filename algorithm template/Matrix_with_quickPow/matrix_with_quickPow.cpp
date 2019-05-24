// 线性代数中提到的矩阵乘法
// 矩阵乘法也有幂次方运算，矩阵快速幂可以快速算出矩阵的幂

#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1e2 + 5;

struct Matrix {
	int r, c;
	int a[maxn][maxn];

	Matrix(int r = 0, int c = 0) : r(r), c(c) {
		memset(a, 0, sizeof(a));
	}

	Matrix operator * (const int x) const { // 矩阵乘数
		Matrix tmp;
		tmp.r = r; tmp.c = c;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				tmp.a[i][j] = a[i][j] * x;
			}
		}
		return tmp;
	}

	Matrix operator * (const Matrix& rhs) const { // 矩阵乘法
		// c must equal rhs.r
		Matrix tmp;
		tmp.r = r; tmp.c = rhs.c;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < rhs.c; j++) {
				for (int k = 0; k < c; k++) {
					tmp.a[i][j] += a[i][k] * rhs.a[k][j];
				}
			}
		}
		return tmp;
	}

	Matrix operator + (const Matrix& rhs) const { // 矩阵加法
		Matrix tmp;
		tmp.r = r; tmp.c = c;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				tmp.a[i][j] = a[i][j] + rhs.a[i][j];
			}
		}
		return tmp;
	}

	Matrix operator - (const Matrix& rhs) const { // 矩阵减法
		Matrix tmp;
		tmp.r = r; tmp.c = c;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				tmp.a[i][j] = a[i][j] - rhs.a[i][j];
			}
		}
		return tmp;
	}
};

// 计算 x 的 y 次方，x 为矩阵
Matrix quickPow(Matrix x, int y) {
	if (y == 1) return x;
	Matrix tmp;
	tmp = quickPow(x, y / 2);
	tmp = tmp * tmp;
	if (y & 1) tmp = tmp * x;
	return tmp;
}

Matrix e; // 单位阵及其初始化
void initE(Matrix E, int r, int c) {
	E.r = r; E.c = c;
	for (int i = 0; i < r; i++) E.a[i][i] = 1;
}

bool checkTimes(Matrix a, Matrix b) { // 检查矩阵乘法可能性
	return a.c == b.r;
}

bool checkAdd(Matrix a, Matrix b) { // 检查矩阵加法可能性
	return a.r == b.r && a.c == b.c;
}

void MatrixRead(Matrix& x) { // 矩阵的读入
	scanf("%d%d", &x.r, &x.c);
	for (int i = 0; i < x.r; i++) {
		for (int j = 0; j < x.c; j++) {
			scanf("%d", &x.a[i][j]);
		}
	}
}

void MatrixPrint(Matrix x) { // 矩阵的输出
	for (int i = 0; i < x.r; i++) {
		for (int j = 0; j < x.c; j++) {
			printf("%d", x.a[i][j]);
			if (j == x.c - 1) printf("\n");
			else printf(" ");
		}
	}
}

int main() {
	Matrix a, b;
	MatrixRead(a);
	MatrixRead(b);
	
	puts("There is (a+b)^5");
	Matrix ans = quickPow(a + b, 5);
	MatrixPrint(ans);
	puts("There is a * b");
	MatrixPrint(a * b);
	puts("There is a * 3");
	MatrixPrint(a * 3);
	puts("There is a + b");
	MatrixPrint(a + b);
	puts("There is a - b");
	MatrixPrint(a - b);
	return 0;
}