#include <stdio.h>
#include <string.h> // for strlen(), strcpy(), strcmp()
#include <stdlib.h> // for atoi(), rand()
#include <time.h> // for time()
#include <unistd.h> // for read()
#define CODE_SIZE 4 // the size of the secret code and the guess code
#define DIGIT_ARRAY_SIZE 9
#define BUFFER_SIZE 5 // CODE_SIZE + 1; the size of the buffer used to read the input data for 4 digit / char code, incl the null terminator, each char in guess code is represented by a single byte 


void start_message()
{
    printf("=============================\n");
    printf("        MASTERMIND\n");
    printf("=============================\n");
    printf("Will you find a secret code?\nPlease enter a valid guess.\n");
}


char* generate_secret_code(char* code)
{
    // Initialize random seed with the current time, thus we get a different sequence of random numbers every time a program is run
    srand(time(NULL));

    // Create an array of digits from 0 to 8
    int digit[DIGIT_ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int i, j, k, temp;

    // Shuffle the array by swapping each element with a random element
    for (i = 0; i < DIGIT_ARRAY_SIZE; i++)
    {
        // Generate a random digit between 0 and 9 and assign it to j variable
        j = rand() % 9;
        temp = digit[i];
        digit[i] = digit[j];
        digit[j] = temp;
    }

    // Create a secret code from the first 4 digits of the shuffled array
    code = (char*)malloc((CODE_SIZE+1)*sizeof(char));

    for (k = 0; k < CODE_SIZE; k++)
    {
        // Convert digit to char and copy to secret code string
        code[k] = digit[k] + '0'; 
    }
    // Add a null terminator to the end of the string
    code[CODE_SIZE] = '\0'; 
  
    return code;
}


char* read_guess_code(char* guess_code)
{
    guess_code = (char*)malloc((CODE_SIZE+1)*sizeof(char));

    // Keep prompting until input is valid
    while(1)
    {
        int valid_input = 0; // Reset valid_input to 0 at the beginning of each loop iteration

        read(STDIN_FILENO, guess_code, BUFFER_SIZE);
        guess_code[CODE_SIZE] = '\0'; // Add a null terminator to the end of the string

        for (int i = 0; i < CODE_SIZE; i++)
        {
            if (guess_code[i] < '0' || guess_code[i] > '8')
            {
                valid_input = 1; // Input is invalid
                break; // No need to continue
            }
        }
        
        if (strlen(guess_code) != CODE_SIZE || valid_input == 1)
        {
            printf("Wrong Input!\n");
        }
        else
        {
            break;
        }
    }
    return guess_code;
}


int guess_compare(char* secret_code, char* guess_code)
{
    int well_placed_piece = 0;
    int mis_placed_piece = 0;

    // Compare each element of secret and guess code
    for (int i = 0; i < CODE_SIZE; i++)
    {
        // If elements that are at the same index are equal
        if (guess_code[i] == secret_code[i])
        {
            // It means the piece is well placed, count well placed pieces
            well_placed_piece = well_placed_piece + 1;
        }
        // If elements are not the same
        else   
        {   // Iterate over a guess code string / character array
            for (int j = 0; j < CODE_SIZE; j++)
                {   // Compare each element of the guess code with secret code element at the index of the outer loop
                    // If there are any elements that exist in the guess code that are the same as the secret code element
                    if (guess_code[j] == secret_code[i])
                    {
                        // It means the piece is misplaced, count misplaced pieces
                        mis_placed_piece = mis_placed_piece + 1;
                    }
                }
        }
    }

    printf("Well placed pieces: %d\n", well_placed_piece);
    printf("Misplaced pieces: %d\n", mis_placed_piece);

    return well_placed_piece;
}


int main(int ac, char**av)
{
    // Declare a secret code variable; +1 is for null terminator
    char* secret_code =(char*)malloc((CODE_SIZE+1)*sizeof(char));

    // Declare a guess code variable; +1 is for null terminator
    char* guess_code =(char*)malloc((CODE_SIZE+1)*sizeof(char));

    // Declare attempts variable and initialize to 10 attempts 
    int attempts = 10;

    // Check if secret secret code and the number of attempts have been passed as arguments in CL: -c <code> and -t <attempts>
    // Loop through the 'av' array of strings and check for these arguments
    for (int i = 1; i < ac; i++)
    {
        // If CL input includes the code
        if(strcmp(av[i], "-c") == 0)
        {
            // Copy the CL input into the secret code variable
            strcpy(secret_code, av[i+1]);
        }
        // If CL includes the number of attempts
        else if (strcmp(av[i], "-t") == 0)
        {
            // Convert the attempts from string to integer and assign to the attempts variable
            attempts = atoi(av[i+1]);
        }
    }

    // If there's no secret code entered in the CL
    if (strlen(secret_code) == 0)
    {
        // Generate a secret code and assign it to the secret code variable
        secret_code = generate_secret_code(secret_code);
        printf("Computer generated secret code: %s\n", secret_code);
    }

    start_message();

    int well_placed_pieces;
    int i = 0;
    while (i < attempts)
    {
        printf("---\n");
        printf("Round %d\n", i);
        guess_code = read_guess_code(guess_code);
        well_placed_pieces = guess_compare(secret_code, guess_code);
        if (well_placed_pieces == 4)
        {
            printf("------------------------------\n");
            printf("    Congratz! You did it!\n");
            printf("------------------------------\n");
            break;
        }
        i++;
    }

    if (i == attempts && well_placed_pieces != 4)
    {
        printf("------------------------------\n");
        printf("  Oh no, you lost! Try again!\n");
        printf("------------------------------\n");
    }

    free(secret_code);
    free(guess_code);

    return 0;
}