# Day 1: FreeRTOS Tasks and Scheduler

## Project Description

This lab introduces basic FreeRTOS task creation on the ESP32.

Two tasks run independently:

* LED Task → turns the LED ON and OFF every 500 ms.
* Serial Task → prints a message every 1000 ms.

The tasks are created once in `setup()` and then managed by the FreeRTOS scheduler.

## Components Used

* ESP32 38-pin board
* LED
* 220 Ω resistor
* Breadboard
* Jumper wires
* USB cable

## Wiring

### LED

```text
ESP32 GPIO 2 → 220 Ω resistor → LED anode
LED cathode → ESP32 GND
```

## Concepts Learned

- Basic FreeRTOS task structure
- Using `xTaskCreatePinnedToCore()`
- Using `vTaskDelay()`
- Using `pdMS_TO_TICKS()`
- Running multiple tasks with the same priority
- Creating tasks once inside `setup()`
- Understanding basic task scheduling
- Running tasks on Core 1
- Understanding that task handles and task parameters can be left as `NULL` when not needed

## Example Output

```text
Serial Task is running
LED Task: LED OFF
LED Task: LED ON
Serial Task is running
LED Task: LED OFF
LED Task: LED ON
Serial Task is running
LED Task: LED OFF
LED Task: LED ON
Serial Task is running
LED Task: LED OFF
LED Task: LED ON
Serial Task is running
LED Task: LED OFF
LED Task: LED ON
Serial Task is running
LED Task: LED OFF
LED Task: LED ON
```

## Mistakes Fixed

- Learned that FreeRTOS tasks should normally be created once in `setup()`.
- Learned that `vTaskDelay()` pauses only the current task.
- Understood that equal-priority tasks can share CPU time.
- Learned that a task handle is not required when the task does not need to be controlled later.
- Learned that `Serial.begin()` and `pinMode()` are still required even when using FreeRTOS.

## Demo Files

- `circuit-photo.jpeg`
- `task-output-screenshot.png`

## Embedded Systems Relevance

FreeRTOS helps split a larger embedded system into separate tasks for sensors, outputs, communication, displays, and control logic.

This makes complex firmware easier to organize and helps different parts of the system stay responsive.