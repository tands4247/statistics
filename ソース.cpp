//�@���vver2
/* ver1�Ƃ̈Ⴂ�͗v�f���ƃf�[�^�𗐐���p���Đ������邱�ƂƁA�z���v�f�����̃������𓮓I�Ɋm�ۂ��邱�ƁB*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void hyouji(double* p_array, int n, double heikinn);	//�\�����s���܂�
void deviation(double* p_array, int n);					//���ρA���U�A�W���΍����Z�o���܂�
void seiretu(double* p_array, int n);					//�����ɕ��בւ��A�ŏ��l�A�ő�l�A�����l���Z�o���܂�
void mode(double* p_array, int n);						//�ŕp�l���Z�o���܂�
void histgram(double* p_array, int n);					//�q�X�g�O������\��

int main() {
	int n;

	//���݂̎�������ɗ����𐶐�
	srand((unsigned int)time(NULL));

	// 1�`50�̗����ŗv�f��n�𐶐�
	printf("1�`50�̗����ŗv�f���𐶐����܂�\n");
	n = 1 + rand() % 50;
	printf("�v�f����%d�ł�\n", n);

	// n���̃������𓮓I�m��
	double* p_array = (double*)malloc(n * sizeof(double));
	if (p_array == NULL)
		printf("���������m�ۂł��܂���ł���\n");

	//�����̓���
	printf("%d�̐�����1�`100�̗����Ő������܂�\n", n);
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


//�\���͏����������܂���
void hyouji(double *p_array, int n, double heikinn) {
	//�\��
	printf("\n\n\n");
	printf("�v�f |    �f�[�^   |  ���ϒl����̍�  | (���ϒl����̍�)^2\n");
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

	//���ς̎Y�o
	for (int i = 0; i < n; i++) {
		sum += p_array[i];
	}
	double heikinn = sum / n;

	//���U�̎Z�o
	for (int i = 0; i < n; i++) {
		sum_t += (heikinn - p_array[i]) * (heikinn - p_array[i]);
	}
	double bunnsann = sum_t / n;

	hyouji(p_array, n, heikinn);

	printf("���� �� %.2f\n", heikinn);
	printf("���U �� %.2f\n", bunnsann);
	printf("�W���΍� �� %.2f\n\n", sqrt(bunnsann));		//sqrt(bunnsann)�ŕ��U�̕������i�W���΍��j���Z�o
}


void seiretu(double* p_array, int n) {
	//�o�u���\�[�g
	printf("�����Ƀ\�[�g\n");
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p_array[i] > p_array[j]) {
				double tmp = p_array[i];
				p_array[i] = p_array[j];
				p_array[j] = tmp;
			}
		}
	}

	//�\�[�g��\��
	for (int i = 0; i < n; i++) {
		printf("%.2f   ", p_array[i]);
	}
	printf("\n\n");

	printf("�ŏ��l �� %.2f\n", p_array[0]);
	printf("�ő�l �� %.2f\n", p_array[n - 1]);

	//�v�f������Ȃ畁�ʂɒ����l���Z�o
	if ((n % 2) == 1) {
		printf("�����l �� %.2f\n", p_array[n / 2]);
	}
	//�v�f���������Ȃ璆���l�ɓ������̐����̕��ς��Ƃ�
	else {
		printf("�����l �� %.2f\n", (p_array[n / 2] + p_array[n / 2 - 1]) / 2);
	}
}


void mode(double* p_array, int n) {
	int count[100];

	//�o���񐔂�0�ŏ�����
	for (int i = 0; i < n; i++) {
		count[i] = 0;
	}

	//�����̏o���񐔂��J�E���g
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p_array[i] == p_array[j]) {
				count[j]++;
			}
		}
	}

	//�o���񐔂����Ƃɍŕp�l�̓Y�������Z�o
	int mode_num;
	int max_mode = 0;
	for (int i = 0; i < n; i++) {
		if (max_mode <= count[i]) {
			max_mode = count[i];
			mode_num = i;
		}
	}

	printf("�ŕp�l �� %.2f\n\n", p_array[mode_num]);
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

	printf("�q�X�g�O������\��\n");
	for (int i = 0; i < 10; i++) {
		printf("%2d - %3d :", 10 * i + 1, 10 * (i + 1));
		for (int j = 0; j < x[i]; j++) {
			printf("��");
		}
		printf("\n");
	}
}

/*����
switch���̎���double�^�͎g���Ȃ� �� double�^�͐M�������Ⴂ���炾����
switch(p_array[i] / 10)�@���ƁA���܂������Ȃ�
��
int v = p_array[i] / 10;
switch(v)	
�̂悤��switch�̒��ŕ]�����Ȃ��ŁA�ϐ��Œl���o���Ă���switch�ŕ]��


p_array[i] �� *(p_array + i)�͓���
*/
