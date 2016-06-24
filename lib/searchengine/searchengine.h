/*
	Program 		: searchengine.h
	Deskripsi 		: ADT Mini Search Engine
	Author 			: Ferdhika Yudira (151524010)
	Tanggal/Version : 21/06/2016 v.0.1
	Compiler 		: Dev C++ V5.7.1
	Depedency		: avltree.h
*/
#ifndef STOPWORD_H_INCLUDED
#define STOPWORD_H_INCLUDED

#include<stdio.h>
#include<stdbool.h>
#include<dirent.h>
#include"../avltree/avltree.h"

typedef struct SE{
	AVL* data;
	char pathfile[50];
	char namafile[50];
	float tfIdf;
	int JmlKata;
} SE;


void initStopword();
void tampilStopword();
bool cariStopword(char *kata);

void initSearchEngine(SE listFile[]);

/*
	Memasukkan kata dari isi file ke avl tree
*/
void fileKeTree(SE listFile[]);
void hasilSorting(int ExistedTerm[], int df, SE listFile[], char cari[]);
void hasilSearching(int indexTampil[], int jumlahFilena, SE listFile[]);

/*
	Mengambil jumlah file dalam folder
*/
int jmlFile();

void countJmlKata(SE listFile[], char cari[]);

void cekKalimat(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]);

void cekPerKata(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]);

void StrLower(char str[]);

void wordOperation(int jmlKata, char* tempCari[], SE listFile[]);

int getDF(SE listFile[],char cari[]);
float TfIdf(int tf, int jml_file, int df); // mengembalikan nilai Term Frequency

void swap(int *A, int *B);

#endif // STOPWORD_H_INCLUDED
