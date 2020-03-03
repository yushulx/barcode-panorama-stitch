#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "BarcodeReaderConfig.h"
#include "DynamsoftPanorama.h"

#if defined(LINUX) || defined(MACOS)
#include <sys/time.h>
#endif

using namespace cv;
using namespace std;
using std::cout; 
using std::cerr; 
using std::endl;

#define INTERVAL 35

typedef struct {
	volatile int count;
} Status;

// https://answers.opencv.org/question/44263/delay-syntax-in-opencv-wait/
#if defined(WINDOWS)

  #include <windows.h>

  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }

#else  /* presume POSIX */

  #include <unistd.h>

  inline void delay( unsigned long ms )
    {
    usleep( ms * 1000 );
    }

#endif

bool SaveBitmap(int iwidth, int iHeight, int iBitcount, unsigned char *pData, int nDatasize, string savePath)
{
	const int height = iHeight;
	const int width = iwidth;
	const int size = nDatasize;
	const int bitCount = iBitcount;

	BITMAPFILEHEADER fileHeader;

	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+size;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	BITMAPINFOHEADER bitmapHeader = { 0 };

	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biHeight = -height;
	bitmapHeader.biWidth = width;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = bitCount;
	bitmapHeader.biSizeImage = size;
	bitmapHeader.biCompression = 0; //BI_RGB

	FILE *output = fopen(savePath.c_str(), "wb");

	if (output == NULL)
	{
		printf("Error when saving file!\n");
		return false;
	}
	else
	{
		fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, output);
		fwrite(&bitmapHeader, sizeof(BITMAPINFOHEADER), 1, output);
		fwrite(pData, size, 1, output);
		fclose(output);
		return true;
	}
}

void GetPanoramaResult(PanoramaResultArray** resultArray, void* pUser)
{
	// if ((*resultArray)->panoramaResult[0]->indexOfFirstFrameInResultImg != 0)
	// {
	// 	((Status *)pUser)->count = 1;
	// }
	CPanoramaStitcher::FreePanoramaResults(resultArray);
}

void GetErrorCode(int errorCode, void* pUser)
{

}

bool SaveDMBitmapToLocal(DMBitmap* bitmap, string savePath)
{
	return SaveBitmap(bitmap->iWidth, bitmap->iHeight, bitmap->iBitCount,
		bitmap->pImageData, bitmap->iImageSize, savePath);

}

