#include <iostream>
#include <vector>
#include <string>

class Player
{
private:
    char marker;
    int wins{0};

public:
    // constructor
    Player(char marker)
    {
        this->marker = marker;
    }
    // getters & setters
    char getMarker()
    {
        return marker;
    }
    void setMarker(char marker)
    {
        this->marker = marker;
    }
    int getWins()
    {
        return wins;
    }
    void setWins(int wins)
    {
        this->wins = wins;
    }
    void incrementWins()
    {
        wins += 1;
    }
};

class Board
{
private:
    std::vector<std::vector<int>> boardMap;
    std::vector<Player> players;
    bool gameOver{false};

public:
    // constructor
    Board(std::vector<Player> players, int xSize = 3, int ySize = 3)
    {
        generateBoard(xSize, ySize);
        this->players = players;
    }
    // getters & setters
    bool getGameOver()
    {
        return gameOver;
    }
    void setGameOver(bool gameOver)
    {
        this->gameOver = gameOver;
    }
    // board utility/display functions
    void generateBoard(int xSize, int ySize)
    {
        // generates a board of given size marking each spot with 0
        for (int i{0}; i < xSize; i++)
        {
            boardMap.push_back({});
            for (int j{0}; j < ySize; j++)
            {
                boardMap[i].push_back(0);
            }
        }
    }
    void displayBoard()
    {
        system("clear");
        int iterator{1};
        // displays board, 0 - unmarked, 1 - player1 marker, 2 - player2 marker
        for (int i{0}; i < boardMap.size(); i++)
        {
            for (int j{0}; j < boardMap[i].size(); j++)
            {
                switch (boardMap[i][j])
                {
                case 0:
                    std::cout << iterator << " ";
                    break;
                case 1:
                    std::cout << players[0].getMarker() << " ";
                    break;
                case 2:
                    std::cout << players[1].getMarker() << " ";
                    break;
                }
                iterator++;
            }
            std::cout << "\n";
        }
    }
    // prompts
    void promptWelcome()
    {
        std::cout << "Welcome To Tic Tac Toe!\n";
        std::cout << "Players 1 & 2 take turns placing pieces\n";
        std::cout << "Whichever player get three in a row horizontally, vertically, or diagonally wins!\n";
        std::cout << "Draws are common, may the best player win!\n";
    }
    bool determineValidity(std::vector<int> indexes)
    {
        if (boardMap[indexes[0]][indexes[1]] != 0)
        {
            return false;
        }
        return true;
    }
    void promptPlayer()
    {
        int sel{0};

        while (true)
        {
            std::cout << "Select Player (1/2): ";
            std::cin >> sel;

            if (sel > 2 || sel <= 0)
            {
                std::cout << "Please enter a valid input!\n";
            }
            else
            {
                break;
            }
        }

        promptInput(players[sel - 1]);
        sel = (sel == 1) ? 1 : 0; // this will need to be amended if more than two players should play which would make sense on larger boards
        displayBoard();
        promptInput(players[sel]);
    }
    void promptInput(Player _player)
    {
        int square{0};
        while (true)
        {
            if (_player.getMarker() == 'X')
            {
                std::cout << "Player 1, Please Select Square: ";
            }
            else
            {
                std::cout << "Player 2, Please Select Square: ";
            }
            std::cin >> square;

            std::vector<int> coords = convertNumToCoord(square);

            if (!determineValidity(coords)) // determine if spot is open
            {
                displayBoard();
                std::cout << "Please select a valid square!\n";
            }
            else
            {
                if (_player.getMarker() == 'X')
                {
                    boardMap[coords[0]][coords[1]] = 1;
                }
                else
                {
                    boardMap[coords[0]][coords[1]] = 2;
                }

                // marker is placed, determine if _player wins
                if (determineWin() == 1)
                {
                    std::cout << "Player 1 wins!\n"; // TESTING ONLY
                    gameOver = true;
                }
                else if (determineWin() == 2){
                    std::cout << "Player 2 wins!\n";
                    gameOver = true;
                }

                break;
            }
        }
    }
    std::vector<int> convertNumToCoord(int numSelected)
    {
        // determine x & y dimensions of boardMap
        int xMax{boardMap[0].size()};
        int yMax{boardMap.size()};
        int max{xMax * yMax};

        int x{0};
        int y{0};

        float yCalc{numSelected / yMax};
        float yCalcRem{numSelected % yMax};

        if (yCalcRem == 0)
        { // if whole num
            y = yCalc - 1;
        }
        else
        { // if division has remainder, then the y value is the base base from the division (without remainder)
            y = yCalc;
        }

        x = ((numSelected - (y * xMax)) - 1);

        std::vector<int> returnVector;
        // we push the y value to the vector first because we have our map organized as rows then cols
        returnVector.push_back(y);
        returnVector.push_back(x);

        return returnVector;
    }
    // win calculation function(s)
    int determineWin()
    {
        int maxCols{boardMap[0].size()};
        int maxRows{boardMap.size()};

        char marker;

        for (int row{0}; row < maxRows; row++)
        {
            for (int col{0}; col < maxCols; col++)
            {
                if (boardMap[row][col] != 0) // if there is a marker
                {
                    marker = boardMap[row][col] == 1 ? 'X' : 'O';  // for matching with what player wins, may need to check later

                    int returnValue {marker == 'X' ? 1 : 2};

                    // check diagonals
                    if (row == 0 && col == 0) // top left corner
                    {
                        for (int i{0}; i < maxCols; i++)
                        {
                            if (boardMap[row][col] != boardMap[i][i])  // if any spot does not have a mark, there can't be a win
                            {
                                break;
                            }

                            if (i == maxCols - 1) // if we reached the alternate corner and have had matches up to that point
                            {
                                return returnValue;
                            }
                        }
                    }
                    else if ((row == 0) && (col == (maxCols - 1))) // top right corner
                    {
                        for (int i{0}; i < maxCols; i++)
                        {
                            if (boardMap[row][col] != boardMap[i][(maxCols - 1) - i])
                            {
                                break;
                            }

                            if (i == maxCols - 1)
                            {
                                return returnValue;
                            }
                        }
                    }

                    // check horizontals using left edge of board to start
                    if (((row == 0) && (col == 0)) || ((row == 1) && (col == 0)) || ((row == 2) && (col == 0))){
                        for (int i {0}; i < maxCols; i++){
                            if (boardMap[row][col] != boardMap[row][i]){
                                break;
                            }

                            if (i == maxCols - 1){
                                returnValue;
                            }
                        }
                    }

                    // check verticals using top edge of board to start
                    if (((row == 0) && (col == 0)) || ((row == 0) && (col == 1)) || ((row == 0) && (col == 2))){
                        for (int i {0}; i < maxCols; i++){
                            if (boardMap[row][col] != boardMap[i][col]){
                                break;
                            }

                            if (i == maxCols - 1){
                                returnValue;
                            }
                        }
                    }                    
                }
            }
        }

        return 0;
    }
};

int main()
{
    std::vector<Player> players;

    Player _player1('X');
    Player _player2('O');

    players.push_back(_player1);
    players.push_back(_player2);

    Board _board(players);

    _board.promptWelcome();

    while (!_board.getGameOver())
    {
        _board.displayBoard();
        _board.promptPlayer();
    }
    return 0;
}