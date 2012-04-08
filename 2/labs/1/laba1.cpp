//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

//Лабораторная работа №1 (Структуры) Вариант № 6
/* Описать структуру с именем NOTE содержащую следующие поля:
Фамилия, имя;
Номер телефона;
Дата рождения (массив из трёх чисел).
Написать программу, выполняющую следующие действия:
Ввод с клавиатуры данных в массив, состоящий из 8 структур типа NOTE, записи должны быть упорядочены по датам рождения;
Вывод информации о тех людях, чьи дни рождения приходятся на месяц, значение которого введено с клавиатуры.
Если таких нет, вывести соответствующие сообщение. */

int main() {
	const int N = 8; //Количество описываемых людей
	int i,j,jj;
	int ii = 0; //Количество найденных по людей по заданному месяцу
	int usermonth = 0; //Номер месяца рождения, заданный пользователем
	struct note {
		char first_name[100], last_name[100], phone[20]; //Имя, фамилия, телефон
		int birthday[3]; //[0] - день, [1] - месяц, [2] - год
	};
	
	note peoples[N];
	
	note tmp; //Промежуточная структура (для сортировки)
	
	for(i = 0; i < N; i++) {
		peoples[i].first_name[0] = '\0';
		peoples[i].last_name[0] = '\0';
		peoples[i].phone[0] = '\0';
		peoples[i].birthday[0] = 0;
		peoples[i].birthday[1] = 0;
		peoples[i].birthday[2] = 0;
	}
	for(i = 0; i < N; i++) {
		cout<<"Введите информацию о "<<i+1<<" человеке"<<endl;
		
		printf("Введите Имя: \n");
		cin>>peoples[i].first_name;
		printf("Введите Фамилию: \n");
		cin>>peoples[i].last_name;
		printf("Введите номер телефона: \n");
		cin>>peoples[i].phone;
		printf("Введите день рождения: \n");
		scanf("%d",&peoples[i].birthday[0]);
		printf("Введите номер месяца рождения: \n");
		scanf("%d",&peoples[i].birthday[1]);
		printf("Введите год рождения: \n");
		scanf("%d",&peoples[i].birthday[2]);
	}
	
	for(i = 0; i < N; i++) {
		cout<<peoples[i].first_name<<"\t"<<peoples[i].last_name<<"\t"<<peoples[i].phone<<"\t"<<peoples[i].birthday[0]<<"\t"<<peoples[i].birthday[1]<<"\t"<<peoples[i].birthday[2]<<endl;
	}
	
	/*for(i = 0; i < N+1; i++)
		for(j = 0; j < i; j++) {
			if( (peoples[j].birthday[2] > peoples[j+1].birthday[2] && peoples[j].birthday[2] != peoples[j+1].birthday[2]) || (peoples[j].birthday[2] == peoples[j+1].birthday[2] && peoples[j].birthday[1] > peoples[j+1].birthday[1]) || (peoples[j].birthday[2] == peoples[j+1].birthday[2] && peoples[j].birthday[1] == peoples[j+1].birthday[1] && peoples[j].birthday[0] > peoples[j+1].birthday[0] ) ) {
				tmp = peoples[j+1];
				peoples[j+1] = peoples[j];
				peoples[j] = tmp;
			}
		}*/
	
	for(jj = 0; jj < 3; jj++)
		for(i = 0; i < N; i++)
			for(j = 0; j < i; j++)
				if(peoples[j].birthday[jj] > peoples[j+1].birthday[jj]) {
					tmp = peoples[j+1];
					peoples[j+1] = peoples[j];
					peoples[j] = tmp;
				}
	
	printf("\nДанные отсортированы по возрастанию даты рождения: \nРезультат: \n");
	for(i = 0; i < N; i++) {
		cout<<peoples[i].first_name<<"\t"<<peoples[i].last_name<<"\t"<<peoples[i].phone<<"\t"<<peoples[i].birthday[0]<<"\t"<<peoples[i].birthday[1]<<"\t"<<peoples[i].birthday[2]<<endl;
	}
	
	printf("Введите номер месяца рождения людей, для которых хотите получить информацию: ");
	scanf("%d",&usermonth);
	if(usermonth > 0 && usermonth < 32) {
		for(i = 0; i < N; i++) {
			if(peoples[i].birthday[1] == usermonth) {
				cout<<peoples[i].first_name<<"\t"<<peoples[i].last_name<<"\t"<<peoples[i].phone<<"\t"<<peoples[i].birthday[0]<<"\t"<<peoples[i].birthday[1]<<"\t"<<peoples[i].birthday[2]<<endl;
				ii++;
			}
		}
		
		if(ii == 0)
			printf("Нет данных о людях, родившихся в %d месяце.",usermonth);
		
	}
	else
		printf("Введен неверный номер месяца!");
	
	return 0;
}
