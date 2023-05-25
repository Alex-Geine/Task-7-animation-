
// Task-7(animation)Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Task-7(animation).h"
#include "Task-7(animation)Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.14
#define ID_TIMER_1 1234154

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CTask7animationDlg



CTask7animationDlg::CTask7animationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASK7ANIMATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTask7animationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Graph, Pic);
	DDX_Control(pDX, IDC_EDIT1, freq);
	DDX_Control(pDX, IDC_EDIT2, phase);
	DDX_Control(pDX, IDC_CHECK1, check);
}

BEGIN_MESSAGE_MAP(CTask7animationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTask7animationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CTask7animationDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCLOSE, &CTask7animationDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// Обработчики сообщений CTask7animationDlg

BOOL CTask7animationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	SetTimer(ID_TIMER_1, 100, NULL);  
	Pic.friq = &freq;
	Pic.phase = &phase;
	freq.SetWindowTextW(L"150");
	phase.SetWindowTextW(L"100");


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTask7animationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTask7animationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTask7animationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//Нарисовать
void CTask7animationDlg::OnBnClickedOk()
{
	Pic.Invalidate(FALSE);
}

//Прибавить фазу
void CTask7animationDlg::OnBnClickedOk2()
{	
	Pic.phaseapd += 2 * PI / 360;
	if (Pic.phaseapd == 2 * PI)
		Pic.phaseapd = 0;
	Pic.Invalidate(FALSE);
}

//Закрыть
void CTask7animationDlg::OnBnClickedClose()
{
	this->OnCancel();	
}

//Обработчик таймера

afx_msg void CTask7animationDlg::OnTimer(UINT_PTR nIDEvent) {
	if (check.GetCheck()) {
		Pic.phaseapd += 2 * PI / 360;
		if (Pic.phaseapd == 2 * PI)
			Pic.phaseapd = 0;
		Pic.Invalidate(FALSE);
	}	
}