#define FASTADC 1
#define wave 3

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
int value = 0;
long duration = 0;
boolean exec = true;

void setup() {
  Serial.begin(9600);
  pinMode(wave, OUTPUT);
  #if FASTADC
  // set clock prescale to 16
    sbi(ADCSRA,ADPS2) ;
    cbi(ADCSRA,ADPS1) ;
    cbi(ADCSRA,ADPS0) ;
  #endif
}

void loop() {
  if(exec==true)
  {
	  // wave generation loop, duration is almost 10 secs
	  for(duration=0; duration<200000; duration++) {
		digitalWrite(wave, LOW);
		delayMicroseconds(20);
		value = analogRead(0);
		delayMicroseconds(15);
		digitalWrite(wave, HIGH);
		delayMicroseconds(50);
	  }
	  Serial.println(value);
	  exec=false;
  }
}
