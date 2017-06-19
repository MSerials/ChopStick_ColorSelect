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

// ChopStickDetectView.cpp : CChopStickDetectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CChopStickDetectView 构造/析构

CChopStickDetectView::CChopStickDetectView()
{
	// TODO: 在此处添加构造代码
	m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;  // 样式    
	m_RectTracker.m_nHandleSize = 10;  //手柄大小  
	m_RectTracker.m_rect.SetRectEmpty(); // 最初的矩形   
	m_msg = 0;
	m_mp = L"鼠标位置";
	m_tooltip.Create(this);
	m_tooltip.AddTool(this, TTS_ALWAYSTIP);
	//设定文字的颜色
	m_tooltip.SetTipTextColor(RGB(0, 0, 255));
	//设定提示文字在控件上停留的时间
	m_tooltip.SetDelayTime(150);
}

CChopStickDetectView::~CChopStickDetectView()
{
}

BOOL CChopStickDetectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChopStickDetectView 绘制
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

	// TODO: 在此处为本机数据添加绘制代码

	CRect rt;
	GetClientRect(&rt);
	int nWndWidth = rt.right - rt.left;
	int nWndHeight = rt.bottom - rt.top;

	uchar *pdata = NULL;
	if (g.opencv.CopyMatDataToMem(src, &pdata))
	{

		CDC dcMem;
		CBitmap bmp; //内存中承载临时图象的位图
		bmp.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());
		dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC
									   //创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
		CBitmap *pOldBit = dcMem.SelectObject(&bmp);
		//按原来背景填充客户区，不然会是黑色
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

		//将内存DC上的图象拷贝到前台
		//绘图完成后的清理
		dcMem.DeleteDC();     //删除DC
		bmp.DeleteObject(); //删除位图
		free(pdata);
	}
}


// CChopStickDetectView 打印


void CChopStickDetectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChopStickDetectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChopStickDetectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CChopStickDetectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CChopStickDetectView 诊断

#ifdef _DEBUG
void CChopStickDetectView::AssertValid() const
{
	CView::AssertValid();
}

void CChopStickDetectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChopStickDetectDoc* CChopStickDetectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChopStickDetectDoc)));
	return (CChopStickDetectDoc*)m_pDocument;
}
#endif //_DEBUG


// CChopStickDetectView 消息处理程序



void CChopStickDetectView::Draw(const cv::Mat& src)
{
	CDC *pdc = CChopStickDetectView::GetDC();
	iOnDraw(pdc,src);
	ReleaseDC(pdc);
}


void CChopStickDetectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!g.RectState) return;
	CRect cwrect;
	//GetDlgItem(IDC_STATIC_IMGCAPTURE)->GetWindowRect(&cwrect); //获取窗体中控件的区域
	//ScreenToClient(&cwrect); //转换为相对区域的CRect  if(point.x>cwrect.left&& point.y>cwrect.top    //确保按下的坐标在控件区域内   && point.x
	{
		if (m_RectTracker.HitTest(point) < 0)     //如果未击中矩形选择框,重新画选择框
		{
			m_RectTracker.TrackRubberBand(this, point, TRUE);
			m_RectTracker.m_rect.NormalizeRect();   //正规化矩形（关于正规化矩形下面有介绍）
		}
		else           //如果击中矩形选择框
		{
			m_RectTracker.Track(this, point, TRUE);
			m_RectTracker.m_rect.NormalizeRect();   //正规化矩形
													//SendMessage(WM_LBUTTONUP,NULL,NULL);
		}
		Invalidate(FALSE);
	//	Draw();
	//	Invalidate(FALSE);   //刷新窗口区域，使得CrectTracker对象重绘到窗口上
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
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()
}


void CChopStickDetectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HDC h = ::GetDC(m_hWnd);//当前窗口的句柄
	COLORREF clr = COLORREF(GetPixel(h, point.x, point.y));//获取当前鼠标颜色
	CDC *pDC = GetDC();
	pDC->FillSolidRect(0, 0, 20, 20, clr);   //显示鼠标出的颜色 
	uchar B = (clr & 0xFF0000) >> 16;
	uchar G = (clr & 0xFF00) >> 8;
	uchar R = (clr & 0xFF);
	cv::Mat c(1, 1, CV_8UC3, Scalar(B, G, R)),d;
	cv::cvtColor(c, d, CV_BGR2HSV_FULL);
	uchar H = d.at<uchar>(0, 0);
	uchar S = d.at<uchar>(0, 1);
	uchar V = d.at<uchar>(0, 2);
	CString str;
	str.Format(_T("鼠标位置(%d,%d),H:%d,S:%d,V:%d"), point.x, point.y,H,S,V);
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.GetElement(0)->SetText(str);
	pFrame->m_wndStatusBar.GetElement(0)->SetDescription(L"显示当前鼠标位置颜色状态");
	pFrame->m_wndStatusBar.GetElement(0)->Redraw();
//	pFrame->m_wndStatusBar.RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}

BOOL CChopStickDetectView::SetTipText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pTTTStruct;
	UINT nID = pTTTStruct->idFrom;   //得到相应窗口ID，有可能是HWND   
	return TRUE;

}


void CChopStickDetectView::ThresHoldHsv(uchar h, uchar s, uchar v)
{
	if (g.opencv.m_RawMatImg.empty()) return;
	cv::Mat d;
}
