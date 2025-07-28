#ifndef HELPERS_1_C
#define HELPERS_1_C
#include "helpers_2.c"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#include "defs.h"

//void loadPlayersFromFile(Team *team, const char *teamName);
//void displayTeamMembers(Team *team, const char *teamName);
//void addPlayerToTeam(Team *team);
//void selectSpyForTeam(Team *team, const char *teamName);
//void manageTeam(Team *team, const char *teamName);
//void newGame(Team *blueTeam, Team *redTeam);
//void selectCard(char maxFiles[20][50], int *filesFound, GameState *game);
//void spyPhase(GameState *game);
//void playGame(GameState *game);
//int checkWinCondition(GameState *game);

// Function to load players from players.txt for specific team
void loadPlayersFromFile(Team *team, const char *teamName) {
    FILE *file = fopen("players.txt", "r");
    if (file == NULL) {
        printf("Warning: Could not open players.txt. Starting with empty team.\n");
        return;
    }
    
    char line[50];
    char sectionHeader[50];
    int foundSection = 0;
    int playersAdded = 0;
    
    // Create section header to look for (e.g., "[BLUE]" or "[RED]")
    sprintf(sectionHeader, "[%s]", teamName);
    
    // Don't reset memberCount - we want to append to existing players
    // Reset spy selection when loading from file (since player indices might change)
    team->spyIndex = -1;
    
    // Read each line from the file
while (fscanf(file, "%49[^\n]\n", line) == 1 && team->memberCount < 50)    
 {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Check if this is a section header
        if (line[0] == '[' && line[strlen(line)-1] == ']') {
            foundSection = (strcmp(line, sectionHeader) == 0);
            continue;
        }
        
        // If we're in the right section, check for duplicates and add the player
        if (foundSection) {
            // Check if player already exists in the team
            int isDuplicate = 0;
            for (int i = 0; i < team->memberCount; i++) {
                if (strcmp(team->members[i].userName, line) == 0) {
                    isDuplicate = 1;
                    printf("Player '%s' already exists in team, skipping...\n", line);
                    break;
                }
            }
            
            // Add player if not duplicate
            if (!isDuplicate) {
                strcpy(team->members[team->memberCount].userName, line);
                // Initialize player scores
                team->members[team->memberCount].blueScore = 0;
                team->members[team->memberCount].redScore = 0;
                team->memberCount++;
                playersAdded++;
            }
        }
    }
    
    fclose(file);
    printf("Loaded %d new players from players.txt for %s team\n", playersAdded, teamName);
    printf("Total players in %s team: %d\n", teamName, team->memberCount);
}

void displayTeamMembers(Team *team, const char *teamName) {
    printf("\n\n==%s TEAM== \n", teamName);
    printf("Current %s Team members: \n", teamName);
   
    if(team->memberCount == 0) {
        printf("No members added yet.\n");
    } else {
        for(int i = 0; i < team->memberCount; i++) {
            if(i == team->spyIndex) {
                printf("+ %s (SPYMASTER) \n", team->members[i].userName);
            } else {
                printf("+ %s \n", team->members[i].userName);
            }
        }
    }
    
    // Display spy information
    if(team->spyIndex == -1) {
        printf("No spymaster selected.\n");
    } else {
        printf("Spymaster: %s\n", team->members[team->spyIndex].userName);
    }
}

// Function to add a new player to team
void addPlayerToTeam(Team *team) {
    if(team->memberCount < 50) {
        printf("Input Username: ");
        scanf("%s", team->members[team->memberCount].userName);
        // Initialize player scores
        team->members[team->memberCount].blueScore = 0;
        team->members[team->memberCount].redScore = 0;
        team->memberCount++;
        printf("Player added successfully!\n");
    } else {
        printf("Team is full! Maximum 50 players.\n");
    }
}

// Function to select spy for the team
void selectSpyForTeam(Team *team, const char *teamName) {
    if(team->memberCount == 0) {
        printf("No players in the team! Add players first.\n");
        return;
    }
    
    printf("\n=== SELECT SPYMASTER FOR %s TEAM ===\n", teamName);
    printf("Available players:\n");
    
    for(int i = 0; i < team->memberCount; i++) {
        printf("[%d] %s\n", i + 1, team->members[i].userName);
    }
    
    int spyChoice;
    printf("Enter the number of the player to make spymaster (1-%d): ", team->memberCount);
    scanf("%d", &spyChoice);
    
    if(spyChoice >= 1 && spyChoice <= team->memberCount) {
        team->spyIndex = spyChoice - 1;
        printf("Successfully selected %s as the spymaster for %s team!\n", 
               team->members[team->spyIndex].userName, teamName);
    } else {
        printf("Invalid selection. Please try again.\n");
    }
}

