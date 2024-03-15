#include <afxwin.h>         // ���� ���������� MFC � ���������� ����������
#include <afxcmn.h>         // ����� �������� ���������� ���������� MFC 
#include <Afxsock.h>        // ���������� MFC ��� ��������� �������
#include <string.h>			// ����������� ������� ��� ������ �� �������
#include "WSockChk.h"


class CWSockChkApp : public CWinApp  //�������� ������ ����������
{
public:
	virtual BOOL InitInstance();	//����� ���������� Windows ��� ������������� ����������
};



class CWindow : public CFrameWnd    //�������� ������ ���� ����������
{
protected:
	afx_msg void AboutOk();        //����� ���������� ��� ������ ������ ���� About
	afx_msg void ExitApp();		   //����� ���������� ��� ������ ������ ���� Exit
	afx_msg void ComboSelect();    //����� ���������� ��� ������ ���������
	afx_msg void ButtontoSend();   //����� ���������� ��� ������� �� ������ �������� �������
	afx_msg void ButtontoStop();   //����� ���������� ��� ������� �� ������ ������ ����������
	afx_msg void OnClear();	       //����� ���������� ��� ������� ������ ������� ������� ������
	DECLARE_MESSAGE_MAP()          //���������� ������������� ����� ��������� 
};

BEGIN_MESSAGE_MAP(CWindow, CFrameWnd)   //���������� ������������ ��������� (������)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_HELP_ABOUT, AboutOk)
	ON_BN_CLICKED(ID_BUT_CLEAR, OnClear)
	ON_BN_CLICKED(ID_BUT_SEND, ButtontoSend)
	ON_BN_CLICKED(ID_BUT_STOP, ButtontoStop)
	ON_CBN_SELENDOK(801, ComboSelect)
	ON_COMMAND(ID_FILE_EXIT, ExitApp)
END_MESSAGE_MAP()                      //���������� ������������ ��������� (�����)


class CConsOut :public CEdit				//�������� ������ ������� ������ �� ������ ������ CEdit	
{
public:
	void AppendText(char* text);       //����������� ������ ���������� ������ � ������� ������
};



class ASocet :public CAsyncSocket         //�������� ��������� ������ ������� �� CAsyncSocket
{
public:
	virtual void OnConnect(int nErrorCode); //��������������� ������ ����������� �������� 
	//��������� MFC ��� ���������� ������� ���������� ������ 
	virtual void OnReceive(int nErrorCode); //��������������� ������ ����������� �������� 
	//��������� MFC ��� ������� �� ������� ������
	//������ ������ ������� ����� �������� 
};








CWSockChkApp theApp;                       //�������� ������� ����������
CWindow* pFrame = new CWindow;             //�������� ������� ���� ����������

ASocet* sock = new ASocet;                  //�������� ������� ������


CComboBox* lProtSel = new CComboBox;        //�������� ������� ������ ComboBox ������ ���������
CEdit* lHstSel = new CEdit;	               //�������� ������� ��������� ���� ������ ����� �������
CEdit* lPortSel = new CEdit;                //�������� ������� ��������� ���� ������ ����� �������
CEdit* lStrSel = new CEdit;                 //�������� ������� ��������� ���� ����� �������� ������

CButton* bSend = new CButton;               //�������� ������� ������ �������� ���������
CButton* bStop = new CButton;               //�������� ������� ������ ������ ����������

CListCtrl* cList = new CListCtrl;          //�������� ������� ���� ��������� ����������

CConsOut* EConOut = new CConsOut;           //�������� ������� ������� ������


int SockInit = Fail;	             //���������� ��� �������� ��������� ������������� �������
int ProtocolType = TCP;	        //���������� ������������ ��������� ��������





