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
} SE;


void initStopword();
void tampilStopword();
bool cariStopword(char *kata);

void initSearchEngine(SE listKata[]);

/*
	Memasukkan kata dari isi file ke avl tree
*/
void fileToTree();

/*
	Mengambil jumlah file dalam folder
*/
int jmlFile();

void StrLower(char str[]);
#endif // STOPWORD_H_INCLUDED
