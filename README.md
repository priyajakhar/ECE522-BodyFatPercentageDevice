# Body Fat Percentage Electronic Analyzer


### BIA
Body Fat percentage is a better representation of a person's nutritional state and muscle mass.

Bioelectrical impedance analysis (BIA) is a non-invasive method that uses bioelectrical impedance vector analysis (BIVA) to measure body fat percentage. BIA works by passing a fixed frequecy, low amplitude electrical current through the body via electrodes. The impedance of the body to this current results in voltage drop that hels estimate the body fat composition.


### Device
User provides basic information: gender, age and weight (in lbs) through the SerialMonitor of Arduino in the specific format of "<gender,age,weight>".
The electrical signal is produced by the device which travels through the user via the electrodes placed on the wrist and the ankle.
After about 3 seconds, the body fat percent of the user is displayed on the LCD.


### Contents:
    Device1.HEIC - Device with full enclosure
    Device2.HEIC - Device with inside components visible and working
    https://youtube.com/shorts/4t0SykkCMiM - Video of device being used by a human
    Materials List - List of all the components of the project

	Software 
		Microcontroller Software - finalCode.ino
		Microcontroller Software (earlier iteration) - draftCode.ino

	Hardware
		Schematic - "BIA_Schematic"
		PCB Layout - "BIA_Board_Layout.png"
		3D Models - "BIA_Board_Render.png"
		Enclosure 3D model - "V2Part 1.stl", "V2Part 2.stl"