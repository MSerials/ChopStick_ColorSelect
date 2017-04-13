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

// ChopStickDetectView.h : CChopStickDetectView 类的接口
//

#pragma once


class CChopStickDetectView : public CView
{
protected: // 仅从序列化创建
	CChopStickDetectView();
	DECLARE_DYNCREATE(CChopStickDetectView)

// 特性
public:
	CChopStickDetectDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	void iOnDraw(CDC* pDC, const cv::Mat & src);  // 重写以绘制该视图
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CChopStickDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void Draw(const cv::Mat& src);
	void SetMessage(int msg = 0) { m_msg = msg; }
private:
	int m_msg;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CRectTracker  m_RectTracker;
	CString m_mp;
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	BOOL SetTipText(UINT id, NMHDR * pTTTStruct, LRESULT * pResult);

	CMFCToolTipCtrl		   m_tooltip;
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ThresHoldHsv(uchar h, uchar s, uchar v);
};

#ifndef _DEBUG  // ChopStickDetectView.cpp 中的调试版本
inline CChopStickDetectDoc* CChopStickDetectView::GetDocument() const
   { return reinterpret_cast<CChopStickDetectDoc*>(m_pDocument); }
#endif

