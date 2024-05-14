//////////////////////////////////////////////////////////////////////////////
// Variablen und Konstanten für das Spiel Asteorids
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#define W 200               // Spielfeldbreite
#define H 200               // Spielfeldhöhe

#define SHIPCOLOR 5         // Farbe vom Schiff 5=weiß
#define SHOTCOLOR 7         // Farebe der Schüsse
#define ASTEROIDCOLOR 8     //==> 8 = bunt / Zufallsfarben

#define MAX_ASTEROIDS 5               // Maximale Anzahl der Asteorieden
#define ASTEROID_TYPES 9              // Größe vom Asteorieden-Array
#define SIZEOF_ASTEROID_RECORD 18     // Anzahl der Vektoren von einem Asteorieden *2
#define DetectAsteroidAsteroidCollision true // Sollen sich Asteorieden gegenseitig abstoßen? evtl. Auskommentieren, dann wird weniger Rechenleistung benötigt.
#define MAX_SHOTS 5                   // Maximale Anzahl an Schüssen, die gleichzeitig dargestellt werden
#define Ships 3                       // Anzahl der Schiffe bis GameOver
#define AsteroidExplosionSound 1      // Welcher Sound soll bei der Explosion von Asteorieden abgespielt werden
#define ShipExplosionSound 2          // Welcher Sound soll bei der Explosion des Schiffs abgespielt werden

int shipOrientation = 1;              // In welche Richtung feuert und fliegt das Schiff
byte shipX = W/2;                     // X-Koordinate vom Schiff
byte shipY = H/2;                     // Y-Koordinate vom Schiff
byte ShipsLeft = Ships;               // Wie viele Schiffe verbleiben noch bis zum GameOver
long score = 0;                        // Variable für die erreichten Punkte
long HighScore = 0;                    // Variable für den HighScore                     
boolean running = true;               // Läuft das Spiel gerade?
boolean SoundStop = false;            // Variable für Sound
float AsteroidenGeschwindigkeit = 0.2;// Wie schnell bewegen sich die Asteorieden

typedef struct Asteroid {
  float z;
  int x;
  int y;
  byte type;  
  int directionX;
  int directionY;
  byte color;
} Asteroid;

Asteroid asteroids[MAX_ASTEROIDS];

typedef struct Shot {
  int x;
  int y;
  int directionX;
  int directionY;
} Shot;

Shot shots[MAX_SHOTS];

int shipVectors[8][4]
{
 {-2,6,2,6},{2,5,5,2},{6,2,6,-2},{5,-2,2,-5},{2,-5,-2,-5},{-2,-5,-5,-2},{-5,-2,-5,2},{-5,2,-2,5} 
};

byte asteroidsVectors[ASTEROID_TYPES][SIZEOF_ASTEROID_RECORD]
{
  {6,0,  0,6,  0,9,  6,15,  8,15,  18,9,  18,6,  15,6,  6,0 },
  {4,0,  0,4,  0,6,  4,10,  8,10,  12,6,  12,4,  10,4,  4,0 },
  {14,1, 7,3,  11,9, 1,14,  8,23,  17,20, 25,22, 23,4,  14,1}, 
  {8,1,  3,2,  1,7,  4,15,  9,11,  15,9,  12,5,  13,1,  8,1 }, 
  {8,0,  0,8,  0,12, 8,20,  16,20, 20,12, 20,8,  16,8,  8,0 },
  {19,1, 13,11,1,17, 14,23, 18,39, 26,23, 40,15, 26,10, 19,1}, 
  {1,15, 3,26, 14,35,27,34, 36,29, 40,16, 28,4,  14,3,  1,15}, 
  {16,0, 0,16, 0,24, 16,40, 32,40, 40,24, 40,16, 32,16, 16,0},
  {8,0,  0,16, 0,24, 16,25, 32,40, 40,24, 40,16, 32,0,  8,0 }  
};

// Das Explosionsgeräusch wird im Programmspeicher abgelegt, um Variabelspeicher zu sparen
const byte explosionFreq[200]  = {
187, 155, 147, 145, 158, 143, 141, 154, 171, 188,
179, 163, 164, 187, 147, 177, 173, 164, 164, 166,
158, 181, 198, 160, 179, 190, 142, 167, 188, 164,
144, 151, 610, 193, 197, 199, 189, 174, 165, 195,
148, 197, 154, 197, 183, 145, 175, 167, 146, 145,
189, 176, 175, 157, 154, 156, 143, 199, 195, 162,
182, 192, 181, 140, 169, 185, 168, 198, 168, 195,
178, 149, 180, 176, 173, 194, 170, 176, 157, 194,
157, 160, 145, 159, 191, 141, 177, 196, 148, 199,
171, 162, 171, 140, 178, 174, 168, 188, 190, 150,
187, 155, 147, 145, 158, 143, 141, 154, 171, 188,
179, 163, 164, 187, 147, 177, 173, 164, 164, 166,
158, 181, 198, 160, 179, 190, 142, 167, 188, 164,
144, 151, 610, 193, 197, 199, 189, 174, 165, 195,
148, 197, 154, 197, 183, 145, 175, 167, 146, 145,
189, 176, 175, 157, 154, 156, 143, 199, 195, 162,
182, 192, 181, 140, 169, 185, 168, 198, 168, 195,
178, 149, 180, 176, 173, 194, 170, 176, 157, 194,
157, 160, 145, 159, 191, 141, 177, 196, 148, 199,
171, 162, 171, 140, 178, 174, 168, 188, 190, 150
};

#endif
