#define GREEN_LED 5
#define BLUE_LED 2
#define RED_LED 4

void ledtask1(void *parameter);
void ledtask2(void *parameter);
void ledtask3(void *parameter);

void setup(){

  Serial.begin(115200);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(BLUE_LED,LOW);
  digitalWrite(RED_LED,LOW);
  xTaskCreatePinnedToCore(ledtask1,"LED Task 1",1000,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(ledtask2,"LED Task 2",1000,NULL,2,NULL,1);
  xTaskCreatePinnedToCore(ledtask3,"LED Task 3",1000,NULL,3,NULL,1);

}

void loop(){

}

void ledtask1(void *parameter){
  while(true){
    digitalWrite(GREEN_LED,HIGH);
    Serial.println("Status Task: Green LED ON");
    vTaskDelay(pdMS_TO_TICKS(1000));
    digitalWrite(GREEN_LED,LOW);
    Serial.println("Status Task: Green LED OFF");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void ledtask2(void *parameter){

  while(true){
    digitalWrite(BLUE_LED,HIGH);
    Serial.println("Sensor Processing Task: Blue LED ON");
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(BLUE_LED,LOW);
    Serial.println("Sensor Processing Task: Blue LED OFF");
    vTaskDelay(pdMS_TO_TICKS(500));
  
  }
}

void ledtask3(void *parameter){
  while(true){
    digitalWrite(RED_LED,HIGH);
    Serial.println("Alarm Task: RED LED ON");
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(RED_LED,LOW);
    Serial.println("Alarm Task: RED LED OFF");
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}



