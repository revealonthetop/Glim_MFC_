// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "GLIM_REPORT.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include "GLIM_REPORTDlg.h"

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent), m_bShowRadius(FALSE)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 이미지 그리는 함수를 만들 것.

	// 창 크기 조절하기
	//MoveWindow(0, 0, 800, 480);

	//이미지 생성하기
	initImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (!m_Image.IsNull())
	{
		m_Image.Destroy();
	}

	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
	DrawInfo(dc);
}

void CDlgImage::initImage()
{
	CRect rect;
	GetClientRect(&rect);

	int nWidth = rect.Width();
	int nHeight = rect.Height();
	int nBpp = 8;

	if (!m_Image.IsNull())
	{
		m_Image.Destroy();
	}

	// 디버깅 코드 추가.
	HRESULT hr = m_Image.Create(nWidth, -nHeight, nBpp);
	if (FAILED(hr)) {
		MessageBox(_T("Failed to create image"), _T("Error"), MB_OK);
		return;
	}

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff , nWidth * nHeight);
}


void CDlgImage::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	lpMMI->ptMinTrackSize.x = 0;
	lpMMI->ptMinTrackSize.y = 0;
	lpMMI->ptMaxTrackSize.x = 0;
	lpMMI->ptMaxTrackSize.y = 0;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CDlgImage::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_Image.IsNull())
		m_Image.Destroy();
}
/* ======================
이미지 지우기
=====================*/

void CDlgImage::ClearImage()
{
	if (!m_Image != NULL)
		m_Image.Destroy();
}
/*=======================
이미지 업데이트
=======================*/
void CDlgImage::UpdateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

/*==========================
초기화면 이미지
=========================*/
void CDlgImage::CreateImage()
{
	GetClientRect(&m_rcImage);
	ClearImage();

	const int nBPP = 8;

	// 디버깅 정보 출력
	TRACE("Width: %d, Height: %d, nBPP: %d\n", m_rcImage.Width(), m_rcImage.Height(), nBPP);


	if (!m_Image.IsNull())
	{
		m_Image.Destroy();
	}
	//이미지 생성하기
	HRESULT hr = m_Image.Create(m_rcImage.Width(), -m_rcImage.Height(), nBPP);

	if (m_Image.IsNull())
	{
		//AfxMessageBox("Image creation failed!");
		return;
	}

	if (nBPP == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

		m_Image.SetColorTable(0, sizeof(rgb) / sizeof(rgb[0]), rgb);
	}
}

/*==================================
원 그리기 n값 받아서.
=================================*/

void CDlgImage::DrawCircle(int n)
{
	CRect rect;
	GetClientRect(&rect);

	for (int i = 0; i < n ; ++i) 
	{
		ClearImage();
		
		int nBpp = 8;

		if (!m_Image.IsNull())
		{
			m_Image.Destroy();
		}

		m_Image.Create(rect.Width(), rect.Height(), nBpp);

		if (nBpp == 8) {
			static RGBQUAD rgb[256];
			for (int j = 0; j < 256; j++) {
				rgb[j].rgbRed = rgb[j].rgbGreen = rgb[j].rgbBlue = j;
			}
			m_Image.SetColorTable(0, 256, rgb);
		}


		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		int nPitch = m_Image.GetPitch();

		int nRadius = rand() % (rect.Width() / 4);
		int nX = rand() % (rect.Width() - nRadius * 2) + nRadius;
		int nY = rand() % (rect.Height() - nRadius * 2) + nRadius;

		HDC hdc = m_Image.GetDC();
		HBRUSH brush = CreateSolidBrush(RGB(128, 128, 128));

		SelectObject(hdc, brush);

		Ellipse(hdc, nX - nRadius, nY - nRadius, nX + nRadius, nY + nRadius); // 수정된 부분

		UpdateDisplay();

		m_Image.ReleaseDC();

		SaveImage(m_Image, i);

		DeleteObject(brush);

		Sleep(200);
	}

}

/* ====================
이미지 저장
==================*/
void CDlgImage::SaveImage(CImage& image, int index)
{
	CString filePath;
	filePath.Format(_T(".\\imgs\\circle_%d.bmp"), index); // 이미지 경로 지정
	image.Save(filePath);
}
/* ====================
원 정보 불러 오기. 
==================*/


void CDlgImage::GetCircleInfo()
{
	ClearImage();

	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_imagePath = dlg.GetPathName();
		LoadAndDisplayImage();
	}

	GetInfo();
}

void CDlgImage::LoadAndDisplayImage()
{
	if (FAILED(m_Image.Load(m_imagePath)))
	{
		AfxMessageBox(_T("이미지를 불러오지 못했습니다."));
		return;
	}

	UpdateDisplay();
	// 디버깅 끝나고 없애줄것.
	return;
}

/* ====================
원 정보값 수정하는 함수
==================*/

