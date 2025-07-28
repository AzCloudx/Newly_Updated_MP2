/**
* Description : <short description of the project>
* Author/s : <student1 full name (last name, first name)>
* <student2 full name (last name, first name)>
* Section : S24
* Last Modified : <date when last revision was made>
* Acknowledgments : God, Ms. Kristine Kalaw <list of references used in the making of this project>
*/

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
    	printf("\n\n");
    	printf("+================================================================================================================+\n");
    	printf("|  _______     _______     ________     __________   ___     _      ____     ___        ___   _________    _____ |\n");
    	printf("| / ______|   / _____ \\   |  _____ \\   |  ________| |   \\   | |    / __ \\   |   \\      /   | |  _______|  / ____||\n");
    	printf("|/ /         / /     \\ \\  | |     \\ \\  | |          | |\\ \\  | |   / /  \\ \\  | |\\ \\    / /| | | |         / /     |\n");
    	printf("|| |         | |     | |  | |      | | | |______    | | \\ \\ | |  | |    | | | | \\ \\  / / | | | |_____    \\ \\___  |\n");
    	printf("|| |         | |     | |  | |      | | |  ______|   | |  \\ \\| |  | |    | | | |  \\ \\/ /  | | |  _____|    \\___ \\ |\n");
    	printf("|| |         | |     | |  | |     / /  | |          | |   \\   |  | |    | | | |   \\__/   | | | |              \\ \\|\n");
    	printf("|\\ \\______   \\ \\_____/ /  | |____/ /   | |________  | |    \\  |  | |    | | | |          | | | |_______   ____/ /|\n");
    	printf("| \\_______|   \\_______/   |_______/    |__________| |_|     \\_|  |_|    |_| |_|          |_| |_________| |_____/ |\n");
    	printf("+================================================================================================================+");
    	printf("\n\n");

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
                    printf("\nKeycard selected and roles assigned!\n");
                    
                    printf("\nAll setup complete! Starting the game...\n");
                    printf("Press Enter to begin...");
                    getchar();
                    getchar();
                    
                    // Start the game proper
                    spyPhase(&game);
                    playGame(&game);
                    
                } else {
                    printf("Both teams must have members and a spymaster before starting the game!\n");
                }
                break;
                
            case 2:
              if (game.blueTeam.spyIndex < 0 && game.redTeam.spyIndex < 0) {
                    printf("No games have been played yet! Returning to menu.\n");
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

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of
* other students and/or persons.
*
* <student1 full name (last name, first name)> (DLSU ID# <number>)
* <student2 full name (last name, first name)> (DLSU ID# <number>)
*/
