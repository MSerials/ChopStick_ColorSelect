// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ChopStickDetect.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_BUTTON_LOAD, &CChopStickDetectApp::OnButtonLoad)
	ON_COMMAND(ID_BUTTON_TEST, &CChopStickDetectApp::OnButtonTest)
	ON_COMMAND(ID_BUTTONROI, &CChopStickDetectApp::OnButtonroi)
	ON_COMMAND(ID_BUTTON_OK_EXAMPLES, &CChopStickDetectApp::OnButtonOkExamples)
	ON_COMMAND(ID_BUTTON_NG_EXAMPLES, &CChopStickDetectApp::OnButtonNgExamples)
	ON_COMMAND(ID_BUTTON_TRAIN, &CChopStickDetectApp::OnButtonTrain)
	ON_COMMAND(ID_BUTTON_PREDICT, &CChopStickDetectApp::OnButtonPredict)
END_MESSAGE_MAP()


// CChopStickDetectApp ����

CChopStickDetectApp::CChopStickDetectApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ChopStickDetect.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CChopStickDetectApp ����

CChopStickDetectApp theApp;


// CChopStickDetectApp ��ʼ��

BOOL CChopStickDetectApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CChopStickDetectDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CChopStickDetectView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
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
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CChopStickDetectApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CChopStickDetectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CChopStickDetectApp �Զ������/���淽��

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

// CChopStickDetectApp ��Ϣ�������





void CChopStickDetectApp::OnButtonLoad()
{
	// TODO: �ڴ���������������
	try {
		CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|λͼ�ļ� (*.bmp)|*.bmp||");

		if (fileDlg.DoModal() != IDOK) return;

		//��ȡ�����ļ�
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	CMainFrame*   pFrame = (CMainFrame*)AfxGetMainWnd();
	//CView* pView = (CView*)pFrame->GetActiveView();
	CChopStickDetectView *pView = (CChopStickDetectView*)pFrame->GetActiveView();
	CRect rt;
	pView->GetClientRect(&rt);
	pView->SetMessage(1);//֪ͨ�����

}


void CChopStickDetectApp::OnButtonOkExamples()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|λͼ�ļ� (*.bmp)|*.bmp||");

	if (fileDlg.DoModal() != IDOK) return;

	//��ȡ�����ļ�
	g.opencv.LoadMatImg((char*)(LPCSTR)(CStringA)fileDlg.GetPathName());

	//g.opencv.ColorInvert(g.opencv.m_RawMatImg);
	if (g.opencv.m_RawMatImg.empty()) return;
	g.opencv.color_predict(g.opencv.m_RawMatImg);
}
