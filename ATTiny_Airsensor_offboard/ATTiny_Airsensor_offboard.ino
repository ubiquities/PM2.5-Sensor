/* 
 *  Code for off loaded led, buzzer and timer functions.
 */

//Global Variable
#define every(interval) \
    static uint32_t __every__##interval = millis(); \
    if (millis() - __every__##interval >= interval && (__every__##interval = millis()))

#define Millis 
#define Second  *150
j #define Seconds *150
int interval = 1 Second;
byte LED = 2;
byte buzzer = 1;
byte warning = 3;
const int Tone = 239;


void setup(){
pinMode(LED, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(warning, INPUT_PULLUP);
digitalWrite(LED, LOW);
digitalWrite(buzzer, LOW);
}

void loop() {

if (digitalRead(warning)==LOW) {

  every(200 Millis){
   digitalWrite(LED, HIGH);
   delay(5);
   digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, LOW);
  }

  every(4000 Millis) {
  TinyTone(Tone, 4, 3);
  }
} //Close if statement
} //Close loop

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  //TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}
