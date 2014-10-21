#include <iostream> 
#include <cstdlib> 
using namespace std;

/*
 *Accepts two arguments, a start location and an end location
 * runs off of an insanely basic map at the moment.
 */
int main(int argc, char* argv[]) { 
	//each element of the argv array after zero is a space delimited
	//input.  this allows you to input two integers and then have
	//them stored.  pretty cool amirite?
	int startLocation = atoi(argv[1]);
	int endLocation = atoi(argv[2]);
	cout << startLocation << endLocation << endl;
	return 0; 
}
