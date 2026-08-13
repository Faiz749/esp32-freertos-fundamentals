SemaphoreHandle_t counterMutex;
int counter = 0;
void taskone(void *parameter);
void tasktwo(void *parameter);


void setup(){
  Serial.begin(115200);
  counterMutex = xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(taskone,"Task One",1000,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(tasktwo,"Task Two",1000,NULL,1,NULL,1);
}


void loop(){
}


void taskone(void *parameter){
  while(true){
    if(xSemaphoreTake(counterMutex,portMAX_DELAY) == pdTRUE){
      counter++;
      Serial.print("Task 1 Counter: ");
      Serial.println(counter);
      xSemaphoreGive(counterMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}


void tasktwo(void *parameter){
  while(true){
    if(xSemaphoreTake(counterMutex,portMAX_DELAY)==pdTRUE){
      counter++;
      Serial.print("Task 2 Counter: ");
      Serial.println(counter);
      xSemaphoreGive(counterMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

