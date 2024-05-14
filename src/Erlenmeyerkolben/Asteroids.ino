//////////////////////////////////////////////////////////////////////////////
// Asteroids für den Laser optimiert
// 
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////
#include "Asteroids.h"
#include <Preferences.h>
Preferences preferences;  //.. für den HighScore

boolean buttonZ   = false;  // für die Buttons vom WII Nunchuk
boolean buttonC   = false;
 
void play_Asteroids()
{ 
  if ( running == true)
  {
    beginFrame(); 
      if (AsteroidenGeschwindigkeit<5) AsteroidenGeschwindigkeit= 0.5 + score/200;  // Geschwindigkeit der Asteroiden langsam steigern  
      for (int i = 0 ; i < MAX_ASTEROIDS ; i++) moveAsteroid(i);    // Asteroiden anzeigen und bewegen
        PollNunchuk();  
      if (buttonZ == HIGH) newShot();                               // Schießen
      drawShots();                                                  // Schüsse anzeigen und bewegen
      detectShipCollisions();                                       // Kollision Schiff / Asteroid
      detectShotCollisions();                                       // Kollision Schuss / Asteroid
    endFrame();  
  } else ShipExplosion();                                           // Schiff wurde vom Asteroiden getroffen und explodiert
  
 }


void ShipExplosion()
{
  int schritt=1;
  static int phase=0;
  beginFrame();
  
  if(ShipsLeft < 1) 
   {
    GameOver(); 
   }else 
   {
    phase += schritt;   
  
  if (phase==1) setSound(2);
  if (phase <150)
  {  
    
    if ((shipX+phase+schritt <W) &(shipY+phase+schritt <H))
    {
      blanking(shipX+phase,shipY+phase);
      DrawLine(shipX+phase+schritt,shipY+phase+schritt,4);
    }
    if ((shipX+phase+schritt <W) &(shipY-phase-schritt >0))
    {
      blanking(shipX+phase,shipY-phase);
      DrawLine(shipX+phase+schritt,shipY-phase-schritt,4);
    }
    if ((shipX-phase-schritt >0) &(shipY+phase+schritt <H))
    {
      blanking(shipX-phase,shipY+phase);
      DrawLine(shipX-phase-schritt,shipY+phase+schritt,4);
    }
    if ((shipX-phase-schritt >0) &(shipY-phase-schritt >0))
    {
      blanking(shipX-phase,shipY-phase);
      DrawLine(shipX-phase-schritt,shipY-phase-schritt,4);
    }
  }    

  if ((phase >150) & (ShipsLeft>0))
  { 
    draw_string("Ships left",100,100, 1);
    drawInt(ShipsLeft,120,120,1);   
  } 

  if ((phase >200) & (ShipsLeft>0))
  { 
    init_Asteroids();
    running=true;
    phase=0;
  }   
  endFrame();
   }
}


void detectShipCollisions() 
{
  boolean collision = false;

  for (int j = 0 ; j < MAX_ASTEROIDS ; j++)
  {
    if (inPolygon(SIZEOF_ASTEROID_RECORD, asteroids[j], shipX, shipY))
    {
      collision = true;      
    } else if (inPolygon(SIZEOF_ASTEROID_RECORD,asteroids[j], shipX+shipVectors[shipOrientation-1][0], shipY+shipVectors[shipOrientation-1][1])) 
     {
      collision = true;      
     } else if (inPolygon(SIZEOF_ASTEROID_RECORD, asteroids[j] , shipX+shipVectors[shipOrientation-1][2], shipY+shipVectors[shipOrientation-1][3])) 
      {
        collision = true;      
      }
   }
   drawShip(SHIPCOLOR);
      
  if (collision == true )
  {
    running = false;
    ShipsLeft = ShipsLeft - 1;
  }
}

void detectShotCollisions() {
byte color = 2;
for (int i = 0 ; i < MAX_SHOTS ; i++)
 if (shots[i].x > 0)
 {
  for (int j = 0 ; j < MAX_ASTEROIDS ; j++)
    if (inPolygon(SIZEOF_ASTEROID_RECORD, asteroids[j], shots[i].x, shots[i].y)) 
    {
      shots[i].x =-1;
      brakeAsteroid(j );
      score += MAX_ASTEROIDS-asteroids[j].type;
      setSound(AsteroidExplosionSound);  
    }
 }
}

void brakeAsteroid(byte j)  // Große Asteroiden zerfallen in 2 kleine Stücke
{
 if (asteroids[j].type>3)
 {
   asteroids[j].type=1;
 } else newAsteroid(j); 
}


