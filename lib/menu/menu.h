#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include<stdio.h>
#include<windows.h> 
#include<stdlib.h>
#include<string.h>
#include"../searchengine/searchengine.h"
#include"../avltree/avltree.h"

void InputKata();

void FileNotFound(char kata[]);

void FileFound()

void ListFile(SE se[], int df, int ET[], char cari[]);

int Pilihan(int n, char pilihan[][100]);

void kordinat(int baris, int kolom);

#endif
