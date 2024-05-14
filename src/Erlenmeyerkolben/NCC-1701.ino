//////////////////////////////////////////////////////////////////////////////////////////////////
// Als Beispiel wird die NCC-1701 Enterprise als Vektordaten aus dem Programmspeicher gelesen
// und dem Stream übergeben.
// Die Vektoren sind in der Datei Vectors.h deffiniert
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include "Vectors.h"         // In dieser Datei sind die Daten für die Enterprise hinterlegt


void showBild() // Anzeigen der Enterprise
{
  if (lastPoints != VectorsPicture) loadBild();// Daten nur neu laden, wenn sich die Vektorenanzahl ändert.
   else PointerSet = -1;
}

void loadBild() // Enterprise aus dem Programmspeicher in den Stream laden
{
 beginFrame();
  for (int i = 0 ; i <= points_NCC ; i++)
  {
    byte x = pgm_read_byte_near(px_NCC+i);     // Vektoren aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_NCC+i);     //            - || -
    byte color = pgm_read_byte_near(pc_NCC+i); //            - || -
    DrawLine(x, y, color); 
  }
 endFrame();
 lastPoints = PointerSet;
 VectorsPicture  = PointerSet;
}

void showBild2() //Enterprise langsam aufbauen mit Stricheffekt
{
 const  float Speed = 0.05;  // Geschwindigkeit, mit der die Enterprise aufgebaut wird
 static float Bildpos  = 0;  // An welcher Stelle hat der letzte Frame geendet
 static int SetposMarker = 0;
 static  int Bildpos_old = -1;
 unsigned long t;

 //----------------------------------------------------------------------
 // Die folgenden Zeilen zeigen die Enterprise nach der Annimation 
 // für 5 Sekunden komplett an. 
  if (Bildpos < points_NCC-1) Bildpos += Speed; 
    else {
          SetPointerSet(SetposMarker);  // Befüllzeiger auf letzte Position ohne Funkeneffekt
          endFrame();                   // Frame abschließen
          PointerSet=-1;                // Frame immer wieder anzeigen
          t=millis();                   // Zeitverzögerung
          while(t+5000 > millis()){}    //    - || -
          Bildpos=0;                    // alle zurücksetzen, damit die Annimation erneut angezeigt werden kann
          SetposMarker=0;               //  - || -
          Bildpos_old=-1;               //  - || -
        }
  //---------------------------------------------------------------------- 
        
  SetPointerSet(SetposMarker);  
  if (Bildpos_old < Bildpos)
   { 
    Bildpos_old++;
    byte x = pgm_read_byte_near(px_NCC+Bildpos_old);     // Vektoren aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_NCC+Bildpos_old);     //            - || -
    byte color = pgm_read_byte_near(pc_NCC+Bildpos_old); //            - || -
    DrawLine(x, y,color);  
    SetposMarker = PointerSet;    
   }
  DrawLine(120,115,1);
  blanking(pgm_read_byte_near(px_NCC), pgm_read_byte_near(py_NCC));
  endFrame(); 
}
