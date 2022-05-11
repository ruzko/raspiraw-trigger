// compile with : g++ -Wall -pthread -o readpin2 readpin.cpp -l pigpio

/*This c++ program should do the following steps:
 * 1. delete any pre-exisiting 'outputFile' and declare a 'new' outputFile,
 * 2. read pin state from 'readPinFile'.
 * 3. write '1' to 'outputFile' if pin state is 'HIGH' and write '0' to 'outputFile' if pin state is 'LOW',
 * 4. continue running until user says otherwise.
 *
Each step is divided into its own code block, containing logic and exception handling.
As a testing environment, step 2 is replaced by a code block which emulates pin state by changing between 'LOW' and 'HIGH' every 5 seconds
 */

//#include <pigpio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <ctime>


using namespace std;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::fstream;


//global declarations
const char* outputFile ="triggerOutStatus.txt";
const char* readPinFile = "dummy_gpio.txt";
char currentStatus;  //A store for the single integers read from 'readPinFile'
fstream ifs;
fstream ofs;
int interval = 5; //seconds between swapping of 'inputFile'

void function();

int main () {

// Starting the count
    time_t startTime, end;
    startTime = time(0);
    //deltaTime = clock();
/*  if (gpioInitialise() < 0)
  {
    return 1;
  }
*/
//code block 1, deleting output outputFile
/*
  try
  {
    if (remove(outputFile))
       cout << "file " << outputFile << " deleted.\n";
    else
       cout << "file " << outputFile << " not found.\n";
  }

  catch(system_error const& ex)
  {
     cout << "filesystem error: " ; //<<err.what() << '\n';
  }



*/
fstream ifs; //(readPinFile); //declaring a file stream object
//Testing whether the file can be read from, and
  ifs.open(readPinFile, ios::in);
  if (ifs.is_open())
  {
    cout << "inputFile is opened!" << endl;

  }
  else
  {
     cerr << "inputFile could not be opened" << endl;
  }
ifs.close();


ofstream ofs;//declaring a file stream object
//Testing whether the file can be read from, and
  ofs.open(outputFile, ios::out);
  if (ofs.is_open())
  {
    cout << "outputFile is opened!" << endl;
  }
  else
  {

    cerr << "outputFile could not be opened" << endl;
  }
ofs.close();

 while (1)
  {

    if (time(0) - startTime == interval)
    {
      function();
      startTime=startTime+interval;
    }
  }
   return 0;
}
// End of code block 1

//------------------------------------------------------------//

//Start of temporary code block 2, swapping state of 'pin' between 'LOW' and 'HIGH' every 5 seconds. First deleting readPinFile

void function()
{
  //opening 'readPinFile' as read-only filestream, reading the first character and storing it in 'currentStatus'
  ifs.open(readPinFile, ios::in);
  ifs.get(currentStatus);

  //printing 'currentStatus' for testing purposes
  cout << "input is currently " << currentStatus << endl;

  //closing read-only filestream of 'readPinFile'
  ifs.close();

  //declaring variables for the sake of timing the swapping of values written to 'readPinFile'
//  int runtime = '0';
//  ; //milliseconds

    {
// Opening 'readPinFile' as writable filestream
       ifs.open(readPinFile, ios::out);

// reading value stored in 'currentStatus', and writing the opposite value to 'readPinFile'. In effect flipping the value each permutation
        if (currentStatus == '1')
        {
            ifs.put('0');
            ifs.close();
        }
        else
        {
            ifs.put('1');
            ifs.close();
        }

    }

//End of temporary code block 2

//--------------------------------------------------------------------//

//Start of actual code block 2, reading status of pin into a variable
/*
  gpioSetMode(18, PI_INPUT);
  gpioSetPullUpDown(18, PI_PUD_DOWN);

  if (gpioRead(18) == PI_LOW)
{*/

//End of actual code block 2

//--------------------------------------------------------------------//

//Start of code block 3, writing currentStatus to outputFile

//declaring variable 'outputStatus' for storing integers
int outputStatus;

//opening 'outputFile' as a writable filestream
ofs.open(outputFile, ios::out);

// A switch case which reads the value stored in 'currentStatus' and writes the same value to 'outputFile'
  switch(currentStatus)
  {
    // if currentStatus equals 1, it means the extruder is active. Possible to trigger a recording
    case '1' :
    cout << "<Extruder active>" << endl;
    outputStatus = '1';
    ofs.put(outputStatus);
    ofs.close();
    break;

    //if currentStatus equals 0, it means the extruder is inactive. Don't trigger a recording
    case '0' :
    cout << "<Not extruding>" << endl;
    outputStatus = '0';
    ofs.put(outputStatus);
    ofs.close();
    break;

    // Error handling in case something goes wrong
    default :
      cout << "Switch statement failed" << endl;

  }

//  gpioTerminate(); // Compulsory. If gpio isn't terminated, pins aren't uninitialized and can cause trouble for later assignments.

}
