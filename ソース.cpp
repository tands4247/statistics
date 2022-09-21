//　統計ver2

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void hyouji(double* p_array, int n, double heikinn);			//表示
void deviation(double* p_array, int n);					//平均、分散、標準偏差を算出
void seiretu(double* p_array, int n);					//昇順に並べ替え、最小値、最大値、中央値を算出
void mode(double* p_array, int n);						//最頻値を算出
void histgram(double* p_array, int n);					//ヒストグラムを表示

int main() {
	int n;

	//現在の時刻を種に乱数を生成
	srand((unsigned int)time(NULL));

	// 1～50個の乱数で要素数nを生成
	printf("1～50個の乱数で要素数を生成します\n");
	n = 1 + rand() % 50;
	printf("要素数は%dです\n", n);

	// n個分のメモリを動的確保
	double* p_array = (double*)malloc(n * sizeof(double));
	if (p_array == NULL)
		printf("メモリを確保できませんでした\n");

	//数字の入力
	printf("%d個の数字を1～100の乱数で生成します\n", n);
	for (int i = 0; i < n; i++) {
		p_array[i] = 1 + rand() % 100;
	}

	deviation(p_array, n);
	seiretu(p_array, n);
	mode(p_array, n);
	histgram(p_array, n);

	printf("\n\n");

	free(p_array);
}


//表示は少しこだわりました
void hyouji(double *p_array, int n, double heikinn) {
	//表示
	printf("\n\n\n");
	printf("要素 |    データ   |  平均値からの差  | (平均値からの差)^2\n");
	printf("--------------------------------------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("%4d | %10.2f  |    %10.2f    |  %10.2f", i + 1, p_array[i], (heikinn - p_array[i]), (heikinn - p_array[i]) * (heikinn - p_array[i]));
		printf("\n");
	}
	printf("\n\n");
}


void deviation(double* p_array, int n) {
	double sum = 0;
	double sum_t = 0;

	//平均の産出
	for (int i = 0; i < n; i++) {
		sum += p_array[i];
	}
	double heikinn = sum / n;

	//分散の算出
	for (int i = 0; i < n; i++) {
		sum_t += (heikinn - p_array[i]) * (heikinn - p_array[i]);
	}
	double bunnsann = sum_t / n;

	hyouji(p_array, n, heikinn);

	printf("平均 ＝ %.2f\n", heikinn);
	printf("分散 ＝ %.2f\n", bunnsann);
	printf("標準偏差 ＝ %.2f\n\n", sqrt(bunnsann));		//sqrt(bunnsann)で分散の平方根（標準偏差）を算出
}


void seiretu(double* p_array, int n) {
	//バブルソート
	printf("昇順にソート\n");
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p_array[i] > p_array[j]) {
				double tmp = p_array[i];
				p_array[i] = p_array[j];
				p_array[j] = tmp;
			}
		}
	}

	//ソート後表示
	for (int i = 0; i < n; i++) {
		printf("%.2f   ", p_array[i]);
	}
	printf("\n\n");

	printf("最小値 ＝ %.2f\n", p_array[0]);
	printf("最大値 ＝ %.2f\n", p_array[n - 1]);

	//要素数が奇数なら普通に中央値を算出
	if ((n % 2) == 1) {
		printf("中央値 ＝ %.2f\n", p_array[n / 2]);
	}
	//要素数が偶数なら中央値に当たる二つの数字の平均をとる
	else {
		printf("中央値 ＝ %.2f\n", (p_array[n / 2] + p_array[n / 2 - 1]) / 2);
	}
}


void mode(double* p_array, int n) {
	int count[100];

	//出現回数を0で初期化
	for (int i = 0; i < n; i++) {
		count[i] = 0;
	}

	//数字の出現回数をカウント
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p_array[i] == p_array[j]) {
				count[j]++;
			}
		}
	}

	//出現回数をもとに最頻値の添え字を算出
	int mode_num;
	int max_mode = 0;
	for (int i = 0; i < n; i++) {
		if (max_mode <= count[i]) {
			max_mode = count[i];
			mode_num = i;
		}
	}

	printf("最頻値 ＝ %.2f\n\n", p_array[mode_num]);
}


void histgram(double* p_array, int n) {
	int x[10] = { 0 };
	int v;

	for (int i = 0; i < n; i++) {
		v = p_array[i] / 10;
		switch (v) {
			case 0:	x[0]++;
				break;
			case 1:	x[1]++;
				break;
			case 2: x[2]++;
				break;
			case 3: x[3]++;
				break;
			case 4: x[4]++;
				break;
			case 5: x[5]++;
				break;
			case 6: x[6]++;
				break;
			case 7:	x[7]++;
				break;
			case 8: x[8]++;
				break;
			default :	x[9]++;
				break;
		}
	}

	printf("ヒストグラムを表示\n");
	for (int i = 0; i < 10; i++) {
		printf("%2d - %3d :", 10 * i + 1, 10 * (i + 1));
		for (int j = 0; j < x[i]; j++) {
			printf("□");
		}
		printf("\n");
	}
}

/*メモ
switch分の式はdouble型は使えない → double型は信頼性が低いからだそう
例　switch(p_array[i] / 10)　  ・・・(p_array はdouble*型)だと、うまくいかない
↓
int v = p_array[i] / 10;
switch(v)	
のようにswitchの中で評価しないで、変数で値を出して(int型に変換)からswitchで評価


p_array[i] と *(p_array + i)は同じ
*/
