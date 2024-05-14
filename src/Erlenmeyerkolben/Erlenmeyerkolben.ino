
//////////////////////////////////////////////////////////////////////////////
//Erlenmeyerkolben
//
// Enthalten sind die Spiele Asteorieds und Pong.
// Daneben sind auch Testbilder und Beispiele für den Umgang mit 
// den Zeichenroutinen enthalten.
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include "Asteroids.h"  // Variablen und Konstanten für das Spiel Asteorieds
#include "Pong.h"       // Variablen und Konstanten für das Spiel Pong
#include <Time.h>       // Bibliothek  für die Uhr
#include <ESP32Time.h>  // Bibliothek  für die Uhr
ESP32Time rtc;    // Bibliothek  für die Uhr
 
#define tonePin 22      // Pin, an dem der Sound-Verstärker angeschlossen wird
#define Schalter1 16    // Pins für Auswahl der Spiele und Testbilder (Pins Codierschalter)
#define Schalter2 17    //         - || -
#define Schalter3 18    //         - || -
#define Schalter4 19    //         - || -

// Define DAC pins
#define Galvo_X 26        // Pin, an dem das analoge X-Signal ausgegeben wird
#define Galvo_Y 25        // Pin, an dem das analoge X-Signal ausgegeben wird
#define Poti_Taktrate 36  // Pin an dem das Potentiometer hängt
int TR = 20;              // Variable für die Tacktrate der Galvo Spiegel

#define laser_pin_r   23 // Pin, an dem der rote Laser angeschlossen ist
#define laser_pin_g   21 // Pin, an dem der rote Laser angeschlossen ist
#define laser_pin_b   22 // Pin, an dem der rote Laser angeschlossen ist


byte Switch;            // Variable für den Codierschalter
byte lastSwitch = 0;

//------------------------ Globale Variablen für Galvo-Scanner und Draw------------------------------------
int current_pos_x;       // An welcher Position steht der Galvo gerade?
int current_pos_y;       //      - || -

int PointerSet = 0;      // An dieser Position wird in den Stram geschrieben (Befüll-Zeiger)
int PointerShow = 0;     // An dieser Position befindet sich gerade der Laser (oder gerauer die Galvo-Scanner)(AnzeigeZeiger)
int lastPoints = 99998; 
int VectorsPicture = 99999;                          
//---------------------------------------------------------------------------------------------------------

// ####################################### Prototyping ################################################
//------------------------------------------ Laser ------------------------------------------
void init_Laser();// alle Laserpins als Output definieren
void laser_on();  // alle Laser einschalten
void laser_off(); // alle Laser ausschalten
//----------------------------------------- ASCII ------------------------------------------
void blanking(byte x, byte y);
void drawLine(byte x0, byte y0, byte x, byte y);
void drawInt(int z, byte x, byte y, byte color);   // Anzeige einer Integerzahl
void draw_string(String text, int x, int y, byte color=1);  // Anzeige von einem String
void marquee(String text, int x, int y, int x_length, byte color=1);  // Lauftext anzeigen
void draw_letter(byte letter, byte x, byte y, byte color);
void drawLineTo(byte x, byte y);
void draw_string_time(String text, byte x, byte y, byte color, int dauer);
//------------------------------------------ Draw -------------------------------------------
void DrawLine(byte x1, byte y1, byte color);
void DrawMaxDistanceLine (byte x, byte y, byte color);
void DrawBresenhamLine(byte x1, byte y1, byte color);
void DrawSpeedLine(byte x1, byte y1, byte color);
void DrawFastLine(byte x1, byte y1, byte color);
void BlankingLine(byte x1, byte y1, byte color);
void DrawCircle(int xm, int ym, int _r,byte color);
void DrawSquare(byte left, byte top, byte right, byte botton, byte color);
void drawMeldung(String Meldung, int posX, int posY,int dauer = 1000, byte color = 1);
//----------------------------------------- Galvo ---------------------------------------------
void beginFrame();
void Set_TAKTRATE();
void init_DAC(int _TAKTRATE);
void Stop_Galvo();
void setPixel(byte posX, byte posY, int color);
void beginFrame();
void endFrame();
void SetPointerSet(int position);
void interrupt();

