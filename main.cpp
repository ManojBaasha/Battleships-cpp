
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <sstream>

bool StreamOnlyContainsWhiteSpace(std::istream &stream);
int getValidInt(const std::string &prompt);
char getValidChar(const std::string &prompt);
int getIntBetween(const std::string &prompt, int min, int max);
int getPositiveInt(const std::string &prompt);

class Board
{
public:
    Board(int numRows, int numCols, char blankChar);
    Board(int dimensions, char blankChar);

    int getNumRows() const;
    int getNumCols() const;

    void display() const;

    void placePieceAt(int row, int col, char piece);
    bool isBlank(int row, int col) const;

    const char &at(int row, int col) const;
    char &at(int row, int col);

    std::vector<std::string> boardContents;
    const char blankChar;

    char getPieceAt(int row, int col) const;

    friend class Player;
};

class Player
{
public:
    Player(int playerNum);
    void display_players();

public:
    std::string name;
    char playernum;
};

void Player::display_players()
{
    std::cout << "Player 1: " << name << std::endl;
    std::cout << "Player number: " << playernum << std::endl;
}

Player::Player(int playerNum)
{
    std::cout << "Player " << playerNum << " please enter your name: ";
    std::getline(std::cin, name);
    playernum = playerNum;
}

Board::Board(int numRows, int numCols, char blankChar) : boardContents(numRows, std::string(numCols, blankChar)),
                                                         blankChar(blankChar)
{
}

Board::Board(int dimensions, char blankChar) : Board(dimensions, dimensions, blankChar)
{
}

void Board::display() const
{
    std::cout << "  ";
    for (int i = 0; i < getNumCols(); ++i)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    int rowNum = 0;
    for (const auto &row : boardContents)
    {
        std::cout << rowNum << ' ';
        for (const auto &piece : row)
        {
            std::cout << piece << ' ';
        }
        std::cout << std::endl;
        ++rowNum;
    }
}

int Board::getNumCols() const
{
    return boardContents.front().size();
}

int Board::getNumRows() const
{
    return boardContents.size();
}

char Board::getPieceAt(int row, int col) const
{
    return boardContents[row][col];
}

void Board::placePieceAt(int row, int col, char piece)
{
    boardContents.at(row).at(col) = piece;
}

bool Board::isBlank(int row, int col) const
{
    return at(row, col) == blankChar;
}

const char &Board::at(int row, int col) const
{
    return boardContents.at(row).at(col);
}

char &Board::at(int row, int col)
{
    return boardContents.at(row).at(col);
}

int getValidInt(const std::string &prompt)
{
    std::string lineRead;
    int val;
    bool readSuccessful = false;
    do
    {
        std::cout << prompt;
        std::getline(std::cin, lineRead);                          // grab the line
        std::stringstream lineParser(lineRead);                    // put it into a string stream so we can parse it
        lineParser >> val;                                         // read what we want
        readSuccessful = StreamOnlyContainsWhiteSpace(lineParser); // check that there isn't anything left
    } while (!readSuccessful);                                     // keep asking until they give me what I want
    return val;
}

char getValidChar(const std::string &prompt)
{
    std::string lineRead;
    char val;
    bool readSuccessful = false;
    do
    {
        std::cout << prompt;
        std::getline(std::cin, lineRead);                          // grab the line
        std::stringstream lineParser(lineRead);                    // put it into a string stream so we can parse it
        lineParser >> val;                                         // read what we want
        readSuccessful = StreamOnlyContainsWhiteSpace(lineParser); // check that there isn't anything left
    } while (!readSuccessful);                                     // keep asking until they give me what I want
    return val;
}

/**
 * Check that the stream is empty or contains only white space
 * @param stream: The stream to read from which is modified by the read
 * @return
 */
bool StreamOnlyContainsWhiteSpace(std::istream &stream)
{
    char c = '!';
    if (!stream)
    {                 // if you can't read from the stream
        return false; // something is wrong with the stream
    }
    else
    {
        stream >> c; // attempt to read a nonwhitespace character
        // if the stream is bad it means we failed to read
        // and we should since there shouldn't be anything left
        return !stream;
    }
}

int getPositiveInt(const std::string &prompt)
{
    int val;
    do
    {
        val = getValidInt(prompt);
    } while (val < 0);
    return val;
}

int getIntBetween(const std::string &prompt, int min, int max)
{
    int val;
    do
    {
        val = getValidInt(prompt);
    } while (!(val >= min and val <= max));
    return val;
}

bool checkIfValidMove(int row, int col, int numRows, int numCols)
{
    return (row >= 0 and row < numRows and col >= 0 and col < numCols);
}

