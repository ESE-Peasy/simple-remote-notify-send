# About the Library

UDP Broadcaster and Receiver to trigger Notify-Send messages

## Requirements

- Currently the system only runs on Linux
- notify-send [See here for more details](http://vaskovsky.net/notify-send/linux.html)

You can test notify-send is working with a simple command like

`notify-send "Test"`

A pop up should appear on your screen, with the text "Test"

_Note: It's been found on the raspberry pi to make notify-send work, the following installs are also needed_  
`sudo apt-get install mate-notification-daemon mate-notification-daemon-common`

## Example Projects

[Posture Perfection](https://github.com/ESE-Peasy/PosturePerfection)

## Future Work

- Add MacOS broadcaster and client
- Add Windows broadcaster and client
