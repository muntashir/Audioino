#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

const int analogInRight = A0;
const int analogInLeft = A1;  
const int analogOutRight = 6;
const int analogOutLeft = 5;

int audioIn = 0;     
int audioOut = 0;    

void setup() {  
  //Set ADC prescale to 16 (77 kHz sampling)
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);

  //Set pins 5 and 6 to Fast PWM at 62.5 kHz
  TCCR0B = 0;
  sbi(TCCR0B, CS00);
  sbi(TCCR0A, COM0A1);
  sbi(TCCR0A, COM0B1); 
  sbi(TCCR0A, WGM01); 
  sbi(TCCR0A, WGM00); 
}

void loop() {
  audioIn = (analogRead(analogInRight));
  audioOut = map(audioIn, 300, 800, 0, 255);
  analogWrite(analogOutRight, audioOut);
}