bool ship_area_empty(Board &board, int row, int col, int numRows, int numCols)
{
    for (int i = row; i < row + numRows; ++i)
    {
        for (int j = col; j < col + numCols; ++j)
        {
            if (!board.isBlank(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

char getOrientation(char orientation, Player &player1, std::vector<std::pair<char, int>> &ships, int i)
{
    orientation = getValidChar(player1.name + ", do you want to place " + ships[i].first + " horizontally or vertically?\nEnter h for horizontal or v for vertical\nYour choice: ");
    if (orientation == 'h' || orientation == 'v' || orientation == 'H' || orientation == 'V')
    {
        return orientation;
    }
    else
    {
        return getOrientation(orientation, player1, ships, i);
    }
}

int main(int argc, char const *argv[])
{
    // read file
    std::fstream in(argv[1]);
    int numRows, numCols;
    int no_of_ships;
    std::vector<std::pair<char, int>> ships;
    int total_ship_bits = 0;

    in >> numRows;
    in >> numCols;
    in >> no_of_ships;

    for (int i = 0; i < no_of_ships; ++i)
    {
        char ship;
        int size;
        in >> ship >> size;
        total_ship_bits += size;
        ships.push_back(std::make_pair(ship, size));
    }

    Board board1(numRows, numCols, '*');
    Board board2(numRows, numCols, '*');

    // player 1
    Player player1(1);
    board1.display();

    for (int i = 0; i < no_of_ships; ++i)
    {
        char orientation;
        int row, col;
        int yes = 0;
        while (true)
        {
            orientation = getOrientation(orientation, player1, ships, i);
            if (orientation == 'h' || orientation == 'H')
            {
                std::cout << player1.name + ", enter the row and column you want to place " + ships[i].first + ", which is " + std::to_string(ships[i].second) + " long, at with a space in between row and col: ";
                std::cin >> row >> col;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (row == 0 && col > 1000)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (checkIfValidMove(row, col, numRows, numCols) && checkIfValidMove(row, col + ships[i].second - 1, numRows, numCols))
                {
                    for (int j = 0; j < ships[i].second; ++j)
                    {
                        board1.placePieceAt(row, col + j, ships[i].first);
                    }
                    board1.display();
                    yes = 1;
                    break;
                }
            }
            if (orientation == 'v' || orientation == 'V')
            {
                std::cout << player1.name + ", enter the row and column you want to place " + ships[i].first + ", which is " + std::to_string(ships[i].second) + " long, at with a space in between row and col: ";
                std::cin >> row >> col;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (row == 0 && col > 1000)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (checkIfValidMove(row, col, numRows, numCols) && checkIfValidMove(row + ships[i].second - 1, col, numRows, numCols))
                {
                    for (int j = 0; j < ships[i].second; ++j)
                    {
                        board1.placePieceAt(row + j, col, ships[i].first);
                    }
                    board1.display();
                    yes = 1;
                    break;
                }
            }
            if (yes == 1)
            {
                break;
            }
        }
    }

    // player 2
    Player player2(2);
    board2.display();
    for (int i = 0; i < no_of_ships; ++i)
    {
        char orientation;
        int row, col;
        int yes = 0;
        while (true)
        {
            orientation = getOrientation(orientation, player2, ships, i);
            if (orientation == 'h' || orientation == 'H')
            {
                std::cout << player2.name + ", enter the row and column you want to place " + ships[i].first + ", which is " + std::to_string(ships[i].second) + " long, at with a space in between row and col: ";
                std::cin >> row >> col;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (row == 0 && col > 1000)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (checkIfValidMove(row, col, numRows, numCols) && checkIfValidMove(row, col + ships[i].second - 1, numRows, numCols))
                {
                    for (int j = 0; j < ships[i].second; ++j)
                    {
                        board2.placePieceAt(row, col + j, ships[i].first);
                    }
                    board2.display();
                    yes = 1;
                    break;
                }
            }
            if (orientation == 'v' || orientation == 'V')
            {
                std::cout << player2.name + ", enter the row and column you want to place " + ships[i].first + ", which is " + std::to_string(ships[i].second) + " long, at with a space in between row and col: ";
                std::cin >> row >> col;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (row == 0 && col > 1000)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if (checkIfValidMove(row, col, numRows, numCols) && checkIfValidMove(row + ships[i].second - 1, col, numRows, numCols))
                {
                    break;
                }
                for (int j = 0; j < ships[i].second; ++j)
                {
                    board2.placePieceAt(row + j, col, ships[i].first);
                }
                board2.display();
                yes = 1;
                break;
            }
            if (yes == 1)
            {
                break;
            }
        }
    }

    Board firingboard1(numRows, numCols, '*');
    Board firingboard2(numRows, numCols, '*');

    int player1_bits = total_ship_bits;
    int player2_bits = total_ship_bits;

    int count1 = 0;
    int count2 = 0;

    // game
    while (true)
    {
        // player 1
        std::cout << player1.name + "'s Firing Board" << std::endl;
        firingboard1.display();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << player1.name + "'s Placement Board" << std::endl;
        board1.display();
        int row, col = 0;

        while (true)
        {
            // print vector ships
            char a, b;
            std::cout << player1.name + ", where would you like to fire?\nEnter your attack coordinate in the form row col: ";
            std::cin >> a >> b;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if a and b are integers
            if (!std::isdigit(a) && !std::isdigit(b))
            {
                continue;
            }
            row = a - '0';
            col = b - '0';

            if (checkIfValidMove(row, col, numRows, numCols) && firingboard1.getPieceAt(row, col) == '*')
            {
                break;
            }
            std::cout << player1.name + "'s Firing Board" << std::endl;
            firingboard1.display();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << player1.name + "'s Placement Board" << std::endl;
            board1.display();
        }
        char ship;

        if (board2.getPieceAt(row, col) != '*')
        {
            ship = board2.getPieceAt(row, col);
            firingboard1.placePieceAt(row, col, 'X');
            board2.placePieceAt(row, col, 'X');
        }
        else if (board2.getPieceAt(row, col) == '*')
        {
            ship = '*';
            firingboard1.placePieceAt(row, col, 'O');
            board2.placePieceAt(row, col, 'O');
        }

        std::cout << player1.name + "'s Firing Board" << std::endl;
        firingboard1.display();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << player1.name + "'s Placement Board" << std::endl;
        board1.display();

        if (ship != '*')
        {
            std::cout << player1.name + " hit " << player2.name << "'s " << ship << "!" << std::endl;
            player2_bits -= 1;
            ships[ship].second -= 1;
            count1 += 1;
            if (count1 == 2)
            {
                std::cout << player1.name + " destroyed " << player2.name << "'s " << ship << "!" << std::endl
                          << std::endl;
            }
        }
        else if (ship == '*')
        {
            std::cout << "Missed." << std::endl;
            std::cout << std::endl;
        }
        // check win
        if (player2_bits == 0)
        {
            std::cout << player1.name + " won the game!";
            std::cout << std::endl;
            break;
        }

        std::cout << player2.name + "'s Firing Board" << std::endl;
        firingboard2.display();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << player2.name + "'s Placement Board" << std::endl;
        board2.display();

        while (true)
        {
            char a, b;
            std::cout << player2.name + ", where would you like to fire?\nEnter your attack coordinate in the form row col: ";
            std::cin >> a >> b;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (!std::isdigit(a) && !std::isdigit(b))
            {
                continue;
            }
            row = a - '0';
            col = b - '0';
            if (checkIfValidMove(row, col, numRows, numCols) && firingboard2.getPieceAt(row, col) == '*')
            {
                break;
            }
            std::cout << player2.name + "'s Firing Board" << std::endl;
            firingboard2.display();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << player2.name + "'s Placement Board" << std::endl;
            board2.display();
        }

        if (board1.getPieceAt(row, col) != '*')
        {
            ship = board1.getPieceAt(row, col);
            firingboard2.placePieceAt(row, col, 'X');
            board1.placePieceAt(row, col, 'X');
        }
        else if (board1.getPieceAt(row, col) == '*')
        {
            ship = '*';
            firingboard2.placePieceAt(row, col, 'O');
            board1.placePieceAt(row, col, 'O');
        }

        std::cout << player2.name + "'s Firing Board" << std::endl;
        firingboard2.display();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << player2.name + "'s Placement Board" << std::endl;
        board2.display();

        if (ship != '*')
        {
            std::cout << player2.name + " hit " << player1.name << "'s " << ship << "!" << std::endl;
            player1_bits -= 1;
            // ships[ship].second -= 1;
            std::cout << std::endl;
            // std::cout << ships[ship].second << std::endl;

            if (ships[ship].second == 0)
            {
                std::cout << player2.name + " destroyed " << player1.name << "'s " << ship << std::endl;
                std::cout << std::endl;
            }
        }
        else if (ship == '*')
        {
            std::cout << "Missed." << std::endl;
            std::cout << std::endl;
        }

        if (player1_bits == 0)
        {
            std::cout << player2.name + " won the game!";
            break;
        }
    }
}