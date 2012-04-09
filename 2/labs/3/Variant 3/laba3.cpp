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


#include <iostream>
#include <stdio.h>
#include <errno.h>
using namespace std;

//Вариант №3
//Написать программу, в текстовом файле находит и удаляет все вопросительные предложения.

int main() {
	char predlozhenie[9999];
	int i = 0;
	char c;
	int deletethispredl = 0;
	
	FILE *fp;
	fp = fopen("text.txt","r+");
	
	if(fp != NULL) {
		
		FILE *temp;
		temp = fopen("temp.txt","w+");

		while(!feof(fp)) {
			i = 0; //Указываем на начало буфера
			deletethispredl = 0;
			do {
				if((c = fgetc(fp)) != EOF) {
					predlozhenie[i] = c;
					if(c == '?')
						deletethispredl = 1;
					i++;
				}
			}
			while(c != '.' && c != '!' && c != '?' && !feof(fp));
			predlozhenie[i] = '\0';
			if(!deletethispredl) {
				fputs(predlozhenie,temp);
			}
		}
		
		fclose(fp);
		fclose(temp);
		
		remove("text.txt");
		rename("temp.txt","text.txt");
		
		cout<<"Вопросительные предложения удалены из файла text.txt";
	}
	return 0;
}
