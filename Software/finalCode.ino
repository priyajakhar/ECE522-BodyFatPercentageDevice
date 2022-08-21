//A4 (SDA) and A5 (SCL)

#define FASTADC 1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define wave 3
LiquidCrystal_I2C lcd(0x27,20,4);

// define variables for setting the pre-division factor of system clock for ADC conversion
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// declare the global variables
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char gender[numChars] = {0};
int age = 0;
float weight = 0.0;
boolean newData = false;

// initialize the serial monitor, the LCD and the ADC clock speed
void setup() {
    Serial.begin(9600);
    pinMode(wave, OUTPUT);
    #if FASTADC
      sbi(ADCSRA,ADPS2) ;
      cbi(ADCSRA,ADPS1) ;
      cbi(ADCSRA,ADPS0) ;
    #endif
    lcd.init();
    lcd.backlight();
    lcd.setCursor(8,1);
    lcd.print("Hello!");
    Serial.println("Enter data <Gender (M/F), Age, Weight in lbs>"); // prompt user for input on serial monitor
}

// main function which runs only once
void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
        parseData();
        int volt = generateWave();
        lcdupdate(volt);
        newData = false;
    }
}

// function for getting the input from user, bound by angular brackets
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0';
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

// function for parsing the user input and assigning parts to gender, age and weight variables
void parseData() {
    char * strtokIndx;
    
    strtokIndx = strtok(tempChars,","); // get the first part
    strcpy(gender, strtokIndx); // copy it to gender
 
    strtokIndx = strtok(NULL, ","); // get the second part
    age = atoi(strtokIndx); // copy it to age
    
    strtokIndx = strtok(NULL, ","); //get the third part
    weight = atof(strtokIndx); // copy it to weight

}

// function for generating the signal to pass to the circuit which then interfaces to the user through the electrodes
// also reading and returning the analog voltage value
int generateWave() {
  long duration;
  int reading = 0.0;
  for(duration=0; duration<20000; duration++) {
    digitalWrite(wave, LOW);
    delayMicroseconds(20);
    reading = analogRead(0);
    delayMicroseconds(15);
    digitalWrite(wave, HIGH);
    delayMicroseconds(50);
  }
  return reading;
}

// function for calculating the fat percent and displaying it on the LCD
void lcdupdate(int reading){
  long body_fat = 0;
  
  if(gender[0]=='M' or gender[0]=='m')
    //body_fat = -2.2335*age+0.3624*weight-0.0078*reading; //earlier equation
	body_fat = -0.29669*age+0.3624*weight-0.0078*reading; //later equation

  else
    body_fat = -0.0698*age+0.1415*weight-0.002*reading;

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Age:");
  lcd.setCursor(9,0); lcd.print(age);
  lcd.setCursor(0,1); lcd.print("Weight:");
  lcd.setCursor(9,1); lcd.print(weight);
  lcd.setCursor(13,1); lcd.print("lbs");
  lcd.setCursor(0,3); lcd.print("Body Fat:");
  lcd.setCursor(9,3); lcd.print(body_fat);
  lcd.setCursor(11,3); lcd.print("%");
}