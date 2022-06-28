
// Graphics_DrawView.cpp: CGraphics_DrawView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphics_Draw.h"
#endif

#include "Graphics_DrawDoc.h"
#include "Graphics_DrawView.h"
#include "CSetPenSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphics_DrawView

IMPLEMENT_DYNCREATE(CGraphics_DrawView, CView)

BEGIN_MESSAGE_MAP(CGraphics_DrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CGraphics_DrawView::OnDrawLine)
	ON_COMMAND(ID_32772, &CGraphics_DrawView::OnDrawCurve)
	ON_COMMAND(ID_32773, &CGraphics_DrawView::OnDrawRectangle)
	ON_COMMAND(ID_32774, &CGraphics_DrawView::OnDrawRRectangle)
	ON_COMMAND(ID_32775, &CGraphics_DrawView::OnDrawArc)
	ON_COMMAND(ID_32777, &CGraphics_DrawView::OnDrawEllips)
	ON_COMMAND(ID_32776, &CGraphics_DrawView::OnDrawCircle)
	ON_COMMAND(ID_32778, &CGraphics_DrawView::OnDrawPolygon)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32779, &CGraphics_DrawView::OnDrawSector)
	ON_COMMAND(ID_32781, &CGraphics_DrawView::OnSetColor)
	ON_COMMAND(ID_32780, &CGraphics_DrawView::OnSetPenSize)
	ON_COMMAND(ID_32782, &CGraphics_DrawView::OnSetPencil)
	ON_COMMAND(ID_32783, &CGraphics_DrawView::OnSetEraser)
	ON_COMMAND(ID_32785, &CGraphics_DrawView::OnSetBallPen)
	ON_COMMAND(ID_32784, &CGraphics_DrawView::OnSetLightPen)
	ON_COMMAND(ID_32786, &CGraphics_DrawView::OnDrawPolyline)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_32787, &CGraphics_DrawView::OnDrawBrush)
	ON_COMMAND(ID_32788, &CGraphics_DrawView::OnSetBrushColor)
END_MESSAGE_MAP()

// CGraphics_DrawView 构造/析构

CGraphics_DrawView::CGraphics_DrawView() noexcept
{
	// TODO: 在此处添加构造代码
	m_PenColor = RGB(0, 0, 0);
	m_PenSize = 1;
	m_BrushColor = RGB(0, 0, 0);
	m_PointBegin = CPoint(0, 0);
	m_PointEnd = CPoint(0, 0);
	m_LeftVertex = CPoint(0, 0);
	m_RightVertex = CPoint(0, 0);
	m_DrawType = DrawType::Curve;
	m_PenType = PenType::Pencil;
	mark = 0;
}

CGraphics_DrawView::~CGraphics_DrawView()
{
}

BOOL CGraphics_DrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphics_DrawView 绘图

