//////////////////////////////////////////////////////////////////////////////
// Verschiedene Routinen zum Zeichnen mit dem Laser
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#define  maxDistDrawn 4
#define  postDraw     7
#define  preBlanking  1
#define  postBlanking 7

/////////////////////////////////////////////////////////////////////////////

  // möglichst schnelles Positionieren der Galvos
  // bei abgeschalteten Lasern. 
void blanking(byte x, byte y)
{
  DrawFastLine(x,y,0);
}


  // Diese Routine wird zum Zeichen von Linien aufgerufen.
  // Zu Testzwecken können die darin enthaltenen Methoden
  // aktiviert oder auskommentiert werden.
  // Mein Favorit ist "DrawMaxDistanceLine".
void DrawLine(byte x1, byte y1, byte color)
{
   DrawMaxDistanceLine( x1, y1, color); // mein Favorit
   //DrawSpeedLine( x1, y1, color);     // sehr schnell
   //DrawBresenhamLine( x1, y1, color); // sehr genau
}


  // Linie zeichnen, mit "maxDistDrawn" - Abstand zwischen zwei Punkte.
  // Die Geschwindigkeit kann durch die Konstannte "maxDistDrawn" bestimmt werden.
void DrawMaxDistanceLine (byte x, byte y, byte color)
{
  int z=0;
  float Schrittx, Schritty;
  float temPosX, temPosY; 
  float errx = (x-current_pos_x);
  float erry = (y-current_pos_y);
  temPosX = current_pos_x;
  temPosY = current_pos_y;

  if (abs(errx) > abs(erry)) z = abs(errx) / maxDistDrawn;
    else  z = abs(erry) / maxDistDrawn;
  Schrittx = errx / z;
  Schritty = erry / z;

  while(z-- > 0)
  {
    temPosX += Schrittx;
    temPosY += Schritty;  
    setPixel(temPosX, temPosY , color);
  }
  for (int i = 0; i < postDraw; i++) setPixel(x, y , color); 
}


  // Linie Zeichnen mit dem Bresenham-Algorithmus
  // sehr exackt, aber langsam, da jeder Punkt gezeichnet werden muss
void DrawBresenhamLine(byte x1, byte y1, byte color)
{
   int dx =  abs(x1-current_pos_x), sx = current_pos_x<x1 ? 1 : -1;
   int dy = -abs(y1-current_pos_y), sy = current_pos_y<y1 ? 1 : -1; 
   int err = dx+dy, e2; // error value e_xy 
   while(1)
   { 
      setPixel(current_pos_x, current_pos_y, color);
      if (current_pos_x==x1 && current_pos_y==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; current_pos_x += sx; } 
      if (e2 <= dx) { err += dx; current_pos_y += sy; } 
   }
    
   // Dem Galvo extra  Zeit geben, um zur Endposition zu kommen
   for (int i = 0; i < postDraw; i++)  setPixel(current_pos_x, current_pos_y, color);
}

  // schnelle Linie Zeichnen mit einem Bresenham-Algorithmus,
  // dabei wird nicht jeder Punkt gesetzt, sondern "maxDistDraw" übersprungen
void DrawSpeedLine(byte x1, byte y1, byte color)
{
   byte z;
   int dx =  abs(x1-current_pos_x), sx = current_pos_x<x1 ? 1 : -1;
   int dy = -abs(y1-current_pos_y), sy = current_pos_y<y1 ? 1 : -1; 
   int err = dx+dy, e2; // error value e_xy
  while(abs(err) > maxDistDrawn){
      int dxy=abs(current_pos_x-x1)+abs(current_pos_y-y1);
      if (( z++ % maxDistDrawn)==1)  setPixel(current_pos_x,current_pos_y,color);
      if (current_pos_x==x1 && current_pos_y==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; current_pos_x += sx; } 
      if (e2 <= dx) { err += dx; current_pos_y += sy; } 
   }

   while(1)
   { 
      setPixel(current_pos_x,current_pos_y,color);
      if (current_pos_x==x1 && current_pos_y==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; current_pos_x += sx; } 
      if (e2 <= dx) { err += dx; current_pos_y += sy; } 
   }
    
   // Dem Galvo extra  Zeit geben, um zur Endposition zu kommen
  for (int i = 0; i < postDraw; i++)  setPixel(x1, y1, color);
}


  // Sehr schnelles Zeichnen einer langen Linie
  // dabei werden die Schritte, die zurückgelegt werden,
  // zum Ziel hin immer kleiner, damit der Galvo Zeit zum Bremsen hat
