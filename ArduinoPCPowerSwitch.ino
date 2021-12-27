/*
  PC Toggle Switch

  The circuit:
  - Toggle switch connected to pin 2 and GND
  - 5V relay 
    - Connect (+) to 5V
    - Connect (-) to ground
    - Connect signal to pin 13
  - PC board connection
    - ATX power pin 4 connected to Vin
    - ATX power pin 24 connected to GND
    - USB 5V to pin 12 of Arduino
    - Power switch header to relay NO connection
*/

const int buttonPin = 2; // Connect to a SPST toggle-switch
const int signalPin = 13; // Connect to relay signal input pin
const int pcstatePin = 12; // Connect to USB 5V output

void setup() {
  //start serial connection
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP);   //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(signalPin, OUTPUT);
  pinMode(pcstatePin, INPUT);
}

void loop() {
  //read the pushbutton value into a variable
  int buttonPinState = digitalRead(buttonPin);
  int signalPinState = digitalRead(signalPin);
  int pcState = digitalRead(pcstatePin);

  if (buttonPinState == LOW)
  {
    Serial.println("Switch is on");
  }
  else
  {
    Serial.println("Switch is off");
  }

  if (pcState == LOW)
  {
    Serial.println("PC is off");
  }
  else
  {
    Serial.println("PC is on");
  }

  Serial.println("********************");

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when toggle switch is open, and LOW when switch is close. 
  
  if (buttonPinState  == LOW && pcState == LOW) { // Switch is in on position and PC is off
      toggleSignalPin();  // Turn on PC
      //digitalWrite(pcstatePin, HIGH);
  }

  if (buttonPinState == HIGH && pcState == HIGH) { // Switch is in off position and PC is on
      toggleSignalPin();  // Turn off PC
      Serial.println("Wait for PC to shutoff");
      delay(5000); // Need to wait a bit for PC to shut off
  }
    
}

void toggleSignalPin()
{
      Serial.println("Toggle signal pin");
      digitalWrite(signalPin, HIGH);
      delay(20);
      digitalWrite(signalPin, LOW);
}
