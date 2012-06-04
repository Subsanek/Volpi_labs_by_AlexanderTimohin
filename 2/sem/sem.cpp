//GPL v 2/3

/* Вариант №28
 * Создать файл, содержащий сведения о книгах в книгохранилище. Структура  записи: шифр книги, автор, название, год издания. Написать программу, которая:
определяет автора наибольшего количества книг;
 печатает список книг в заданном диапазоне шифров. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	printf("----------------------------------------\n");
	for(i = 0; i < lines_num; i++) {
		printf("%s %s %s %s\n",db[i].id,db[i].author,db[i].name,db[i].year);
	}
	printf("----------------------------------------");
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

void sort_by_year(book *db) {
	//Сортирует БД по убыванию году издания
	//Пусть будет пузырёк
	int i,j;
	book tmp; //Временная структура
	for(i = 0; i < lines_num; i++)
			for(j = 0; j < i; j++) {
				if(strcmp(db[j].year,db[j+1].year)>0) {
					tmp = db[j+1];
					db[j+1] = db[j];
					db[j] = tmp;
				}
			}
}

void sort_by_id(book *db) {
	//Возвращаем к кононическому состоянию - отсортированным по шифру
	int i,j;
	book tmp; //Временная структура
	for(i = 0; i < lines_num; i++)
			for(j = 0; j < i; j++) {
				if(strcmp(db[j].id,db[j+1].id)>0) {
					tmp = db[j+1];
					db[j+1] = db[j];
					db[j] = tmp;
				}
			}
}

void author_by_max_books(book *db) {
	//Выводит автора наибольшего количества книг
	int i;
	//int imax = 0;
	for(i = 0; i < lines_num; i++) {
		//db[i].author;
	}
	printf("Автор наибольшего количества книг:");
}

void print_by_id(book *db) {
	//Выводим в заданном диапазоне шифров
	int i;
	int start,stop;
	printf("Начальная граница: ");
	scanf("%d",&start);
	printf("Конечная граница: ");
	scanf("%d",&stop);
	printf("----------------------------------------\n");
	for(i = 0; i <= lines_num; i++) {
		printf("%s %s %s %s\n",db[i].id,db[i].author,db[i].name,db[i].year);
	}
	printf("----------------------------------------");
}

void add_book(book *db) {
	//Добавление новой книги в БД
	int i;
	int id = lines_num + 1; //Шифр новой книги по умолчанию
	int change_or_not; //Менять ли шифр книги на пользовательский
	char author[255],name[255],year[10];
	printf("Предлагаемый шифр книги: %d. \n\
Введите 1 если хотите изменить это значение, в противном случае введите 0:  ",id);
	scanf("%d",&change_or_not);
	if(change_or_not) {
		printf("Введите свой шифр книги: ");
		scanf("%d",&id);
	}
	printf("Введите автора книги: ");
	scanf("%s",author);
	printf("Введите название книги: ");
	scanf("%s",name);
	printf("Введите год выпуска книги: ");
	scanf("%s",year);
	
	fp = fopen(filename,"r");
	if(fp != NULL) {
		//Открываем временный файл
		FILE *tmp;
		tmp = fopen("temp","w+");
		//Копируем старые данные
		for(i = 0; i < lines_num; i++)
			fprintf(tmp,"%s^%s^%s^%s\n",db[i].id,db[i].author,db[i].name,db[i].year);
		
		//Добавляем новую строку
		fprintf(tmp,"%d^%s^%s^%s\n",id,author,name,year);
		
		fclose(fp);
		fclose(tmp);
		rename("temp",filename);
		remove("temp"); //Удаляем временный файл
		lines_num = lines_num + 1; //Корректируем количество книг
	}
	else
		printf("\nerroe\n");
}

int delete_book(book *db) {
	//Удаление книги из БД
	char bookid[255]; //Шифр удаляемой книги
	int i;
	int deleted; //Номер удаленного элемента
	printf("Введите шифр удаляемой книги (или 0 для отмены): ");
	scanf("%s",bookid);
	if(!strcmp(bookid,"0")) //Если пользователь отменил операцию
		return -1;
	fp = fopen(filename,"r");
	if(fp != NULL) {
		//Открываем временный файл
		FILE *tmp;
		tmp = fopen("temp","w+");
		for(i = 0; i < lines_num; i++) {
			if(strcmp(db[i].id,bookid)) {
				//Если шифр не совпал, то записываем строку в файл
				fprintf(tmp,"%s^%s^%s^%s\n",db[i].id,db[i].author,db[i].name,db[i].year);
			}
			else
				deleted = i; //Сохраняем номер удаляемого
		}
		fclose(fp);
		fclose(tmp);
		rename("temp",filename);
		remove("temp"); //Удаляем временный файл
		lines_num = lines_num - 1; //Корректируем количество книг
	}
	else {
		printf("\nerroe\n");
		return -1;
	}
	return deleted;
}

void change_db_file() {
	//Позволяет выбрать другой файл базы данных
	
}

int main() {
	char menu_num; //Выбранный пользователем номер меню
	int deleted;
	book *db;
	db = new book[lines_num];
	get_db(db); //Инициализируем БД
	do {
		show_menu();
		printf("Выберите пункт: ");
		gets(&menu_num);
		switch(menu_num) {
			case '1': print_db(db); break;
			case '2': sort_by_year(db); print_db(db); sort_by_id(db); break;
			case '3': author_by_max_books(db); break;
			case '4': sort_by_id(db); print_by_id(db); break;
			case '5': add_book(db);
						delete [] db;
						db = new book[lines_num];
						get_db(db);
						break;
			case '6': 
						deleted = delete_book(db);
						if(deleted) //Если удаление прошло успешно
							printf("Элемент с шифром %d удалён.",deleted);
						delete [] db;
						db = new book[lines_num];
						get_db(db);
						break;
			case '7': change_db_file(); break;
			case '0': break;
			default: printf("Выбран неверный номер, повторите попытку!"); break;
		}
	}
	while(menu_num != '0'); //Пока не выбран выход из программы
	
	delete [] db; //Освобождаем память
	return 0;
}