BOOL CWSockChkApp::InitInstance()         //��������������� ������ CWinApp::InitInstance()
{
	m_pMainWnd = pFrame;                 //�������� ����� �������� ����(������) ����������

	Enable3dControls();

	RECT Rct;							 //���������� ������������ ��� ����������� 
	//��������� ���� ��������


// ������� ��� ������ ��� ����������������� ����������
/*
CFont *Cf=new CFont;
Cf->CreateFont(10,8,0,0,100,NULL,NULL,NULL,ANSI_CHARSET,OUT_CHARACTER_PRECIS
	,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH|FF_ROMAN,"System");

CFont *Cf2=new CFont;
Cf2->CreateFont(16,10,0,0,100,NULL,NULL,NULL,ANSI_CHARSET,OUT_CHARACTER_PRECIS
	,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FIXED_PITCH|FF_ROMAN,"System");

CFont *Cf3=new CFont;
Cf3->CreateFont(18,8,0,0,100,NULL,NULL,NULL,ANSI_CHARSET,OUT_CHARACTER_PRECIS
	,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH|FF_ROMAN,"System");
*/
	CFont* Cf = new CFont;
	Cf->CreateFont(15, 7, 0, 0, 100, NULL, NULL, NULL, ANSI_CHARSET, OUT_CHARACTER_PRECIS
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_ROMAN, "Verdana");

	CFont* Cf2 = new CFont;
	Cf2->CreateFont(16, 10, 0, 0, 100, NULL, NULL, NULL, ANSI_CHARSET, OUT_CHARACTER_PRECIS
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_ROMAN, "Courier New");

	CFont* Cf3 = new CFont;
	Cf3->CreateFont(19, 8, 0, 0, 100, NULL, NULL, NULL, ANSI_CHARSET, OUT_CHARACTER_PRECIS
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Courier New");


	// ������� ������� ���� ����������
	//Rct.left=100;Rct.top=100;Rct.right=800;Rct.bottom=470;
	Rct.left = 100; Rct.top = 100; Rct.right = 810; Rct.bottom = 480;
	pFrame->Create(AfxRegisterWndClass(NULL, LoadCursor(IDC_ARROW), NULL/*(HBRUSH)COLOR_BACKGROUND*/, NULL),
		"Windows Socket Check",
		WS_DLGFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		Rct, NULL, NULL, NULL);
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();


	CMenu* Mmenu = new CMenu;             //������� ������ ����
	Mmenu->LoadMenu(MainMenu);			 //��������� ��������� ���� � ����� �������� �������� ����
	pFrame->SetMenu(Mmenu);              //������������� ���� � ������� ���� ����������



	// ������� ����� ������ ������� ����������
	Rct.left = 10; Rct.top = Ydown; Rct.right = 360; Rct.bottom = Ydown + 170;
	CButton* chB = new CButton;
	chB->Create("Winsock Statistic", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, Rct, pFrame, 501);
	chB->SetFont(Cf, TRUE);



	//������� ������� ������ ����������
	Rct.left = 20; Rct.top = Ydown + 20; Rct.right = 350; Rct.bottom = Ydown + 130;
	cList->Create(WS_VISIBLE | WS_CHILD | LVS_EX_GRIDLINES | LVS_REPORT | LVS_EDITLABELS
		| WS_BORDER, Rct, pFrame, 601);
	cList->InsertColumn(0, "Item", LVCF_TEXT, 180, 0);
	cList->InsertColumn(1, "State", LVCF_TEXT, 180, 1);
	cList->InsertItem(0, "Windows Sockets Version", -1);
	cList->InsertItem(1, "Windows Sockets Implementation", -1);
	cList->InsertItem(2, "Windows Sockets Status", -1);
	cList->InsertItem(3, "Current Sockets Type", -1);
	cList->InsertItem(4, "Current Sockets Protocol", -1);
	cList->SetItemText(0, 1, "NULL");
	cList->SetItemText(1, 1, "NULL");
	cList->SetItemText(2, 1, "NULL");
	cList->SetItemText(3, 1, "NULL");
	cList->SetItemText(4, 1, "NULL");


	// ������� ������� Final Status of WinSocket DLL
	Rct.left = 20; Rct.top = Ydown + 145; Rct.right = 270; Rct.bottom = Ydown + 165;
	CStatic* CsFinal = new CStatic;
	CsFinal->Create("Final Status of WinSocket DLL :", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 701);
	CsFinal->SetFont(Cf, TRUE);




	// ������� ����� ������ ���� ����� ������	
	Rct.left = 10; Rct.top = 10; Rct.right = 680; Rct.bottom = Ydown - 10;
	CButton* cWork = new CButton;
	cWork->Create("Input Console", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, Rct, pFrame, 502);
	cWork->SetFont(Cf, TRUE);


	// ������� ������� Select Protocol
	Rct.left = 20; Rct.top = 35; Rct.right = 160; Rct.bottom = 50;
	CStatic* CsPrSel = new CStatic;
	CsPrSel->Create("Select Protocol", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 702);
	CsPrSel->SetFont(Cf2, TRUE);

	// ������� ���� ������ ���������
	Rct.left = 170; Rct.top = 30; Rct.right = 240; Rct.bottom = 180;
	lProtSel->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, Rct, pFrame, 801);
	lProtSel->AddString("TCP");
	lProtSel->AddString("UDP");
	lProtSel->SetFont(Cf2, TRUE);
	lProtSel->SelectString(0, "TCP");


	// ������� ������� Input IP adress or Host Name
	Rct.left = 20; Rct.top = 65; Rct.right = 280; Rct.bottom = 85;
	CStatic* CsIPSel = new CStatic;
	CsIPSel->Create("Input IP adress or Host Name", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 703);
	CsIPSel->SetFont(Cf2, TRUE);


	// ������� ���� ����� ����� ����� ��� IP ������ �������
	Rct.left = 290; Rct.top = 60; Rct.right = 410; Rct.bottom = 85;
	lHstSel->Create(WS_CHILD | WS_VISIBLE | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_UPPERCASE, Rct, pFrame, 1901);
	lHstSel->SetFont(Cf3, TRUE);


	// ������� ������� Input TCP/UDP port
	Rct.left = 430; Rct.top = 65; Rct.right = 600; Rct.bottom = 85;
	CStatic* CsPrtSel = new CStatic;
	CsPrtSel->Create("Input TCP/UDP port", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 706);
	CsPrtSel->SetFont(Cf2, TRUE);


	// ������� ���� ����� ����� �������	
	Rct.left = 610; Rct.top = 60; Rct.right = 670; Rct.bottom = 85;
	lPortSel->CreateEx(WS_EX_CLIENTEDGE, "Edit", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT, Rct, pFrame, 902, NULL);
	lPortSel->SetFont(Cf3, TRUE);
	lPortSel->SetLimitText(5);

	// ������� ������� Input Echo Test String
	CStatic* CsStrSel = new CStatic;
	Rct.left = 20; Rct.top = 95; Rct.right = 220; Rct.bottom = 115;
	CsStrSel->Create("Input Echo Test String", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 702);
	CsStrSel->SetFont(Cf2, TRUE);


	// ������� ���� ����� �������� ������
	Rct.left = 230; Rct.top = 90; Rct.right = 410; Rct.bottom = 115;
	lStrSel->Create(WS_CHILD | WS_VISIBLE | ES_LEFT | WS_BORDER, Rct, pFrame, 901);
	lStrSel->SetFont(Cf3, TRUE);


	// ������� ������ ������� ���������	
	Rct.left = 420; Rct.top = 95; Rct.right = 530; Rct.bottom = 115;
	bSend->Create("Send Request", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, Rct, pFrame, ID_BUT_SEND);
	bSend->SetFont(Cf, TRUE);


	// ������� ������ ��������� ������� ����������
	Rct.left = 540; Rct.top = 95; Rct.right = 670; Rct.bottom = 115;
	bStop->Create("Stop Connection", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_DISABLED
		, Rct, pFrame, ID_BUT_STOP);
	bStop->SetFont(Cf, TRUE);



	// ������� ����� ������ ������� ������
	Rct.left = 370; Rct.top = Ydown; Rct.right = 680; Rct.bottom = Ydown + 170;
	CButton* cConsOut = new CButton;
	cConsOut->Create("Output Console", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, Rct, pFrame, 501);
	cConsOut->SetFont(Cf, TRUE);




	// ������� ������� ������	
	Rct.left = 380; Rct.top = Ydown + 20; Rct.right = 670; Rct.bottom = Ydown + 130;
	EConOut->CreateEx(WS_EX_CLIENTEDGE, "Edit", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT |
		ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_WANTRETURN | WS_HSCROLL
		| WS_VSCROLL | ES_READONLY, Rct, pFrame, 5902, NULL);
	EConOut->SetFont(Cf2, TRUE);


	// ������� ������ ������� ������� ������
	Rct.left = 600; Rct.top = Ydown + 140; Rct.right = 670; Rct.bottom = Ydown + 160;
	CButton* bClear = new CButton;
	bClear->Create("Clear", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, Rct, pFrame, ID_BUT_CLEAR);
	bClear->SetFont(Cf, TRUE);



	WSADATA wsinfo;                              //���������� 
	char buffTemp[5] = { '\0','\0','\0','\0','\0' }; //������������ ��� �������������
	char buffver[5] = { '\0','\0','\0','\0','\0' };  //���������� �������

	if (AfxSocketInit(&wsinfo) != 0) //����� ������ ����������������� ���������� �������
	{
		//������� �������������� ������� Initiated
		CStatic* CTotal = new CStatic;
		Rct.left = 275; Rct.top = Ydown + 145; Rct.right = 350; Rct.bottom = Ydown + 165;
		CTotal->Create("Initiated", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 701);
		CTotal->SetFont(Cf, TRUE);

		//������� ���������� �� ������
		strcat(buffver, itoa(HIBYTE(wsinfo.wHighVersion), buffTemp, 10));
		strcat(buffver, ".");
		strcat(buffver, itoa(LOBYTE(wsinfo.wHighVersion), buffTemp, 10));

		cList->SetItemText(0, 1, buffver);
		cList->SetItemText(1, 1, wsinfo.szDescription);
		cList->SetItemText(2, 1, wsinfo.szSystemStatus);
		cList->SetItemText(3, 1, "Stream");
		cList->SetItemText(4, 1, "TCP");
		EConOut->AppendText("Windows Socket DLL initiated ...\r\n");
		SockInit = Init;
	}
	else
	{
		//������� �������������� ������� Error � ��������� � ������� ������
		CStatic* CTotal = new CStatic;
		Rct.left = 275; Rct.top = Ydown + 145; Rct.right = 350; Rct.bottom = Ydown + 165;
		CTotal->Create("Error", SS_LEFT | WS_VISIBLE | WS_CHILD, Rct, pFrame, 701);
		CTotal->SetFont(Cf, TRUE);
		EConOut->AppendText("Windows Socket initiated Error...\r\n");
		SockInit = Fail;
	}

	return TRUE;

}



