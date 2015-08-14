#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

const int analogOutPin = 6;

int signal = 0; 
int buffer[512];
int index = 0;

void setup() {  
  //Set ADC parameters
  ADCSRA = 0;
  cbi(ADCSRA, ADPS2);
  sbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
  
  sbi(ADCSRA, ADATE);
  sbi(ADCSRA, ADEN);
  sbi(ADCSRA, ADSC);
  
  sbi(ADMUX, REFS0);
  sbi(ADMUX, ADLAR);

  //Set pins 5 and 6 to Fast PWM at 62.5 kHz
  TCCR0B = 0;
  sbi(TCCR0B, CS00);
  sbi(TCCR0A, COM0A1);
  sbi(TCCR0A, COM0B1); 
  sbi(TCCR0A, WGM01); 
  sbi(TCCR0A, WGM00); 
  
  int i;
  for (i = 0; i < 512; i +=1)
  {
    buffer[i] = 0;
  }
}

void loop() {
  //ADCH reads from A0
  signal = ADCH;
  buffer[index] = signal;
  
  int delayIndex = index - 510;
  if (delayIndex < 0) {
    delayIndex += 512;
  }
  
  //Output
  signal = (4 * buffer[delayIndex] + 6 * signal) / 10;
  analogWrite(analogOutPin, signal);
  
  index = (index + 1) % 512;
}