void CGraphics_DrawView::OnDraw(CDC* /*pDC*/)
{
	CGraphics_DrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGraphics_DrawView 打印

BOOL CGraphics_DrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphics_DrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphics_DrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGraphics_DrawView 诊断

#ifdef _DEBUG
void CGraphics_DrawView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphics_DrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphics_DrawDoc* CGraphics_DrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphics_DrawDoc)));
	return (CGraphics_DrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphics_DrawView 消息处理程序


void CGraphics_DrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_LBUTTON) {
		CClientDC dc(this);
		CPen newPen, * oldPen, LightPen, BallPen,Pencil;
		LightPen.CreatePen(PS_SOLID, m_PenSize + 8, RGB(255, 255, 77));
		BallPen.CreatePen(PS_SOLID, m_PenSize + 3, m_PenColor);
		Pencil.CreatePen(PS_SOLID, m_PenSize, m_PenColor);
		newPen.CreatePen(PS_SOLID, m_PenSize, m_PenColor);
		oldPen = dc.SelectObject(&newPen);
		switch (m_PenType)
		{
		case PenType::Pencil:
			oldPen = dc.SelectObject(&Pencil);
			break;
		case PenType::BallPen:
			oldPen = dc.SelectObject(&BallPen);
			break;
		case PenType::LightPen:
			oldPen = dc.SelectObject(&LightPen);
			break;
		default:
			break;
		}
		switch (m_DrawType)
		{
		case DrawType::Line:
			dc.SetROP2(R2_NOTXORPEN);

			dc.MoveTo(m_PointBegin);
			dc.LineTo(m_PointEnd);

			dc.MoveTo(m_PointBegin);
			dc.LineTo(point);

			m_PointEnd = point;
			break;
		case DrawType::Rectangle:
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SelectStockObject(5);

			CRect rectP1(m_PointBegin, m_PointEnd);
			dc.Rectangle(rectP1);

			CRect rectP2(m_PointBegin, point);
			dc.Rectangle(rectP2);

			m_PointEnd = point;
			break;
		}
		case DrawType::Circle:
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SelectStockObject(PS_NULL);
			int length_1 = m_PointEnd.y - m_PointBegin.y;
			if (m_PointBegin.x < m_PointEnd.x) {
				m_PointEnd.x = m_PointBegin.x + abs(length_1);
			}
			else {
				m_PointEnd.x = m_PointBegin.x + abs(length_1);
			}
			CRect rectP1(m_PointBegin, m_PointEnd);
			dc.Ellipse(rectP1);
			int length_2 = point.y - m_PointBegin.y;
			if (point.x < m_PointEnd.x) {
				m_PointEnd.x = m_PointBegin.x + abs(length_2);
			}
			else {
				m_PointEnd.x = m_PointBegin.x + abs(length_2);
			}
			m_PointEnd.y = point.y;
			CRect rectP2(m_PointBegin, m_PointEnd);
			dc.Ellipse(rectP2);
			m_PointEnd = point;
			break;
		}
		case DrawType::Ellips:
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SelectStockObject(PS_NULL);
			CRect rectP1(m_PointBegin, m_PointEnd);
			dc.Ellipse(rectP1);
			CRect rectP2(m_PointBegin, point);
			dc.Ellipse(rectP2);
			m_PointEnd = point;
			break;
		}
		case DrawType::Curve:
		{
			m_PointBegin = m_PointEnd;
			m_PointEnd = point;
			dc.MoveTo(m_PointBegin);
			dc.LineTo(m_PointEnd);
			break;
		}
		case DrawType::RRectangle:
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SelectStockObject(PS_NULL);

			CRect rectP1(m_PointBegin, m_PointEnd);
			dc.RoundRect(rectP1, CPoint(15, 15));

			CRect rectP2(m_PointBegin, point);
			dc.RoundRect(rectP2, CPoint(15, 15));

			m_PointEnd = point;
			break;
		}
		case DrawType::Sector:
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SelectStockObject(PS_NULL);
			m_LeftVertex = m_PointBegin;
			m_RightVertex = m_PointEnd;
			int length_1 = m_RightVertex.y - m_LeftVertex.y;
			if (m_LeftVertex.x < m_RightVertex.x) {
				m_RightVertex.x = m_LeftVertex.x + abs(length_1);
			}
			else {
				m_RightVertex.x = m_LeftVertex.x + abs(length_1);
			}
			CRect rectP1(m_LeftVertex, m_RightVertex);
			dc.Pie(rectP1, m_PointBegin, m_PointEnd);
			int length_2 = point.y - m_LeftVertex.y;
			if (point.x < m_RightVertex.x) {
				m_RightVertex.x = m_LeftVertex.x + abs(length_2);
			}
			else {
				m_RightVertex.x = m_LeftVertex.x + abs(length_2);
			}
			m_RightVertex.y = point.y;
			CRect rectP2(m_LeftVertex, m_RightVertex);
			dc.Pie(rectP2, m_PointBegin, point);
			m_PointEnd = point;
			break;
		}
		case DrawType::Arc:
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SelectStockObject(PS_NULL);

			m_LeftVertex = m_PointBegin;
			m_RightVertex = m_PointEnd;
			int length_1 = m_RightVertex.y - m_LeftVertex.y;
			if (m_LeftVertex.x < m_RightVertex.x) {
				m_RightVertex.x = m_LeftVertex.x + abs(length_1);
			}
			else {
				m_RightVertex.x = m_LeftVertex.x + abs(length_1);
			}
			CRect rectP1(m_LeftVertex, m_RightVertex);
			dc.Arc(rectP1, m_PointBegin, m_PointEnd);
			int length_2 = point.y - m_LeftVertex.y;
			if (point.x < m_RightVertex.x) {
				m_RightVertex.x = m_LeftVertex.x + abs(length_2);
			}
			else {
				m_RightVertex.x = m_LeftVertex.x + abs(length_2);
			}
			m_RightVertex.y = point.y;
			CRect rectP2(m_LeftVertex, m_RightVertex);
			dc.Arc(rectP2, m_PointBegin, point);
			m_PointEnd = point;
			break;
		}
		case DrawType::Eraser:
		{
			COLORREF pColor = dc.GetBkColor();
			CPen newPen(PS_SOLID,m_PenSize+20,pColor);
			dc.SelectObject(newPen);
			m_PointBegin = m_PointEnd;
			m_PointEnd = point;
			dc.MoveTo(m_PointBegin);
			dc.LineTo(m_PointEnd);
			break;
		}
		default:
			break;
		}

		dc.SelectObject(oldPen);
	}
	CView::OnMouseMove(nFlags, point);
}


