#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define BUFFER_LENGTH 512

const int analogOutPin = 6;

int signal = 0; 
int delayBuffer[BUFFER_LENGTH];
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
  
  memset(delayBuffer, 0, sizeof(delayBuffer));
}

void loop() {
  //ADCH reads from A0
  signal = ADCH;
  analogWrite(analogOutPin, delaySignal(signal));
}

int delaySignal(int input) {
  int output = 0;
  
  delayBuffer[index] = input;
  
  int delayIndex = index - 510;
  if (delayIndex < 0) {
    delayIndex += BUFFER_LENGTH;
  }
  
  output = (2 * delayBuffer[delayIndex] + 3 * signal) / 5;
  index = (index + 1) % BUFFER_LENGTH;
  return output;
}
