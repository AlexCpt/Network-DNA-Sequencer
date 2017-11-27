
// ClientMaladifDlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "MyEchoSocket.h"

// boîte de dialogue CClientMaladifDlg
class CClientMaladifDlg : public CDialogEx
{
// Construction
public:
	void OnReceive();
	void OnClose();
	void OnAccept();
	CClientMaladifDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTMALADIF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
private:
	int m_port;
	bool connecte;
	CString m_status;
	CString m_recieveddata;
public:
	afx_msg void OnBnClickedButtonConnexion();
	afx_msg void OnBnClickedButtonStop();
private:
	CButton m_listenbutton;
	CButton m_stopbutton;
	MyEchoSocket m_sListener;
	MyEchoSocket m_sConnected;
public:
	afx_msg void OnBnClickedSend();
private:
	CString m_barreDeCmd;
	CString m_ip;
public:
	CEdit m_zoneEdit;
private:
	CString m_cmdAllowed;
	long int top_chrono;
	int dataTransfered;
};
