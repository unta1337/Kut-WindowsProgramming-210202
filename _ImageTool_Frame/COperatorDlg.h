﻿#pragma once


// COperatorDlg 대화 상자

class COperatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COperatorDlg)

public:
	COperatorDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~COperatorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPERATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboImage1;
	CComboBox m_comboImage2;
	int m_nFunction;
	virtual BOOL OnInitDialog();
};
