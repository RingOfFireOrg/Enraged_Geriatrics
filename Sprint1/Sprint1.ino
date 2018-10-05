#include <Servo.h>
#include <NewPing.h>
#include <LiquidCrystal.h>

int reedPin = A0;                                   // select the input  pin for  the reed
int TRIGGER_PIN = 4;                                // Arduino pin tied to trigger pin on the ultrasonic sensor.
int ECHO_PIN = 6;                                   // Arduino pin tied to echo pin on the ultrasonic sensor.
int MAX_DISTANCE = 400;                             // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int sensorPin = A1;                                 // select the input  pin for  the potentiometer
int sensorValue = 0;                                // variable to  store  the value  coming  from  the sensor
int reedValue = 0;                                  // variable to  store  the value  coming  from  the sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo LeftServo;                                    // create new servo object for the left servo
Servo RightServo;                                   // create new servo object for the right servo
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);             // initialize the library with the numbers of the interface pins

// make a custom walker characters:

byte walker[8] = {
    0b00000,
    0b11100,
    0b10010,
    0b10010,
    0b10010,
    0b10010,
    0b11011,
    0b11011};

void setup()
{

  //Left Servo recieves signal from pin 3
  LeftServo.attach(3);
  //Right Servo recieves signal from pin 5
  RightServo.attach(5);
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  // create a new character
  lcd.createChar(5, walker);
  // Print a message to the lcd.
  // Start at Upper left corner
  lcd.setCursor(byte(0), byte(0));
  // Print walker symbol
  lcd.write((byte)5); // when calling lcd.write() '0' must be cast as a byte
  // Print team name
  lcd.print(" Enraged  G's ");
  // Print walker symbol
  lcd.write((byte)5); // when calling lcd.write() '0' must be cast as a byte
  // Initialize the Serial monitor for readings from the robot
  Serial.begin(9600);

  LeftServo.write(90);
  RightServo.write(90);
}

void loop()
{

  // read the potentiometer on A1:
  //int sensorReading = analogRead(A1);
  // set cursor at the start of line 2
  lcd.setCursor(byte(0), 1);

  /*
  LeftServo.write(180); // Run Left servo full reverse
  RightServo.write(0);  //Run Right servo full forward
  delay(2000);
*/

  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  sensorValue = analogRead(sensorPin);
  reedValue = analogRead(reedPin);

  // send the reading to the serial monitor
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.println(sensorValue); // shows reading off of photoresistor
  Serial.print("Reed: ");
  Serial.println(reedValue); // show reed value

  //send the readings to the LCD screen
  lcd.print(uS / US_ROUNDTRIP_CM);
  lcd.print("cm");
  lcd.print("/");
  lcd.print(sensorValue); // shows reading off of photoresistor
  lcd.print("/");
  lcd.print(reedValue);

  /*
  //Stop the servo for 2000 milliseconds
  LeftServo.write(90);
  RightServo.write(90);
  delay(2000);
*/
}
