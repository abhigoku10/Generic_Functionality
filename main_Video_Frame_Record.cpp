#include<opencv2/highgui/highgui.hpp>
#include"Headers.h"

//C
#include <stdio.h>
//C++
#include <Windows.h>
#include<strsafe.h>
#include<cwchar>
#include <windows.h>
#include <cstdio>
#include <cstdlib>



#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

///global variables 
Mat oMatImg, oMatRoiImg;
string sImgType;



int main(int argc, char **argv)
{

	////to read the images from the folder 
	if (argc < 2)
	{
		cout << "Give Input Parameters!" << endl;
		cin.get();
		return 0;
	}




	const string OutputVideo(argv[1]);
	const string sFilenumber(argv[2]);


	string OutputSavingFolder = OutputVideo + "\\" + "Vd_" + (sFilenumber.c_str());
	mkdir(OutputSavingFolder.c_str());

	string OutputVideoFile = OutputSavingFolder + "\\" + "Vd_" + (sFilenumber.c_str()) + ".avi";
	

	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR: Cannot open the video file" << endl;
		return -1;
	}


	namedWindow("RecordVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video


	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

	VideoWriter oVideoWriter(OutputVideoFile, CV_FOURCC('P', 'I', 'M', '1'), 30, frameSize, true); //initialize the VideoWriter object 

	if (!oVideoWriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video" << endl;
		return -1;
	}



	int k = 0;
	int nImgeNumber = 0;
	while (true)
	{

		cap >> oMatImg;

		if (oMatImg.empty())
		{
			cout << "The image read is empty" << endl;
			break;
		}

		if (nImgeNumber < 10)
		{
			sImgType = "Img_0000";
		}
		else if (nImgeNumber < 100)
		{
			sImgType = "Img_000";
		}

		else
		{
			sImgType = "Img_00";
		}

		std::string savingName = OutputSavingFolder + "\\" + sImgType + std::to_string(nImgeNumber) + ".jpg";

		oVideoWriter.write(oMatImg); //writer the frame into the file

		if (nImgeNumber % 2 == 0)
		{

			cout << "this is a even frame" << endl;
		}
		else
		{
			imwrite(savingName, oMatImg);
		}

		nImgeNumber++;

		imshow("RecordVideo", oMatImg); //show the frame in "MyVideo" window

		waitKey(33);

		if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}


	}
	return 0;
}