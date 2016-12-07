/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include "png.h"
#include <iostream>
#include <vector>
#include <map>
#include <queue>

class SquareMaze
{
public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    
private:
    /**
    int w;
    int h;
    DisjointSets cells;
    vector<int> path;
    vector<bool> wallRight;
    vector<bool> wallBottom;
    int exit;
    int getCell(int x, int y, int dir);
    */
    
    vector <int> mazepath;
    int wid;
    int hei;
    DisjointSets cells;
    vector<bool> wallr;
    vector<bool> wallb;
    int exit;
    int getNext( int x, int y, int dir );
    
    
};
#endif
