#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "file.h"
#include "Highscore.h"

#define UP 10
#define LEFT 11
#define DOWN 12
#define RIGHT 13
#define EXIT -1

int main(){
	int n;
	Tower towers[3];
	int tingkatKesulitan;
	int numDisks, numTower=3;
	int simpanDisks = 0;
	
	while(1) {
		menu(&n);
		if(n == 1){
			pilihTingkatKesulitan(tingkatKesulitan, &numDisks);
			playgame(towers, numTower, numDisks);
		}
		else if (n == 2){
			highscore();
		}
		else if (n == 3){
			exit(1);
		}
	}
	return 0;
}
