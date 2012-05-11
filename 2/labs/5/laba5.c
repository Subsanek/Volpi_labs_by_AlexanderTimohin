//GPL v 2/3

#include <stdio.h>

//Вариант №12. Подсчитать сумму цифр в десятичной записи заданного числа

int sum = 0; //Сумма цифр в десятичной записи

int digsum(int user, int i) {
	int a; //Цифра из числа
	a = (user/i)%10;
	sum += a;
	i *= 10;
	if((user/i) < 1 )
		return sum;
	digsum(user,i);
}

int main() {
	int user; //Число, введённое пользователем
	printf("Программа подсчитывает сумму цифр в десятичной записи заданного числа\n");
	printf("Введите число: ");
	scanf("%d",&user);
	printf("\n Сумма: %d", digsum(user,1));
	return 0;
}
