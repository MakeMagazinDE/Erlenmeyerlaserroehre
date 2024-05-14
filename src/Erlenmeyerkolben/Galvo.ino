//////////////////////////////////////////////////////////////////////////////
// Steuerung von xy-Galvos mit einem R2R Netzwerk
// Die Daten werden in einen Stream geschrieben und asynchron von den 
// Berechnungsroutinen über das Timer1 Interrupt an das R2R-Netzwerk gelegt
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#define MAXPOS 1850  // Maximale Länge des Streams (1850)... kann verädert werden
hw_timer_t * timer = NULL; // Hardware Timer für den Galvotackt registrieren

// Arrays für den Anzeigestream
//----------------------------------
 byte points_X [MAXPOS+1];
 byte points_Y [MAXPOS+1];
 byte points_color[MAXPOS+1];
//-----------------------------------
boolean behind = false;  // erfolgt das Befüllen mit Daten gerade vor oder hinter der Ausgabe

void Set_TAKTRATE()
{
  TR = analogRead (Poti_Taktrate);                    // Poti_Tacktrate auslesen
  TR = map(TR, 0, 4095, 4 , 200);                     // Wert in gesetzte Grenzen umwandeln
  Serial.print("Taktrate: ");Serial.println(TR);      // Taktrate Serial ausgeben
  timerAlarmDisable(timer);                           // Timer abschalten
  timerAlarmWrite(timer,TR, true);                    // Tacktrate für den Galvo setzen
  timerWrite(timer, 0);                               // Timer auf 0 stellen    
  timerAlarmEnable(timer);                            // Timer wieder starten
}

void Stop_Galvo()
{
  timerAlarmDisable(timer);
}

void init_DAC(int _TAKTRATE)
{
  Serial.println("init_DAC");
  timer = timerBegin(0, 80, true);                // Timer_0, Prescaler 80, neu starten bei Überlauf
  timerAttachInterrupt(timer, &interrupt, true);  // Timer Interrupt registrieren
  Set_TAKTRATE();                                 // Tacktrate über Potentiometer ermitteln
}                                                 // und TimerAlarm anpassen  
  
void setPixel(byte posX, byte posY, int color)
{  
  PointerSet++;                                         // Befüllzeiger auf nächste Position setzen
  if (PointerSet >= MAXPOS)fehlerMaxpos(PointerSet);   // Wird die maximale Anzahl an Punkten überschritten, dann Fehler anzeigen
  while ( PointerShow == PointerSet) delayMicroseconds(1); // Warten um Anzeigestream nicht zu überholen
  points_color[PointerSet] = color;                // Laserfarbe in den Stream schreiben
  points_X[PointerSet] = posX;                     // Position X in den Stream schreiben
  points_Y[PointerSet] = posY;                     // Position Y in den Stream schreiben
  current_pos_x = posX;                            // weitere Berechnungen von der  
  current_pos_y = posY;                            // aktuellen Koordinate ausführen 
}

void beginFrame()
{
 PointerSet = 0;                // Befüllzeiger auf erste Positon 
 behind = true;                 // der Befüllzeiger (setpos) befindet sich hinter dem Anzeigezeiger (pos)
 points_X[PointerSet] = 127;    // Galovo X auf die Bildmitte fahren
 points_Y[PointerSet] = 127;    // Galovo Y auf die Bildmitte fahren
 points_color[PointerSet] = 0;
}

void endFrame()
{  
 PointerSet++;                                    // Befüllzeiger auf nächste Position setzen
 while ( PointerShow == PointerSet) delayMicroseconds(1); // Bei Bedarf warten, um Anzeigestream nicht zu überholen
 points_X[PointerSet] = points_X[PointerSet-1];   // Galvoposition X nicht verändern
 points_Y[PointerSet] = points_Y[PointerSet-1];   // Galvoposition X nicht verändern
 points_color[PointerSet] = 128;                  // Laser Ausschalten und Zeichen für Ende Frame
 behind = true; 
}

void SetPointerSet(int position)
{
  if (position > 0) 
  {
    current_pos_x = points_X[position];
    current_pos_y = points_Y[position];
  } else beginFrame();
  PointerSet = position;  
}

void interrupt()
{ 
  if ((behind == true) | (PointerSet < PointerShow) )    // zuerst prüfen, ob der Stream gerade vor oder hinter dem Anzeigestream befüllt wird
  {   
    PointerShow++;                                       // Anzeigezeiger auf nächste Position setzen 
    if (points_color[PointerShow] !=  points_color[PointerShow-1]) // Laser nur schalten, wenn sich etwas geändert hat  
      RGBLaser(points_color[PointerShow]);
  
   dacWrite( Galvo_X, points_X[PointerShow]);
   dacWrite( Galvo_Y, points_Y[PointerShow]);
   
    if ((PointerShow >= MAXPOS ) | (points_color[PointerShow] == 128)) // Ende vom Frame erreicht
    {
      behind = false; 
      PointerShow = 0;
     } 
  }
 doSound();   // Bei Bedarf Sound abspielen (siehe dort)
}
