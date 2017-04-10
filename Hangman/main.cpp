// Example program
//hangman game - new
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <algorithm> // std::random_shuffle

//Function Prototypes
void hangman_draw(int); //creates and outputs hangman graphics
void display_progress(std::vector<char>);
void display_wrong(std::vector<char>);
std::string get_word(); //get a word for player to guess
std::vector<int> findPositions(std::string, char); //searches the selected word for player guess

int main()
{
    const int maxWrongGuess = 6; //max number of wrong guesses
    const int winningGraphic = maxWrongGuess + 1; //stores the winning graphic row number
    const char placeHolder = '_'; //character place holder
    const char spacer = ' '; //character spacer

    int wrongGuessQty = 0; //current number of wrong guesses
    char playerGuess = ' '; //letter currently guessed by player
    
    std::vector<int> foundPositions; //hold positions of found chars
    std::vector<char> wrongGuesses; //hold all wrongly guessed chars
    std::vector<char> guessProgress; //holds the player guess progress of the selected word

    //get a word for player to guess
    std::string selectedWord = get_word();

    //prepare guess vector for holding player progress
    for (unsigned int i = 0; i < selectedWord.size(); ++i)
    {
        guessProgress.push_back (placeHolder);

        //eliminates extra space at the end
        if ((i + 1) != selectedWord.size())
            guessProgress.push_back (spacer);
        }
        std::cout << "Your word has " << selectedWord.size() << " characters, you are allowed " << maxWrongGuess << " wrong guesses.\n";
        //call to output hangman graphics
        hangman_draw(wrongGuessQty);
        //display progress as a visual for current word for player
        display_progress(guessProgress);

        while (wrongGuessQty < maxWrongGuess)
        {
            //get players guess and convert it to upper case
            std::cout << "Enter your guess, single character only: ";
            std::cin >> playerGuess;
            playerGuess = toupper(playerGuess);

            //check player guess against selected word
            foundPositions = findPositions(selectedWord, playerGuess);

            switch (foundPositions.size())
            {
                case 0:
                    std::cout << "\n\nThe letter " << playerGuess << " was not found.\n\n";
                    break;
                case 1:
                    std::cout << "\n\nThe letter " << playerGuess << " was found once\n\n";
                    break;
                default:
                    std::cout << "\n\nThe letter " << playerGuess << " was found " << foundPositions.size() << " times.\n\n";
            }

            if (foundPositions.empty())
            {
                //if players guess was not found in selected word
                ++wrongGuessQty;

                //record wrong guess letter
                wrongGuesses.push_back (playerGuess);

                //call to output hangman graphics
                hangman_draw(wrongGuessQty);

                //display progress as a visual for current word for player
                display_progress(guessProgress);

                //output all wrong guesses
                display_wrong(wrongGuesses);
            }
            else
            {
                //if players guess was found in selected word
                for (std::vector<int>::iterator it = foundPositions.begin(); it != foundPositions.end(); ++it)
                    guessProgress.at(*it) = playerGuess;

                //display progress as a visual for current word for player
                display_progress(guessProgress);

                //output all wrong guesses
                display_wrong(wrongGuesses);

                //Check if the player guessed all of the letters by checking for the placeholder
                if (std::find(guessProgress.begin(), guessProgress.end(), placeHolder) == guessProgress.end())
                {
                    //output winning hangman graphic
                    hangman_draw(winningGraphic);
                    break;
                }
            }
            std::cout << "You have " << maxWrongGuess - wrongGuessQty << " wrong guess(es) remaining.\n\n";
        }
        if (wrongGuessQty == maxWrongGuess)
            std::cout << "Sorry, you lost... The correct word was " << selectedWord << std::endl;
        else
            std::cout << "Congratulations, you won!!!\n\n";

    return 0;
}

//picks a word from the word list for player to guess
std::string get_word()
{
    std::vector<std::string> wordList;
    std::string selectedWord = "";

    wordList =
    {
        "APPLE",
        "DEVELOPE",
        "DEVICE",
        "ENOUGH",
        "HUMAN",
        "MAMMAL",
        "PLANET",
        "PROGRAM",
    };
    
    auto engine = std::default_random_engine{};
    std::shuffle(std::begin(wordList), std::end(wordList), engine);
    
    selectedWord = wordList[0];

    return selectedWord;
}

//displays the players current progress
void display_progress(std::vector<char> currentProgress)
{
    std::cout << std::endl;
    for (std::vector<char>::iterator it = currentProgress.begin(); it != currentProgress.end(); ++it)
        std::cout << *it;
    std::cout << std::endl << std::endl;
}

//displays the players current wrong guesses
void display_wrong(std::vector<char> wrong)
{
    //only output if they have at least one wrong guess
    if (wrong.size() != 0)
    {
        std::cout << "You have guessed the following incorrect letters: ";
        for (std::vector<char>::iterator it = wrong.begin(); it != wrong.end(); ++it)
            std::cout << *it << " ";

        std::cout << std::endl << std::endl;
    }
}