void newAsteroid(byte z)
{
  byte max_x=0;
  byte max_y=0;
  
 if (ASTEROIDCOLOR > 7 )asteroids[z].color=+random(1,8);
  else asteroids[z].color = ASTEROIDCOLOR;
 
 // Große Asteroiden nur jeweils einmal 
 asteroids[z].type = random(0,ASTEROID_TYPES);
 if ( asteroids[z].type > 4)
 {
  for (int i=0 ; i < MAX_ASTEROIDS ; i++)
  {
   if ((i != z)&(asteroids[i].type == asteroids[z].type)) 
   {
    asteroids[z].type -= 5;
    break;
   }
  }
 }
 
 // Maximale Größen des Asteroiden ermitteln
 for (int i = 0 ; i < SIZEOF_ASTEROID_RECORD-1 ; i +=2)
 {
  if (asteroidsVectors[asteroids[z].type][i]   > max_x) max_x = asteroidsVectors[asteroids[z].type][i];
  if (asteroidsVectors[asteroids[z].type][i+1] > max_y) max_y = asteroidsVectors[asteroids[z].type][i+1];
 }

 // Ort des Auftauchens zufällig an den Rändern
 byte tmpx= random(0,(W - 2*max_x)); 
 byte tmpy= random(0,(H - 2*max_y));

 // Bewegungsrichtungen des Asteroiden festlegen
 do{ 
    asteroids[z].directionX=-3+random(0,7); 
    asteroids[z].directionY=-3+random(0,7);
 }while((asteroids[z].directionX == 0) | (asteroids[z].directionY == 0));
 
 if ((asteroids[z].directionX > 0) & (asteroids[z].directionY > 0))  {asteroids[z].x = tmpx;   asteroids[z].y = 0;}
 if ((asteroids[z].directionX <=0) & (asteroids[z].directionY >0 ))  {asteroids[z].x = W-max_x; asteroids[z].y = tmpy;}
 if ((asteroids[z].directionX > 0) & (asteroids[z].directionY <=0))  {asteroids[z].x = 0;   asteroids[z].y = tmpy;}
 if ((asteroids[z].directionX <=0) & (asteroids[z].directionY <=0))  {asteroids[z].x = tmpx; asteroids[z].y = H-max_y;}
//Ausgabe4(asteroids[z].x,asteroids[z].y,asteroids[z].directionX,asteroids[z].directionY );
 if (detectAsteroidCollisions(z) >= 0) newAsteroid(z);
}

void moveAsteroid(byte n)
{
 if (buttonC==LOW)
 {
    asteroids[n].z += AsteroidenGeschwindigkeit; 
    // Bewegungsgeschwindigkeit in Abhängigkeit von der Größe
    if (asteroids[n].z > ( asteroids[n].type+2))
    {  
      asteroids[n].x += asteroids[n].directionX;
      asteroids[n].y += asteroids[n].directionY;
      asteroids[n].z = 0; 
 
      //------------   Kollision zwischen zwei Asteroiden ----------------------------
      // evtl. Auskommentieren, dann wird weniger Rechenleistung benötigt!
      if (DetectAsteroidAsteroidCollision == true)  AsteroidAsteroidCollision(n);
      
      for (int i = 0 ; i <= (SIZEOF_ASTEROID_RECORD-1) ; i += 2)
      {
        if (((asteroidsVectors[asteroids[n].type][i]+asteroids[n].x) > W)   |
            ((asteroidsVectors[asteroids[n].type][i+1]+asteroids[n].y) > H) | 
            ((asteroidsVectors[asteroids[n].type][i]+asteroids[n].x) < 0)   | 
            ((asteroidsVectors[asteroids[n].type][i+1]+asteroids[n].y) < 0)) 
            {
              newAsteroid(n); 
              return;           
            }
         }
    }
 }
    drawAsteroid(asteroids[n],2);
}

int detectAsteroidCollisions(byte n)
{
  for (int i = 0 ; i < MAX_ASTEROIDS ; i++)
  {
   if (n != i)
    for ( int t=0 ; t < SIZEOF_ASTEROID_RECORD-1 ; t +=2)
        {
          byte typeI = asteroids[i].type;
          if (inPolygon(SIZEOF_ASTEROID_RECORD, asteroids[n], asteroids[i].x + asteroidsVectors[typeI][t] ,  asteroids[i].y + asteroidsVectors[typeI][t+1]))
          {
           return i;
           }
        }
  }
 return -1;        
}

void AsteroidAsteroidCollision(byte n)
{
   int tmpx, tmpy; 
   int t = detectAsteroidCollisions(n);
   if (t >= 0)
        {
           asteroids[n].x -= asteroids[n].directionX;
           asteroids[n].y -= asteroids[n].directionY;
           tmpx=asteroids[n].directionX ;
           tmpy=asteroids[n].directionY ;
           asteroids[n].directionX = asteroids[t].directionX;
           asteroids[n].directionY = asteroids[t].directionY;
           asteroids[t].directionX = tmpx;
           asteroids[t].directionY = tmpy;
           asteroids[t].x += asteroids[t].directionX;
           asteroids[t].y += asteroids[t].directionY;
        } 
}



