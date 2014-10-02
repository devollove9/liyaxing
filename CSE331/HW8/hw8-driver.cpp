// CSE 331 HW8 Driver

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	// check to make sure there are the correct number of arguments
	if(argc!=3)
	{
		cout << "wrong number of arguments!" << endl;
		return 0;
	}
	
   	ifstream fin;		// input stream
   	vector<int> x, y;	// vectors x and y for first and second files
   	
   	// open first file and see if it opens properly
   	fin.open(argv[1]);
	if(!fin.is_open())
	{
		cout << argv[1] << " did not open properly!" << endl;
		return 0;
	}
	
	int inputNumber;
	
	// read through first file
	while(fin >> inputNumber)
		x.push_back(inputNumber);
	
	fin.close();
	
	// open second file and see if it opens properly
	fin.open(argv[2]);
	if(!fin.is_open())
	{
		cout << argv[2] << " did not open properly!" << endl;
		return 0;
	}
	
	// read through second file
	while(fin >> inputNumber)
		y.push_back(inputNumber);	
	
	fin.close();
	
	// print out first file's numbers
	for(int n=0; n<x.size(); n++)
		cout << x[n] << " ";
	cout << endl;
	
	// print out second file's numbers
	for(int n=0; n<y.size(); n++)
		cout << y[n] << " ";
	cout << endl;
	
	return 0;
}
