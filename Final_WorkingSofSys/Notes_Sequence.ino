int t = 0;

byte sine[] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119,};
int notes [15] = {50, 75, 44};    

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  for (int i=0;i<8;i++){
    pinMode(i,OUTPUT);
  }
  
  cli();//disable interrupts
  //set timer0 interrupt at 40kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 40khz increments
  //OCR2A = 40;// = (16*10^6) / (40000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS11 bit for 8 prescaler
  TCCR2B |= (1 << CS21); 
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei();//enable interrupts
}
//A3 = 91
//G3 = 50

ISR(TIMER2_COMPA_vect){
  //OCR2A = notes[i];
  if (t < 120) {
    PORTD = sine[t];
    t++;
  } else t = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < 15; i++) {
    OCR2A = notes[i];  
    Serial.println(i);
    delay(100);
  }
}
