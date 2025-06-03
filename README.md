# 🚦 Arduino Traffic Light System with Pedestrian Control and Buzzer

## Overview

This project simulates a two-way traffic light system with pedestrian crosswalk buttons and an audible buzzer signal for pedestrian crossing. It uses an Arduino board to manage traffic light transitions and pedestrian interactions via push buttons.

The system controls two intersections and includes a buzzer to signal pedestrians when it is safe to cross.

## Features

- Two traffic light systems (for two directions)
- Pedestrian push-button integration for each side
- Audible buzzer signal during pedestrian crossing
- Timed traffic light state transitions
- Debounced button reading for reliable operation

## Components Used

- Arduino Uno (or compatible board)
- 6 LEDs (Red, Yellow, Green × 2 sets)
- 2 Push Buttons (for pedestrians)
- 1 Buzzer
- Resistors (220Ω for LEDs, 10kΩ for buttons)
- Breadboard and jumper wires

## How It Works

1. **Initial State:** One traffic light is green, the other is red.
2. **Timed Switch:** Lights alternate after `greenDuration` (5s) and `yellowDuration` (2s).
3. **Pedestrian Request:** When a button is pressed:
   - The system waits for a safe moment in the light cycle.
   - Then it halts vehicle traffic on the requested side.
   - Lights turn red for vehicles.
   - Green pedestrian signal is simulated by lighting LEDs and triggering a buzzer 5 times (with 1s intervals).
4. **Resumption:** Normal traffic flow resumes after the pedestrian phase.

## Code Highlights

- Uses `millis()` for non-blocking delays.
- Implements a simple state machine (`currentState`) for managing light phases.
- Buttons are debounced using software.
- Pedestrian phases are handled separately with a buzzer and controlled timing.

## Setup Instructions

1. Wire the components according to the pin configuration.
2. Upload the code to the Arduino using the Arduino IDE.
3. Open the Serial Monitor (9600 baud) to see button press feedback.

## Future Improvements

- Add pedestrian LED indicators (Walk/Don't Walk)
- Use an LCD to display countdown timers
- Add support for traffic sensors or adaptive timing
- Improve buzzer sound patterns (e.g., faster countdown beeps)
