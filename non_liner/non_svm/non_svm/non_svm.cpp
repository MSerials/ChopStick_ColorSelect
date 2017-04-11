// non_svm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

#pragma warning(disable:2228)

#ifdef _DEBUG
#pragma comment(lib,"opencv_world320d.lib")
#else
#pragma comment(lib,"opencv_world320.lib")
#endif

#define	NTRAINING_SAMPLES	100			// Number of training samples per class
#define FRAC_LINEAR_SEP		0.9f	    // Fraction of samples which compose the linear separable part

using namespace cv;
using namespace cv::ml;
using namespace std;

static void help()
{
	cout << "\n--------------------------------------------------------------------------" << endl
		<< "This program shows Support Vector Machines for Non-Linearly Separable Data. " << endl
		<< "Usage:" << endl
		<< "./non_linear_svms" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< endl;
}

cv::Mat traindata = cv::Mat();
cv::Mat labels;


float average_data(const cv::Mat &src)
{
	double size = static_cast<double>(src.cols*src.rows);
	size_t step = src.step;
	double average = 0;
	for (size_t h = 0; h<src.rows; ++h)
		for (size_t w = 0; w < src.cols; ++w)
		{
			double d = static_cast<double>(src.data[h*step + w]);
			average += d / size;
		}
	return static_cast<float>(average);
}

void exsplit(const cv::Mat src, std::vector<cv::Mat>& mv)
{

	size_t chs = src.channels();
	int type = src.type();
	for (int i = 0;; ++i)
	{
		int itype = src.type() - 8 * i;
		if (itype < 0) break;
		type = itype;
	}

	for (size_t i = 0; i < chs; ++i)
	{
		mv.push_back(cv::Mat(src.size(), type));
	}
	size_t ostep = src.step;
	size_t step = mv[0].step;
	//bug
	for (size_t h = 0; h<src.rows; ++h)
		for (size_t w = 0; w < src.cols; ++w)
		{
			for (size_t ch = 0; ch < chs; ++ch)
			{
				mv[ch].data[h*step + w] = src.data[h*ostep + chs*w + ch];
			}
		}
}

cv::Mat getHSVData(cv::Mat & src)
{
	cv::Mat rect_img, rect_hsv, color;
	if (CV_8UC3 != src.type()) cvtColor(src, rect_img,COLOR_GRAY2BGR);
	std::vector <cv::Mat> mv;
	cvtColor(src, rect_hsv, COLOR_BGR2HSV_FULL);
	exsplit(rect_hsv, mv);
	cv::Mat avg(1,3,CV_32FC1);
	avg.at<float>(0, 0) = average_data(mv[0]);
	avg.at<float>(0, 1) = average_data(mv[1]);
	avg.at<float>(0, 2) = average_data(mv[2]);
	return avg;
}

void readimg()
{
	//20 samples and 3 datas
	traindata = cv::Mat(20, 3, CV_32FC1);
	labels = cv::Mat(20, 1, CV_32SC1);  //having

	int index = 0;
	for (int i = 0; i < 10; i++)
	{
		char path[256] = { 0 };
		sprintf_s(path,"COLOROK/%d.png",i+1);
		cv::Mat src = cv::imread(path, -1); 
		namedWindow(path);
		if(!src.empty())imshow(path, src);

		cv::Mat data = getHSVData(src);
		traindata.at<float>(index, 0) = data.at<float>(0, 0);
		traindata.at<float>(index, 1) = data.at<float>(0, 1);
		traindata.at<float>(index, 2) = data.at<float>(0, 2);

		labels.at<float>(index, 0) = -1.0;
		index++;
	}

	for (int i = 0; i < 10; i++)
	{
		char path[256] = { 0 };
		sprintf_s(path, "COLORNG/%d.png", i + 1);
		cv::Mat src = cv::imread(path, -1);
		namedWindow(path);
		if (!src.empty())imshow(path, src);

		cv::Mat data = getHSVData(src);
		traindata.at<float>(index, 0) = data.at<float>(0, 0);
		traindata.at<float>(index, 1) = data.at<float>(0, 1);
		traindata.at<float>(index, 2) = data.at<float>(0, 2);

		labels.at<float>(index, 0) = 1.0;
		index++;
	}
}



int main()
{
//	help();
	readimg();

//	waitKey(0);
//	return 0;
	std::cout << "Starting training process" << std::endl;
	//! [init]
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setC(0.1);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, (int)1e7, 1e-6));
	//! [init]
	//! [train]
	svm->train(traindata, ROW_SAMPLE, labels);
	//! [train]
	std::cout << "Finished training process" << std::endl;

	cv::Mat src = cv::imread("COLORNG/1.png", -1);

	for(int index = 0;index<20;index++)
	{ 
	cv::Mat data(1, 3, CV_32FC1); //= getHSVData(src);
	data.at<float>(0, 0) = traindata.at<float>(index, 0);
	data.at<float>(0, 1) = traindata.at<float>(index, 1);
	data.at<float>(0, 2) = traindata.at<float>(index, 2);

	float response = svm->predict(data);
	
	if (response < 0) cout << "颜色正确,预测值为:" << response << endl;
	else cout << "颜色不合格预测值为:" << response << endl;
	}
	cv::waitKey(0);
	return 0;
