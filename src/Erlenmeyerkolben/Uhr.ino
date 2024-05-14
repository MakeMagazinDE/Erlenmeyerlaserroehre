//////////////////////////////////////////////////////////////////////////////
// Anzeigen einer analogen oder digitalen Uhr
//
// Das Ziffernblatt wird nur einmal berechnet und dem Stream übergeben.
// Die Zeiger werden dann immer von der Endposition des Ziffernblatts
// in den Stream geschrieben. Dadurch wird die Rechenzeit mit Winkelfunktionen verkleinert.
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////
#define Durchmesser 60        // Durchmesser der Uhr
#define Drehung_Stunden  7    // wenn der Laser oder der Galvo gedreht verbaut sind, muss evtl. der Stundenzeiger verdreht werden
int pointsUhr = 9999;
int SecondSaved;
bool is_NTC_time = false;     // wurde bereits NTC_Zeit abgerufen
float winkel;                 // Variable für die Winkelberechnung der Zeiger


void digitalUhr()  // Zeigt eine digitale Uhr an (langweilig...;-)
{
   uint8_t Std = rtc.getHour(true);
   uint8_t Min = rtc.getMinute();
   uint8_t Second = rtc.getSecond();
  if(is_NTC_time == false)
  {
    WIFI_Connect();
    is_NTC_time = true;
  }
  beginFrame();
  String s = String(Std)+':'+String(Min)+':'+String(Second);
   draw_string(s, 75, 100, 1);
  endFrame();  
}

void analogUhr()  // Zeigt eine analoge Uhr
                  // Die darin enthaltenen Winkelberechnungen könnten sicher noch optimiert werden
{ 
   uint8_t Std    = rtc.getHour(); 
   uint8_t Min    = rtc.getMinute();
   uint8_t Second = rtc.getSecond();

  if(is_NTC_time == false) // Zeit vom Zeitserver holen (aber nur ein mal)
  {
    WIFI_Connect();
    is_NTC_time = true;
  }
   if  (pointsUhr != lastPoints) ZiffernblattRund(); //ZiffernblattMake(); // Daten nur neu laden, wenn sich die Punkteanzahl ändert.
    else behind = true;
   if (Second != SecondSaved) // nur neu Berechnen, wenn sich der Sekundenzeiger bewegt werden muss
    {
      PointerSet = pointsUhr; // Anstelle von beginFrame(),so muss das Ziffernblatt nicht neu konstruiert werden
   // --------------------------------------------------------------------------------Sundenzeiger
      byte color = 3;  // Farbe Gelb
     blanking( 100,100);
      winkel = 0.01745*(0.5*(60-Min) + 30*(24-Std-Drehung_Stunden));
        float dx = 100 + sin (winkel)*(Durchmesser-25);  
        float dy = 100 + cos (winkel)*(Durchmesser-25);  
      DrawLine(dx, dy, color);
      DrawLine(100,100, color);
            
    //-------------------------------------------------------------------------------- Minutenzeiger
     color=2;   // Farbe Grün
      winkel = 0.1047*(60-Min);
        dx = 100-sin (winkel)*(Durchmesser-14);
        dy = 100-cos (winkel)*(Durchmesser-14);
      DrawLine( dx,dy, color);
      DrawLine(100,100, color);

    // ------------------------------------------------------------------------------- Sekundenzeiger
    color=7;    // Farbe weiss
       winkel = 0.1047*(60-Second);
        dx = 100-sin (winkel)*(Durchmesser-10);
        dy = 100-cos (winkel)*(Durchmesser-10);
      DrawLine(dx, dy, color);
    blanking( 200,100);
    endFrame();
    SecondSaved = Second;
  } 
  
}

void ZiffernblattRund()
{
  beginFrame();  
  byte color = 1;   
        DrawCircle(100, 100, Durchmesser, 1);
         for (int i = 90; i < 450 ; i = i+30)
         {
          float sina = sin (0.01745*i);
          float cosa = cos (0.01745*i);
          double dx = 100+ sina*(Durchmesser-3);
          double dy= 100+ cosa*(Durchmesser-3);
          blanking(dx, dy);
           dx = 100+ sina*(Durchmesser-10);
           dy = 100+ cosa*(Durchmesser-10);
          DrawLine(dx, dy, color);
         }
    lastPoints=PointerSet;
   pointsUhr=PointerSet;
   
 endFrame(); 
}

void ZiffernblattMake()
{
 beginFrame();
  for (int i=0 ; i<points_MAKE; i++)
  {
    byte x = pgm_read_byte_near(px_MAKE+i);     // Vektoren aus dem Programmspeicher auslesen
    byte y = pgm_read_byte_near(py_MAKE+i);     //            - || -
    byte color = pgm_read_byte_near(pc_MAKE+i); //            - || -
    DrawLine(x, y,color); 
  }
  lastPoints = PointerSet;
  pointsUhr=PointerSet;
 endFrame();
}
