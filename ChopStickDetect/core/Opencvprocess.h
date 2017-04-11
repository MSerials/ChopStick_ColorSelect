#pragma once


#if !defined(_OPENCV_PROC_002078B03530__INCLUDED_)
#define _OPENCV_PROC_002078B03530__INCLUDED_

#include "opencv.hpp"
#include "ml.hpp"
#include <opencv2/ml/ml.hpp>

//#include <hash_map>
//using namespace stdext;
using namespace cv;
using namespace cv::ml;

#define NOEXIST -1


#define ColorInvert(mat) MonoInvert(mat)
#define image_mono_cesus(mat) image_color_cesus(mat, 0)

enum{ INVALID = 0, NOOBJECT, NODOTS, UP, DOWN, LEFT, RIGHT };
enum{ OTSU = 0,CONST_VALUE};

class COpencvprocess
{ 
public:

	enum{
		LLINESAMPLE1, LLINESAMPLE2, LLINESAMPLE3, LLINESAMPLE4,  RLINESAMPLE1, RLINESAMPLE2, RLINESAMPLE3, RLINESAMPLE4};

	int m_coordinate[RLINESAMPLE4 + 1][2];             //�洢����[x][y]

	float m_line[2][2];

	enum {
		NoError = 0, ISOLATE = 1, ADDED = 2
	};
private:
	enum{ROISQUARE, ROILINE, ROIFACE,ROIMAX};
public:
	COpencvprocess();
	virtual ~COpencvprocess();  



	struct V4i {
		int x1;
		int y1;
		int x2;
		int y2;
	};
	struct V2i {
		int x;
		int y;
	};

	//�洢����ͨ�������Ϣ
	struct AreaInfo {
		//�Ŵ����ڵڼ�����
		int RusSubTo;
		//���ŵ�����
		int RunsSerial;
		//���ŵ����
		union
		{
			float fsquare;
			int isquare;
		} AreaSquare;
		//�����ڵڼ���
		int row;
		int st;
		int ed;
		int sign;
	};


	struct AreaInfoIndex
	{
		int Signed;
		int Cloud;
		int Square;
		vector<AreaInfo> index;
	};

	struct COLOR
	{
		uchar R;
		uchar G;
		uchar B;
	}_RED, _GREEN, _BLUE, _YELLOW;



	struct tagImgROI{
		int xpos;
		int ypos;
		int width;
		int height;
	}ImgROI, MFCROI, SHOWIMGPOS;

	struct tagImgProperty
	{
		int width;
		int height;
		int DPI;
		int sRGB;
		int ISO;
		short manufactory[1024];
		short type[16];
		int nChannels;
		int depth;
	}ImgProperty;

	struct MotionInfo
	{
		struct Tpye1
		{
			int move_wise; //-1 is clockwise 0 is no move and 1 is counterclockwise
			int move_angle;
		}tpye1;
		struct Tpye2
		{
			int arrayTo;
		}tpye2;
		int Valid;
	}motion_info, MotionInfoClear;

	int ColorCesus[4][256];
	int* MonoCesus = ColorCesus[0];
public:
	//ͼ���� Mat��ʽ
	void MonoInvert(const Mat& mat);

	//ͼ�񻺴�
	IplImage* m_IplBuffer;
	//��ȡͼ�����Ȥ����
	void GetROI(tagImgROI &ROI);
	//�Իҽ�ֱ��ͼ���д洢
	int m_GrayImgStatics[256];


	void SwapValue(char &a, char &b);
private:
	// ͨ�������ȡӳ�����Ȥ����
	BOOL GetIplROI(IplImage* Ipl);
	BOOL GetMatROI(const Mat& mat);

public:
	//�洢��ֵ��
	int m_thresholdvalue;
	//�洢��ֵ������ֵ
	int m_tholdadjust;
private:

	int m_TotalPix;
	
	int otsuThreshold(const Mat& mat);
	int otsubyROI(const Mat& mat);
	void Threshold(const Mat& mat, int threshold);
public:
	
private:
	// Ѱ��ȡ����
	bool FindLineSample(IplImage* Ipl);
public:
	bool FindLine();
	double average(int* data, int* len);
	double Lb, La, Rb, Ra;
	void DrawLine(IplImage* Ipl);
private:

public:
	// Ϊ�˽�ͼƬ��mat��ʽת����bmp��ʽ����Ҫ�����ĸ�ʽͷ��Ϣ������
	LPBITMAPINFO CreateMapInfo(Mat mat);
	// ��bmp��ʽת��Mat��ʽ
	cv::Mat BmpToMat(BITMAPINFO* bmpinfo, BYTE* imageData);

