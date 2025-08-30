#for full usage instructions, please see full README.md in this repository. 

import sounddevice as sd
import numpy as np
from scipy.signal import welch
import time
from datetime import datetime

# Parameters
DURATION = 10   # seconds per recording
INTERVAL = 60   # seconds between recordings
SAMPLE_RATE = 44100
BEE_BAND = (200, 300)  # Hz range to monitor
THRESHOLD = 0.0001  # Optional: noise threshold


def record_audio():
    """Record a short audio clip from the microphone."""
    audio = sd.rec(int(DURATION * SAMPLE_RATE), samplerate=SAMPLE_RATE, channels=1, dtype='float32')
    sd.wait()
    return audio.flatten()

def band_power_welch(signal, fs, fmin=200, fmax=300, nperseg=1024):
    """Compute average power in a target frequency band using Welch’s method."""
    freqs, psd = welch(signal, fs=fs, nperseg=nperseg)
    mask = (freqs >= fmin) & (freqs <= fmax)
    band_power = np.mean(psd[mask])
    return band_power

def analyze(audio):
    """Return the bee band power for a given audio clip."""
    return band_power_welch(audio, SAMPLE_RATE, fmin=BEE_BAND[0], fmax=BEE_BAND[1])

# ------------------------
# Main monitoring loop
# ------------------------
try:
    while True:
        audio = record_audio()
        score = analyze(audio)
        timestamp = datetime.now().isoformat()

        if score > THRESHOLD:
            with open("bee_activity.csv", "a") as f:
                f.write(f"{timestamp},{score}\n")
            print(f"{timestamp} | Activity Score: {score}")
        else:
            print(f"{timestamp} | No significant activity")

        # Wait until next recording cycle
        time.sleep(max(0, INTERVAL - DURATION))

except KeyboardInterrupt:
    print("Monitoring stopped by user.")
except Exception as e:
    print(f"{datetime.now().isoformat()} | Error: {e}")
