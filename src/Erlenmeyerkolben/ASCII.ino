////////////////////////////////////////////////////////////////////////////////////////
// Verschiedene Routinen zum Anzeigen von Zeichen, Integerwerten, Strings und Lauftext
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////
byte _color;

void drawInt(int z, byte x, byte y, byte color)   // Anzeige einer Integerzahl
{
 String s = String(z);
 int l = s.length();
 for (int i = 0 ; i < l ; i++) draw_letter(s[i], x+10*i, y, color);
}

void draw_string(String text, int x, int y, byte color)  // Anzeige von einem String
{  
    text.toUpperCase(); // Ich habe bisher nur Großbuchstanben definiert
    blanking(x, y);
    int i = 0;
    while (text.charAt(i) != '\0')
    {
       draw_letter(text.charAt(i), x+i*10, y, color); 
       i ++;
    }  
}

void marquee(String text, int x, int y, int x_length, byte color)  // Lauftext anzeigen
{
  String tmp = "";
  int z = x_length;
  static int i,zz;
  for (int i = 0 ; i < z ; i++) tmp = tmp+" ";
  text = tmp+text+tmp;
  int l = text.length();
  zz++;
  if (zz > 10)
  {
    i++;
    zz = 0;
  }
  if (i > l) i = 1; 
  draw_string(text.substring(i,i+z), 10+x-zz, y, color);
}

