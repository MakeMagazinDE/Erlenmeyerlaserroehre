//////////////////////////////////////////////////////////////////////////////
// Verschiedene Routinen zum Debuggen und
// Testbilder zum einstellen von Laser und Galvo-Scanner
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

void Ausgabe1(int a)
{
   Serial.println (a);
}

void Ausgabe2(int a, int b)
{
   Serial.print (a);
   Serial.print(" - ");
   Serial.println (b);
}

void Ausgabe3(int a, int b, int c)
{
   Serial.print (a);
   Serial.print(" - ");
   Serial.print (b);
   Serial.print(" - ");
   Serial.println (c);
}

void Ausgabe4(int a, int b, int c,int d)
{
   Serial.print (a);
   Serial.print(" - ");
   Serial.print (b);
   Serial.print(" - ");
   Serial.print (c);
   Serial.print(" - ");
   Serial.println (d);
}

void showBool(boolean b)
{
  if (b == true) Serial.println("true");
    else Serial.println("false");
}

void Ausgabe0(int a)
{
  drawInt(a,120,120,1);
}

void fehlerMaxpos(int a)
{
 int z;
 while(1)
 {
  z++;
  if (z < 100)  {
       beginFrame();
      draw_string("SETPOS", 0,  0,  1);
      endFrame();
    } else if (z < 200)  {
      beginFrame();
      draw_string("to", 0 ,0, 1);
      endFrame();   
    } else if (z < 300)  {
      beginFrame();
      draw_string("HIGH"  , 0, 0, 1);
      endFrame();
    } else if (z  < 400)  {
      beginFrame();
      drawInt(a,  0,  0,  1);
      endFrame();
    }else z = 0;
  }
}


void Testbild_1()
{
  byte color = 7;
  beginFrame();
    blanking(127, 0);
    DrawFastLine(254, 127,  color);
    DrawFastLine(127, 254,  color);
    DrawFastLine(0, 127,  color);
    DrawFastLine(127, 0,  color);

    DrawFastLine(127,  254,  color);
    DrawFastLine(254, 127,  color);
    DrawFastLine(0, 127,  color);

    DrawFastLine(0, 0,  color);
    DrawFastLine(254, 0,  color);
    DrawFastLine(254, 254,  color);
    DrawFastLine(0, 254,  color);
    DrawFastLine(0, 127,  color);
    DrawSquare(70,  70, 184 ,184, color);

  endFrame(); 
  lastPoints = PointerSet;
}
 
 void Testbild_2()
{
  beginFrame();
  byte color = 1; 

 //Waagrecht
  blanking(10, 10); 
  for (int i = 10; i <= 130; i = i+40)
  {
    DrawFastLine(i,   10, color);
    DrawFastLine(i, 170, color);
    DrawFastLine(i+20, 170, color);
    DrawFastLine(i+20, 10, color);
  }
    DrawFastLine(170, 10, color);
    DrawFastLine(170, 170, color);
  
  // Senkrecht
  blanking(10, 10);
  for (int  i = 10 ; i <= 130 ; i = i+40)
  {
    DrawFastLine(10, i, color);
    DrawFastLine(170, i, color);
    DrawFastLine(170, i+20, color);
    DrawFastLine(10, i+20, color);
  }
  DrawFastLine(10, 170, color);
  DrawFastLine(170, 170, color);
  
    draw_letter ('R', 75, 75, 1);
    draw_letter ('G', 95, 75, 2);
    draw_letter ('B', 75, 95, 4);
    draw_letter ('W', 95, 95, 7);
    endFrame(); 
    lastPoints = PointerSet;
}


 void Testbild_3()
 {
  beginFrame();
    blanking(100, 0);
    DrawLine(100, 200,  7);
    blanking(0,   100);
    DrawLine(200, 100,  7);

    blanking(0,   0);
    DrawLine(200, 200,  7);
    blanking(200, 0);
    DrawLine(0,   200,  7);    
  endFrame();
  lastPoints = PointerSet;
 }


void print_Reset_reason()  // warum ist der Prozessor neu gestartet?
{
     esp_reset_reason_t reason = esp_reset_reason();

    switch (reason) {
        case ESP_RST_UNKNOWN:
          Serial.println("Reset reason can not be determined");
        break;

        case ESP_RST_POWERON:
          Serial.println("Reset due to power-on event");
        break;

        case ESP_RST_EXT:
          Serial.println("Reset by external pin (not applicable for ESP32)");
        break;

        case ESP_RST_SW:
          Serial.println("Software reset via esp_restart");
        break;

        case ESP_RST_PANIC:
          Serial.println("Software reset due to exception/panic");
        break;

        case ESP_RST_INT_WDT:
          Serial.println("Reset (software or hardware) due to interrupt watchdog");
        break;

        case ESP_RST_TASK_WDT:
          Serial.println("Reset due to task watchdog");
        break;

        case ESP_RST_WDT:
          Serial.println("Reset due to other watchdogs");
        break;                                

        case ESP_RST_DEEPSLEEP:
          Serial.println("Reset after exiting deep sleep mode");
        break;

        case ESP_RST_BROWNOUT:
          Serial.println("Brownout reset (software or hardware)");
        break;
        
        case ESP_RST_SDIO:
          Serial.println("Reset over SDIO");
        break;
        
        default:
        break;
    }
}
