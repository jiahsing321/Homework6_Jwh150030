/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Jia Hsing Jwh150030
 * Email:  jwh150030@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


class BinaryFileHeader
{
public: 
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;


};

//Size of the fixed length buffer
const int maxRecordStringLength = 25;

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];


};






int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);


  //Get the Header Data
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  


  stringstream header;
  stringstream record;

  //Read From Header
  string magicNumber, versionNumber, numRecords;
  header << "Magic: 0x" << hex << uppercase << myHeader->magicNumber;
  magicNumber = header.str();
  header.str(""); //Clear
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber.c_str() );
 
  header << dec << "Version: " << myHeader->versionNumber;
  versionNumber = header.str();
  header.str("");
  setCDKMatrixCell(myMatrix, 1, 2, versionNumber.c_str());


  header <<"NumRecords: " <<  myHeader->numRecords;
  numRecords = header.str();
  header.str("");
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());



  //Read From Record
  string str1, str2, str3, str4;
  string length;

  //First Read and display
  binInfile.read((char *) myRecord,sizeof(BinaryFileRecord));
  record << myRecord->stringBuffer;
  str1 = record.str();
  record.str("");
  record << "strlen: " <<  strlen(str1.c_str());
  length = record.str();
  setCDKMatrixCell(myMatrix, 2, 1, length.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, str1.c_str());
  record.str("");

  //Second Read and display
  binInfile.read((char *) myRecord,sizeof(BinaryFileRecord));
  record << myRecord->stringBuffer;
  str2 = record.str();
  record.str("");
  record << "strlen: " <<  strlen(str2.c_str());
  length = record.str();
  setCDKMatrixCell(myMatrix, 3, 1, length.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, str2.c_str());
  record.str("");

  //Third Read and display
  binInfile.read((char *) myRecord,sizeof(BinaryFileRecord));
  record << myRecord->stringBuffer;
  str3 = record.str();
  record.str("");
  record << "strlen: " <<  strlen(str3.c_str());
  length = record.str();
  setCDKMatrixCell(myMatrix, 4, 1, length.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, str3.c_str());
  record.str("");

  //Fourth Read and display
  binInfile.read((char *) myRecord,sizeof(BinaryFileRecord));
  record << myRecord->stringBuffer;
  str4 = record.str();
  record.str("");
  record << "strlen: " <<  strlen(str4.c_str());
  length = record.str();
  setCDKMatrixCell(myMatrix, 5, 1, length.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, str2.c_str());
  record.str("");


  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
