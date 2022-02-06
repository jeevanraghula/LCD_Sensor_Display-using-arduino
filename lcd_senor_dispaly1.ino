#include <LiquidCrystal.h> //Import the LCD library
#include <Servo.h>

Servo myservo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
#define contrast 9 //Define the pin that controls the contrast of the screen

const int trigPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int pos = 0;    // variable to store the servo position
int threshold_distance=50 ;

void setup() 
{
  lcd.begin(16, 2);          //Tell the LCD that it is a 16x2 LCD
  Serial.begin(9600);
  pinMode(contrast, OUTPUT);  //set pin 9 to OUTPUT
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  digitalWrite(contrast,LOW); 
 
}
void loop()
{ lcd.print("Thrshld_dis:");
  lcd.print(threshold_distance);
  lcd.print("cm");
  
 //reading distance from ultrasonic sensor
  distance =Ultrasonic_read();
  
 // Displays the distance on the Serial Monitor
  serial_display();
 
 //*****Also Displaying on LCD******
  lcd_display();
 
 //setting up servo motor
 pos=0;
 while(distance<=threshold_distance)
 {
  myservo.attach(10);
  if(pos<180)
  {
  myservo.write(pos);
  delay(20);
  
  Serial.print("angle of servo :");
  Serial.print(pos);
  Serial.println();
  pos += 1 ;
  distance =Ultrasonic_read(); 
   serial_display(); // displaying new input data on Serial
   lcd_display();    // and LCD display
  } 
 }
     
  lcd.setCursor(0, 0);
  delay(200);
}

int Ultrasonic_read()
{
  digitalWrite(trigPin, LOW); // Clears the trigPin condition
  delayMicroseconds(2);  
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);       // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration*0.034)/2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

void serial_display()
{
  Serial.print("Distnce: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();
  delay(10);
}

void lcd_display()
{
  lcd.setCursor(0, 1);
  lcd.print("Distance : ");
  lcd.print(distance);
  lcd.print(" cm");
  delay(10);
}

            