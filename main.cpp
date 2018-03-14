/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#include <iostream>
#include <string>
#include <stdexcept>
#include "game.hpp"

using std::string;
using std::cout;
using std::endl;
using std::cout;
using std::invalid_argument;

/* ------------------------------------------------------------------------- *\
 *                                  main                                     *
\* ------------------------------------------------------------------------- */
int main(int argc, char** argv)
{
    //Check number of argument.
    if(argc==3)
    {
        string mapPath = argv[1];
        string posPath = argv[2];
        //Creating a sample game and play with it.
        Game game(mapPath,posPath);
        if(game.play())
        {
            cout << " ===================" <<endl;
            cout << "=====! YOU WON !=====" <<endl;
            cout << " ===================" <<endl<<endl;
        }
        else
        {
            cout << " ====================" <<endl;
            cout << "=====! YOU LOST !=====" <<endl;
            cout << " ====================" <<endl<<endl;
        }
        //Deleting board!
        game.deleteBoard();
    }
    else if (argc ==2)
    {
        cout <<"There is no position text file given in argument. Displaying the board." <<endl;
        string mapPath = argv[1];
        Game game(mapPath);
        //Display the board
        game.printBoard();
        //deleting it
        game.deleteBoard();
    }
    else
    {
        throw invalid_argument("Escape can only take 1 or 2 arguments: the path the map text file to display the map or the path the map text file and the path to the start/end position to play!");
    }
    return 0;
}
