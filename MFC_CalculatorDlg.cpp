
// MFC_CalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_Calculator.h"
#include "MFC_CalculatorDlg.h"
#include "afxdialogex.h"
#include "operate.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

wstring input1;			// ��¼ǰ������������
bool isEqu = false;		// false��ʾ֮ǰδ���µ���״̬, true��ʾ֮ǰ���µ���״̬
bool isMute = false;	// �Ƿ���

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFC_CalculatorDlg �Ի���



CMFC_CalculatorDlg::CMFC_CalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_CalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_ID_0, &CMFC_CalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(BTN_ID_1, &CMFC_CalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(BTN_ID_2, &CMFC_CalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(BTN_ID_3, &CMFC_CalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(BTN_ID_4, &CMFC_CalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(BTN_ID_5, &CMFC_CalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(BTN_ID_6, &CMFC_CalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(BTN_ID_7, &CMFC_CalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(BTN_ID_8, &CMFC_CalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(BTN_ID_9, &CMFC_CalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(BTN_ID_PLUS, &CMFC_CalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(BTN_ID_MINUS, &CMFC_CalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(BTN_ID_TIMES, &CMFC_CalculatorDlg::OnBnClickedButtonTimes)
	ON_BN_CLICKED(BTN_ID_OVER, &CMFC_CalculatorDlg::OnBnClickedButtonOver)
	ON_BN_CLICKED(BTN_ID_MOD, &CMFC_CalculatorDlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(BTN_ID_SQRT, &CMFC_CalculatorDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(BTN_ID_AC, &CMFC_CalculatorDlg::OnBnClickedButtonAC)
	ON_BN_CLICKED(BTN_ID_DOT, &CMFC_CalculatorDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(BTN_ID_EQUAL, &CMFC_CalculatorDlg::OnBnClickedButtonEqual)
	ON_WM_SETFOCUS()
	ON_COMMAND(IDR_MENU_FILE_EXIT, &CMFC_CalculatorDlg::OnMenuFileExit)
	ON_COMMAND(IDR_MENU_HELP_ABOUT, &CMFC_CalculatorDlg::OnMenuHelpAbout)
	ON_COMMAND(IDR_MENU_EDIT_MUTE, &CMFC_CalculatorDlg::OnMenuEditMute)
	ON_UPDATE_COMMAND_UI(IDR_MENU_EDIT_MUTE, &CMFC_CalculatorDlg::OnUpdateMenuEditMute)
END_MESSAGE_MAP()


// CMFC_CalculatorDlg ��Ϣ�������

BOOL CMFC_CalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ��ӡ��ļ����˵�
	CMenu m_Menu;
	m_Menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_Menu);

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CFont *m_Font;
	m_Font = new CFont;
	m_Font->CreateFont(80, 35, 0, 0, 100,
		FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("Segoe UI Bold"));
	CStatic* screen_hwnd_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_hwnd_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	screen_hwnd_main->SetFont(m_Font);
	screen_hwnd_main->SetWindowTextW(_T("0"));
	screen_hwnd_sub->SetWindowTextW(_T(""));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFC_CalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_CalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFC_CalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ְ�ť��������
void CMFC_CalculatorDlg::OnBnClickedButton0()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num0.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("0");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton1()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num1.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("1");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton2()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num2.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("2");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton3()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num3.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("3");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton4()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num4.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("4");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton5()
{	
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num5.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("5");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton6()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num6.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("6");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton7()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num7.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("7");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton8()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num8.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("8");
	Number(screen_main, screen_sub, input, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButton9()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\num9.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("9");
	Number(screen_main, screen_sub, input, input1, isEqu);
}

// �㰴ť��������
void CMFC_CalculatorDlg::OnBnClickedButtonDot()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\dot.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	Dot(screen_main, screen_sub, isEqu);
}

// ���Ű�ť��������
void CMFC_CalculatorDlg::OnBnClickedButtonSqrt()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\sqrt.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	Sqrt(screen_main, screen_sub, isEqu);
}

// AC��ť��������
void CMFC_CalculatorDlg::OnBnClickedButtonAC()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\clear.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	input1.clear();
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	Clear(screen_main, screen_sub, isEqu);
}

// �������ť��������
void CMFC_CalculatorDlg::OnBnClickedButtonPlus()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\plus.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input1 = _T("+");
	Operator(screen_main, screen_sub, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButtonMinus()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\minus.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input1 = _T("-");
	Operator(screen_main, screen_sub, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButtonTimes()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\times.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input1 = _T("*");
	Operator(screen_main, screen_sub, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButtonOver()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\over.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input1 = _T("/");
	Operator(screen_main, screen_sub, input1, isEqu);
}
void CMFC_CalculatorDlg::OnBnClickedButtonMod()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\mod.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input1 = _T("%");
	Operator(screen_main, screen_sub, input1, isEqu);
}

// �ȺŰ�ť��������
void CMFC_CalculatorDlg::OnBnClickedButtonEqual ()
{
	if (isMute == false)
	{
		PlaySound(_T("res\\Sound\\equal.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	isEqu = true;
	Equal(screen_main, screen_sub, input1, isEqu);
}

void CMFC_CalculatorDlg::OnMenuFileExit()
{
	DestroyWindow();
}


void CMFC_CalculatorDlg::OnMenuHelpAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg About;
	About.DoModal();
}

void CMFC_CalculatorDlg::OnMenuEditMute()
{
	isMute = !isMute;
}

void CMFC_CalculatorDlg::OnUpdateMenuEditMute(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(isMute);
}



