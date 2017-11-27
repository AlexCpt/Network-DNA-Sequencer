
// ClientMaladifDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "ClientMaladif.h"
#include "ClientMaladifDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
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


// boîte de dialogue CClientMaladifDlg



CClientMaladifDlg::CClientMaladifDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLIENTMALADIF_DIALOG, pParent)
	, m_port(0)
	, m_status(_T(""))
	, m_recieveddata(_T(""))
	, m_barreDeCmd(_T(""))
	, m_ip(_T("127.0.0.1"))
	, m_cmdAllowed(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientMaladifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_port);
	DDX_Text(pDX, IDC_EDIT3, m_status);
	DDX_Text(pDX, IDC_EDIT4, m_recieveddata);
	DDX_Control(pDX, IDC_BUTTON3, m_listenbutton);
	DDX_Control(pDX, IDC_BUTTON1, m_stopbutton);
	DDX_Text(pDX, IDC_EDIT5, m_barreDeCmd);
	DDX_Text(pDX, IDC_EDIT1, m_ip);
	DDX_Control(pDX, IDC_EDIT4, m_zoneEdit);
}

BEGIN_MESSAGE_MAP(CClientMaladifDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &CClientMaladifDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CClientMaladifDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON3, &CClientMaladifDlg::OnBnClickedButtonConnexion)
	ON_BN_CLICKED(IDC_BUTTON1, &CClientMaladifDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDOK, &CClientMaladifDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// gestionnaires de messages pour CClientMaladifDlg

BOOL CClientMaladifDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO: ajoutez ici une initialisation supplémentaire

	m_sListener.SetParentDlg(this);
	m_sConnected.SetParentDlg(this);
	m_status = "Non connecté";
	m_port = 2000;
	m_stopbutton.EnableWindow(FALSE);
	UpdateData(FALSE);
	top_chrono = 0;
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CClientMaladifDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CClientMaladifDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CClientMaladifDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientMaladifDlg::OnEnChangeEdit2()
{
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialogEx::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
}


void CClientMaladifDlg::OnEnChangeEdit3()
{
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialogEx::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
}

void CClientMaladifDlg::OnAccept() //Connexion du serveur en retour //Pas utilisé
{
	CString strIP;
	UINT port;
	CString message;
	if (m_sListener.Accept(m_sConnected))
	{
		m_sConnected.GetSockName(strIP, port);
		m_sConnected.Send("Acceptation du Client", strlen("Acceptation du Client"));

		CString strData;
		strData = "Le Serveur s'est connecté\r\n";
		m_recieveddata.Insert(m_recieveddata.GetLength(), strData);   //display in server
		m_status = "Connecté";
		connecte = true;
		UpdateData(FALSE);
	}

	else
	{
		//AfxMessageBox("Cannoot Accept Connection");
	}
}

void CClientMaladifDlg::OnClose()
{
	//AfxMessageBox("Socket Is Closed!!!");
	OnBnClickedButtonStop();
}

void CClientMaladifDlg::OnReceive()
{
	long int arret_chrono = clock();
	float tpsSocket = (float)(arret_chrono - top_chrono) / CLOCKS_PER_SEC;
	tpsSocket = tpsSocket * 1000;
	CString leInt;

	char *pBuf = new char[1025];
	CString strData;
	int iLen;
	iLen = m_sConnected.Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		//AfxMessageBox("Could not Recieve");
	}
	else
	{
		CString leFloat;
		pBuf[iLen] = NULL;
		strData = pBuf;

		//Data transfered at receiving
		dataTransfered = sizeof(strData);
		leInt.Format(_T("%d"), dataTransfered);

		//out
		strData += "       tps de send/receive = ";
		leFloat.Format(_T("%f"),tpsSocket);
		strData += leFloat;
		strData += " ms";
		strData += "   (taille reçu = ";
		strData += leInt;
		strData += " b)";
		strData += "\r\n\r\n";
		m_recieveddata.Insert(m_recieveddata.GetLength(), strData);   //display in server
		UpdateData(FALSE);

		//m_sConnected.Send(pBuf, iLen);
		//m_sConnected.ShutDown(0);  
		delete pBuf;
	}
}


void CClientMaladifDlg::OnBnClickedButtonConnexion()
{
	// TODO: Add your control notification handler code here
	bool success;

	UpdateData(TRUE);
	
	m_sConnected.Create();
	success = m_sConnected.Connect(m_ip, m_port);
	//if (success)
	{
		m_status = "Connecté";
		UpdateData(FALSE);
		m_listenbutton.EnableWindow(FALSE);
		m_stopbutton.EnableWindow(TRUE);
		connecte = true;
	}
	/*else
	{
		m_status = "Echec";
		UpdateData(FALSE);
	}*/
	

}

void CClientMaladifDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	m_sConnected.Close();
	m_sListener.Close();
	m_status = "Non connecté";
	connecte = false;
	UpdateData(FALSE);
	m_listenbutton.EnableWindow(TRUE);
	m_stopbutton.EnableWindow(FALSE);

}


void CClientMaladifDlg::OnBnClickedSend()
{
	if (connecte)
	{
		CStringA strData;
		CString display;
		CString leInt;

		UpdateData(TRUE);
		strData = m_barreDeCmd;

		const size_t newsizea = (strData.GetLength() + 1);

		char *pBuf = new char[newsizea];
		strcpy_s(pBuf, newsizea, strData);

		//Data transfered at sending
		dataTransfered = sizeof(strData);

		//out
		leInt.Format(_T("%d"), dataTransfered);
		top_chrono = clock();
		m_sConnected.Send(strData, strData.GetLength());
		display = ">> ";
		display += strData;
		display += "  (taille envoi = ";
		display += leInt;
		display += " b)";
		display += "\r\n";
		m_recieveddata.Insert(m_recieveddata.GetLength(), display);   //display in server
		m_barreDeCmd = "";

		UpdateData(FALSE);
	}
	
	
	
	
	//CDialogEx::OnOK();
}