//searches the selected word for the players guessed character
//returns a vector of ints if char is found
//returns an empty vector if nothing is found
std::vector<int> findPositions(std::string targetWord, char entry)
{
    std::vector<int> characterLocations;
    for(unsigned int i =0; i < targetWord.size(); i++)
        if(targetWord[i] == entry)
            //muliply position by 2 since we added a space between each letter
            //for a visual representation
            characterLocations.push_back(i*2);

    return characterLocations;
}

//create the hangman vector for the hangman graphics
//output selected graphic to the screen
void hangman_draw(int showRow)
{
    std::vector<std::vector<std::string>> hangmanGraphic(8, std::vector<std::string>(8));
    hangmanGraphic[0][0] = "  -----    ";
    hangmanGraphic[0][1] = "  |   |    ";
    hangmanGraphic[0][2] = "      |    ";
    hangmanGraphic[0][3] = "      |    ";
    hangmanGraphic[0][4] = "      |    ";
    hangmanGraphic[0][5] = "      |    ";
    hangmanGraphic[0][6] = "      |    ";
    hangmanGraphic[0][7] = "   ------- ";
    hangmanGraphic[1][0] = "  -----    ";
    hangmanGraphic[1][1] = "  |   |    ";
    hangmanGraphic[1][2] = "  O   |    ";
    hangmanGraphic[1][3] = "      |    ";
    hangmanGraphic[1][4] = "      |    ";
    hangmanGraphic[1][5] = "      |    ";
    hangmanGraphic[1][6] = "      |    ";
    hangmanGraphic[1][7] = "   ------- ";
    hangmanGraphic[2][0] = "  -----    ";
    hangmanGraphic[2][1] = "  |   |    ";
    hangmanGraphic[2][2] = "  O   |    ";
    hangmanGraphic[2][3] = "  |   |    ";
    hangmanGraphic[2][4] = "  |   |    ";
    hangmanGraphic[2][5] = "      |    ";
    hangmanGraphic[2][6] = "      |    ";
    hangmanGraphic[2][7] = "   ------- ";
    hangmanGraphic[3][0] = "  -----    ";
    hangmanGraphic[3][1] = "  |   |    ";
    hangmanGraphic[3][2] = "  O   |    ";
    hangmanGraphic[3][3] = " /|   |    ";
    hangmanGraphic[3][4] = "  |   |    ";
    hangmanGraphic[3][5] = "      |    ";
    hangmanGraphic[3][6] = "      |    ";
    hangmanGraphic[3][7] = "   ------- ";
    hangmanGraphic[4][0] = "  -----    ";
    hangmanGraphic[4][1] = "  |   |    ";
    hangmanGraphic[4][2] = "  O   |    ";
    hangmanGraphic[4][3] = " /|\\  |    ";
    hangmanGraphic[4][4] = "  |   |    ";
    hangmanGraphic[4][5] = "      |    ";
    hangmanGraphic[4][6] = "      |    ";
    hangmanGraphic[4][7] = "   ------- ";
    hangmanGraphic[5][0] = "  -----    ";
    hangmanGraphic[5][1] = "  |   |    ";
    hangmanGraphic[5][2] = "  O   |    ";
    hangmanGraphic[5][3] = " /|\\  |    ";
    hangmanGraphic[5][4] = "  |   |    ";
    hangmanGraphic[5][5] = " /    |    ";
    hangmanGraphic[5][6] = "      |    ";
    hangmanGraphic[5][7] = "   ------- ";
    hangmanGraphic[6][0] = "  -----    ";
    hangmanGraphic[6][1] = "  |   |    ";
    hangmanGraphic[6][2] = "  X   |    ";
    hangmanGraphic[6][3] = " /|\\  |    ";
    hangmanGraphic[6][4] = "  |   |    ";
    hangmanGraphic[6][5] = " / \\  |    ";
    hangmanGraphic[6][6] = "      |    ";
    hangmanGraphic[6][7] = "   ------- ";
    hangmanGraphic[7][0] = "        -----    ";
    hangmanGraphic[7][1] = "        |   |    ";
    hangmanGraphic[7][2] = "            |    ";
    hangmanGraphic[7][3] = "            |    ";
    hangmanGraphic[7][4] = "  O         |    ";
    hangmanGraphic[7][5] = " \\|/        |    ";
    hangmanGraphic[7][6] = "  |         |    ";
    hangmanGraphic[7][7] = " / \\  -------   ";
    //output the desired graphic
    std::cout << "\n";
    for (unsigned int j = 0; j < hangmanGraphic[showRow].size(); ++j)
        std::cout << hangmanGraphic[showRow][j] << "\n";
    
    std::cout << "\n";

    return;
}
