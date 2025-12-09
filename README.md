Jason Pliszak + Vanessa Namirembe

BeagleSnake*DX is a hardware*accelerated snake game built using the Qt Graphics framework designed to run on the BeagleBone with an attached LCD Display.

Overview
	* Fully functional Snake Game using Qt Framework 
	* LCD 4.3" display 
	* BBB Rev. C (runs/hosts game)
	* smooth responsive gameplay 
	* clean seperation between game logic and UI 
	* Touchscreen + keyboard control 
	* Buzzer sound output (emiting sound based on gamestate)
	* Polished UI 
	* High score Tracking 
  
How to Run Code: (Assuming BBB and LCD cape are configured based on EC535 Lab5/Project instructions)
###1. clone git repo onto local device 
###2. Compile with resources and toolchain contained within $EC535/ folder set up for Qt 5.15.2 
	2a. Steps:
		* ssh to vlsi or signals BU machine (local)
		* source /ad/eng/courses/ec/ec535/bashrc_ec535 (remote)
		* export WORKSPACE=$HOME/EC535/lab5 (remote)
		* mkdir -p $WORKSPACE (remote)
		* cd $WORKSPACE (remote)
		* zip -r BeagleSnake-DX.zip BeagleSnake-DX/src BeagleSnake-DX/Snake_game.pro BeagleSnake-DX/README.md BeagleSnake-DX/icons BeagleSnake-DX/resources.qrc (local)
		* scp <path_to_.zip>/BeagleSnake-DX.zip <username>@vlsiXX:/home/<username>/EC535/lab5/ (local)
		* unzip BeagleSnake-DX.zip (remote)
		* cd BeagleSnake-DX (remote)
			* qmake 
			* make 
		* scp <username>@vlsiXX:/home/<username>/EC535/lab5/BeagleSnake-DX/BeagleSnake-DX ~/Downloads/ (local)
  ###3. Once Executable is available using above commands or by using Pre-compiled verion (BeagleSnake-DX_V4)
	3a. Steps:
		* connect USB to TTL Serial Cable to local device + BBB
			* green -> UART4_RXD
			* white -> UART4_TXD
			* black -> GND 
		* run ls -d /dev/- | grep -i 'usb\|ama\|sac' 
		* run picocom -b 115200 -s sz -v rz SERIAL_DEV
			* Login to BBB 
				* username: root 
				* password: ec535 
		* rz then... cmd A + cmd S 
		* enter file path to executable
		* wait for transfer to complete...
  ###4. Connect Devices to BBB 
	4a. Steps:
		* USB keyboard to USB port on BBB 
		*connect LCD Cape to BBB 
		* connect LCD display to LCD Cape 
		* connect Buzzer(+) to P9_14 on LCD Cape 
		* connect Buzzer(-) to GND on LCD Cape 
  ###5.  Run on BBB
	5a. Steps:
		* chmod +x BeagleSnake-DX
		* echo 0 > /sys/class/vtconsole/vtcon1/bind
		* <./BeagleSnake-DX or ./BeagleSnake-DX_V4> -platform linuxfb
		* HAVE FUN + PLAY SNAKE!!!



