# ReSpeaker Lights

Control the NeoPixels on the ReSpeaker with your voice. 

[Demo video](https://youtu.be/xZ3_fAlDEvA?t=2s)

## Prerequisites

These instructions assume that you've set up the network on your ReSpeaker. See the [Getting Started Guide](https://github.com/respeaker/get_started_with_respeaker/wiki) for more info.

## Installation

### Arduino
On your computer use Arduino IDE 1.6.11 to load [lights.ino](lights.ino) onto your ReSpeaker.

### OpenWrt

Clone the source code onto the SD Card of your ReSpeaker.

ssh to the ReSpeaker

    ssh root@mylinkit.local

Clone this repo onto the SD card

    cd /tmp/run/mountd/mmcblk0p1
    git clone https://github.com/don/respeaker-lights.git

Libraries

    cd respeaker-lights
    pip install monotonic webrtcvad

Get a key for the [Bing Speech API](https://www.microsoft.com/cognitive-services/en-us/speech-api) and create creds.py with the key

    cp creds_template.py creds.py
    vi creds.py  # add the key and save

Run the app

    python lights.py

Give the app time to start, then try "Turn the lights on", "Make the lights red", "Turn the brightness up", "Make the lights green", "Turn the lights off".

## Next

What's next? This app runs an open microphone and sends all text to Microsoft for voice to text, which isn't ideal. Ideally this could run in offline mode using pocketsphinx or use a combination of keyword spotting and Bing. See the [pocketsphinx_keyword_spotting](https://github.com/respeaker/pocketsphinx_keyword_spotting) and [respeaker_hi](https://github.com/respeaker/respeaker_hi) examples.

## Props

This code is based on the [microsoft_cognitive_services](https://github.com/respeaker/microsoft_cognitive_services) and [spi bridge](https://github.com/respeaker/spi_bridge) ReSpeaker examples.
