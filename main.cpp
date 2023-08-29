#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	int imgX = 640, imgY = 480;
	namedWindow("Game", 0);
	Mat img(imgY,imgX, CV_8UC3);
	Mat imgClone = img.clone();
	imgClone.copyTo(img);
	int pointX, pointY, ballRotation;
	srand(time(0));
	ballRotation = 0;
	pointX = 320;
	pointY = 240;
	int radius = 5, speed = 3;
	while(true)
	{
		putText(imgClone, "Use w a s d to move!", Point(120, 160), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 2);
		putText(imgClone, "Hold button to move quicker!", Point(120, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 2);
		putText(imgClone, "Press spacebar to start!", Point(120, 240), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 2);
		imshow("Game", imgClone);
		int button = waitKey(0);
		if(button == ' ')
		{
			img.copyTo(imgClone);
			break;
		}
		else
			continue;
	}

	int points = 0;
	int dotX = 20 + (int) (600.0 * (rand() / (RAND_MAX + 1.0))), dotY = 20 + (int) (440.0 * (rand() / (RAND_MAX + 1.0)));
	while(true)
	{
		//checking if circle hits the edge
		if((pointX - radius <= 0 || pointX + radius >= imgX) || (pointY - radius <= 0 || pointY + radius >= imgY))
		{
			img.copyTo(imgClone);
			putText(imgClone, "Game over!", Point(60, 100), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(0,255,255), 3);
			putText(imgClone, "You have " + to_string(points) + " Points", Point(60, 140), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(0,255,255), 3);
			putText(imgClone, "Press R to play again", Point(60, 180), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(0,255,255), 3);
			putText(imgClone, "Press E to exit", Point(60, 220), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(0,255,255), 3);
			imshow("Game", imgClone);
			int button = waitKey(0);
			while(true)
			{
				if(button == 'e')
					exit(0);
				if(button == 'r')
				{
					points = 0;
					pointX = 320;
					pointY = 240;
					radius = 5;
					speed = 3;
					break;
				}
				else
					button = waitKey(0);
				}
		}

		circle(imgClone, Point(dotX, dotY), 5, Scalar(0,0,255), -1);

		if((pointX + radius > dotX && pointX - radius < dotX) && (pointY + radius > dotY && pointY - radius < dotY))
		{
			dotX = 20 + (int) (600.0 * (rand() / (RAND_MAX + 1.0))), dotY = 20 + (int) (440.0 * (rand() / (RAND_MAX + 1.0)));
			radius++, speed++, points++;
		}
		//circle movement calculation
		pointX += speed*cos(ballRotation*M_PI/180);
		pointY += speed*sin(ballRotation*M_PI/180);
		circle(imgClone, Point(pointX, pointY), radius, Scalar(0,255,155), -1);
		imshow("Game", imgClone);
		char button = waitKey(100);
		//cleaning the old circle
		img.copyTo(imgClone);
		if(button == 'w')
			ballRotation = 270;
		if(button == 'a')
			ballRotation = 180;
		if(button == 's')
			ballRotation = 90;
		if(button == 'd')
			ballRotation = 0;

		putText(imgClone, to_string(points), Point(10, 50), FONT_HERSHEY_COMPLEX_SMALL, 2, Scalar(0,255,255), 3);
	}



	return 0;

}
