# Twisted-String-Robot-Dog
Arduino-powered quadruped robot dog using Twisted-String Actuators for leg movement. Features homing with limit switches, PWM motor control, and a simple walking gait.


## 1. Overview
This project implements a small quadruped (four-legged) robot dog that uses **Twisted-String Actuators** instead of traditional servo motors.  
A Twisted-String Actuator works by twisting a high-strength string with a small DC motor, causing the string to shorten and pull a joint — simulating a muscle. When untwisted, the joint returns to its original position.

The robot can perform a simple walking gait by alternating diagonal leg movements.

---

## 2. Components
- 4 × Small DC motors (3–6V recommended)
- 2 × Dual-channel motor driver modules (TB6612FNG or L298N)
- Arduino Uno (or similar)
- High-strength nylon fishing line
- 4 × Limit switches (for homing)
- Spools/pulleys for each motor (can be 3D printed)
- Robot dog frame (wood, plastic, or 3D printed)
- Battery pack (Li-ion 7.4V or 6V AA pack)
- Wires and connectors

---

## 3. How It Works
- **Homing:** At startup, each actuator twists until it presses its limit switch. This defines the “home” position.
- **Actuation:** PWM signals control the motors to twist (shorten) or untwist (lengthen) the string.
- **Walking:** The robot lifts and lowers diagonal pairs of legs in sequence to move forward.

---

## 4. Wiring
### Example Pin Mapping (Arduino Uno)
| Leg | IN1 | IN2 | PWM | Limit Switch |
|-----|-----|-----|-----|--------------|
| Front Left (FL)  | D2 | D3 | D5  | A0 |
| Front Right (FR) | D4 | D7 | D6  | A1 |
| Back Left (BL)   | D8 | D9 | D10 | A2 |
| Back Right (BR)  | D11| D12| D3  | A3 |

> **Note:** If using TB6612, connect VM to motor supply voltage, VCC to 5V logic, and GND to Arduino GND.

---

## 5. Arduino Code
A simple open-loop Arduino sketch is included in this repository:
- Calibrates actuators using limit switches.
- Moves diagonal leg pairs alternately to simulate walking.

---

## 6. Usage
1. **Build the frame** — attach motors, pulleys, and string to each leg joint.
2. **Wire everything** according to the table above.
3. **Upload the code** to Arduino.
4. **Power on the robot** — it will home all actuators, then start walking.
5. Adjust PWM speed and delays in code to refine movement.

---

## 7. Tips
- Use smooth, low-friction string guides to prevent wear.
- Test each actuator individually before assembling all four.
- Consider adding springs for automatic return motion.
- For more precise control, add rotary encoders to each motor.

---

## 8. Future Improvements
- Implement closed-loop control with encoders.
- Add sensors for obstacle avoidance.
- Create multiple gaits (e.g., trot, crawl).
- Make the frame from lightweight carbon fiber for speed.

---

