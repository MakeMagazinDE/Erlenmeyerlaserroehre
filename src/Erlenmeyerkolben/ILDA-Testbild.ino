//////////////////////////////////////////////////////////////////////////////
// ShowIldaTestbild() generiert ein Testbild, das ähnlich wie 
// das original ILDA-Testbild zum Einstellen der Galvos 
// und zum Geschwindigkeit Testen verwendet werden kann.
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

void ShowIldaTestbild()
{
 byte color;
 beginFrame();
  draw_string("Y", 125, 30, 1);

  // obere Stufenline
  color = 3;
  blanking(85,  50);
  DrawLine(110, 50, color);
  blanking(110, 52);
  DrawLine(110, 58, color);
  blanking(110, 60);
  DrawLine(180, 60, color);

  //2. Stufenline
  color = 7;
  blanking(127, 65);
  DrawLine(127, 75, color); // Senkrechte Linie
  blanking(85,  70);
  DrawLine(124, 70, color);
  blanking(130, 70);
  DrawLine(180, 70, color);

 // Mittelpfeil
  color = 1;
  blanking(30,  127);
  DrawLine(220, 127, color);
  DrawLine(210, 117, color);
  
  draw_string("X", 230, 124, 1);
  
 // Mittelkreuz
  color = 3;
  blanking(134, 127);
  DrawLine(120, 127, color);
  blanking(127, 120);
  DrawLine(127, 134, color);
    
  DrawCircle(127, 127, 30, 5);
  DrawSquare(96, 96, 158, 158, 6);

  //Linien unter dem Kreis
  blanking(135, 165);
  DrawLine(120, 165, 1);
  blanking(115, 170);
  DrawLine(140, 170, 2);
  blanking(145, 175);
  DrawLine(110, 175, 3);

  color = 7;
  DrawSquare(110, 200, 114, 204, color);
  DrawSquare(120, 190, 123, 193, color);
  DrawSquare(130, 200, 132, 202, color);
  DrawSquare(140, 190, 141, 191, color);
  
 endFrame();  
 
}
