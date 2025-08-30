# bee_monitor.py — Passive Acoustic Bee Activity Monitor

This project uses a Raspberry Pi and a USB microphone to monitor bee activity in small gardens or flowerbeds. It records short audio clips, estimates the power spectral density (PSD) using Welch’s method, and logs events when energy in the bee wingbeat frequency band (default: 200–300 Hz) exceeds a configurable `THRESHOLD`.

---

## Features

- Lightweight, self-contained Python script suitable for Raspberry Pi 3/4
- Detects bee presence acoustically without disturbing plants or insects
- Logs timestamped activity events to `bee_activity.csv`
- Optional console output for real-time monitoring

---

## Dependencies

**Python libraries (install via pip):**
- `numpy`
- `scipy`
- `sounddevice`

**Standard library modules (no install needed):**
- `time`
- `datetime`

---

## Hardware Requirements

- Raspberry Pi 3/4 (or similar capable of running Python 3.x)
- USB polar-pattern condenser microphone (plug-and-play)

---

## Key Concepts

- **Welch’s method**: Produces a smoothed, averaged PSD, reducing the effect of random noise spikes and making it easier to detect consistent signals like bee buzz frequencies.  
- **THRESHOLD**: Defines the minimum power in the bee frequency band that counts as activity, filtering out background noise (wind, traffic, etc.).

---

## Why THRESHOLD Matters

Without a threshold, weak background noise could be logged as bee activity. Setting an appropriate threshold ensures only signals strong enough to indicate actual bee presence are recorded.

---

## Tuning Guidance

- **Too low**: Background hum or distant sounds may trigger false positives.  
- **Too high**: Quiet but real bee activity may be ignored (false negatives).  
- **Best practice**: Run the script in your environment, examine logged scores, and adjust `THRESHOLD` upward until non-bee background is consistently excluded, but genuine activity is detected.

---

## Usage

1. Install dependencies:

```bash
pip install numpy scipy sounddevice
