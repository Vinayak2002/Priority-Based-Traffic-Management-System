#include <NewPing.h>
#include <Wire.h>
 
#define MAX_DISTANCE 2000

struct intensity
{
  int lane_1_intensity;
  int lane_2_intensity;
};

int trig[] = {8, 9, 10, 11, 12, 13};
int echo[] = {8, 9, 10, 11, 12, 13};

int distance[6];
const int idle_distance = 10;
 
NewPing sonar1(trig[0], echo[0], MAX_DISTANCE);
NewPing sonar2(trig[1], echo[1], MAX_DISTANCE);
NewPing sonar3(trig[2], echo[2], MAX_DISTANCE);
NewPing sonar4(trig[3], echo[3], MAX_DISTANCE);
NewPing sonar5(trig[4], echo[4], MAX_DISTANCE);
NewPing sonar6(trig[5], echo[5], MAX_DISTANCE);


struct intensity light();
void transmit(struct intensity input);
void delay_time(int p, int q);
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
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
  Wire.beginTransmission(4);
  Wire.write(input.lane_1_intensity);
  Wire.write(input.lane_2_intensity);
  Wire.endTransmission();

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

  delay(delay_ * 1000);
  Serial.print("Waiting for ");
  Serial.print(delay_);
  Serial.println(" seconds");
  
}

struct intensity light()
{
  int lane1, lane2;
  struct intensity out;
  if (distance[0] < idle_distance && distance[1] < idle_distance && distance[2] < idle_distance)
  lane1 = 3;
  else if (distance[0] < idle_distance && distance[1] < idle_distance) 
  lane1 = 2;
  else if (distance[0] < idle_distance) 
  lane1 = 1;
  else 
  lane1 = 0;

  if (distance[3] < idle_distance && distance[4] < idle_distance && distance[5] < idle_distance)
  lane2 = 3;
  else if (distance[3] < idle_distance && distance[4] < idle_distance) 
  lane2 = 2;
  else if (distance[3] < idle_distance) 
  lane2 = 1;
  else 
  lane2 = 0;

  out.lane_1_intensity = lane1;
  out.lane_2_intensity = lane2;

  Serial.print("LANE 1 --> ");
  Serial.println(lane1);
  Serial.print("LANE 2 --> ");
  Serial.println(lane2);  
  
  return out;
 
}
