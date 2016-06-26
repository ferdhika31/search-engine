/*
	Program 		: Main.c
	Deskripsi 		: Mini search engine 
	Author 			: Ferdhika Yudira (151524010) & Gita Suciana (151524012)
	Tanggal/Version : 21/06/2016 v.1.0
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: Mini search engine
*/
#include<stdio.h>
#include<stdbool.h>
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
	char cari[50];
	
	// Init stopword
	initStopword();
	
	// Init search engine
	initSearchEngine(listFile);

	/* Algoritma */		
	header();
	kordinat(7,16);
	printf("Masukkan kata yang dicari : ");
	gets(cari);
	
	// pecah kalimat menjadi kata dan merubah karakter menjadi lowercase
	token = strtok(cari,tok);
	while(token != NULL){
		tempCari[jmlKata] = token;
		StrLower(tempCari[jmlKata]); 
		token = strtok(NULL,tok);
		jmlKata++;
	}
	
	// cek file dari kalimat yang diinputkan, akan tampil paling atas jika semua kata ada pada file tsb dan dikalkulasikan berdasarkan tf-idf nya
	cekKalimat(&i, &NotExist, listFile, jmlKata, indexTampil, tempCari);
	
	// cek file per kata
	cekPerKata(&i, &NotExist, listFile, jmlKata, indexTampil, tempCari);
	
	// hasil searching
	hasilSearching(indexTampil, i, listFile);

	return 0;
}
