#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#include "file.h"
#include "Highscore.h"

#define Highscore_FILE "Highscore.txt"


void inisialisasiTower(Tower *tower){
	tower->top = -1;
}

void printTower (Tower towers[3], int numDisks, int selectedTower, int simpanDisks, int langkah){
	system("cls");
	livescore (langkah, numDisks);
	for(int i = numDisks-1; i >= 0; i--){
		for(int  j = 0; j < 3; j++){
			if (i <= towers[j].top){
				printf("   %d   ", towers[j].disks[i]);
			}else {
				printf("   |   ");
			}
		}printf("\n");
	}for (int j = 0; j < 3; j++) { //cetak label tiang A,B,C.
        if (j == selectedTower) {
            printf("  [%c]  ", 'A' + j);
        } else {
            printf("   %c   ", 'A' + j);
        }
    }
    printf("\n");
    cakramDipegang(simpanDisks);
}

void inisialisasiDisks(Tower *tower, int numDisks){
	for(int i = numDisks; i > 0; i--){
		tower->disks[++(tower->top)] = i;
	}
}

void ambilDisks(Tower *towers, int *simpanDisks){ 
	*simpanDisks = towers->disks[(towers->top)--];
}

void dropDisks(Tower *towers, int *simpanDisks){
	towers->disks[++(towers->top)] = *simpanDisks;
	*simpanDisks = 0;
}

int consoleButton(){
	int ch = getch();
	if (ch == 0 || ch == 224){
		switch (getch()){
			case 72: return UP;
			case 80: return DOWN;
			case 75: return LEFT;
			case 77: return RIGHT;
		}
	}else if (ch == 27){
		return EXIT;
	}
}

void pilihTower(int *selectedTower, int direction){
	if (direction == LEFT) {
		(*selectedTower)--;
	}
	if (direction == RIGHT){
		(*selectedTower)++;
	}
}

void playgame(Tower towers[], int numTower, int numDisks) {
    int selectedTower = 0;
    int simpanDisks = 0;
    int langkah = 0;
    int scores;
    int cekKalah = 1;
    
    for (int i = 0; i < 3; ++i) {
    	inisialisasiTower(&towers[i]);
	}
	inisialisasiDisks(&towers[0], numDisks);

    printTower(towers, numDisks, selectedTower, simpanDisks, langkah);

    while (cekKalah == 1) {
        int command = consoleButton();
        switch (command) {
            case UP:
                if (simpanDisks == 0) {
                    if (towers[selectedTower].top >= 0) {
                        ambilDisks(&towers[selectedTower], &simpanDisks);
                        
                    } else {
                        printf("Tiang kosong, tidak ada cakram untuk diambil.\n");
                        getch();
                    }
                } else {
                    printf("Anda sudah memegang cakram. Turunkan cakram terlebih dahulu.\n");
                    getch();
                }
                break;

            case DOWN:
                if (simpanDisks != 0) {
                    if (towers[selectedTower].top == -1 || 
                        simpanDisks < towers[selectedTower].disks[towers[selectedTower].top]) {
                        dropDisks(&towers[selectedTower], &simpanDisks);
                        langkah++;
                    } else {
                        printf("Tidak bisa menaruh cakram lebih besar di atas cakram lebih kecil!\n");
                        getch();
                    }
                } else {
                    printf("Ambil cakram terlebih dahulu.\n");
                    getch();
                }
                break;

            case RIGHT:
                selectedTower = (selectedTower + 1) % numTower;
                break;

            case LEFT:
                selectedTower = (selectedTower + numTower - 1) % numTower;
                break;
            
            case EXIT:
            	return;
        }

        printTower(towers, numDisks, selectedTower, simpanDisks, langkah);
		win (towers, langkah, numDisks, selectedTower, simpanDisks, scores, &cekKalah);
		lose(langkah, numDisks, &cekKalah);
	}
}


void win(Tower towers[], int langkah, int numDisks, int selectedTower, int simpanDisks, int scores, int *cekKalah){
	Highscore HS;
	Highscore newScore;
	printTower(towers, numDisks, selectedTower, simpanDisks, langkah);
	if(towers[2].top == numDisks - 1){
		printf("Selamat Anda Menyelesaikan Permainan dalam %d Langkah\n\n", langkah);
		printf("Tekan tombol [Esc] untuk kembali ke main menu.");
//		addHighscore (&newScore, scores, numDisks);
//		manageHighscore (newScore);
//		displayHighscore ();
//		*cekKalah = 0;
	}
}
	
void handBiggerThanTower(Tower *towers, int hands){
	if (towers->disks[towers->top]== hands){
		printf("Cakram dipegang lebih besar");
		getch();
	}
}

