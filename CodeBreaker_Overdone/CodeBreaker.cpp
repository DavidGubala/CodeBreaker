/*
David Gubala
February 21, 2020
CODEBREAKER
*/

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std;
using this_thread::sleep_for;
using chrono::milliseconds;

void game();                                    // The Game Loop
void generate_code(int(*arr)[4]);               // A function to generate a random 4-digit code with each number being unique

// Below are functions to make the console game a little more FUN
void typewriter(const string&, unsigned int);   // A cool typing effect to make the console game more appealing
void game_art(int, int(*cGuess)[4]);


int main()
{
    cout << "Welcome to CODEBREAKER!" << endl;
    cout << "Press Enter to begin." << endl;
    cin.get();
    cout << string(50, '\n');   // Clear Screen
    game();                     // Start Game
    cout << "\nThank You for playing CODEBREAKER!"<<endl;
    cout << "-David Gubala";
    return 0;
}

void game(){
    string msg;
    bool endGame,correctInput, replayGame;
    int code[4], guessCode[4], cGuess[4], i, j, matched, found, attempt;
    char input;

    do {                        // Beginning of the Game Loop, ends with asking the player if they would like to replay
        attempt = 0;
        endGame = false;
        generate_code(&code);
        msg = "After months of work, you're finally in. \nYou've masked your identitiy and hacked your way into the Official Government Database (OGD)."
            "\nThere it is, a directory named \"ALIENS\" blocked by a 4-digit passcode."
            "\nUsing the numbers 0-9, each only once, you have 8 chances to guess correctly."
            "\nIt's up to you CODEBREAKER. Crack the code, and find the truth.\n";
        typewriter(msg, 30);
        cin.get();

        do                              // Beginning of Guess Loop
        {
            cout << string(50, '\n');
            game_art(attempt, &cGuess);
            msg = "Enter your guess. Quickly, they're hot on your trail\n";
            typewriter(msg, 30);
            cout << "|_|_|_|_|" << "\r" << flush;
            cout << "|";
            for (i = 0; i < 4; i++) {           // Checks to make sure the user is inputting integers
                do
                {
                    input = _getch();
                    if (isdigit(input)) {
                        correctInput = true;
                        guessCode[i] = input - '0';  // Converts char to int
                    }
                    else {
                        correctInput = false;
                    }
                } while (!correctInput);

                cout << input << "|";
            }

            matched = 0;
            found = 0;

            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (code[i] == guessCode[j]) {
                        if (i == j) {
                            cGuess[i] = guessCode[j];
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
                msg = "\nYOU DID IT! YOU CRACKED THE CODE.";
                typewriter(msg, 75);
                endGame = true;
                cin.get();
                cout << string(50, '\n');
                game_art(9, &cGuess);
                msg = "Aliens: CONFIRMED";
                typewriter(msg, 200);
            }
            else {

                cout << "\nAmount of numbers correctly placed : " << matched;

                cout << "\nAmount of right numbers in the wrong place : " << found;

                attempt++;
                if (attempt == 8) {
                    endGame = true;
                    cout << string(50, '\n');
                    game_art(attempt, &cGuess);
                    msg = "YOU WERE CAUGHT!\n";
                    typewriter(msg, 200);
                }
                else {
                    msg = "\nThey're getting closer!"
                        "\nYou have " + to_string(8 - attempt) + " attempts left.\n"
                        "Press [Enter] to try again.";
                    typewriter(msg, 30);
                }
                cin.get();
            }
        } while (!endGame && attempt != 8);         // End of Guess Loop

        msg = "\nWould you like to play again?";
        typewriter(msg, 50);

        do
        {
            input = _getch();
            if (input == 'y') {
                correctInput = true;
                replayGame = true;
                for (i = 0; i < 4;i++) {
                    cGuess[i] = -1;
                }
            }
            else if (input == 'n') {
                correctInput = true;
                replayGame = false;
            }
            else {
                correctInput = false;
            }
        } while (!correctInput);
        
        cout << string(50, '\n');

    }while (replayGame);            // End of Game Loop
}

void generate_code(int(*arr)[4]) {
    int num;
    srand((unsigned int)time(0));                           // Random Number Seed
    for (int i = 0; i < 4; i++) {
        do{
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

void typewriter(const string& msg, unsigned int tpc) {
    for (const char c : msg) {
        cout << c << flush;
        sleep_for(milliseconds(tpc));   // tpc = Time per character : The time to pause per character typed to screen
    }
}

void game_art(int gamePhase, int(*cGuess)[4]) {
    string asciiArt;
    char p0 = '_', p1 = '_', p2 = '_', p3 = '_';
    if ((*cGuess)[0] >= 0) {
        p0 = '0' + (*cGuess)[0];
    }
    if ((*cGuess)[1] >= 0) {
        p1 = '0' + (*cGuess)[1];
    }
    if ((*cGuess)[2] >= 0) {
        p2 = '0' + (*cGuess)[2];
    }
    if ((*cGuess)[3] >= 0) {
        p3 = '0' + (*cGuess)[3];
    }
    switch (gamePhase) {
    case 0: // Attempt Numbers 0-7
        asciiArt =  "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     _     _     _     _     _     _    X   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 1:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     _     _     _     _     _     X    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 2:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     _     _     _     _     X     _    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 3:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     _     _     _     X     _     _    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 4:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     _     _     X     _     _     _    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 5:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     _     X     _     _     _     _    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 6:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  _     X     _     _     _     _     _    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 7:
        asciiArt =   "   ._________________.\n"
"   |.---------------.|\n" 
"   ||               ||                                                            _ _.-\'`-._ _\n"
"   ||Hacking in     ||                                                           ;.\'________\'.;\n"
"   ||Progress       ||                                                _________n.[____________].n_________\n"
"   ||               ||                                               |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
"   ||  |||||    ||  X     _     _     _     _     _     _    _   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
"   ||_______________||                                               |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
"   /.-.-.-.-.-.-.-.-.\\                                               |.. .. .. ..||..||..||..||.. .. .. ..|\n"
"  /.-.-.-.-.-.-.-.-.-.\\                                              |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
" /.-.-.-.-.-.-.-.-.-.-.\\                                          ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n"
"/______/__________\\_____\\                                        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
"\\_______________________/\n";
        break;
    case 8: // Caught by FBI
        asciiArt =
            "                          _______________\n"
            "                          \\      __     /          __\n"
            "                           \\_____()____/          /  )\n"
            "                           '===========`         /  /\n"
            "                            #---\\ /---#         /  /\n"
            "                           (# @\\| |/@ #)       /  /\n"
            "                            \\   (_)   /       /  /\n"
            "                            |\\  ---  /|      /  /\n"
            "                    _______/ \\'_____'//\\____/ o_|\n"
            "                   /       \\  /     \\  /   / o_|\n"
            "                  / |           o|        / o_| \\\n"
            "                 /  |  _____     |       / /   \\ \\\n"
            "                /   |  |===|    o|      / /\\    \\ \\\n"
            "               |    |   \\@/      |     / /  \\    \\ \\\n"
            "               |    |___________o|__/----)  |\\    \\/\n"
            "               |    '              ||  --)  | \\     |\n"
            "               |___________________||  --)  |  \\    /\n"
            "                    |           o|   ''''   |   \\__/\n"
            "                    |            |          |\n";


        break;
    case 9: // Successful Hack
        asciiArt = "        .     .       .  .   . .   .   . . +  .\n"
            ".     .  :        .    .. :. .___---------___.\n"
            "       .  .    .    .  :.:. _\".^ .^ ^.  \'.. :\"-_. .\n"
            ".  :           .  .  .:../:            . .^  :.:\\.\n"
            "        .   . :: +. :.:/: .   .    .        . . .:\\ \n"
            " .  :    .     . _ :::/:               .  ^ .  . .:\\ \n"
            ".. . .     . - : :.:./.                        .  .:\\ \n"
            "  .      .     . :..|:                    .  .  ^. .:| \n"
            "    .       . : : ..||        .                . . !:| \n"
            ".      . . . ::. ::\\(                           . :)/ \n"
            " .   .     : . : .:.|. ######              .#######::| \n"
            "  :.. .  :-  : .:  ::|.#######           ..########:| \n"
            ".  .  .  . .  .  .. :\\ ########          :######## :/ \n"
            "  .        .+ :: : -.:\\ ########       . ########.:/ \n"
            "    .  .+   . . . . :.:\\. #######       #######..:/ \n"
            "    : :  . . . . ::.:..:.\\           .   .   ..:/ \n"
            "   .   .   .  .. :  -::::.\\.       | |     . .:/ \n"
            "     .  :  .  .   .-:.\":.::.\\             ..:/ \n"
            ".       -.   . . . .: .:::.:.\\.           .:/ \n"
            ".   .   .  :      : ....::_:..:\\   ___.  :/ \n"
            "   .   .  .   .:. .. .  .: :.:.:\\       :/ \n"
            "+        .   .   : . ::. :.:. .:.|\\  .:/|\n"
            "     .         +   .  .  ...:: ..| --.: | \n"
            ".      . . .  .  .  . ... :..:. /\"(  .. )\\\" \n"
            " .   .       .     :  .   .: ::/  .  . : :\\ \n";
        break;
    default:
        asciiArt = "";
    }
    if (gamePhase < 8) {
        asciiArt.insert(460, 1, p0);
        asciiArt.insert(462, 1, p1);
        asciiArt.insert(464, 1, p2);
        asciiArt.insert(466, 1, p3);
    }
    cout << asciiArt;
}