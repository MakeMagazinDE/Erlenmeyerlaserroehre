///////////////////////////////////////////////////////////////////
// Pong Spiel für Galvo und Laser
// Ulrich Schmerold
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////

void play_Pong()
{
  paddleLength_A = 20;
  if (Trefferzaehler>20) V=3; else if (Trefferzaehler>8) V=2; else V=1;// Geschwindigkeit im Spielverlauf steigern
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
  beginFrame();               // Frame begin
   moveBall(); // Ball bewegen
    drawBounds();                 // Spielfelränder zeichnen
    pollPos();                    // Position der Paddels ermitteln
    drawPaddleA(paddleAy);        // Paddle A Zeichnen
    drawInt (Score, mid-50, 0, 1);// Score A zeichnen
    if (ballx < mid) drawBall();  // Den Ball zeichen, wenn er sich links von der Mittelline befindet
    drawNet();                    // Netz zeichnen
    if (ballx >= mid) drawBall(); // Den Ball zeichen, wenn er sich rechts von der Mittelline befindet
    drawInt (Score2, mid+40,0,1); // Score B zeichnen
    drawPaddleB(paddleBy);        // Paddle B Zeichnen
  endFrame();                  // Frame ende
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
 if (started == false) gameOver();  // Game Over
}

void play_SoloPong() // Pong für einen Spieler
{
   paddleLength_A = H_Pong;                                               // Das Paddle A geht von unten bis oben
   if (Trefferzaehler>20) V=3; else if (Trefferzaehler>8) V=2; else V=1;// Geschwindigkeit im Spielverlauf steigern
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
  beginFrame();               // Frame begin
   moveBall(); // Ball bewegen
    drawBounds();                 // Spielfelränder zeichnen
    pollPos();                    // Position der Paddels ermitteln
    drawPaddleA(paddleAy);        // Paddle A Zeichnen
    drawInt (Score, mid-50, 0, 1);// Score A zeichnen
    if (ballx < mid) drawBall();  // Den Ball zeichen, wenn er sich links von der Mittelline befindet
    drawNet();                    // Netz zeichnen
    if (ballx >= mid) drawBall(); // Den Ball zeichen, wenn er sich rechts von der Mittelline befindet
    drawInt (Score2, mid+40,0,1); // Score B zeichnen
    drawPaddleB(paddleBy);        // Paddle B Zeichnen
  endFrame();                  // Frame ende
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
 if (started == false) gameOver();  // Game Over
 
}

// Spielinitialisierung
void init_Pong() {

  ballx = random(40, 57);
  bally = random(56, 73);
  dx = 1;
  if (random(0, 2) == 0) {
    dy = 1;
  } else {
    dy = -1;
  }
  Score = 0;
  Score2 = 0;
  V=1;
}



// Ball bewegen und prüfen, ob er ein Paddel oder den Spielfeldrand trifft,
// oder das Spielfeld verlässt.
void moveBall() {

  if (ballx <= 2) { // links aus dem Feld
    if (Score2 >= 9) {
      gameOver();
      return;
    }
    ballx = random(W_Pong/2, (3*W_Pong)/4);
    bally = random(H_Pong/4, (3*H_Pong)/4);
    dx = -1;
    if (random(0, 2) == 0) {
      dy = 1;
    } else {
      dy = -1;
    }
    pauseCounter = 40;  // Pause bei neuem Ball  
  }
  
  if (ballx > (W_Pong-ballsize+2)) {// rechts aus dem Feld
    Score++;
    scoreSound();
    if (Score == 9) {
      gameOver();
      return;
    }
    ballx = random(W_Pong/4, W_Pong/2);
    bally = random(H_Pong/4, (3*H_Pong)/4);
    dx = 1;
    if (random(0, 2) == 0) {
      dy = 1;
    } else {
      dy = -1;
    }
    pauseCounter = 40;  // Pause bei neuem Ball
  }

  // prüfen, ob der Ball Paddle A trifft
  if (ballx <= 4) {
    if ((bally >= (paddleAy-ballsize)) && (bally < (paddleAy+paddleLength_A))) {
      dx = 1;
      Trefferzaehler++;
      hitSound();
    }
  }

  // prüfen, ob der Ball Paddle B trifft
  if (ballx >= W_Pong-ballsize) {
    if ((bally >= (paddleBy-ballsize)) && (bally < (paddleBy+paddleLength_B))) {
      dx = -1;
      Trefferzaehler++;
      hitSound();
    }
  }

 // Ball trifft oberen Spielfeldrand
  if (bally <= RandObenPong) {
    bounceSound();
    dy = 1;
  }
  // Ball trifft unteren Spielfeldrand
  if (bally >= (H_Pong-ballsize)) {
    bounceSound();
    dy = -1;
  }
 
  ballx = ballx + V*dx;
  bally = bally + V*dy;
}


void drawBall() {
  const byte color = 1;
    blanking(ballx+3, bally+3);
    blanking(ballx+2, bally);
    DrawLine(ballx+4, bally,   color);
    DrawLine(ballx+6, bally+2, color);
    DrawLine(ballx+6, bally+4, color);
    DrawLine(ballx+4, bally+6, color);
    DrawLine(ballx+2, bally+6, color);
    DrawLine(ballx,   bally+4, color);
    DrawLine(ballx,   bally+2, color);
    DrawLine(ballx+2, bally,   color);
    DrawLine(ballx+4, bally,   color);
}

void drawBounds()  // Spielfeldgrenzen oben und unten zeichnen
{
  byte speed = 5;
  blanking(8, RandObenPong);
  DrawSpeedLine(W_Pong-2, RandObenPong,2);
  blanking(W_Pong-2, H_Pong);
  DrawSpeedLine(8, H_Pong,2); 
}

void drawNet() {
  const byte color = 2;
  byte lg = H_Pong/13;
  for(byte y = 11 ; y <= H_Pong-lg ; y = y+2*lg) {
    blanking(mid, y+lg);
    DrawLine(mid, y+2*lg, color);    
  }
}

 void pollPos()
{
  paddleAy = map(analogRead(PaddleA),0, 4095, 1, (H_Pong-paddleLength_A));
  paddleBy = map(analogRead(PaddleB),0, 4095, 1, (H_Pong-paddleLength_B));
}

void drawPaddleA(int y)   // Paddle A Zeichen
{
  blanking(4, y+paddleLength_A);
  DrawLine(4, y, 7);
 }

void drawPaddleB(int y)   // Paddle B Zeichen 
{
  blanking(W_Pong, y);
  DrawLine(W_Pong, y+paddleLength_B, 7);
 }
 
void gameOver() 
{
  do  // Game Over zeichnen bis Spiel neu gestartet wird
  {
   beginFrame(); 
    draw_string("GAME", 40, 40, 1);
    draw_string("OVER", 50, 60, 1);
    started = false;
//    if (StartButton == false)started = true;
   endFrame();
   pollPos();
  } while (started == false); 
  Score  = 0;
  Score2 = 0;
  Trefferzaehler=0;
}


void hitSound() 
{
  tone(tonePin, 932, 20);
}

void bounceSound() 
{
  tone(tonePin, 458, 20);
}

void scoreSound() 
{
  tone(tonePin, 987, 400);
}

void winSound() 
{
 tone(tonePin, 987, 400);
}
