
// MFC_Calculator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_CalculatorApp: 
// �йش����ʵ�֣������ MFC_Calculator.cpp
//

class CMFC_CalculatorApp : public CWinApp
{
public:
	CMFC_CalculatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_CalculatorApp theApp;