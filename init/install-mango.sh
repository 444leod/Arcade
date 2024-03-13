#!/bin/bash

# Install Mango if its not installed

if which mango >/dev/null; then
    echo "Mango is already installed!"
    exit 0
fi
echo "Installing Mango"
sudo rm /bin/mango
sudo curl https://raw.githubusercontent.com/Clement-Z4RM/Mango/main/mango.py -o /bin/mango && sudo chmod +x /bin/mango
