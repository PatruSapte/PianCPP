
// PianDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Pian.h"
#include "PianDlg.h"
#include "afxdialogex.h"

//for sound
#include "Windows.h"
#include "MMSystem.h"

//for volume
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>

//for saving record
#include <iostream>
#include <fstream>
#include <atlstr.h>	
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPianDlg dialog



CPianDlg::CPianDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIAN_DIALOG, pParent)
	, m_strEdit(_T(""))
	, qVol_field(_T(""))
	, wVol_field(_T(""))
	, eVol_field(_T(""))
	, rVol_field(_T(""))
	, tVol_field(_T(""))
	, yVol_field(_T(""))
	, play_editfield(_T(""))
	, SaveName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	timeNumber = 0.0f;
	str = _T("");

}

void CPianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, m_ctrlSlider);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	DDX_Text(pDX, IDC_EDIT2, qVol_field);
	DDX_Text(pDX, IDC_EDIT9, wVol_field);
	DDX_Text(pDX, IDC_EDIT10, eVol_field);
	DDX_Text(pDX, IDC_EDIT11, rVol_field);
	DDX_Text(pDX, IDC_EDIT12, tVol_field);
	DDX_Text(pDX, IDC_EDIT13, yVol_field);
	DDX_Control(pDX, IDC_EDIT3, Edit_number);
	DDX_Control(pDX, IDC_BUTTON20, play_button);
	DDX_Text(pDX, IDC_EDIT5, play_editfield);
	DDX_Control(pDX, IDC_EDIT5, play_edit);
	DDX_Control(pDX, IDC_BUTTON21, SaveButton);
	DDX_Text(pDX, IDC_EDIT4, SaveName);
	DDX_Control(pDX, IDC_EDIT4, SaveEdit);
}

BEGIN_MESSAGE_MAP(CPianDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPianDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPianDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPianDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPianDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPianDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CPianDlg::OnBnClickedButton6)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON7, &CPianDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPianDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CPianDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CPianDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CPianDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CPianDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CPianDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CPianDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CPianDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CPianDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CPianDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CPianDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CPianDlg::OnBnClickedButton19)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON20, &CPianDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CPianDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CPianDlg::OnBnClickedButton22)
END_MESSAGE_MAP()

// for changing volume
BOOL ChangeVolume(float nVolume)
{
	HRESULT hr = NULL;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
	if (FAILED(hr))
		return FALSE;

	IMMDevice* defaultDevice = NULL;
	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	if (FAILED(hr))
		return FALSE;

	IAudioEndpointVolume* endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
	defaultDevice->Release();
	if (FAILED(hr))
		return FALSE;

	hr = endpointVolume->SetMasterVolumeLevelScalar(nVolume, NULL);
	endpointVolume->Release();

	return SUCCEEDED(hr);
}



// CPianDlg message handlers

BOOL CPianDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_ctrlSlider.SetRange(1, 100);
	m_ctrlSlider.SetPos(100);

	m_strEdit = "100";
	masterVolume = 100;

	qVol = 100;
	qVol_field = "100";

	wVol = 100;
	wVol_field = "100";

	eVol = 100;
	eVol_field = "100";

	rVol = 100;
	rVol_field = "100";

	tVol = 100;
	tVol_field = "100";

	yVol = 100;
	yVol_field = "100";

	recordStarted = false;

	play_editfield = "//://";

	ChangeVolume((float)masterVolume / (float)100);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPianDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPianDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPianDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CPianDlg::OnBnClickedButton1()
{
	ChangeVolume(((float)masterVolume / (float)100) * ((float)qVol / (float)100));
	PlaySound(TEXT("q.wav"), NULL, SND_SYNC);
	if (recordStarted) 
	{
		recorder += "\nq,";
		recorder += std::to_string(qVol);
		recorder += "/";
		recorder += std::to_string(timeNumber);
	}
}


