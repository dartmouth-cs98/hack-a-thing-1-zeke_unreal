#include <iostream>
#include <ctime>

using namespace std;

const int MAX_DIFFICULTY = 10;

void SwapInts(int *Int1, int *Int2) {
    int temp = *Int1;
    *Int1 = *Int2;
    *Int2 = temp;
}

void SortInts(int *IntA, int *IntB, int *IntC) {
    if (*IntA > *IntB) SwapInts(IntA, IntB);

    if (*IntB > *IntC) SwapInts(IntB, IntC);

    if (*IntA > *IntB) SwapInts(IntA, IntB);
}

bool PlayGameAtDifficulty(int Difficulty) {
    int CodeA = rand() % Difficulty + Difficulty;
    int CodeB = rand() % Difficulty + Difficulty;
    int CodeC = rand() % Difficulty + Difficulty;

    int CodeSum = CodeA + CodeB + CodeC;
    int CodeProduct = CodeA * CodeB * CodeC;

    cout << "You're on level " << Difficulty << " of " << MAX_DIFFICULTY << ".\n"
        "I'm thinking of three numbers.\n"
        "Their sum is " << CodeSum << ".\n"
        "Their product is " << CodeProduct << ".\n"
        "Enter the three numbers, followed by 'x'.\n > ";

    int GuessA, GuessB, GuessC;

    cin >> GuessA;
    cin >> GuessB;
    cin >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    /* Although within the bounds of the game put in place by Udemy, twin sets like {3, 8, 10} and {4, 5, 12} won't pop up
     * (these sets have the same sums and products but different members), I like to account for this case because it makes
     * the problem a little more interesting, and I get to dust off my skills with pointers a little bit.
     */
    SortInts(&CodeA, &CodeB, &CodeC);
    SortInts(&GuessA, &GuessB, &GuessC);

    cout << "If you thought you could break this program by entering faulty data,\nyou thought wrong, buster. You just lose.\n";

    if (GuessSum == CodeSum && GuessProduct == CodeProduct) {
        if (CodeA == GuessA && CodeB == GuessB && CodeC == GuessC) {
            if (Difficulty == MAX_DIFFICULTY) cout << "You win!\n";
            else cout << "Next level!\n";
        } else {
            cout << "Good guesses, but unfortunately my numbers were " << CodeA << ", " << CodeB << ", and " << CodeC << ". You still lose.\n";
            return false;
        }
    } else {
        cout << "Bruh, those guesses don't even have the right product and sum.\n";
        return false;
    }

    return true;
}

int main() {
    srand(time(NULL));
    // Apparently, Unreal naming conventions call for UpperCamelCase
    int Difficulty = 2;

    while (Difficulty <= MAX_DIFFICULTY) {
        if (!PlayGameAtDifficulty(Difficulty)) {
            cout << "Game over!\n";
            return 0;
        }

        cin.clear();
        cin.ignore();
        Difficulty++;
    }

    cout << "Congrats! You get to move on to the next part of your Hack-a-Thing!\n";
    return 0;
}