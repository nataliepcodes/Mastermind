# MASTERMIND

This program is an implementation of a famous Mastermind game.

## Rules

The game is composed of 9 pieces / numbers: '0' '1' '2' '3' '4' '5' '6' '7' '8'.\
A secret code is then composed of 4 distinct pieces.\
The player has 10 attempts to find a secret code.\
After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.\
A misplaced piece is a piece that is present in the code but it is not in a good position.\
If the player finds the code, he/she wins, and the game stops.\
The players input is read from the standard input.

## Parameters

The program can receive the following parameters:\
-c [CODE]: specifies the secret code. If no code is specified, a random code will be generated.\
-t [ATTEMPS]: specifies the number of attempts; by default the player has 10 attempts.\
\
Command line input example:

```
./my_mastermind -c 1234 -t 2
```

## The game

To start the game with no parameters:

```
./my_mastermind
```

\
A secret code comprising of 4 distinct digits will be computer generated.\
10 attempts will be applied by default.\
\
The below message will be displayed:

```
=============================
        MASTERMIND
=============================
Will you find a secret code?
Please enter a valid guess.
```

\
The game will start at Round 0.

```
Round 0
```

\
The player can enter a 4 digit guess code.

```
Round 0
>1234
```

\
If the player entered a wrong input, e.g. entered less than 4 digits or entered letters instead of digits,\
then the player can entere the correct input again, in the same round.\
\
If the player's input is correct, the program will diplay the number of well placed pieces and the number of misplaced pieces.

```
Round 0
6507
Well placed pieces: 1
Misplaced pieces: 2
```

\
If the player guessed all 4 pieces / numbers of the secret code, a congratulations message will be displayed.

```
Round 1
7608
Well placed pieces: 4
Misplaced pieces: 0
------------------------------
    Congratz! You did it!
------------------------------
```

\
If the game was lost, the following message will be displayed:

```
Round 1
5612
Well placed pieces: 0
Misplaced pieces: 2
------------------------------
  Oh no, you lost! Try again!
------------------------------
```


# Programming concepts used in this project

Loops: single for loops, nested for loops, while loops, infinite while loops\
Arrays\
Strings: string compare, string copy, string length\
Read from standard input\
Command line arguments\
Dynamic memory allocation\
Generating random numbers\
Makefile\
Readme file
