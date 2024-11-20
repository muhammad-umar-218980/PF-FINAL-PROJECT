#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

// <------------------------------------------ FUNCTION PROTOTYPES ------------------------------------------>
void animation();

void welcomeAgain();

void drawHangman(int guesses);

void getRandomWord(char word[], int category);

int chooseCategory();

void playRound(char word[]);

void clearScreen() {
    system("cls");
}

void byeAnimation();

int score = 0;  // jab round khatam ho jayega score again 0 ho jayega is lie global variable set kia hai 

// <------------------------------------------ MAIN FUNCTION ------------------------------------------>
int main() {
    srand(time(NULL)); 
    char word[20]; 
    char choice;

    animation();

    do {
        int category = chooseCategory();
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

// <------------------------------------------ FUNCTION DEFINITIONS ------------------------------------------>



// <------------------------------------------ ANIMATION ------------------------------------------>

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





// <------------------------------------------ WELCOME AGAIN ANIMATION ------------------------------------------>
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






// <------------------------------------------ BYE AGAIN ANIMATION ------------------------------------------>
void byeAnimation(){
    char text[] = "\n\n THANK YOU FOR PLAYING HANGMAN \n\n GOOD BYE !!";
    int length = strlen(text);
    
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        Sleep(100);
    }

    printf("\n\n");
}





// <------------------------------------------ DRAW HANGMAN FUNCTION------------------------------------------>
// ye function hangman draw karega guesses k according 
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





// <------------------------------------------ CHOOSE CATEGORY------------------------------------------>
// so basically this function is used to choose a category out of 4 
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




// <------------------------------------------ RANDOM WORD PICKER FUNCTION------------------------------------------>
// <------------------------------------------ FILE HANDLING FUNCTION------------------------------------------>
//ye function file se random word select karega
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

    char words[100][20];
    int count = 0;
    char temp[20];

    while (fgets(temp, sizeof(temp), file)) {
        temp[strcspn(temp, "\n")] = '\0';
        strcpy(words[count], temp);
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("Error: No words found in file %s\n", fileName);
        exit(1);
    }

    int randomIndex = rand() % count;
    strcpy(word, words[randomIndex]);
}





// <------------------------------------------ FUNCTION FOR PLAYING HANGMAN------------------------------------------>
// basically is function mein puray game ki logic hai 

void playRound(char word[]) {
    char guessedWord[20] = {0}; 
    char guessedLetters[26] = {0}; 
    int guessedCount = 0;
    int guesses = 6; // Total guesses 6 hain or har ghalat guess pr ye reduce hogi by 1 upto 0 
    int wordLength = strlen(word);
    int gameWon = 0;

    // Ye Guessed word ki length k equal _ _ store karega in each index
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }

    while (guesses > 0 && !gameWon) {
        drawHangman(guesses);
        
        // ye Guessed words ki jagah _ _ print karega
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

        // isalpha function ye check karega k user ne alphabet k ilawa tou kuch enter nhi kia
        if (!isalpha(guess)) {
            printf("\nInvalid input! Please enter a letter.\n");
            Sleep(1000);
            continue;
        }

        // Ye loop check karega k agar user ne already letter guess kia hai ya nhi
        int alreadyGuessed = 0;
        for (int i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("\nYou have already guessed the letter %c.\n", guess);
            Sleep(1000);
            continue;
        }

        // Sye guessed letter store karega
        guessedLetters[guessedCount++] = guess;

        int correctGuess = 0;
        
        // Ye function guessed word ko check karega k sahi hai ya nhi
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

        // Ye function check karega k agar word completely guess ho gaya ya nhi agar nhi hua so loop will continue till guesses are 0 
        gameWon = 1;
        for (int i = 0; i < wordLength; i++) {
            if (guessedWord[i] == '_') {
                gameWon = 0;
                break;
            }
        }
    }

// Score calculate karnay k lie
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
