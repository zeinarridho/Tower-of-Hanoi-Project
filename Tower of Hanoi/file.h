#ifndef file_h
#define file_h

#define UP 10
#define LEFT 11
#define DOWN 12
#define RIGHT 13
#define EXIT -1

typedef struct {
    int disks[9];
    int top;
} Tower;

typedef struct {
	char inisial[3];
	char mode[6];
	int jmldisks;
	int score;
}Highscore;

void menu(int *numDisks);
void playgame(Tower towers[], int numTower, int numDisks);
void menentukanCakram(int *numDisks);
void printTower(Tower towers[3], int numDisks, int selectedTower, int simpanDisks, int langkah);
void highscore();
void livescore (int langkah, int numDisks);
void hitunglangkah();
void pilihTower(int *selectedTower, int direction);
void ambilDisks(Tower *towers, int *simpanDisks);
void dropDisks(Tower *towers, int *simpanDisks);
void win(Tower towers[], int langkah, int numDisks, int selectedTower, int simpanDisks, int score, int *cekKalah);
void handBiggerThanTower();
void inisialisasiTower(Tower *tower);
void inisialisasiDisks(Tower *tower, int numDisks);
int consoleButton();
void pilihTingkatKesulitan(int tingkatKesulitan, int *numDisks);
void tingkatSusah(int *numDisks, int tingkatKesulitan);
void cakramDipegang(int simpanDisks);
void lose (int langkah, int numDisks, int *cekKalah);

void sortingScore(Highscore HSS[], int jmlstruct);
void manageHighscore (Highscore newScore);
void displayHighscore();
void addHighscore (Highscore *newScore, int scores, int numDisks);

#endif