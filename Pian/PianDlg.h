
// PianDlg.h : header file
//

#pragma once
#include <string>
#define TIMERCOUNT 1000

// CPianDlg dialog
class CPianDlg : public CDialogEx
{
// Construction
public:
	CPianDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CSliderCtrl m_ctrlSlider;
	CString m_strEdit;
	
	int masterVolume;
	int qVol, wVol, eVol, rVol, tVol, yVol;
	float timeNumber;
	bool recordStarted;
	int recPlayerLength;
	float recPlayerTime;
	int beep;
	struct recordPlayer {
		float timeSpawn;
		char soundName;
		int volume;
	} recPlayer[256];
	int numberOfBeeps;
	CString str;
	std::string recorder;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton7();
	CString qVol_field;
	afx_msg void OnBnClickedButton8();
	
	CString wVol_field;
	CString eVol_field;
	CString rVol_field;
	CString tVol_field;
	CString yVol_field;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	CEdit Edit_number;
	afx_msg void OnBnClickedButton19();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton play_button;
	CString play_editfield;
	afx_msg void OnBnClickedButton20();
	CEdit play_edit;
	CButton SaveButton;
	CString SaveName;
	afx_msg void OnBnClickedButton21();
	CEdit SaveEdit;
	afx_msg void OnBnClickedButton22();
};