	// ͼ��ԭʼ����
	Mat m_RawMatImg,m_ResultMatImg;;

	Mat LoadMatImg(char* filename);
	LPBITMAPINFO m_lpBmi;

	bool get_Mat_depth_and_channels(const Mat& mat, int& depth, int& channels);
	inline void swapValue(uchar& a, uchar& b);
public:
	int MatImgProcess(Mat& mat);
	int MatImgProcess(const cv::Mat& mat, cv::Mat& dst);
	void getWidthAndHeight(cv::Mat mat, cv::Point &pt);
	// ͳ��ͼƬֱ��ͼ
	int image_color_cesus(const Mat& mat, int channel);
	// ������ֱ��ͼ����
	int m_ColorCesus[4][256];
private:
	Mat m_RawMatCannotChanged;
public:
	inline float IvtSqrt(float x);
	inline float Sqrt(float x);
	int hough_lines(const Mat& mat, vector<Vec4i>& lines, double rho, double theta, int threshold, double  minLineLength = 0, double  maxLineGap = 0);

	void InitMat(Mat& mat, int t);
	Mat m_canny;
	Mat m_dst;
private:
	float m_fabs(float &a);
	float m_default_ang_sin[180];
	float m_default_ang_cos[180];
	float m_default_ang_cos_sin[360];
	void swapValuei(int& a, int& b);
	// �����˱���ͼƬ
	Mat m_BackGroundMatImg;
	// �ӱ���ͼƬ����ȡ����
	
public:
	// �ӱ���ͼƬ����ȡ����ͼƬ
	Mat m_BackGroundMaskMatImg;
	bool get_mask_from_background(const Mat& mat);
private:
	void delete_Mat_with_Mask(Mat& mat);
public:
	// �洢�˴�������ͼƬ
	
	void get_BackGroud_Mat_img(Mat& dst);

	float find_circle_radius(Mat& src, int& lower, int& higher, int *point);

	//Mat img, gray, bggray;
	void find_gravity_center(const Mat& mat, vector<V2i>& p);
	void find_gravity_center(const Mat& mat, V2i& p);
	void find_gravity_center(const Mat& mat, Point &p);
	void DrawLatticeOnMat(const Mat& mat, vector<V2i>& p);
	void CopyMatDataToMem(const Mat& mat);
	bool CopyMatDataToMem(const Mat& src, uchar **data);
	uchar* ImageData;
	void MarkMaskImg(const Mat& mat, Mat& mask, int type = 1);
	int getAllBlockSquare(const Mat& mat, vector<AreaInfo>& Runs, vector<AreaInfoIndex>& InfoIndex);
	bool isOverLap(int& a ,int& b, int& c,int& d);
	void signBlockArea(Mat& mat, vector<AreaInfo>& Runs, vector<AreaInfoIndex>& InfoIndex, int maxarea, int minarea, float ratio, const COLOR& color);

	void vector_emerge(vector<AreaInfoIndex>& vec, int inserted, int emerged);
	int isAreadyHave(int Cloud, vector<AreaInfoIndex>& InfoIndex);

	void getSizeContours(vector<vector<Point>> &contours, size_t cmin, size_t cmax);
	int getMaxIDandDeleteMin(vector<vector<Point>> &contours,size_t cmin);
	void getAllBlackBlockinGray(Mat& black_mask, const Mat& gray, const Mat& white_mask);
	int getOtsuByMask(const Mat& src, const Mat& mask);

	void drawArrow(Mat& img, Point pStart, Point pEnd, int len, int alpha,Scalar& color, int thickness, int lineType);
	int iabs(int a);
	bool show_error(Mat& mat, char* str);



