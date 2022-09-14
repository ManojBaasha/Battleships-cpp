
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <sstream>

using namespace std;

class Game
{
public:
    Game();

private:
    int row;
    int col;
};

class Board
{
public:
    std::vector<std::vector<std::string>> display;
    std::vector<std::vector<std::string>> solution;

    Board(int row, int col);
    void print_display();
    void print_solution();//havent done this yet
};

Game::Game()
{
    // TODO: Input file

    // inputting row and col
    cin >> row;
    cin >> col;

    // creating boards
    Board board(row, col);
    board.print_display();
}

Board::Board(int row, int col)
{
    // creating display board
    for (int i = 0; i < row; i++)
    {
        std::vector<std::string> row;
        for (int j = 0; j < col; j++)
        {
            row.push_back("*");
        }
        display.push_back(row);
    }

    // creating solution board
    for (int i = 0; i < row; i++)
    {
        std::vector<std::string> row;
        for (int j = 0; j < col; j++)
        {
            row.push_back("*");
        }
        solution.push_back(row);
    }
}

void Board::print_display()
{
    //TODO: add numbers to the board while displaying

    for (int i = 0; i < display.size(); i++)
    {
        for (int j = 0; j < display[i].size(); j++)
        {
            cout << display[i][j];
        }
        cout << endl;
    }
}

int main()
{
    Game game;
}