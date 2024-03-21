int encoderPin1 = 27;
int encoderPin2 = 26;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  pinMode(4, INPUT);
  Serial.begin(9600);

  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  attachInterrupt(27, updateEncoder, CHANGE);
  attachInterrupt(26, updateEncoder, CHANGE);
}

void loop() {
  Serial.print("Angle =");
  Serial.println(encoderValue);
}


void updateEncoder() {
  int MSB = digitalRead(encoderPin1);  //MSB = most significant bit
  int LSB = digitalRead(encoderPin2);  //LSB = least significant bit

  int encoded = (MSB << 1) | LSB;          //converting the 2 pin value to single number
  int sum = (lastEncoded << 2) | encoded;  //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++; //13, 4, 2, 11
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--; //14, 7, 1, 8

  lastEncoded = encoded;  //store this value for next time
}
