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

// ChopStickDetect.h : ChopStickDetect Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CChopStickDetectApp:
// �йش����ʵ�֣������ ChopStickDetect.cpp
//

class CChopStickDetectApp : public CWinAppEx
{
public:
	CChopStickDetectApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
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
