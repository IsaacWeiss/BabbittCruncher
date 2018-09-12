#ifndef babbittSquare_h
#define babbittSquare_h

#include <string>

class babbittSquare
{
private:
      short startingPitch; // used to adjust output, since matrix must start with 0
      const std::string pitchClasses[12] =
      {"C","C#","D","Eb","E","F","F#","G","G#","A","Bb","B"};
      // modify for different enharmonic spelling in output
      short matrix[12][12]; // stores entire square, C = 0 and so on
      void coutNumberAsNote(short); // print notename for number, using startingPitch to adjust from 0
public:
      babbittSquare(); // default constructor, fills in meaningless square
      void setStartingPitch(); // fetch input for first pitch
                               // used to adjust output, since matrix must start with 0
      void setP0(); // fetch input for 0-based prime form of row
      void initializeMatrix(); // fill in rest of matrix from first row
      void printMatrix(); // print complete Babbitt square
      bool iCombinatoriality(); // compare each inversion to prime form for hexachordal combinatoriality
};

#endif