// Function to manage a team (generic for both blue and red)
void manageTeam(Team *team, const char *teamName) {
    // Initialize spy index to -1 (no spy selected)
    team->spyIndex = -1;
    
    int done = 0;
   
    while(!done) {
        displayTeamMembers(team, teamName);
       
        int optionSelect;
        printf("==Choose Option== \n");
        printf("[0] Done adding team & spy members \n");
        printf("[1] Add new player \n");
        printf("[2] Load players from file \n");
        printf("[3] Select spymaster \n");
        printf("Enter choice: ");
        scanf("%d", &optionSelect);
       
        switch(optionSelect) {
            case 1:
                addPlayerToTeam(team);
                break;
            case 2:
                loadPlayersFromFile(team, teamName);
                break;
            case 3:
                selectSpyForTeam(team, teamName);
                break;
            case 0:
                // Check if team has members and a spy selected
                if(team->memberCount == 0) {
                    printf("Cannot finish setup: No players in the team! Add players first.\n");
                    break;
                }
                
                if(team->spyIndex == -1) {
                    printf("\nWARNING: No spymaster selected for %s team!\n", teamName);
                    printf("You must select a spymaster before finishing team setup.\n");
                    printf("Please select option [3] to choose a spymaster.\n");
                    break;
                }
                
                done = 1;
                printf("Finished managing %s team.\n", teamName);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}

// Updated newGame function to initialize player scores
void newGame(Team *blueTeam, Team *redTeam) {
    // Initialize the teams properly
    blueTeam->memberCount = 0;
    blueTeam->spyIndex = -1;
    
    redTeam->memberCount = 0;
    redTeam->spyIndex = -1;
    
    printf("\n=== NEW GAME SETUP ===\n");
   
    // Set up blue team
    printf("Setting up Blue Team...\n");
    manageTeam(blueTeam, "BLUE");
   
    // Set up red team
    printf("\nSetting up Red Team...\n");
    manageTeam(redTeam, "RED");
   
    printf("\n=== GAME SETUP COMPLETE ===\n");
    printf("Blue Team: %d members", blueTeam->memberCount);
    if(blueTeam->spyIndex != -1) {
        printf(" (Spymaster: %s)", blueTeam->members[blueTeam->spyIndex].userName);
    }
    printf("\n");
    
    printf("Red Team: %d members", redTeam->memberCount);
    if(redTeam->spyIndex != -1) {
        printf(" (Spymaster: %s)", redTeam->members[redTeam->spyIndex].userName);
    }
    printf("\n");
}

/**
* <Description of what the function does>
* @param <filenames[20]> <o build filenames like "01.txt", "20.txt", etc.>
* @param <maxFiles[20][21]> <to store the filenames that really exist. 20 is for the number 21 is for the names>
* @param <filesFound> <Tracks how many valid files were found>
* @param <choice> <randomly chosen number to be used>
* ...
* @param <nameN> <description of parameter N>
* @return <description of the return value>
* @pre <keycard folder and files must exist>
*/
void selectCard(char maxFiles[20][50], int *filesFound, GameState *game) {
    int i = 20;
    char filenames[50];  // Fixed size - was too small before
    int choice;
    char line[50];
    char fileData[26];   // Array to store all data: 1 turn + 25 grid cells
    int dataIndex = 0;
    
    // Find all available keycard files
    while(i--) {
        sprintf(filenames, "keycard/%02d.txt", i); // creates "01.txt", "02.txt", etc.
        FILE* fp = fopen(filenames, "r");
        if (fp != NULL) {
            fclose(fp); // Immediately close since we only wanted to know if it exists
            strcpy(maxFiles[*filesFound], filenames);
            ++*filesFound;
        }
    }
    
    // Select random file
    srand(time(NULL));
    choice = rand() % *filesFound;
    printf("Random File Chosen %s\n", maxFiles[choice]);
    
    // Read all data from the selected file
    FILE* selected = fopen(maxFiles[choice], "r");
    if(selected != NULL) {
        // Read all data into 1D array first
        while(fscanf(selected, "%s", line) == 1 && dataIndex < 26) {
            fileData[dataIndex] = line[0]; // Store first character of each word
            dataIndex++;
        }
        fclose(selected);
        
        // Display the data as before but 5x5
//        for(int displayIndex = 0; displayIndex < dataIndex; displayIndex++) {
//            if (displayIndex == 0) {
//            	printf("=========== SPYMASTER VIEW ===========\n");
//                printf("Assigned Color: %c (%s Spy Master Start!)\n\n", fileData[displayIndex],(fileData[0]=='B')?"Blue":"Red"); // First element gets its own line
//            } else {
//                printf("%c ", fileData[displayIndex]);
//                if ((displayIndex - 1) % 5 == 4) { // After every 5 elements in the grid
//                    printf("\n");
//                }
//            }
//        }
        
        // Set the current turn (first element)
        switch(fileData[0]) {
            case 'B': 
                game->currentTurn = 'B';
                break;
            case 'R': 
                game->currentTurn = 'R';
                break;
            default:
                break;
        }
        
        // Convert 1D to 2D array (skip first element which is turn indicator)
        int k = 1; // Start at index 1 to skip turn indicator
        for(int row = 0; row < 5; row++) {
            for(int col = 0; col < 5; col++) {
                game->keyGrid[row][col] = fileData[k++];
            }
        }
        
//        printf("\n--- Spy Master Grid Conversion Check ---\n");
//        for(int row = 0; row < 5; row++) 
//        {
//            for(int col = 0; col < 5; col++) {
//                printf("%c ", game->keyGrid[row][col]);
//            }
//            printf("\n");
//        }
//        printf("------------------------\n\n");
//        
    } 
    else 
    {
        printf("Could not open the file\n");
    }
}


void spyPhase(GameState *game){
int i,j;
int phaseEnd=0;

while(phaseEnd!=1){
	printf("=========== SPYMASTER VIEW ===========\n");
	printf("Assigned Color: %c (%s Spy Master Start!)\n", game->currentTurn,(game->currentTurn=='B')?"Blue":"Red");
	for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%c ", game->keyGrid[i][j]);
        	}
		printf("\n");
    	}
   			printf("=========== WORD GRID VIEW ===========\n\n");
    		displayBoard(game);
    		printf("Enter number clue: ");
			if(game->currentTurn=='B'){
 	   		scanf("%d", &game->blueTeam.blueClue);
 	    	} else  {
  	    	scanf("%d", &game->redTeam.redClue);
   		    		}
   	phaseEnd=1;
	}
	
     
}


