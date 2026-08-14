# Day 6: FreeRTOS Queues

## Project Description

This project demonstrates how FreeRTOS queues can be used to safely send data between two tasks.

A Sensor Task generates an integer value and sends it to a FreeRTOS queue. A Display Task waits for data in the queue, receives the value, and prints it to the Serial Monitor.

The project demonstrates producer-consumer communication without requiring both tasks to directly access the same shared variable.

## Components Used

* ESP32 38-pin board
* USB cable
* Serial Monitor

## Queue

The FreeRTOS queue is declared using:

```cpp
QueueHandle_t sensorQueue;
```

The queue is created inside `setup()` using:

```cpp
sensorQueue = xQueueCreate(5, sizeof(int));
```

The queue can store up to five integer values.

## Task Structure

### Sensor Task

The Sensor Task acts as the producer.

It:

* Starts with a sensor value of `100`.
* Increases the value by `10`.
* Sends the value into the queue.
* Prints the successfully sent value to the Serial Monitor.
* Waits for 500 milliseconds.
* Repeats continuously.

Data is sent using:

```cpp
xQueueSend(sensorQueue, &sensorValue, portMAX_DELAY);
```

If the queue is full, `portMAX_DELAY` causes the task to wait until space becomes available.

### Display Task

The Display Task acts as the consumer.

It:

* Waits for data to become available in the queue.
* Receives the integer value.
* Prints the received value to the Serial Monitor.
* Repeats continuously.

Data is received using:

```cpp
xQueueReceive(sensorQueue, &receivedValue, portMAX_DELAY);
```

If the queue is empty, the Display Task blocks and waits until new data arrives.

Because `xQueueReceive()` blocks the task while waiting, an additional `vTaskDelay()` is not required in the Display Task.

## Concepts Learned

* Understanding FreeRTOS queues
* Creating a queue using `xQueueCreate()`
* Using `QueueHandle_t`
* Sending data using `xQueueSend()`
* Receiving data using `xQueueReceive()`
* Understanding producer and consumer tasks
* Understanding queue capacity
* Understanding FIFO queue behavior
* Using `pdTRUE` to check successful queue operations
* Using `portMAX_DELAY` with queues
* Understanding that a sender blocks when the queue is full
* Understanding that a receiver blocks when the queue is empty
* Passing integer data safely between FreeRTOS tasks
* Understanding why a receiving task may not require `vTaskDelay()`

## Output

Example Serial Monitor output:

```text
Queue created successfully
Sensor Task Sent: 110
Monitor Task Received: 110
Sensor Task Sent: 120
Monitor Task Received: 120
Sensor Task Sent: 130
Monitor Task Received: 130
Sensor Task Sent: 140
Monitor Task Received: 140
```

The Sensor Task sends each generated value to the queue, and the Display Task receives the same value.

## Mistakes Fixed

* Renamed the local sensor value variable to `sensorValue` to avoid confusion with the `sensorTask()` function name.
* Added a check to confirm that the queue was successfully created.
* Removed the accidental semicolon after the `xQueueSend()` `if` condition.
* Checked `xQueueSend()` against `pdTRUE`.
* Printed the sent value only after the queue operation succeeded.
* Used `portMAX_DELAY` so tasks block instead of continuously checking the queue.
* Correctly avoided adding an unnecessary delay to the Display Task.

## Demo Files

* `queue-output-screenshot.png`

## Embedded Systems Relevance

FreeRTOS queues are widely used in embedded systems to transfer data safely between tasks.

For example, a sensor task can collect measurements and send them through a queue to another task responsible for processing, displaying, logging, or responding to that information.

Queues reduce direct sharing of global variables and provide a structured method for communication between concurrent tasks.
