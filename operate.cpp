#include "operate.h"
#include "stdafx.h"
#include <cmath>
#include <mmsystem.h>

// 处理数字
void Number(CStatic*, CStatic*, wstring, wstring, bool&);

// 处理符号
void Operator(CStatic*, CStatic*, wstring, bool&);

// 计算结果
void Equal(CStatic*, CStatic*, wstring, bool&);

// 处理小数点
void Dot(CStatic*, CStatic*, bool&);

// 处理根号
void Sqrt(CStatic*, CStatic*, bool&);

// 清零
void Clear(CStatic*, CStatic*, bool&);

void ShowSubScreen(CStatic*);

void ShowMainScreen(CStatic*);

// 状态转移flag
bool isNum = true;			// false表示之前按下运算符状态, true表示之前按下数字状态
bool isDot = false;			// false表示之前非小数状态, true表示之前按下小数状态
bool isSqr = false;			// false表示之前未按下根号状态, true表示之前按下根号状态

double operand1 = 0.0;		// 被操作数（结果）
double operand2 = 0.0;		// 操作数
wstring operators;          // 记录符号
WCHAR tmp[256];             // 记录主屏幕上的值(中间值)
wstring lblText;			// 记录主屏幕上的值
wstring record;				// 记录算式
wstring record_tmp;			// 记录有效根号计算前的算式
int cnt = 0;				// 计算有效运算符个数
wstring preOpt;             // 输完数字时，记录上一次按下的有效运算(用以处理连续按等号的情况)
double tmp_operand;         // 第一次按等号时，记录等号之前输入的数字
int cntEqul = 0;            // 记录连续等号次数

void Number(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, wstring num, wstring opt, bool &isEqu)
{
	//PlaySound(, NULL, SND_SYNC | SND_FILENAME);
	// 将焦点重新定位到主窗口上
	//SetFocus(hwnd);

	// 连续等号次数清零
	cntEqul = 0;
	
	// 记录前次有效运算符
	preOpt = opt;

	// 在之前进行等号计算结果后直接输入数字，当作AC清零处理
	if (isEqu == true) {
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
	}
	
	// 获取主屏幕上的内容
	screen_hwnd_main->GetWindowText(tmp, 256);
	//GetWindowText(screen_hwnd_main, tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> lblText;
	buffer.clear();

	// isNum是false，表示前一个是运算符，直接替换当前屏幕中的数字
	if (isNum == false) {
		wstringstream buffer;
		buffer << num;
		buffer >> tmp;
		buffer.clear();
		screen_hwnd_main->SetWindowTextW(tmp);
		//SetWindowText(screen_hwnd_main, tmp);
		//SetWindowText(screen_hwnd_main, num);
	}
	// isNum是true，表示前一个是数字，这里有2种情况
	// 1. 判断前导0
	// 2. 判断是否输入位数超过限制
	else {
		if (lblText.length() == 1 && lblText[0] == '0') {
			//MessageBox(NULL, num, num, MB_OK);
			wstringstream buffer;
			buffer << num;
			buffer >> tmp;
			buffer.clear();
			screen_hwnd_main->SetWindowTextW(tmp);
			//SetWindowText(screen_hwnd_main, tmp);
			//SetWindowText(screen_hwnd_main, num);
		}
		else if (lblText.length() < 11) {
			if (isSqr == false)
			{
				lblText += num[0];
			}
			else
			{
				record = record_tmp;
				lblText = num[0];
				ShowSubScreen(screen_hwnd_sub);
			}
			ShowMainScreen(screen_hwnd_main);
		}
	}

	// 状态转移
	isNum = true;
	isSqr = false;
}

