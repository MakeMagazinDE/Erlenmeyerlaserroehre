//////////////////////////////////////////////////////////////////////////////
// Routinen zum Abfragen des WII Nunchuk
// für das Spiel Asteroids
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <wii_i2c.h> // Diese Bibliothek muss installiert werden

// pins connected to the Nunchuk:
#define PIN_SDA 32
#define PIN_SCL 33

// ESP32 I2C port (0 or 1)
#define WII_I2C_PORT 0

// CPU id where the task will run (1=the core
// where your code usually runs, 0=the other core):
#define READ_TASK_CPU 0

// delay in milliseconds between controller reads:
#define READ_DELAY 30

 wii_i2c_nunchuk_state state;

int drive = 0;

void init_Nunchuk() { 
  if (wii_i2c_init(WII_I2C_PORT, PIN_SDA, PIN_SCL) != 0) {
    Serial.println("Error initializing nunchuk :(");
    return;
  } else {
    Serial.println("WII Nunchuck angeschlossen");
    if (wii_i2c_start_read_task(READ_TASK_CPU, READ_DELAY) != 0) Serial.println("Error creating task to read controller state");
  }  
}

boolean get_Firebutton()
{
   const unsigned char *data = wii_i2c_read_data_from_task();
  wii_i2c_decode_nunchuk(data, &state);
  return( state.z);
}

boolean get_CButton()
{
   const unsigned char *data  = wii_i2c_read_data_from_task();
  wii_i2c_decode_nunchuk(data, &state);
  return( state.c);
}



// Steuerung von Androids über den WII Nunchuk
void PollNunchuk()
{
  int tmpx;
  int tmpy;
  int shipXold, shipYold;
  int x, y;
  byte drive = 0;
  static unsigned long lastHigh;
  static unsigned long lastChange;
  static byte LastShipOrientation;
 const unsigned char *data = wii_i2c_read_data_from_task();   
  wii_i2c_decode_nunchuk(data, &state);
 
 tmpy = state.y;
 tmpx = state.x;
 buttonC = state.c; 
 buttonZ = state.z;
  
 if (buttonZ == HIGH) 
 {
   if ((lastHigh+100) > millis()) buttonZ = LOW;
    else  lastHigh = millis();
 }
 
 shipXold = shipX;
 shipYold = shipY;
 
   if (tmpx > 0) x = 1;
    else   if (tmpx < 0)  x = -1;
     else  x = 0;

  if (tmpy > 0) y = -1;
   else   if (tmpy < 0)  y = 1;
    else y = 0;
  if ((lastChange+100) < millis()) drive = 2; else drive = 0;
  
  LastShipOrientation = shipOrientation;
  
  if ((x== 0) & (y==-1)){shipOrientation=1; shipY -= drive;}              
  if ((x==-1) & (y==-1)){shipOrientation=2; shipY -= drive; shipX -=drive;}
  if ((x==-1) & (y== 0)){shipOrientation=3; shipX -= drive;}
  if ((x==-1) & (y== 1)){shipOrientation=4; shipY += drive; shipX -=drive;}
  if ((x== 0) & (y== 1)){shipOrientation=5; shipY += drive;}
  if ((x== 1) & (y== 1)){shipOrientation=6; shipY += drive; shipX +=drive;}
  if ((x== 1) & (y== 0)){shipOrientation=7; shipX += drive;}
  if ((x== 1) & (y==-1)){shipOrientation=8; shipY -= drive; shipX +=drive;}

  if (LastShipOrientation != shipOrientation)lastChange = millis();
   
  // Schiff berührt Spielfeldrand
  if ((shipX > (W-6)) |(shipX < 6) | (shipY > (H-6)) | (shipY < 6) )
  {
    shipY = shipYold;
    shipX = shipXold;
   }
 }

void show_nunchuk()
{
  for(int i=0;i<10;i++)
  {
    const unsigned char *data = wii_i2c_read_data_from_task(); 
    if (data) {
        wii_i2c_decode_nunchuk(data, &state);

        if (state.z) Serial.println(" Taste Z");
        if (state.c) Serial.println(" Taste C");
        Serial.print("State_x: ");  Serial.print(int(state.x));  Serial.print("| State_y: ");  Serial.println(int(state.y));
   } Serial.println("No Data");
    delay(1000);
  }
}
