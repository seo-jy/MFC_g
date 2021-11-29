
// MFC_gView.h: CMFCgView 클래스의 인터페이스
//

#pragma once


class CMFCgView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCgView() noexcept;
	DECLARE_DYNCREATE(CMFCgView)

// 특성입니다.
public:
	CMFCgDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int x;
	int count;
	int y;
	int w;
	int z;
	int step;
	int m_winright;
	int m_winbottom;
	int flag;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC_gView.cpp의 디버그 버전
inline CMFCgDoc* CMFCgView::GetDocument() const
   { return reinterpret_cast<CMFCgDoc*>(m_pDocument); }
#endif