int checkWinCondition(GameState *game) {
    // Check if assassin was revealed
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 5; col++) {
            if(game->grid[row][col].identity == 'A' && game->grid[row][col].isRevealed) {
                // Team that revealed assassin loses
                game->winner = (game->currentTurn == 'B') ? 'R' : 'B';
                game->gameOver = 1;
                return 1;
            }
        }
    }
    
    // Check if blue spymaster has won (9 cards)
    if(game->blueTeam.spyIndex != -1 && 
       game->blueTeam.members[game->blueTeam.spyIndex].blueScore >= 9) {
        game->winner = 'B';
        game->gameOver = 1;
        return 1;
    }
    
    // Check if red spymaster has won (8 cards)
    if(game->redTeam.spyIndex != -1 && 
       game->redTeam.members[game->redTeam.spyIndex].redScore >= 8) {
        game->winner = 'R';
        game->gameOver = 1;
        return 1;
    }
    
    return 0; // Game continues
}


void playGame(GameState *game) {
    int row, col;
    char input[100];
    int continueTurn = 1;

	
    printf("\n=====CODENAMES GAME STARTED!======\n");
    
    // Initialize spy scores for this game
    if(game->blueTeam.spyIndex != -1) {
        game->blueTeam.members[game->blueTeam.spyIndex].blueScore = 0;
    }
    if(game->redTeam.spyIndex != -1) {
        game->redTeam.members[game->redTeam.spyIndex].redScore = 0;
    }
    
    game->gameOver = 0;
    game->winner = 'N';

    // Copy identities from keyGrid to game grid
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            game->grid[i][j].identity = game->keyGrid[i][j];
        }
    }

    while(!game->gameOver) {
        displayBoard(game);
        continueTurn = 1;

        while(continueTurn && !game->gameOver) {
            printf("%s team's turn!\n", (game->currentTurn == 'B') ? "BLUE" : "RED");
            printf("Enter coordinates (row col):");

            if(fgets(input, sizeof(input), stdin) != NULL) {
                if(sscanf(input,"%d %d", &row, &col) == 2) {
                    // Validate coordinates
                    if(row >= 0 && row < 5 && col >= 0 && col < 5) {
                        // Check if card is already revealed
                        if(game->grid[row][col].isRevealed) {
                            printf("Card at (%d,%d) is already revealed! Choose another.\n\n", row, col);
                            
                        }

                        // Reveal the card
                        game->grid[row][col].isRevealed = 1;
                        char cardIdentity = game->grid[row][col].identity;

                        printf("\nYou selected: %s at (%d,%d)\n", 
                               game->grid[row][col].word, row, col);

                        // Display the updated board immediately after revealing the card
                        printf("\nUpdated Board:\n");
                        displayBoard(game);

                        switch(cardIdentity) {
                            case 'B':
                                printf("[-Blue-] CARD! Blue team gets a point!\n");
                                if(game->blueTeam.spyIndex != -1) {
                                    game->blueTeam.members[game->blueTeam.spyIndex].blueScore++;
                                    printf("Point awarded to spymaster: %s\n", 
                                           game->blueTeam.members[game->blueTeam.spyIndex].userName);
                                }
                                if(game->currentTurn == 'B') {
                                    printf("Blue team continues their turn!\n");
                                } else {
                                    printf("Red team gave blue a point! Turn switches to Blue.\n");
                                    game->currentTurn = 'B';
                                    continueTurn = 0;
                                }
                                break;

                            case 'R':
                                printf("[-Red-] CARD! Red team gets a point!\n");
                                if(game->redTeam.spyIndex != -1) {
                                    game->redTeam.members[game->redTeam.spyIndex].redScore++;
                                    printf("Point awarded to spymaster: %s\n", 
                                           game->redTeam.members[game->redTeam.spyIndex].userName);
                                }
                                if(game->currentTurn == 'R') {
                                    printf("Red team continues their turn!\n");
                                } else {
                                    printf("Blue team gave red a point! Turn switches to Red.\n");
                                    game->currentTurn = 'R';
                                    continueTurn = 0;
                                }
                                break;

                            case 'I':
                                printf("[-Innocent-] CARD! No points awarded.\n");
                                printf("Turn switches to %s team.\n", 
                                       (game->currentTurn == 'B') ? "RED" : "BLUE");
                                game->currentTurn = (game->currentTurn == 'B') ? 'R' : 'B';
                                continueTurn = 0;
                                break;

                            case 'A':
                                printf("[-Assassin-] CARD! Game Over!\n");
                                printf("%s team revealed the assassin and loses!\n", 
                                       (game->currentTurn == 'B') ? "BLUE" : "RED");
                                continueTurn = 0;
                                break;
                        }

                        // Display current scores with spymaster names
                        printf("\nCurrent Scores:\n");
                        if(game->blueTeam.spyIndex != -1) {
                            printf("Blue Spymaster %s: %d/9 points\n", 
                                   game->blueTeam.members[game->blueTeam.spyIndex].userName,
                                   game->blueTeam.members[game->blueTeam.spyIndex].blueScore);
                        }
                        if(game->redTeam.spyIndex != -1) {
                            printf("Red Spymaster %s: %d/8 points\n", 
                                   game->redTeam.members[game->redTeam.spyIndex].userName,
                                   game->redTeam.members[game->redTeam.spyIndex].redScore);
                        }

                        // Check win conditions after each move
                        if(checkWinCondition(game)) {
                            break;
                        }

                        printf("\nPress Enter to continue...");
                        getchar();

                    } else {
                        printf("Invalid coordinates! Please enter values between 0-4.\n\n");
                    }
                } else {
                    printf("Invalid input format! Please enter: row col (e.g., '2 3')\n\n");
                }
            }
        }
    }

    // Game over - display results
    printf("\nGAME OVER!\n");
    displayBoard(game);

    if(game->winner == 'B') {
        printf("BLUE TEAM WINS!\n");
        if(game->blueTeam.spyIndex != -1) {
            printf("Winning Spymaster: %s\n", game->blueTeam.members[game->blueTeam.spyIndex].userName);
            if(game->blueTeam.members[game->blueTeam.spyIndex].blueScore >= 9) {
                printf("Blue spymaster found all their cards!\n");
            } else {
                printf("Red team hit the assassin!\n");
            }
        }
    } else if(game->winner == 'R') {
        printf("RED TEAM WINS!\n");
        if(game->redTeam.spyIndex != -1) {
            printf("Winning Spymaster: %s\n", game->redTeam.members[game->redTeam.spyIndex].userName);
            if(game->redTeam.members[game->redTeam.spyIndex].redScore >= 8) {
                printf("Red spymaster found all their cards!\n");
            } else {
                printf("Blue team hit the assassin!\n");
            }
        }
    }

    printf("\nThanks for playing Codenames!\n");
}


#endif
