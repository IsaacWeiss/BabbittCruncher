#include "babbittSquare.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

// helper function to display letter names
void babbittSquare::coutNumberAsNote(short n)
{
      cout << pitchClasses[ (n + startingPitch) % 12 ];
}

// default constructor
babbittSquare::babbittSquare()
: startingPitch(0)
{
      for (size_t i = 0; i < 12; ++i)
            matrix[0][i] = i;
      initializeMatrix();
}

// fetch input for first pitch
void babbittSquare::setStartingPitch()
{
      do
      {
            cout << "Enter numeric value of first pitch (C = 0, Db = 1, etc.): ";
            cin >> startingPitch;
      }
      while (startingPitch < 0 || startingPitch > 11);
}

// fetch input for 0-based prime form of row
void babbittSquare::setP0()
{
      cout << "Enter zero-based prime form of row, separated by spaces\n"
      << "(first value MUST be 0): ";

      // initialize P0 (first row)
      cin >> matrix[0][0];
      if (matrix[0][0] != 0)
            throw std::invalid_argument("Error! First value must be 0. Restart program.");

      // fetch input for remainder of P0 (first row)
      for (size_t i = 1; i < 12; ++i)
            cin >> matrix[0][i];

      // TODO: sanity check to make sure input is genuine 12-tone series
}

// fill in rest of matrix based on first row
void babbittSquare::initializeMatrix()
{
      // initialize I0 (first column)
      for (size_t i = 1; i < 12; ++i)
      {
            short interval = matrix[0][i] - matrix[0][i-1];
            matrix[i][0] = (matrix[i-1][0] - interval + 12) % 12;
      }

      // initialize rest of matrix
      for (size_t i = 1; i < 12; ++i)
            for (size_t j = 1; j < 12; ++j)
                  matrix[i][j] = (matrix[0][j] + matrix[i][0]) % 12;
}

// print complete babbitt square
void babbittSquare::printMatrix()
{
      cout << "\t\t"; // indent header
      for (size_t i = 0; i < 12; ++i)
            cout << 'I' << matrix[0][i] << '\t'; // numbers across top
      cout << endl << "\t\t"; // indent dividing lines
      for (size_t i = 0; i < 12; ++i)
            cout << "---" << '\t'; // dividing lines
      cout << endl;

      for (size_t i = 0; i < 12; ++i)
      {
            cout << 'P' << matrix[i][0] << "\t|\t"; // numbers down left side
            for (size_t j = 0; j < 12; ++j)
            {
                  coutNumberAsNote(matrix[i][j]);
                  cout << '\t';
            }
            cout << endl;
      }
}

// compare each inversion to prime form for hexachordal combinatoriality
bool babbittSquare::iCombinatoriality()
{
      // create hexachords from first and second halves of P0 and first half of I0
      short pHexA[6], pHexB[6], iHexA[6];
      for (size_t i = 0; i < 6; ++i)
      {
            pHexA[i] = matrix[0][i];
            pHexB[i] = matrix[0][i+6];
            iHexA[i] = matrix[i][0];
      }

      // sort hexachords for easier comparison
      sort(pHexA, pHexA + 6);
      sort(pHexB, pHexB + 6);
      sort(iHexA, iHexA + 6);

      // flag variables
      bool match1;
      bool match2;
      bool combinatorial = false;

      for (int t = 0; t < 12; ++t) // loop up to 12x, for each transposition of inversion
      {
            match1 = match2 = true; // reset before checking each transposition

            for (size_t i = 0; i < 6; ++i)
            {
                  if (pHexA[i] != iHexA[i])
                  {
                        match1 = false;
                        break;
                  }
            }
            for (size_t i = 0; i < 6; ++i)
            {
                  if (pHexB[i] != iHexA[i])
                  {
                        match2 = false;
                        break;
                  }
            }

            // if either the first or second hexachord was entirely a match,
            // combinatoriality is proven, so print where the combinatoriality was found
            if (match1 || match2)
            {
                  //cout << "Combinatoriality found between P0 and I" << t << endl;

                  cout << "Hex" << (match1 ? "B" : "A") << " in I" << t << " { ";

                  if (match1)
                        for (size_t i = 0; i < 6; ++i)
                        {
                              coutNumberAsNote((matrix[i+6][0] + t) % 12);
                              cout << ' ';
                        }
                  else // match2
                        for (size_t i = 0; i < 6; ++i)
                        {
                              coutNumberAsNote((matrix[i][0] + t) % 12);
                              cout << ' ';
                        }
                  cout << "} combines with HexA in P0 { ";
                  for (size_t i = 0; i < 6; ++i)
                  {
                        coutNumberAsNote((matrix[0][i]));
                        cout << ' ';
                  }
                  cout << "}" << endl;
                  cout << "(and the same is true of I" << ((t+1) % 12)
                  << " with P1, and all other transpositions)" << endl;
                  combinatorial = true;
            }

            // transpose iHexA before going through loop again
            for (size_t i = 0; i < 6; ++i)
            {
                  iHexA[i] = (iHexA[i] + 1) % 12;
            }
            //... and RE-SORT to put smallest first again! BUG SQUASHED
            sort(iHexA, iHexA + 6);
      }

      // all loops done and not returned true yet
      if (!combinatorial)
            cout << "I-combinatoriality not found" << endl;
      return false;
}

// TODO: automatically generate and process all possible tone rows
// to determine which ones are i-combinatorial
