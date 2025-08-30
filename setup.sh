#!/bin/bash
# Install dependencies
sudo apt update
sudo apt install -y python3-pip
pip3 install -r /home/pi/buzz-monitor/requirements.txt

# Make script executable
chmod +x /home/pi/buzz-monitor/buzz_monitor.py

# Setup auto-run on boot via crontab
(crontab -l 2>/dev/null; echo "@reboot /usr/bin/python3 /home/pi/buzz-monitor/buzz_monitor.py") | crontab -
