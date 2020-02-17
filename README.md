# Fountain_Foundation-MTS (Fall of 2K!8)
Implementation of the Fourier decomposition algorithm, decomposing a musical composition (with a sampling frequency of 44100 kHz) into .wav components into a score for further use in animation of the lighting part and control of the nozzles of the Aurora fountain.



## How to run the program?

1. The music file required for conversion must be in the same directory as the program.
2. Open the settings.conf file in any text editor and specify the name of the audio track in the "nameTrack" field (for example: nameTrack = example.wav).
3. Using the Python 3.6 interpreter, run the main.py file. For work libraries are required:
    - configparser (library for config parsing)
    - numpy (library for mathematical calculations)
    - wave (library for working with sound files in .wav format)
4. In the course of processing the sound file, the status of the program execution will be displayed in the console.
5. After successful completion of the program in the current directory, a file with the name "partitura.txt" will appear.
6. The score for the fountain is ready!
