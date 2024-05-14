//////////////////////////////////////////////////////////////////////////////
// Variablen und Konstanten für das Spiel Pong
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>

#ifndef PONG_H
#define PONG_H

#define PaddleA 34    // Pin, an dem das Paddle A angeschlossen ist
#define PaddleB 35    // Pin, an dem das Paddle B angeschlossen ist

#define W_Pong 220        // Spielfeld Breite
#define H_Pong 160        // Spielfeld Höhe
#define RandObenPong 16   // Spielfeldrand oben
byte mid = W_Pong / 2;    // Spielfeldmitte

byte Score, Score2 = 0;  // Spielstände
byte V=1;                // Ballgeschwindigkeit
int Trefferzaehler=0;    // Anzahl der Paddeltreffer für Spielgeschwindigkeit

int pauseCounter = 0;    // Variable für Spielpause
int ballx, bally;        // Position vom Ball
int dx, dy;              // Variable für Ballrichtung
byte paddleAy, paddleBy; // Position der Paddels

byte ballsize = 6;        // Ballgröße ( nicht verändern!!! sonst muss drawBall() angepasst werden)
byte paddleLength_A = 20; // Länge der Paddels A
byte paddleLength_B = 20; // Länge der Paddels B

boolean started = true;       // Läuft das Spiel gerade oder GameOver

#endif
