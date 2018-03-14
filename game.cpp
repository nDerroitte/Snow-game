/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#include "game.hpp"

/* ------------------------------------------------------------------------- *\
 *                              Constructors                                 *
\* ------------------------------------------------------------------------- */
Game::Game(string& fileName)
{
    boardInit(fileName);
}
Game::Game(string& fileNameMap, string& fileNamePosition)
{
    boardInit(fileNameMap);
    //We open the postfile in reading mode.
    ifstream in(fileNamePosition,ios::in);
    //Check if we can open the file
    if(!in)
        throw invalid_argument ("Error while opening the position text file.");
    //Reading the if there is enough arguments
    unsigned int tmp;
    unsigned int i = 0;
    //get the number of unsigned integer in the file
    while (in>> tmp) ++i;
    if (i!=4)
        throw invalid_argument ("The pos text file must only have 4 integers.");
    in.clear();
    in.seekg(0,ios::beg);
    //if there is 4 unsigned int we try to set the End and the Start
    unsigned int exitHeight, exitWidth, startHeight, startWidth;
    in >>exitHeight>>exitWidth>>startHeight>>startWidth;
    in.close();
    //Check if the input end is in the map and if the exit created is valid
    if(exitHeight>= playArea->getNbLines()|| exitWidth>= playArea->getNbColumns() ||!setExit(*playArea->getCoord(exitHeight, exitWidth)))
    {
        cerr <<"The exit is incorrect!" <<endl;
        std::exit(EXIT_FAILURE);
    }
    //Check if the input start is in the map and if the start created is valid
    if(startHeight>= playArea->getNbLines()|| startWidth>= playArea->getNbColumns() ||!setStart(*playArea->getCoord(startHeight, startWidth)))
    {
        cerr<<"The start is incorrect! "<<endl;
        std::exit(EXIT_FAILURE);
    }
    else
        startPosition();
    
}
/* ------------------------------------------------------------------------- *\
 *                          Public Member function                           *
\* ------------------------------------------------------------------------- */
bool Game::setExit(const Coord& inputExit)
{
    //Check arguments :
    if(inputExit.getHeight()>= playArea->getNbLines() ||
       inputExit.getWidth()>= playArea->getNbColumns())
    {
        cerr <<"Invalid exit : the coordonate of the exit are out of the map!"<<endl;
        return false;
    }
    exit = playArea->getCoord(inputExit.getHeight(), inputExit.getWidth());
    exit->setElement(ICE);
    
    //First linking. Eventually, one of these will be change if the exit is correct
    exit->setNodeLeft(exit);
    exit->setNodeRight(exit);
    exit->setNodeUp(exit);
    exit->setNodeDown(exit);
    
    //As exit will replace an OBSTACLE which are not linked, we need to re-do the linking process.
    if(inputExit.getHeight()== 0)
    {
        for(unsigned int i=0; i<playArea->getNbLines(); i++)
        {
            if(playArea->getCoord(i,exit->getWidth())->getElement()==OBSTACLE)
            {
                if(i==1) //We stopped directly: the exit is blocked
                {
                    cerr << "The exit is blocked!"<<endl;
                    return false;
                }
                exit->setNodeDown(playArea->getCoord(i-1,exit->getWidth()));
                break;
            }
            playArea->getCoord(i,exit->getWidth())->setNodeUp(exit);
        }
    }
    else if (inputExit.getHeight() == playArea->getNbLines()-1)
    {
        for( int i=inputExit.getHeight(); i>=0; i--)
        {
            if(playArea->getCoord(i,exit->getWidth())->getElement()==OBSTACLE)
            {
                if(i==static_cast<int>(inputExit.getHeight()-1)) //We stopped directly: the exit is blocked
                {
                    cerr << "The exit is blocked!"<<endl;
                    return false;
                }
                exit->setNodeDown(playArea->getCoord(i+1,exit->getWidth()));
                break;
            }
            playArea->getCoord(i,exit->getWidth())->setNodeDown(exit);
        }
    }
    else if (inputExit.getWidth()==0)
    {
        for(unsigned int j=0; j<playArea->getNbColumns(); j++)
        {
            if(playArea->getCoord(exit->getHeight(),j)->getElement()==OBSTACLE)
            {
                if(j==1) //We stopped directly: the exit is blocked
                {
                    cerr << "The exit is blocked!"<<endl;
                    return false;
                }
                exit->setNodeLeft(playArea->getCoord(exit->getHeight(),j-1));
                break;
            }
            playArea->getCoord(exit->getHeight(),j)->setNodeLeft(exit);
        }
    }
    else if (inputExit.getWidth()==playArea->getNbColumns()-1)
    {
        for( int j=inputExit.getWidth(); j>=0; j--)
        {
            if(playArea->getCoord(exit->getHeight(),j)->getElement()==OBSTACLE)
            {
                if(j==static_cast<int>(inputExit.getWidth()-1)) //We stopped directly: the exit is blocked
                {
                    cerr << "The exit is blocked!"<<endl;
                    return false;
                }
                exit->setNodeRight(playArea->getCoord(exit->getHeight(),j+1));
                break;
            }
            playArea->getCoord(exit->getHeight(),j)->setNodeRight(exit);

        }
    }
    else
    {
        cerr << "The exit must be on one of the edges!"<<endl;
        return false;
    }
    return true;
}
bool Game::setStart(const Coord& inputStart)
{
    //Check arguments :
    if(inputStart.getHeight()>= playArea->getNbLines()||
       inputStart.getWidth()>= playArea->getNbColumns())
    {
        cerr <<"Invalid exit : the coordonate of the exit are out of the map!"<<endl;
        return false;
    }
    //Check if the start isn't on a obstacle
    if(playArea->getCoord(inputStart.getHeight(), inputStart.getWidth())->getElement() == OBSTACLE)
    {
        cerr << "The start position can not be on a obstacle!"<<endl;;
        return false;
    }
    //Check is the start is winnable
    start = playArea->getCoord(inputStart.getHeight(), inputStart.getWidth());
    vector<Coord*> wayOut = playArea->pathFinding(*start, *exit);
    if(!wayOut.size())
    {
        cerr<<"The start position doesn't allow you to win the game.." <<endl;
        return false;
    }
    return true;
}

