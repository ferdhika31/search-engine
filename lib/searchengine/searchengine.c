/*
	Program 		: searchengine.c
	Deskripsi 		: ADT Mini Search Engine
	Author 			: Ferdhika Yudira (151524010) & Gita Suciana (151524012)
	Tanggal/Version : 21/06/2016 v.0.1
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: 
		(*) http://www.ranks.nl/stopwords/indonesian
		(*) Modul menu dari project ludo Husain Fadhlullah
		(*) get list file on directory from http://stackoverflow.com/a/612176/1517085
*/
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<math.h>
#include"../avltree/avltree.h"
#include"searchengine.h"

// Var Global avl tree stopword
AVL *avlStopWord = NULL;

/*
	Membangun sebuah avl tree dan memasukkan semua kata yang ada pada file text stopword 
	kedalam avl tree dengan semua karakter menjadi lowercase.
*/
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

/*
	Menampilkan kata stopword yang ada pada tree
*/
void tampilStopWord(){	
	display_avl(avlStopWord);
}

/*
	Mencari kata dalam stopword.
	akan menghasilkan nilai true jika kata yang di cari ada pada tree stopword
	dan menghasilkan nilai false jika kata yang di cari tidak ada.
*/
bool cariStopword(char *kata){
	// ngambil modul find kata dari avl
	return (find(kata, avlStopWord)==NULL) ? false : true;
}

/*
	Membaca semua file yang ada di dalam direktori (files).
	Membuat avl tree sejumlah file yang ada pada direktori dan menginisialisasi data, tfidf, pathfile, namafile dan jumlahKata.
*/
void initSearchEngine(SE listFile[]){	
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
				listFile[i].data = NULL; // init avl
				listFile[i].tfIdf = 0; // init tf Idf
				listFile[i].JmlKata = 0;
				// init path file dari direktori
				strcpy(listFile[i].pathfile,"files/");
				strcat(listFile[i].pathfile,ent->d_name);
				// init nama file dari direktori
				strcpy(listFile[i].namafile,ent->d_name);
				i++;
			}
		}
		closedir (dir);
		// bangun tree file
		fileKeTree(listFile);
	}else{
		/* could not open directory */
		printf("Tidak dapat membuka direktori");	
	}
}

/*
	Memasukkan semua kata yang tidak mengandung kata stopword ke dalam tree 
	dan menghitung frekuensi masing masing dari kata tersebut.
*/
void fileKeTree(SE listFile[]){
	char line[25];
	char separator[] = " !?-.,\":\n\t";
	char *token;
	FILE *fr;
	int i;
	
	for(i=0;i<jmlFile();i++){
		fr = fopen (listFile[i].pathfile, "r");  /* open the file for reading */
		if (!fr) exit(1);
		
		while(fscanf(fr, "%s", line) != EOF){
			token = strtok(line, separator);
			while(token != NULL){
				StrLower(token);
				if(!cariStopword(token)){ // seleksi stopword
					listFile[i].data = insertAVL(token,listFile[i].data);
				}
				
				token = strtok(NULL,separator);
			}
		}
		fclose(fr);	
	}
}

/*
	Mengkalkulasikan tf-idf dari kata yang dicari dalam file dan menyusun urutan dari tf-idf yang terbesar (Descending)
*/
void tfidfSortKata(int ExistedTerm[], int df, SE listFile[], char cari[]){	
	int i,j=0;
	
	for(i=0;i<jmlFile();i++){
		if(find(cari, listFile[i].data)!=NULL){
			ExistedTerm[j]=i;
			j++;
			listFile[i].tfIdf = TfIdf(countKata(find(cari, listFile[i].data)), jmlFile, df);
			//printf("(*) %s jumlah frekuensi %d, Tf-Idf %.2f\n",listFile[i].namafile,countKata(find(cari, listFile[i].data)),listFile[i].tfIdf);
		}
	}
	
	for(j = 0 ; j < df-1; j++){
		for(i = j+1 ; i < df ; i++){
			if(listFile[ExistedTerm[j]].tfIdf < listFile[ExistedTerm[i]].tfIdf || (listFile[ExistedTerm[j]].tfIdf == listFile[ExistedTerm[i]].tfIdf && listFile[ExistedTerm[j]].namafile > listFile[ExistedTerm[i]].namafile)){
				swap(&ExistedTerm[j],&ExistedTerm[i]);
			} // isi array disort berdasarkan Tf Idf atau berdasarkan nama, bila Tf Idfnya sama
		}//printf("(*) %s jumlah frekuensi %d, Tf-Idf %.2f\n",listFile[ExistedTerm[j]].namafile,countKata(find(cari, listFile[ExistedTerm[j]].data)),listFile[ExistedTerm[j]].tfIdf);
	}
}

