In this task, we will extend our previous `writeNumber` program to add support for displaying negative integers on a set of seven-segment displays.

![7sd](assets/writeNegative.png)

The DAQ module with configuration `4` has two toggle-switches and 8 seven-segment displays:

- `SWITCH0` - digital input channel 0
- `SWITCH1` - digital input channel 1
- `DISPLAY0` - display output position 0
- ...
- `DISPLAY7` - display output position 7

The seven-segment displays are arranged in reverse order, so that `DISPLAY0` is the furthest to the right.  Each seven-segment display is driven by an integer which lights up particular segments according to:

![7sd](assets/seven_segment_display.png)

A main program is provided for you that reads an integer in the range [-9999999, 99999999] from standard input, and calls a new function

- `void writeNumber(int val)`: writes a number to the seven-segment displays
 
It is your job to implement this new function.  Note the range of valid inputs: your function must support both positive and negative integers, and there will be at most 8 characters to display, including the sign.

You are provided with the following:

- `void displayWrite(int val, int position)`: writes a binary-encoded value to the given display position to turn on/off the corresponding LED segments

---

## Evaluation

You should be able to test your program using the usual DAQ simulator.  

Your code will be evaluated using a modified command-line simulator (see the attached `DAQlibTerminal.c` file).  The program is set to read and write values using standard I/O.

**NOTE:** the command-line simulator and provided code will handle all of the inputs/outputs for you.  Do not include your own `printf`/`scanf` statements apart from the ones in the template.

## Input Format

If using the command-line simulator, each iteration of the super loop corresponds to two lines in the input.  The first line contains the values of the two digital input switches, which are to be ignored.  The second is the number to be written to the displays.

## Ouput Format

In the command-line simulator, 
- the first line indicates the setup number used to initialize the DAQ
- each subsequent group of 4 lines depicts the values of the seven-segment displays
at the end of the corresponding super loop iteration

---

## Sample

### Input
```default
0 0
-32176
0 0
42
0 0
-96
```

### Output

```default
4
                                 
                                 
                                 
 ___ ___ ___ ___ ___ ___ ___ ___ 
              _   _       _   _  
          _   _|  _|   |   | |_  
              _| |_    |   | |_| 
 ___ ___ ___ ___ ___ ___ ___ ___ 
                              _  
                         |_|  _| 
                           | |_  
 ___ ___ ___ ___ ___ ___ ___ ___ 
                          _   _  
                      _  |_| |_  
                          _| |_| 
 ___ ___ ___ ___ ___ ___ ___ ___ 
```

### Explanation

- The DAQ is initialized with setup number 4, and the displays are all initially blank `___` on the first call to `continueSuperLoop()`
- The first line of input (and every second line thereafter) corresponds to the values of the input switches, which are ignored
- The second input line `-32176` tells us to display that negative number on the set of 7-segment displays
- The fourth input line `42` tells us to display the number 42
- etc...