void CPianDlg::OnBnClickedButton2()
{
	ChangeVolume(((float)masterVolume / (float)100) * ((float)wVol / (float)100));
	PlaySound(TEXT("w.wav"), NULL, SND_SYNC);
	if (recordStarted)
	{
		recorder += "\nw,";
		recorder += std::to_string(wVol);
		recorder += "/";
		recorder += std::to_string(timeNumber);
	}
}


void CPianDlg::OnBnClickedButton3()
{
	ChangeVolume(((float)masterVolume / (float)100) * ((float)eVol / (float)100));
	PlaySound(TEXT("e.wav"), NULL, SND_SYNC);
	if (recordStarted)
	{
		recorder += "\ne,";
		recorder += std::to_string(eVol);
		recorder += "/";
		recorder += std::to_string(timeNumber);
	}
}


void CPianDlg::OnBnClickedButton4()
{
	ChangeVolume(((float)masterVolume / (float)100) * ((float)rVol / (float)100));
	PlaySound(TEXT("r.wav"), NULL, SND_SYNC);
	if (recordStarted)
	{
		recorder += "\nr,";
		recorder += std::to_string(rVol);
		recorder += "/";
		recorder += std::to_string(timeNumber);
	}
}


void CPianDlg::OnBnClickedButton5()
{
	ChangeVolume(((float)masterVolume / (float)100) * ((float)tVol / (float)100));
	PlaySound(TEXT("t.wav"), NULL, SND_SYNC);
	if (recordStarted)
	{
		recorder += "\nt,";
		recorder += std::to_string(tVol);
		recorder += "/";
		recorder += std::to_string(timeNumber);
	}
}


void CPianDlg::OnBnClickedButton6()
{
	ChangeVolume(((float)masterVolume / (float)100) * ((float)yVol / (float)100));
	PlaySound(TEXT("y.wav"), NULL, SND_SYNC);
	if (recordStarted)
	{
		recorder += "\ny,";
		recorder += std::to_string(yVol);
		recorder += "/";
		recorder += std::to_string(timeNumber);
	}
}


void CPianDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (nSBCode == SB_THUMBTRACK)
	{
		m_strEdit.Format(_T("%Id"), nPos);
		masterVolume = nPos;
		ChangeVolume((float)masterVolume/(float)100);
		UpdateData(FALSE);
	}
	else
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CPianDlg::OnBnClickedButton7()
{
	if (qVol < 100)
	{
		qVol += 20;
		qVol_field.Format(_T("%Id"), qVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton8()
{
	if (qVol > 20)
	{
		qVol -= 20;
		qVol_field.Format(_T("%Id"), qVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton9()
{
	if (wVol < 100)
	{
		wVol += 20;
		wVol_field.Format(_T("%Id"), wVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton10()
{
	if (wVol > 20)
	{
		wVol -= 20;
		wVol_field.Format(_T("%Id"), wVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton11()
{
	if (eVol < 100)
	{
		eVol += 20;
		eVol_field.Format(_T("%Id"), eVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton12()
{
	if (eVol > 20)
	{
		eVol -= 20;
		eVol_field.Format(_T("%Id"), eVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton13()
{
	if (rVol < 100)
	{
		rVol += 20;
		rVol_field.Format(_T("%Id"), rVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton14()
{
	if (rVol > 20)
	{
		rVol -= 20;
		rVol_field.Format(_T("%Id"), rVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton15()
{
	if (tVol < 100)
	{
		tVol += 20;
		tVol_field.Format(_T("%Id"), tVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton16()
{
	if (tVol > 20)
	{
		tVol -= 20;
		tVol_field.Format(_T("%Id"), tVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton17()
{
	if (yVol < 100)
	{
		yVol += 20;
		yVol_field.Format(_T("%Id"), yVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton18()
{
	if (yVol > 20)
	{
		yVol -= 20;
		yVol_field.Format(_T("%Id"), yVol);
		UpdateData(FALSE);

	}
}


void CPianDlg::OnBnClickedButton19()
{
	if (!recordStarted)
	{
		timeNumber = 0;
		play_button.EnableWindow(FALSE);
		SaveButton.EnableWindow(FALSE);
		SetTimer(TIMERCOUNT, 100, NULL);
		recordStarted = true;
		recorder = "";
	}
	else
	{
		KillTimer(TIMERCOUNT);
		recordStarted = false;
		recorder = std::to_string(timeNumber) + recorder;
		timeNumber = 0;
		recorder += '!';
		play_button.EnableWindow(TRUE);
		SaveButton.EnableWindow(TRUE);
		
	}
}


void CPianDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMERCOUNT)
	{
		timeNumber += 0.1f;
		str.Format(_T("%f"), timeNumber);
		str.Format(_T("%c%c%c"), str[0], str[1], str[2]);
		if (recordStarted)
		{
			Edit_number.SetWindowText(str);
		}
		else
		{
			play_edit.SetWindowText(str+":"+to_string((int)recPlayerTime).c_str());

			if (recPlayer[beep].timeSpawn <= timeNumber)
			{
				ChangeVolume(((float)masterVolume / (float)100) * ((float)recPlayer[beep].volume / (float)100));
				switch (recPlayer[beep].soundName)
				{
				case 'q':
					PlaySound(TEXT("q.wav"), NULL, SND_SYNC); break;
				case 'w':
					PlaySound(TEXT("w.wav"), NULL, SND_SYNC); break;
				case 'e':
					PlaySound(TEXT("e.wav"), NULL, SND_SYNC); break;
				case 'r':
					PlaySound(TEXT("r.wav"), NULL, SND_SYNC); break;
				case 't':
					PlaySound(TEXT("t.wav"), NULL, SND_SYNC); break;
				case 'y':
					PlaySound(TEXT("y.wav"), NULL, SND_SYNC); break;

				default:
					break;
				}
				beep++;
			}
			if (timeNumber>=recPlayerTime)
			{
				KillTimer(TIMERCOUNT);
				play_button.EnableWindow(TRUE);

			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CPianDlg::OnBnClickedButton20()
{

	play_button.EnableWindow(FALSE);

	int i;
	string timeString="";
	for (i = 0; recorder[i] !='\n'; i++)
	{
		timeString += recorder[i];
	}
	recPlayerTime = stof(timeString);
	numberOfBeeps=-1;
	while (recorder[i] != '!')
	{
		if (recorder[i] == '!')	
			break;	

		if (recorder[i] == '\n')
		{
			i++;
			numberOfBeeps++;
			recPlayer[numberOfBeeps].soundName = recorder[i];
			i++;
		}

		if (recorder[i] == ',')
		{
			i++;
			timeString = "";
			while (recorder[i] != '/')
			{
				timeString += recorder[i];
				i++;
			}
			recPlayer[numberOfBeeps].volume = stoi(timeString);
		
			i++;
			timeString = "";
			while (recorder[i] != '\n' && recorder[i] != '!')
			{
				timeString += recorder[i];
				i++;
			}
			recPlayer[numberOfBeeps].timeSpawn = stof(timeString);
		}
	}
	numberOfBeeps++;
	beep = 0;
	SetTimer(TIMERCOUNT, 100, NULL);

}


void CPianDlg::OnBnClickedButton21()
{
	UpdateData(TRUE);
	CT2CA vari(SaveName.GetString());
	string name(vari);
	std::ofstream saveFile(name+".van");
	saveFile << recorder;
	saveFile.close();
	SaveButton.EnableWindow(FALSE);
}


void CPianDlg::OnBnClickedButton22()
{
	CFileDialog dlg(TRUE); // TRUE is to tell the dialog is used as an open CFileDialog.
	if (dlg.DoModal() == IDOK)
	{
		CString fullPathName = dlg.GetPathName(); // get the full path name of the selected file.
		ifstream loadFile(dlg.GetPathName());
		recorder.assign((std::istreambuf_iterator<char>(loadFile)),
			(std::istreambuf_iterator<char>()));
		play_button.EnableWindow(TRUE);
	}
}
