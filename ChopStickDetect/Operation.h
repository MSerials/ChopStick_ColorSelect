#pragma once
#ifndef __PANE1__
#define __PANE1__

#include "Ctrl.h"

class COperation : public CDockablePane
{
	DECLARE_DYNAMIC(COperation)

public:
	COperation();
	virtual ~COperation();

protected:
	DECLARE_MESSAGE_MAP()

	

public:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CCtrl m_ctrl_dlg;
};

#endif
