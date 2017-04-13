// Ctrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ChopStickDetect.h"
#include "Ctrl.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// CCtrl 消息处理程序


void CCtrl::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g.RectState) { AfxMessageBox(L"请画完模板框！"); return; }
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
