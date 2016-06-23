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
	SE listKata[jmlFile()];
	char line[255];
	char tok[] = " !?-.,\":\n\t";
	char *token;
	FILE *fr;
	int i;
	
	// Init stopword
	initStopword();
	
	// Init search engine
	initSearchEngine(listKata);

	/* Algoritma */
	for(i=0;i<jmlFile();i++){
		fr = fopen (listKata[i].pathfile, "r");  /* open the file for reading */
		if (!fr) return 1;
		
		while (fgets(line,sizeof(line), fr)!=NULL){
			token = strtok(line, tok);
			while(token != NULL){
				StrLower(token);
				if(!cariStopword(token)){
					listKata[i].data = insertAVL(token,listKata[i].data);
				}
				
				token = strtok(NULL,tok);
			}
		}
		fclose(fr);	
	}
	
	char cari[50];
	printf("Masukkan kata yang dicari : ");
//	scanf("%s",&cari);
	gets(cari);
	StrLower(cari);
	
	printf("\nPencarian dengan keyword %s :\n",cari);
	for(i=0;i<jmlFile();i++){
//		// Nyari nama file
//		StrLower(listKata[i].namafile);
//		if(strstr(listKata[i].namafile, cari)!=NULL){
//			printf("Nama file %s\n",listKata[i].namafile);
//		}
		if(find(cari, listKata[i].data)!=NULL){
			printf("(*) %s jumlah frekuensi %d\n",listKata[i].namafile,countKata(find(cari, listKata[i].data)));
		}
	}


	return 0;
}
