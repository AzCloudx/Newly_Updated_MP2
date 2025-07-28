#ifndef HELPERS_2_C 
#define HELPERS_2_C 

#include <stdio.h>
#include <string.h> 
#include<stdlib.h>
#include<time.h>
#include "defs.h"

/**
* The function first opens the file and initializes 400 numbers into an array
the shuffles it using rand() and srand() and saves it into another array to be used
* @param <name1> <description of parameter 1>
* @param <name2> <description of parameter 2>
* ...
* @param <nameN> <description of parameter N>
* @return <description of the return value>
* @pre <list of pre-conditions>
*/
void wordRandom(int output[25]) {
    int list[400];
    int i;

    // Fill the pool with values from 1 to 400
    for (i = 0; i < 400; i++) {
        list[i] = i + 1;
    }

    // Shuffle using Fisher-Yates algorithm
    srand(time(NULL));
    for (i = 399; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }

    // Take the first 25 numbers
    for (i = 0; i < 25; i++) {
        output[i] = list[i];
    }
}


void loadWords(GameState *game, int output[25]){
FILE* fRead=fopen("codenames.txt", "r");

int rows, cols, i;
char wordList[400][21];
int index=0;

if(fRead==NULL){
	printf("File not found!");
}else{
printf("Game Start!\n");
	 }

for(i=0;i<400;i++){
	fscanf(fRead,"%20s",wordList[i]);
}

fclose(fRead);	

	for(rows=0;rows<5;rows++){
		for(cols=0;cols<5;cols++){
				strcpy(game->grid[rows][cols].word,wordList[output[index]]);
			 	game->grid[rows][cols].isRevealed=0;//initializes the other variables in the struct
			 	game->grid[rows][cols].identity='X';
			 	index++;
		}
	}

}



void displayBoard(GameState *game){
     int rows, cols;  
       
   for (rows = 0; rows < 5; rows++){
    printf("+==================================================+=================================================+\n");    
        for (cols = 0; cols <5; cols++)
        {
            if(game->grid[rows][cols].isRevealed==0){
                 printf("|(%d,%d) %-12s ",rows,cols,game->grid[rows][cols].word); // revealed full word with 0-based coords
            }
            else {
                // Show the formatted identity when card is revealed
                switch(game->grid[rows][cols].identity) {
                    case 'B':
                        printf("|    [-Blue-]     ");
                        break;
                    case 'R':
                        printf("|    [-Red-]      ");
                        break;
                    case 'I':
                        printf("|  [-Innocent-]   ");
                        break;
                    case 'A':
                        printf("|  [-Assassin-]   ");
                        break;
                    default:
                        printf("|        %c       ", game->grid[rows][cols].identity); // fallback
                        break;
                }
            }
        }
        printf(" |\n");
    }
    printf("+==================================================+=================================================+\n");    
}

void showTopSpymasters(GameState *game) {
FILE* fp=fopen("Spymaster Scores.txt","a");

if(fp!=NULL){
 fprintf(fp,"\n=== TOP SPYMASTERS ===\n");
    if (game->blueTeam.spyIndex != -1) {
        fprintf(fp,"Blue Spymaster: %s | Score: %d\n",
            game->blueTeam.members[game->blueTeam.spyIndex].userName,
            game->blueTeam.members[game->blueTeam.spyIndex].blueScore);
    } else {
            fprintf(fp,"\n=== TOP SPYMASTERS ===\n");
    }
    if (game->redTeam.spyIndex != -1) {
        fprintf(fp,"Red Spymaster: %s | Score: %d\n",
            game->redTeam.members[game->redTeam.spyIndex].userName,
            game->redTeam.members[game->redTeam.spyIndex].redScore);
    } else {
        fprintf(fp,"No Red Spymaster selected yet.\n");
    }

    }

}

#endif // HELPERS_2_C; Include this to prevent redefinition error
