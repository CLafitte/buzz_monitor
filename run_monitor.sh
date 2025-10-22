#!/bin/bash

MODE_FILE="/home/pi/buzz-monitor/monitor_mode.txt"

# Check if mode has been set previously
if [ -f "$MODE_FILE" ]; then
    MODE=$(cat "$MODE_FILE")
else
    # First-time setup: prompt user
    echo "Select monitoring mode:"
    echo "1) Burst mode (short periodic recordings)"
    echo "2) Long recording mode (1-hour + C++ analysis)"
    read -p "Enter 1 or 2 (default 1): " MODE
    case $MODE in
        2) MODE=2 ;;
        *) MODE=1 ;;
    esac
    echo "$MODE" > "$MODE_FILE"
fi

# Run the selected mode
case $MODE in
    1)
        echo "Starting burst mode..."
        python3 /home/pi/buzz-monitor/buzz_monitor.py
        ;;
    2)
        echo "Starting long recording mode..."
        python3 /home/pi/buzz-monitor/long_record.py
        ;;
    *)
        echo "Invalid mode file. Defaulting to burst mode..."
        python3 /home/pi/buzz-monitor/buzz_monitor.py
        ;;
esac
