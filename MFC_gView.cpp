
// MFC_gView.cpp: CMFCgView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_g.h"
#endif

#include "MFC_gDoc.h"
#include "MFC_gView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCgView

IMPLEMENT_DYNCREATE(CMFCgView, CView)

BEGIN_MESSAGE_MAP(CMFCgView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
//	ON_WM_TIMER()
//ON_WM_SIZE()
ON_WM_SIZE()
ON_WM_TIMER()
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCgView 생성/소멸

CMFCgView::CMFCgView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	x = 0;
	y = 0;
	w = 720;
	z = 20;
	step = 10;
	count = 0;
	flag = 0;
}

CMFCgView::~CMFCgView()
{
}

BOOL CMFCgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCgView 그리기

void CMFCgView::OnDraw(CDC* pDC)
{
	CMFCgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	/*
	CDC mdc;
	CBitmap s_bit, * oldbit;
	mdc.CreateCompatibleDC(pDC);
	s_bit.LoadBitmap(IDB_BITMAP3);
	oldbit = mdc.SelectObject(&s_bit);
	pDC->BitBlt(x + m_winright, y + m_winbottom, 100, 100, &mdc, 0, 0, SRCCOPY);
	mdc.SelectObject(oldbit);
	s_bit.DeleteObject();
	mdc.DeleteDC();
	
	CClientDC dc(this);
	CRect rect;
	GetClientRect(rect);
	CBrush bs, * pbs; 
	CPen pen, * oldpen; 
	bs.CreateStockObject(NULL_BRUSH); //투명 사각형
	pen.CreatePen(PS_NULL, 0, RGB(255, 255, 255)); //선
	pbs = dc.SelectObject(&bs);
	oldpen = dc.SelectObject(&pen);
	dc.Rectangle(x + m_winright + 10, y + m_winbottom, x + m_winright + 35, y + m_winbottom + 50);
	dc.SelectObject(pbs);
	dc.SelectObject(oldpen);
	pen.DeleteObject();

	if (x + m_winright + 10 > m_winright && x >= m_winright)
		x = x * -1;
	else if (x + m_winright + 10 <= m_winright && x <= -m_winright)
		x = x * -1;
	*/
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CString str;
	str.Format(_T("점수 = %d"), count); //str에 저장
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW(10, 10, str);  //100,0에 str 출력
	//dc.Ellipse(w + 25, z + 25, w - 25, z - 25);
	//SetTimer(0, 10, NULL);

	//비트맵 이미지
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP3);

	CBitmap* pOldBmp = NULL;
	pOldBmp = memDC.SelectObject(&bmp);

	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);

	pDC->TransparentBlt(x + m_winright, y + m_winbottom, bmpInfo.bmWidth, bmpInfo.bmHeight, &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));//비트맵 이미지의 흰배경 삭제

	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	bmp.DeleteObject();

	//투명한 사각형 그리기
	CBrush bs1, * pbs1;
	CPen pen, * oldpen;
	bs1.CreateStockObject(NULL_BRUSH); //투명 사각형
	pen.CreatePen(PS_NULL, 0, RGB(255, 255, 255)); // 흰색선
	pbs1 = dc.SelectObject(&bs1);
	oldpen = dc.SelectObject(&pen);
	dc.Rectangle(x + m_winright + 10, y + m_winbottom, x + m_winright + 35, y + m_winbottom + 50);
	dc.SelectObject(pbs1);
	dc.SelectObject(oldpen);
	pen.DeleteObject();

	if (x + m_winright > m_winright && x > m_winright)
		x = x * -1;
	else if (x + m_winright < m_winright && x < -m_winright)
		x = x * -1;

}

//CMFCgView 인쇄
BOOL CMFCgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCgView 진단

#ifdef _DEBUG
void CMFCgView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCgDoc* CMFCgView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCgDoc)));
	return (CMFCgDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCgView 메시지 처리기


void CMFCgView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_RIGHT)
		x += step;
	if (nChar == VK_LEFT)
		x -= step;
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCgView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_winright = cx / 2;
	m_winbottom = cy - 50;
}


void CMFCgView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	//z += 10;
	//Invalidate();
	CView::OnTimer(nIDEvent);
}
