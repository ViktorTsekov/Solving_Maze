#include <iostream>

#include "AI.h"

void PathFinder::initGrid(int row, int col) {
	_row = row;
	_col = col;
	booleanGrid = new bool*[_row];
	
	for(int i = 0; i < _row; i++) {
		booleanGrid[i] = new bool[_col];
	}
	
	for(int i = 0; i < _row; i++) {
		for(int j = 0; j < _col; j++) {
			booleanGrid[i][j] = false;
		}
	}
	
}

void PathFinder::resetGrid() {
	for(int i = 0; i < _row; i++) {
		for(int j = 0; j < _col; j++) {
			booleanGrid[i][j] = false;
		}
	}
}

void PathFinder::projectSnakeOnGrid() {
	for(int i = 0; i < snakeBody.size(); i++) {
		booleanGrid[snakeBody[i].x][snakeBody[i].y] = true;
	}
}

void PathFinder::BFS() {
	visitedNodes.push_back(snakeBody[snakeBody.size() - 1]);
	
	while(true) {
		Point cur = visitedNodes[visitedNodes.size() - 1];
		int x = cur.x;
		int y =  cur.y;
		
		if(x == goalX && y == goalY) {
            break;
        }
		
		//Right
		if(y + 1 < _col - 1 && booleanGrid[x][y + 1] != true) {
            visitedNodes.push_back(Point(x, y + 1));
            path.push_back("right");
            booleanGrid[x][y + 1] = true;
        } 
		//Down
        else if(x + 1 < _row - 1 && booleanGrid[x + 1][y] != true) {
            visitedNodes.push_back(Point(x + 1, y));
            path.push_back("down");
            booleanGrid[x + 1][y] = true;
        }
		//Left
        else if(y - 1 >= 1 && booleanGrid[x][y - 1] != true) {
            visitedNodes.push_back(Point(x, y - 1));
            path.push_back("left");
            booleanGrid[x][y - 1] = true;
        }  
		//Up
		else if(x - 1 >= 1 && booleanGrid[x - 1][y] != true) {
            visitedNodes.push_back(Point(x - 1, y));
            path.push_back("up");
            booleanGrid[x - 1][y] = true;
        } 
        //Dead end
        else {
            visitedNodes.pop_back();
            path.pop_back();
        }
		
	}
	
}

void PathFinder::freeMemory() {
	for(int i = 0 ; i < _row ; i++) {
	    delete[] booleanGrid[i];
	}
	
	delete[] booleanGrid;
}

vector<string> PathFinder::returnPath(int x, int y, vector<Point> sb) {
	snakeBody = sb;
	goalX = x;
	goalY = y;
	path.clear();
	
	resetGrid();
	projectSnakeOnGrid();
	BFS();
	
	return path;
}

