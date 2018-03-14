/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <vector>
#include <queue>
#include "coord.hpp"

using std::vector;      using std::cout;        using std::pair;
using std::ostream;     using std::endl;        using std::queue;

/* ------------------------------------------------------------------------- *\
 *                              Game Class                                   *
\* ------------------------------------------------------------------------- */

class Board
{
    //------------------------------- Friend -----------------------------------
    friend ostream& operator<<(ostream&, const Board&);

    public:
    //----------------------------- Constructor --------------------------------
        Board(){};
        Board(unsigned int,unsigned int,vector<string>&);
    //-------------------------- Public Member function ------------------------
        /* getCoord
         *
         *  Return the corresponding coord in the private map.
         *
         *   -INPUT :    unsigned int height, width
         *   -OUTOUT:    the corresponding coord.
         */
        Coord* getCoord(unsigned int, unsigned int);
    
        /* getNbLines
         *
         *  Return the number of lines of the  map.
         *
         *   -OUTOUT:   the number of lines
         */
        unsigned int getNbLines();
    
        /* getNbColumns
         *
         *  Return the number of columns of the  map.
         *
         *   -OUTOUT:   the number of columns
         */
        unsigned int getNbColumns();
    
        /*printBoard
         *
         * Print the current map on the standard input stream.
         */
        void printBoard();
    
        /* deleteBoard
         *
         * Delete the dynamicly allowed  bidimentionnal matrix. This function is called by deleteBoard()
         * at the end of the program.
         *
         */
        void deleteMap();

        /* pathFinding
         *
         * Implementation of the Breadth First Screach (BFS) algorithm in order to find the shortest way between the current nodes and the exit of the map. The implementation was based on the pseudo-code presented by P.Geurt during a lesson of "INFO0902-1 Structures des données et algorithmes" (Ulg -May 2016).
         *
         *   -INPUT  : the current node and the nodes to reach.
         *   -OUTPUT : Vector containing  the nodes linking the current and the node to reach by the                   
         *             shortest path.
         *
         */
        vector<Coord*> pathFinding(Coord&, Coord&);

    private:
    //-------------------------- Private variables -----------------------------
        unsigned int nbLines;
        unsigned int nbColumns;
        vector<vector<Coord*> > map;
    //-------------------------- private Member function ------------------------
        /* horizontalLinking
         *
         * Return in a pair of index containg the first obstacle at the left of a node and the first 
         * obstacle at the right of this node in a line.
         *
         *   -INPUT :    the line the index of the current node
         *   -OUTOUT:    pair filled with the corresponding index :
         *               first -> index of the first obstacle at the left of the node
         *               second-> index of the first obstacle at the right of the node
         */
        pair<unsigned int, unsigned int> horizontalLinking(string& , unsigned int );
    
        /* verticalLinking
         *
         * Return in a pair of index containg the first obstacle above a node and the first
         * obstacle under this node in a array of string.
         *
         *   -INPUT :    the line the index of the current node
         *   -OUTOUT:    pair filled with the corresponding index :
         *               first -> index of the first obstacle above the node
         *               second-> index of the first obstacle under the node
         */
        pair<unsigned int, unsigned int> verticalLinking(vector<string>& , unsigned int , unsigned int , unsigned int);
};
/* ------------------------------------------------------------------------- *\
 *                      non-member operator overloading                      *
\* ------------------------------------------------------------------------- */
// << operator overload
//
// Allow to print on the output stream a Board Object using the << operator of an ostream. (ex : cout)
ostream& operator<<(ostream& os, const Board& currentBoard);

#endif