/*
	Menampilkan hasil dari pencarian, jika tidak ada kata yang dicari dalam file
	akan menampilkan pesan Tidak ada file dengan keyword tersebut.
	dan jika ada, akan menampilkan file yang isinya sesuai dengan keyword yang dimasukkan
*/
void hasilSearching(int indexTampil[], int jumlahFilena, SE listFile[]){
	int l;
	char back,yakin;
	int teuAktif,aktif,pencet,xAwal,xAkhir,korektor,y,j,k=0,korXakhir=0;
	short i=0;
	char pathFile[100];
	
	do{
		i=2;
		teuAktif = 0; //null char
		aktif = 111; //simbol o sebagai chosen menu
		korektor = 0;
		xAwal = 10;
		xAkhir = 10;
		
		kordinat(8,16);
		if(jumlahFilena==0){ //NotExist == jmlKata + jmlFile()
			printf("Tidak ada file dengan keyword tersebut.");
		}else{
			printf("Hasil : ");
		}
		
		// Print Hasil
		for(j=1;j<=jumlahFilena;j++){
			k=j*2;
			korXakhir = 8+k;
			kordinat(korXakhir,21);
			printf("%c %s TF-IDF:(%0.2f)",teuAktif, listFile[indexTampil[j-1]].namafile, listFile[indexTampil[j-1]].tfIdf);
		}
		korXakhir = 8+j*2;
		kordinat(korXakhir,21);
		printf("%c Cari Lagi",teuAktif);
		j++;
		korXakhir = 8+j*2;
		kordinat(korXakhir,21);
		printf("%c Keluar",teuAktif);
		
		kordinat(10,16);
		printf("%c",aktif);
		
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
				if(xAwal > korXakhir){
					xAwal = 10;
				}
				if(xAwal < 10){
					xAwal = korXakhir;
				}
				kordinat(xAkhir,16);
				printf("%c",teuAktif);
				kordinat(xAwal,16);
				printf("%c",aktif);
			}
		}
		for(j=1;j<=jumlahFilena;j++){
			k=j*2;
			korXakhir = 8+k;
			if(xAwal==korXakhir){
				strcpy(pathFile,"cd files && \"");
				strcat(pathFile,listFile[indexTampil[j-1]].namafile);
				strcat(pathFile,"\"");
				system(pathFile);
				system("cls");
				header();
				hasilSearching(indexTampil, jumlahFilena, listFile);
//				main();
			}
		}
		korXakhir = 8+j*2;
		if(xAwal==korXakhir){
			system("cls");
			main();
		}else{
			exit(1);
		}
		
	}while(back!=' ');
}

/*
	Mengambil jumlah file dalam folder, menghasilkan nilai berupa integer
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
				total_file++;
			}
		}
		closedir (dir);
	}
	
	return total_file;
}

/*
	Menghitung jumlah kata untuk mencocokan jumlah kata pada keyword dengan
	jumlah kata yang di cari pada file
*/
void countJmlKata(SE listFile[], char cari[]){
	int i;
	for(i=0;i<jmlFile();i++){
		if(find(cari, listFile[i].data)!=NULL){
			listFile[i].JmlKata++;
		}
	}
}

