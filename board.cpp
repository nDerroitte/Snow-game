/* ------------------------------------------------------------------------- *\
 *                              Natan Derroitte
 *
 *          Object oriented programing project - Project 3 - 23/12/16
\* ------------------------------------------------------------------------- */
#include "board.hpp"
/* ------------------------------------------------------------------------- *\
 *                              Constructors                                 *
\* ------------------------------------------------------------------------- */
Board:: Board(unsigned int inputNbLines,unsigned int inputNbColumns,vector<string>& lineContainer):
nbLines(inputNbLines), nbColumns(inputNbColumns)
{
    //Creating the map of Coord
    map.resize(nbLines);
    for(unsigned int i=0; i<nbLines; i++)
    {
        map[i].resize(nbColumns);
        for(unsigned int j=0; j<nbColumns; j++)
            map[i][j] = new Coord(i,j,lineContainer[i][j]);
    }
    //Creating the nodes and linking process
    pair <unsigned int, unsigned int> widthObstacle;
    pair <unsigned int, unsigned int> heightObstacle;
    for(unsigned int i=0; i<nbLines; i++)
    {
        for(unsigned int j=0; j<nbColumns; j++)
        {
            if(lineContainer[i][j] == ICE)
            {
                widthObstacle = horizontalLinking(lineContainer[i],j);
                map[i][j]->setNodeLeft(map[i][widthObstacle.first]);
                map[i][j]->setNodeRight(map[i][widthObstacle.second]);
                heightObstacle = verticalLinking(lineContainer,i,j,nbLines);
                map[i][j]->setNodeUp(map[heightObstacle.first][j]);
                map[i][j]->setNodeDown(map[heightObstacle.second][j]);
            }
        }
    }
}
/* ------------------------------------------------------------------------- *\
 *                          Public Member function                           *
 * ------------------------------------------------------------------------- */
Coord* Board::getCoord(unsigned int height, unsigned int width)
{
    return map[height][width];
}

unsigned int Board::getNbLines()
{
    return nbLines;
}

unsigned int Board::getNbColumns()
{
    return nbColumns;
}

void Board::printBoard()
{
    cout << *this;
}

void Board::deleteMap()
{
    for(unsigned int i=0; i<nbLines; i++)
    {
        for(unsigned int j=0; j<nbColumns; j++)
            delete map[i][j];
    }
}