int panoramaMode(CPanoramaStitcher* panoramaStitcher, VideoCapture &capture, bool isVideoMode, int interval)
{
	Mat frame;
	int ret = 0;
	{
		capture >> frame;
		int width = capture.get(CAP_PROP_FRAME_WIDTH);
		int height = capture.get(CAP_PROP_FRAME_HEIGHT);
		int format = capture.get(CAP_PROP_FORMAT);
		int t = frame.type();
		int depth = frame.depth();
		int chnnel = frame.channels();

		Status status = {0};
		void* pUser = &status;
		panoramaStitcher->SetResultCallback(&GetPanoramaResult, pUser);
		panoramaStitcher->SetErrorCodeCallback(&GetErrorCode, pUser);

		panoramaStitcher->StartPanoramaStitchingByBuffer(width, height, width * chnnel, DPS_IPF_RGB_888);
		printf("Scanning frames...\n");

		const String windowName = "Barcode Scanner";
		int inputCount = 0;
		unsigned __int64 begin = GetTickCount(), end = GetTickCount();

		for (;;)
		{
			capture >> frame; 
			++inputCount;

			int key = waitKey(1);
			if (key == 27/*ESC*/ || status.count == 1 || frame.empty()) {
				destroyWindow(windowName);
				break;
			}

			imshow(windowName, frame);
			ret = panoramaStitcher->AppendNewFrameByBuffer(frame.data);
			
			if (ret)
			{
				cout << "Failed to append new frame" << endl;
				destroyWindow(windowName);
				break;
			}

			if (isVideoMode)
				delay(interval);
		}

		printf("Total input frames: %d\n", inputCount);
		printf("Waiting for stitching...\n");
		panoramaStitcher->WaitForFinishStitching();
		printf("Stop stitching...\n");
		panoramaStitcher->StopPanoramaStitching();
		PanoramaResultArray* finalResult = NULL;
		panoramaStitcher->GetFinalResults(&finalResult);

		if (finalResult->resultCount > 0)
		{
			printf("Total panorama results: %d\n", finalResult->resultCount);

			for (int j = 0; j < finalResult->resultCount; ++j)
			{
				int thickness = 2;
				Scalar color(0, 255, 0);

				String fileName = to_string(j) + ".bmp";

				if(SaveDMBitmapToLocal(finalResult->panoramaResult[j]->resultImg, fileName))
				{
					printf("The panorama result is saved. Total stiched image number: %d\n", finalResult->panoramaResult[j]->stitchedImgsNumber);
					
					Mat img = imread(fileName);

					printf("Total barcodes: %d\n", finalResult->panoramaResult[j]->barcodeNumber);
					for (int i = 0; i < finalResult->panoramaResult[j]->barcodeNumber; ++i)
					{
						BarcodeInfo *barcode = finalResult->panoramaResult[j]->barcodes[i];
						const char *text = barcode->barcodeText;
						const char *format = barcode->barcodeFormatString;
						int x1 = barcode->x1;
						int y1 = barcode->y1;
						int x2 = barcode->x2;
						int y2 = barcode->y2;
						int x3 = barcode->x3;
						int y3 = barcode->y3;
						int x4 = barcode->x4;
						int y4 = barcode->y4;
						printf("Format: %s, text: %s\n", format, text);
						line( img, Point(x1, y1), Point(x2, y2), color, thickness);
						line( img, Point(x2, y2), Point(x3, y3), color, thickness);
						line( img, Point(x3, y3), Point(x4, y4), color, thickness);
						line( img, Point(x4, y4), Point(x1, y1), color, thickness);
					}
					imwrite(to_string(j) + ".png", img);
					imshow(to_string(j), img);
				}
			}
			waitKey(0);
		}

		CPanoramaStitcher::FreePanoramaResults(&finalResult);
	}

	return 0;
}

int cameraMode(CPanoramaStitcher* panoramaStitcher)
{
	cout << "Opening camera..." << endl;

	VideoCapture capture(0 + cv::CAP_DSHOW); 
	if (!capture.isOpened())
	{
		cerr << "ERROR: Can't initialize camera capture" << endl;
		return 1;
	}

	return panoramaMode(panoramaStitcher, capture, false, 0);
}

int videoMode(String video, int interval, CPanoramaStitcher* panoramaStitcher) 
{
	Mat frame;
	cout << "Playing video..." << endl;

	VideoCapture capture(video); 
	if (!capture.isOpened())
	{
		cerr << "ERROR: Can't initialize camera capture" << endl;
		return 1;
	}

	return panoramaMode(panoramaStitcher, capture, true, interval);
}

int main(int argc, char *argv[])
{
	CPanoramaStitcher* panoramaStitcher = new CPanoramaStitcher;
	// Get trial license from https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx
	int ret = panoramaStitcher->InitLicense("LICENSE-KEY);
	if (ret)
	{
		cout << "Invalid license!" << endl;
		return 0;
	}
	
	char error[512];

	if (argc <= 1)
	{
		ret = panoramaStitcher->InitRuntimeSettingsWithString("{\"InputSourceMode\":0, \"PreviewImgScaleRatio\": 0.5}", error, 512);
		if (ret)
		{
			printf("Invalid settings. Error code: %d \n", ret);
		}
		else
		{
			cameraMode(panoramaStitcher);
		}
		
	}
	else
	{
		int interval = 0;
		if (argc >= 3)
		{
			try
			{
				interval = stoi(argv[2]);
			}
			catch(invalid_argument const &e)
			{
				cerr << e.what() << endl;
				cout << "Bad input. Please set a integer number for interval." << endl;
			}
		}
		
		ret = panoramaStitcher->InitRuntimeSettingsWithString("{\"InputSourceMode\":1, \"PreviewImgScaleRatio\": 0.5}", error, 512);
		if (ret)
		{
			printf("Invalid settings. Error code: %d \n", ret);
		}
		else
		{
			videoMode(argv[1], interval > 0 ? interval : INTERVAL, panoramaStitcher);
		}
		
	}

	if (panoramaStitcher) delete panoramaStitcher;

	return 0;
}