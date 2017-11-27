
// AlexMaladifDlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "MyEchoSocket.h"

// boîte de dialogue CAlexMaladifDlg
class CAlexMaladifDlg : public CDialogEx
{
// Construction
public:
	void OnReceive();
	void OnClose();
	void OnAccept();
	CAlexMaladifDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALEXMALADIF_DIALOG };
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
	CEdit idc_edit1;

private:
	MyEchoSocket m_sListener;
	MyEchoSocket m_sConnected;
	bool connecte;
	int m_port2;
	CString m_zone2;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CButton m_button1;
public:
	CButton m_button2;
};