void draw_letter(byte letter, byte x, byte y, byte color)
{
  _color = color;
  switch (letter){
    case '1':
     drawLine(x+3,y+5,x+7,y);
     drawLineTo(x+7,y+10);
    break;
     
   case '2':
    drawLine(x+2,y,x+8,y);
    drawLineTo(x+8,y+5);
    drawLineTo(x+2,y+5);
    drawLineTo(x+2,y+10);
    drawLineTo(x+8,y+10);
   break;
   case '3':
    drawLine(x+2,y,x+8,y);
    drawLineTo(x+8,y+5);
    drawLineTo(x+4,y+5);
    drawLine(x+8,y+5,x+8,y+10);
    drawLineTo(x+2,y+10);    
   break;
   case '4':
    drawLine(x+3,y,x+3,y+6);
    drawLineTo(x+10,y+6);
    drawLine(x+8,y+2,x+8,y+10);
   break;
   case '5':
    drawLine(x+8,y,x+2,y);
    drawLineTo(x+2,y+5);
    drawLineTo(x+8,y+5);
    drawLineTo(x+8,y+10);
    drawLineTo(x+2,y+10);
   break;
   case '6':
     drawLine(x+6,y+1,x+1,y+1);
     drawLineTo(x+1,y+11);
     drawLineTo(x+7,y+10);
     drawLineTo(x+7,y+5);
     drawLineTo(x+1,y+5);
   break;
   case '7':
     drawLine(x+1,y,x+7,y);
     drawLineTo(x+2,y+11);
   break;
   case '8':
    drawLine(x+2,y,x+8,y);
    drawLineTo(x+8,y+10);
    drawLineTo(x+2,y+10);
    drawLineTo(x+2,y);
    drawLine(x+2,y+5,x+8,y+5);
   break;
   case '9':
     drawLine(x+8,y+5,x+2,y+5);
     drawLineTo(x+2,y);
     drawLineTo(x+8,y);
     drawLineTo(x+8,y+10);
     drawLineTo(x+2,y+10);
   break;
   case '0':
    drawLine(x+2,y,x+8,y);
    drawLineTo(x+8,y+10);
    drawLineTo(x+2,y+10);
    drawLineTo(x+2,y);
   break;
   case 'A':
      drawLine(x,y+11,x+5,y);
      drawLineTo(x+9,y+11);
      drawLine(x+2,y+5,x+7,y+5);
   break;
   case 'B':
    drawLine(x+2,y,x+8,y);
    drawLineTo(x+8,y+10);
    drawLineTo(x,y+10);
    drawLineTo(x,y);
    drawLine(x+2,y+5,x+7,y+5);
   break;
   case 'C':
    drawLine(x+8,y,x+1,y);
    drawLineTo(x+1,y+10);
    drawLineTo(x+8,y+10);
   break;
   case 'D':
    drawLine(x+1,y,x+8,y);
    drawLineTo(x+8,y+10);
    drawLineTo(x+1,y+10);
    drawLineTo(x+1,y);
   break;
   case 'E':
    drawLine(x+8,y,x+1,y);
    drawLineTo(x+1,y+10);
    drawLineTo(x+8,y+10);
    drawLine(x+1,y+4,x+6,y+4);
   break;
   case 'F':
    drawLine(x+8,y,x+1,y);
    drawLineTo(x+1,y+10);
    drawLine(x+1,y+4,x+5,y+4);   
   break;
   case 'G':
    drawLine(x+8,y,x,y);
    drawLineTo(x,y+10);
    drawLineTo(x+6,y+10);
    drawLineTo(x+6,y+4);
    drawLineTo(x+2,y+4);   
   break;
   case 'H':
     drawLine(x+1,y,x+1,y+11);
     drawLine(x+8,y,x+8,y+11);
     drawLine(x+1,y+4,x+8,y+4);     
   break;
   case 'I':
      drawLine(x+4,y,x+7,y);
      drawLine(x+5,y,x+5,y+10);
      drawLine(x+4,y+10,x+7,y+10);
   break;
   case 'J':
      drawLine(x+4,y,x+7,y);
      drawLineTo(x+7,y+10);
      drawLineTo(x+2,y+10);
      drawLineTo(x+2,y+7);
      drawLineTo(x+5,y+5);
   break;
   case 'K':
      drawLine(x+1,y,x+1,y+11);
      drawLine(x+2,y+4,x+7,y+10);
      drawLine(x+2,y+4,x+7,y);
   break;
   case 'L':
      drawLine(x+2,y,x+2,y+10);
      drawLineTo(x+7,y+10);
   break;
   case 'M':
      drawLine(x,y+11,x,y);
      drawLineTo(x+3,y+5);
      drawLineTo(x+7,y);
      drawLineTo(x+7,y+10);
   break;
   case 'N':
      drawLine(x+2,y+10,x+2,y);
      drawLineTo(x+8,y+10);
      drawLineTo(x+8,y);
   break;
   case 'O':
    drawLine(x+1,y,x+8,y);
    drawLineTo(x+8,y+10);
    drawLineTo(x+1,y+10);
    drawLineTo(x+1,y);
    drawLineTo(x+1,y);
   break;
   case 'P':
    drawLine(x+2,y+10,x+2,y);
    drawLineTo(x+6,y);
    drawLineTo(x+6,y+5);
    drawLineTo(x+3,y+5);
   break;
   case 'Q':
    drawLine(x+3,y,x+8,y);
    drawLineTo(x+7,y+10);
    drawLineTo(x+1,y+10);
    drawLineTo(x+1,y);
    drawLine(x+6,y+8,x+10,y+11);
   break;
   case 'R':
    drawLine(x+2,y+10,x+2,y);
    drawLineTo(x+6,y);
    drawLineTo(x+6,y+5);
    drawLineTo(x+3,y+5);
    drawLineTo(x+8,y+12);
   break;
   case 'S':
    drawLine(x+8,y,x+1,y);
    drawLineTo(x+2,y);
    drawLineTo(x+2,y+5);
    drawLineTo(x+8,y+5);
    drawLineTo(x+8,y+10);
    drawLineTo(x+1,y+10);     
   break;
   case 'T':
    drawLine(x+3,y,x+8,y);
    drawLine(x+5,y,x+5,y+10);
   break;
   case 'U':
    drawLine(x+2,y,x+2,y+11);
    drawLineTo(x+8,y+10);
    drawLineTo(x+8,y);
   break;
   case 'V':
    drawLine(x+2,y,x+5,y+11);
    drawLineTo(x+8,y);
   break;
   case 'W':
    drawLine(x+1,y,x+3,y+11);
    drawLineTo(x+5,y+7);
    drawLineTo(x+7,y+10);
    drawLineTo(x+9,y);
   break;
   case 'X':
    drawLine(x+2,y,x+10,y+10);
    drawLine(x+9,y,x,y+10);
   break;
   case 'Y':
    drawLine(x+2,y,x+5,y+6);
    drawLine(x+8,y,x+2,y+10);
   break;
   case 'Z':
    drawLine(x+2,y,x+9,y);
    drawLineTo(x,y+10);
    drawLineTo(x+8,y+9);
   break;
 }
}

void drawLine(byte x0, byte y0, byte x, byte y)
{
 blanking(x0,y0);
 DrawLine(x,y,_color);
}

void drawLineTo(byte x, byte y)
{
  DrawLine(x,y,_color); 
}

void draw_string_time(String text, byte x, byte y, byte color, int dauer)
{
  int d = dauer* 25;
 for ( int i=0; i<d ; i++)
  {
    beginFrame();
    draw_string(text ,1,1,1);
    endFrame();
  }
}
