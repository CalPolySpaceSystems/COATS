This demo is meant to show a simple way of interfacing an Arduino with the COSMOS software. The Arduino reads its ADCs and sends the packets over USB into COSMOS. It is assumed that you have a working install of COSMOS.

# Instructions
1: Compile and upload `COATS_Example.ino` to an Arduino Uno or other compatible board.
2: Take note of what Serial port your Arduino is connected to.
3: Launch COSMOS via running `Launcher` or `Launcher.bat` in the `COSMOS_COATS_DEMO` folder.
4: Open the Config Editor by clicking its button on the bottom of the launcher.
5: In the file browser on the left side of the window, navigate to `config/targets/COATS/cmd_tlm_server.txt`
6: In this file, replace the write and read ports with the ports your Arduino is connected to.
7: Save the file and exit the Config Editor
8: Open the Command and Telemetry Server
9: COSMOS should connect to the Arduino automatically.
10: Open the Telemetry Viewer from the Launcher to see the voltages the ADCs are reading.
