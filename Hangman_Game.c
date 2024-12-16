#include <stdio.h>
#include <stdlib.h>  
#include <string.h> 
#include <time.h>   
#include <ctype.h>  
#include <windows.h>  

// <------------------------------ FUNCTION PROTOTYPES ------------------------------->
void animation(); //same

void welcomeAgain(); //same

void drawHangman(int guesses);

void getRandomWord(char word[], int category);

int chooseCategory();

void playRound(char word[]);

void clearScreen() {
    system("cls");
}

void byeAnimation(); //same

int score = 0;  
// <--------------------------------- MAIN FUNCTION ------------------------------------>

int main() {
    srand(time(NULL)); 
    char word[20]; //yei string hai
    char choice;

    animation(); 
    do {
        int category = chooseCategory(); //267
        getRandomWord(word, category);
        playRound(word);
   
do {
            printf("\nDo you want to play again? (Y/N): ");
            scanf(" %c", &choice);
            choice = tolower(choice);

            if (choice != 'y' && choice != 'n') {
                printf("Invalid choice! Please enter Y or N.\n");
            }
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y') {
            clearScreen();
            welcomeAgain();
        }

    } while (choice == 'y');

    byeAnimation();
    return 0;
}

// <------------------------------ FUNCTION DEFINITIONS ------------------------------->

// <------------------------------------ ANIMATION ------------------------------------------>

void animation() {
    char text[] = "WELCOME TO HANGMAN (The Ultimate Word Guessing Game)";
    int length = strlen(text);

    printf("          ");
    for (int i = 0; i < length + 30; i++) {
        printf("-");
    }
    printf("\n\n");

    printf("\t\t\t");

    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        Sleep(100);
    }

    
printf("\n\n");

    printf("          ");
    for (int i = 0; i < length + 30; i++) {
        printf("-");
    }
    printf("\n");
}


// <--------------------------- WELCOME AGAIN ANIMATION ---------------------------->

void welcomeAgain() {
   
 char text[] = "WELCOME AGAIN !!";
    int length = strlen(text);

    printf("          ");
    for (int i = 0; i < length + 30; i++) {
        printf("-");
    }
    printf("\n\n");

    printf("\t\t\t");

    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        Sleep(100);
    }

    printf("\n\n");

    printf("          ");
    for (int i = 0; i < length + 30; i++) {
        printf("-");
    }
    printf("\n");
}





// <--------------------------- BYE AGAIN ANIMATION ------------------------------->

void byeAnimation(){
   
 char text[] = "\n\n THANK YOU FOR PLAYING HANGMAN \n\n GOOD BYE !!";
    int length = strlen(text);
    
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        Sleep(100);
    }

    printf("\n\n");
}


// <------------------------------ DRAW HANGMAN FUNCTION---------------------------->

void drawHangman(int guesses) {
    switch (guesses) {
        case 6:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;

        case 5:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n O     | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;

        case 4:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n O     | ");
            printf("\n |     | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;

        case 3:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n O     | ");
            printf("\n/|     | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;

        case 2:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n O     | ");
            printf("\n/|\\    | ");
            printf("\n       | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;

        case 1:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n O     | ");
            printf("\n/|\\    | ");
            printf("\n/      | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;

        



       

        case 0:
            printf("\n +-----+ ");
            printf("\n |     | ");
            printf("\n O     | ");
            printf("\n/|\\    | ");
            printf("\n/ \\    | ");
            printf("\n       | ");
            printf("\n=========\n");
            break;
    }
}

// <----------------------------- CHOOSE CATEGORY---------------------------------->

int chooseCategory() {
    printf("\nSelect a category:\n");
    printf("1. Cities\n");
    printf("2. Countries\n");
    printf("3. Fruits\n");
    printf("4. Vegetables\n");
    printf("Enter your choice (1-4): ");

    int choice;
    scanf("%d", &choice);

    while (choice < 1 || choice > 4) {
        printf("Invalid choice! Enter a number between 1 and 4: ");
        scanf("%d", &choice);
    }

    return choice;
}

// <-------------------------- RANDOM WORD PICKER FUNCTION----------------------->

// <----------------------------- FILE HANDLING FUNCTION-------------------------------->
void getRandomWord(char word[], int category) {
    char fileName[20];
  
  FILE *file; 


if (category == 1) {
        strcpy(fileName, "cities.txt");
    } else if (category == 2) {
        strcpy(fileName, "countries.txt");
    } else if (category == 3) {
        strcpy(fileName, "fruits.txt");
    } else if (category == 4) {
        strcpy(fileName, "vegetables.txt");
    } else {
        printf("Invalid category selected.\n");
        exit(1); 
    }

    file = fopen(fileName, "r");  
   
 if (file == NULL) {   
        printf("Error: Could not open file %s\n", fileName);  
        
        exit(1);
    }

    char words[30][20];  
    int count = 0;
    char temp[20];

    while (fgets(temp, sizeof(temp), file)) {  
        
         temp[strcspn(temp, "\n")] = '\0';  
       
         strcpy(words[count], temp); 
        count++;
    }

    fclose(file);

    int randomIndex = rand() % count; 
    
    strcpy(word, words[randomIndex]); 
}




// <------------------------ FUNCTION FOR PLAYING HANGMAN----------------------->

void playRound(char word[]) {
   
    char guessedWord[20] = {0}; 
    char guessedLetters[26] = {0}; 
    int guessedCount = 0;
    int guesses = 6; 
    int wordLength = strlen(word);
    int gameWon = 0;

    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }

    while (guesses > 0 && !gameWon) {
        drawHangman(guesses);
       
        printf("\nGuessed word: ");
        for (int i = 0; i < wordLength; i++) {
            printf("%c ", guessedWord[i]);
        }
        printf("\n");

        printf("Guessed letters: ");
        for (int i = 0; i < guessedCount; i++) {
            printf("%c ", guessedLetters[i]);
        }
        printf("\n\nGuess a letter: ");

        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("\nInvalid input! Please enter a letter.\n"); 
            continue;
        }
     



      int alreadyGuessed = 0;
        for (int i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("\nYou have already guessed the letter %c.\n", guess);
            continue;
        }

        guessedLetters[guessedCount++] = guess;

        int correctGuess = 0;
        
        
        for (int i = 0; i < wordLength; i++) {
            if (tolower(word[i]) == guess) {
                guessedWord[i] = word[i];
                correctGuess = 1;
            }
        }

        if (correctGuess) {
            printf("\nCorrect guess!\n");
        } else {
            guesses--;
            printf("\nIncorrect guess. You have %d guesses left.\n", guesses);
        }

        gameWon = 1;
        for (int i = 0; i < wordLength; i++) {
            if (guessedWord[i] == '_') {
                gameWon = 0;
                break;
            }
        }
    }



    int roundScore = 0;
    if (guesses == 6) {
        roundScore = 100;
    } else if (guesses == 5) {
        roundScore = 80;
    } else if (guesses == 4) {
        roundScore = 60;
    } else if (guesses == 3) {
        roundScore = 40;
    } else if (guesses == 2) {
        roundScore = 20;
    } else if (guesses == 0) {
        roundScore = 0;
    }

    score = score + roundScore;  
    if (guesses > 0) {
        printf("\nCongratulations! You've guessed the word: %s\n", word);
    } else {
        printf("\nSorry, you've run out of guesses. The word was: %s\n", word);
    }

    printf("Your score for this round: %d\n", roundScore);
    printf("Total score: %d\n", score);
}
