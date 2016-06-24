/*
	Program 		: _Ferdhika.c
	Deskripsi 		: 
	Author 			: Ferdhika Yudira (151524010)
	Tanggal/Version : -/01/2016 v.1.0
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: 
*/
#include "menu.h"

void InputKata(){
	system("cls");
	kordinat(20,80);
	printf("Masukkan kata yang dicari : ");
}

void FileNotFound(char kata[]){
	system("cls");
	char pilihan[2][100];
	
	kordinat(18,75);
	//printf("tidak ada file dengan kata ""%s""!", kata);
	strcpy(pilihan[0],"Cari dengan keyword lain");
	strcpy(pilihan[1],"Keluar");
	
	int n=2;
	
	int choosen = Pilihan(n,pilihan);
	system("cls");
	printf("%d", choosen);
}

void ListFile(SE se[], int df, int ET[], char cari[]){
	int j;
	for(j = 0 ; j < df; j++){
		printf("(*) %s jumlah frekuensi %d, Tf-Idf %.2f\n",se[ET[j]].namafile,countKata(find(cari, se[ET[j]].data)),se[ET[j]].tfIdf);
	}
}

int Pilihan(int n, char pilihan[][100]){
	/* Deklarasi */
	char back,yakin;
	int teuAktif,aktif,pencet,xAwal,xAkhir,korektor,y;
//	FILE *bacaFile;
	char tampil[200];
	short i,j=0;
	int choosen;
	
	do{
		i=10;
		teuAktif = 0; //null char
		aktif = 3; //simbol o sebagai chosen menu
		korektor = 0;
		xAwal = 20;
		xAkhir = 20;
		
		// open file txt
//		bacaFile=fopen("header.txt","r");
//		while(fgets(tampil,sizeof(tampil),bacaFile)){	
//			kordinat(i,42);
//			printf("%s",tampil);
//			i++;
//		}

//		fclose(bacaFile);
		while(j<n){
			
			kordinat(20 + (2*j) ,80);
			printf("%s", pilihan[j]);
			j++;
		}
		
		while(korektor != 1){
			kordinat(xAwal,-1);
			xAkhir = xAwal;
			pencet = getch();
			if(pencet == 13){
				korektor = 1;
			}else{
				if(pencet == 80){
					xAwal += 2;
				}
				if(pencet == 72){
					xAwal -= 2;
				}
				if(xAwal > 20 + (2*n)){
					xAwal = 20;
				}
				if(xAwal < 20){
					xAwal = 20 + (2*n);
				}
				kordinat(xAkhir,75);
				printf("%c",teuAktif);
				kordinat(xAwal,75);
				printf("%c",aktif);
			}
		}
		
		j = 0;
		
		while(j < n && xAwal != 20+(2*j)){
			j++;
		}
		
		choosen = j;
		
		
		
/*		if(xAwal==20){
//			maen();
		}else if(xAwal==22){
//			petunjuk();
		}else if(xAwal==24){
//			tentang();
		}else if(xAwal==26){
			system("cls");
			kordinat(10,10);
			printf("Apakah anda yakin akan keluar dari permainan?\nketik y atau Y untuk keluar..\n");
			yakin=getch();
			if(yakin=='Y' || yakin=='y'){
				exit(1);	
			}else{
//				menuUtama();
			}
		}
*/	}while(korektor != 1);
	
	/* Algoritma */
	
	return choosen;
}

/* Modul */
void kordinat(int baris, int kolom){ // Referensi : Modul kordinat di http://erwintsuki.blogspot.com/2012/02/pernahkan-anda-gagal-menggunakan-fungsi.html
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.Y = baris;  
	dwCursorPosition.X = kolom;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}

