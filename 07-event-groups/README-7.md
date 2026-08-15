# Day 7: FreeRTOS Event Groups

## Project Description

This project demonstrates how **FreeRTOS Event Groups** can be used to keep track of multiple ON/OFF conditions.

Three safety events are simulated:

* Flame
* Gas
* Obstacle

Two FreeRTOS tasks are used:

* **Event Simulator Task** changes the event states.
* **Event Monitor Task** reads the states and prints them to the Serial Monitor.

No physical sensors are used. Everything is simulated in software.

## Components Used

* ESP32
* Arduino IDE
* Serial Monitor

## Event Group

The Event Group is created to store the different safety conditions.

Each event uses one bit:

```text
Bit 0 → Flame
Bit 1 → Gas
Bit 2 → Obstacle
```

The bits are defined using:

```cpp
#define FLAME_BIT     (1 << 0)
#define GAS_BIT       (1 << 1)
#define OBSTACLE_BIT  (1 << 2)
```

Each bit can be either `1` (ON) or `0` (OFF).

## Task Structure

### Event Simulator Task

The Event Simulator Task changes the event states.

It:

* Turns Flame ON.
* Turns Gas ON.
* Turns Flame OFF.
* Turns Obstacle ON.
* Turns Gas OFF.
* Turns Obstacle OFF.
* Repeats the sequence.

An event is turned ON using:

```cpp
xEventGroupSetBits(safetyEvents, FLAME_BIT);
```

An event is turned OFF using:

```cpp
xEventGroupClearBits(safetyEvents, FLAME_BIT);
```

There is a small delay between each change.

### Event Monitor Task

The Event Monitor Task checks the current event states and prints them to the Serial Monitor.

The Event Group is read using:

```cpp
EventBits_t bits;

bits = xEventGroupGetBits(safetyEvents);
```

A specific event can then be checked like this:

```cpp
if (bits & FLAME_BIT)
```

If the bit is set, the event is active. If it is not set, the event is safe.

The Monitor Task also uses:

```cpp
vTaskDelay(pdMS_TO_TICKS(1000));
```

so it does not print continuously too fast.

## Concepts Learned

* Understanding FreeRTOS Event Groups
* Creating and using Event Groups
* Using event bits to represent ON/OFF states
* Using `xEventGroupSetBits()`
* Using `xEventGroupClearBits()`
* Using `xEventGroupGetBits()`
* Checking individual event bits
* Using multiple FreeRTOS tasks
* Understanding `EventBits_t`
* Understanding how multiple conditions can be stored in one Event Group

## Output

Example Serial Monitor output:

```text
------ Safety Status ------
Flame: Active
Gas: SAFE
Obstacle: SAFE

------ Safety Status ------
Flame: Active
Gas: Active
Obstacle: SAFE

------ Safety Status ------
Flame: SAFE
Gas: Active
Obstacle: SAFE

------ Safety Status ------
Flame: SAFE
Gas: Active
Obstacle: Active
```

The Event Simulator changes the bits, and the Monitor Task displays the current state.

## Mistakes Fixed

* Changed `EventGroupHandle_t bits` to the correct `EventBits_t bits`.
* Added a delay to the Monitor Task so it does not print too quickly.
* Added a check to make sure the Event Group was created successfully.
* Used the correct bit for each safety condition.

## Demo Files

* `event-group-output.png`

## Embedded Systems Relevance

Event Groups are useful when an embedded system needs to keep track of several conditions at the same time.

For example:

```text
Flame detected
Gas detected
Obstacle detected
```

Each condition can be represented by a different bit.

This allows multiple FreeRTOS tasks to easily check or react to different events without needing separate variables for every condition.
