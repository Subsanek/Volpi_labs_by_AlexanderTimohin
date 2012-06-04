//GPL v 2/3

/* Вариант №28
 * Создать файл, содержащий сведения о книгах в книгохранилище. Структура  записи: шифр книги, автор, название, год издания. Написать программу, которая:
определяет автора наибольшего количества книг;
 печатает список книг в заданном диапазоне шифров. */

#include <stdio.h>
#include <stdlib.h>

//В файле одна книга - одна строка, поля отделяются символом '^'

int lines_num_get();
void show_menu();

//Файл с базой данных
char filename[255] = "file.db"; 

FILE *fp;

//Информация о книге
struct book {
	char id[255]; //Шифр книги
	char author[255]; //Автор
	char name[255]; //Название
	char year[255]; //Год
};

int lines_num = lines_num_get(); //Узнаём количество строк

void show_menu() {
	//Главное меню
	printf("\nКниг в базе данных: %d\n",lines_num_get());
	printf("1. Вывести базу данных полностью;\n\
2. Вывести базу данных, отсортированную по году издания;\n\
3. Определить автора наибольшего количества книг;\n\
4. Вывести список книг в заданном диапазаоне шифров;\n\
5. Добавить новую книгу в базу данных;\n\
6. Удалить книгу из базы данных;\n\
7. Сменить файл базы данных;\n\
0. Выход\n");
} 

void print_db(book *db) {
	//Выводим БД полностью, как оно есть в файле
	int i;
	for(i = 0; i < lines_num; i++) {
		printf("%s %s %s %s\n",db[i].id,db[i].author,db[i].name,db[i].year);
	}
}

int lines_num_get() {
	//Функция возвращает количество строк в файле filename
	int lines = 0; //Количество строк в файле
	char s;
	fp = fopen(filename,"r");
	if(fp == NULL)
		return 0;
	else {
		while((s = fgetc(fp)) != EOF) 
			if(s == '\n')
				lines++;
		fclose(fp);
	}
	return lines;
}

void get_db(book *db) {
	//Копируем данные из файла в массив структур
	int i; //Обход по строкам в файле (элементу БД)
	int j;
	char c; //Текущий символ из файла
	fp = fopen(filename,"r");
	if(fp != NULL) {
		for(i = 0; i < lines_num; i++) {
			//Считываем шифр
			j = 0;
			do {
				c = fgetc(fp);
				if(c != '^') //Чтобы не копировать табуляцию
					db[i].id[j] = c;
				j++;
			}
			while(c != '^');
			//Считываем автора
			j = 0;
			do {
				c = fgetc(fp);
				if(c != '^') //Чтобы не копировать табуляцию
					db[i].author[j] = c;
				j++;
			}
			while(c != '^');
			//Считываем название
			j = 0;
			do {
				c = fgetc(fp);
				if(c != '^') //Чтобы не копировать табуляцию
					db[i].name[j] = c;
				j++;
			}
			while(c != '^');
			//Считываем год
			j = 0;
			do {
				c = fgetc(fp);
				if(c != '\n') //Чтобы не копировать табуляцию
					db[i].year[j] = c;
				j++;
			}
			while(c != '\n');
		}
		
		fclose(fp);
	}
	else
		printf("\error\n");
}



void author_by_max_books(book *db) {
	//Выводит автора наибольшего количества книг
	
}

int main() {
	char menu_num; //Выбранный пользователем номер меню
	book *db;
	db = new book[lines_num];
	get_db(db); //Инициализируем БД
	
	do {
		show_menu();
		printf("Выберите пункт: ");
		menu_num = getchar();
		switch(menu_num) {
			case '1': print_db(db); break;
			case '0': break;
			
			default: printf("Выбран неверный номер, повторите попытку!"); break;
		}
	}
	while(menu_num != '0'); //Пока не выбран выход из программы
	
	
	delete [] db;
	return 0;
}
