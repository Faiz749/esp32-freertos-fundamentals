## Day 1: FreeRTOS Tasks and Scheduler

## Project Description

In this lab, I learned how to create and run multiple FreeRTOS tasks on the ESP32.

The project uses two independent tasks:

* **LED Task** – blinks an LED every 500 ms.
* **Serial Task** – prints a message to the Serial Monitor every 1000 ms.

Both tasks use `vTaskDelay()` instead of blocking the processor. While one task is waiting, the FreeRTOS scheduler allows the other task to run.

This demonstrates one of the main advantages of using an RTOS: multiple operations can be organized into separate tasks while sharing CPU time efficiently.

## Components Used

* ESP32 38-pin development board
* LED
* 220 Ω resistor
* Breadboard
* Jumper wires
* USB cable

## Wiring

The LED was connected to GPIO 2 of the ESP32 through a 220 Ω current-limiting resistor.

```text
ESP32 GPIO 2 → 220 Ω resistor → LED anode
LED cathode → ESP32 GND
```

## Concepts Learned

During this lab, I practiced several important FreeRTOS concepts:

* Creating basic FreeRTOS tasks
* Using `xTaskCreatePinnedToCore()`
* Using `vTaskDelay()` for non-blocking task delays
* Converting milliseconds to RTOS ticks with `pdMS_TO_TICKS()`
* Running multiple tasks with the same priority
* Understanding how the scheduler shares CPU time between ready tasks
* Creating tasks once inside the Arduino `setup()` function
* Understanding when a task handle is optional

## Example Output

The Serial Monitor produced output similar to the following:

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
```

The output shows that both tasks are running independently while being managed by the FreeRTOS scheduler.

## Mistakes Fixed and Lessons Learned

A few important lessons became clearer while completing this lab:

* Tasks should normally be created once inside `setup()` rather than repeatedly inside `loop()`.
* `vTaskDelay()` pauses only the task that calls it. It does not stop the entire ESP32.
* Tasks with the same priority can share CPU time when they are both ready to run.
* A task handle is not required if the task does not need to be suspended, deleted, resumed, or controlled later.

## Demo Files

The project folder also includes files showing the physical circuit and program output:

* `circuit-photo.jpeg` – photo of the completed ESP32 and LED circuit
* `task-output-screenshot.png` – screenshot of the Serial Monitor output

## Embedded Systems Relevance

FreeRTOS is useful because it allows an embedded application to be divided into separate tasks.

For example, a larger system could have individual tasks for:

* Reading sensors
* Updating a display
* Controlling LEDs or motors
* Handling Wi-Fi or Bluetooth communication
* Monitoring buttons or user input
* Running control logic

Separating these operations into tasks makes larger embedded systems easier to organize, maintain, and expand. It also helps keep the system responsive because one delayed task does not necessarily prevent other tasks from running.