void CGraphics_DrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen newPen, * oldPen, LightPen, BallPen, Pencil;
	oldPen = dc.SelectObject(&newPen);
	LightPen.CreatePen(PS_SOLID, m_PenSize + 8, RGB(255, 255, 77));
	BallPen.CreatePen(PS_SOLID, m_PenSize + 3, m_PenColor);
	Pencil.CreatePen(PS_SOLID, m_PenSize, m_PenColor);
	newPen.CreatePen(PS_SOLID, m_PenSize, m_PenColor);
	oldPen = dc.SelectObject(&newPen);
	switch (m_PenType)
	{
	case PenType::Pencil:
		oldPen = dc.SelectObject(&Pencil);
		break;
	case PenType::BallPen:
		oldPen = dc.SelectObject(&BallPen);
		break;
	case PenType::LightPen:
		oldPen = dc.SelectObject(&LightPen);
		break;
	case PenType::Brush:
	{
		CClientDC dc(this);
		CBrush newBrush(m_BrushColor), * oldBrush;
		oldBrush = dc.SelectObject(&newBrush);
		dc.SelectObject(newBrush);
		dc.FloodFill(m_PointBegin.x, m_PointBegin.y, m_PenColor);
		dc.SelectObject(oldBrush);
	}
	default:
		break;
	}

	switch (m_DrawType)
	{
	case DrawType::Line:

		dc.MoveTo(m_PointBegin);
		dc.LineTo(point);

		break;
	case DrawType::Rectangle:
	{
		dc.SelectStockObject(PS_NULL);
		CRect rectP2(m_PointBegin, point);
		dc.Rectangle(rectP2);
		break;
	}
	case DrawType::RRectangle:
	{
		dc.SelectStockObject(PS_NULL);
		CRect rectP2(m_PointBegin, point);
		dc.RoundRect(rectP2, CPoint(15, 15));
		break;
	}
	case DrawType::Sector:
	{
		dc.SelectStockObject(PS_NULL);
		int length_2 = point.y - m_LeftVertex.y;
		if (point.x < m_RightVertex.x) {
			m_RightVertex.x = m_LeftVertex.x + abs(length_2);
		}
		else {
			m_RightVertex.x = m_LeftVertex.x + abs(length_2);
		}
		m_RightVertex.y = point.y;
		CRect rectP2(m_LeftVertex, m_RightVertex);
		dc.Pie(rectP2, m_PointBegin, point);
		break;
	}
	case DrawType::Arc:
	{
		dc.SelectStockObject(PS_NULL);
		int length_2 = point.y - m_LeftVertex.y;
		if (point.x < m_RightVertex.x) {
			m_RightVertex.x = m_LeftVertex.x + abs(length_2);
		}
		else {
			m_RightVertex.x = m_LeftVertex.x + abs(length_2);
		}
		m_RightVertex.y = point.y;
		CRect rectP2(m_LeftVertex, m_RightVertex);
		dc.Arc(rectP2, m_PointBegin, point);
		break;
	}
	case DrawType::Circle:
	{
		dc.SelectStockObject(PS_NULL);
		int length_2 = point.y - m_PointBegin.y;
		if (point.x < m_PointEnd.x) {
			m_PointEnd.x = m_PointBegin.x + abs(length_2);
		}
		else {
			m_PointEnd.x = m_PointBegin.x + abs(length_2);
		}
		m_PointEnd.y = point.y;
		CRect rectP2(m_PointBegin, m_PointEnd);
		dc.Ellipse(rectP2);
		break;
	}
	case DrawType::Ellips:
	{
		dc.SelectStockObject(PS_NULL);
		CRect rectP2(m_PointBegin, point);
		dc.Ellipse(rectP2);
		break;
	}
	case DrawType::Polyline:
		if (mark > 1) {
			dc.Polyline(m_ptArray, 2);

		}
		m_ptArray[0] = m_ptArray[1];
		break;
	case DrawType::Polygon:
		if (mark > 1) {
			dc.Polyline(m_ptArray, 2);

		}
		m_ptArray[0] = m_ptArray[1];
		break;
	default:
		break;
	}
	

	CView::OnLButtonUp(nFlags, point);
}


