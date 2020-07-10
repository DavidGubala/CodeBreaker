/*
David Gubala
February 21, 2020
CODEBREAKER
*/

#include <iostream>
#include <string>
#include <thread>
#include <conio.h>

using namespace std;

void game();                                    // The Game Loop
void generate_code(int(*arr)[4]);               // A function to generate a random 4-digit code with each number being unique

int main()
{
    cout << "Welcome to CODEBREAKER!" << endl;
    cout << "Press Enter to begin." << endl;
    cin.get();
    cout << string(50, '\n');   // Clear Screen
    game();                     // Start Game
    cout << "\nThank You for playing CODEBREAKER!" << endl;
    cout << "-David Gubala";
    return 0;
}

void game() {
    bool endGame, correctInput, replayGame;
    int code[4], guessCode[4], i, j, matched, found, attempt;
    int input;

    do {                        // Beginning of the Game Loop, ends with asking the player if they would like to replay
        attempt = 0;
        endGame = false;
        generate_code(&code);
        cout << "There is a 4-digit code. Crack the code to win. Each number is unique, you have 8 chances" << endl;
        do                              // Beginning of Guess Loop
        {
            cout << "Enter your guess" << endl;
            cin >> input;
            while (!cin.good()) {
                cin.clear();
                cin.ignore(100 , '\n');
                cout << "that input was incorrect, please enter a 4-digit code." << endl;
                cin >> input;
            }
            for (i = 3; i >= 0; i--) {
                guessCode[i] = input % 10;
                input /= 10;
            }
            matched = 0;
            found = 0;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (code[i] == guessCode[j]) {
                        if (i == j) {
                            matched++;
                        }
                        else {
                            found++;
                        }
                        break;
                    }
                }
            }

            if (matched == 4) {                     // If all numbers match, you win. Game ends.
                cout << "\nYOU DID IT! YOU CRACKED THE CODE." << endl;
                endGame = true;
                cin.get();
            }
            else {
                cout << "Amount of digits correctly placed : " << matched<< endl;
                cout << "Amount of right digits in the wrong place : " << found << endl;
                attempt++;
                if (attempt == 8) {
                    endGame = true;
                    cout << "You Lose." << endl;
                }
                else {
                    cout << "You have " + to_string(8 - attempt) + " attempts left." << endl << endl;
                }
                cin.get();
            }
        } while (!endGame && attempt != 8);         // End of Guess Loop
        cout << "Would you like to play again?";
        do
        {
            if (_getch() == 'y') {
                correctInput = true;
                replayGame = true;
                cout << string(50, '\n');
            }
            else if (_getch() == 'n') {
                correctInput = true;
                replayGame = false;
            }
            else {
                correctInput = false;
            }
        } while (!correctInput);
    } while (replayGame);            // End of Game Loop
}

void generate_code(int(*arr)[4]) {
    int num;
    srand((unsigned int)time(0));                           // Random Number Seed
    for (int i = 0; i < 4; i++) {
        do {
            num = rand() % 10;
        } while (find(begin((*arr)), end((*arr)), num) != end((*arr)));   // Checks if the number is already in the generated array
        (*arr)[i] = num;
    }
    /*
    for (int i = 0; i < 4; i++) {         //Uncomment this to print code at start
        cout << (*arr)[i];
    }*/
    cout << "\n";
}
