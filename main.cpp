#include <iostream>
#include "Solutions.cpp"

void printPath(vector<MazeNode> answer)
{
    for(int i = 0; i < answer.size(); i++){
        std::cout << answer[i] << std::endl;
    }
}

int main()
{

    Maze mazeOne("maze_1.csv");
    Maze mazeTwo("maze_2.csv");
    Maze mazeThree("maze_3.csv");
    
    // To solve other mazes change the parameter to "mazeOne", "mazeTwo", or "mazeThree"
    // To solve the maze using different algorithms, change the function to "solveDFS", "solveBFS", or "solveDEF"
    
    // solveDFS -> solves the maze using Depth-First Search
    // solveBFS -> solves the maze using Breadth-First Search
    // solveDEF -> solves the maze using Dead-End Filling

    vector<MazeNode> answer = solutions::solveDFS(mazeOne);
    printPath(answer);
    
    return 0;
}
