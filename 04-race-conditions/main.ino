#define LED_PIN 5

int counter = 0;

void increment_Counter(void *parameter);
void read_Counter(void *parameter);

void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
  xTaskCreatePinnedToCore(increment_Counter,"Increment Counter",1000,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(read_Counter,"Read_Counter",1000,NULL,1,NULL,1);
}

void loop(){

}

void increment_Counter(void *parameter){
  while(true){
    counter ++;
    digitalWrite(LED_PIN,HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    counter ++;
    digitalWrite(LED_PIN,LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void read_Counter(void *parameter){
  while(true){
    Serial.print("Monitor Task: Counter = ");
    Serial.println(counter);
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}