#if 0
	// Data for visual representation
	const int WIDTH = 512, HEIGHT = 512;
	Mat I = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	//--------------------- 1. Set up training data randomly ---------------------------------------
	Mat trainData(2 * NTRAINING_SAMPLES, 2, CV_32FC1);
	Mat labels(2 * NTRAINING_SAMPLES, 1, CV_32SC1);

	RNG rng(100); // Random value generation class

				  // Set up the linearly separable part of the training data
	int nLinearSamples = (int)(FRAC_LINEAR_SEP * NTRAINING_SAMPLES);

	//! [setup1]
	// Generate random points for the class 1
	Mat trainClass = trainData.rowRange(0, nLinearSamples);
	// The x coordinate of the points is in [0, 0.4)
	Mat c = trainClass.colRange(0, 1);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(0.4 * WIDTH));
	// The y coordinate of the points is in [0, 1)
	c = trainClass.colRange(1, 2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	// Generate random points for the class 2
	trainClass = trainData.rowRange(2 * NTRAINING_SAMPLES - nLinearSamples, 2 * NTRAINING_SAMPLES);
	// The x coordinate of the points is in [0.6, 1]
	c = trainClass.colRange(0, 1);
	rng.fill(c, RNG::UNIFORM, Scalar(0.6*WIDTH), Scalar(WIDTH));
	// The y coordinate of the points is in [0, 1)
	c = trainClass.colRange(1, 2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));
	//! [setup1]

	//------------------ Set up the non-linearly separable part of the training data ---------------
	//! [setup2]
	// Generate random points for the classes 1 and 2
	trainClass = trainData.rowRange(nLinearSamples, 2 * NTRAINING_SAMPLES - nLinearSamples);
	// The x coordinate of the points is in [0.4, 0.6)
	c = trainClass.colRange(0, 1);
	rng.fill(c, RNG::UNIFORM, Scalar(0.4*WIDTH), Scalar(0.6*WIDTH));
	// The y coordinate of the points is in [0, 1)
	c = trainClass.colRange(1, 2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));
	//! [setup2]
	//------------------------- Set up the labels for the classes ---------------------------------
	labels.rowRange(0, NTRAINING_SAMPLES).setTo(1);  // Class 1
	labels.rowRange(NTRAINING_SAMPLES, 2 * NTRAINING_SAMPLES).setTo(2);  // Class 2

																		 //------------------------ 2. Set up the support vector machines parameters --------------------
																		 //------------------------ 3. Train the svm ----------------------------------------------------
	cout << "Starting training process" << endl;
	//! [init]
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setC(0.1);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, (int)1e7, 1e-6));
	//! [init]
	//! [train]
	svm->train(trainData, ROW_SAMPLE, labels);
	//! [train]
	cout << "Finished training process" << endl;

	//------------------------ 4. Show the decision regions ----------------------------------------
	//! [show]
	Vec3b green(0, 100, 0), blue(100, 0, 0);
	for (int i = 0; i < I.rows; ++i)
		for (int j = 0; j < I.cols; ++j)
		{
			Mat sampleMat = (Mat_<float>(1, 2) << i, j);
			float response = svm->predict(sampleMat);

			if (response == 1)    I.at<Vec3b>(j, i) = green;
			else if (response == 2)    I.at<Vec3b>(j, i) = blue;
		}
	//! [show]

	//----------------------- 5. Show the training data --------------------------------------------
	//! [show_data]
	int thick = -1;
	int lineType = 8;
	float px, py;
	// Class 1
	for (int i = 0; i < NTRAINING_SAMPLES; ++i)
	{
		px = trainData.at<float>(i, 0);
		py = trainData.at<float>(i, 1);
		circle(I, Point((int)px, (int)py), 3, Scalar(0, 255, 0), thick, lineType);
	}
	// Class 2
	for (int i = NTRAINING_SAMPLES; i <2 * NTRAINING_SAMPLES; ++i)
	{
		px = trainData.at<float>(i, 0);
		py = trainData.at<float>(i, 1);
		circle(I, Point((int)px, (int)py), 3, Scalar(255, 0, 0), thick, lineType);
	}
	//! [show_data]

	//------------------------- 6. Show support vectors --------------------------------------------
	//! [show_vectors]
	thick = 2;
	lineType = 8;
	Mat sv = svm->getUncompressedSupportVectors();

	for (int i = 0; i < sv.rows; ++i)
	{
		const float* v = sv.ptr<float>(i);
		circle(I, Point((int)v[0], (int)v[1]), 6, Scalar(128, 128, 128), thick, lineType);
	}
	//! [show_vectors]

	imwrite("result.png", I);	                   // save the Image
	imshow("SVM for Non-Linear Training Data", I); // show it to the user
	waitKey(0);
#endif 
}
