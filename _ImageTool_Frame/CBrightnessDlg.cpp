// CBrightnessDlg.cpp: 구현 파일
//

//#include "pch.h"
#include "stdafx.h"
#include "ImageTool.h"
#include "CBrightnessDlg.h"
#include "afxdialogex.h"


// CBrightnessDlg 대화 상자

IMPLEMENT_DYNAMIC(CBrightnessDlg, CDialogEx);

CBrightnessDlg::CBrightnessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BRIGHTNESS, pParent)
	, m_nBrightness(0)
{

}

CBrightnessDlg::~CBrightnessDlg()
{
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRIGHTNESS_SLIDER, m_sliderBrightness);
	//DDX_Control(pDX, IDC_BRIGHTNESS_EDIT, m_nBrightness);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialogEx)
END_MESSAGE_MAP()


// CBrightnessDlg 메시지 처리기


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderBrightness.SetRange(-255, 255);
	m_sliderBrightness.SetTicFreq(32);
	m_sliderBrightness.SetPageSize(32);

	return TRUE;
}
