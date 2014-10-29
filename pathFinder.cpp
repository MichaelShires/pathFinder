#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#define LINE_SEG 21
#define MX_LGTH_MP 1023
using namespace std;

int pDist = MX_LGTH_MP;
int shortestPath[LINE_SEG] = {0};

struct location {
	bool type; // true will be point, false is line
	int location;
} currentLoc;

struct Route {
	int initStart;		//the initial start location.  good for diagnostics
	int endLoc;		//the all holy end location.  where you are going
	int startLoc;		//the current "start" location.  used for which point you are considering yourself at
	int path[1023];		//the path so far
	int map[LINE_SEG][3];	//the map data pulled from map.csv
	int pSum;		//the total distance of this path so far
	int step;		//which step you are on now.  Useful for attaining final path without non-zero check in whitespace
	int pvPoint;		//the last point visited.  useful for just not going backwards and being dumb.  like you
};

int pathFind(Route route)
{
	cout << "initStart is: " << route.initStart << endl;
	cout << "startLoc is thus: " << route.startLoc << endl;
	cout << "endLoc is thus: " << route.endLoc << endl;
	bool notVisited = true;
	for(int i = 0; i < LINE_SEG; i++)
	{
		if(route.map[i][0] == route.startLoc && route.map[i][1] != route.pvPoint)
		{
			for(int k = 0; k < route.step; k++)
			{
				if(route.path[k] == i)
				{
					notVisited = false;
					cout << "you've already been there silly!" << endl;
				}
			}
			if(notVisited)
			{
				cout << "the point of comparison is " << route.map[i][0] << endl;
				cout << "LineSegment: " << i << " is an option" << endl;
				cout << "The other side of this line is: " << route.map[i][1] << " vs. " << route.endLoc << endl;
				cout << "last point was: " << route.pvPoint << endl;
				if(route.map[i][1] == route.endLoc)
				{
					route.path[route.step] = i;
					route.step++;
					route.pSum = route.pSum + route.map[i][2];
					cout << "you made it, And you wasted this much walking distance: " << route.pSum << endl;
					cout << "you took this many steps: " << route.step << " and pDist is this: " << pDist << endl;
					if(route.pSum < pDist)
					{
						cout << "Excellent! this path was faster!" << endl;
						pDist = route.pSum;
					}
					return route.step;
				}
				else
				{
					char answer;
					cout << "would you like to take this line segment?" << endl;
					//cin >> answer;
					if (true)
					{
						Route newRoute = route;
						newRoute.path[newRoute.step] = i;
						newRoute.step++;
						newRoute.pSum = newRoute.pSum + newRoute.map[i][2];
						newRoute.pvPoint = newRoute.map[i][0];
						newRoute.startLoc = route.map[i][1];
						pathFind(newRoute);
					}
				}
			}
		}
		if(route.map[i][1] == route.startLoc && route.map[i][0] != route.pvPoint)
		{
			for(int k = 0; k < route.step; k++)
			{
				if(route.path[k] == i)
				{
					notVisited = false;
					cout << "you've already been there silly!" << endl;
				}
			}
			if(notVisited)
			{
				cout << "the point of comparison is " << route.map[i][1] << endl;
				cout << "LineSegment: " << i << "is an option" << endl;
				cout << "The other side of this line is: " << route.map[i][0] << " vs. " << route.endLoc << endl;
				cout << "last point was: " << route.pvPoint << endl;
				if(route.map[i][0] == route.endLoc)
				{
					route.path[route.step] = i;
					route.step++;
					route.pSum = route.pSum + route.map[i][2];
					cout << "you made it, And you wasted this much walking distance: " << route.pSum << endl;
					cout << "you took this many steps: " << route.step << " and pDist is this: " << pDist << endl;
					if(route.pSum < pDist)
					{
						cout << "Excellent! this path was faster!" << endl;
						pDist = route.pSum;
					}
					return route.step;
				}
				else
				{
					char answer;
					cout << "would you like to take this line segment?" << endl;
					//cin >> answer;
					if (true)
					{
						Route newRoute = route;
						newRoute.path[newRoute.step] = i;
						newRoute.step++;
						newRoute.pSum = newRoute.pSum + newRoute.map[i][2];
						newRoute.pvPoint = newRoute.map[i][1];
						newRoute.startLoc = newRoute.map[i][0];
						pathFind(newRoute);
					}
				}
			}
		}
	}
}

Route initRoute(int startLoc, int endLoc) {
	Route blankRoute;
	blankRoute.initStart = startLoc;
	blankRoute.startLoc = startLoc;
	blankRoute.endLoc = endLoc;
	blankRoute.pSum = 0;
	blankRoute.step = 0;
	blankRoute.pvPoint = 99;
	int a;
	const char* dataPointer;
	string data;
	ifstream map ("map1.csv");
	//reads out the two input numbers
	cout << blankRoute.initStart << ' ' << blankRoute.endLoc << endl;

	for(int i = 0; i < LINE_SEG; i++)
	{
		for(int n = 0; n < 2; n++)
		{
			getline(map, data, ',');
			dataPointer = data.c_str();
			a = atoi(dataPointer);
			blankRoute.map[i][n] = a;
		}
		getline(map, data, '\n');
		dataPointer = data.c_str();
		a = atoi(dataPointer);
		blankRoute.map[i][2] = a;
	}
	cout << data << endl << endl;
	for(int i = 0; i < LINE_SEG; i++)
	{
		cout << i + 1 << ' ';
		for(int n = 0; n < 3; n++)
		{
			cout << blankRoute.map[i][n] << ' ';
		}
		cout << endl;
	}
	return blankRoute;
}

/*
 *Accepts two arguments, a start location and an end location
 * runs off of an insanely basic map at the moment.
 */
int main(int argc, char* argv[]) { 
	//each element of the argv array after zero is a space delimited
	//input.  this allows/forces you to input two integers and then have
	//them stored.  pretty cool amirite?
	int initStart = atoi(argv[1]);
	cout << "initstart is: " << initStart << endl;
	int endLoc = atoi(argv[2]);
	Route route = initRoute(initStart, endLoc);
	//goToFrom(endLocation, currentLoc, mapData);
	char answer = 'y';
	pathFind(route);
	cout << "the fastest path you found between " << initStart << " and " << endLoc << " was " << pDist << " meters long." << endl;
	return 0; 
}
