
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
    void print_solution();
};

class Ships{

    public:
    std::vector<std::pair<char, int>> ships;
    Ships();
};

Ships::Ships(){
    int ship_count;
    cin >> ship_count;
    
    for(int i = 0; i < ship_count; i++){
        char ship_type;
        int ship_size;
        cin >> ship_type >> ship_size;
        ships.push_back(std::make_pair(ship_type, ship_size));
    }

}

Game::Game()
{

    // inputting row and col
    cin >> row;
    cin >> col;

    // creating boards
    Board player1(row, col);
    Board player2(row, col);
    
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
    cout << "Display Board" << endl;
    cout << "  ";
    for (int i = 0; i < display.size(); ++i)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < display.size(); i++)
    {
        cout << i << ' ';
        for (int j = 0; j < display[i].size(); j++)
        {
            cout << display[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::print_solution()
{
    cout << "Solution Board" << endl;
    cout << "  ";
    for (int i = 0; i < solution.size(); ++i)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < solution.size(); i++)
    {
        cout << i << ' ';
        for (int j = 0; j < solution[i].size(); j++)
        {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{   //FIXME : add input file
    Game game();
}