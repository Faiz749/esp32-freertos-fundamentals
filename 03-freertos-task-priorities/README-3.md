# Day 3: FreeRTOS Task Priorities

## Project Description

This project demonstrates FreeRTOS task priorities on the ESP32 using three independent LED tasks.

Each task represents a different type of embedded-system activity:

* Status Task
* Sensor Processing Task
* Alarm Task

All three tasks run on Core 1, but each task is assigned a different priority. The Status Task has the lowest priority, the Sensor Processing Task has medium priority, and the Alarm Task has the highest priority.

Each task controls its own LED and uses `vTaskDelay()` for independent timing. The Serial Monitor prints the activity of each task as its LED turns ON and OFF.

## Components Used

* ESP32 38-pin board
* Green LED
* Blue LED
* Red LED
* 3 × 220 Ω resistors
* Breadboard
* Jumper wires
* USB cable

## Wiring

### Green LED

```text
ESP32 GPIO 5 → 220 Ω resistor → Green LED anode
Green LED cathode → ESP32 GND
````

### Blue LED

```text
ESP32 GPIO 2 → 220 Ω resistor → Blue LED anode
Blue LED cathode → ESP32 GND
```

### Red LED

```text
ESP32 GPIO 4 → 220 Ω resistor → Red LED anode
Red LED cathode → ESP32 GND
```

## Task Configuration

### Status Task

```text
LED: Green
Priority: 1
Core: 1
ON time: 1000 ms
OFF time: 1000 ms
```

### Sensor Processing Task

```text
LED: Blue
Priority: 2
Core: 1
ON time: 500 ms
OFF time: 500 ms
```

### Alarm Task

```text
LED: Red
Priority: 3
Core: 1
ON time: 500 ms
OFF time: 1500 ms
```

## Concepts Learned

* Creating multiple FreeRTOS tasks
* Assigning different priorities to tasks
* Understanding that a higher priority means greater scheduler preference
* Understanding that task priority does not determine task timing
* Using `vTaskDelay()` for independent task delays
* Using `pdMS_TO_TICKS()` to convert milliseconds into FreeRTOS ticks
* Running multiple tasks on the same ESP32 core
* Using embedded-style task roles such as status, sensor processing, and alarm handling
* Controlling separate GPIO outputs from different tasks
* Using Serial Monitor to observe task execution
* Leaving the Arduino `loop()` empty while FreeRTOS tasks perform the repeated work

## Output

Example Serial Monitor output:

```text
Status Task: Green LED ON
Sensor Processing Task: Blue LED ON
Alarm Task: RED LED ON
Sensor Processing Task: Blue LED OFF
Alarm Task: RED LED OFF
Status Task: Green LED OFF
Sensor Processing Task: Blue LED ON
Sensor Processing Task: Blue LED OFF
```

The exact order of the messages can vary because the FreeRTOS scheduler decides which ready task runs.

## Mistakes Fixed

* Assigned a separate GPIO pin to each LED.
* Used a separate 220 Ω resistor for each LED.
* Configured all LED pins as outputs.
* Started all LEDs in the OFF state.
* Created a separate FreeRTOS task for each embedded-system activity.
* Assigned priorities 1, 2, and 3 to represent increasing task importance.
* Used `vTaskDelay()` instead of Arduino `delay()`.
* Used `pdMS_TO_TICKS()` for FreeRTOS timing.
* Kept all three tasks on Core 1 so task priority could be observed on the same CPU core.
* Used clearer embedded-system roles: Status Task, Sensor Processing Task, and Alarm Task.

## Demo Files

* `priority-circuit-photo.jpeg`
* `priority-output-screenshot.png`

## Embedded Systems Relevance

Task priorities are important in real-time embedded systems because some operations are more urgent than others.

A background status task may have low priority, sensor processing may require medium priority, and an alarm or safety task may require higher priority.

This lab demonstrates how FreeRTOS allows firmware tasks to be assigned different importance levels while still maintaining independent timing and execution.