void menentukanCakram(int *numDisks){
	printf("Masukan Jumlah Cakram : ");
	scanf("%d", &*numDisks);
}

void menu(int *n){
	system("cls");
	printf("\n**************\nMENU\n**************\n");
	printf("1-PLAY\n");
	printf("2-HIGHSCORE\n");
	printf("3-EXIT\n**************\n");
	printf("Pilih Menu : ");
	scanf("%d",&(*n));
}

void highscore(){
	system("cls");
	printf("asodaosidnaosidmaosidmoas");
	system("pause");
}

void pilihTingkatKesulitan(int tingkatKesulitan, int *numDisks){
	system("cls");
	printf("Pilih Tingkat Kesulitan: \n------------------------------\n");
	printf("[1] EASY (3 Cakram)\n");
	printf("[2] MEDIUM (6 Cakram)\n");
	printf("[3] HARD (9 Cakram)\n");
	printf("[4] CUSTOM\n");
	getchar();
	scanf("%d", &tingkatKesulitan);
	tingkatSusah(&*numDisks, tingkatKesulitan);
}

void tingkatSusah(int *numDisks, int tingkatKesulitan){
		if (tingkatKesulitan == 1){
		*numDisks = 3;
	}else if (tingkatKesulitan == 2){
		*numDisks = 6;
	}else if (tingkatKesulitan == 3){
		*numDisks = 9;
	}else if (tingkatKesulitan == 4){
		menentukanCakram(&*numDisks);
	}
}

void cakramDipegang (int simpanDisks){
	if (simpanDisks != 0){
		printf("Anda sedang memegang cakram: %d\n", simpanDisks);
	}else{
		printf("Anda sedang tidak memegang cakram!\n");
	}
}

void livescore (int langkah, int numDisks){
	int scores;
	
	if (langkah > pow(2,numDisks) - 1){
		scores = 1000 - (langkah - (pow(2,numDisks) - 1))*20;
	}
	else {
		scores = 1000;
	}
	printf("Score : %d\nLangkah: %d\n\n", scores, langkah);
}

void lose (int langkah, int numDisks, int *cekKalah){
	if (langkah == 50+(pow(2,numDisks)-1)){
		system("cls");
		printf("Karena poin anda menyentuh angka 0, anda dikeluarkan dari permainan, silakan mulai ulang permainan!");
		*cekKalah = 0;
	}
}

void manageHighscore(Highscore newScore) {
	Highscore HS = {"", "", 0, 0};

    FILE *file = fopen("file.txt", "w+");
    Highscore HSS[20];
    int jmlstruct = 0;

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Membaca data dari file
    rewind(file); // Pastikan posisi baca di awal file
    while (fscanf(file, "%s %s %d %d", HSS[jmlstruct].inisial, HSS[jmlstruct].mode, &HSS[jmlstruct].jmldisks, &HSS[jmlstruct].score) !=EOF/*fread(&HSS[jmlstruct], sizeof(Highscore), 1, file) == 1*/) {
        jmlstruct++;
    }

    // Menambahkan skor baru
    HSS[jmlstruct] = newScore;
    jmlstruct++;

    // Mengurutkan skor
    sortingScore(HSS, jmlstruct);

    // Menulis ulang hanya 5 skor tertinggi
    fclose(file);
    file = fopen("file.txt", "w");
    if (file == NULL) {
        perror("Error reopening file for writing");
        return;
    }

    int len = (jmlstruct < 5) ? jmlstruct : 5;
    for (int i = 0; i < len; i++) {
//        printf("Menulis ke file: %s %s %d %d\n",
//               HSS[i].inisial, HSS[i].mode, HSS[i].jmldisks, HSS[i].score);
        fprintf(file, "%s %s %d %d\n", HSS[i].inisial, HSS[i].mode, HSS[i].jmldisks, HSS[i].score);
        //fwrite(&HSS[i], sizeof(Highscore), 1, file);
    }
    fclose(file);
}

