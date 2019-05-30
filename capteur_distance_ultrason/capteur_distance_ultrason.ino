#include <tm1637.h>

//#include <TinyNewPing.h>

#define TRIGGER_PIN       3
#define ECHO_PIN          4
#define OUTPUT_PIN        1
 
/* Constantes pour le timeout */
//const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, 300);


void setup()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  
  
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  delay(500);
  digitalWrite(OUTPUT_PIN, LOW);


  TM1637_init();
  TM1637_set_brightness(7);
}
 


void loop()
{
  
  // 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe)
  pinMode(ECHO_PIN, INPUT);
  long mesure = pulseIn(ECHO_PIN, HIGH, 50000UL);
   
  // 3. Calcul la distance à partir du temps mesuré
  mesure = (mesure * 17) / 2000;


  //unsigned int mesure = sonar.ping() / US_ROUNDTRIP_CM;

  digitalWrite(OUTPUT_PIN, mesure == 0);

  if(mesure != 0)
  {

    for(char i = 3; i >= 0; i--)
    {
      TM1637_display_digit(i, mesure % 10);
      mesure /= 10;
    }

  }

  delay(100);
}
