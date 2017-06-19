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

// ChopStickDetectView.cpp : CChopStickDetectView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ChopStickDetect.h"
#endif

#include "ChopStickDetectDoc.h"
#include "ChopStickDetectView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChopStickDetectView

IMPLEMENT_DYNCREATE(CChopStickDetectView, CView)

BEGIN_MESSAGE_MAP(CChopStickDetectView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChopStickDetectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()

	ON_NOTIFY_EX(TTN_NEEDTEXT,0,SetTipText)

END_MESSAGE_MAP()

// CChopStickDetectView ����/����

CChopStickDetectView::CChopStickDetectView()
{
	// TODO: �ڴ˴���ӹ������
	m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;  // ��ʽ    
	m_RectTracker.m_nHandleSize = 10;  //�ֱ���С  
	m_RectTracker.m_rect.SetRectEmpty(); // ����ľ���   
	m_msg = 0;
	m_mp = L"���λ��";
	m_tooltip.Create(this);
	m_tooltip.AddTool(this, TTS_ALWAYSTIP);
	//�趨���ֵ���ɫ
	m_tooltip.SetTipTextColor(RGB(0, 0, 255));
	//�趨��ʾ�����ڿؼ���ͣ����ʱ��
	m_tooltip.SetDelayTime(150);
}

CChopStickDetectView::~CChopStickDetectView()
{
}

BOOL CChopStickDetectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChopStickDetectView ����
void CChopStickDetectView::OnDraw(CDC* pDC)
{
	CChopStickDetectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

void CChopStickDetectView::iOnDraw(CDC* pDC, const cv::Mat & src)
{
	CChopStickDetectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	CRect rt;
	GetClientRect(&rt);
	int nWndWidth = rt.right - rt.left;
	int nWndHeight = rt.bottom - rt.top;

	uchar *pdata = NULL;
	if (g.opencv.CopyMatDataToMem(src, &pdata))
	{

		CDC dcMem;
		CBitmap bmp; //�ڴ��г�����ʱͼ���λͼ
		bmp.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());
		dcMem.CreateCompatibleDC(pDC); //��������DC���������ڴ�DC
									   //��������λͼ(������pDC���������򻭳���ͼ�α�ɺ�ɫ)
		CBitmap *pOldBit = dcMem.SelectObject(&bmp);
		//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
		HDC  hDC = dcMem.GetSafeHdc();
		::SetStretchBltMode(hDC, COLORONCOLOR);

		LPBITMAPINFO pBitmapInfo = g.opencv.CreateMapInfo(src);
		const int height = src.rows;
		const int width = src.cols;
		::StretchDIBits(hDC,
			0,//nWndWidth,
			0,//nWndHeight,
			nWndWidth,
			nWndHeight,
			0,
			0,
			width,
			height,
			(BYTE*)pdata,
			pBitmapInfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);
		GetClientRect(&rt);
		hDC = pDC->GetSafeHdc();
		pDC->BitBlt(0, 0, rt.Width(), rt.Height(), &dcMem, 0, 0, SRCCOPY);

		//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
		//��ͼ��ɺ������
		dcMem.DeleteDC();     //ɾ��DC
		bmp.DeleteObject(); //ɾ��λͼ
		free(pdata);
	}
}


// CChopStickDetectView ��ӡ


void CChopStickDetectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChopStickDetectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CChopStickDetectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CChopStickDetectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CChopStickDetectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (g.RectState)
	{
		CRect rt;
		GetClientRect(&rt);
		switch (g.RectState)
		{
		case DRAWCOLORRECT:

			break;
		default:
			break;
		}





		g.RectState = NODRAWRECT;
		return;
	}
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChopStickDetectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CChopStickDetectView ���

#ifdef _DEBUG
void CChopStickDetectView::AssertValid() const
{
	CView::AssertValid();
}

void CChopStickDetectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChopStickDetectDoc* CChopStickDetectView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChopStickDetectDoc)));
	return (CChopStickDetectDoc*)m_pDocument;
}
#endif //_DEBUG


// CChopStickDetectView ��Ϣ�������



void CChopStickDetectView::Draw(const cv::Mat& src)
{
	CDC *pdc = CChopStickDetectView::GetDC();
	iOnDraw(pdc,src);
	ReleaseDC(pdc);
}


void CChopStickDetectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!g.RectState) return;
	CRect cwrect;
	//GetDlgItem(IDC_STATIC_IMGCAPTURE)->GetWindowRect(&cwrect); //��ȡ�����пؼ�������
	//ScreenToClient(&cwrect); //ת��Ϊ��������CRect  if(point.x>cwrect.left&& point.y>cwrect.top    //ȷ�����µ������ڿؼ�������   && point.x
	{
		if (m_RectTracker.HitTest(point) < 0)     //���δ���о���ѡ���,���»�ѡ���
		{
			m_RectTracker.TrackRubberBand(this, point, TRUE);
			m_RectTracker.m_rect.NormalizeRect();   //���滯���Σ��������滯���������н��ܣ�
		}
		else           //������о���ѡ���
		{
			m_RectTracker.Track(this, point, TRUE);
			m_RectTracker.m_rect.NormalizeRect();   //���滯����
													//SendMessage(WM_LBUTTONUP,NULL,NULL);
		}
		Invalidate(FALSE);
	//	Draw();
	//	Invalidate(FALSE);   //ˢ�´�������ʹ��CrectTracker�����ػ浽������
		CPaintDC pDC(this); // device context for painting
		m_RectTracker.Draw(&pDC);
		/*
		g.opencv.m_rect.y = m_RectTracker.m_rect.top;
		g.opencv.m_rect.x = m_RectTracker.m_rect.left;
		g.opencv.m_rect.width = m_RectTracker.m_rect.Width();
		g.opencv.m_rect.height = m_RectTracker.m_rect.Height();
		*/
	}

	CView::OnLButtonDown(nFlags, point);
}


void CChopStickDetectView::OnPaint()
{
#if 0
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CView::OnPaint();
	}
	//	CBrush brh(clr);

	//	CPaintDC dc(this);
	CDC *pDC = GetDC();
	for (int i = 0; i<100; i++)
	{
		pDC->FillSolidRect(i, 0, 1, 100, RGB(i*2.55, 255 - i*2.55, 255));
		pDC->FillSolidRect(100 + i, 0, 1, 100, RGB(255, i*2.55, 255 - 2.55*i));
		pDC->FillSolidRect(200 + i, 0, 1, 100, RGB(255 - 2.55*i, 255 - i*2.55, 2.55*i));
		pDC->FillSolidRect(300 + i, 0, 1, 100, RGB(2.55*i, 0, 255 - 2.55*i));
		pDC->FillSolidRect(400 + i, 0, 1, 100, RGB(255 - 2.55*i, 0, 2.55*i));
	}

#endif
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
}


void CChopStickDetectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HDC h = ::GetDC(m_hWnd);//��ǰ���ڵľ��
	COLORREF clr = COLORREF(GetPixel(h, point.x, point.y));//��ȡ��ǰ�����ɫ
	CDC *pDC = GetDC();
	pDC->FillSolidRect(0, 0, 20, 20, clr);   //��ʾ��������ɫ 
	uchar B = (clr & 0xFF0000) >> 16;
	uchar G = (clr & 0xFF00) >> 8;
	uchar R = (clr & 0xFF);
	cv::Mat c(1, 1, CV_8UC3, Scalar(B, G, R)),d;
	cv::cvtColor(c, d, CV_BGR2HSV_FULL);
	uchar H = d.at<uchar>(0, 0);
	uchar S = d.at<uchar>(0, 1);
	uchar V = d.at<uchar>(0, 2);
	CString str;
	str.Format(_T("���λ��(%d,%d),H:%d,S:%d,V:%d"), point.x, point.y,H,S,V);
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.GetElement(0)->SetText(str);
	pFrame->m_wndStatusBar.GetElement(0)->SetDescription(L"��ʾ��ǰ���λ����ɫ״̬");
	pFrame->m_wndStatusBar.GetElement(0)->Redraw();
//	pFrame->m_wndStatusBar.RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}

BOOL CChopStickDetectView::SetTipText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pTTTStruct;
	UINT nID = pTTTStruct->idFrom;   //�õ���Ӧ����ID���п�����HWND   
	return TRUE;

}


void CChopStickDetectView::ThresHoldHsv(uchar h, uchar s, uchar v)
{
	if (g.opencv.m_RawMatImg.empty()) return;
	cv::Mat d;
}