void Operator(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, wstring op, bool &isEqu)
{
	// 将焦点重新定位到主窗口上
	//SetFocus(hwnd);

	// 连续等号次数清零
	cntEqul = 0;

	// 获取主屏幕上的内容
	screen_hwnd_main->GetWindowText(tmp, 256);
	//GetWindowText(screen_hwnd_main, tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> lblText;
	buffer.clear();
	if (lblText[lblText.length() - 1] == '.')
	{
		lblText.erase(lblText.end() - 1);
	}

	//MessageBox(NULL, NULL, tmp, MB_OK);

	// 在之前进行等号计算结果后输入运算符号，将结果作为被操作数，开始新一轮的计算
	if (isEqu == true) {
		double num_tmp = 0.0;
		buffer << tmp;
		buffer >> num_tmp;
		buffer.clear();
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
		ShowMainScreen(screen_hwnd_main);
		operand1 = num_tmp;
	}

	// 如果第一次有效按下运算符
	if (cnt == 0) {
		//MessageBox(NULL, NULL, tmp, MB_OK);
		buffer << tmp;
		buffer >> operand1;
		buffer.clear();
	}

	// isNum是false，表示前一个是运算符，直接替换当前辅屏幕中的最后一位运算符
	if (isNum == false) {
		
		record[record.length() - 1] = op[0];
		ShowSubScreen(screen_hwnd_sub);
	}
	// isNum是true的话，进行以下操作
	// 1. 将上一次有效的运算符记录下来
	// 2. record += (lblText + op[0])
	// 3. 在输入有效运算符的次数超过1次是，计算出前一步的结果（结果放入主屏幕在Equal()中进行）
	// 4. 将相关结果分别放入辅屏幕
	else {
		/*preOpt = op;*/
		//MessageBox(NULL, preOpt.c_str(), NULL, MB_OK);
		
		// 若刚才未进行根号计算则将屏幕内容加入record
		// 否则直接将运算符加入record
		if (isSqr == false)
		{
			record += lblText;
		}
		record += op[0];

		ShowSubScreen(screen_hwnd_sub);
		if (cnt > 0) {
			Equal(screen_hwnd_main, screen_hwnd_sub, preOpt, isEqu);
		}
		cnt++;
	}

	// 状态转移
	isNum = false;
	isDot = false;
	isSqr = false;
}

void Equal(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, wstring op, bool &isEqu)
{
	// 将焦点重新定位到主窗口上
	//SetFocus(hwnd);
	
	// 获取主屏幕上的内容
	wstringstream buffer;
	screen_hwnd_main->GetWindowText(tmp, 256);
	//GetWindowText(screen_hwnd_main, tmp, 256);
	buffer << tmp;
	buffer >> operand2;
	buffer.clear();

	//MessageBox(NULL, tmp, tmp, MB_OK);

	if (cntEqul == 0) {
		tmp_operand = operand2;
		/*buffer << tmp_operand;
		buffer >> tmp;
		buffer.clear();
		MessageBox(NULL, tmp, tmp, MB_OK);*/
	}

	if (isEqu == true) {
		operand2 = tmp_operand;
	}

	// 进行计算
	switch (op[0])
	{
	case '+':
		operand1 += operand2;
		break;
	case '-':
		operand1 -= operand2;
		break;
	case '*':
		operand1 *= operand2;
		break;
	case '/':
	{
		if (fabs(operand2 - 0.0) < 1e-8) {
			MessageBox(NULL, _T("Cannot divide by zero!"), _T("Warning!"), MB_OK);
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
			return;
		}
		operand1 /= operand2;
	}
	break;
	case '%':
	{
		if (fabs(operand2 - 0.0) < 1e-8) {
			MessageBox(NULL, _T("Cannot do modulo with zero!"), _T("Warning!"), MB_OK);
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
			return;
		}
		int nOperand1, nOperand2;
		bool flag1 = false;
		bool flag2 = false;
		if (fabs(operand1 - (int)(operand1 + 0.5)) < 1e-8) {
			flag1 = true;
			nOperand1 = (int)(operand1 + 0.5);
		}
		if (fabs(operand2 - (int)(operand2 + 0.5)) < 1e-8) {
			flag2 = true;
			nOperand2 = (int)(operand2 + 0.5);
		}
		if (operand1 < -1.0 * 1e-8 && fabs(operand1 - (int)(operand1 - 0.5)) < 1e-8) {
			flag1 = true;
			nOperand1 = (int)(operand1 - 0.5);
		}
		if (operand2 < -1.0 * 1e-8 && fabs(operand2 - (int)(operand2 - 0.5)) < 1e-8) {
			flag2 = true;
			nOperand2 = (int)(operand2 - 0.5);
		}
		if (flag1 == true && flag2 == true) {
			nOperand1 %= nOperand2;
			operand1 = nOperand1;
		}
		else {
			MessageBox(NULL, _T("Cannot do modulo with demical!"), _T("Warning!"), MB_OK);
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
			return;
		}
	}
	break;
	default:
		break;
	}

	// 显示结果
	// 辅屏幕
	if (operand1 > 1e+308 || operand1 < -1.0 * 1e+308) {
		MessageBox(NULL, _T("Cannot calculate!"), _T("Warning!"), MB_OK);
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
		return;
	}

	buffer << tmp;
	buffer >> lblText;
	buffer.clear();
	
	// 多次连续按辅屏幕
	if (isEqu == true && cntEqul > 0) {
		if (cnt == 0)
		{
			return;
		}
		record.clear();
		record += (lblText + preOpt);
		buffer << tmp_operand;
		buffer >> lblText;
		buffer.clear();
		record += (lblText + _T("="));
		ShowSubScreen(screen_hwnd_sub);
	}

	// 第一次按等于时候的辅屏幕
	if (isEqu == true && cntEqul == 0) {
		if (lblText[lblText.length() - 1] == '.')
		{
			lblText.erase(lblText.end() - 1);
		}
		if (isSqr == false)
		{
			record += lblText;
		}
		record += _T('=');
		cntEqul++;
	}

	ShowSubScreen(screen_hwnd_sub);
	// 主屏幕
	if (cnt == 0)
	{
		ShowMainScreen(screen_hwnd_main);
		return;
	}
	buffer << setprecision(9) << operand1;
	buffer >> lblText;
	buffer.clear();
	ShowMainScreen(screen_hwnd_main);

}

