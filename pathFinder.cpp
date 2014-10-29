#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#define LINE_SEG 21
#define VERTEX 20
#define MX_LGTH_MP 1023
using namespace std;

int pDist = MX_LGTH_MP;
int pStep = 0;
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
				}
			}
			if(notVisited)
			{
				if(route.map[i][1] == route.endLoc)
				{
					route.path[route.step] = i;
					route.step++;
					route.pSum = route.pSum + route.map[i][2];
					if(route.pSum < pDist)
					{
						pDist = route.pSum;
						pStep = route.step;
						for(int s = 0; s < route.step; s++)
						{
							shortestPath[s] = route.path[s];
						}
					}
					return route.step;
				}
				else
				{
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
				}
			}
			if(notVisited)
			{
				if(route.map[i][0] == route.endLoc)
				{
					route.path[route.step] = i;
					route.step++;
					route.pSum = route.pSum + route.map[i][2];
					if(route.pSum < pDist)
					{
						pDist = route.pSum;
						for(int s = 0; s < route.step; s++)
						{
							shortestPath[s] = route.path[s];
						}
					}
					return route.step;
				}
				else
				{
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
	for(int i = 0; i<LINE_SEG; i++)
		{
			blankRoute.path[i] = 0;
		}
	int a;
	const char* dataPointer;
	string data;
	ifstream map ("map.csv");
	//reads out the two input number
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
	return blankRoute;
}

void findFastestPath(Route route) {
	pathFind(route);
	cout << route.initStart << ' ' << route.endLoc << ' ' << pDist << ' ' << pStep << ' ' << "p: ";
	for(int i = 0; i < pStep; i++)
	{
		cout << shortestPath[i] << ' ';
	}
	cout << endl;
	pDist = MX_LGTH_MP;
	pStep = 0;
	for(int i = 0; i < LINE_SEG; i++)
		{
			shortestPath[i] = 0;
		}
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
	int endLoc = atoi(argv[2]);
	Route route = initRoute(initStart, endLoc);
	findFastestPath(route);
	/*for(int stt = 1; stt < VERTEX+1; stt++)
		{
			for(int end = 1; end < VERTEX+1; end++)
				{
					route = initRoute(stt, end);
					findFastestPath(route);
				}
		}*/
	return 0;
}
