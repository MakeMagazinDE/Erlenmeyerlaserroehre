//////////////////////////////////////////////////////////////////////////////
// Rotinen zur Erzeugung von Tönen und Geräuschen
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

int sound = 0;
int SoundPhase= - 1;

void Sound_ESP_Start()
{
  for (byte i = 1 ; i < 5 ; i++) 
  { 
    tone(tonePin, i*500, 50); 
    delay(100);
  }
}

void Sound_explosion()
{
  if ( SoundPhase > 0)
  {
   SoundPhase++;
   tone(tonePin, explosionFreq[SoundPhase]); //der Ton wird aus dem Programmspeicher geladen ==> definiert wird er in Asteorieds.h
   if (SoundPhase >= 200) 
   {
    tone(tonePin, explosionFreq[SoundPhase],10); //der Ton wird aus dem Programmspeicher geladen ==> definiert wird er in Asteorieds.h
    SoundPhase = -1;
   }
  }
}


void Sound_Die()
{
    if ( SoundPhase > 0)
    {
     SoundPhase++;
      tone(tonePin, 2060-10*SoundPhase); 
    }
    if ( SoundPhase > 200)
    {
     tone(tonePin, 60, 10);
     SoundPhase = -1;
   }
}

void Sound_NewGame()
{
  static int b = 0;
  static int r = 1;
    if ( SoundPhase > 0)
    {
     SoundPhase++;
     if (SoundPhase ==250) r = -1;
     b += r;
     if  (SoundPhase < 500)
     {
       tone(tonePin, 50+b, 10); 
     } else {
      r = 1;
      b = 0;
      SoundPhase= - 1;
     }
   }
}

void Sound_NewGame2()
{
    if ( SoundPhase > 0)
    {
     SoundPhase++;
     switch (SoundPhase)
     {
      case 2:   tone(tonePin, 600, 600); 
                SoundStop = true; 
       break;
      case 200: tone(tonePin, 800, 600); 
       break;
      case 400: tone(tonePin, 1000, 600);
                SoundPhase = -1;
                SoundStop = false; 
       break;
     }
   }
}


void sound_Fire()
{
  tone(tonePin, 370, 40);
}


void setSound(int s)
{
  if (SoundStop != true)
  { 
   sound = s;
   SoundPhase = 1;
  }
}

void doSound()
{
  static unsigned int t;
  if (sound != 0)
  {
 
    if (t++ > 70)
    {
       switch (sound)
       {
         case 1: Sound_explosion();  
         break;
         case 2: Sound_Die();   
         break;
         case 3: Sound_Die();  
         break;
         case 4: Sound_NewGame();  
         break;
       }
      t=0;
    }
  }  
}
