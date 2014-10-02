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

//signal handler
//Ctrl + c handler-------------------------------
void Chandler(int signo)
{
    
	if ( signo == SIGINT )
	{
		alarm(0);                                      //Stop SIGLARM when ctrl + c pressed
		printf("Are you sure you want to quit? (y/n)");//User prompt before exit
		char input;
		cin>>input;	
		if (input =='y' or input =='Y')                //Exit when y/Y entered
	    	{
			printf("Program terminated.\n\n");   
	 		exit(0);
	    	}		
        	else if (input == 'n' or input =='N')	       //Continues when n/N entered
	    	{
                	printf("Program Continues..\n\n");
            	}		
		else Chandler(SIGINT);			       //Pormpt again when other things entered
        }
}


//SIGALRM handler---------------------------------
void handler(int signo)
{
    
	if ( signo == SIGALRM )			
	{		
		parse_ps(run_ps());				//prase_ps and run_ps
	}

    //Spinner detect---------------------------------    
	if (bad_process_pid_queue.empty()) cout<<"NO spinner process found.."<<endl;    
	else 
	{          
	      for (unsigned int i=0; i<bad_process_pid_queue.size(); i++)
	      {
		cout<<bad_process_name_queue[i]<<" is consuming too much CPU time."<<endl;
		cout<<"Attempting to kill process "<<bad_process_pid_queue[i]<<"..."<<endl;
		kill(bad_process_pid_queue[i],SIGKILL);         //Kill the spinner process
		raise(SIGUSR1); 				//raise SIGUSR2 when kill spinner 
		
	      }
        }
    //Zombie detect---------------------------------- 
	if (zombie_pid_queue.empty()) cout<<"NO zombie process found.."<<endl;    
	else 
	{          
	      for (unsigned int i=0; i<zombie_pid_queue.size(); i++)
	      {
		cout<<"Zombie process found:  \n";
		cout<<zombie_name_queue[i]<<endl;
		cout<<"Attempting to kill process "<<zombie_pid_queue[i]<<"..."<<endl;
		kill(zombie_pid_queue[i],SIGKILL);		//kill the zombie process
		raise(SIGUSR1);					//raise SIGUSR1 when kill zombie
		
	      }
        }
}

void sigusr( int signo)
{
	if (signo==SIGUSR1) cout<<"Successfully killed zombie program."<<endl<<endl;
	if (signo==SIGUSR2) cout<<"Successfully killed spinner program."<<endl<<endl;
}
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

    //register SIGINT-----------------------
    if (signal(SIGINT,Chandler)== SIG_ERR)	
	{
		printf("faild to register sigint handler");
		exit(1);	
	} 
    //register SIGALRM---------------------   
    if (signal(SIGALRM,handler)== SIG_ERR)	
	{
		printf("faild to register alarm handler");
		exit(1);	
	} 
    //register SIGUSR1---------------------   
    if (signal(SIGUSR1,sigusr)== SIG_ERR)	
	{
		printf("faild to register SIGUSR1 handler");
		exit(1);	
	}
    //register SIGUSR2---------------------   
    if (signal(SIGUSR2,sigusr)== SIG_ERR)	
	{
		printf("faild to register SIGUSR2 handler");
		exit(1);	
	}
    // remember to check return values   
    

    // start the alarm timer
    printf("Checking process....\n");  // first time
    alarm(interval);
    sleep(interval);
    while(true)			//recursively sending alarms
    {
        cout<<endl<<endl;
	printf("Checking process....\n");
	alarm(interval);	
        sleep(interval);	
    }
}