/*
	cek file dari kalimat yang diinputkan, 
	akan tampil paling atas jika semua kata ada pada file tsb 
	dan diurutkan berdasarkan tf-idf nya
*/
void cekKalimat(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]){
	int j,k, tf=0;
	
	// count jumlah kata yang cocok dengan keyword dengan kata yang ada pada isi file
	for(j=0;j<jmlKata;j++){
		countJmlKata(listFile,tempCari[j]);
	}
	
	// Memasukkan index file yang semua kata yang dimasukkan ke dalam sebuah array
	for(j=0;j<jmlFile();j++){
		// tampil pertama berdasarkan frequensi (semua kata ada pada file)
		if(listFile[j].JmlKata == jmlKata){
			indexTampil[(*i)]=j;
			(*i)++;
		}else{
			(*NotExist)++;
		}
	}
	
	// Kalkulasi TF-IDF Kata
//	printf("Sebelum Sorting : \n");
	for(j=0;j<(*i);j++){
		for(k=0;k<jmlKata;k++){
			tf = countKata(find(tempCari[k], listFile[indexTampil[j]].data));
			// printf("Kata : %s (%d)\n", tempCari[k],countKata(find(tempCari[k], listFile[indexTampil[j]].data)));
			listFile[indexTampil[j]].tfIdf += TfIdf(tf, jmlFile(), (*i));
//			printf("TFIDF Asal : %f | TF : %d | JmFile : %d | DF: %d\n",listFile[indexTampil[j]].tfIdf, tf,jmlFile(), (*i));
		}
//		printf("(*) %s : %.2f\n", listFile[indexTampil[j]].namafile, listFile[indexTampil[j]].tfIdf);
	}
	
	// sorting file desc berdasarkan TF-IDF
	sortingFile(0,(*i), listFile, indexTampil);
}

/*
	cek file per kata
	akan tampil setelah pengecekkan kalimat 
	dan diurutkan berdasarkan tf-idf nya
*/
void cekPerKata(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]){
	int j, df, k, index;
	bool isExist;
	
	
	for(j=0;j<jmlKata;j++){
		df = getDF(listFile, tempCari[j]);
		
		if(df == 0){
			(*NotExist)++;
		}else{
			int ExistedTerm[df-1];
			
			// Kalkulasi TF-IDF Kata & Sorting File
			tfidfSortKata(ExistedTerm, df, listFile, tempCari[j]);
			
			// seleksi file sebelumnya yang udah tampil di kalimat
			for(index = 0 ; index < df; index++){
				k=0;
				isExist=false;
				// membandingkan file yang ada di modul kalimat dengan modul kata
				while(k<(*i) && !isExist){
					if(ExistedTerm[index]==indexTampil[k]){
						isExist=true;
					}
					k++;
				}
				if(!isExist){
					indexTampil[(*i)]=ExistedTerm[index];
					(*i)++;
//					printf("\n(*) %s  Tf-Idf %.2f",listFile[ExistedTerm[index]].namafile, listFile[ExistedTerm[index]].tfIdf);
				}
			}
			
		}
	}
}

/*
	Merubah string huruf besar (uppercase) menjadi huruf kecil (lowercase)
*/
void StrLower(char str[]){
	int i;
	for (i = 0; str[i] != '\0'; i++){
		str[i] = (char)tolower(str[i]);	
	}
}

/*
	Mengurutkan file berdasarkan tf-idf secara descending
*/
void sortingFile(int indexAwal, int indexAkhir, SE listFile[], int index[]){
	int j,i;
	
	for(j = indexAwal ; j < indexAkhir-1; j++){
		for(i = j+1 ; i < indexAkhir ; i++){
			if(listFile[index[j]].tfIdf < listFile[index[i]].tfIdf || (listFile[index[j]].tfIdf == listFile[index[i]].tfIdf && listFile[index[j]].namafile > listFile[index[i]].namafile)){
				swap(&index[j],&index[i]);
			} // isi array disort berdasarkan Tf Idf, atau berdasarkan nama bila Tf Idfnya sama
		}
	}
}

/*
	Menghitung jumlah Document Frequency
*/
int getDF(SE listFile[],char cari[]){
	int jumlah = 0,i;
	
	for(i=0;i<jmlFile();i++){
		if(find(cari, listFile[i].data)!=NULL){
			jumlah++;
		}
	}
	
	return jumlah;
}

/*
	Kalkulasi TF-IDF
	Rumus : tf * log(jml_file/df)
	tf = jumlah kata yg dicari dalam 1 file
	df = jumlah dokumen yang mengandung kata yang dicari
*/
float TfIdf(int tf, int jml_file, int df){
	// tf = jumlah kata yg dicari dalam 1 file
	// df = jumlah dokumen yang mengandung kata yang dicari
//	if(jml_file==df){
//		return (tf)*0.1;
//	}else{
		return (tf)*log(jml_file/df);
//	}
	
}

/* Swap */
void swap(int *A, int *B){
	(*A) = (*A) + (*B);
	(*B) = (*A) - (*B);
	(*A) = (*A) - (*B);
}
