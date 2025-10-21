# buzz_monitor

**A passive acoustic bee monitor**

This project uses a Raspberry Pi and a USB microphone to monitor bee activity in small gardens or flowerbeds. It records short audio clips, estimates the power spectral density (PSD) using Welch’s method, and logs events when energy in the bee wingbeat frequency band (default: 200–300 Hz) exceeds a configurable `THRESHOLD`. 

This project is in alpha testing. To join testing, please download the latest release v.0.1.0. 

---

## Features

- Lightweight, self-contained Python script suitable for Raspberry Pi 3/4
- Detects bee presence acoustically without disturbing plants or insects
- Logs timestamped activity events to `buzz_activity.csv`
- Optional console output for real-time monitoring

---

## Dependencies

**Python libraries (install via pip):**
- `numpy`
- `scipy`
- `sounddevice`
---

## Hardware Requirements

- Raspberry Pi 3/4 (or similar capable of running Python 3.x)
- Condenser USB microphone. Omnidirectional pattern recommended, but physical placement of the device might require different polar patterns. Any plug-and-play mic will work, since mics intended for human voice usually capture along the 100Hz - 8Khz range). 

---

## Defining THRESHOLD

- **THRESHOLD**: Defines the minimum power in the bee frequency band that counts as activity, filtering out background noise (wind, traffic, etc.).

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
pip install -r requirements.txt
```

2. Connect your USB microphone to the Raspberry Pi

3. Run the script:

```bash
python bee_monitor.py
```

4. Check bee_activity.csv offline for logged events. For real-time monitoring, you attach a monitor attached and observe console output.

---

## Outputs

bee_activity.csv: CSV file logging timestamp and activity score whenever bee activity exceeds the threshold.

Console prints: Optional real-time detection feedback.

## License

MIT License. 

## Open source and Alpha testing

Please share any comments and contributions you might have at connor@connorlafitte.com
