#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#include "file.h"
#include "Highscore.h"

#define Highscore_FILE "Highscore.txt"


void inisialisasiTower(Tower *tower){
	tower->top = -1;
}

void printTower (Tower towers[3], int numDisks, int selectedTower, int simpanDisks, int langkah){
	system("cls");
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
    livescore (langkah, numDisks);
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

void moveDisks(int *selectedTower, int direction){
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
    
    for (int i = 0; i < 3; ++i) {
    	inisialisasiTower(&towers[i]);
	}
	inisialisasiDisks(&towers[0], numDisks);

    printTower(towers, numDisks, selectedTower, simpanDisks, langkah);

    while (1) {
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

        if (towers[2].top == numDisks - 1) {
            printf("Selamat! Anda menyelesaikan permainan dalam %d langkah.\n", langkah);
            getch();
            break;
        }
    }
}


void win(Tower towers[], int langkah, int numDisks, int selectedTower, int simpanDisks){
	printTower(towers, numDisks, selectedTower, simpanDisks, langkah);
	if(towers->disks[towers->top]==1){
		printf("Selamat Anda Menyelesaikan Permainan dalam %d Langkah", langkah);
		getch();
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
	for (int i = 0; i < 100; i++){
		printf("BELUM BANG     ");
	}
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
		scores = 1000 - (langkah - (pow(2,numDisks) - 1))*10;
	}
	else if (scores == 0){
		lose(scores);
	}
	else {
		scores = 1000;
	}
	printf("Score : %d\n\n", scores);
}

void lose (int scores){
	
}

/*void highscores (Highscore *HS){
	FILE *file = fopen(Highscore_h, "r");
	if 
} */