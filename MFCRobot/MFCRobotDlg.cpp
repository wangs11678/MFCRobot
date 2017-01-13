
// MFCRobotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCRobot.h"
#include "MFCRobotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCRobotDlg 对话框



CMFCRobotDlg::CMFCRobotDlg(CWnd* pParent /*=NULL*/) //构造函数初始值列表
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


// CMFCRobotDlg 消息处理程序

BOOL CMFCRobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCRobotDlg::OnBnClickedButtonConnectSocket() //请求连接服务器
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonCloseSocket();
	UpdateData(TRUE);  
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        AfxMessageBox("套接字错误!");
        state = "套接字错误!";
    }
	else
		state = "套接字正确!";

    // 创建一个新的Socket来连接服务器     
    mfc_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

    ServerAddr.sin_family = AF_INET;    
    ServerAddr.sin_port = htons(PORT);     
    ServerAddr.sin_addr.s_addr = inet_addr(IP); 
    memset(ServerAddr.sin_zero, 0x00, 8);
 
    // 向服务器发出连接请求  
    if(connect(mfc_socket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR){
        AfxMessageBox("连接服务器失败！");
		state = "连接服务器失败!";
    }  
	else
		state = "连接服务器成功!";
	UpdateData(FALSE);
}


void CMFCRobotDlg::OnBnClickedButtonCloseSocket() //关闭连接
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char closeSerial = 0xff;
	if(send(mfc_socket, (char*)&closeSerial, sizeof(closeSerial), 0) == SOCKET_ERROR){
		//AfxMessageBox("未关闭连接！");
		state = "未关闭连接！";
	}
	else
		state = "已关闭连接！";
	closesocket(mfc_socket);    // 释放Windows Socket DLL的相关资源   
    WSACleanup();
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonStartSerial() //启动串口控制
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char startSerial = 0xc0;
	if(send(mfc_socket, (char*)&startSerial, sizeof(startSerial), 0) == SOCKET_ERROR){
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功！";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonCloseSerial() //关闭串口控制
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char closeSerial = 0x80;
	if(send(mfc_socket, (char*)&closeSerial, sizeof(closeSerial), 0) == SOCKET_ERROR){
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功!";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonForward() //向前
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char forward = 0xc8;
	if(send(mfc_socket, (char*)&forward, sizeof(forward), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功！";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonBackward() //向后
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char backward = 0xc9;
	if(send(mfc_socket, (char*)&backward, sizeof(backward), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功！";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonLeft() //向左
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char left = 0xca;
	if(send(mfc_socket, (char*)&left, sizeof(left), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功！";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonRight() //向右
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char right = 0xcb;
	if(send(mfc_socket, (char*)&right, sizeof(right), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功！";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedButtonStop() //停止
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	unsigned char stop = 0xcc;
	if(send(mfc_socket, (char*)&stop, sizeof(stop), 0) == SOCKET_ERROR)
	{
		AfxMessageBox("消息发送失败！");
		state = "消息发送失败！";
	}
	else
		state = "消息发送成功！";
	UpdateData(FALSE); 
}


void CMFCRobotDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonCloseSocket();
	CDialogEx::OnCancel();

}
