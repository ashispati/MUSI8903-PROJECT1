
#include <iostream>
#include <ctime>

#include "MUSI8903Config.h"

#include "AudioFileIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    float                   **ppfAudioData      = 0;

    CAudioFileIf            *phAudioFile        = 0;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    sInputFilePath =  "/Users/apple/Desktop/ABBA.wav";  //argv[0];
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::FileIoType_t::kFileRead);
    sOutputFilePath = sInputFilePath + ".txt";
    
    
    CAudioFileIf::FileSpec_t spec;
    phAudioFile->getFileSpec(spec);
    long long int fileLength;
    phAudioFile->getLength(fileLength);
    
    ppfAudioData = new float*[spec.iNumChannels];
    
    for(int i = 0; i < spec.iNumChannels; i++)
    {
        ppfAudioData[i] = new float[fileLength/spec.iNumChannels];
    }
    
    long long int numFrames = fileLength/spec.iNumChannels;
    phAudioFile->readData(ppfAudioData, numFrames);
    
    
    cout << numFrames << endl;
    cout << spec.fSampleRateInHz << endl;
    
    
    
    

    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "Hello there!" << endl << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up

    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI8903" << endl;
    cout << "(c) 2016 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

