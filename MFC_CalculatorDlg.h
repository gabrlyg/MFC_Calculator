
// MFC_CalculatorDlg.h : 头文件
//

#pragma once


// CMFC_CalculatorDlg 对话框
class CMFC_CalculatorDlg : public CDialogEx
{
// 构造
public:
	CMFC_CalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 处理数字按钮的函数声明
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

	// 处理点的函数声明
	afx_msg void OnBnClickedButtonDot();

	// 处理根号的函数声明
	afx_msg void OnBnClickedButtonSqrt();

	// 处理AC按钮的函数声明
	afx_msg void OnBnClickedButtonAC();

	// 处理运算符按钮的函数声明
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

