//GPL v 2/3

/* Вариант №28
 * Создать файл, содержащий сведения о книгах в книгохранилище. Структура  записи: шифр книги, автор, название, год издания. Написать программу, которая:
определяет автора наибольшего количества книг;
 печатает список книг в заданном диапазоне шифров. */

#include <stdio.h>
#include <stdlib.h>

//В файле одна книга - одна строка, поля отделяются табуляцией (\t)

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
			j = 0;
			do {
				c = fgetc(fp);
				db[i].id[j] = c;
				j++;
			}
			while(c != '\t');
			db[i].id[j] = '\0';
		}
		fclose(fp);
	}
	else
		printf("\nerror\n");
}



void author_by_max_books(book *db) {
	
	
}

int main() {
	int i;
	book *db;
	db = new book[lines_num];
	get_db(db);
	for(i = 0; i < lines_num; i++) {
		printf("%s ",db[i].id);
	}
	
	show_menu();
	
	delete [] db;
	return 0;
}
