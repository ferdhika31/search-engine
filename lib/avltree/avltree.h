/*
	Program 		: avltree.h
	Deskripsi 		: ADT AVL Tree
	Author 			: Zentut
	Tanggal/Version : 21/06/2016 v.1.0
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: from www.zentut.com 
*/
#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVL{
	char data[25];
	struct AVL* left;
	struct AVL* right;
	int height;
	int count;
} AVL;

void dispose(AVL* t);
AVL* find( char *e, AVL *t );
AVL* find_min( AVL *t );
AVL* find_max( AVL *t );
AVL* insertAVL( char *data, AVL *t );
AVL* delete( char *data, AVL *t );
void display_avl(AVL* t);
char* get( AVL* n );
int* countKata(AVL* n);

#endif // AVLTREE_H_INCLUDED
