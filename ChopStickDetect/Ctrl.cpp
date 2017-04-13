// Ctrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChopStickDetect.h"
#include "Ctrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ChopStickDetect.h"

// CCtrl �Ի���

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


// CCtrl ��Ϣ�������


void CCtrl::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (g.RectState) { AfxMessageBox(L"�뻭��ģ���"); return; }
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
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;// (0, 0, 1920, 1080);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(32, 32, 35));
	CDialogEx::OnPaint();
}


BOOL CCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str;
	str.Format(_T("%d"), g.ini.m_h);
	GetDlgItem(IDC_EDIT_H)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_s);
	GetDlgItem(IDC_EDIT_S)->SetWindowText(str);
	str.Format(_T("%d"), g.ini.m_v);
	GetDlgItem(IDC_EDIT_V)->SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CCtrl::OnBnClickedButtonDrawrect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g.RectState = DRAWCOLORRECT;
}


void CCtrl::OnBnClickedButtonTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CChopStickDetectApp *pApp = (CChopStickDetectApp *)AfxGetApp();
	pApp->TresholdHsv(g.ini.m_h, g.ini.m_s, g.ini.m_v);
}
