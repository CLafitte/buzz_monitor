#!/bin/bash
# Install dependencies
sudo apt update
sudo apt install -y python3-pip
pip3 install -r /home/pi/buzz-monitor/requirements.txt

# Make scripts executable
chmod +x /home/pi/buzz-monitor/buzz_monitor.py
chmod +x /home/pi/buzz-monitor/long_record.py
chmod +x /home/pi/buzz-monitor/run_monitor.sh

# Setup auto-run on boot via crontab
(crontab -l 2>/dev/null; echo "@reboot /home/pi/buzz-monitor/run_monitor.sh") | crontab -
