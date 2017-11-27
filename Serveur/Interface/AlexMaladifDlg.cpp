
// AlexMaladifDlg.cpp : fichier d'impl�mentation
//

#include "stdafx.h"
#include "AlexMaladif.h"
#include "AlexMaladifDlg.h"
#include "afxdialogex.h"
#include "ProcessingRequest.h"
#include <conio.h>
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// bo�te de dialogue CAboutDlg utilis�e pour la bo�te de dialogue '� propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Donn�es de bo�te de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Impl�mentation
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


// bo�te de dialogue CAlexMaladifDlg



CAlexMaladifDlg::CAlexMaladifDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALEXMALADIF_DIALOG, pParent)
	, m_port2(2000)
	, m_zone2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlexMaladifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_port2);
	DDX_Text(pDX, IDC_EDIT3, m_zone2);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
}

BEGIN_MESSAGE_MAP(CAlexMaladifDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAlexMaladifDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAlexMaladifDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// gestionnaires de messages pour CAlexMaladifDlg

BOOL CAlexMaladifDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'�l�ment de menu "� propos de..." au menu Syst�me.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes syst�me.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	AllocConsole(); // DEBUG----------------------------------------------------------------------------

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		//ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// D�finir l'ic�ne de cette bo�te de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fen�tre principale de l'application n'est pas une bo�te de dialogue
	SetIcon(m_hIcon, TRUE);			// D�finir une grande ic�ne
	SetIcon(m_hIcon, FALSE);		// D�finir une petite ic�ne

	// TODO: ajoutez ici une initialisation suppl�mentaire
	m_sListener.SetParentDlg(this);
	m_sConnected.SetParentDlg(this);
	m_button1.EnableWindow(TRUE);
	m_button2.EnableWindow(FALSE);
	return TRUE;  // retourne TRUE, sauf si vous avez d�fini le focus sur un contr�le
}

void CAlexMaladifDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si vous ajoutez un bouton R�duire � votre bo�te de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'ic�ne.  Pour les applications MFC utilisant le mod�le Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CAlexMaladifDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de p�riph�rique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'ic�ne dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'ic�ne
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le syst�me appelle cette fonction pour obtenir le curseur � afficher lorsque l'utilisateur fait glisser
//  la fen�tre r�duite.
HCURSOR CAlexMaladifDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlexMaladifDlg::OnBnClickedButton1()
{	
	UpdateData(TRUE);

	m_sListener.Create(m_port2);
	if (m_sListener.Listen() == FALSE)
	{
		m_sListener.Close();
		return;
	}
		CString msgServer;
		msgServer = "Serveur running\r\n";
		m_zone2.Insert(m_zone2.GetLength(), msgServer);
		UpdateData(FALSE);
		m_button1.EnableWindow(FALSE);
		m_button2.EnableWindow(TRUE);
}


void CAlexMaladifDlg::OnBnClickedButton2()
{
	m_sConnected.Close();
	m_sListener.Close();
	connecte = false;

	CString msgServer;
	msgServer = "Serveur stopped\r\n";
	m_zone2.Insert(m_zone2.GetLength(), msgServer);

	UpdateData(FALSE);
	m_button1.EnableWindow(TRUE);
	m_button2.EnableWindow(FALSE);
}

void CAlexMaladifDlg::OnAccept() //Connexion du serveur en retour 
{
	CString strIP;
	UINT port;
	CString message;
	if (m_sListener.Accept(m_sConnected))
	{
		m_sConnected.GetSockName(strIP, port);
		message = "Client Connected,IP :";
		message += strIP;
		message += "\r\n";
		m_sConnected.Send("Bonjour, veuillez vous identifier \r\n", strlen("Bonjour, veuillez vous identifier \r\n"));

		m_zone2.Insert(m_zone2.GetLength(), message);   //display in server
		connecte = true;
		UpdateData(FALSE);
	}

	else
	{
		//AfxMessageBox("Cannoot Accept Connection");
	}
}

void CAlexMaladifDlg::OnClose()
{
	//AfxMessageBox("Socket Is Closed!!!");
	OnBnClickedButton2();
	FreeConsole();
}

void CAlexMaladifDlg::OnReceive()
{
	char *pBuf = new char[1025];
	CString strData;
	CString affichageCmdClient;
	CStringA responseToClient;

	int iLen;
	iLen = m_sConnected.Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		OnBnClickedButton2();
	}
	else
	{
		pBuf[iLen] = NULL;
		strData = pBuf;

		//Affichage cmdClient
		affichageCmdClient = "client : ";
		affichageCmdClient += pBuf;
		affichageCmdClient += "\r\n";
		m_zone2.Insert(m_zone2.GetLength(), affichageCmdClient);

		//Processing Request
		ProcessingRequest pr;

		CT2CA pszConvertedAnsiString(strData);
		std::string strStd(pszConvertedAnsiString);
		long int top_chrono = clock();

		string reply = pr.getManager(strStd);

		long int arret_chrono = clock();
		float t = (float)(arret_chrono - top_chrono) / CLOCKS_PER_SEC;
		strData;
		strData = "TEMPS ALGO: ";
		strData += to_string(t).c_str();
		strData += "\r\nserver : ";
		strData += reply.c_str();
		strData += "\r\n";

		//Response server
		m_zone2.Insert(m_zone2.GetLength(), strData);   //display in server

		//Response to Client
		responseToClient = strData;
		const size_t newsizea = (responseToClient.GetLength() + 1);
		char *pBuf = new char[newsizea];
		strcpy_s(pBuf, newsizea, responseToClient);
		m_sConnected.Send(pBuf, strData.GetLength());

		UpdateData(FALSE);

		delete pBuf;
	}
}
