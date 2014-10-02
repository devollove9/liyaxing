//#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <vector>

using namespace std;

// The interval of time between process checks by the monitor program
int interval = 10;

// Global vectors for storing bad processes that need to be killed

// The vector to store bad process pids.
std::vector<pid_t>  bad_process_pid_queue;

// The vector to store bad process names.
std::vector<string> bad_process_name_queue;

// The vector to store zombie pids.
std::vector<pid_t>  zombie_pid_queue;

// The vector to store zombie names.
std::vector<string> zombie_name_queue;

/*********************************
 * Name:    help_message
 * Purpose: display to the users how to run this program
 *          also show users the available paramters
 * Receive: the arguments
 * Return:  none
 *********************************/
void help_message(char *argv[])
{
    cout << endl;
    cout << "PURPOSE: The program " << argv[0] 
         << " is a monitor program that checks for" << endl;
    cout << "    1. presence of a previously identified rogue process (spinner), and" 
         << endl;
    cout << "    2. presence of one or more zombie processes." << endl;
    cout << endl;
    cout << "USAGE: " << argv[0] << " [parameters]" << endl;
    cout << "The following parameters are optional:" << endl;
    cout << "    -t interval    Specify the monitoring interval." << endl
         << "                   Default value is 10 seconds." << endl;
    cout << "    -h             Display help message." << endl;
    cout << endl;
    cout << "EXAMPLE: " << argv[0] << " -t 5" << endl;
    cout << "The monitor program checks every 5 seconds";
    cout << "and kills targeted processes." << endl;
    cout << endl;
}


/*********************************
 * Name:    parse_argv
 * Purpose: parse the parameters
 * Receive: the arguments argv and argc
 * Return:  true if the arguments are valid, false otherwise.
 *          but the value for global variables interval and threshold will be 
 *          determined.
 *********************************/
bool parse_argv(int argc, char* argv[])
{
    char *endptr; // for strtol

    for(int i = 1; i < argc; i++)
    {
        // parse interval
        if((!strncmp(argv[i], "-t", 2)) ||
           (!strncmp(argv[i], "-T", 2)))
        {
            // make sure that there is a value after -t
            // otherwise it will segfault later.
            if((i + 1) >= argc){
                cerr << "Invalid interval value. " 
                     << "There muts be a interval value after -t."
                     << endl;
                return false;
            }
            // parse the parameter to int
            interval = strtol(argv[++i], &endptr, 0);
            if(*endptr || interval <= 0) // Invalid interval value
                                         // it must be a positive int
            {
                cerr << "Invalid interval value. " 
                     << "The interval must be a positive value."
                     << endl;
                return false;
            }
        }
        // help message is requested
        else if((!strncmp(argv[i], "-h", 2)) ||
                (!strncmp(argv[i], "-H", 2)))
        {
            return false;
        }
        else // all other paramters are not allowed 
        {
            cerr << "Invalid parameter: " << argv[i] << endl;
            return false;
        }
    }

    return true;
}

/*********************************
 * Name:    run_ps
 * Purpose: run ps command
 * Receive: none
 * Return:  the ps results as one string
 *********************************/
string run_ps()
{
    string cmd = "ps uf";
    FILE *in;       // A FILE pointer for storing the cmd execution outputs
    char buff[512]; // buffer for reading the results from FILE pointer
    string results; // A string to hold all results

    //execute command and store results in the file
    if(!(in = popen(cmd.c_str(), "r"))){
        cerr << "Unable to execute ps. Something is wrong."
             << " Program terminates." << endl;
        exit(EXIT_FAILURE);
    }

    // read the execution results from the file pointer and store
    // them in the result string
    while(fgets(buff, sizeof(buff), in)!=NULL){
        results += buff; // here you have the output of your script in buff
    }
    pclose(in); // close the file pointer


    // Uncomment next line if you want to have a look at the results
    // cout << results << endl;

    return results;
}


/*********************************
 * Name:    parse_ps
 * Purpose: parse the ps result string
 * Receive: the ps result string
 * Return:  none,
 *          but any spinner process or zombie process 
 *          will be captured
 *********************************/
void parse_ps(string results)
{
    unsigned int pos = 0; // For splitting the results by line
    int line_number = 0;  // For counting line number
    string pid_str, name_str, state_str, cpu_str;

    // reset the vectors
    bad_process_name_queue = vector<string>();
    bad_process_pid_queue = vector<pid_t>();
    zombie_name_queue = vector<string>();
    zombie_pid_queue = vector<pid_t>();

    while(pos != string::npos && results != "")
    {
        pid_t tmp_pid;

        // split the results by line
        pos = results.find("\n");
        // grab a line
        string a_line = results.substr(0, pos);
        // remove the line from results
        results = results.substr(pos+1, results.length());
        // output the line
        cout << a_line << endl;

        if(line_number != 0)
        {
            // get the state
            state_str = a_line.substr(47, 4);
            if(state_str.find("Z") != string::npos){
                // If this line/process is a zombie process, we cannot kill it,
                // it is already dead! We need to kill its parent process, which
                // is the previous process. Therefore, we do not update the
                // pid_str here so that pid_str still stores the parent process
                // pid
                //pid_str   = a_line.substr(9, 5);  // char 9 ~ 13 is the pid
            }
            else
            {
                // if this line/prorcess is not a zombie.
                pid_str   = a_line.substr(9, 5);  // char 9 ~ 13 is the pid
            }
            // get the cpu time
            cpu_str   = a_line.substr(15, 4); // char 15 ~ 18 is the CPU time

            // It means this process is a child process. We want to store its parent
            // process name too.
            if(a_line[65] == ' ')
            {
                name_str += "\n";
                name_str += a_line.substr(65);    // char 65 till the end is the 
                                                  // process name
            }
            else
            {
                name_str = a_line.substr(65);
            }
            
                               
            // converts cpu_str to unsigned int
            //istringstream cpu_buf(cpu_str);
            //cpu_buf >> cpu;

            // converts pid_str to pid_t
            // NOTE: This conversion might not work on other systems.
            istringstream pid_buf(pid_str);
            pid_buf >> tmp_pid;

            // output and check if the parsed values are correct
            // uncomment the following section if you need to check if the 
            // parsing is correct
            /*
            cout << "====================================================" << endl;
            cout << "PID:   " << tmp_pid << endl;
            cout << "Name:  " << endl
                              << name_str << endl;
            cout << "State: " << state_str << endl;
            cout << "CPU:   " << cpu << endl;
            cout << "====================================================" << endl;
            */

            // if the process is using CPU time more than the threshold
            // add it into the queue, so that the monitor can kill it.
            //if(cpu > threshold)
            if(name_str.find("spinner") != string::npos)
            {
                bad_process_pid_queue.push_back(tmp_pid);
                bad_process_name_queue.push_back(name_str);
            }

            // if the process state contains zombie.
            if(state_str.find("Z") != string::npos)
            {
                zombie_pid_queue.push_back(tmp_pid);
                zombie_name_queue.push_back(name_str);
            }
        }
        line_number += 1;
    }
}
