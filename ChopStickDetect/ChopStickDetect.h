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

// ChopStickDetect.h : ChopStickDetect 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CChopStickDetectApp:
// 有关此类的实现，请参阅 ChopStickDetect.cpp
//

class CChopStickDetectApp : public CWinAppEx
{
public:
	CChopStickDetectApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonTest();
	afx_msg void OnButtonroi();
	afx_msg void OnButtonOkExamples();
	afx_msg void OnButtonNgExamples();
	afx_msg void OnButtonTrain();
	afx_msg void OnButtonPredict();
	afx_msg void OnButtonShowControl();
};

extern CChopStickDetectApp theApp;