void CDlgImage::GetInfo()
{
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nPitch = m_Image.GetPitch();

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	int nMinX = 0x7FFFFFFF; // signed int 최대값
	int nMinY = 0x7FFFFFFF; // signed int 최대값
	int nMaxX = 0x80000000; // signed int 최소값
	int nMaxY = 0x80000000; // signed int 최소값

	for (int y = 0; y < m_Image.GetHeight(); y++)
	{
		for (int x = 0; x < m_Image.GetWidth(); x++)
		{
			// 0x00 ~ 0x7F: Off
			// 0x80 ~ 0xFF: On
			if (fm[y * nPitch + x] >= 0x80)
			{
				nSumX += x;
				nSumY += y;
				nCount++;

				if (nMinX > x)	nMinX = x;
				if (nMinY > y)	nMinY = y;
				if (nMaxX < x)	nMaxX = x;
				if (nMaxY < y)	nMaxY = y;
			}
		}
	}

	m_dCircleRadius = sqrt(pow(m_dCenterX - m_nMinX, 2) + pow(m_dCenterY - m_nMinY, 2));
	m_dCenterX = (double)nSumX / nCount;
	m_dCenterY = (double)nSumY / nCount;
	m_nMinX = nMinX;
	m_nMinY = nMinY;
	m_nMaxX = nMaxX;
	m_nMaxY = nMaxY;

	m_bIsData = TRUE;
	m_bShowRadius = TRUE;

	Invalidate(FALSE);
}
//원그릴때 썼던 함수. [네모 만들고 원모양의 true/false 판별]
//BOOL CDlgImage::IsInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius)
//{
//	int dx = x - nCenterX;
//	int dy = y - nCenterY;
//	int distSqare = dx * dx + dy * dy;
//
//	return distSqare <= (nRadius * nRadius);
//};

//void CDlgImage::DrawImage(CDC& dc)
//{
//	m_Image.Draw(dc, m_rcImage);
//};

/* ====================
원 정보 관련 그림 그리기
==================*/
void CDlgImage::DrawInfo(CDC& dc)
{
	if (!m_bIsData)
		return;
	
	ClearImage();

	HPEN hPenYellow = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	HPEN hPenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));			// 빨간 펜~
	HPEN hPenWhite = CreatePen(PS_DOT, 1, RGB(255, 255, 255));	// 흰색 점선 펜.
	HPEN hPenGreen = CreatePen(PS_DASHDOT, 1, RGB(0, 255, 0));		// 녹색 펜.

	HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));			// 빨간 브러시 		
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN hOldPen = (HPEN)dc.SelectObject(hPenYellow);
	HBRUSH hOldBrush = (HBRUSH)dc.SelectObject(hBrush);

	// 배경을 투명하게 설정
	int oldBkMode = dc.SetBkMode(TRANSPARENT);

	if (m_bShowRadius) 
	{
		//노란색 타원 그리기
		dc.Ellipse(m_nMinX, m_nMinY, m_nMaxX, m_nMaxY);

		// 흰색 점선 네모 그리기
		dc.SelectObject(hPenWhite);
		// 상단 변
		dc.MoveTo(-1, -1);
		dc.LineTo((int)m_dCenterX, -1);
		// 우측 변
		dc.MoveTo((int)m_dCenterX, -1);
		dc.LineTo((int)m_dCenterX, (int)m_dCenterY);
		// 하단 변
		dc.MoveTo((int)m_dCenterX, (int)m_dCenterY);
		dc.LineTo(0, (int)m_dCenterY);
		// 좌측 변
		dc.MoveTo(-1, (int)m_dCenterY);
		dc.LineTo(-1, -1);

		//빨간 브러시 변경
		dc.SelectObject(hPenRed);
		dc.SelectObject(hBrushRed);


		// 중심점부터 원의 끝부분까지 빨간색 선 그리기
		dc.MoveTo((int)round(m_dCenterX), (int)round(m_dCenterY));
		dc.LineTo((int)round(m_dCenterX), m_nMaxY);

		//녹색 선 그리기
		dc.SelectObject(hPenGreen);

		dc.MoveTo((int)round(m_dCenterX), m_nMaxY);
		dc.LineTo((int)round(m_dCenterX) + 100, m_nMaxY);

		// 반지름 길이를 녹색 글씨로 쓰기
		dc.SelectObject(hPenGreen);
		CString radiusText;
		radiusText.Format(_T("radius == %.2f"), m_dCircleRadius);

		// 텍스트 위치 조정
		int textX = (int)round(m_dCenterX + 100); // 중심점에서 오른쪽으로 10만큼 이동
		int textY = (int)round(m_nMaxY); // 선의 중간 부분


		// 녹색 글씨 쓰기
		dc.SetTextColor(RGB(0, 255, 0)); // 텍스트 색상 녹색으로 설정
		dc.SetBkMode(TRANSPARENT); // 텍스트 배경 투명 모드 설정
		dc.TextOutW(textX, textY, radiusText);
	}



	// 원래의 브러시와 펜으로 복구
	dc.SelectObject(hOldBrush);
	dc.SelectObject(hOldPen);

	dc.SetBkMode(oldBkMode);

	// 사용한 펜과 브러시 삭제
	DeleteObject(hPenYellow);
	DeleteObject(hPenRed);
	DeleteObject(hPenWhite);
	DeleteObject(hPenGreen);

}

CString CDlgImage::GetCoorditate()
{
	CString coordinateString;
	coordinateString.Format(_T(" %d , %d "),(int)m_dCenterX, (int)m_dCenterY);
	return coordinateString;
};