void Dot(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, bool& isEqu)
{
	// 将焦点置于主窗口
	//SetFocus(hwnd);
	
	if (isDot == true)
	{
		return;
	} 
	else {
		wstringstream buffer;

		// 若刚才按下等号时按下"."则直接清空并补'.'
		if (isEqu == true)
		{
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
		} 
		// 获取主屏幕上的内容
		screen_hwnd_main->GetWindowText(tmp, 256);
		//GetWindowText(screen_hwnd_main, tmp, 256);
		buffer << tmp;
		buffer >> lblText;
		buffer.clear();
		// 若输入新的运算符或刚才为未确定的根号计算则清空并置为"0."
		if (isNum == false || isSqr == true)
		{
			if (isSqr == true)
			{
				record = record_tmp;
				ShowSubScreen(screen_hwnd_sub);
			}
			lblText = _T("0");
		}
		if (lblText.length() < 11)
		{
			lblText += _T(".");
		}
		ShowMainScreen(screen_hwnd_main);
	}
	// 状态转移
	isDot = true;
	isNum = true;
	isSqr = false;
}


void Sqrt(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, bool& isEqu)
{
	// 焦点置于主窗口
	//SetFocus(hwnd);
	
	if (isSqr == false)
	{
		record_tmp = record;
	}

	screen_hwnd_main->GetWindowText(tmp, 256);
	//GetWindowText(screen_hwnd_main, tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> operand2;
	buffer.clear();
	
	if (operand2 >= 0.0)
	{
		operand2 = sqrt(operand2);
		buffer << operand2;
		buffer >> lblText;
		buffer.clear();

		// 处理连续按根号的情况
		if (isSqr == true)
		{
			record = record_tmp;
		}
		record += _T("Sqrt(");
		record += tmp;
		record += _T(")");
	}
	else
	{
		MessageBox(NULL, _T("Invalid input!*"), _T("Warning!"), MB_OK);
		lblText = _T("0");
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqu);
		return;
	}

	ShowMainScreen(screen_hwnd_main);
	ShowSubScreen(screen_hwnd_sub);

	// 状态转移
	isSqr = true;
	isNum = true;
}

void Clear(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, bool &isEqu)
{
	isNum = true;
	isDot = isSqr = isEqu = false;
	operand1 = operand2 = tmp_operand = 0.0;
	cnt = cntEqul = 0;
	operators.clear();
	record.clear();
	preOpt.clear();
	screen_hwnd_main->SetWindowTextW(_T("0"));
	screen_hwnd_sub->SetWindowTextW(_T(""));
	//SetWindowText(screen_hwnd_main, _T("0"));
	//SetWindowText(screen_hwnd_sub, _T(""));
}

void ShowSubScreen(CStatic* screen_hwnd_sub)
{
	wstringstream buffer;
	buffer << record;
	buffer >> tmp;
	buffer.clear();
	screen_hwnd_sub->SetWindowTextW(tmp);
	//SetWindowText(screen_hwnd_sub, tmp);
}

void ShowMainScreen(CStatic* screen_hwnd_main)
{
	wstringstream buffer;
	buffer << lblText;
	buffer >> tmp;
	buffer.clear();
	screen_hwnd_main->SetWindowTextW(tmp);
	//SetWindowText(screen_hwnd_main, tmp);
}

