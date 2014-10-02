#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>

#include "proj1.h"

using namespace std;

// define signal handler functions here.


int main(int argc, char* argv[])
{
    interval = 10;  // Global variable for sleep interval. Default interval is 10 seconds. 

    //parse the argvs, obtain interval and threshold values
    if(parse_argv(argc, argv) == false)
    {
        help_message(argv);
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Checking process activity";
        cout << " every " << interval << " seconds." << endl;
    }

    // register signal handlers
    // remember to check return values 
    
    

    // start the alarm timer

    while(true)
    {
        sleep(10);
    }
}