	int ThresHold(Mat& mat, Mat& dst);
	void DeleteCenterCircle(Mat& mat, const Point& pt, unsigned int radius);
	void exAdaptiveThreshold(const Mat& src, Mat& dst, int ThresHoldFixed, int BlockRange,int type);
	void getDirectImage(const Mat& src, const Mat& white_mask, Mat& dst, Point& pt, int direct);
	void MixMatImg(const Mat& src, Mat& dst);
	int getDotsNumber(const Mat& src, uchar gray);
	CString SaveFile(cv::Mat src,CString str = L"");
	void get_mask_image(const Mat& src, Mat& dst, vector<vector<Point>>& contours, int ID = 1);

	//image caculate
	//HDR
	cv::Mat hdr(const std::vector<cv::Mat> & images, cv::Mat& dst, const std::vector<float>& times, cv::Mat respose);

	cv::Mat hdr(const std::vector<cv::Mat>images, const std::vector<float>& times, cv::Mat response);
	//ldr
	cv::Mat ldr(const std::vector<cv::Mat> & images, cv::Mat& dst, const std::vector<float>& times, cv::Mat response);

	cv::Mat ldr(const std::vector<cv::Mat> & images, const std::vector<float>& times, cv::Mat response);

	cv::Mat fusion(const std::vector<cv::Mat> images, cv::Mat & dst);

	cv::Mat fusion(const std::vector<cv::Mat> images);

	void exsplit(const cv::Mat src, std::vector<cv::Mat>& mv);

	float average_data(const cv::Mat &src);

	cv::Mat GetHSVData(const cv::Mat & src, cv::Rect rect);

	Ptr<ANN_MLP> color_train(const Mat_<float> &data, const Mat_<float>& responses);
	float color_predict(Mat_<float>& data);
	float color_predict(const cv::Mat & src);
	int ann_train(const std::vector<std::string>& front_images, const std::vector<std::string>& back_images);

	bool ann_load(const String filename = "color.xml");

	//UI
	void SetWindow(size_t width, size_t height, void* winhandle = nullptr);
	cv::Rect GetROI(cv::Rect ScreenSize, cv::Rect DrawROI, cv::Rect ImgSize);

	private:
		Ptr<ANN_MLP> color_network;
		size_t winwidth;
		size_t winheight;
		size_t winroiwidth;
		size_t winroiheight;
		struct _window { size_t w; size_t h; void* winhandle; };
		std::vector<_window> Window;
};

//extern COpencvprocess *cvproc;

#endif 


#ifndef __SIFTDESCTOR__
#define __SIFTDESCTOR__


class siftDesctor {
public:
	siftDesctor() {};
	std::string imageName;
	std::vector<std::vector<float>> frame;
	std::vector<std::vector<float>> desctor;
	void covdet_keypoints_and_descriptors(cv::Mat &img, std::vector<std::vector<float>> &frames, std::vector<std::vector<float>> &desctor, bool rooSIFT, bool verbose);
	std::vector<float> rootsift(std::vector<float> &dst);

	void Serialize(std::ofstream &outfile) const {
		std::string tmpImageName = imageName;
		int strSize = (int)imageName.size();
		outfile.write((char *)&strSize, sizeof(int));
		outfile.write((char *)&tmpImageName[0], sizeof(char)*strSize); // д���ļ���

		int descSize = (int)desctor.size();
		outfile.write((char *)&descSize, sizeof(int));

		// д��sift����
		for (int i = 0; i < descSize; i++) {
			outfile.write((char *)&(desctor[i][0]), sizeof(float) * 128);
			outfile.write((char *)&(frame[i][0]), sizeof(float) * 6);
		}

	}

	static siftDesctor Deserialize(std::ifstream &ifs) {
		siftDesctor siftDesc;
		int strSize = 0;
		ifs.read((char *)&strSize, sizeof(int)); // д���ļ���
		siftDesc.imageName = "";
		siftDesc.imageName.resize(strSize);
		ifs.read((char *)&(siftDesc.imageName[0]), sizeof(char)*strSize); // �����ļ���

		int descSize = 0;
		ifs.read((char *)&descSize, sizeof(int));

		// ����sift������frame
		for (int i = 0; i < descSize; i++) {
			std::vector<float> tmpDesc(128);
			ifs.read((char *)&(tmpDesc[0]), sizeof(float) * 128);
			siftDesc.desctor.push_back(tmpDesc);

			std::vector<float> tmpFrame(6);
			ifs.read((char *)&(tmpFrame[0]), sizeof(float) * 6);
			siftDesc.frame.push_back(tmpFrame);
		}

		return siftDesc;
	}

};

#endif