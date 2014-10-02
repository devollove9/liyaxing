// CSE 331 HW8 LCS
//Yaxing Li

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
        cout<<endl<<"file 1:    "<<endl;
	for(int n=0; n<x.size(); n++)
		cout << x[n] << " ";
	cout << "-------------------"<<endl;

        cout<<endl<<"file 2:    "<<endl;
	// print out second file's numbers
	for(int n=0; n<y.size(); n++)
		cout << y[n] << " ";
	cout << endl;
	cout << "-------------------"<<endl;
	
        vector<int> c;

        /*-----------------LCS-----stored in vector c---------------------------------*/
        int i , j, n, m ;    
        n = x.size();
        m = y.size();
        vector<int> w1=x;
        vector<int> w2=y;
        vector < vector < int> > M (n+1) ;
        for (i = 0; i < n+1; i++)
            M[i].resize(m+1);
        for (i = 0; i <= n; i++)
            M[i][0] = 0;
        for (j = 0; j <= m ; j++)
            M[0][j] = 0;
        for (j = 1; j<= m ; j++)
            for (i = 1; i <= n ; i++)
                {
                    if (w1[i-1] == w2[j-1])
                        M[i][j] = 1+ M[i-1][j-1];
                    else
                        M[i][j] = max (M[i][j-1], M[i-1][j]);
                }
        // Now the trace back code
        i = n;
        j = m;
        
        cout<<"Matches:"<<endl;
        while(i>0 && j > 0)
            {
                if (M[i][j] == 1+ M[i-1][j-1]
                    && w1[i-1] == w2[j-1])// there was a match
                    {
                        c.push_back(w1[i-1]);
                        cout<<w1[i-1]<<' ';
                        i--;
                        j--;
                    }
                else if (M[i-1][j] > M[i][j-1])
                    i--;
                else
                    j--;
              
            }
        for (int nn=c.size()-1;nn>=0;nn--)
            {
                //        cout<<c[nn]<<' ';
            }
        cout<<endl;
         return 0;
}
