#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#define LINE_SEG 4
#define MX_LGTH_MP 84
using namespace std;

void pathFind(int endLoc, int startLoc, int path[LINE_SEG], int map[LINE_SEG][3], int pSum, int step, int pvPoint, int* addr, int* paddr)
{
	for(int i = 0; i < LINE_SEG; i++)
	{
		if(map[i][1] == startLoc && map[i][2] != pvPoint)
		{
			
			pSum = pSum+map[i][0];
			path[step] = i;
			step++;
			if(map[i][2] == endLoc)
			{
				if(pSum < *addr)
				{
					*addr = pSum;
				}
			}
			else
			{
				pathFind(endLoc, map[i][1], path, map, pSum, step, startLoc, addr, paddr);
			}
		}
		else if(map[i][2] == startLoc && map[i][1] != pvPoint)
		{
			pSum = pSum+map[i][0];
			path[step] = i;
			step++;
			if(map[i][1] == endLoc)
			{
				if(pSum < *addr)
				{
					*addr = pSum;
				}
			}
			else
			{
				pathFind(endLoc, map[i][1], path, map, pSum, step, startLoc, addr, paddr);
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
	int pSum = 0;
	if(!startLoc.type)
	{
		int point1;
		int point2;
		point1 = map[startLoc.location][1];
		point2 = map[startLoc.location][2];
		pathFind(endLoc, point1, path, map, pSum, 0, 99, addr, paddr);
		pathFind(endLoc, point2, path, map, pSum, 0, 99, addr, paddr);
	}
	else
	{
		pathFind(endLoc, startLoc.location, path, map, pSum, 0, 99, addr, paddr);
	}
	cout << pDist << endl;
	for(int i = 0; path[i] != 0; i++)
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
	for(int i = 0; i < LINE_SEG - 1; i++)
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