void CWindow::AboutOk()
{
	//������� ���� ���������� ���������� � ��������
	pFrame->MessageBox("Program for Windows Socket test(c)2001", "About", MB_OK);
}



void CWindow::ExitApp()
{
	//��������� ����������
	pFrame->DestroyWindow();
}


//����� ���������
void CWindow::ComboSelect()
{
	switch (lProtSel->GetCurSel())
	{
	case 0:
		cList->SetItemText(3, 1, "Stream");
		cList->SetItemText(4, 1, "TCP");
		ProtocolType = TCP;
		break;

	case 1:
		cList->SetItemText(3, 1, "Datagram");
		cList->SetItemText(4, 1, "UDP");
		ProtocolType = UDP;
		break;
	}
}




void CWindow::ButtontoSend()
{
	char HostAddr[1024];
	char HostPort[7];

	if (SockInit == Fail)
	{
		EConOut->AppendText("Windows Socket initiated Error...\r\n");
		return;
	}

	//������� ����� � ������������ � ��������� ����������
	if (ProtocolType == TCP)
	{
		if (sock->Create(0, SOCK_STREAM, FD_READ | FD_CONNECT, NULL) != 0)
		{
			EConOut->AppendText("\r\nCreated Stream TCP Socket\r\n");
		}
		else
		{
			EConOut->AppendText("Creating Socket Failed\r\n");
			return;
		}
	}
	else
	{
		if (sock->Create(0, SOCK_DGRAM, FD_READ | FD_CONNECT, NULL) != 0)
		{
			EConOut->AppendText("\r\nCreated Datagram UDP Socket\r\n");
		}
		else
		{
			EConOut->AppendText("Creating Socket Failed\r\n");
			return;
		}
	}

	if (ProtocolType == TCP) EConOut->AppendText("Tring connect to host ... \r\n");


	bSend->ModifyStyle(NULL, WS_DISABLED, 0);
	bStop->ModifyStyle(WS_DISABLED, NULL, 0);
	bSend->InvalidateRect(NULL, 1);
	bStop->InvalidateRect(NULL, 1);

	//��������� ����� � ���� ������� � �������� ���������� � ��� �����
	lHstSel->GetWindowText(HostAddr, 1024);
	lPortSel->GetWindowText(HostPort, 7);
	sock->Connect(HostAddr, (UINT)atoi(HostPort));

	if (ProtocolType == UDP) sock->OnConnect(0);

}




