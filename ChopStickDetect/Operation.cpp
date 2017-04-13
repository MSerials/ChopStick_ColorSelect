// Operation.cpp : 实现文件
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



// COperation 消息处理程序




//BOOL COperation::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	m_ctrl_dlg.Create(IDD_ADJUST_DIALOG,this);
//	m_ctrl_dlg.ShowWindow(SW_SHOW);
//	return CDockablePane::PreCreateWindow(cs);
//}


//BOOL COperation::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CDockablePane::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


int COperation::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// TODO:  在此添加您专用的创建代码
	COperation * t = this;
	if (!m_ctrl_dlg.Create(IDD_CONTROL_DLG, t))
	{
		TRACE0("未能创建输出选项卡窗口/n");
		return-1;      // 未能创建
	}
	m_ctrl_dlg.ShowWindow(SW_SHOW);
	return 0;
}


void COperation::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
