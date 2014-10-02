#include <stdio.h>
#include <signal.h>
#include <unistd.h>     /* Symbolic Constants */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     //strcmp()


//using namespace std;

int freq[6]={0,0,0,0,0,0};
int cur_linenum=0;

// Ctrl + c handler-------------------------------
void Chandler(int signo)
{ 
  if ( signo == SIGINT )
  {
    alarm(0);                                      //Stop SIGLARM when ctrl + c pressed
    printf("Exit? (Y/N)");//User prompt before exit
    char input;
    gets (&input);
    	
    if (input =='y' || input =='Y')                //Exit when y/Y entered
    {
	//printf("Program terminated.\n\n");   
	exit(0);
    }		
    else if (input == 'n' || input =='N')	       //Continues when n/N entered
    {
	//printf("Program Continues..\n\n");
	alarm(1);
    }		
    else Chandler(SIGINT);			       //prompt again when other things entered
  }
}


// SIGUSR 1
void sigusr( int signo)
{
  if (signo==SIGUSR1)
  {
    printf("keyword sparty occurs %d times\n", freq[5]);
  }

}

    
// user defined signal handler for alarm.
void alarm_handler(int signo)
{
  if (signo==SIGALRM)
  {
    printf("reading line #%d ...\n", cur_linenum);
    alarm(2);
  }
}

int main(int argc, char * argv[])
{
// register the signal handler
  
  
  size_t len=0;
  char * line;
  char * word;

  // Check if input format right
  if (argc>2)
  {
    printf("incorrect number of arguments\n");
    return 0;
  }

  //register SIGINT-----------------------
    if (signal(SIGINT,Chandler)== SIG_ERR)	
	{
		printf("faild to register sigint handler\n");
		exit(1);	
	}

  //register SIGALRM---------------------   
    if (signal(SIGALRM,alarm_handler)== SIG_ERR)	
	{
		printf("faild to register alarm handler\n");
		exit(1);	
	} 

  //register SIGUSR1---------------------   
    if (signal(SIGUSR1,sigusr)== SIG_ERR)	
	{
		printf("faild to register SIGUSR1 handler\n");
		exit(1);	
	}
  
  // Open the file   
  FILE *fp;
  fp=fopen(argv[1],"r");
  if (fp == NULL) 
  {perror ("Error opening file");exit(0);}

  // Start Alarm
  alarm(1);

  // Read each line in a file
  while (getline(&line,&len,fp)!=-1)
  {
    cur_linenum++;		

    // Read each word in a line
    word = strtok(line," ");    
    while (word !=NULL)
    {
      if (strcmp(word,"a")==0 )
      {
	freq[0]+=1;
      }
      if (strcmp(word,"an")==0 )
      {
	freq[1]+=1;
      }
      if (strcmp(word,"the")==0 )
      {
	freq[2]+=1;
      }
      if (strcmp(word,"is")==0 )
      {
	freq[3]+=1;
      }
      if (strcmp(word,"are")==0 )
      {
	freq[4]+=1;
      }
      if (strcmp(word,"sparty")==0 )
      {
	freq[5]+=1;
	if (freq[5]%10000==0)
	{
	  raise(SIGUSR1);
	}
      }
      word = strtok(NULL," ");
    }  
  }

  // Stop alarm
  alarm(0);

  // Display output
  printf("a: %d\n",freq[0]);
  printf("an: %d\n",freq[1]);
  printf("the: %d\n",freq[2]);
  printf("is: %d\n",freq[3]);
  printf("are: %d\n",freq[4]);
  printf("sparty: %d\n",freq[5]);

}




