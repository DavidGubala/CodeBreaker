"# CodeBreaker" 
Code breaker is a console game created using the instructions below. I created two implementations. One fairly simple and the other with ASCII art.

#Instructions
Implement a code breaking game as a console application. At the beginning of the game, it randomly generates a secret 4 digit code.
Each digit should be unique. For example, 0123 and 3217 are valid codes, but 0112 and 7313 are not.

Once the number has been generated, the player has 8 chances to guess the code. After each guess, the game should report how many digits
they guessed correctly, and how many had the right number, but in the wrong place. For example, with a secret code of 0123, a guess of 0451
has one digit correct (the 0), and one digit with the right number in the wrong place (the 1).

After the player has either correctly broken the code or run out of guesses, ask if they would like to play again. If so, generate a new
code and start again, otherwise exit the program.
All code should go in this file. While we do not expect exhaustive error handling, we do expect that your game will handle unexpected inputs without crashing.