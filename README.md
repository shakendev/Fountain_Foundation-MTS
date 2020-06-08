# Fountain_Foundation-MTS (Fall of 2K!8)
Implementation of the Fourier decomposition algorithm, decomposing a musical composition (with a sampling frequency of 44,100 kHz) into .wav components into a score for further use in animation of the lighting part and control of the nozzles of the Aurora fountain.



# How to run the program?

## Instruction

1. The music file required for conversion must be in the same directory as the program.
2. Open the settings.conf file in any text editor and specify the name of the audio track in the "nameTrack" field (for example: nameTrack = example.wav).
3. Using the Python 3.6 interpreter, run the main.py file. For work libraries are required:
    - configparser (library for config parsing)
    - numpy (library for mathematical calculations)
    - wave (library for working with sound files in .wav format)
4. In the course of processing the sound file, the status of the program execution will be displayed in the console.
5. After successful completion of the program in the current directory, a file with the name "partitura.txt" will appear.
6. The score for the fountain is ready!


## macOS Emulator

In the macOS Emulator folder there is a fountain emulator with a music file and a pre-prepared score for quickly checking the result of decomposition of a music file using the Fourier algorithm.

```bash
On macOS version 10.13 or above - to run the emulator, you need to do the following steps:
    - Right click on the emulator and select "Show Package Contents"
    - Then follow the path: Contents -> MacOS
    - Launch a terminal application
    - Enter the following line into the terminal console: chmod +x pathToFile, where pathToFile is file in Contents -> MacOS folder
    - And now back to the folder MacOS, holding down the Control key and selecting the open menu item and confirm the opening
```

If you are using macOS Catalina (ver. 10.15), then you need to allow the opening of the fountain emulator in the "Privacy" section of the system settings.

## Windows Emulator

In the Windows Emulator folder there is a fountain emulator with a music file and a pre-prepared score for quickly checking the result of decomposition of a music file using the Fourier algorithm.

## Xcode Project

```bash
To start an Xcode project, you must specify the path to the project in the Edit Scheme menu; to do this, follow these steps:
    - In the Xcode project menu bar, select Product -> Scheme -> Edit Scheme
    - Check the Working Directory checkbox and specify the path to the folder with the Vizualization DTFT.xcodeproj file
    - Save the changes and run the project
```

