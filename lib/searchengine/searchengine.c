/*
	Program 		: searchengine.c
	Deskripsi 		: ADT Mini Search Engine
	Author 			: Ferdhika Yudira (151524010) & Gita Suciana
	Tanggal/Version : 21/06/2016 v.0.1
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: 
	Baca file perbaris https://www.codingunit.com/c-tutorial-file-io-using-text-files
*/
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include"../avltree/avltree.h"
#include"searchengine.h"

AVL *avlStopWord = NULL;

void initStopword(){
	char kata[50];
	FILE *fr;
	int length;
	
	fr = fopen ("lib/searchengine/stopword.txt", "r");  /* open the file for reading */
	if (!fr) printf("File tidak ada!");
	
	while (fgets(kata,sizeof(kata), fr)!=NULL){
		length = strlen(kata);
		kata[length-1] = '\0'; // assign \n sama eof \0
		StrLower(kata); // kecilkan semua huruf
		avlStopWord = insertAVL(kata,avlStopWord);
	}
	
	fclose(fr);
}

void tampilStopWord(){	
	display_avl(avlStopWord);
}

bool cariStopword(char *kata){
	// ngambil modul find kata dari avl
	return (find(kata, avlStopWord)==NULL) ? false : true;
}

void initSearchEngine(SE listKata[]){	
	DIR *dir;
	struct dirent *ent;
	char folder[] = "files";
	int i=0;
	
	/* Algoritma */
	if ((dir = opendir (folder)) != NULL){
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			// back dir tidak di tampilkan
			if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
				listKata[i].data = NULL; // init avl
				// init path file dari direktori
				strcpy(listKata[i].pathfile,"files/");
				strcat(listKata[i].pathfile,ent->d_name);
				// init nama file dari direktori
				strcpy(listKata[i].namafile,ent->d_name);
				i++;
			}
		}
		closedir (dir);
	}else{
		/* could not open directory */
		printf("Tidak dapat membuka direktori");	
	}
}

/*
	MODUL FILE
*/
int jmlFile(){
	DIR *dir;
	struct dirent *ent;
	char folder[] = "files";
	int total_file=0;
	
	/* Algoritma */
	if ((dir = opendir (folder)) != NULL){
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			// back dir tidak di tampilkan
			if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
//				printf ("%s\n", ent->d_name);
				total_file++;
			}
		}
		closedir (dir);
	}else{
		/* could not open directory */
//		printf("Tidak dapat membuka direktori");	
	}
	
	return total_file;
}

void StrLower(char str[]){
	int i;
	for (i = 0; str[i] != '\0'; i++){
		str[i] = (char)tolower(str[i]);	
	}
}
