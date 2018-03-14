/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#ifndef coord_hpp
#define coord_hpp

#include <iostream>
#include <string>

using std::string;
using std::ostream;

/* ------------------------------------------------------------------------- *\
 *                       constants used by the Coord class                   *
\* ------------------------------------------------------------------------- */

const char    ICE = '.';
const char    OBSTACLE = '#';
const char    COUNTER = '0';
const string  ALLOWEDELEMENT = ".#";
/* ------------------------------------------------------------------------- *\
 *                              Coord Class                                  *
\* ------------------------------------------------------------------------- */

class Coord
{
    //------------------------------- Friend -----------------------------------
    friend ostream& operator<< (ostream&, const Coord&);
    friend bool operator==(const Coord& , const Coord&);

    public:
    //----------------------------- Constructor --------------------------------
        Coord(){};
        Coord(int, int);
        Coord(unsigned int, unsigned int, char);
    //-------------------------- Public Member function ------------------------
        /* getHeight
         *
         *  Return the value of the private variable height
         *
         */
        unsigned int  getHeight()  const;
        /* getWidth
         *
         *  Return the value of the private variable width
         *
         */
        unsigned int  getWidth()   const;
        /* getElement
         *
         *  Return the value of the private variable element
         *
         */
        char getElement() const;
        /* getNodeLeft/Right/Up/Down
         *
         *  Return the first node on the left/right/up/down of the current Coord object.
         *
         */
        Coord* getNodeLeft()   const;
        Coord* getNodeRight()  const;
        Coord* getNodeUp()     const;
        Coord* getNodeDown()   const;
        /* setElement
         *
         * Change the value of the element private variable. Since this function is public, element
         * could have been public as well. We keep it private for a better lisibilty.
         *
         *    -INPUT  : the element to set.
         */
        void setElement(char);
    
        /* setNodeLeft/Right/Up/Down
         *
         *  Link the node on the left/right/up/down with the current Coord object.
         *
         *    -INPUT : the node to link with the current Coord object
         */
        void setNodeLeft (Coord*);
        void setNodeRight(Coord*);
        void setNodeUp   (Coord*);
        void setNodeDown (Coord*);
    
    private:
    //-------------------------- Private variables -----------------------------
        unsigned int height;
        unsigned int width;
        char element;
        Coord* nodeLeft;
        Coord* nodeRight;
        Coord* nodeUp;
        Coord* nodeDown;

};
/* ------------------------------------------------------------------------- *\
 *                      non-member operator overloagind                      *
\* ------------------------------------------------------------------------- */
// << operator overload
//
// Allow to print on the output stream a line Object using the << operator of an ostream. (ex : cout)
ostream& operator<<(ostream& os, const Coord& currentCoord);

// == operator overload
//
// Allow to compare two Coord. The operatore will check the egality of all the 3 variables
bool operator==(const Coord& coordA, const Coord& coordB);

#endif /* coord_hpp */
