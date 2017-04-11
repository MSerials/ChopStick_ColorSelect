// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// ChopStickDetect.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ChopStickDetect.h"
#include "MainFrm.h"


#include "ChopStickDetectDoc.h"
#include "ChopStickDetectView.h"

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChopStickDetectApp

BEGIN_MESSAGE_MAP(CChopStickDetectApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CChopStickDetectApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_BUTTON_LOAD, &CChopStickDetectApp::OnButtonLoad)
	ON_COMMAND(ID_BUTTON_TEST, &CChopStickDetectApp::OnButtonTest)
	ON_COMMAND(ID_BUTTONROI, &CChopStickDetectApp::OnButtonroi)
	ON_COMMAND(ID_BUTTON_OK_EXAMPLES, &CChopStickDetectApp::OnButtonOkExamples)
	ON_COMMAND(ID_BUTTON_NG_EXAMPLES, &CChopStickDetectApp::OnButtonNgExamples)
	ON_COMMAND(ID_BUTTON_TRAIN, &CChopStickDetectApp::OnButtonTrain)
	ON_COMMAND(ID_BUTTON_PREDICT, &CChopStickDetectApp::OnButtonPredict)
END_MESSAGE_MAP()


// CChopStickDetectApp 构造

CChopStickDetectApp::CChopStickDetectApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ChopStickDetect.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CChopStickDetectApp 对象

CChopStickDetectApp theApp;


// CChopStickDetectApp 初始化

BOOL CChopStickDetectApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CChopStickDetectDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CChopStickDetectView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();



#ifdef _DEBUG
	AllocConsole();
#else
	AttachConsole(ATTACH_PARENT_PROCESS);
#endif
#ifdef _TEST
	FILE* pCout;
	freopen_s(&pCout, "conout$", "w", stdout); //returns 0
#endif






	return TRUE;
}

int CChopStickDetectApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CChopStickDetectApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CChopStickDetectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CChopStickDetectApp 自定义加载/保存方法

void CChopStickDetectApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CChopStickDetectApp::LoadCustomState()
{
}

void CChopStickDetectApp::SaveCustomState()
{
}

// CChopStickDetectApp 消息处理程序





void CChopStickDetectApp::OnButtonLoad()
{
	// TODO: 在此添加命令处理程序代码
	try {
		CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");

		if (fileDlg.DoModal() != IDOK) return;

		//读取磁盘文件
		g.opencv.LoadMatImg((char*)(LPCSTR)(CStringA)fileDlg.GetPathName());

		g.opencv.ColorInvert(g.opencv.m_RawMatImg);

		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		CChopStickDetectView *view = (CChopStickDetectView*)pMain->GetActiveView();
		view->Draw();
	}
	catch (...)
	{

		return;
	}
}


void CChopStickDetectApp::OnButtonTest()
{
	// TODO: 在此添加命令处理程序代码
//	std::vector<std::string> images;
//	g.opencv.ann_train(g.color_ok_images,g.color_ng_images);
	cv::Rect rect(0, 0, (int)g.opencv.m_RawMatImg.cols, (int)g.opencv.m_RawMatImg.rows);
	g.opencv.m_RawMatImg = g.opencv.GetHSVData(g.opencv.m_RawMatImg, rect);
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CChopStickDetectView *view = (CChopStickDetectView*)pMain->GetActiveView();
	view->Draw();

}


void CChopStickDetectApp::OnButtonroi()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	//CView* pView = (CView*)pFrame->GetActiveView();
	CChopStickDetectView *pView = (CChopStickDetectView*)pFrame->GetActiveView();
	CRect rt;
	pView->GetClientRect(&rt);
	pView->SetMessage(1);//通知画框框

}


void CChopStickDetectApp::OnButtonOkExamples()
{
	// TODO: 在此添加命令处理程序代码
#if 0
	win_tool wt;
	CString AppPath = wt.AppPath();
	CString tp = AppPath + L"\\COLOROK\\";
	CreateDirectory(tp, NULL);
#endif
	cv::Mat t;
	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	CString str = DirPath.Show();
	DirPath.ProcPicDir(str, images);
	for (size_t index = 0; index < images.size(); index++)
	{
		std::string file = (std::string)(CStringA)images[index];
		t = cv::imread(file, -1);
		if (!t.empty()) g.color_ok_images.push_back((std::string)(CStringA)images[index]);
	}
	g.ini.m_front_path = str;
	g.ini.SaveParaFile(PARA_ALL);
}


void CChopStickDetectApp::OnButtonNgExamples()
{
	// TODO: 在此添加命令处理程序代码
#if 0
	win_tool wt;
	CString AppPath = wt.AppPath();
	CString tp = AppPath + L"\\COLORNG\\";
	CreateDirectory(tp, NULL);
#endif
	cv::Mat t;
	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	CString str = DirPath.Show();
	DirPath.ProcPicDir(str, images);
	for (size_t index = 0; index < images.size(); index++)
	{
		std::string file = (std::string)(CStringA)images[index];
		t = cv::imread(file, -1);
		if (!t.empty())g.color_ng_images.push_back((std::string)(CStringA)images[index]);
	}
	g.ini.m_back_path = str;
	g.ini.SaveParaFile(PARA_ALL);
}


void CChopStickDetectApp::OnButtonTrain()
{
	// TODO: 在此添加命令处理程序代码
	win_tool wt;
	CString App = wt.AppPath();
	cv::Mat t;
	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	DirPath.ProcPicDir(App + L"\\" + g.ini.m_front_path + L"\\", images);
	for (size_t index = 0; index < images.size(); index++)
	{
		std::string file = (std::string)(CStringA)images[index];
		cout << file << endl;
		t = cv::imread(file, -1);
		if(!t.empty()) g.color_ok_images.push_back(file);
	}
	images.clear();
	DirPath.ProcPicDir(App + L"\\" + g.ini.m_back_path, images);
	for (size_t index = 0; index < images.size(); index++)
	{
		std::string file = (std::string)(CStringA)images[index];
		t = cv::imread(file, -1);
		if (!t.empty()) g.color_ng_images.push_back(file);
	}

	g.opencv.ann_train(g.color_ok_images, g.color_ng_images);
}


void CChopStickDetectApp::OnButtonPredict()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");

	if (fileDlg.DoModal() != IDOK) return;

	//读取磁盘文件
	g.opencv.LoadMatImg((char*)(LPCSTR)(CStringA)fileDlg.GetPathName());

	//g.opencv.ColorInvert(g.opencv.m_RawMatImg);
	if (g.opencv.m_RawMatImg.empty()) return;
	g.opencv.color_predict(g.opencv.m_RawMatImg);
}
