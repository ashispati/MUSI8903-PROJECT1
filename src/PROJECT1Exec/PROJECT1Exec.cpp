
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cmath>

#include "PROJECT1Config.h"

#include "AudioFileIf.h"
#include "MyProject.h"

#define PI 3.14159265359

//using std::cout;
//using std::endl;
using namespace std;

// local function declarations
void    showClInfo ();
void	Test1();
void	Test2();
void	Test3();
void	Test4();


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
	Error_t					error_check;
    std::ofstream           outfile,infile;
	showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
	// It's not really possible to check if the user actually input the correct data.
	// atoi and atof will automatically return 0 if the string isn't a valid type.
	// Use stoi and stof
	
	try
	{
		switch (argc)
		{
		case 1: cout << "Too few arguments. Enter Filename." << endl;
			exit(0);
			break;
		case 2: sInputFilePath = argv[1];
			break;
		case 3: sInputFilePath = argv[1];
			type = stoi(argv[2]);
			break;
		case 4: sInputFilePath = argv[1];
			type = stoi(argv[2]);
			delayTimeInSec = stof(argv[3]);
			break;
		case 5: sInputFilePath = argv[1];
			type = stoi(argv[2]);
			delayTimeInSec = stof(argv[3]);
			gain = stof(argv[4]);
			break;
		default: cout << "Too many parameters. Check what you're entering." << endl;
			exit(0);
		}
	}
	catch (exception &exc)
	{
		cerr << "Invalid arguments passed. Please use the correct formatting for running the program." << endl;
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
	
	error_check = CMyProject::create(filter, type, delayTimeInSec, gain, spec.fSampleRateInHz, spec.iNumChannels);
	if (error_check == kFunctionIllegalCallError)
		cout << "Illegal filter type, use 0 for FIR and 1 for IIR"<<endl;
	else if (error_check == kFunctionInvalidArgsError)
		cout << "Invalid filter parameters used. Delay should be positive and Gain should be between -1 and +1."<<endl;
    
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = blockSize;
        phAudioFile->readData(inputAudioData, iNumFrames);
        filter->process(inputAudioData, outputAudioData, iNumFrames);
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int j = 0; j < spec.iNumChannels; j++)
            {
                outfile << outputAudioData[j][i] << " ";
                infile << inputAudioData[j][i] << " ";
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

	Test1();
	Test2();
	Test4();

    cout << "Done Processing" << endl;
	system("pause");
    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI-8903" << endl;
    cout << "(c) 2016 by Sid and Ashis" << endl;
    cout  << endl;

    return;
}

void genSineWave(float *wave, float amplitude,float frequency, float timeInSecs, float fs)
{
	for (int i = 0; i < timeInSecs*fs; i++)
	{
		wave[i] = amplitude*sin(2 * PI*i*frequency/fs);
	}
	return;
}

void Test1()
{
	CMyProject	*filter = 0;
	float **sinewave, **output;
	int flag = 1;
	std::ofstream           outfile, infile;
	string sOutputFilePath = "C:/Users/SiddGururani/Desktop/output.txt";
	string sInput2TxtPath = "C:/Users/SiddGururani/Desktop/input.txt";
	outfile.open(sOutputFilePath);
	infile.open(sInput2TxtPath);

	//Generating a single channel sine wave of amplitude 1, frequency 441Hz and sampling frequency 44100Hz
	sinewave = new float*[1];
	sinewave[0] = new float[44100];
	genSineWave(sinewave[0], 1, 441.0, 1, 44100.0);

	//Allocating memory for output signal
	output = new float*[1];
	output[0] = new float[44100];
	//Filtering sine wave with delay of one period and gain of -1.
	CMyProject::create(filter, 0, 1/441.0, -1, 44100, 1);
	filter->process(sinewave, output, 44100);
	for (int i = 0;i < 44100;i++)
	{
		outfile << output[0][i] << endl;
		infile << sinewave[0][i] << endl;
	}

	for (int i = 101;i < 44100; i++)
	{
		if (output[0][i] > 0.00005) //Tolerance for 0 value is set to 0.00005
		{
			//cout << sinewave[0][i] << "\t" << output[0][i] << endl;
			flag = 0;
		}
	}
	if (flag == 0)
		cout << "Test 1 Failed" << endl;
	else
		cout << "Test 1 Passed" << endl;
	delete[] sinewave[0];
	delete[] output[0];
	delete[] sinewave;
	delete[] output;
	CMyProject::destroy(filter);

	outfile.close();
	infile.close();
	return;
}

