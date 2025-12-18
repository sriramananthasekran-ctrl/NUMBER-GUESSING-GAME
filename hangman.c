#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Game constants
#define MAX_ATTEMPTS 10
#define EASY_RANGE 50
#define MEDIUM_RANGE 100
#define HARD_RANGE 200

// Function prototypes
void playGame(int difficulty);
void showMenu();
int getDifficulty();
void showInstructions();
void showHighScore(int score, int attempts, int difficulty);
int playAgain();

int main() {
    int choice;
    int playing = 1;
    
    // Initialize random seed
    srand(time(0));
    
    printf("========================================\n");
    printf("    🎮 NUMBER GUESSING CHALLENGE 🎮\n");
    printf("========================================\n");
    
    while(playing) {
        showMenu();
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                playGame(getDifficulty());
                break;
            case 2:
                showInstructions();
                break;
            case 3:
                printf("\n════════════════════════════════════════\n");
                printf("           GAME STATISTICS\n");
                printf("════════════════════════════════════════\n");
                printf("🎯 Easy Mode: Guess between 1-50\n");
                printf("🎯 Medium Mode: Guess between 1-100\n");
                printf("🎯 Hard Mode: Guess between 1-200\n");
                printf("🎯 Maximum attempts: %d\n", MAX_ATTEMPTS);
                printf("════════════════════════════════════════\n\n");
                break;
            case 4:
                printf("\nThanks for playing! Goodbye! 👋\n");
                playing = 0;
                break;
            default:
                printf("Invalid choice! Please enter 1-4.\n");
        }
    }
    
    return 0;
}

void showMenu() {
    printf("\n════════════════════════════════════════\n");
    printf("              MAIN MENU\n");
    printf("════════════════════════════════════════\n");
    printf("1. 🎯 Play Game\n");
    printf("2. 📖 Instructions\n");
    printf("3. 📊 Game Info\n");
    printf("4. 🚪 Exit\n");
}

int getDifficulty() {
    int diff;
    
    printf("\n════════════════════════════════════════\n");
    printf("          SELECT DIFFICULTY\n");
    printf("════════════════════════════════════════\n");
    printf("1. 🟢 Easy (1-50)\n");
    printf("2. 🟡 Medium (1-100)\n");
    printf("3. 🔴 Hard (1-200)\n");
    
    do {
        printf("Choose (1-3): ");
        scanf("%d", &diff);
        
        if(diff < 1 || diff > 3) {
            printf("Please enter 1, 2, or 3!\n");
        }
    } while(diff < 1 || diff > 3);
    
    return diff;
}

void showInstructions() {
    printf("\n════════════════════════════════════════\n");
    printf("           HOW TO PLAY\n");
    printf("════════════════════════════════════════\n");
    printf("1. I will think of a random number\n");
    printf("2. You try to guess it\n");
    printf("3. I'll tell you if your guess is:\n");
    printf("   📈 Too HIGH\n");
    printf("   📉 Too LOW\n");
    printf("   🎉 CORRECT!\n");
    printf("4. You have %d attempts maximum\n", MAX_ATTEMPTS);
    printf("5. Score is based on attempts used:\n");
    printf("   Fewer attempts = Higher score!\n");
    printf("════════════════════════════════════════\n\n");
}

void playGame(int difficulty) {
    int number, guess, attempts = 0;
    int maxNumber;
    char playAgainChoice;
    
    // Set range based on difficulty
    switch(difficulty) {
        case 1:  // Easy
            maxNumber = EASY_RANGE;
            number = rand() % EASY_RANGE + 1;
            break;
        case 2:  // Medium
            maxNumber = MEDIUM_RANGE;
            number = rand() % MEDIUM_RANGE + 1;
            break;
        case 3:  // Hard
            maxNumber = HARD_RANGE;
            number = rand() % HARD_RANGE + 1;
            break;
    }
    
    printf("\n════════════════════════════════════════\n");
    printf("           GAME START!\n");
    printf("════════════════════════════════════════\n");
    printf("I'm thinking of a number between 1 and %d\n", maxNumber);
    printf("Can you guess it in %d tries or less?\n\n", MAX_ATTEMPTS);
    
    // Game loop
    while(attempts < MAX_ATTEMPTS) {
        attempts++;
        
        printf("Attempt %d/%d → Enter your guess: ", attempts, MAX_ATTEMPTS);
        scanf("%d", &guess);
        
        // Validate input
        if(guess < 1 || guess > maxNumber) {
            printf("Please guess between 1 and %d!\n", maxNumber);
            attempts--; // Don't count invalid guess
            continue;
        }
        
        // Check guess
        if(guess == number) {
            printf("\n════════════════════════════════════════\n");
            printf("           🎉 CONGRATULATIONS! 🎉\n");
            printf("════════════════════════════════════════\n");
            printf("You guessed it! The number was %d\n", number);
            printf("You found it in %d attempt(s)!\n", attempts);
            
            // Calculate score (higher score for fewer attempts)
            int score = (MAX_ATTEMPTS - attempts + 1) * (difficulty * 10);
            showHighScore(score, attempts, difficulty);
            
            break;
        }
        else if(guess < number) {
            printf("📉 Too LOW!");
            
            // Give hint every few attempts
            if(attempts % 3 == 0) {
                int difference = number - guess;
                if(difference > 20) printf(" (Way too low!)");
                else if(difference > 10) printf(" (Still quite low)");
                else printf(" (Getting close!)");
            }
            printf("\n");
        }
        else {
            printf("📈 Too HIGH!");
            
            // Give hint every few attempts
            if(attempts % 3 == 0) {
                int difference = guess - number;
                if(difference > 20) printf(" (Way too high!)");
                else if(difference > 10) printf(" (Still quite high)");
                else printf(" (Getting close!)");
            }
            printf("\n");
        }
        
        // Last attempt warning
        if(attempts == MAX_ATTEMPTS - 1) {
            printf("\n⚠️  Last attempt! Choose wisely!\n");
        }
    }
    
    // If ran out of attempts
    if(attempts == MAX_ATTEMPTS && guess != number) {
        printf("\n════════════════════════════════════════\n");
        printf("           💀 GAME OVER 💀\n");
        printf("════════════════════════════════════════\n");
        printf("Sorry! You used all %d attempts.\n", MAX_ATTEMPTS);
        printf("The number was: %d\n", number);
        
        // Give a hint
        if(number % 2 == 0) {
            printf("Hint: The number was EVEN\n");
        } else {
            printf("Hint: The number was ODD\n");
        }
    }
    
    printf("\n════════════════════════════════════════\n");
}

void showHighScore(int score, int attempts, int difficulty) {
    char* diffName;
    
    switch(difficulty) {
        case 1: diffName = "EASY"; break;
        case 2: diffName = "MEDIUM"; break;
        case 3: diffName = "HARD"; break;
    }
    
    printf("\n🏆 YOUR SCORE\n");
    printf("════════════════════════════════════════\n");
    printf("Difficulty: %s\n", diffName);
    printf("Attempts used: %d\n", attempts);
    printf("Your score: %d points\n", score);
    
    // Give rating based on performance
    printf("Performance: ");
    if(attempts <= 3) {
        printf("🌟 AMAZING! You're a pro!\n");
    } else if(attempts <= 5) {
        printf("👍 Excellent! Great job!\n");
    } else if(attempts <= 7) {
        printf("😊 Good work!\n");
    } else {
        printf("💪 You got it! Keep practicing!\n");
    }
    printf("════════════════════════════════════════\n");
}