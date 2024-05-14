//////////////////////////////////////////////////////////////////////////////
// Als Beispiel wird ein Testbild als Vektordaten aus dem Programmspeicher gelesen
// und dem Stream übergeben.
// Die Vektoren sind in der Datei Vectors.h definiert
//
/// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include "Vectors.h"      // In dieser Datei sind die Daten für den MAKE-Schriftzug hinterlegt


void showTestpicture() // Anzeigen des MAKE-Schriftzuges
{
  if (lastPoints != VectorsPicture) loadTestpicture();              // Daten nur neu laden, wenn sich die Vektorenanzahl ändert.
      else PointerSet = -1;
}

void loadTestpicture() // MAKE-Schriftzug aus dem Programmspeicher in den Stream laden
{
 beginFrame();
  for (int i = 0 ; i < points_Testbild ; i++)
  {
    byte x = pgm_read_byte_near(px_Testbild+i);     // Vektoren aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_Testbild+i);     //            - || -
    byte color = pgm_read_byte_near(pc_Testbild+i); //            - || -
    DrawLine(x, y,color); 
  }
 endFrame();
 lastPoints = PointerSet;
 VectorsPicture  = PointerSet;
}
