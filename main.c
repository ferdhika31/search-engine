/*
	Program 		: Main.c
	Deskripsi 		: Mini search engine 
	Author 			: Ferdhika Yudira (151524010) & Gita Suciana
	Tanggal/Version : 21/06/2016 v.1.0
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: Mini search engine
*/
#include<stdio.h>
#include<stdbool.h>

#include"lib/avltree/avltree.h"
#include"lib/searchengine/searchengine.h"

int main(){
	/* Deklarasi */
	SE listFile[jmlFile()];
	int i,j=0,jmlKata=0;
	char tok[] = " -.,\":";
	char *token, *tempCari[25];
	bool isExist = true;
	int NotExist = 0;
	int indexTampil[jmlFile()];
	
	// Init stopword
	initStopword();
	
	// Init search engine
	initSearchEngine(listFile);

	/* Algoritma */	
	char cari[50];
	printf("Masukkan kata yang dicari:");
	gets(cari);
	
	// kalimat
	token = strtok(cari,tok);
	while(token != NULL){
		tempCari[jmlKata] = token;
		token = strtok(NULL,tok);
		jmlKata++;
	}
	
	// operasi strlower dan hitung jumlah kata
	wordOperation(jmlKata, tempCari, listFile);
	
	// cek file dari kalimat yang diinputkan
	cekKalimat(&i, &NotExist, listFile, jmlKata, indexTampil, tempCari);
	
	// cek file per kata
	cekPerKata(&i, &NotExist, listFile, jmlKata, indexTampil, tempCari);
	
	// hasil searching
	hasilSearching(indexTampil, i, listFile);
		
	exit(1);

	return 0;
}
