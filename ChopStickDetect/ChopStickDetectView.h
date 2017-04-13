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

// ChopStickDetectView.h : CChopStickDetectView ��Ľӿ�
//

#pragma once


class CChopStickDetectView : public CView
{
protected: // �������л�����
	CChopStickDetectView();
	DECLARE_DYNCREATE(CChopStickDetectView)

// ����
public:
	CChopStickDetectDoc* GetDocument() const;

// ����
public:

// ��д
public:
	void iOnDraw(CDC* pDC, const cv::Mat & src);  // ��д�Ի��Ƹ���ͼ
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CChopStickDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // ChopStickDetectView.cpp �еĵ��԰汾
inline CChopStickDetectDoc* CChopStickDetectView::GetDocument() const
   { return reinterpret_cast<CChopStickDetectDoc*>(m_pDocument); }
#endif

