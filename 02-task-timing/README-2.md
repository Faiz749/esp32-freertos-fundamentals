# Day 2: FreeRTOS Task Timing

## Project Description

This project demonstrates how multiple FreeRTOS tasks can run independently on an ESP32 using different timing intervals.

Three LEDs are controlled by three separate tasks:

* **Blue LED** toggles every **500 ms**
* **Red LED** toggles every **1000 ms**
* **Green LED** toggles every **2000 ms**

Each task uses `vTaskDelay()` to pause for its own interval. While one task is delayed, the FreeRTOS scheduler allows the other tasks to continue running.

The Serial Monitor also prints the current state of each LED whenever it changes.

## Components Used

* ESP32 38-pin development board
* Blue LED
* Red LED
* Green LED
* 3 × 220 Ω resistors
* Breadboard
* Jumper wires
* USB cable

## Wiring

### Blue LED

```text
ESP32 GPIO 4 → 220 Ω resistor → Blue LED anode
Blue LED cathode → ESP32 GND
```

### Red LED

```text
ESP32 GPIO 5 → 220 Ω resistor → Red LED anode
Red LED cathode → ESP32 GND
```

### Green LED

```text
ESP32 GPIO 2 → 220 Ω resistor → Green LED anode
Green LED cathode → ESP32 GND
```

## Task Configuration

```text
Blue LED Task
Priority: 1
Core: 1
Delay: 500 ms

Red LED Task
Priority: 1
Core: 1
Delay: 1000 ms

Green LED Task
Priority: 1
Core: 1
Delay: 2000 ms
```

All three tasks use the same priority and run on the same ESP32 core. The main difference is the delay assigned to each task.

## How It Works

Each task continuously repeats the same basic process:

1. Toggle its LED.
2. Print the LED state to the Serial Monitor.
3. Delay for the assigned amount of time using `vTaskDelay()`.
4. Repeat.

The important part is that `vTaskDelay()` only pauses the task that calls it.

For example, when the green LED task is delayed for 2000 ms, the blue and red LED tasks can still continue running at their own intervals.

## Concepts Learned

* Creating multiple FreeRTOS tasks
* Giving each task its own timing interval
* Running multiple tasks with the same priority
* Using `vTaskDelay()` instead of Arduino `delay()`
* Using `pdMS_TO_TICKS()` to convert milliseconds to FreeRTOS ticks
* Understanding that delaying one task does not block the others
* Running multiple tasks on the same ESP32 core
* Controlling different GPIO pins from separate tasks
* Monitoring task activity through the Serial Monitor
* Using an empty Arduino `loop()` when FreeRTOS tasks handle the repeated work

## Example Serial Monitor Output

```text
BLUE LED: OFF
RED LED: OFF
GREEN LED: OFF
BLUE LED: ON
BLUE LED: OFF
RED LED: ON
BLUE LED: ON
BLUE LED: OFF
GREEN LED: ON
RED LED: OFF
```

The exact order may be slightly different each time because the FreeRTOS scheduler decides which ready task runs first.

## Mistakes Fixed

Some important fixes and improvements made during this project:

* Set each LED pin as an `OUTPUT`
* Started all LEDs in the OFF state
* Created a separate task for each LED
* Replaced Arduino `delay()` with `vTaskDelay()`
* Used `pdMS_TO_TICKS()` for task delays
* Gave each LED a different delay interval
* Added Serial Monitor output for LED state changes
* Used a separate 220 Ω resistor for each LED

## Demo Files

* `task-timing-photo.jpeg`
* `task-timing-screenshot.png`
* `task-timing-demo.mp4`

## Embedded Systems Relevance

In real embedded systems, different parts of the system often need to run at different rates.

For example:

* A sensor task may run every few milliseconds.
* A button-checking task may run every few hundred milliseconds.
* A display task may update once every second.
* A communication task may send data at a completely different interval.

FreeRTOS makes this possible by allowing each task to manage its own timing without stopping the rest of the system.

This project is a simple example of that behaviour and builds a foundation for larger multitasking ESP32 applications.
