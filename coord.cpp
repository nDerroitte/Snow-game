/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#include <iostream>
#include "coord.hpp"

/* ------------------------------------------------------------------------- *\
 *                              Constructors                                 *
\* ------------------------------------------------------------------------- */

Coord::Coord ( int inputHeight,  int inputWidth)
: height(inputHeight), width(inputWidth){}
Coord::Coord (unsigned int inputHeight, unsigned int inputWidth, char inputElement)
: height(inputHeight), width(inputWidth),element(inputElement){}

/* ------------------------------------------------------------------------- *\
 *                          Public Member function                           *
\* ------------------------------------------------------------------------- */

unsigned int Coord::getHeight() const
{
    return height;
}
unsigned int Coord::getWidth() const
{
    return width;
}
char Coord::getElement() const
{
    return element;
}

Coord* Coord::getNodeLeft() const
{
    return nodeLeft;
}

Coord* Coord::getNodeRight() const
{
    return nodeRight;
}

Coord* Coord::getNodeUp() const
{
    return nodeUp;
}

Coord* Coord::getNodeDown() const
{
    return nodeDown;
}

void Coord::setElement(char inputElement)
{
    element = inputElement;
}

void Coord::setNodeLeft(Coord* coord)
{
    nodeLeft = coord;
}

void Coord::setNodeRight(Coord* coord)
{
    nodeRight = coord;
}

void Coord::setNodeUp(Coord* coord)
{
    nodeUp = coord;
}

void Coord::setNodeDown(Coord* coord)
{
    nodeDown = coord;
}

/* ------------------------------------------------------------------------- *\
 *                      non-member operator overloading                      *
\* ------------------------------------------------------------------------- */
bool operator==(const Coord& coordA, const Coord& coordB)
{
    if(coordA.element == coordB.element && coordA.height == coordB.height && coordA.width == coordB.width)
        return true;
    return false;
}

ostream& operator<<(ostream& os, const Coord& currentCoord)
{
    os << currentCoord.element;
    return os;
}
