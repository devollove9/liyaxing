#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    pid_t pid = fork();

    if(pid < 0)
    {
        cerr << "Unable to fork. Something is wrong. Program terminating." << endl;
    }
    else if(pid == 0)
    {
        cout << "Child process terminating." << endl;
    }
    else
    {
        sleep(60);
        cout << "Parent process terminating." << endl;
    }
}

