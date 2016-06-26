/*
	Program 		: searchengine.h
	Deskripsi 		: ADT Mini Search Engine
	Author 			: Ferdhika Yudira (151524010) & Gita Suciana (151524012)
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

/*
	Membangun sebuah avl tree dan memasukkan semua kata yang ada pada file text stopword 
	kedalam avl tree dengan semua karakter menjadi lowercase.
*/
void initStopword();

/*
	Menampilkan kata stopword yang ada pada tree
*/
void tampilStopword();

/*
	Mencari kata dalam stopword.
	akan menghasilkan nilai true jika kata yang di cari ada pada tree stopword
	dan menghasilkan nilai false jika kata yang di cari tidak ada.
*/
bool cariStopword(char *kata);

/*
	Membaca semua file yang ada di dalam direktori (files).
	Membuat avl tree sejumlah file yang ada pada direktori dan menginisialisasi data, tfidf, pathfile, namafile dan jumlahKata.
*/
void initSearchEngine(SE listFile[]);

/*
	Memasukkan semua kata yang tidak mengandung kata stopword ke dalam tree 
	dan menghitung frekuensi masing masing dari kata tersebut.
*/
void fileKeTree(SE listFile[]);

/*
	Mengkalkulasikan tf-idf dari kata yang dicari dalam file dan menyusun urutan dari tf-idf yang terbesar (Descending)
*/
void tfidfSortKata(int ExistedTerm[], int df, SE listFile[], char cari[]);

/*
	Mengambil jumlah file dalam folder, menghasilkan nilai berupa integer
*/
int jmlFile();

/*
	Menghitung jumlah kata untuk mencocokan jumlah kata pada keyword dengan
	jumlah kata yang di cari pada file
*/
void countJmlKata(SE listFile[], char cari[]);

/*
	cek file dari kalimat yang diinputkan, 
	akan tampil paling atas jika semua kata ada pada file tsb 
	dan diurutkan berdasarkan tf-idf nya
*/
void cekKalimat(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]);

/*
	cek file per kata
	akan tampil setelah pengecekkan kalimat 
	dan diurutkan berdasarkan tf-idf nya
*/
void cekPerKata(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]);

/*
	Menampilkan hasil dari pencarian, jika tidak ada kata yang dicari dalam file
	akan menampilkan pesan Tidak ada file dengan keyword tersebut.
	dan jika ada, akan menampilkan file yang isinya sesuai dengan keyword yang dimasukkan
*/
void hasilSearching(int indexTampil[], int jumlahFilena, SE listFile[]);

/*
	Merubah string huruf besar (uppercase) menjadi huruf kecil (lowercase)
*/
void StrLower(char str[]);

/*
	Mengurutkan file berdasarkan tf-idf secara descending
*/
void sortingFile(int indexAwal, int indexAkhir, SE listFile[], int index[]);

/*
	Menghitung jumlah Document Frequency
*/
int getDF(SE listFile[],char cari[]);

/*
	Kalkulasi TF-IDF
	Rumus : tf * log(jml_file/df)
	tf = jumlah kata yg dicari dalam 1 file
	df = jumlah dokumen yang mengandung kata yang dicari
*/
float TfIdf(int tf, int jml_file, int df); // mengembalikan nilai Term Frequency

/*
	Swap 
*/
void swap(int *A, int *B);

#endif // STOPWORD_H_INCLUDED
