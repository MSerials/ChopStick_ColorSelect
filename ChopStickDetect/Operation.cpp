// Operation.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChopStickDetect.h"
#include "Operation.h"


// COperation

IMPLEMENT_DYNAMIC(COperation, CDockablePane)

COperation::COperation()
{

}

COperation::~COperation()
{
}


BEGIN_MESSAGE_MAP(COperation, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COperation ��Ϣ�������




//BOOL COperation::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//	m_ctrl_dlg.Create(IDD_ADJUST_DIALOG,this);
//	m_ctrl_dlg.ShowWindow(SW_SHOW);
//	return CDockablePane::PreCreateWindow(cs);
//}


//BOOL COperation::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	return CDockablePane::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


int COperation::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// TODO:  �ڴ������ר�õĴ�������
	COperation * t = this;
	if (!m_ctrl_dlg.Create(IDD_CONTROL_DLG, t))
	{
		TRACE0("δ�ܴ������ѡ�����/n");
		return-1;      // δ�ܴ���
	}
	m_ctrl_dlg.ShowWindow(SW_SHOW);
	return 0;
}


void COperation::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}