void CWindow::ButtontoStop()
{
	bStop->ModifyStyle(0, WS_DISABLED, 0);
	bSend->ModifyStyle(WS_DISABLED, 0, 0);
	bSend->InvalidateRect(NULL, 1);
	bStop->InvalidateRect(NULL, 1);
	EConOut->AppendText("Connection Aborted\r\n");

	sock->ShutDown(2);
	sock->Close();
}






void CWindow::OnClear()
{
	EConOut->SetWindowText("");//������� ������� ������
}

//���������� ������ CConsOut::AppendText
void CConsOut::AppendText(char* text)
{
	int strCnt;
	char* strBuff;
	strCnt = GetLineCount();
	strBuff = (char*)calloc((strCnt * 512 + strlen(text)), 1);

	GetWindowText(strBuff, strCnt * 512 + strlen(text));
	strcat(strBuff, text);
	SetWindowText(strBuff);
	LineScroll(strCnt, 0);

	free(strBuff);
}










void ASocet::OnConnect(int nErrorCode)
{
	char sendBuff[1024];    //����� ��������

	if (SockInit == Fail)
	{
		EConOut->AppendText("Windows Socket initiated Error...\r\n");
		return;
	}

	switch (nErrorCode)
	{
	case(0):
		if (ProtocolType == TCP) EConOut->AppendText("Connected....\r\n");
		if (ProtocolType == UDP) EConOut->AppendText("Try send datagram....\r\n");

		lStrSel->GetWindowText(sendBuff, 1024);
		EConOut->AppendText("Sending Data....\r\n");

		//���� ���������� ������ ������ �������� �������� �������� ������
		Send(sendBuff, strlen(sendBuff), 0);
		EConOut->AppendText("Ready to receive Data....\r\n");
		break;

	default:
		EConOut->AppendText("Connection failed\r\n");

		ShutDown(2);
		Close();

		bStop->ModifyStyle(0, WS_DISABLED, 0);
		bSend->ModifyStyle(WS_DISABLED, 0, 0);
		bSend->InvalidateRect(NULL, 1);
		bStop->InvalidateRect(NULL, 1);

		break;
	}

}




void ASocet::OnReceive(int nErrorCode)
{

	char receiveBuff[1024]; //����� ������
	memset(receiveBuff, '\0', 1024);

	if (SockInit == Fail)
	{
		EConOut->AppendText("Windows Socket initiated Error...\r\n");
		return;
	}

	switch (nErrorCode)
	{
	case(0):
		//������� ��������� OnReceive �������� �������� ������
		Receive(receiveBuff, 1024, 0);
		EConOut->AppendText("Receive Data \r\n\r\n");
		EConOut->AppendText(receiveBuff);
		EConOut->AppendText("\r\n");

		//������� ������ ��������� �����

		ShutDown(2);
		Close();
		break;

	default:
		EConOut->AppendText("Receive Failed\r\n");
		break;
	}
	bStop->ModifyStyle(0, WS_DISABLED, 0);
	bSend->ModifyStyle(WS_DISABLED, 0, 0);
	bSend->InvalidateRect(NULL, 1);
	bStop->InvalidateRect(NULL, 1);
}



