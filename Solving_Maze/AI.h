#ifndef AI
#define AI

#include <vector>

#include "Point.h"

using namespace std;

class PathFinder {
	private:
		vector<Point> visitedNodes;
		vector<Point> snakeBody;
		vector<string> path;
		bool** booleanGrid;
		int _row;
		int _col;
		int goalX;
		int goalY;

		void resetGrid();
		void projectSnakeOnGrid();
		void BFS();
		
	public:
		void initGrid(int, int);
		void freeMemory();
		vector<string> returnPath(int, int, vector<Point>);
};

#endif