void Game::startPosition()
{
    counter = start;
    counter->setElement(COUNTER);
}

void Game::printBoard()
{
    playArea->printBoard();
}

void Game::deleteBoard()
{
    playArea->deleteMap();
    delete playArea;
}

bool Game::play(istream& is , ostream& os)
{
    vector<Coord*> wayOut;
    char input;
    unsigned int nbMovesLeft = 0;
    int difficulty =1;
    os << " ==================" <<endl;
    os << "=====! ESCAPE !=====" <<endl;
    os << " ==================" <<endl<<endl;
    os << "The difficulty is set to : easy. That means you have an infinite number of moves to win the game! To change difficulty, press 'c'" <<endl;
    os << "Also, if you need Help on how to play : Press H !" <<endl<<endl;

    while(true)//Gaming loop.
    {
        //Display the map
        os<<*playArea <<endl;
        //Check if the player has win
        if(counter==exit)
            return true;
        //Check if the player has still some moves left (difficulty >=1)
        if(difficulty!=1)
        {
            if(nbMovesLeft ==0)
            {
                os <<"You have no move left!"<<endl;
                return false;
            }
        }
        //Update the wayOut
        wayOut = playArea->pathFinding(*counter,*exit);
        if(wayOut.size())
        {
            os << "Minimal moves needed to end : " << (wayOut.size()-1) <<endl;
            os << "Number of moves done: " << nbMoves << std::endl;
            if(difficulty!=1)
                os << "Number of moves left: " << nbMovesLeft << std::endl;
        }
        else
        {
            os << "Impossible to win.. "  << endl;
            os << "Number of moves done: " << nbMoves << endl;
            return false;
        }
        os << "What do you want to do next?"<<endl<<" -> ";
        is >> input;
        if(input == HELP_INPUT)
        {
            os<< "The goal is to escape the rectangle play area."<< endl
            <<"Press 'u','d','l','r' to move the curseur (0). It will not stop until it hits a wall."<<endl
            <<"Press 'h' to perform the better move in your current position. This operation costs 2 moves!" << endl
            <<"Press 'c' to change the difficulty at the start of the game! Once you started the game, you cannot change it back.." <<endl
            <<"Press 'e' to quit the game."<<endl;
            os << "What do you want to do next?"<<endl<<" -> ";
            is >> input;
        }
        if (input == CHANGE_LVL)
        {
            if(nbMoves!=0)
                os <<"You can only change difficulty at the start of the game!"<<endl;
            else
            {
                os <<"To put the difficulty to easy, press 1"<<endl
                <<   "To put the difficulty to medium, press 2"<<endl
                <<"To put the difficulty to easy, press 3"<<endl;
                is>>difficulty;
                if(difficulty != 1 && difficulty!=2 && difficulty !=3)
                {
                    os << "The difficulty is the set to his default value : easy"<<endl;
                    difficulty = 1;
                }
                if (difficulty ==2)
                {
                    os <<"You are now playing in medium mode"<<endl;
                    nbMovesLeft = static_cast<unsigned int>((wayOut.size()-1)+(wayOut.size()/2));
                }
                if (difficulty==3)
                {
                    os <<"You are now playing in hard mode"<<endl;
                    nbMovesLeft = static_cast<unsigned int>((wayOut.size()-1));
                }
            }
            continue;
        }
        if(input == EXIT_INPUT)
        {
            os<< "Are you sure you want to exit the game? (y/n)"<< endl;
            is >> input;
            if ( input == 'y')
                return false;
            else
            {
                os << "We continue then! " << endl;
            }
        }
        counter->setElement(ICE);
        if(input==HINT_INPUT)
        {
            counter = wayOut[1]  ;
            nbMoves = nbMoves + 2;
            counter->setElement(COUNTER);
            if(difficulty!=1)
                nbMovesLeft-=2;
            continue;
        }
        nbMoves++;
        if(difficulty!=1)
            nbMovesLeft--;
        if(input==LEFT_INPUT)
            counter = counter->getNodeLeft();
        if(input==RIGHT_INPUT)
            counter = counter->getNodeRight();
        if(input==UP_INPUT)
            counter = counter->getNodeUp();
        if(input==DOWN_INPUT)
            counter = counter->getNodeDown();
        counter->setElement(COUNTER);
    }
}
/* ------------------------------------------------------------------------- *\
 *                          Private Member function                          *
\* ------------------------------------------------------------------------- */
void Game::boardInit(string& fileName)
{
    //We open the file in reading mode.
    ifstream in(fileName,ios::in);
    //Check if we can open the file
    if(!in)
        throw invalid_argument ("Error while opening the map text file.");
    
    string currentLine;
    vector<string> lineContainer;
    unsigned int nbLines   = 0;
    unsigned int nbColumns = 0;
    //Reading the map and memorising int in a bidimentionnal matrix of char.
    while(getline(in, currentLine))
    {
        //We don't memorise empty line
        if (currentLine.empty())
            continue;
        //We get rid of the last character
        if(currentLine.back() == '\r' || currentLine.back() == '\n')
            currentLine.pop_back();
        if(nbLines==0)
        {
            checkEdgeLine(currentLine);
            nbColumns = static_cast <unsigned int>(currentLine.size());
        }
        checkLine(currentLine, nbColumns);
        lineContainer.push_back(currentLine);
        nbLines ++;
    }
    if (!currentLine.empty())
        checkEdgeLine(currentLine);
    nbMoves = 0;
    //Creating the map from the bidimentionnal matrix of char
    playArea = new Board(nbLines,nbColumns,lineContainer);
    in.close();
}

void Game::checkEdgeLine (string& line)
{
    if ( line.empty())
        throw invalid_argument ("Lines can not be empty! Check your input file.");
    if (line.find_first_not_of(OBSTACLE) != string::npos)
        throw invalid_argument("The edge lines must be filled with obstacles (#).");
}

void Game::checkLine(string& line, unsigned int nbColumns)
{
    if ( line.empty())
        throw invalid_argument ("Lines can not be empty! Check your input file.");
    if (line.size() != nbColumns)
        throw invalid_argument ("Every line must be the same size!");
    if (line.find_first_not_of(ALLOWEDELEMENT) != string::npos)
        throw invalid_argument("Invalid character. All lines must be filled with '.' or '#'");
}














