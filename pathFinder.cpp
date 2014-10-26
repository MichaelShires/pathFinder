#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#define LINE_SEG 3
#define MX_LGTH_MP 84
using namespace std;

int pathFind(int endLoc, int startLoc, int path[LINE_SEG], int map[LINE_SEG][3], int pSum, int step, int pvPoint, int* addr, int* paddr)
{
	cout << "startLoc is thus: " << startLoc << endl;
	cout << "endLoc is thus: " << endLoc << endl;
	for(int i = 0; i < LINE_SEG; i++)
	{
		if(map[i][0] == startLoc && map[i][1] != pvPoint)
		{
			cout << "the point of comparison is " << map[i][0] << endl;
			cout << "LineSegment: " << i << " is an option" << endl;
			cout << "The other side of this line is: " << map[i][1] << " vs. " << endLoc << endl;
			cout << "last point was: " << pvPoint << endl;
			if(map[i][1] == endLoc)
			{
				paddr[step] = map[i][0];
				step++;
				pSum = pSum + map[i][2];
				cout << "you made it, And you wasted this much walking distance: " << pSum << endl;
				cout << "you took this many steps: " << step << endl;
				*addr = pSum;
				return step;
			}
			else
			{
				char answer;
				cout << "would you like to take this line segment?" << endl;
				cin >> answer;
				if (answer == 'y')
				{
					paddr[step] = map[i][0];
					step++;
					pSum = pSum + map[i][2];
					pvPoint = map[i][0];
					return pathFind(endLoc, map[i][1], path, map, pSum, step, pvPoint, addr, paddr);
				}
			}
		}
		if(map[i][1] == startLoc && map[i][0] != pvPoint)
		{
			cout << "the point of comparison is " << map[i][1] << endl;
			cout << "LineSegment: " << i << "is an option" << endl;
			cout << "The other side of this line is: " << map[i][0] << " vs. " << endLoc << endl;
			cout << "last point was: " << pvPoint << endl;
			if(map[i][0] == endLoc)
			{
				paddr[step] = map[i][1];
				step++;
				pSum = pSum + map[i][2];
				cout << "you made it, And you wasted this much walking distance: " << pSum << endl;
				cout << "you took this many steps: " << step << endl;
				*addr = pSum;
				return step;
			}
			else
			{
				char answer;
				cout << "would you like to take this line segment?" << endl;
				cin >> answer;
				if (answer == 'y')
				{
					paddr[step] = map[i][1];
					step++;
					pSum = pSum + map[i][2];
					pvPoint = map[i][1];
					return pathFind(endLoc, map[i][0], path, map, pSum, step, pvPoint, addr, paddr);
				}
			}
		}
	}
}

struct location {
	bool type; // true will be point, false is line
	int location;
} currentLoc;

int goToFrom(int endLoc, location startLoc, int map[LINE_SEG][3])
{
	int path[LINE_SEG] = {0};
	int* paddr = path;
	int pDist = MX_LGTH_MP;
	int* addr = &pDist;
	int step;
	if(!startLoc.type)
	{
		int point1;
		int point2;
		int path1Step;
		int path2Step;
		point1 = map[startLoc.location][1];
		point2 = map[startLoc.location][2];
		path1Step = pathFind(endLoc, point1, path, map, 0, 0, 99, addr, paddr);
		path2Step = pathFind(endLoc, point2, path, map, 0, 0, 99, addr, paddr);
		if(path1Step > path2Step)
		{
			path1Step = path2Step;
		}
		step = path1Step;
	}
	else
	{
		step = pathFind(endLoc, startLoc.location, path, map, 0, 0, 99, addr, paddr);
	}
	cout << pDist << endl;
	for(int i = 0; i < step-1; i++)
	{
		cout << path[i] << ' ';
	}
	cout << endl;
}

/*
 *Accepts two arguments, a start location and an end location
 * runs off of an insanely basic map at the moment.
 */
int main(int argc, char* argv[]) { 
	//each element of the argv array after zero is a space delimited
	//input.  this allows/forces you to input two integers and then have
	//them stored.  pretty cool amirite?
	int startLocation = atoi(argv[1]);
	int endLocation = atoi(argv[2]);
	int mapData[LINE_SEG][3];
	int a;
	const char* dataPointer;
	string data;
	ifstream map ("map.csv");
	currentLoc.location = startLocation;
	currentLoc.type = true;
	//reads out the two input numbers
	cout << startLocation << ' ' << endLocation << endl;

	for(int i = 0; i < LINE_SEG; i++)
	{
		for(int n = 0; n < 2; n++)
		{
			getline(map, data, ',');
			dataPointer = data.c_str();
			a = atoi(dataPointer);
			mapData[i][n] = a;
		}
		getline(map, data, '\n');
		dataPointer = data.c_str();
		a = atoi(dataPointer);
		mapData[i][2] = a;
	}
	cout << data << endl << endl;
	for(int i = 0; i < LINE_SEG; i++)
	{
		cout << i + 1 << ' ';
		for(int n = 0; n < 3; n++)
		{
			cout << mapData[i][n] << ' ';
		}
		cout << endl;
	}
	goToFrom(endLocation, currentLoc, mapData);
	return 0; 
}
