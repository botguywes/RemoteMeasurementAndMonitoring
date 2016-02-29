

void setup()
{
  Serial.begin(9600);
  Serial3.begin(19200);
}

void loop()
{
  
  Serial3.flush();
  Serial3.println("d");
  while (!Serial3.available()) { Serial.println("Waiting"); }
  
  Serial.println(Serial3.parseFloat());
  
  delay(5000);
}
