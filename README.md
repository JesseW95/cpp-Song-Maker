# coms327p2

C++ Version of project 1 using OOP.

## Features
  - Run main_a.exe
  -	- Enter the request inputs
  -	- File is output in source directory with file name containing the output of the wave.
  - Run main_b.exe
  -	- Enter song notes and respective wave, reverb, and adsr data
  - - Alternatively, run in command line with a file name, entering each input on a new line:
  - - - piano note, wave(1-4), reverb delay, reverb attenuation, attack time, attack leve, decay time, sustain level, release time
  -	- File is output in source directory with file name containing the output of the notes + 0.25s of silence between each.
### MakeFile
 - open cmd at directory and typing 'make' will create 2 executables
    - main_a and main_b
 - typing 'make clean' will clean the directory of .o files, executables, and any .txt files.
 
## [Developer](DEVELOPER.md)