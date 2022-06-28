
// Graphics_DrawView.h: CGraphics_DrawView 类的接口
//

#pragma once
#include<afxtempl.h>

class CGraphics_DrawView : public CView
{
protected: // 仅从序列化创建
	CGraphics_DrawView() noexcept;
	DECLARE_DYNCREATE(CGraphics_DrawView)

// 特性
public:
	CGraphics_DrawDoc* GetDocument() const;

	int m_PenSize;
	COLORREF m_PenColor, m_BrushColor;
	CPoint m_PointBegin, m_PointEnd;
	CPoint m_LeftVertex, m_RightVertex;
	CPoint m_ptArray[2];
	int mark;

	enum DrawType		//画图形类型
	{
		Line,		//画线
		Curve,		//画曲线
		Rectangle,  //画矩形
		RRectangle, //画圆角矩形
		Arc,		//画圆弧
		Ellips,		//画椭圆
		Circle,	    //画圆
		Polygon,	//画多边形
		Polyline,   //画折线
		Sector,     //画扇形
		Eraser,		//画图的橡皮擦
		
	}m_DrawType;

	enum PenType {
		Pencil,	    //铅笔
		BallPen,	//圆珠笔
		LightPen,    //荧光笔
		Brush       //画刷
	}m_PenType;
// 操作
public:


// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphics_DrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawCurve();
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawRRectangle();
	afx_msg void OnDrawArc();
	afx_msg void OnDrawEllips();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawPolygon();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawSector();
	afx_msg void OnSetColor();
	afx_msg void OnSetPenSize();
	afx_msg void OnSetPencil();
	afx_msg void OnSetEraser();
	afx_msg void OnSetBallPen();
	afx_msg void OnSetLightPen();
	afx_msg void OnDrawPolyline();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawBrush();
	afx_msg void OnSetBrushColor();
};

#ifndef _DEBUG  // Graphics_DrawView.cpp 中的调试版本
inline CGraphics_DrawDoc* CGraphics_DrawView::GetDocument() const
   { return reinterpret_cast<CGraphics_DrawDoc*>(m_pDocument); }
#endif

