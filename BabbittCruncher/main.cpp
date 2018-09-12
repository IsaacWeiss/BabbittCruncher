#include "babbittSquare.h"

#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
      cout << "Welcome to BabbittCruncher v. 1.0!" << endl;
      cout << "----------------------------------" << endl;
      cout << "* This is a console program. After each input, press Enter. *" << endl << endl;

      babbittSquare* _babbittSquare = new babbittSquare;

      _babbittSquare->setStartingPitch();

      try {
            _babbittSquare->setP0();
      } catch (invalid_argument err) {
            cout << err.what() << endl;
            return 9; // force termination if first value was not 0
      }

      _babbittSquare->initializeMatrix();

      cout << "\nComplete matrix:" << endl;
      _babbittSquare->printMatrix();

      cout << endl << "Combinatoriality check:" << endl;
      _babbittSquare->iCombinatoriality();

      return 0;
}
