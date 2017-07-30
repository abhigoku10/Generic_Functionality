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
int k = 0, ii = 0;


string sImgType;


int main(int argc, char **argv)
{

	////to pas the min 2 arguments  
	if (argc < 2)
	{
		cout << "Give Input Parameters!" << endl;
		cin.get();
		return 0;
	}




	string InputVideo(argv[1]);
	string OutputFolder(argv[2]);



	vector<string> v_strFileNames;
	string strDataSetName = InputVideo.substr(InputVideo.find_last_of("\\/") + 1);
	cout << strDataSetName << " In Process......" << endl;
	FileIO::GetImageFilesInFolder(InputVideo, v_strFileNames);

	if (v_strFileNames.empty())
	{
		cout << " The video file is not read" << endl;
	}


	while (v_strFileNames.size())
	{

		string strDataSetName = v_strFileNames[k].substr(v_strFileNames[k].find_last_of("\\/") + 1);
		string strFoldername = strDataSetName.erase(strDataSetName.find_last_of("."));

		string outputpath = OutputFolder + "\\" + strFoldername;
		mkdir(outputpath.c_str());

		VideoCapture cap(v_strFileNames[k]); // open the video camera no. 0

		if (!cap.isOpened())  // if not success, exit program
		{
			cout << "ERROR: Cannot open the video file" << endl;
			return -1;
		}


		/// to pass the original size of the video 

		double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
		double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

		Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));


		int nImgeNumber = 0;
		while (true)
		{

			cap >> oMatImg;
			if (oMatImg.empty())
			{
				break;
			}

			if (nImgeNumber < 10)
			{
				sImgType = strFoldername + "_Img_0000";
			}
			else if (nImgeNumber < 100)
			{
				sImgType = strFoldername + "_Img_000";
			}

			else
			{
				sImgType = strFoldername + "_Img_00";
			}


			std::string savingName = outputpath + "\\" + sImgType + std::to_string(nImgeNumber) + ".jpg";
			if (nImgeNumber % 2 == 0)
			{

				cout << "this is a even frame" << endl;
			}
			else
			{
				imwrite(savingName, oMatImg);
			}


			nImgeNumber++;

			imshow("Video", oMatImg); //show the frame in "MyVideo" window

			if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			{
				cout << "esc key is pressed by user" << endl;
				break;
			}
		}
		k++;
		if (k >= v_strFileNames.size())
		{
			return 0;
		}

	}
	return 0;
}