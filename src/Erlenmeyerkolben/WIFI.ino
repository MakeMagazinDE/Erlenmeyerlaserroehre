//////////////////////////////////////////////////////////////////////////////
// WLAN verbinden und Internetzeit abrufen (Verwendung für die Uhren)
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////

#include <WiFi.h>

const char* ssid      = "FritzUS";              // Hier die eigene SSID eintragen (RouterName)
const char* password  = "48094564919405773644"; // Hier das eigene WLan-Passwort einfügen

const char* ntpServer1 = "pool.ntp.org";                // 1. Zeitserver
const char* ntpServer2 = "time.nist.gov";               // 2. Zeitserver
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";   // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

String stamp;  // Variable für den Zeitstempel.
String f;      // Variable um Strings zusammenzusetzen und Anzuzeigen

void SerialprintWifiStatus()
{
  Serial.print("* SSID: ");
  Serial.println(WiFi.SSID());
  Serial.println("* IP Addresse: " + WiFi.localIP().toString());
  Serial.println("* Signalstärke (RSSI):" + String(WiFi.RSSI()) + " dBm");
}

unsigned long get_Local_Time()
{
  struct tm timeinfo;
  int n = 0;
  bool erfolg = true;

 
  configTzTime(time_zone, ntpServer1, ntpServer2);
  Serial.println("Suche Internetzeit");
  drawMeldung("SUCHE INTERNETZEIT", 5,100,3000);

  while ( (n < 10) and (!getLocalTime(&timeinfo)))
  {   
    n++;
    Serial.print("█");
    f="Versuch: " + String(n);
    drawMeldung(f,30,100,1000);
   }
  if (n > 9) {
    Serial.println("Keine Zeit ermittelt");
    drawMeldung("keine Zeit gefunden", 5,100,3000);
    erfolg = false;
  } else {
    drawMeldung("ERFOLG Zeit", 30,100,3000);
    rtc.setTimeStruct(timeinfo);
    for (n=1 ; n<6; n++)
    {
      make_time_stamp ();
      Serial.println(stamp);
      drawMeldung(stamp, 5,100,1000);
    }
  }
  delay(500);
  if (erfolg) return rtc.getEpoch(); else return 0;
}

String make_time_stamp ()
{
 stamp = rtc.getTime("%d.%m.%Y %H:%M:%S");
 return stamp;
}


void WIFI_Connect()
{ 
  Serial.println("Verbinde zu: " + String(ssid));
  f = "Verbinde zu: " + String(ssid);
  
   drawMeldung(f, 5,100,3000);
   drawMeldung("Bitte Warten", 30,100,3000);
  //--------------------------------------------------   Verbindungsversuche ins Netz-----------------------------------------------
  byte n = 0;
  
  WiFi.begin(ssid, password);
  while ((WiFi.status() != WL_CONNECTED) and (n < 20))
  {    
    n++;
    Serial.print("█");
    f="Versuch: " + String(n);
    drawMeldung(f,30,100,1000);
  } Serial.println("");

  if (WiFi.status() == WL_CONNECTED) //--------------------- WIFI wurde verbunden --------------------------------------------------
  {
    Serial.println("WIFI ist verbunden");
    drawMeldung("ERFOLG WIFI", 30,100,3000);

    // -------------------------------------------------  Zeit aus dem Internet holen und RTC damit einstellen----------------------
    get_Local_Time();
  } else {
    Serial.println("WIFI ist nicht verbunden :-(");
    drawMeldung("keine Verbindung", 15,100,3000);
  } 
  WiFi.mode(WIFI_OFF);
  delay(500);
}
