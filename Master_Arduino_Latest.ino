#include <NewPing.h>  // Libraries for Ultrasonic Sensors
#include <SPI.h>  // Communication Library
#include <nRF24L01.h> // NRF module Library
#include <RF24.h> // NRF module Library

#define MAX_DISTANCE 2000 // Maximum distance for ultrasonic sensor to detect

struct intensity  // Sturct type to send the information from and to various functions
{
  char lane_1_intensity;
  char lane_2_intensity;
};

int trig[] = {2, 3, 4, 5, 6, 7};  // 2, 3, 4 pins for lane 1
int echo[] = {2, 3, 4, 5, 6, 7};  // 5, 6, 7 pins for lane 2

int distance[6];  // integer array for distance detected by ultrasonic sensors
const int idle_distance = 10; // The distance below which ultrasonic sensors return active value

RF24 radio(9, 8); 
NewPing sonar1(trig[0], echo[0], MAX_DISTANCE);
NewPing sonar2(trig[1], echo[1], MAX_DISTANCE);
NewPing sonar3(trig[2], echo[2], MAX_DISTANCE);
NewPing sonar4(trig[3], echo[3], MAX_DISTANCE);
NewPing sonar5(trig[4], echo[4], MAX_DISTANCE);
NewPing sonar6(trig[5], echo[5], MAX_DISTANCE);
const byte address[6] = "00001";


struct intensity light();
void transmit(struct intensity input);
void delay_time(int p, int q);
 
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
}
 
void loop() {
  delay(1000);
  struct intensity lanes;

  Serial.println("******Loop Begin******");
  
  Serial.println("Ping1: ");
  Serial.print(sonar1.ping_cm());
  Serial.println("cm");
  distance[0] = sonar1.ping_cm();
  
  Serial.println("Ping2: ");
  Serial.print(sonar2.ping_cm());
  Serial.println("cm");
  distance[1] = sonar2.ping_cm();
  
  Serial.println("Ping3: ");
  Serial.print(sonar3.ping_cm());
  Serial.println("cm");
  distance[2] = sonar3.ping_cm();
  
  Serial.println("Ping4: ");
  Serial.print(sonar4.ping_cm());
  Serial.println("cm");
  distance[3] = sonar4.ping_cm();
  
  Serial.println("Ping5: ");
  Serial.print(sonar5.ping_cm());
  Serial.println("cm");
  distance[4] = sonar5.ping_cm();
  
  Serial.println("Ping6: ");
  Serial.print(sonar6.ping_cm());
  Serial.println("cm");
  distance[5] = sonar6.ping_cm();

  lanes = light();
  transmit(lanes);

  
  Serial.println("******Loop End******");
}

void transmit(struct intensity input)
{
  char sendvalue1,sendvalue2;
  sendvalue1 = input.lane_1_intensity;
  sendvalue2 = input.lane_2_intensity;

  const char text[] = {input.lane_1_intensity, input.lane_2_intensity};
  
  Serial.println(text);
  radio.write(&text, sizeof(text));
  delay(5000);

  delay_time(input.lane_1_intensity, input.lane_2_intensity);
  
}

void delay_time(int p, int q)
{
  int delay_ = 0;
  if (p == 0)
  delay_ += 1;
  else if (p == 1)
  delay_ += 5;
  else if (p == 2)
  delay_ += 10;
  else
  delay_ += 15;

  if (q == 0)
  delay_ += 1;
  else if (q == 1)
  delay_ += 5;
  else if (q == 2)
  delay_ += 10;
  else
  delay_ += 15;

  Serial.print("Waiting for ");
  Serial.print(delay_);
  Serial.println(" seconds");
  
//  delay(delay_ * 1000);
}

struct intensity light()
{
  char lane1, lane2;
  struct intensity out;
  if (distance[0] < idle_distance && distance[1] < idle_distance && distance[2] < idle_distance)
  lane1 = '3';
  else if (distance[0] < idle_distance && distance[1] < idle_distance) 
  lane1 = '2';
  else if (distance[0] < idle_distance) 
  lane1 = '1';
  else 
  lane1 = '0';

  if (distance[3] < idle_distance && distance[4] < idle_distance && distance[5] < idle_distance)
  lane2 = '3';
  else if (distance[3] < idle_distance && distance[4] < idle_distance) 
  lane2 = '2';
  else if (distance[3] < idle_distance) 
  lane2 = '1';
  else 
  lane2 = '0';

  out.lane_1_intensity = lane1;
  out.lane_2_intensity = lane2;

  Serial.print("LANE 1 --> ");
  Serial.println(lane1);
  Serial.print("LANE 2 --> ");
  Serial.println(lane2);  
  
  return out;
 
}
