﻿
// ImageToolDoc.cpp : CImageToolDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"
#include "FileNewDlg.h"

#include <propkey.h>

#include "IppImage/IppImage.h" 
#include "IppImage/IppConvert.h" 
#include "IppImage/IppEnhance.h" 

#include "CBrightnessDlg.h"
#include "CContrastDlg.h"
#include "COperatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageToolDoc

IMPLEMENT_DYNCREATE(CImageToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageToolDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CImageToolDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CImageToolDoc::OnEditCopy)
	ON_COMMAND(ID_IMAGE_INVERSE, &CImageToolDoc::OnImageInverse)
	ON_COMMAND(ID_32780, &CImageToolDoc::OnBrightness)
	ON_COMMAND(ID_OPERATOR, &CImageToolDoc::OnOperator)
	ON_COMMAND(ID_32783, &CImageToolDoc::OnContrast)
END_MESSAGE_MAP()


// CImageToolDoc 생성/소멸

CImageToolDoc::CImageToolDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageToolDoc::~CImageToolDoc()
{
}

BOOL CImageToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL ret = TRUE;

	if (theApp.m_pNewDib == NULL)
	{
		CFileNewDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nType == 0) // 그레이스케일 비트맵
				ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
			else // 트루컬러 비트맵
				ret = m_Dib.CreateRgbBitmap(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return ret;
}




// CImageToolDoc serialization

void CImageToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageToolDoc 진단

#ifdef _DEBUG
void CImageToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageToolDoc 명령


BOOL CImageToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	BOOL res = m_Dib.Load(CT2A(lpszPathName));
	if (res)
		AfxPrintInfo(_T("[파일 열기] 파일 경로: %s, 가로 크기: %d픽셀, 세로 크기: %d픽셀, 색상수: %d"),
			lpszPathName, m_Dib.GetWidth(), m_Dib.GetHeight(), 0x01 << m_Dib.GetBitCount());

	return res;
}


BOOL CImageToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_Dib.Save(CT2A(lpszPathName));
}


void CImageToolDoc::OnWindowDuplicate()
{
	AfxNewBitmap(m_Dib);
}


void CImageToolDoc::OnEditCopy()
{
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
}


void CImageToolDoc::OnImageInverse()
{
	IppDib dib;

	IppByteImage bImg;
	IppRgbImage rgbImg;

	switch (m_Dib.GetBitCount())
	{
	case 8:
		IppDibToImage(m_Dib, bImg);
		IppInverse(bImg);
		IppImageToDib(bImg, dib);
		break;
	case 24:
		IppDibToImage(m_Dib, rgbImg);
		IppInverse(rgbImg);
		IppImageToDib(rgbImg, dib);
		break;
	default:
		break;
	}

	// Dib 영상 출력.
	AfxPrintInfo(_T("[반전] 입력 영상: %s"), GetTitle());
	AfxNewBitmap(dib);
}


void CImageToolDoc::OnBrightness()
{
	CBrightnessDlg dlg;

	IppDib dib;

	IppByteImage bImg;
	IppRgbImage rgbImg;

	if (dlg.DoModal() == IDOK)
	{
		switch (m_Dib.GetBitCount())
		{
		case 8:
			IppDibToImage(m_Dib, bImg);
			IppBrightness(bImg, dlg.m_nBrightness);
			IppImageToDib(bImg, dib);
			break;
		case 24:
			IppDibToImage(m_Dib, rgbImg);
			IppBrightness(rgbImg, dlg.m_nBrightness);
			IppImageToDib(rgbImg, dib);
			break;
		default:
			break;
		}
	}

	AfxPrintInfo(_T("[밝기 조절] 입력 영상: %s, 밝기: %d"), GetTitle(), dlg.m_nBrightness);
	AfxNewBitmap(dib);
}


void CImageToolDoc::OnContrast()
{
	CContrastDlg dlg;

	IppDib dib;

	IppByteImage bImg;
	IppRgbImage rgbImg;

	if (dlg.DoModal() == IDOK)
	{
		switch (m_Dib.GetBitCount())
		{
		case 8:
			IppDibToImage(m_Dib, bImg);
			IppContrast(bImg, dlg.m_nContrast);
			IppImageToDib(bImg, dib);
			break;
		case 24:
			IppDibToImage(m_Dib, rgbImg);
			IppContrast(rgbImg, dlg.m_nContrast);
			IppImageToDib(rgbImg, dib);
			break;
		default:
			break;
		}
	}

	AfxPrintInfo(_T("[명암비 조절] 입력 영상: %s, 밝기: %d"), GetTitle(), dlg.m_nContrast);
	AfxNewBitmap(dib);
}


void CImageToolDoc::OnOperator()
{
	COperatorDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CImageToolDoc* pDoc1 = (CImageToolDoc*)dlg.m_pDoc1;
		CImageToolDoc* pDoc2 = (CImageToolDoc*)dlg.m_pDoc2;

		IppByteImage img1;
		IppByteImage img2;

		IppDibToImage(pDoc1->m_Dib, img1);
		IppDibToImage(pDoc2->m_Dib, img2);

		IppByteImage img3;

		bool ret = false;

		switch (dlg.m_nFunction)
		{
		case 0: ret = IppOperator(img1, img2, img3, &IppAddOp);  break;
		case 1: ret = IppOperator(img1, img2, img3, &IppSubOp);  break;
		case 2: ret = IppOperator(img1, img2, img3, &IppAndOp);  break;
		case 3: ret = IppOperator(img1, img2, img3, &IppXorOp);  break;
		}

		if (ret)
		{
			IppDib dib;
			IppImageToDib(img3, dib);

			TCHAR* op[] = { _T("덧셈"), _T("뺄셈"), _T("논리곱"), _T("배타적 논리합") };
			AfxPrintInfo(_T("[이미지 연산] [%s] 이미지 이름 #1: %s, 이미지 이름 #2: %s"), 
				op[dlg.m_nFunction], pDoc1->GetTitle(), pDoc2->GetTitle());
			AfxNewBitmap(dib);
		}
		else
			AfxMessageBox(_T("올바르지 않은 옵션입니다!"));
	}
}
