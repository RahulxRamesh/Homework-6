//Rahul Ramesh rxr162130@utdallas.edu CS3377.002

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
  public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
  public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{
  //ifstream object infile opened
  ifstream infile("cs3377.bin", ios::in | ios::binary);
  //Initial records filled
  BinaryFileHeader *myHeader = new BinaryFileHeader();  
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  //values read in;
  infile.read((char *) myHeader, sizeof(BinaryFileHeader));
  infile.read((char *) myRecord, sizeof(BinaryFileRecord));
  //using the read version of stringstream, ostringstream to convert the non string types read from the class and .bin file into strings, then converted to c style strings 
  ostringstream magic,version,num;
  magic << hex << uppercase << myHeader->magicNumber;
  string magicstring = "Magic: 0x" + magic.str();
  const char* ccmagic = magicstring.c_str(); //Converted to c style string for use with the CDK matrix
  
  version << myHeader->versionNumber;
  string versionstring = "Version: " + version.str();
  const char* ccversion = versionstring.c_str();

  num << myHeader->numRecords;
  string temp = num.str();
  string numString = "NumRecords: " + num.str();
  const char* ccnum = numString.c_str();
    
  int count = atoi(temp.c_str()); //Numrecords is converted to an int and used later on for control of a while loop
  
  //CDK code given by professor  
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix
  //custom row and column names
  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  window = initscr();
  cdkscreen = initCDKScreen(window);

   initCDKColor();

    myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
  
  // Display the Matrix
  drawCDKMatrix(myMatrix, true);
  //Messages based on header .bin values
  setCDKMatrixCell(myMatrix, 1, 1, ccmagic);
  setCDKMatrixCell(myMatrix, 1, 2, ccversion);
  setCDKMatrixCell(myMatrix, 1, 3, ccnum);
    
  int i = 0;
  //while loop for iterating and displaying the values of the records
  while(i<count)
  {
    i++;
    int k=1;
    ostringstream seed;
    int a = static_cast<int>(myRecord->strLength);
    seed<<a;
    string seedString = "strlen: "+seed.str();
    const char* ccseed = seedString.c_str();
    
   string placeholder =  myRecord->stringBuffer;
   const char* placehold = placeholder.c_str();
 
   setCDKMatrixCell(myMatrix, k+i, 1, ccseed); //Dynamically setting the placements as the while loop iterates
  setCDKMatrixCell(myMatrix, k+i, 2, placehold);
  infile.read((char *) myRecord, sizeof(BinaryFileRecord)); //Re-reading to get the next record
}

  drawCDKMatrix(myMatrix, true);   

  infile.close();

  //Reads that a key is pressed so that we can keep the CDK matrix displayed until a key is pressed
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
  
  return 0;
}