//Cfr the documentation concerning the chose of implementation.
vector<Coord*> Board::pathFinding(Coord& start, Coord& end)
{
    //wayNodes is a bi-dimentionnal matrix of pair. The frist element of the pair is the path between the concerning node and the start. The second element is a boolean value that check if the node where already visited or not.
    vector<vector<pair<vector<Coord*>,bool> > > wayNodes;
    Coord* currentNode = &start;
    
    //We want wayNodes bi-dimentionnal matrix to be the same size as the map
    wayNodes.resize(map.size());
    for(unsigned int i=0; i<nbLines; i++)
        wayNodes[i].resize(map[i].size());

    //We create a queue that will memorise the nodes we have to consider
    queue<Coord*> nodesToCheck;
    nodesToCheck.push(&start);
    
    //Initialisation of wayNodes.
    for(unsigned int i=0; i< nbLines; i++)
    {
        for(unsigned int j=0; j<nbColumns; j++)
            wayNodes[i][j].second = false;
    }
    wayNodes[start.getHeight()][start.getWidth()].first.push_back(&start);
    wayNodes[start.getHeight()][start.getWidth()].second = true;
    while(!nodesToCheck.empty())
    {
        //Check if we can move left
        if(currentNode != currentNode->getNodeLeft())
            //check if we already have traited that node
            if(!wayNodes[currentNode->getNodeLeft()->getHeight()][currentNode->getNodeLeft()->getWidth()].second)
            {
                //We mark the node as visited
                wayNodes[currentNode->getNodeLeft()->getHeight()][currentNode->getNodeLeft()->getWidth()].second = true;
                //We give the path of the current node to the next one.
                wayNodes[currentNode->getNodeLeft()->getHeight()][currentNode->getNodeLeft()->getWidth()].first = wayNodes[currentNode->getHeight()][currentNode->getWidth()].first;
                wayNodes[currentNode->getNodeLeft()->getHeight()][currentNode->getNodeLeft()->getWidth()].first.push_back(currentNode->getNodeLeft());
                //We add the next nodes the queue of nodes to check.
                nodesToCheck.push(currentNode->getNodeLeft());

            }
        //Check if we can move right
        if(currentNode != currentNode->getNodeRight())
            //check if we already have traited that node
            if(!wayNodes[currentNode->getNodeRight()->getHeight()][currentNode->getNodeRight()->getWidth()].second)
            {
                //We mark the node as visited
                wayNodes[currentNode->getNodeRight()->getHeight()][currentNode->getNodeRight()->getWidth()].second = true;
                //We give the path of the current node to the next one.
                wayNodes[currentNode->getNodeRight()->getHeight()][currentNode->getNodeRight()->getWidth()].first = wayNodes[currentNode->getHeight()][currentNode->getWidth()].first;
                wayNodes[currentNode->getNodeRight()->getHeight()][currentNode->getNodeRight()->getWidth()].first.push_back(currentNode->getNodeRight());
                //We add the next nodes the queue of nodes to check.
                nodesToCheck.push(currentNode->getNodeRight());
            }
        //Check if we can move up
        if(currentNode != currentNode->getNodeUp())
            //check if we already have traited that node
            if(!wayNodes[currentNode->getNodeUp()->getHeight()][currentNode->getNodeUp()->getWidth()].second)
            {
                //We mark the node as visited
                wayNodes[currentNode->getNodeUp()->getHeight()][currentNode->getNodeUp()->getWidth()].second = true;
                //We give the path of the current node to the next one.
                wayNodes[currentNode->getNodeUp()->getHeight()][currentNode->getNodeUp()->getWidth()].first = wayNodes[currentNode->getHeight()][currentNode->getWidth()].first;
                wayNodes[currentNode->getNodeUp()->getHeight()][currentNode->getNodeUp()->getWidth()].first.push_back(currentNode->getNodeUp());
                //We add the next nodes the queue of nodes to check.
                nodesToCheck.push(currentNode->getNodeUp());
            }
        //Check if we can move down
        if(currentNode != currentNode->getNodeDown())
            //check if we already have traited that node
            if(!wayNodes[currentNode->getNodeDown()->getHeight()][currentNode->getNodeDown()->getWidth()].second)
            {
                //We mark the node as visited
                wayNodes[currentNode->getNodeDown()->getHeight()][currentNode->getNodeDown()->getWidth()].second = true;
                //We give the path of the current node to the next one.
                wayNodes[currentNode->getNodeDown()->getHeight()][currentNode->getNodeDown()->getWidth()].first = wayNodes[currentNode->getHeight()][currentNode->getWidth()].first;
                wayNodes[currentNode->getNodeDown()->getHeight()][currentNode->getNodeDown()->getWidth()].first.push_back(currentNode->getNodeDown());
                //We add the next nodes the queue of nodes to check.
                nodesToCheck.push(currentNode->getNodeDown());
            }
        nodesToCheck.pop();
        currentNode = nodesToCheck.front();
    }
    return wayNodes[end.getHeight()][end.getWidth()].first;
}
/* ------------------------------------------------------------------------- *\
 *                          Private Member function                          *
\* ------------------------------------------------------------------------- */
pair<unsigned int, unsigned int> Board::horizontalLinking(string& currentString, unsigned int index)
{
    pair<unsigned int, unsigned int> currentPair;
    currentPair.first = static_cast<unsigned int>(currentString.find_last_of(OBSTACLE, index)+1);
    currentPair.second= static_cast<unsigned int>(currentString.find (OBSTACLE,index)-1);
    
    return currentPair;
}
pair<unsigned int, unsigned int> Board::verticalLinking(vector<string>& lineContainer, unsigned int line, unsigned int index, unsigned int nbLines)
{
    pair<unsigned int, unsigned int> currentPair;
    for( int i= static_cast<int>(line) ; i>=0 ; i--)
    {
        if(lineContainer[i][index] == OBSTACLE)
        {
            currentPair.first = static_cast<unsigned int>(i+1);
            break;
        }
    }
    for(unsigned int i= line ; i<nbLines ; i++)
    {
        if(lineContainer[i][index] == OBSTACLE)
        {
            currentPair.second = static_cast<unsigned int>(i-1);
            break;
        }
    }
    return currentPair;
}
/* ------------------------------------------------------------------------- *\
 *                      non-member operator overloading                      *
\* ------------------------------------------------------------------------- */
ostream& operator<<(ostream& os, const Board& currentBoard)
{
    for(unsigned int i=0; i< currentBoard.nbLines; i++)
    {
        for(unsigned int j=0; j<currentBoard.nbColumns; j++)
            os << *currentBoard.map[i][j];
        os << endl;
    }
    return os;
}
