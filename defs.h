#ifndef DEFS_H 
#define DEFS_H 
#define MAXSCORE_1 9;
#define MAXSCORE_2 8;

typedef struct player
{
  char userName[50];  
int blueScore;    // Score for blue team games
  int redScore;     // Score for red team games
} Player;


typedef struct {
    Player members[50];
    int memberCount;
    int spyIndex;  // Index of the spy (-1 if no spy selected)
	int redScore;
	int blueScore;
} Team;

typedef struct card
{
	char word[20];          // The codename word
    char identity;          // 'B', 'R', 'I', 'A' (blue, red, innocent, assassin)
    int isRevealed;         // 0 if true role hidden, 1 if revealed
} Card;


typedef struct gameState	
{
    Card grid[5][5];        // 5x5 grid of cards
    char keyGrid[5][5];
    Team blueTeam;
    Team redTeam;
    char currentTurn;       // 'B'=0 or 'R'=1 for current team
    int  gameOver;          // 0 if ongoing, 1 if finished
    char winner;            // 'B', 'R', or 'N' (none/assassin loss)
} GameState;

#endif // DEFS_H; Include this to prevent redefinition error
