#pragma once
#include "afxdialogex.h"



// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();


	CWnd* m_pParent;
	CImage m_Image;

private:
	CRect m_rcImage;
	CString m_imagePath;

	BOOL m_bIsData;
	BOOL m_bShowRadius;

	double m_dCenterX=0.0;	// X 중심
	double m_dCenterY=0.0;	// Y 중심
	double m_dCircleRadius = 0.0;

	int m_nMinX=0;			// 분포범위
	int m_nMinY=0;			// 분포범위
	int m_nMaxX=0;			// 분포범위
	int m_nMaxY=0;			// 분포범위

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	void initImage();
	void CreateImage();
	void DrawCircle(int n);
	void SaveImage(CImage& image, int index);
	void LoadAndDisplayImage();
	void GetCircleInfo();
	void GetInfo();
	void ClearImage();
	void UpdateDisplay();

	void DrawInfo(CDC& dc);

	CString GetCoorditate();

	afx_msg void OnDestroy();
};
