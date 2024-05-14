//////////////////////////////////////////////////////////////////////////////
// Steuerung der Laser
// Wird nur ein Laser verwendet, so muss die Zeile   "#define Farblaser true"
// nach "#define Farblaser false" geändert werden.
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

bool Farblaser = false;

void init_Laser()               // alle Laserpins als Output definieren
{
  pinMode(laser_pin_r, OUTPUT); 
  pinMode(laser_pin_g, OUTPUT);
  pinMode(laser_pin_b, OUTPUT);
}


void rgb_laser(boolean r, boolean g, boolean b) // Laser schalten
{                                               // Farben werden als Einzelwerte angegeben
  digitalWrite(laser_pin_r, r);
  digitalWrite(laser_pin_g, g);
  digitalWrite(laser_pin_b, b);

}


void RGBLaser(byte Color)                 // Laser schalten    
{                                         // Farbe als Binaerwert angeben
  if (Farblaser == true)                  // Unterscheidung ob Farblaser oder monochromer Laser
  {
    digitalWrite(laser_pin_r, Color & 1);    // 0 = Laser aus
    digitalWrite(laser_pin_g, Color & 2);    // 1 = Rot,  2 = Gruen, 4 = Blau, 7 = Weiss
    digitalWrite(laser_pin_b, Color & 4);    // 3 = Mischfarbe aus Rot und  Grün ...usw.
  } else if ((Color == 0) or (Color == 128)) // 0 = Laser aus, 128 = Ende Stream
      digitalWrite(laser_pin_r,0);           // ==> kein Farblaser ==> roten Laser ausschalten
      else digitalWrite(laser_pin_r,1);      // ==> kein Farblaser ==> roten Laser einschalten
}

void laser_on() // alle Laser einschalten
{
  RGBLaser(7);
}


void laser_off() // alle Laser ausschalten
{
  RGBLaser(0);
}
