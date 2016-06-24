/*
	Program 		: searchengine.c
	Deskripsi 		: ADT Mini Search Engine
	Author 			: Ferdhika Yudira (151524010) & Gita Suciana
	Tanggal/Version : 21/06/2016 v.0.1
	Compiler 		: Dev C++ V5.7.1
	Ctt Lain 		: 
*/
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<math.h>
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
				if(!cariStopword(token)){
					listFile[i].data = insertAVL(token,listFile[i].data);
				}
				
				token = strtok(NULL,separator);
			}
		}
		fclose(fr);	
	}
}

void hasilSorting(int ExistedTerm[], int df, SE listFile[], char cari[]){	
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

void hasilSearching(int indexTampil[], int i, SE listFile[]){
	int l;
	if(i==0){ //NotExist == jmlKata + jmlFile()
		printf("\nTidak ada file dengan kata tersebut.");
	}else{
		printf("Hasil : \n");
		for(l=0;l<i;l++){
			printf("Fileke : %d = %s TF-IDF:(%0.2f)\n",l, listFile[indexTampil[l]].namafile, listFile[indexTampil[l]].tfIdf);
		}
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
				total_file++;
			}
		}
		closedir (dir);
	}
	
	return total_file;
}

void countJmlKata(SE listFile[], char cari[]){
	int i;
	for(i=0;i<jmlFile();i++){
		if(find(cari, listFile[i].data)!=NULL){
			listFile[i].JmlKata++;
		}
	}
}

void cekKalimat(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]){
	int j;
	(*i)=0;
	for(j=0;j<jmlFile();j++){
		// tampil pertama berdasarkan frequensi (semua kata ada pada file)
		if(listFile[j].JmlKata == jmlKata){
//			printf("\n(*) %s : %.2f", listFile[j].namafile, listFile[j].tfIdf);
			indexTampil[(*i)]=j;
			(*i)++;
		}else{
			NotExist++;
		}
	}
}

void cekPerKata(int *i, int *NotExist, SE listFile[], int jmlKata, int indexTampil[], char* tempCari[]){
	int j, df, k;
	bool isExist;
	
	for(j=0;j<jmlKata;j++){
		df = getDF(listFile, tempCari[j]);
		
		if(df == 0){
			(*NotExist)++;
		}else{
			int ExistedTerm[df-1];
			
			// sorting berdasarkan tfidf
			hasilSorting(ExistedTerm, df, listFile, tempCari[j]);
			
			for(j = 0 ; j < df; j++){
				k=0;
				isExist=false;
				while(k<(*i) && !isExist){
					if(ExistedTerm[j]==indexTampil[k]){
						isExist=true;
					}
					k++;
				}
				if(!isExist){
					indexTampil[(*i)]=ExistedTerm[j];
					(*i)++;
//					printf("\n(*) %s jumlah frekuensi %d, Tf-Idf %.2f",listFile[ExistedTerm[j]].namafile,countKata(find(tempCari[j], listFile[ExistedTerm[j]].data)),listFile[ExistedTerm[j]].tfIdf);
				}
			}
			
		}
	}
}

void StrLower(char str[]){
	int i;
	for (i = 0; str[i] != '\0'; i++){
		str[i] = (char)tolower(str[i]);	
	}
}

void wordOperation(int jmlKata, char* tempCari[], SE listFile[]){
	int j;
	
	// operasi per kata
	for(j=0;j<jmlKata;j++){
		StrLower(tempCari[j]);
		countJmlKata(listFile,tempCari[j]);
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

float TfIdf(int tf, int jml_file, int df){
	// tf = jumlah kata yg dicari dalam 1 file
	// df = jumlah dokumen yang mengandung kata yang dicari
	return (tf)*log(jml_file/df);
}

/* Swapping */
void swap(int *A, int *B){
	(*A) = (*A) + (*B);
	(*B) = (*A) - (*B);
	(*A) = (*A) - (*B);
}
