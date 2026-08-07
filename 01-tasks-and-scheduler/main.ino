#define LED_PIN 2 

void ledtask(void *parameter);
void serialmonitorTask(void *parameter);
 
void setup(){
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
  xTaskCreatePinnedToCore(serialmonitorTask,"Serial monitor task",1000,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(ledtask,"led task",1000,NULL,1,NULL,1);
  Serial.println("FreeRTOS Day 1 started");

}

void loop(){

}

void ledtask(void *parameter){

  while(true){
    
    digitalWrite(LED_PIN,LOW);
    Serial.println("LED Task: LED OFF");
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LED_PIN,HIGH);
    Serial.println("LED Task: LED ON");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void serialmonitorTask(void *parameter){
  while(true){
    Serial.println("Serial Task is running");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