bool inPolygon(byte nvect, struct Asteroid a, int x, int y) {
  byte i;
  int xv0, xv1, yv0, yv1;
  boolean inside = false;
  byte type = a.type;
  
  for (i=0 ; i<=(nvect-4); i += 2 ) {
    xv0 = a.x + asteroidsVectors[type][i];
    yv0 = a.y + asteroidsVectors[type][i+1];
    xv1 = a.x + asteroidsVectors[type][i+2];
    yv1 = a.y + asteroidsVectors[type][i+3];
    if ( ((yv0 > y) != (yv1 > y)) &&  (x < (xv1 - xv0) * (y - yv0) / (yv1 - yv0) + xv0) )
       inside = !inside;
  }
  return inside;
}

void newShot()
{
 for (int i=0; i < MAX_SHOTS ; i++)
 {
  if  (shots[i].x < 0) // noch Schuss frei?
  {
    sound_Fire();
    shots[i].x = shipX;
    shots[i].y = shipY;
    switch (shipOrientation)
    {
      case 1:shots[i].directionX = 0; shots[i].directionY =-1; break;
      case 2:shots[i].directionX =-1; shots[i].directionY =-1; break;
      case 3:shots[i].directionX =-1; shots[i].directionY = 0; break;
      case 4:shots[i].directionX =-1; shots[i].directionY = 1; break;
      case 5:shots[i].directionX = 0; shots[i].directionY = 1; break;
      case 6:shots[i].directionX = 1; shots[i].directionY = 1; break;
      case 7:shots[i].directionX = 1; shots[i].directionY = 0; break;
      case 8:shots[i].directionX = 1; shots[i].directionY =-1; break;
    }
    return;
  }
 }
}

void drawShots()
{
  byte color=SHOTCOLOR;
  for (int i=0 ; i < MAX_SHOTS ; i++)
  {
    if (shots[i].x > 0)
    {
      blanking (shots[i].x , shots[i].y);
      shots[i].x += 5*(shots[i].directionX);
      shots[i].y += 5*(shots[i].directionY);
      if ((shots[i].x < 5 ) | (shots[i].y < 5 ) | (shots[i].x >= (W-5)) | (shots[i].y >= (H-5)) )
      {
       shots[i].x = -1; 
      }else  DrawLine(shots[i].x ,shots[i].y, color);
    }
  }
}




void drawAsteroid(struct Asteroid a,byte color) 
{
 blanking(asteroidsVectors[a.type][0]+a.x, asteroidsVectors[a.type][1]+a.y);  
 for ( int i = 2 ;  i < (SIZEOF_ASTEROID_RECORD-1) ; i +=2)
 {
  DrawLine(asteroidsVectors[a.type][i]+a.x, asteroidsVectors[a.type][i+1]+a.y, a.color);
 } 
}



void drawShip(byte color) 
{
  blanking(shipX,shipY);
  DrawLine(shipX+shipVectors[shipOrientation-1][0], shipY+shipVectors[shipOrientation-1][1], color);
  DrawLine(shipX+shipVectors[shipOrientation-1][2], shipY+shipVectors[shipOrientation-1][3], color); 
  DrawLine(shipX,shipY,color); 
}

void writeHighScore()
{
   byte result;
  preferences.begin("Erlenmeyer", false); 
  result = preferences.putLong("Highscore", HighScore);
  preferences.end();
}

void readHighScore()
{
   byte result;
  preferences.begin("Erlenmeyer", false); 
  HighScore = preferences.getLong("Highscore");
  preferences.end();
}

 void GameOver()
 {
  static int z;
   z++;
   PollNunchuk();
   setSound(3);
   SoundStop = true;
  if (score > HighScore) 
  {
   HighScore = score;
  writeHighScore(); 
  }
  if (buttonC == HIGH) newGame();

  if (z < 100)
  { PointerSet=0;
    draw_string("Game",50,100, 1);
    draw_string("over",60,115, 1);
    endFrame();
  } else if (z < 200){ 
    PointerSet=0; 
    draw_string("Score",50,100, 1);
    drawInt(score,110,100,1);
    endFrame();
  } else if (z < 300){ 
    PointerSet=0; 
    draw_string("HighScore",30,100, 1);
    drawInt(HighScore,50,115, 1);
    endFrame();
  } else   z= 0;
  
 }

void newGame()
{  
 SoundStop = false;
 setSound(4);   
 for (int i = 0 ;  i < 100 ; i++)
 {
  beginFrame();
  draw_string("New", 100, 100, 1);
  draw_string("Game", 120, 120, 1); 
  endFrame();
 }
  ShipsLeft = Ships;
  score = 0;
  init_Asteroids();

}

void init_Asteroids()
{ 
  readHighScore(); 
  shipX = W/2;
  shipY = H/2;
  running = true;
  for (int i = 0; i < MAX_SHOTS     ; i++)  shots[i].x = -1;
  for (int i = 0; i < MAX_ASTEROIDS ; i++)  newAsteroid(i);
  PollNunchuk(); 
}
