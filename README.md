# ECE4760-PIC32-Setup
A simple build environment for PIC32MX, targeted for students in ECE 4760 at Cornell University


# Introdcution
This mini-project exists for two reasons: we wanted to understand how the loading subsystem of the PIC32 worked and we were frustrated with MPLABX, as it's bulky and unnecessary. We believe that the best way to learn a new system is to understand what happens behind the scenes, so this should be a sneak peak at that.

# Requirements 
Here's what we assume you already have:
1. Understanding of the Unix command line (Linux or Mac)
1. Basic understanding of Makefiles
1. Basic understanding of Bash
1. You've succefully compiled and loaded from your computer (See below for a note on making PLIB work if that's what's giving you trouble)
1. Make installed. On Mac this requires installing XCode and then installing Command Line Tools (search the internet for this process, it's been documented a thousand times)
1. Download https://cornell.box.com/s/8aqitoj0c5vtj689i8u1i5aqp8c3wa6m and unzip in the home (`~`) directory

# PLIB Setup
If you've already gotten PLIB properly set up, skip this section

There are two issues when trying to install PLIB on Mac (we haven't verified that this works on Linux, but if you are using Linux, we trust you'll figure it out):

First, it defaults to installing into it's version directory (v1.40), while it needs to be installed into the same directory as XC32 (currently, that's v1.44). So, when running the PLIB installer, make sure to check the installation directory and make sure it's where XC32 was installed.

Second, the installer doesn't work on the lastest version of macOS. We currently don't have a fix for this (Nikita is still on OS X and didn't run into this problem, Eric on macOS did). The easiest way to get it is to have a friendly neighbor with OS X install XC32 and PLIB on their computer and copy that entire folder over to your computer (it's about 4GB, so we won't upload it here). 

# Basic Setup

There are two important files/folders in this repo: ```utils/``` and ```ipecmd.sh```. Place these wherever you like on your system, but remember the path. ```ipecmd.sh``` is a script to make loading from any directory (not just within the same directory as the loading program, see Nitty Gritty Details below if you care for an explanation) possible. ```utils/``` is a folder containing the class's TFT code, protothreads code, and in the future, other class-wide libraries. You don't need ```utils/``` if you plan to put the TFT and protothreads files within every one of your projects, we just did this to make everything cleaner. 

Open up ```ipecmd.sh``` and make sure to edit the path to the ipecmd.jar directory towards the bottom. If you installed on Mac using the default settings, this shouldn't need to change. 

## Example: ```blink_led```

We've provided the prototypical blinking LED exmaple, using our system. Edit the Makefile to reflect the proper locations of the XC32 compiler binaries and the location of the ```ipecmd.sh``` script. Run ```make``` and it should compile and load without problems.

From here, you should be able to build your own projects. You'll have to edit the Makefile for any C files you add, such as the tft files, if you don't use our utils system, described below. 

# ```utils```

Since we will be compiling basically every lab with the protothreads and TFT code, we decided to put it into it's own library. We added a file, ```tft_unity.c``` to make the Makefile cleaner. Instead of compiling each C file individually, you can just compile this one and it will compile all of them. The Makefile in the root of this repo shows an example of this compilation and how it gets linked into the .elf program

# The Nitty Gritty Details

If you are still reading this, then you are probably insane and want to know how this actually all works, so here it is (this is also just a general documentation for our reference of what we did).

## The Compilation Process

Like any C program, every C file gets compiled into an object file (.o) and then those get linked together into a binary (.elf). You can read the Makefile to see all the flags necessary for compilation. The most important flag is ```-mprocessor=32MX250F128B```. This is what actually tells the compiler which processor to compile to. As of writing, ECE 4760 uses the PIC32MX250F128B. We haven't played with the other flags to see what they do or if they are necessary, but 

One last step necessary is to convert the .elf format into the .hex format. This is what actually gets loaded onto the chip, byte by byte. 

## The Loading Process

Currently, the only way to load from the compand line is to use ipecmd.jar. This is a program packaged into MPLABX that does the actual loading. It's not super well documented and (at least on Mac) has a fun bug: the shell must be in the same directory as ipecmd.jar and it's support files to recognize the Microstick. I (Nikita) don't know Java, so the workaround is a simple bash script, ```ipecmd.sh```, that goes into the directory and calls ipecmd.jar and forwards the parameters passed into the script. You can read the script to figure out exactly what it does. 

There are four main parameters that need to be passed to the loader: ```-TPPKOB```, which tells the loader to search for a Microstick and use that as the programming tool; ```-P32MX250128B```, which tells the loader what the target processor is and should be the same as what was specfied for compilation above, ```-OL``` which tells the loader to not hold the chip in reset (more on this later); and ```-M``` which tells the loader to program the entire memory of the PIC32.

### ```-OL``` Flag

When the loader is done, it doesn't release the chip from reset for some reason, so the Microstick needs to be power cycled. Haven't found a fix, but a workaround the ```-OL``` flag. This tells the loader to not hold the chip in reset. This successfully releases the chip from reset, but will also toggle it during the loading process, so you'll see the TFT constantly flash. This is not ideal, but it's okay for now. 

There's a lot going on here and this document probably doesn't detail it as well as some might hope. Reach out if you're completely stuck, we'll do our best to reply. Cheers. 

-Nikita Ermoshkin (ne75)
-Eric Dai (emd88)

----

All code in the utils folder (except ```tft_unity.c```) was provided by Bruce Land for ECE 4760 and belongs to its respective author. All other code belongs to Nikita Ermoshkin and Eric Dai, and is free for anyone to use (just tell the world we saved you a headache, buy us a beer at CTB or something).
