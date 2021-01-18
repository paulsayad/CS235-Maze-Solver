/*

Title  : Solutions.cpp
Author : Paul Sayad
Descp  : This is the cpp file where I implement the DFS, BFS, DEF, and Custom Algorithims to find the shorest paths in each maze
DOC    : MAY 15 2020

*/

#include "Maze.cpp"

using namespace std;
#include <vector>
#include <queue>
#include <stack>

namespace solutions
{

int getNumberOfWalls(MazeNode *a_node)
{
    int wall_counter = 0;
    if(a_node->getDirectionNode(directions::nesw::NORTH) == nullptr || a_node->getDirectionNode(directions::nesw::NORTH)->isWall() || a_node->getDirectionNode(directions::nesw::NORTH)->isVisited()){
            wall_counter++;
    }
    if(a_node->getDirectionNode(directions::nesw::EAST) == nullptr || a_node->getDirectionNode(directions::nesw::EAST)->isWall() || a_node->getDirectionNode(directions::nesw::EAST)->isVisited()){
            wall_counter++;
    }
    if(a_node->getDirectionNode(directions::nesw::SOUTH) == nullptr || a_node->getDirectionNode(directions::nesw::SOUTH)->isWall() || a_node->getDirectionNode(directions::nesw::SOUTH)->isVisited()){
            wall_counter++;
    }
    if(a_node->getDirectionNode(directions::nesw::WEST) == nullptr || a_node->getDirectionNode(directions::nesw::WEST)->isWall() || a_node->getDirectionNode(directions::nesw::WEST)->isVisited()){
            wall_counter++;
    }
    return wall_counter;
}

bool canTravel(MazeNode *a_node)
{
    if(a_node == nullptr){
        return false;
    }
    if (a_node->isVisited() || a_node->isWall()){
        return false;
    }
    return true;
}

/** Adds an item to a position
 * @post If successful, shortest path for maze will be returned
 * @param maze that is being searched
 * @return returns the shortest path through a DFS algorithim
 **/
std::vector<MazeNode> solveDFS(Maze &a_maze)
{
    MazeNode* myNode = a_maze.getFirstNode();   // Setting the node that will traverse the maze to the first node
    MazeNode* lastNode = a_maze.getLastNode();  // Node that holds the last node
    stack<MazeNode> visited;                    // stack that will hold all the nodes visited
    visited.push(*myNode);                      // Adding starting node to visited stack
    myNode->setVisited();                       // Setting first node to visited

    // Creating while loop to traverse the maze
    while(!visited.empty()){

        //Final Step: When myNode is at lastNode move stack to vector and return vector
        if(myNode->getStrPos() == lastNode->getStrPos()){
            int x = visited.size();
            vector<MazeNode> path(x);
            for(int i = 0; i < x; i++){
                path[x - (1 + i)] = visited.top();
                visited.pop();
            }
            return path;
        }
        
        // Step 1: if statement for each direction to make myNode traverse the maze - while adding to stack/setting visited
        if(canTravel(myNode->getDirectionNode(directions::nesw::NORTH)) == true){
            myNode = myNode->getDirectionNode(directions::nesw::NORTH);
            //cout << "I am at: " << myNode->getStrPos() << endl;
            myNode->setVisited();
            visited.push(*myNode); 
        } else if(canTravel(myNode->getDirectionNode(directions::nesw::EAST)) == true) {
            myNode = myNode->getDirectionNode(directions::nesw::EAST);
            //cout << "I am at: " << myNode->getStrPos() << endl;
            myNode->setVisited();
            visited.push(*myNode);     
        } else if(canTravel(myNode->getDirectionNode(directions::nesw::SOUTH)) == true) {
            myNode = myNode->getDirectionNode(directions::nesw::SOUTH);
            //cout << "I am at: " << myNode->getStrPos() << endl;
            myNode->setVisited();
            visited.push(*myNode); 
        } else if(canTravel(myNode->getDirectionNode(directions::nesw::WEST)) == true) {
            myNode = myNode->getDirectionNode(directions::nesw::WEST);
            //cout << "I am at: " << myNode->getStrPos() << endl;
            myNode->setVisited();
            visited.push(*myNode); 
        }   

        // Step 2: if loop for when myNode is at a dead end to work its way back to the last node with another route
        // Does so by resettingVisited, moving, and setting previous node to wall and current node to visited
        if(myNode->getStrPos() != lastNode->getStrPos() && canTravel(myNode->getDirectionNode(directions::nesw::NORTH)) == false && canTravel(myNode->getDirectionNode(directions::nesw::SOUTH)) == false && canTravel(myNode->getDirectionNode(directions::nesw::WEST)) == false && canTravel(myNode->getDirectionNode(directions::nesw::EAST)) == false){
            if(myNode->getDirectionNode(directions::nesw::NORTH)->isVisited() == true && myNode->getDirectionNode(directions::nesw::NORTH)->isWall() == false){
                myNode->getDirectionNode(directions::nesw::NORTH)->resetVisited();
                myNode = myNode->getDirectionNode(directions::nesw::NORTH);
                //cout << "N: I am back at: " << myNode->getStrPos() << endl;
                myNode->setVisited();
                myNode->getDirectionNode(directions::nesw::SOUTH)->setWall();    
            } else if(myNode->getDirectionNode(directions::nesw::EAST)->isVisited() == true && myNode->getDirectionNode(directions::nesw::EAST)->isWall() == false){  
                myNode->getDirectionNode(directions::nesw::EAST)->resetVisited(); 
                myNode = myNode->getDirectionNode(directions::nesw::EAST);
                //cout << "E: I am back at: " << myNode->getStrPos() << endl;
                myNode->setVisited();
                myNode->getDirectionNode(directions::nesw::WEST)->setWall();             
            } else if(myNode->getDirectionNode(directions::nesw::SOUTH)->isVisited() == true && myNode->getDirectionNode(directions::nesw::SOUTH)->isWall() == false){  
                myNode->getDirectionNode(directions::nesw::SOUTH)->resetVisited();
                myNode = myNode->getDirectionNode(directions::nesw::SOUTH);
                //cout << "S: I am back at: " << myNode->getStrPos() << endl;
                myNode->setVisited();
                myNode->getDirectionNode(directions::nesw::NORTH)->setWall();
            } else if(myNode->getDirectionNode(directions::nesw::WEST)->isVisited() == true && myNode->getDirectionNode(directions::nesw::WEST)->isWall() == false){ 
                myNode->getDirectionNode(directions::nesw::WEST)->resetVisited(); 
                myNode = myNode->getDirectionNode(directions::nesw::WEST);
                //cout << "W: I am back at: " << myNode->getStrPos() << endl;
                myNode->setVisited();
                myNode->getDirectionNode(directions::nesw::EAST)->setWall();          
            }
            visited.pop(); // Remove most recent node, to move backwards
        }
    }    
}

/** Adds an item to a position
 * @post If successful, shortest path for maze will be returned
 * @param maze that is being searched
 * @return returns the shortest path through a BFS algorithim
 **/
std::vector<MazeNode> solveBFS(Maze &a_maze)
{
    MazeNode* myNode = a_maze.getFirstNode();           // Setting the node that will traverse the maze to the first node
    MazeNode* lastNode = a_maze.getLastNode();          // Node that holds the last node
    MazeNode* tempNode = a_maze.getFirstNode();         // TempNode to help to traverse the map
    MazeNode* backNode = a_maze.getLastNode();          // Node to backtrack safely
    MazeNode* prevNode = a_maze.getFirstNode();         // Node to test backtrack
    vector<MazeNode> visited;                           // All the visited nodes
    vector<MazeNode> path;                              // path but wrong order
    vector<MazeNode> finalPath;                         // path but right order
    queue<MazeNode> myqueue;                            // queue to find the path to the end through a BFS matter
    myNode->setVisited();                               // Making the first node visited = true
    myqueue.push(*myNode);                              // adding first node to queue
    string final = a_maze.getLastNode()->getStrPos();   // final position saved in string so points dont mess it up
    //cout << "Added to queue: " << myNode->getStrPos() << endl;

    // Step 1: while loop to find the end through a BFS search
    // Does so by using a queue and mutiple if statements to add the queue and then take them 1 by 1 until at the last node
    while(myNode->getStrPos() != lastNode->getStrPos()){ 
        *myNode = myqueue.front();
        if(canTravel(myNode->getDirectionNode(directions::nesw::NORTH)) == true){
            tempNode = myNode->getDirectionNode(directions::nesw::NORTH);
            tempNode->setVisited();
            myqueue.push(*tempNode);    
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        if(canTravel(myNode->getDirectionNode(directions::nesw::EAST)) == true){
            tempNode = myNode->getDirectionNode(directions::nesw::EAST);
            tempNode->setVisited();            
            myqueue.push(*tempNode);
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        if(canTravel(myNode->getDirectionNode(directions::nesw::SOUTH)) == true){   
            tempNode = myNode->getDirectionNode(directions::nesw::SOUTH);
            tempNode->setVisited();
            myqueue.push(*tempNode);
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        if(canTravel(myNode->getDirectionNode(directions::nesw::WEST)) == true){
            tempNode = myNode->getDirectionNode(directions::nesw::WEST);
            tempNode->setVisited();       
            myqueue.push(*tempNode);
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        visited.push_back(myqueue.front());
        myqueue.pop();
        myNode->setVisited();
    }

    // Step 2: Settings variables to get ready to backtrack
    int end = visited.size() - 1;
    *backNode = visited[end];
    *prevNode = visited[end - 1];
    path.push_back(*backNode);

    // Step 3: For loop that backtracks from last node to first node, adding everything
    // Uses a vector and checks if last variable is 1 off the x or y axis of the lastNode, then checks 1 by 1 till it gets to the start
    for(int i = 0; i < visited.size(); i++){
        if(visited[end].getStrPos() == final){
            int last = end - (2 + i);
            if(backNode->getPos().first - 1 == prevNode->getPos().first && backNode->getPos().second == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last];
            } else if(backNode->getPos().first + 1 == prevNode->getPos().first && backNode->getPos().second == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last]; 
            } else if(backNode->getPos().first == prevNode->getPos().first && backNode->getPos().second - 1 == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last]; 
            } else if(backNode->getPos().first == prevNode->getPos().first && backNode->getPos().second + 1 == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last]; 
            } else {
                *prevNode = visited[last]; 
            }
        }
    }
    
    // Step 4: Reorder the path to the correct order
    for(int i = path.size() - 1; i >= 0; i--){
        finalPath.push_back(path[i]);
    }

    //Step 5: return the final path
    return finalPath;
}

/** Adds an item to a position
 * @post If successful, shortest path for maze will be returned
 * @param maze that is being searched
 * @return returns the shortest path through a DEF algorithim
 **/
std::vector<MazeNode> solveDEF(Maze &a_maze)
{
    MazeNode* pathNode = a_maze.getFirstNode();
    MazeNode* myNode = a_maze.getFirstNode();       // Setting the node that will fill in the dead ends
    MazeNode* deNode = new MazeNode();              // Node to find the dead ends
    MazeNode* firstNode = a_maze.getFirstNode();    // Setting a node to the first node for the base
    MazeNode* lastNode = a_maze.getLastNode();      // Setting a node to the last node for the base case
    vector<MazeNode> finished;                      // Vector to hold the filled in map with one route
    queue<MazeNode*> myqueue;                       // Holds all the dead ends in here
    vector<MazeNode> allNodes = a_maze.getNodes();  // holds all the nodes in the map
    
    // Step 1: for loop to go through the nodes and find the dead ends
    // Takes the nodes 1 by 1 and checks if they have 3 walls and then it knows its a dead end and adds them to queue (doesnt add first and last node)
    for(int i = 0; i < allNodes.size(); i++){
        deNode = &(allNodes[i]);
        if(getNumberOfWalls(deNode) == 3 && !(deNode->isWall()) && deNode->getStrPos() != firstNode->getStrPos() && deNode->getStrPos() != lastNode->getStrPos()){
            deNode->setWall();
            myqueue.push(deNode);
        }
    }

    // Step 2: while loop to search for other dead ends and create the single one empty path
    // Does so by setting walls where the dead ends and continuing to looks for 3 walls, thus filling the dead ends with walls - using a queue
    myNode = myqueue.front();
    while(!myqueue.empty()){
        myNode->setWall();
        myNode->getDirectionNode(directions::nesw::NORTH)->getDirectionNode(directions::nesw::SOUTH)->setWall();
        //cout << getNumberOfWalls(myNode);
        if(canTravel(myNode->getDirectionNode(directions::nesw::NORTH)) && getNumberOfWalls(myNode->getDirectionNode(directions::nesw::NORTH)) == 3){
            myNode = myNode->getDirectionNode(directions::nesw::NORTH);
            myqueue.push(myNode);
            //cout << "I am at: " << *myNode << endl;
        } else if(canTravel(myNode->getDirectionNode(directions::nesw::EAST)) && getNumberOfWalls(myNode->getDirectionNode(directions::nesw::EAST)) == 3){
            myNode = myNode->getDirectionNode(directions::nesw::EAST);
            myqueue.push(myNode);
            //cout << "I am at: " << *myNode << endl;
        } else if(canTravel(myNode->getDirectionNode(directions::nesw::SOUTH)) && getNumberOfWalls(myNode->getDirectionNode(directions::nesw::SOUTH)) == 3){
            myNode = myNode->getDirectionNode(directions::nesw::SOUTH);
            myqueue.push(myNode);
            //cout << "I am at: " << *myNode << endl;
        } else if(canTravel(myNode->getDirectionNode(directions::nesw::WEST)) && getNumberOfWalls(myNode->getDirectionNode(directions::nesw::WEST)) == 3){
            myNode = myNode->getDirectionNode(directions::nesw::WEST);
            myqueue.push(myNode);
            //cout << "I am at: " << *myNode << endl;
        }
        myqueue.pop();
        if(!myqueue.empty()){
            myNode = myqueue.front();
        }
    }

    // Step 3: Now that there is only one path, call a the standard traverse function to traverse it
    // Since all the dead ends are filled, a simple while loop will easily find the shortest path without any use of backtracing/etc...
    while(pathNode->getStrPos() != lastNode->getStrPos()){
        //cout << pathNode->getStrPos() << endl;
        finished.push_back(*pathNode); // Can't forget that first node
        pathNode->setVisited();
        if(canTravel(pathNode->getDirectionNode(directions::nesw::NORTH))){
            pathNode = pathNode->getDirectionNode(directions::nesw::NORTH);
            //cout << "N: " << pathNode->getStrPos() << endl;
        } else if(canTravel(pathNode->getDirectionNode(directions::nesw::EAST))){
            pathNode = pathNode->getDirectionNode(directions::nesw::EAST);
            //cout << "E: " << pathNode->getStrPos() << endl;
        } else if(canTravel(pathNode->getDirectionNode(directions::nesw::SOUTH))){
            pathNode = pathNode->getDirectionNode(directions::nesw::SOUTH);
            //cout << "S: " << pathNode->getStrPos() << endl;
        } else if(canTravel(pathNode->getDirectionNode(directions::nesw::WEST))){
            pathNode = pathNode->getDirectionNode(directions::nesw::WEST);
            //cout << "W: " << pathNode->getStrPos() << endl;
        }
    }
    finished.push_back(*pathNode); // Can't forget that last node
    
    return finished;
}

/** Adds an item to a position
 * @post If successful, shortest path for maze will be returned
 * @param maze that is being searched
 * @return returns the shortest path through a custom algorithim
 **/
std::vector<MazeNode> solveCustom(Maze &a_maze)
{
    MazeNode* myNode = a_maze.getFirstNode();           // Setting the node that will traverse the maze to the first node
    MazeNode* lastNode = a_maze.getLastNode();          // Node that holds the last node
    MazeNode* tempNode = a_maze.getFirstNode();         // TempNode to help to traverse the map
    MazeNode* backNode = a_maze.getLastNode();          // Node to backtrack safely
    MazeNode* prevNode = a_maze.getFirstNode();         // Node to test backtrack
    vector<MazeNode> visited;                           // All the visited nodes
    vector<MazeNode> path;                              // path but wrong order
    vector<MazeNode> finalPath;                         // path but right order
    queue<MazeNode> myqueue;                            // queue to find the path to the end through a BFS matter
    myNode->setVisited();                               // Making the first node visited = true
    myqueue.push(*myNode);                              // adding first node to queue
    string final = a_maze.getLastNode()->getStrPos();   // final position saved in string so points dont mess it up
    //cout << "Added to queue: " << myNode->getStrPos() << endl;

    // Step 1: while loop to find the end through a BFS search
    // Does so by using a queue and mutiple if statements to add the queue and then take them 1 by 1 until at the last node
    while(myNode->getStrPos() != lastNode->getStrPos()){ 
        *myNode = myqueue.front();
        if(canTravel(myNode->getDirectionNode(directions::nesw::NORTH)) == true){
            tempNode = myNode->getDirectionNode(directions::nesw::NORTH);
            tempNode->setVisited();
            myqueue.push(*tempNode);    
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        if(canTravel(myNode->getDirectionNode(directions::nesw::EAST)) == true){
            tempNode = myNode->getDirectionNode(directions::nesw::EAST);
            tempNode->setVisited();            
            myqueue.push(*tempNode);
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        if(canTravel(myNode->getDirectionNode(directions::nesw::SOUTH)) == true){   
            tempNode = myNode->getDirectionNode(directions::nesw::SOUTH);
            tempNode->setVisited();
            myqueue.push(*tempNode);
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        if(canTravel(myNode->getDirectionNode(directions::nesw::WEST)) == true){
            tempNode = myNode->getDirectionNode(directions::nesw::WEST);
            tempNode->setVisited();       
            myqueue.push(*tempNode);
            //cout << "Added to queue: " << tempNode->getStrPos() << endl;
        }
        visited.push_back(myqueue.front());
        myqueue.pop();
        myNode->setVisited();
    }

    // Step 2: Settings variables to get ready to backtrack
    int end = visited.size() - 1;
    *backNode = visited[end];
    *prevNode = visited[end - 1];
    path.push_back(*backNode);

    // Step 3: For loop that backtracks from last node to first node, adding everything
    // Uses a vector and checks if last variable is 1 off the x or y axis of the lastNode, then checks 1 by 1 till it gets to the start
    for(int i = 0; i < visited.size(); i++){
        if(visited[end].getStrPos() == final){
            int last = end - (2 + i);
            if(backNode->getPos().first - 1 == prevNode->getPos().first && backNode->getPos().second == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last];
            } else if(backNode->getPos().first + 1 == prevNode->getPos().first && backNode->getPos().second == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last]; 
            } else if(backNode->getPos().first == prevNode->getPos().first && backNode->getPos().second - 1 == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last]; 
            } else if(backNode->getPos().first == prevNode->getPos().first && backNode->getPos().second + 1 == prevNode->getPos().second){
                path.push_back(*prevNode);
                *backNode = *prevNode;
                *prevNode = visited[last]; 
            } else {
                *prevNode = visited[last]; 
            }
        }
    }
    
    // Step 4: Reorder the path to the correct order
    for(int i = path.size() - 1; i >= 0; i--){
        finalPath.push_back(path[i]);
    }

    //Step 5: return the final path
    return finalPath;
}
}// namespace solutions