//-------------------------------Debugging----------
void Watchdog_reset();
void hw_wdt_set_timeout(byte seconds);
void hw_wdt_disable();
void hw_wdt_enable();
void print_Reset_reason();
void Testbild_1();
void Testbild_2();  
void Testbild_3();
void Lauftext();
void Testbild_5();
void Annimation();
void showMake();
void showMake2();
void showMake3();
void showBild();
void showBild2();
void showTestpicture();
//------------------------------WIFI----
void WIFI_Connect();
//-----------------------------Galvo------
void init_DAC(int);
//-----------------------------Asteroids------
void init_Asteroids();
void play_Asteroids();
void moveAsteroid(byte n);
void newShot();
void drawShots();
void detectShipCollisions(); 
void detectShotCollisions();
void ShipExplosion();     
void GameOver(); 
void brakeAsteroid(byte j);
void newAsteroid(byte z);
int detectAsteroidCollisions(byte n);
void AsteroidAsteroidCollision(byte n);
bool inPolygon(byte nvect, struct Asteroid a, int x, int y);
void drawAsteroid(struct Asteroid a,byte color) ;
void drawShip(byte color);
void writeHighScore();
void readHighScore();
void newGame();
void init_Asteroids();
//-----------------------------Sound ---------------------
void Sound_ESP_Start();
void setSound(int s);
void sound_Fire();
void Sound_explosion();
void Sound_Die();
void Sound_NewGame();
void Sound_NewGame2();
void doSound();
//-----------------------------Controllers ------------
void init_Nunchuk();
void PollNunchuk(); 
//---------------------------- Pong --------------
void init_Pong();
void play_Pong();
void play_SoloPong();
//-----------------------------Uhr--------------
void digitalUhr();
void analogUhr();
//---------------------------Ilda------------
void ShowIldaTestbild(); 
// ----------------------------

unsigned long time_old = millis();
bool STOP = false;
//---------------------------------------------------------------------------------------------------------

void setup() 
{ 
  ledcAttachPin(22, 0);   // Pin für den Sound, PWM channel
   Sound_ESP_Start();     // Spielt eine Tonfolge, wenn der ESP startet
   
   dacWrite( Galvo_X, 100);  // Initialisierung der ESP32 DAV-Kanäle
   dacWrite( Galvo_Y, 100);  // an den Pins GPIO 24 und GMIO 25
   pinMode(Poti_Taktrate, INPUT);  // initialisierung vom Anschluss für ein Potentiometer als Tacktrate
    
  pinMode(Schalter1, INPUT_PULLUP);  // Initialisierung der Pins für den Programmwahlschalter
  pinMode(Schalter2, INPUT_PULLUP);  // einem Encoder mit 16 Stellungen
  pinMode(Schalter3, INPUT_PULLUP); 
  pinMode(Schalter4, INPUT_PULLUP); 

  
  Serial.begin(115200);   // Serialpor initialisieren für Debuggingausgaben
  delay(50);              // kurz warten, bevor der Grund
   print_Reset_reason();  // für den lezten Rest ausgegeben wird

  Serial.println("### Erlenmeyerkolben startet ###");
  
  randomSeed(analogRead(0)); // Zufallsfunktion initialisieren
  init_Laser(); 
  init_DAC(TR);              // Initialisierung vom Timer für die Galvos (Tacktrate)
  init_Nunchuk();
  init_Asteroids();
  init_Pong();
}


// Kodierschalter abfragen und in Integerwert umrechnen
void poll_switch()
{
  Switch =  !digitalRead(Schalter1) + 2 * !digitalRead(Schalter2) + 4 * !digitalRead(Schalter3) + 8 * !digitalRead(Schalter4);
}

void loop() 
{
  if (millis() > (time_old + 5000))  // Pin_Tacktrate alle 5 Sekunden abfragen
  {                                  // und Timer-Routine entsprechend anpassen
    Set_TAKTRATE();
    time_old = millis();
  }
   
   poll_switch();  // Codierschalter abfragen
                   // Wer keinen verbaut hat, aktiviert die folgende Zeile:
                   // Switch = 0; // .. oder eine andere Nummer angeben

   if (Switch != lastSwitch)
   {
     lastSwitch = Switch;   
     started = true;
     tone(tonePin, 800, 40);  // beim wechseln des Programms, Ton ausgeben
   }
   switch (Switch)
   {
     case 0: analogUhr();
      break;
     case 1: digitalUhr();
      break;
     case 2: play_Asteroids();
      break;
     case 3: play_SoloPong();     // Pong für einen Spieler
      break;
     case 4: play_Pong();         // Pong für zwei Spieler
      break;
     case 5: Testbild_2();        // Rasterbild
      break;
     case 6: ShowIldaTestbild();  // ILDA-Testbild
      break;                    
     case 7: Lauftext();         // Lauftext
      break;
     case 8: Testbild_5();        // Quadratisches Spinnennetz
      break;
     case 9: Annimation();        // Spielt mehrere Annimationen ab
      break;
     case 10: showMake();         // Spielereien mit dem MAKE: Schriftzug
      break;
     case 11: showMake2();        //              - " -
      break;
     case 12: showMake3();       //              - " -
      break;
     case 13: showBild();         // Enterprise NCC 1701
      break;
     case 14: showBild2();         // Enterprise NCC 1701 ... punktweise aufbauen
      break;
     case 15: showTestpicture();
      break;
   }     
   
}
