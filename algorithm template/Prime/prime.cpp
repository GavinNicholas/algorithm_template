#include <cstring>
#include <cmath>
using namespace std;

// 素数筛选朴素算法，时间复杂度：O(n*n)
// 素数筛选（判断 < maxn 的数是否是素数
const int maxn = 1e6 + 5;
bool notPrime[maxn];
void init() {
	memset(notPrime, false, sizeof(notPrime));
	notPrime[0] = notPrime[1] = true;
	for (int i = 2; i < maxn; i++) {
		bool flag = false;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				flag = true;
				break;
			}
		}
		if (flag) notPrime[i] = true;
	}
}

// 素数筛选朴素算法，时间复杂度：O(n*sqrt(n))，比上方略快
// 素数筛选（判断 < maxn 的数是否是素数
const int maxn = 1e6 + 5;
bool notPrime[maxn];
void init() {
	memset(notPrime, false, sizeof(notPrime));
	notPrime[0] = notPrime[1] = true;
	for (int i = 2; i < maxn; i++) {
		bool flag = false;
		for (int j = 2; j < sqrt(i); j++) {
			if (i % j == 0) {
				flag = true;
				break;
			}
		}
		if (flag) notPrime[i] = true;
	}
}

// 埃氏筛法，时间复杂度：O(n*logn)
// 素数筛选（判断 < maxn 的数是否是素数
const int maxn = 1e6 + 5;
bool notPrime[maxn];  
void Prime(){
	memset(notPrime, false, sizeof(notPrime));
	notPrime[0] = notPrime[1] = true;
	for (int i = 2; i <= maxn; i++) {
		if (!notPrime[i]) {
			for (int j = i*i; j <= maxn; j += i) { 
				notPrime[j] = true;
			}
		}
	}
}

// 欧拉筛：线性筛，时间复杂度：O(n)
// 素数筛选（判断 < maxn 的数是否是素数
const int maxn = 1e6 + 5;
bool notPrime[maxn];
void init() {
	memset(notPrime, false, sizeof(notPrime));
	notPrime[0] = notPrime[1] = true;
	for (int i = 2; i < maxn; i++) {
		if (!notPrime[i]) {
			if (i > maxn / i) continue;
			// 直接从 i*i 开始就可以，小于 i 倍的数之前已经都筛选过了，每次向下前进 i
			for (int j = i * i; j < maxn; j += i) notPrime[j] = true;
		}
	}
}

// 欧拉筛：线性筛，时间复杂度：O(n)
// 素数筛选（筛选除小于等于 maxn 的所有素数
// prime[0] 存的是当前已找到的素数的个数
int prime[maxn];
void getPrime() {
	memset(prime, 0, sizeof(prime));
	// for (int i = 0; i < maxn; i++) prime[i] = 0;
	for (int i = 2; i <= maxn; i++) {
		if (!prime[i]) prime[++prime[0]] = i;
		for (int j = 1; j <= prime[0] && prime[j] <= maxn / i; j++) {
			prime[prime[j] * i] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}