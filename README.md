# MUSIC-8903-2016: Assignment 1 
Comb Filter Library

This repository contains the Filter library implemented for the MUSI8903 Audio Software engineering assignment and a demo program that uses the interface to apply the comb filter on an audio file and runs test cases as specified in the assignment problem statement.
The readme file contains information for the usage of the program and the design decisions taken by the developers of this library.

The repository contains a folder which has Matlab plots which verify the functionality of the filters by comparing Matlab's result with the result generated by the library's functions.

#Usage Instructions:

The file PROJECT1Exec.cpp is the code for a command line program that takes as input the audio file, the filter type, delay time and gain. 

The command line application has to be run as follow:

   \<project1exec binary> \<file path> \<filter_type> \<filter_delay in seconds> \<filter_gain>
    
 - \<filter_type>: Takes 0 for FIR, 1 for IIR.

- \<filter_delay in seconds>: Has to be non-negative.

- \<filter_gain>: Magnitude has to be < 1 for IIR.

The program outputs 2 text files, containing the input signal and output filtered signal data so that they may be compared in Matlab as well as to check the implementation against the Matlab code.

The program then proceeds to run the test functions as mentioned in the assignment. An extra test case has been checked for when the delay length is longer than the input signal, in which case the output should be the same as the input.

# Interface Design Decisions:

The thought behind having a filter superclass and 2 subclasses deriving from this class comes from the OOP way of thinking. A Filter is one class of real world objects and the IIR and FIR Comb filters are sub types of Filters, which translate to separate derived classes.

Why we used abstract filter class and subclasses for the 2 comb filters? Because for real projects, you want to be able to add code files without changing previous code, which is enabled by using such an interface.
Which enables us to easily add more filter implementations at a later stage.

Data members are currently protected because we wanted to give direct access for the derived classes. However, there are also getter and setter functions which could have been used but that way would have been more tedious.

The adjustable parameters within this interface are the filter's gain and delay. Also, the filter type may be chosen by the user.

The parameters which the user can get using this interface are:
 - Filter delay in samples
 - Filter gain

The user can set the filter type and parameters while instantiating an object via the create() method. The interface currently doesn't support on-the-fly parameter changing, which could have been possible had we implemented a fixed maximum delay buffer.
Currently there is no upper bound on the size of the delay buffer which could be problematic for large delays.

The user may however, reset the old filter using the reset() method and reinitialize the same filter with new parameters using the init() function.

The interface should work with all sample rates and channel configurations.

User can access both filter types from the same class interface by simply specifying which type of filter he/she wants while calling the create() function. The constructor automatically instantiates the filter of the correct type. This functionality was another reason behind choosing to have the interface class and then implementing it in subclasses, instead of having functions for the 2 filter types.

The process function is not inplace.
