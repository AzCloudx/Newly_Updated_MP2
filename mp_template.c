#include <stdio.h>
#include "helpers_1.c"
#include "helpers_2.c"
#include <string.h>

int main() {
    int menuInput;
    GameState game;
    int output[25];
    char maxFiles[20][50];
    int filesFound = 0;
    
    do {
        printf("\n=== CODENAMES GAME (blue team setup first then red team) ===\n");
        printf("MENU: \n");
        printf("1. New game \n");
        printf("2. Top Spymaster \n");
        printf("0. Exit \n");
        printf("Enter choice: ");
        scanf("%d", &menuInput);
        
        // Clear input buffer after scanf
        
        switch(menuInput) {
            case 1:
                printf("\n Starting New Game Setup...\n");
                
                // Setup teams and assign to game struct
                newGame(&game.blueTeam, &game.redTeam);
                
                // Only proceed if both teams have members and a spymaster
                if (game.blueTeam.memberCount > 0 && game.redTeam.memberCount > 0 &&
                    game.blueTeam.spyIndex != -1 && game.redTeam.spyIndex != -1) {
                    
                    printf("\n Teams setup complete!\n");
                    printf("Blue Team: %d members, Spymaster: %s\n", 
                           game.blueTeam.memberCount, 
                           game.blueTeam.members[game.blueTeam.spyIndex].userName);
                    printf("Red Team: %d members, Spymaster: %s\n", 
                           game.redTeam.memberCount, 
                           game.redTeam.members[game.redTeam.spyIndex].userName);
                    
                    printf("\nSetting up game board...\n");
                    
                    // Generate random word indices
                    wordRandom(output);
                    
                    // Load random words into the game grid
                    loadWords(&game, output);
                    printf("Random words loaded!\n");
                    
                    // Select keycard and set starting team
                    selectCard(maxFiles, &filesFound, &game);
                    printf("Keycard selected and roles assigned!\n");
                    
                    printf("\n All setup complete! Starting the game...\n");
                    printf("Press Enter to begin...");
                    getchar();
                    
                    // Start the game proper
                    playGame(&game);
                    
                } else {
                    printf("Both teams must have members and a spymaster before starting the game!\n");
                }
                break;
                
            case 2:
              if (game.blueTeam.spyIndex < 0 && game.redTeam.spyIndex < 0) {
                    printf("No games have been played yet! Returning to menu.\n");
                    break;
                }
                showTopSpymasters(&game);
                break;
                
            case 0:
                printf("Goodbye! Thanks for playing Codenames!\n");
                break;
                
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while(menuInput != 0);
    
    return 0;
}