void displayHighscore() {
    Highscore HS = {"", "", 0, 0};

    FILE *file = fopen("file.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Membaca dan menampilkan data
    while (fscanf(file, "%s %s %d %d", HS.inisial, HS.mode, &HS.jmldisks, &HS.score) != EOF/*fread(&HS, sizeof(Highscore), 1, file) == 1*/) {
        printf("%s %s %d %d\n", HS.inisial, HS.mode, HS.jmldisks, HS.score);
    }

    fclose(file);
}


void sortingScore(Highscore HSS[], int jmlstruct){
	Highscore temp;
	for (int i = 0; i < jmlstruct-1; i++){
		for  (int j = i+1; j < jmlstruct; j++){
			if (HSS[i].score <= HSS[j].score){
				temp = HSS[i];
				HSS[i] = HSS[j];
				HSS[j] = temp;
			}
			
		}
	}
	
}
//
//void manageHighscore (Highscore newScore){
//	FILE *file = fopen ("file.txt","a+");
//	Highscore HSS[20];
//	int jmlstruct = 0;
//	if (file == NULL){
//		fwrite(&newScore, sizeof(Highscore), 1, file);
//		fclose(file);
//		return;
//	}else{
//		while (fread(&HSS[jmlstruct], sizeof (Highscore), 1, file) == 1){
//			jmlstruct++;
//		}
//		HSS[jmlstruct] = newScore;
//		sortingScore(HSS, jmlstruct);
//	}
//	fclose(file);
//	file = fopen ("file.txt","w");
//	int len;
//	
//	if (jmlstruct < 5){
//		len = jmlstruct;
//	}
//	else{
//		len = 5;
//	}
//	
//	for (int i = 0; i < len; i++){
//		printf("Menulis ke file: %s %s %d %d\n", 
//           HSS[i].inisial, HSS[i].mode, HSS[i].jmldisks, HSS[i].score);
//		fwrite(&HSS[i], sizeof (Highscore), 1, file);
//	}
//	fclose(file);
//}
//
//void displayHighscore (){
//	Highscore HS;
//	
//	FILE *file = fopen ("file.txt","r");
//	while (fread(&HS, sizeof(file), 1, file) != NULL){
//		printf("%s %s %d %d", HS.inisial, HS.mode, HS.jmldisks, HS.score);
//	}
//	fclose(file);
//}
//
void inputInisial(char inisial[]){
	scanf("%3s", inisial);
}

void modeMain(char mode[], int numDisks){
	if (numDisks == 3){
		strcpy(mode, "easy");
	}
	else if (numDisks == 6){
		strcpy(mode, "medium");
	}
	else if (numDisks == 9){
		strcpy(mode, "hard");
	}
	else{
		strcpy(mode, "custom");
	}
}

void addHighscore (Highscore *newScore, int scores, int numDisks){
	char inisial [3];
	char mode[6];
	inputInisial(inisial);
	modeMain(mode, numDisks);
	strcpy((*newScore).inisial, inisial);
	strcpy((*newScore).mode, mode);
	(*newScore).jmldisks = numDisks;
	(*newScore).score = scores;
}

/*
void addHighscore(Highscore HS[], int *count, int maxScores, Highscore newScore)
    if (*count < maxScores) {
        HS[*count] = newScore;
        (*count)++;
    } else {
        // Replace skor terendah jika newScore lebih tinggi
        int minIndex = 0;
        for (int i = 1; i < *count; i++) {
            if (HS[i].score < HS[minIndex].score) {
                minIndex = i;
            }
        }
        if (newScore.score > HS[minIndex].score) {
            HS[minIndex] = newScore;
        }
    }

    // Sort highscores descending
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (HS[j].score < HS[j + 1].score) {
                Highscore temp = HS[j];
                HS[j] = HS[j + 1];
                HS[j + 1] = temp;
            }
        }
    }
}

void saveHighscores(Highscore HS[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan highscores.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %s\n", HS[i].inisial, HS[i].score, HS[i].mode);
    }

    fclose(file);
}

int loadHighscores(Highscore HS[], int maxScores, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File highscores belum tersedia.\n");
        return 0;
    }

    int count = 0;
    while (count < maxScores && 
           fscanf(file, "%s %d %s", HS[count].inisial, &HS[count].score, HS[count].mode) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

void displayHighscores(Highscore HS[], int count) {
    printf("=== Highscores ===\n");
    printf("Inisial\tSkor\tMode\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t%s\n", HS[i].inisial, HS[i].score, HS[i].mode);
    }
}*/



/*void highscores (Highscore *HS, scores, numDisks){
	FILE *fileA;
	
	fileA = fopen("fileA.txt", "w");
	if (fileA == NULL){
		printf("Belum ada highscore.\n");
		return 1;
	}
	
	scanf("%s", &HS->inisial[]);
	if (numDisks == 3){
		HS->mode = 'Easy';
	}
	else if (numDisks == 6){
		HS->mode = 'Medium';
	}
	else if (numDisks == 9){
		HS->mode = 'Hard';
	}
	else {
		HS->mode = 'Custom';
	}
	HS->jmldisks = numDisks;
	HS->score = scores;
}*/