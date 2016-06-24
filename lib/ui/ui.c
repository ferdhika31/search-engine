/*
	Program 		: ui.c
	Deskripsi 		: User Interface Modul
	Author 			: Ferdhika Yudira (151524010)
	Tanggal/Version : 24/01/2016 v.1.0
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: modul ui search engine
*/

#include<stdio.h>
#include<windows.h> 
#include<stdlib.h>

/* Prototype */
void kordinat(int baris, int kolom);
void header();

/* 
	Gotoxy modul
 */
void kordinat(int baris, int kolom){ // Referensi : Modul kordinat di http://erwintsuki.blogspot.com/2012/02/pernahkan-anda-gagal-menggunakan-fungsi.html
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.Y = baris;  
	dwCursorPosition.X = kolom;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}

void header(){
	FILE *bacaFile;
	char tampil[200];
	int i=2;
	
	// open file txt
	bacaFile=fopen("lib/ui/header.txt","r");
	while(fgets(tampil,sizeof(tampil),bacaFile)){	
		kordinat(i,14);
		printf("%s",tampil);
		i++;
	}
	fclose(bacaFile);
}
