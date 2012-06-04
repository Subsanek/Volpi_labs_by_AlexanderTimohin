//GPL v 2/3
//LGPL

#include <stdio.h>

//упорядочить по возрастанию столбец матрицы , сумма элементов которого минимальна

//Размерность массива
const int N = 4; //Количество строк
const int M = 4; //Количество столбцов

int stolbnum(int mas[N][M]) {
	int stnum = 0; //Номер столбца, в котором сумма элементов минимальна
	int sum; //Сумма элементов в текущем столбце
	int i,j;
	int lastsum = 999999999;
	for(j = 0; j < M; j++) {
		sum = 0;
		for(i = 0; i < N; i++) {
			sum += mas[i][j];
		}
		if(sum < lastsum)
			 stnum = j;
		lastsum = sum;
	}
	return stnum;
}

void sortbyminsum(int mas[N][M], int stnum) {
	//Сортировка пузырьком по возрастанию
	printf("Номер столбца, где сумма минимальна: %d",stnum+1);
	int i,ii;
	int tmp;
	for(i = 0; i < N; i++)
		for(ii = 0; ii < N - i - 1; ii++)
			if(mas[ii][stnum] > mas[ii+1][stnum]) {
				tmp = mas[ii+1][stnum];
				mas[ii+1][stnum] = mas[ii][stnum];
				mas[ii][stnum] = tmp;
			}
	printf("\nСтолбец отсортирован по возрастанию");
}

void getmas(int mas[N][M]) {
	int i,j;
	for (i = 0; i < N; i++) {
		printf("Введите %d строку (%d чисел): ",i+1,M);
		for(j = 0; j < M; j++) {
			scanf("%d",&mas[i][j]);
		}
	}
}

void printmas(int mas[N][M]) {
	int i,ii;
	for (i = 0; i < N; i++) {
		printf("\n%d строка: ",i+1);
		for(ii = 0; ii < M; ii++) {
			printf(" %d ",mas[i][ii]);
		}
	}
}

int main() {
	int mas[N][M];
	getmas(mas);
	sortbyminsum(mas,stolbnum(mas));
	printmas(mas);
	return 0;
}
