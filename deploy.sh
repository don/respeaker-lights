# shell script to copy files from local computer to the respeaker
# assumes respeaker alias has been set up in ~/.ssh/config
scp lights.py bing_voice.py spi.py test.py creds.py respeaker:/tmp/run/mountd/mmcblk0p1/lights/
