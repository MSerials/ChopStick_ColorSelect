#pragma once


// CCtrl �Ի���

class CCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CCtrl)

public:
	CCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCtrl();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnPaint();
};
