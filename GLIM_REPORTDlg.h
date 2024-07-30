﻿
// GLIM_REPORTDlg.h: 헤더 파일
//
#include "CDlgImage.h"

#pragma once


// CGLIMREPORTDlg 대화 상자
class CGLIMREPORTDlg : public CDialogEx
{
// 생성입니다.			// 원개수
public:
	CGLIMREPORTDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_REPORT_DIALOG };
#endif

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
		

// 구현입니다.
protected:
	HICON m_hIcon;

	CString CoordinateValue; 
	CStatic m_staticText;    

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnMakecircle();
	afx_msg void OnBnClickedBtnAnalyze();

	void SetCoordinates(const CString& coordinates);
private:
	int m_nNum;
	int Yoffset = 70;
public:

};
