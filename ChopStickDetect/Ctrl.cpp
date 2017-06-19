// Ctrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ChopStickDetect.h"
#include "Ctrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ChopStickDetect.h"

// CCtrl 对话框

IMPLEMENT_DYNAMIC(CCtrl, CDialogEx)

CCtrl::CCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONTROL_DLG, pParent)
{

}

CCtrl::~CCtrl()
{
}

void CCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCtrl::OnBnClickedButtonSave)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_DRAWRECT, &CCtrl::OnBnClickedButtonDrawrect)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CCtrl::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_TRAIN, &CCtrl::OnBnClickedButtonTrain)
	ON_BN_CLICKED(IDC_BUTTON_PREDICT, &CCtrl::OnBnClickedButtonPredict)
END_MESSAGE_MAP()


// CCtrl 消息处理程序


void CCtrl::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g.RectState) { AfxMessageBox(L"请画完模板框！"); return; }
	CString str;
	GetDlgItem(IDC_EDIT_H)->GetWindowText(str);
	g.ini.m_h = _ttoi(str);
	GetDlgItem(IDC_EDIT_S)->GetWindowText(str);
	g.ini.m_s = _ttoi(str);
	GetDlgItem(IDC_EDIT_V)->GetWindowText(str);
	g.ini.m_v = _ttoi(str);
	g.ini.SaveParaFile(PARA_ALL);
}


void CCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;// (0, 0, 1920, 1080);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(32, 32, 35));
	CDialogEx::OnPaint();
}


BOOL CCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	str.Format(_T("%d"), g.ini.m_h);
	GetDlgItem(IDC_EDIT_H)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_s);
	GetDlgItem(IDC_EDIT_S)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_v);
	GetDlgItem(IDC_EDIT_V)->SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCtrl::OnBnClickedButtonDrawrect()
{
	// TODO: 在此添加控件通知处理程序代码
	g.RectState = DRAWCOLORRECT;
}


void CCtrl::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	CChopStickDetectApp *pApp = (CChopStickDetectApp *)AfxGetApp();
	pApp->TresholdHsv(g.ini.m_h, g.ini.m_s, g.ini.m_v);

}


void CCtrl::OnBnClickedButtonTrain()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CString App = wt.AppPath();
	cv::Mat t;
	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	DirPath.ProcPicDir(App + L"\\COLOROK" + L"\\", images);


	std::vector<std::string> front_images;
	for (size_t index = 0; index < images.size(); index++)
	{
		std::string file = (std::string)(CStringA)images[index];
		cout << file << endl;
		t = cv::imread(file, -1);
		if (!t.empty()) front_images.push_back(file);
	}

	if (0 == front_images.size())
	{
		AfxMessageBox(L"没读取到OK样品图片");
	}

	images.clear();
	DirPath.ProcPicDir(App + L"\\COLORNG" + L"\\", images);
	std::vector<std::string> back_images;
	for (size_t index = 0; index < images.size(); index++)
	{
		std::string file = (std::string)(CStringA)images[index];
		cout << file << endl;
		t = cv::imread(file, -1);
		if (!t.empty()) back_images.push_back(file);
	}

	if (0 == back_images.size())
	{
		AfxMessageBox(L"没读取到NG样品图片");
	}

	g.opencv.svm_train(front_images, back_images);
}


void CCtrl::OnBnClickedButtonPredict()
{
	// TODO: 在此添加控件通知处理程序代码
//	g.opencv.TresholdHsv(g.opencv.m_RawMatImg, dst, h, s, v);
	if (g.opencv.m_RawMatImg.empty()) { AfxMessageBox(L"没有载入图片"); return; }
	double res = g.opencv.svm_predict(g.opencv.m_RawMatImg);
	CString str;
	if (res > 0.1)
	{
		str.Format(_T("小于0表示OK， 大于0表示 NG， 数值绝对值越大预测越明显    预测值为%f 判定为NG"), res);
	}
	else if(res<-0.1)
	{
		str.Format(_T("小于0表示OK， 大于0表示 NG， 数值绝对值越大预测越明显    预测值为%f 判定为OK"), res);
	}
	else
	{
		AfxMessageBox(L"预测可能不准确");
		return;
	}

	
	AfxMessageBox(str);
}