void DrawFastLine(byte x1, byte y1, byte color)
{
 int rx,ry; 
 int restx, resty;

 int dx =  abs(x1-current_pos_x);
 if ((x1-current_pos_x) >0 ) rx=1; else rx=-1;
 int dy =  abs(y1-current_pos_y); 
 if ((y1-current_pos_y) >0 ) ry=1; else ry=-1;
  do
  {
    restx = x1-current_pos_x;
    resty = y1-current_pos_y; 
    dx = restx / 8; 
      if ((restx != 0)&(dx == 0)) dx = rx;
    dy = resty / 8; 
      if ((resty != 0)&(dy == 0)) dy = ry;
    setPixel(current_pos_x + dx,(current_pos_y + dy), color);
  } while (((current_pos_x-x1) != 0) | ((current_pos_y-y1) != 0));
  
  // Dem Galvo extra  Zeit geben, um zur Endposition zu kommen
  for (int i = 0; i < postDraw; i++)  setPixel(x1,y1,color); 
}


void BlankingLine(byte x1, byte y1, byte color)
{
 int rx,ry; 
 int restx, resty;

 int dx =  abs(x1-current_pos_x);
 if ((x1-current_pos_x) >0 ) rx=1; else rx=-1;
 int dy =  abs(y1-current_pos_y); 

 // Dem Galvo extra  Zeit geben, bevor er zur neuen Positon startet
 for (int i = 0; i < preBlanking; i++)  setPixel(x1,y1,color); 

 if ((y1-current_pos_y) >0 ) ry=1; else ry=-1;
  do
  {
    restx = x1-current_pos_x;
    resty = y1-current_pos_y; 
    dx = restx / 8; 
      if ((restx != 0)&(dx == 0)) dx = rx;
    dy = resty / 8; 
      if ((resty != 0)&(dy == 0)) dy = ry;
    setPixel(current_pos_x + dx,(current_pos_y + dy), color);
  } while (((current_pos_x-x1) != 0) | ((current_pos_y-y1) != 0));
  
  // Dem Galvo extra  Zeit geben, um zur Endposition zu kommen
  for (int i = 0; i < postBlanking; i++)  setPixel(x1,y1,color); 
}


  // Kreisvariante des Bresenham-Algorithmus
  // Die Berechnung ist wesentlich schneller als eine Berechnung über Winkelfunktionen
void DrawCircle(int xm, int ym, int _r,byte color)
{
  int r,x,y,err;
  blanking( xm + _r, ym);
  for (byte i = 0 ; i < 4 ; i++)
  {
    r=_r;
    x = -r, y = 0, err = 2-2*r; // II. Quadrant 
   do{
    switch(i){
     case 0: setPixel(xm-x, ym+y,color);  //   I. Quadrant 
      break;     
     case 1: setPixel(xm-y, ym-x,color); //  II. Quadrant 
      break;  
     case 2: setPixel(xm+x, ym-y,color); // III. Quadrant 
      break;  
     case 3:setPixel(xm+y, ym+x,color); //  IV. Quadrant 
    } 
      r = err;
      if (r <= y) err += ++y*2+1;           
      if (r > x || err > y) err += ++x*2+1; 
   } while (x < 0);
  }
   for (int i = 0; i < postDraw; i++) setPixel(xm+_r, ym,color);
}


  // Zeichnet ein Rechteck aus Mittelpunkt und  Abstand zum Mittelpunt
void DrawSquare(byte left, byte top, byte right, byte botton, byte color)
{
  blanking( left, top);
  DrawLine( right, top, color);
  DrawLine( right, botton, color);  
  DrawLine( left, botton, color);
  DrawLine( left, top, color);
}


void drawMeldung(String Meldung, int posX, int posY,int dauer , byte color )
{
  unsigned long Begin = millis();
  while ((Begin+dauer) > millis())
  {
     beginFrame();
     draw_string(Meldung, posX, posY, color); 
     endFrame();
  }
  
}
