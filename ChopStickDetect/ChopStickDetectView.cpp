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
END_MESSAGE_MAP()

// CChopStickDetectView ����/����

CChopStickDetectView::CChopStickDetectView()
{
	// TODO: �ڴ˴���ӹ������
	m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;  // ��ʽ    
	m_RectTracker.m_nHandleSize = 10;  //�ֱ���С  
	m_RectTracker.m_rect.SetRectEmpty(); // ����ľ���   
	m_msg = 0;
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

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	CRect rt;
	GetClientRect(&rt);
	int nWndWidth = rt.right - rt.left;
	int nWndHeight = rt.bottom - rt.top;

	uchar *pdata = NULL;
	if (g.opencv.CopyMatDataToMem(g.opencv.m_RawMatImg, &pdata))
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

		LPBITMAPINFO pBitmapInfo = g.opencv.CreateMapInfo(g.opencv.m_RawMatImg);
		const int height = g.opencv.m_RawMatImg.rows;
		const int width = g.opencv.m_RawMatImg.cols;
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
	if (1 == m_msg)
	{
		m_msg = 0;
		CRect rt;
		GetClientRect(&rt);




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



void CChopStickDetectView::Draw()
{
	CDC *pdc = CChopStickDetectView::GetDC();
	OnDraw(pdc);
	ReleaseDC(pdc);
}


void CChopStickDetectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_msg) return;
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
		Draw();
	//	Invalidate(FALSE);   //ˢ�´�������ʹ��CrectTracker�����ػ浽������
		CPaintDC pDC(this); // device context for painting
		m_RectTracker.Draw(&pDC);
	}

	CView::OnLButtonDown(nFlags, point);
}