void CGraphics_DrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_PointBegin = m_PointEnd = point;
	
	switch (m_DrawType)
	{
	case DrawType::Polyline:
		mark++;
		if (mark > 0) {
			m_ptArray[1] = point;
		}
		break;
	case DrawType::Polygon:
		mark++;
		if (mark > 0) {
			m_ptArray[1] = point;
		}
		break;
	default:
		break;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CGraphics_DrawView::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Line;
}


void CGraphics_DrawView::OnDrawCurve()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Curve;
}


void CGraphics_DrawView::OnDrawRectangle()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Rectangle;
}


void CGraphics_DrawView::OnDrawRRectangle()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::RRectangle;
}


void CGraphics_DrawView::OnDrawArc()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Arc;
}


void CGraphics_DrawView::OnDrawEllips()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Ellips;
}


void CGraphics_DrawView::OnDrawCircle()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Circle;
}


void CGraphics_DrawView::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Polygon;
}




void CGraphics_DrawView::OnDrawSector()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Sector;
}


void CGraphics_DrawView::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	if (IDOK == dlg.DoModal()) {
		m_PenColor = dlg.GetColor();
	}
}


void CGraphics_DrawView::OnSetPenSize()
{
	// TODO: 在此添加命令处理程序代码
	CSetPenSizeDialog dlg;
	if (IDOK == dlg.DoModal()) {
		this->m_PenSize = dlg.m_PenSize;
	}

}


void CGraphics_DrawView::OnSetPencil()
{
	// TODO: 在此添加命令处理程序代码
	m_PenType = PenType::Pencil;
	if (m_DrawType == DrawType::Eraser)
		m_DrawType = DrawType::Curve;
}


void CGraphics_DrawView::OnSetEraser()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Eraser;
}


void CGraphics_DrawView::OnSetBallPen()
{
	// TODO: 在此添加命令处理程序代码
	m_PenType = PenType::BallPen;
	if (m_DrawType == DrawType::Eraser)
		m_DrawType = DrawType::Curve;
}


void CGraphics_DrawView::OnSetLightPen()
{
	// TODO: 在此添加命令处理程序代码
	m_PenType = PenType::LightPen;
	if (m_DrawType == DrawType::Eraser)
		m_DrawType = DrawType::Curve;
}


void CGraphics_DrawView::OnDrawPolyline()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DrawType::Polyline;
}


void CGraphics_DrawView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_DrawType == DrawType::Polygon)
		mark = 0;

	CView::OnLButtonDblClk(nFlags, point);
}


void CGraphics_DrawView::OnDrawBrush()
{
	// TODO: 在此添加命令处理程序代码
	m_PenType = PenType::Brush;
	m_DrawType = DrawType::Curve;
}


void CGraphics_DrawView::OnSetBrushColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	if (IDOK == dlg.DoModal()) {
		m_BrushColor = dlg.GetColor();
	}
}
