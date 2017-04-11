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
END_MESSAGE_MAP()

// CChopStickDetectView 构造/析构

CChopStickDetectView::CChopStickDetectView()
{
	// TODO: 在此处添加构造代码
	m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;  // 样式    
	m_RectTracker.m_nHandleSize = 10;  //手柄大小  
	m_RectTracker.m_rect.SetRectEmpty(); // 最初的矩形   
	m_msg = 0;
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

	// TODO: 在此处为本机数据添加绘制代码

	CRect rt;
	GetClientRect(&rt);
	int nWndWidth = rt.right - rt.left;
	int nWndHeight = rt.bottom - rt.top;

	uchar *pdata = NULL;
	if (g.opencv.CopyMatDataToMem(g.opencv.m_RawMatImg, &pdata))
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



void CChopStickDetectView::Draw()
{
	CDC *pdc = CChopStickDetectView::GetDC();
	OnDraw(pdc);
	ReleaseDC(pdc);
}


void CChopStickDetectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_msg) return;
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
		Draw();
	//	Invalidate(FALSE);   //刷新窗口区域，使得CrectTracker对象重绘到窗口上
		CPaintDC pDC(this); // device context for painting
		m_RectTracker.Draw(&pDC);
	}

	CView::OnLButtonDown(nFlags, point);
}
