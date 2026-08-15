EventGroupHandle_t safetyEvents;
#define FLAME_BIT (1<<0)
#define GAS_BIT (1<<1)
#define OBSTACLE_BIT (1<<2)

void eventSimulator(void *parameter);
void eventMonitor(void *parameter);

void setup(){
    Serial.begin(115200);
    safetyEvents = xEventGroupCreate();
    if(safetyEvents == NULL){
        Serial.println("Safety Event couldn't be created");
        return;
    }
    Serial.println("Safety Event created succesfully!!");
    xTaskCreatePinnedToCore(eventSimulator,"Event Simulator",2048,NULL,1,NULL,1);
    xTaskCreatePinnedToCore(eventMonitor,"Event Monitor",2048,NULL,1,NULL,1);
}

void loop(){
}

void eventSimulator(void *parameter){
    while(true){
      xEventGroupSetBits(safetyEvents,FLAME_BIT);
      vTaskDelay(pdMS_TO_TICKS(500));
      xEventGroupSetBits(safetyEvents,GAS_BIT);
      vTaskDelay(pdMS_TO_TICKS(500));
      xEventGroupClearBits(safetyEvents,FLAME_BIT);
      vTaskDelay(pdMS_TO_TICKS(500));
      xEventGroupSetBits(safetyEvents,OBSTACLE_BIT);
      vTaskDelay(pdMS_TO_TICKS(500));
      xEventGroupClearBits(safetyEvents,GAS_BIT);
      vTaskDelay(pdMS_TO_TICKS(500));
      xEventGroupClearBits(safetyEvents,OBSTACLE_BIT);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void eventMonitor(void *parameter){
    EventBits_t bits;
    while(true){
      bits = xEventGroupGetBits(safetyEvents);
      Serial.println("------ Safety Status ------");


      Serial.print("Flame: ");
      if(bits & FLAME_BIT){
        Serial.println("Active");
      }
      else{
        Serial.println("SAFE");
      }

      Serial.print("GAS: ");
      if(bits & GAS_BIT){
        Serial.println("Active");
       }
      else{
        Serial.println("SAFE");
       }

      Serial.print("OBSTACLE: ");
      if(bits & OBSTACLE_BIT){
        Serial.println("Active");
       }
      else{
        Serial.println("SAFE");
      }
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
}













