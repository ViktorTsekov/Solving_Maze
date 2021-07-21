#include <iostream>
#include <vector>
#include <windows.h>
#include <string>

#include "Point.h"

using namespace std;

char maze[5][6] = {{'X', 'O', 'X', 'X', 'X', 'X'}, 
				   {'X', 'O', 'X', 'O', 'O', 'X'}, 
				   {'X', 'O', 'X', 'O', 'X', 'X'}, 
				   {'X', 'O', 'O', 'O', 'S', 'X'}, 
				   {'X', 'X', 'X', 'X', 'X', 'X'}};
bool** booleanGrid;

int startX;
int startY;

int row = 5;
int col = 6;

vector<Point> visitedNodes;
vector<string> path;

void findStartCoordinates() {
	
	for(int i = 0; i < row; i++) {
		
		for(int j = 0; j < col; j++) {
			int cur = maze[i][j];
			
			if(cur == 'S') {
				startX = i;
				startY = j;
				visitedNodes.push_back(Point(startX, startY));
				return;
			}
			
		}
		
	}
	
}

void print() {
	
	for(int i = 0; i < row; i++) {
		
		for(int j = 0; j < col; j++) {
			cout << maze[i][j] << " ";
		}
		
		cout << endl;
	}
	
}

void convertMazeToBooleanGrid() {
	booleanGrid = new bool*[row];
	
	for(int i = 0; i < row; i++) {
		booleanGrid[i] = new bool[col];
	}
	
	for(int i = 0; i < row; i++) {
		
		for(int j = 0; j < col; j++) {
			
			if(maze[i][j] == 'X') {
				booleanGrid[i][j] = false;
			} else if(maze[i][j] == 'O' || maze[i][j] == 'S') {
				booleanGrid[i][j] = true;
			}
			
		}
		
	}
	
}

void BFS() {

	while(true) {
		Point cur = visitedNodes[visitedNodes.size() - 1];
		int x = cur.x;
		int y =  cur.y;
		
		if(x == 0 || x == row - 1 || y == 0 || y == col - 1) {
            break;
        }
		
		//Right
		if(booleanGrid[x][y + 1] == true) {
            visitedNodes.push_back(Point(x, y + 1));
            path.push_back("right");
            booleanGrid[x][y + 1] = false;
        } 
		//Down
        else if(booleanGrid[x + 1][y] == true) {
            visitedNodes.push_back(Point(x + 1, y));
            path.push_back("down");
            booleanGrid[x + 1][y] = false;
        }
		//Left
        else if(booleanGrid[x][y - 1] == true) {
            visitedNodes.push_back(Point(x, y - 1));
            path.push_back("left");
            booleanGrid[x][y - 1] = false;
        }  
		//Up
		else if(booleanGrid[x - 1][y] == true) {
            visitedNodes.push_back(Point(x - 1, y));
            path.push_back("up");
            booleanGrid[x - 1][y] = false;
        } 
        //Dead end
        else {
            visitedNodes.pop_back();
            path.pop_back();
        }
			
	}
	
}

void moveStart(string direction) {
	
	if(direction == "right") {
		maze[startX][startY] = 'O';
		startY += 1;
		maze[startX][startY] = 'S';
	} else if(direction == "down") {
		maze[startX][startY] = 'O';
		startX += 1;
		maze[startX][startY] = 'S';
	} else if(direction == "left") {
		maze[startX][startY] = 'O';
		startY -= 1;
		maze[startX][startY] = 'S';
	} else if(direction == "up") {
		maze[startX][startY] = 'O';
		startX -= 1;
		maze[startX][startY] = 'S';
	}
	
}

void printStartScreen() {
	print();
	cout << "Finding path in 3...";
	Sleep(1000);
	cout << "2...";
	Sleep(1000);
	cout << "1...";
	Sleep(1000);
	system("cls");	
}

int main() {
	printStartScreen();
	findStartCoordinates();
	convertMazeToBooleanGrid();
	BFS();
	

	for(int i = 0; i <= path.size(); i++) {
		print();
		moveStart(path[i]);	
			
		Sleep(500);
		system("cls");	
	}

}
