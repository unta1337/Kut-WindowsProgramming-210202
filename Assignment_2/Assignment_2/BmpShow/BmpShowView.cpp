
// BmpShowView.cpp: CBmpShowView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BmpShow.h"
#endif

#include "BmpShowDoc.h"
#include "BmpShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBmpShowView

IMPLEMENT_DYNCREATE(CBmpShowView, CView)

BEGIN_MESSAGE_MAP(CBmpShowView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_NCLBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CBmpShowView 생성/소멸

CBmpShowView::CBmpShowView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CBmpShowView::~CBmpShowView()
{
}

BOOL CBmpShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBmpShowView 그리기

void CBmpShowView::OnDraw(CDC* /*pDC*/)
{
	CBmpShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CBmpShowView 인쇄

BOOL CBmpShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBmpShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBmpShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBmpShowView 진단

#ifdef _DEBUG
void CBmpShowView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpShowDoc* CBmpShowView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpShowDoc)));
	return (CBmpShowDoc*)m_pDocument;
}
#endif //_DEBUG


// CBmpShowView 메시지 처리기


void CBmpShowView::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnNcLButtonDown(nHitTest, point);
}

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')

void CBmpShowView::OnLButtonDown(UINT nFlags, CPoint point)
{
	FILE* fpKSY2020136018 = NULL;
	fopen_s(&fpKSY2020136018, "./res/lenna.bmp", "rb");

	if (!fpKSY2020136018)
		return;

	BITMAPFILEHEADER bmfhKSY2020136018;
	BITMAPINFOHEADER bmihKSY2020136018;

	if (fread(&bmfhKSY2020136018, sizeof(BITMAPFILEHEADER), 1, fpKSY2020136018) != 1) {
		fclose(fpKSY2020136018);
		return; 
	} 

	if (bmfhKSY2020136018.bfType != DIB_HEADER_MARKER) {
		fclose(fpKSY2020136018);
		return;
	}

	if (fread(&bmihKSY2020136018, sizeof(BITMAPINFOHEADER), 1, fpKSY2020136018) != 1) {
		fclose(fpKSY2020136018);
		return;
	}

	LONG nWidthKSY2020136018 = bmihKSY2020136018.biWidth;
	LONG nHeightKSY2020136018 = bmihKSY2020136018.biHeight;
	WORD nBitCountKSY2020136018 = bmihKSY2020136018.biBitCount; 

	DWORD dwWidthStepKSY2020136018 = (DWORD)((nWidthKSY2020136018 * nBitCountKSY2020136018 / 8 + 3) & ~3);
	DWORD dwSizeImageKSY2020136018 = nHeightKSY2020136018 * dwWidthStepKSY2020136018; 

	DWORD dwDibSizeKSY2020136018;
	if (nBitCountKSY2020136018 == 24)
		dwDibSizeKSY2020136018 = sizeof(BITMAPINFOHEADER) + dwSizeImageKSY2020136018;
	else
		dwDibSizeKSY2020136018 = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << nBitCountKSY2020136018) + dwSizeImageKSY2020136018;

	BYTE* pDibKSY2020136018 = new BYTE[dwDibSizeKSY2020136018]; 

	if (pDibKSY2020136018 == NULL) { 
		fclose(fpKSY2020136018);
		return; 
	} 

	fseek(fpKSY2020136018, sizeof(BITMAPFILEHEADER), SEEK_SET);
	if (fread(pDibKSY2020136018, sizeof(BYTE), dwDibSizeKSY2020136018, fpKSY2020136018) != dwDibSizeKSY2020136018)
	{
		delete[] pDibKSY2020136018;
		pDibKSY2020136018 = NULL;
		fclose(fpKSY2020136018);
		return;
	}

	LPVOID lpvBitsKSY2020136018;
	if (nBitCountKSY2020136018 == 24)
		lpvBitsKSY2020136018 = pDibKSY2020136018 + sizeof(BITMAPINFOHEADER);
	else 
		lpvBitsKSY2020136018 = pDibKSY2020136018 + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << nBitCountKSY2020136018);

	CClientDC dcKSY2020136018(this);
	::SetDIBitsToDevice(dcKSY2020136018.m_hDC, point.x, point.y, nWidthKSY2020136018, nHeightKSY2020136018, 0, 0, 0, nHeightKSY2020136018, lpvBitsKSY2020136018, (BITMAPINFO*)pDibKSY2020136018, DIB_RGB_COLORS); 

	delete[] pDibKSY2020136018;
	fclose(fpKSY2020136018);

	CView::OnLButtonDown(nFlags, point);
}
