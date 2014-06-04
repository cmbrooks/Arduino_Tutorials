const int sensorPin = A0;
float baselineTemp;

void setup(){
  Serial.begin(9600);
  int sensorVal = analogRead(sensorPin);
  float runningSum = 0;
  int x;
  
  //Initializes pins used
  for(int pinNumber = 2; pinNumber < 5; pinNumber++){   
    pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber,LOW);
  }
  
  //Takes an addative sample of temperatures for 5 seconds
  for(x=0; x < 19; x++){
    runningSum = runningSum + (((sensorVal / 1024.0) * 5.0) - .5) * 100.0;
    delay(250);
  }
  
  baselineTemp = runningSum/x; //Averages the sum of temperatures collected
  Serial.print("Baseline Temperature is: ");
  Serial.println(baselineTemp);
}
void loop(){
  
  //Reads raw data off of pin
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  //Converts the raw data into a recognizable volage
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(" , Volts: ");
  Serial.print(voltage);
  
  //Converts voltage into its corrispoding temperature
  float temperature = (voltage - .5) * 100;
  Serial.print(" , Degrees (Celcius): ");
  Serial.println(temperature);
  
  if(temperature < baselineTemp){
  	digitalWrite(2,LOW);
  	digitalWrite(3,LOW);
	digitalWrite(4,LOW);
  }
  
  else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4){
  	digitalWrite(2,HIGH);
  	digitalWrite(3,LOW);
  	digitalWrite(4,LOW);
  }
  
  else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6){
    digitalWrite(2,HIGH);
  	digitalWrite(3,HIGH);
  	digitalWrite(4,LOW);
  }
  
  else if (temperature >= baselineTemp + 6){
    digitalWrite(2,HIGH);
	digitalWrite(3,HIGH);
	digitalWrite(4,HIGH);
  }
  
  delay(1);
  
}
