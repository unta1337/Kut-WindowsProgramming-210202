﻿// COperatorDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ImageTool.h"
#include "COperatorDlg.h"
#include "afxdialogex.h"
#include "ImageToolDoc.h"

// COperatorDlg 대화 상자

IMPLEMENT_DYNAMIC(COperatorDlg, CDialogEx)

COperatorDlg::COperatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPERATOR, pParent)
	, m_nFunction(0), m_pDoc1(NULL), m_pDoc2(NULL)
{

}

COperatorDlg::~COperatorDlg()
{
}

void COperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE1, m_comboImage1);
	DDX_Control(pDX, IDC_COMBO_IMAGE2, m_comboImage2);
	DDX_Radio(pDX, IDC_FUNCTION1, m_nFunction);
}


BEGIN_MESSAGE_MAP(COperatorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COperatorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COperatorDlg 메시지 처리기


BOOL COperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int nIndex = 0;
	CString strTitle;

	CImageToolApp* pApp = (CImageToolApp*)AfxGetApp();
	POSITION pos = pApp->m_pImageDocTemplate->GetFirstDocPosition();

	while (pos != NULL)
	{
		CImageToolDoc* pDoc = (CImageToolDoc*)pApp->m_pImageDocTemplate->GetNextDoc(pos);
		if (pDoc->m_Dib.GetBitCount() != 8)
			continue;;

		strTitle = pDoc->GetTitle();

		m_comboImage1.InsertString(nIndex, strTitle);
		m_comboImage2.InsertString(nIndex, strTitle);

		m_comboImage1.SetItemDataPtr(nIndex, (void*)pDoc);
		m_comboImage2.SetItemDataPtr(nIndex, (void*)pDoc);

		nIndex++;
	}

	m_comboImage1.SetCurSel(0);
	m_comboImage2.SetCurSel(0);
	if (nIndex > 1) m_comboImage2.SetCurSel(1);

	return TRUE;
}


void COperatorDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDoc1 = (CImageToolDoc*)m_comboImage1.GetItemDataPtr(m_comboImage1.GetCurSel());
	m_pDoc2 = (CImageToolDoc*)m_comboImage1.GetItemDataPtr(m_comboImage1.GetCurSel());

	CDialogEx::OnOK();
}
