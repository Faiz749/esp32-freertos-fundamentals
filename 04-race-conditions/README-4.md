# Day 4: Shared Variables and Race Conditions

## Project Description

This project demonstrates how multiple FreeRTOS tasks can access the same shared variable on an ESP32.

A global counter is shared between two tasks. One task increases the counter and controls an LED, while the other task reads the counter and prints its value to the Serial Monitor.

No mutex or semaphore is used in this lab because the goal is to understand how shared data works and why race conditions can occur.

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
ESP32 GPIO 5 → 220 Ω resistor → LED anode
LED cathode → ESP32 GND
```

## Task Structure

### Increment Counter Task

This task:

* Increases the shared counter.
* Turns the LED ON.
* Waits for 500 milliseconds.
* Increases the counter again.
* Turns the LED OFF.
* Waits for another 500 milliseconds.
* Repeats continuously.

### Read Counter Task

This task:

* Reads the shared counter.
* Prints its value to the Serial Monitor.
* Waits for 300 milliseconds.
* Repeats continuously.

Since the read task runs every 300 ms while the counter changes every 500 ms, the same counter value may sometimes be printed more than once.

## Shared Variable

Both tasks use the same global counter variable.

The increment task changes the counter, while the read task accesses its current value. Since no synchronization method is used, both tasks can access the shared data independently.

This helps demonstrate how task scheduling can affect shared variables.

## Serial Monitor Output

Example output:

```text
Monitor Task: Counter = 0
Monitor Task: Counter = 1
Monitor Task: Counter = 1
Monitor Task: Counter = 2
Monitor Task: Counter = 3
Monitor Task: Counter = 3
```

The exact output may vary depending on when FreeRTOS schedules each task.

## Race Condition

A race condition can happen when multiple tasks access the same shared data and at least one task modifies it.

The result can depend on the order and timing of task execution. In this lab, the counter is intentionally left without protection so that shared-data behaviour can be observed.

In larger programs, shared resources may need synchronization using mechanisms such as mutexes or semaphores.

## Concepts Learned

* Sharing a global variable between FreeRTOS tasks
* Reading and modifying shared data
* Understanding the basic idea of race conditions
* Using `vTaskDelay()` for task timing
* Using `pdMS_TO_TICKS()`
* Running multiple tasks with the same priority
* Running multiple tasks on the same ESP32 core
* Understanding how different task delays affect execution
* Understanding why shared data may need protection

## Mistakes Fixed

* Configured GPIO 5 correctly as an LED output.
* Used a global counter so both tasks could access it.
* Created separate tasks for modifying and reading the counter.
* Used `vTaskDelay()` instead of Arduino `delay()`.
* Used `pdMS_TO_TICKS()` for FreeRTOS delays.
* Kept both tasks at the same priority to focus on shared-data behaviour.

## Demo Files

* `race-condition-circuit-photo.jpeg`
* `shared-counter-screenshot.png`

## Embedded Systems Relevance

Shared data is common in embedded systems. Different tasks may need to access sensor readings, counters, system states, communication data, or hardware resources.

If shared data is accessed without proper synchronization, timing-related problems can occur. This lab provides a basic introduction to that problem before learning how mutexes and semaphores can be used to protect shared resources.

## Conclusion

This project showed how two FreeRTOS tasks can work with the same shared variable.

One task updates the counter and controls the LED, while the other monitors the counter through the Serial Monitor. The different task delays also show that FreeRTOS tasks can run independently and may access the same data at different times.

This lab provides a foundation for understanding race conditions and why synchronization is important in larger embedded systems.
