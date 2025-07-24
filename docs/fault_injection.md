# Fault Injection Plan – Capstone EV Control Unit
Author: [M.taha]  
Date: July 24, 2025

---

## 🧪 Purpose

To simulate and test system responses to various fault conditions in the EV control unit. This helps verify robustness, diagnostic routines, and safety logic.

---

## 🔧 Fault Types & Injection Logic

### 1. Over-Temperature Fault (Battery)
- **Trigger**: Simulated battery temperature exceeds 60°C
- **Injection Method**:
  - Send CAN message with `data[0–1] = 0x1770` (6000 → 600.0 / 10 = 60°C)
- **Expected Behavior**:
  - Log overheat event
  - Trigger `enterProtectionMode()`
  - Disable charging or throttle motor torque

---

### 2. Over-Speed Fault (Motor RPM)
- **Trigger**: Motor RPM exceeds 10,000
- **Injection Method**:
  - Send CAN message with `data[0–1] = 0x2710` (10000)
- **Expected Behavior**:
  - Log over-speed warning
  - Cut power or trigger limp mode

---

### 3. Low Voltage Fault (Battery)
- **Trigger**: Voltage < 280V
- **Injection Method**:
  - Simulate voltage reading: `rand() % 40 + 240` (range 240–280)
- **Expected Behavior**:
  - Warning log + power reduction
  - Update system state to “Low Voltage”

---

### 4. Communication Timeout (CAN)
- **Trigger**: No message received from sensor ECU for >1s
- **Injection Method**:
  - Manually pause or skip message reception
- **Expected Behavior**:
  - Set fault flag for `sensor_offline`
  - Log event and enter degraded mode

---

### 5. Sensor Drift (Current Sensor)
- **Trigger**: Current reading slowly rises beyond realistic bounds
- **Injection Method**:
  - Gradually increase simulated current to unrealistic values (e.g. 300A)
- **Expected Behavior**:
  - Log “sensor abnormality”
  - Trigger self-check or sensor recalibration

---

## 🛠 Testing Tools
- `can_parser.c` with manual injection functions  
- `fault_logger.c` to log and timestamp events  
- CLI testing: `simulate_fault("battery_overtemp")`

---

## ✅ Planned Outcome

All fault cases should be:
- **Loggable**
- **Traceable in GitHub commits**
- **Handled with safe logic and fallback behavior**

---

## 🧾 Next Steps
- Implement `logEvent()` and `enterProtectionMode()` in code  
- Integrate into capstone system state machine  
- Simulate via test harness in CLI or debug console

