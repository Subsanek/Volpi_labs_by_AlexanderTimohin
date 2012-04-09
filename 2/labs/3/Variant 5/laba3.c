/* This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */


#include <stdio.h>
#include <errno.h>

/* Лабораторная №3. Вариант №5
 * Написать программу, которая удаляет из текстового файла предложения, в которых встречаются цифры. */

int main() {
	char buff[1024]; //Буфер, куда сохраняем анализируемое предложение
	int i = 0;
	char s;
	int size = 0;
	int del = 0; // =1 если нужно удалить эту строку
	int lines = 0; //Количество строк в файле
	int predl = 0; //Количество предложений
	int digit = 0; //Количество цифр
	
	printf("Введите имя файла, из которого хотите удалить предложения с цифрами: ");
	int N = 256;
	char filename[N];
	//fgets(filename, N-1, stdin);
	gets(filename);
	
	FILE *fp;
	fp = fopen(filename,"r+");
	
	if(fp != NULL) {
		printf("Данные из файла: \n");
		while((s = fgetc(fp)) != EOF) {
			printf("%c",s);
			if(s == '.')
				predl++;
			if(isdigit(s))
				digit++;
			if(s == '\n')
				lines++;
			size++;
		}
		printf("Количество символов: %d\n", size);
		printf("Количестиво предложений: %d.\n", predl);
		printf("Количество цифр: %d.\n",digit);
		printf("Количество строк в файле: %d.\n",lines);
		
		//Открываем временный файл
		FILE *tmp;
		tmp = fopen("temp","w+");
		
		rewind(fp);

		while(!feof(fp)) {
			i = 0; //Указываем на начало буфера
			del = 0; //По умолчанию строка не удаляется
			do {
				if((s = fgetc(fp)) != EOF) {
					buff[i] = s;
					if(isdigit(s))
						del = 1; //Это предложение не будет скопировано
					i++;
				}
			}
			while(s != '.' && s != '!' && s != '?' && !feof(fp));
			buff[i] = '\0';
			if(!del) {
				//Записываем предложение без цифр во временный файл
				fputs(buff,tmp);
			}
		}
		
		fclose(fp);
		fclose(tmp);
		
		//Удаляем текущий файл и заменяем его на наш временный
		remove(filename);
		rename("temp",filename);
		
		printf("\t ------------ \t");
		printf("\nПредложения с цифрами удалены!\nТеперь содержимое файла таково:\n");
		fp = fopen(filename,"r");
		while((s = fgetc(fp)) != EOF) {
			printf("%c",s);
		}
		fclose(fp);
	}
	else
		printf("Ошибка открытия файла: ");
		if(errno == 2)
			printf("файл именем \"%s\" не найден!",filename);
	return 0;
}
