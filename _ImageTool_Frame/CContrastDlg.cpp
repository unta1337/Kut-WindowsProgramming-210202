// CContrastDlg.cpp: 구현 파일
//

//#include "pch.h"
#include "stdafx.h"
#include "ImageTool.h"
#include "CContrastDlg.h"
#include "afxdialogex.h"


// CContrastDlg 대화 상자

IMPLEMENT_DYNAMIC(CContrastDlg, CDialogEx)

CContrastDlg::CContrastDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTRAST, pParent)
	, m_nContrast(0)
{

}

CContrastDlg::~CContrastDlg()
{
}

void CContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
	DDX_Text(pDX, IDC_CONTRAST_EDIT, m_nContrast);
}


BEGIN_MESSAGE_MAP(CContrastDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_CONTRAST_EDIT, &CContrastDlg::OnEnChangeContrastEdit)
END_MESSAGE_MAP()


// CContrastDlg 메시지 처리기


BOOL CContrastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderContrast.SetRange(-255, 255);
	m_sliderContrast.SetTicFreq(32);
	m_sliderContrast.SetPageSize(32);

	return TRUE;
}


void CContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// 밝기 조절 슬라이드바에서 발생한 WM_HSCROLL 메시지 처리
	if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nContrast = m_sliderContrast.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CContrastDlg::OnEnChangeContrastEdit()
{
	UpdateData(TRUE);
	m_sliderContrast.SetPos(m_nContrast);
}
