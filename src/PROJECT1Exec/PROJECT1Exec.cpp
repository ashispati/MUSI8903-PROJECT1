
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

    long long               iInFileLength       = 0;        //!< length of input file

	float                   **inputAudioData	= 0,
							**outputAudioData	= 0;

    CAudioFileIf            *phAudioFile        = 0;

	int						type				= 0;

	float					delayLength			= 0.0,
							gain				= 0.0;

	CMyProject				*filter				= 0;
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
		delayLength = atof(argv[3]);
		break;
	case 5: sInputFilePath = argv[1];
		type = atoi(argv[2]);
		delayLength = atof(argv[3]);
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
    
    CAudioFileIf::FileSpec_t spec;
    phAudioFile->getFileSpec(spec);

    phAudioFile->getLength(iInFileLength);

    inputAudioData = new float*[spec.iNumChannels];
	outputAudioData = new float*[spec.iNumChannels];
    
    for(int i = 0; i < spec.iNumChannels; i++)
    {
        inputAudioData[i] = new float[iInFileLength];
		outputAudioData[i] = new float[iInFileLength];
    }
    
    long long int numFrames = iInFileLength;
    phAudioFile->readData(inputAudioData, numFrames);
    
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing
    //cout << "Hello there!" << endl << endl;
	CMyProject::create(filter, type);
	filter->setDelayLineInSecs(delayLength);
	filter->setGain(gain);
	filter->processFilter(inputAudioData, outputAudioData, spec, iInFileLength);
	
    
    cout << "Exited" << endl;
    // write data to files
    std::ofstream outfile,infile;
    outfile.open(sOutputFilePath);
    infile.open(sInput2TxtPath);
	for (int i = 0; i < spec.iNumChannels; i++)
	{
		for (int j = 0; j < iInFileLength; j++)
		{
			outfile << outputAudioData[i][j] << " ";
			infile << inputAudioData[i][j] << " ";
		}
		outfile << endl;
		infile << endl;
	}
    //////////////////////////////////////////////////////////////////////////////
    // clean-up
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

