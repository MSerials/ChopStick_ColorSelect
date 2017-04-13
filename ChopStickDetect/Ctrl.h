#pragma once


// CCtrl 对话框

class CCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CCtrl)

public:
	CCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCtrl();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnPaint();
};
