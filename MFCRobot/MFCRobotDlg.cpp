
// MFCRobotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCRobot.h"
#include "MFCRobotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCRobotDlg �Ի���



CMFCRobotDlg::CMFCRobotDlg(CWnd* pParent /*=NULL*/) //���캯����ʼֵ�б�
	: CDialogEx(CMFCRobotDlg::IDD, pParent)
	, IP("192.168.1.210")
	, PORT(8000)
	, state()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, IP);
	DDX_Text(pDX, IDC_EDIT_PORT, PORT);
	DDX_Text(pDX, IDC_EDIT_STATE, state);
}

BEGIN_MESSAGE_MAP(CMFCRobotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_SOCKET, &CMFCRobotDlg::OnBnClickedButtonConnectSocket)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_SOCKET, &CMFCRobotDlg::OnBnClickedButtonCloseSocket)
	ON_BN_CLICKED(IDC_BUTTON_START_SERIAL, &CMFCRobotDlg::OnBnClickedButtonStartSerial)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_SERIAL, &CMFCRobotDlg::OnBnClickedButtonCloseSerial)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CMFCRobotDlg::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_BUTTON6_BACKWARD, &CMFCRobotDlg::OnBnClickedButtonBackward)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CMFCRobotDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CMFCRobotDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFCRobotDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDCANCEL, &CMFCRobotDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCRobotDlg ��Ϣ�������

BOOL CMFCRobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCRobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCRobotDlg::OnBnClickedButtonConnectSocket() //�������ӷ�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButtonCloseSocket();
	UpdateData(TRUE);  
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        AfxMessageBox("�׽��ִ���!");
        state = "�׽��ִ���!";
    }
	else
		state = "�׽�����ȷ!";

    // ����һ���µ�Socket�����ӷ�����     
    mfc_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

    ServerAddr.sin_family = AF_INET;    
    ServerAddr.sin_port = htons(PORT);     
    ServerAddr.sin_addr.s_addr = inet_addr(IP); 
    memset(ServerAddr.sin_zero, 0x00, 8);
 
    // �������������������  
    if(connect(mfc_socket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR){
        AfxMessageBox("���ӷ�����ʧ�ܣ�");
		state = "���ӷ�����ʧ��!";
    }  
	else
		state = "���ӷ������ɹ�!";
	UpdateData(FALSE);
}


void CMFCRobotDlg::OnBnClickedButtonCloseSocket() //�ر�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char closeSerial = 0xff;
	if(send(mfc_socket, (char*)&closeSerial, sizeof(closeSerial), 0) == SOCKET_ERROR){
		//AfxMessageBox("δ�ر����ӣ�");
		state = "δ�ر����ӣ�";
	}
	else
		state = "�ѹر����ӣ�";
	closesocket(mfc_socket);    // �ͷ�Windows Socket DLL�������Դ   
    WSACleanup();
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonStartSerial() //�������ڿ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char startSerial = 0xc0;
	if(send(mfc_socket, (char*)&startSerial, sizeof(startSerial), 0) == SOCKET_ERROR){
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ���";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonCloseSerial() //�رմ��ڿ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char closeSerial = 0x80;
	if(send(mfc_socket, (char*)&closeSerial, sizeof(closeSerial), 0) == SOCKET_ERROR){
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ�!";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonForward() //��ǰ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char forward = 0xc8;
	if(send(mfc_socket, (char*)&forward, sizeof(forward), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ���";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonBackward() //���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char backward = 0xc9;
	if(send(mfc_socket, (char*)&backward, sizeof(backward), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ���";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonLeft() //����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char left = 0xca;
	if(send(mfc_socket, (char*)&left, sizeof(left), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ���";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonRight() //����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char right = 0xcb;
	if(send(mfc_socket, (char*)&right, sizeof(right), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ���";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonStop() //ֹͣ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	unsigned char stop = 0xcc;
	if(send(mfc_socket, (char*)&stop, sizeof(stop), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("��Ϣ����ʧ�ܣ�");
		state = "��Ϣ����ʧ�ܣ�";
	}
	else
		state = "��Ϣ���ͳɹ���";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButtonCloseSocket();
	CDialogEx::OnCancel();

}
