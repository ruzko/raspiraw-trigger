// compile with : g++ -Wall -pthread -o readpin2 readpin.cpp -l pigpio

/*This c++ program should do the following steps:
 * 1. delete any pre-exisiting 'outputFile' and declare a 'new' outputFile,
 * 2. read pin state from 'readPinFile'.
 * 3. write '1' to 'outputFile' if pin state is 'HIGH' and write '0' to 'outputFile' if pin state is 'LOW',
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
#include <vector>
#include <tuple>

using namespace std;
//using std::fstream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::fstream;

//using std::filesystem::remove

const char* outputFile ="triggerOutStatus.txt";
const char* readPinFile = "dummy_gpio.txt";
char currentStatus;  //A store for the single integers read from 'readPinFile'

//int main(int argc, char **argv) {
int main () {

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


ofstream ofs;//(outputFile);//declaring a file stream object
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

// End of code block 1

//Start of temporary code block 2, swapping state of 'pin' between 'LOW' and 'HIGH' every 5 seconds. First deleting readPinFile


// int currentStatus;
//while (ifs.get(currentStatus)) //read
//{
ifs.open(readPinFile, ios::in);
  ifs.get(currentStatus);

  cout << "input is currently " << currentStatus << endl;

//  }
  ifs.close();
  int runtime = '0';
  int interval = '5'; //milliseconds
 // while (runtime < 2000)
//  {
/*      int deltaTime;
      int clock = clock_t();
      deltaTime = clock - runtime;
    if (deltaTime == interval)
*///    {
       ifs.open(readPinFile, ios::out);

//    }
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


 //   ifs.put('0');
 //   ifs.close();
    runtime=runtime+interval;

//  }
//}
//End of temporary code block 2

//Start of actual code block 2, reading status of pin into a variable
/*
  gpioSetMode(18, PI_INPUT);
  gpioSetPullUpDown(18, PI_PUD_DOWN);

  if (gpioRead(18) == PI_LOW)
{*/

//End of actual code block 2

//Start of code block 3, writing currentStatus to outputFile

int outputStatus;
ofs.open(outputFile, ios::out);
  switch(currentStatus)
  {
    case '1' :
    fprintf(stdout, "<PRESSED>\n");
    outputStatus = '1';
    ofs.put(outputStatus);
    ofs.close();
    break;

    case '0' :
    fprintf(stdout, "<NONE>\n");
    outputStatus = '0';
    ofs.put(outputStatus);
    ofs.close();
    break;

    default :
      cout << "Switch statement failed" << endl;

  }

//  gpioTerminate(); // Compulsory. If gpio isn't terminated, pins aren't uninitialized and can cause trouble for later assignments.
  return 0;
}
