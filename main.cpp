// compile with : g++ -Wall -pthread -o readpin2 readpin.cpp -l pigpio

/*This c++ program should do the following steps:
 * 1. delete any pre-exisiting 'statusFile' and declare a 'new' statusFile,
 * 2. read pin state,
 * 3. write '1' to 'statusFile' if pin state is 'HIGH' and write '0' to 'statusFile' if pin state is 'LOW',
 * 4. continue running until user says otherwise.
 *
 * Each step is divided into its own code block, containing logic and exception handling.
 * As a testing environment, step 2 is replaced by a code block which emulates pin state by changing between 'LOW' and 'HIGH' every 5 seconds
 *
 */
#include <stdio.h>
//#include <pigpio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <ctime>

using namespace std;
//using std::fstream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::fstream;

//using std::filesystem::remove

const char* statusFile = "gpio_pin_status.txt";
const char* readPinFile = "dummy_gpio.txt";

int main(int argc, char **argv) {
//int main () {

/*  if (gpioInitialise() < 0)
  {
    return 1;
  }
*/
//code block 1, deleting statusFile
  try
  {
    if (remove(statusFile))
       cout << "file " << statusFile << " deleted.\n";
    else
       cout << "file " << statusFile << " not found.\n";
  }

  catch(std::filesystem::filesystem_error const& ex)
  {
     cout << "filesystem error: " ; //<<err.what() << */'\n';
  }

  //fstream statusFile("gpio_pin_status.txt");

// End of code block 1

//Start of temporary code block 2, swapping state of 'pin' between 'LOW' and 'HIGH' every 5 seconds. First deleting readPinFile

/*
  try
  {
    if (remove(readPinFile))
       cout << "file " << readPinFile << " deleted.\n";
    else
       cout << "file " << readPinFile << " not found.\n";
  }

  catch(std::filesystem::filesystem_error const& ex)
  {
     cout << "filesystem error: " ; //<<err.what() << '\n';
  }
*/

 ifstream readPinFile("dummy_gpio.txt");

  string line;
  int runtime = '0';
  int interval = '5'; //milliseconds
  while (1)
  {
      int deltaTime;
      int clock = clock_t();
      deltaTime = clock - runtime;
    if (deltaTime == interval)
    {
       readPinFile.open();
       int currentStatus << readPinFile;
    }
        if (currentStatus == 1)
        {
            readPinFile << "0";
            readPinFile.close();
        }
            else if (currentStatus == 0)
            {
            readPinFile << "1";
            readPinFile.close();
            }


    readPinFile << "0";
    readPinFile.close();
    runtime=runtime+interval;

  }
//End of temporary code block 2

//Start of actual code block 2, reading status of pin into a variable
/*
  gpioSetMode(18, PI_INPUT);
  gpioSetPullUpDown(18, PI_PUD_DOWN);

  if (gpioRead(18) == PI_LOW)
{*/

//End of actual code block 2

//Start of code block 3, writing currentStatus to statusFile
  if (currentStatus == 1)
  {
    fprintf(stdout, "<PRESSED>\n");
    statusFile << "1";
    statusFile.close();
  }

  if(currentStatus == 0)
  {
    fprintf(stdout, "<NONE>\n");
    statusFile << "0";
    statusFile.close();
  }

//  gpioTerminate(); // Compulsory. If gpio isn't terminated, pins aren't uninitialized and can cause trouble for later assignments.
  return 0;
}
