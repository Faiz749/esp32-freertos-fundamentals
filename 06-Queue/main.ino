QueueHandle_t sensorQueue;
void sensorTask(void *parameter);
void displayTask(void *parameter);

void setup(){
  Serial.begin(115200);
  sensorQueue = xQueueCreate(5,sizeof(int));
  if (sensorQueue != NULL){
    Serial.println("Queue created successfully");
  }
  xTaskCreatePinnedToCore(sensorTask,"Sensor Task",2048,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(displayTask,"Display Task",2048,NULL,1,NULL,1);
}

void loop(){
}

void sensorTask(void *parameter){
  int sensorValue = 100;
  while(true){
    sensorValue += 10;
    Serial.print("Sensor Task Sent: ");
    Serial.println(sensorValue);
    if(xQueueSend(sensorQueue,&sensorValue,portMAX_DELAY)== pdTRUE){
      vTaskDelay(pdMS_TO_TICKS(500));
    }
  }
  
}

void displayTask(void *parameter){
  int receivedValue;
  while(true){
    if(xQueueReceive(sensorQueue,&receivedValue,portMAX_DELAY)== pdTRUE){
      Serial.print("Monitor Task Received: ");
      Serial.println(receivedValue);
    }
  }
}



