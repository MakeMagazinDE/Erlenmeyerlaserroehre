//////////////////////////////////////////////////////////////////////////////
// Als Beispiel wird der MAKE-Schriftzug als Vektordaten aus dem Programmspeicher gelesen
// und dem Stream übergeben.
// Die Vektoren sind in der Datei Vectors.h definiert
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include "Vectors.h"      // In dieser Datei sind die Daten für den MAKE-Schriftzug hinterlegt

static float MAKEpos  = 0;  // Für die Annimation, an welcher Stelle hat der letzte Frame geendet

void showMake() // Anzeigen des MAKE-Schriftzuges
{
  if (lastPoints != VectorsPicture) loadMake();              // Daten nur neu laden, wenn sich die Vektorenanzahl ändert.
  PointerSet = VectorsPicture-1;                             // Zeichen für Ende des Streams abschneiden
  blanking(64,143);                                          // Sprühefekt am rechten oberen Eck des MAKE_Schrifftzuges
  DrawLine( random(10, 200) ,random(10, 150), random(1, 7)); // Sprüheffekt mit Zufallszahlen
  blanking(pgm_read_byte_near(px_MAKE),pgm_read_byte_near(py_MAKE));   // Zur ersten Koordinate des MAKE-Schriftzuges fahren
 endFrame();  
}

void loadMake() // MAKE-Schriftzug aus dem Programmspeicher in den Stream laden
{
 beginFrame();
  for (int i = 0 ; i < points_MAKE ; i++)
  {
    byte x = pgm_read_byte_near(px_MAKE+i);     // Vektoren aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_MAKE+i);     //            - || -
    byte color = pgm_read_byte_near(pc_MAKE+i); //            - || -
    DrawLine(x, y,color); 
  }
 endFrame();
 lastPoints = PointerSet;
 VectorsPicture  = PointerSet;
}


void showMake2() // MAKE Schriftzug langsam aufbauen mit Funkeneffekt
{
 const  float Speed = 0.3; // Geschwindigkeit, mit der der MAKE-Schriftzug aufgebaut wird
 beginFrame();
  if (MAKEpos < points_MAKE) MAKEpos += Speed; 
    else MAKEpos=0;
  for (int i = 0 ; i < MAKEpos ; i++)
  {
    byte x = pgm_read_byte_near(px_MAKE+i);     // Vektoren aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_MAKE+i);     //            - || -
    byte color = pgm_read_byte_near(pc_MAKE+i); //            - || -
    DrawLine(x, y,color); 
  }
  DrawLine( random(20, 200), random(80, 150), random(1, 7)); // Sprüheffekt mit Zufallszahlen
  blanking(pgm_read_byte_near(px_MAKE),pgm_read_byte_near(py_MAKE));   // Zur ersten Koordinate des MAKE-Schriftzuges fahren
 endFrame();  
}

void showMake3() // MAKE Schriftzug langsam aufbauen mit Funkeneffekt und anschließendem Standbild
{
 const  float Speed = 0.02;   // Geschwindigkeit, mit der der MAKE-Schriftzug aufgebaut wird
 static float Bildpos  = 0;   // An welcher Stelle hat der letzte Frame geendet
 static int SetposMarker = 0; // Hierin wird die Position des Befüllzeigers gespeichert
 static  int Bildpos_old = -1;// Lezter widergegebene Vektor
 unsigned long t;             // Variable für Zeitverzögerungs Schleife

 //----------------------------------------------------------------------
 // Die folgenden Zeilen zeigen den MAKE-Schriftzug nach der Annimation 
 // für 5 Sekunden komplett an. 
  if (Bildpos < (points_MAKE-1)) Bildpos += Speed; 
    else {
          SetPointerSet(SetposMarker);  // Befüllzeiger auf letzte Position ohne Funkeneffekt
          endFrame();                   // Frame abschließen
          PointerSet=-1;                // Frame immer wieder anzeigen
          t=millis();                   // Zeitverzögerunf
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
    byte x = pgm_read_byte_near(px_MAKE+Bildpos_old);     // Vektor aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_MAKE+Bildpos_old);     //            - || -
    byte color = pgm_read_byte_near(pc_MAKE+Bildpos_old); //            - || -
    DrawLine(x, y,color);  
    SetposMarker = PointerSet;    
  }
    DrawLine( random(current_pos_x-10, current_pos_x+8),  // Sprüheffekt mit Zufallszahlen
              random(current_pos_y-50, current_pos_y+20), 
              random(1, 7));                                   
    blanking(pgm_read_byte_near(px_MAKE),pgm_read_byte_near(py_MAKE));  // Zur ersten Koordinate des MAKE-Schriftzuges fahren
 endFrame(); 
}

 void Testbild_5()
 {
    byte color=0;
    byte s=15;
      beginFrame();
        for (int j = 10; j < 100; j = j+s)
        { color++;
          blanking(100-j,     100-j);
          DrawFastLine(100+j, 100-j,  color);
          DrawFastLine(100+j, 100+j,  color);
          DrawFastLine(100-j, 100+j,  color);
          DrawFastLine(100-j  ,100-j, color);           
        }
     DrawLine(200-s,  200-s,  1);
     blanking(s ,200-s);
     DrawLine(200-s,  s,  1);
   endFrame();
 }

 void Lauftext()
  {
   beginFrame();
    marquee("MAKE is the best thing in the world", 0, 100, 20, 7);
   endFrame();
  }


 void Annimation()
  {
     static byte x=100;
     static byte y=100;
     static int z=0;
     static byte color ;
     z++;
   if ( (z%100) == 0)
   {
     x = random(50, 120);
     y = random(50, 150);    
   }
   if ( (z%20) ==0) color =random(1, 7);
   beginFrame();
     if (z<100)draw_string("MAKE", x, y, color);
     else if (z<200) draw_string("is the", x, y, color);
     else if (z<300) draw_string("best thing", x, y, color);
     else if (z<400) draw_string("in the World", x, y, color);
     else if (z<500) {DrawLine( random(10, 150),random(10, 150),  random(1, 7)); DrawCircle( 100,100, z-400, 1);draw_string("MAKE", 80, 100, color);}
     else if (z<600) { DrawLine( random(10, 150),random(10, 150),  random(1, 7));DrawCircle( 100,100, 600-z, 1);draw_string("MAKE", 80, 100, color);}
     else if (z<1200) { DrawSquare( random(10, 150),random(10, 150), random(100, 250), random(100, 250), random(1, 7));}
     else if (z<1600) { DrawCircle( random(10, 150),random(10, 150), random(10, 100), random(1, 7));draw_string("MAKE", 100, 120, color);}
     else if (z<2500) { DrawLine( random(10, 150),random(10, 150),  random(1, 7));draw_string("MAKE", 100, 100, color);}
     else if (z>2500) z=0;
   endFrame();
  }
