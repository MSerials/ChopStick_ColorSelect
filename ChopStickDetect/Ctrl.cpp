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
