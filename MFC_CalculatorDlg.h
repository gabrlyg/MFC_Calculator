
// MFC_CalculatorDlg.h : ͷ�ļ�
//

#pragma once


// CMFC_CalculatorDlg �Ի���
class CMFC_CalculatorDlg : public CDialogEx
{
// ����
public:
	CMFC_CalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �������ְ�ť�ĺ�������
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();

	// �����ĺ�������
	afx_msg void OnBnClickedButtonDot();

	// ������ŵĺ�������
	afx_msg void OnBnClickedButtonSqrt();

	// ����AC��ť�ĺ�������
	afx_msg void OnBnClickedButtonAC();

	// �����������ť�ĺ�������
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonTimes();
	afx_msg void OnBnClickedButtonOver();
	afx_msg void OnBnClickedButtonMod();

	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnMenuFileExit();
	afx_msg void OnMenuHelpAbout();
	afx_msg void OnUpdateMenuEditMute(CCmdUI *pCmdUI);
	afx_msg void OnMenuEditMute();
};

