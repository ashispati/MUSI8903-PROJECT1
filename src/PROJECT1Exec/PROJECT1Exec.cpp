
#include <iostream>
#include <ctime>
#include <fstream>

#include "PROJECT1Config.h"

#include "AudioFileIf.h"
#include "MyProject.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath,
							sInput2TxtPath;

    static const int        blockSize           = 1024;

	float                   **inputAudioData	= 0,
							**outputAudioData	= 0;

    CAudioFileIf            *phAudioFile        = 0;

	int						type				= 0;

	float					delayTimeInSec			= 0.0,
							gain				= 0.0;

	CMyProject				*filter				= 0;
    std::ofstream           outfile,infile;
	showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
	
	switch (argc)
	{
	case 1: cout << "Too few arguments. Enter Filename." << endl;
		exit(0);
		break;
	case 2: sInputFilePath = argv[1];
		break;
	case 3: sInputFilePath = argv[1];
		type = atoi(argv[2]);
		break;
	case 4: sInputFilePath = argv[1];
		type = atoi(argv[2]);
		delayTimeInSec = atof(argv[3]);
		break;
	case 5: sInputFilePath = argv[1];
		type = atoi(argv[2]);
		delayTimeInSec = atof(argv[3]);
		gain = atof(argv[4]);
		break;
	default: cout << "Too many parameters. Check what you're entering." << endl;
		exit(0);
	}
	
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::FileIoType_t::kFileRead);
    sOutputFilePath = sInputFilePath + "output.txt";
	sInput2TxtPath = sInputFilePath + "input.txt";
    outfile.open(sOutputFilePath);
    infile.open(sInput2TxtPath);
    
    CAudioFileIf::FileSpec_t spec;
    phAudioFile->getFileSpec(spec);

    inputAudioData = new float*[spec.iNumChannels];
	outputAudioData = new float*[spec.iNumChannels];
    
    for(int i = 0; i < spec.iNumChannels; i++)
    {
        inputAudioData[i] = new float[blockSize];
		outputAudioData[i] = new float[blockSize];
    }
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing
	CMyProject::create(filter, type, delayTimeInSec, gain, spec.fSampleRateInHz, spec.iNumChannels);
    
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = blockSize;
        phAudioFile->readData(inputAudioData, iNumFrames);
        filter->process(inputAudioData, outputAudioData, iNumFrames);
        for (int i = 0; i < spec.iNumChannels; i++)
        {
            for (int j = 0; j < iNumFrames; j++)
            {
                outfile << outputAudioData[i][j] << " ";
                infile << inputAudioData[i][j] << " ";
            }
            outfile << endl;
            infile << endl;
        }
        
    }
    
    cout << "Exited" << endl;
    
    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    outfile.close();
    infile.close();
    
    for (int i = 0; i < spec.iNumChannels; i++)
	{
		delete[] inputAudioData[i];
		delete[] outputAudioData[i];
	}
	delete[] inputAudioData;
	delete[] outputAudioData;

	CAudioFileIf::destroy(phAudioFile);
	CMyProject::destroy(filter);

    cout << "Done Processing" << endl;
    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI-8903" << endl;
    cout << "(c) 2016 by Sid and Ashis" << endl;
    cout  << endl;

    return;
}

