#include <iostream>
#include <string>
#include <vector>
#include <cctype> // checking isalpha, char input validation loop

class HangMan
{
private:
    std::string word{""};
    std::vector<char> guesses{};
    int maxGuesses{0};
    int guessesMade{0};
    bool hasGuessesLeft{true};
    bool won{false};

public:
    // constructor
    HangMan(std::string word, int maxGuesses)
    {
        this->word = word;
        this->maxGuesses = maxGuesses;
    }
    // getters & setters
    std::string getWord()
    {
        return word;
    }
    void setWord(std::string word)
    {
        this->word = word;
    }
    std::vector<char> getGuesses()
    {
        return guesses;
    }
    void addGuess(char guess, bool correct)
    {
        if (!correct)
        {
            guessesMade++;

            if (guessesMade == maxGuesses)
            {
                std::cout << "You don't have any more guesses! " << guessesMade << "/" << maxGuesses << " guesses used!\n";
                hasGuessesLeft = false;
            }
        }

        guesses.push_back(guess);
    }
    int getMaxGuesses()
    {
        return maxGuesses;
    }
    void setMaxGuesses(int maxGuesses)
    {
        this->maxGuesses = maxGuesses;
    }
    int getGuessesMade()
    {
        return guessesMade;
    }
    void setGuessesMade(int guessesMade)
    {
        this->guessesMade = guessesMade;
    }
    bool getHasGuessesLeft()
    {
        return hasGuessesLeft;
    }
    void setHasGuessesLeft(bool hasGuessesLeft)
    {
        this->hasGuessesLeft = hasGuessesLeft;
    }
    bool getWon()
    {
        return won;
    }
    void setWon(int won)
    {
        this->won = won;
    }
    // utility & helper
    bool isCorrect(char ch)
    {
        for (char cha : word)
        {
            if (cha == ch)
            {
                return true;
            }
        }
        return false;
    }
    void prompt()
    {
        std::string output{""};

        for (int i{0}; i < word.size(); i++) // populate word with empty placeholders
        {
            output += '*';
        }

        // iterate through each guess, if guesses empty it is still filled with the placeholder characters from before
        for (int i{0}; i < guesses.size(); i++)
        {
            for (int j{0}; j < word.size(); j++) // for each guess, iterate through each character of word and determine if match, if does, replace placeholder character with correct character
            {
                if (guesses[i] == word[j])
                {
                    output[j] = guesses[i];
                }
            }
        }

        // check win condition by seeing if output does not have any more placeholder characters
        won = true;
        for (int i{0}; i < word.size(); i++)
        {
            if (output[i] == '*')
            {
                won = false;
            }
        }

        if (!won)
        {
            std::cout << "The man is hanging!\n";
            std::cout << output << "\n";
        }
        else
        {
            std::cout << "\nCongrats! You Win!\n\n";
        }
    }
    void promptGuess()
    {
        char guess;

        // input validation
        while (true)
        {
            std::cout << "Please guess a letter: ";
            std::cin >> guess;

            if (!isalpha(guess))
            {
                std::cout << "Please input a valid character!\n";
            }
            else
            {
                break;
            }
        }

        addGuess(guess, isCorrect(guess));
    }
    void showRemainingGuesses()
    {
        std::cout << "You have " << maxGuesses - guessesMade << " guesses left!\n\n";
    }
    void promptWelcome()
    {
        std::cout << "Welcome To Hangman!\n\n";
        std::cout << "The goal of the game is to guess the correct word.\n";
        std::cout << "The word starts off with placeholder '*' characters.\n";
        std::cout << "For every correct letter guessed, it is revealed in the word.\n";
        std::cout << "You have five guesses, excluding correct guesses. Good luck!\n\n";
    }
};

std::string randomlySelectWord()
{
    std::string words[] = {"japan", "turkey", "nepal", "malaysia", "philippines", "australia", "america", "ethiopia", "oman", "indonesia"};
    srand(time(0));
    return words[(rand() % 10) - 1];
}

int main()
{
    HangMan _hangman(randomlySelectWord(), 5);

    _hangman.promptWelcome();

    while (_hangman.getHasGuessesLeft())
    {
        _hangman.prompt();

        if (_hangman.getWon())
        {
            break;
        }

        _hangman.promptGuess();
        _hangman.showRemainingGuesses();
    }

    return 0;
}