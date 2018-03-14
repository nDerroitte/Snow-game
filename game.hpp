/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "coord.hpp"
#include "board.hpp"

using std::string;              using std::cerr;
using std::ios;                 using std::endl;
using std::vector;              using std::istream;
using std::ifstream;            using std::cin;
using std::invalid_argument;    using std::exit;

/* ------------------------------------------------------------------------- *\
 *                       constants used by the game class                    *
\* ------------------------------------------------------------------------- */

const char HINT_INPUT  = 'h';
const char EXIT_INPUT  = 'e';
const char LEFT_INPUT  = 'l';
const char RIGHT_INPUT = 'r';
const char UP_INPUT    = 'u';
const char DOWN_INPUT  = 'd';
const char HELP_INPUT  = 'H';
const char YES_INPUT   = 'y';
const char NO_INPUT    = 'n';
const char CHANGE_LVL  = 'c';

/* ------------------------------------------------------------------------- *\
 *                              Game Class                                   *
\* ------------------------------------------------------------------------- */

class Game
{

    public:
    //----------------------------- Constructor --------------------------------
        Game(){};
        Game(string&);
        Game(string&, string&);
    //-------------------------- Public Member function ------------------------
        /* setExit
        *
        *  Set the exit of the escape game!
        *
        *   -INPUT :    const Coord& that must be on one of the edge of the map!
        *   -OUTOUT:    true if the given exit is correct and placed
        *              false otherwise
        */
        bool setExit(const Coord&);
    
        /*  setStart
         *
         *  Set the start of the escape game!
         *
         *   -INPUT :    const Coord& that must be a valid winning position for the map
         *   -OUTOUT:    true if the given start is correct, winnable and placed
         *              false otherwise
         */
        bool setStart(const Coord&);
    
        /*  startPosition
         *
         *  Change the element type of the counter to print it.
         *
         *   -INPUT :    const Coord& the position of the counter
         */
        void startPosition();
    
        /* printBoard
         *
         * Print the current map on the standard input stream.
         */
        void printBoard();
    
        /* deleteBoard
         *
         * Delete the dynamicly allowed Board playArea.
         * This function is called in our main. It could have been called at the end of the play function if we weren't using a personnalise main.
         */
        void deleteBoard();
    
        /* play
         *
         * The main logic of the game : check the input given by the player and act correspondly
         *
         *   -INPUT: the input and output stream.
         *   -OUTPUT : false if the game is quit/lose
         *            true if the game is won
         */
        bool play(istream& is = cin, ostream& os = cout);
    
    private:
    //-------------------------- Private variables -----------------------------
        unsigned int nbMoves;
        Coord* counter;
        Coord* start;
        Coord* exit;
        Board* playArea;
    //-------------------------- Private member functions -----------------------
    /* boardInit
     *
     * Read the input file and initialise the playArea
     *
     *   -INPUT: the path to the map file
     *
     *   -throw invalid_argument
     */
    void boardInit(string&);
    
    /* checkEdgeLine
     *
     * Verify if the given edge line is filled with OBSTACLES(#)
     *
     *   -INPUT: the edge line to check
     *
     *   -throw invalid_argument
     */
    void checkEdgeLine(string&);
    
    /* checkLine
     *
     * Verify if the given  line is filled with the allowed elements (#.), and has the good size
     *
     *   -INPUT: the edge line to check
     *   
     *   -throw invalid_argument
     */
    void checkLine(string&, unsigned int);
};


#endif /* game_hpp */