void Test2()
{
	CMyProject	*filter = 0;
	float **sinewave, **output;
	float energy_input = 0, energy_output = 0, ratio;
	int flag1 = 1, flag2 = 1;

	//Generating a single channel sine wave of amplitude 1, frequency 441Hz and sampling frequency 44100Hz
	sinewave = new float*[1];
	sinewave[0] = new float[44100];
	genSineWave(sinewave[0], 1, 441.0, 1, 44100.0);

	//Allocating memory for output signal
	output = new float*[1];
	output[0] = new float[44100];

	//Filtering sine wave with delay of one period and gain of -1.
	CMyProject::create(filter, 1, 1 / 441.0, 0.5, 44100, 1);
	filter->process(sinewave, output, 44100);

	//Computing ratio of output and input signal at the 1025th sample (output is stable and magnitude should increase by factor of 2)
	ratio = output[0][1025] / sinewave[0][1025];
	if (ratio < 1.995 || ratio > 2.005)
		flag1 = 0;
	for (int i = 1001; i < 44100; i++)
	{
		energy_input += sinewave[0][i] * sinewave[0][i];
		energy_output += output[0][i] * output[0][i];
	}
	ratio = energy_output / energy_input;
	if (ratio < 3.995 || ratio > 4.005)
	{
		flag2 = 0;
	}
	if (flag1 == 1 && flag2 == 1)
		cout << "Test 2 Passed"<<endl;
	else
		cout << "Test 2 Failed"<<endl;
	
	delete[] sinewave[0];
	delete[] output[0];
	delete[] sinewave;
	delete[] output;
	CMyProject::destroy(filter);
	return;
}

void Test3()
{
	CMyProject	*filter = 0;
	int blocksize[] = {256, 512, 1024, 2048, 4096};
	float **input, **output_new, **output_old;
	input = new float*[1];
	output_old = new float*[1];
	output_new = new float*[1];
	input[0] = new float[8096];
	output_old[0] = new float[8096];
	output_new[0] = new float[8096];

	genSineWave(input[0], 1, 441.0, 44100/4096, 44100.0);
	for (int i = 0; i < 5; i++)
	{
		CMyProject::create(filter, 1, 1 / 441.0, 0.5, 44100, 1);
		int num_blocks = 8096 / blocksize[0];
		for (int j = 0; j < num_blocks; j++)
		{

		}
	}
}

void Test4()
{
	CMyProject	*filter = 0;
	float **input, **output_FIR, **output_IIR;
	int flag = 1;

	//Allocating memory for the input and output signals
	input = new float*[1];
	output_FIR = new float*[1];
	output_IIR = new float*[1];
	input[0] = new float[1024];
	output_FIR[0] = new float[1024];
	output_IIR[0] = new float[1024];

	for (int i = 0;i < 1024;i++)
		input[0][i] = 0;
	CMyProject::create(filter, 0, 1, 1, 44100, 1);
	filter->process(input, output_FIR, 1024);
	filter->reset();
	CMyProject::create(filter, 1, 1, 1, 44100, 1);
	filter->process(input, output_IIR, 1024);
	
	for (int i = 0; i < 1024; i++)
	{
		if (output_FIR[0][i] != 0 || output_IIR[0][i] != 0)
			flag = 0;
	}
	if (flag == 0)
		cout << "Test 4 Failed" << endl;
	else
		cout << "Test 4 Passed" << endl;
	delete[] input[0];
	delete[] output_FIR[0];
	delete[] output_IIR[0];
	delete[] input;
	delete[] output_FIR;
	delete[] output_IIR;
	CMyProject::destroy(filter);
	return;
}