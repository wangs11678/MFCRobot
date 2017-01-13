
// MFCRobotDlg.h : 头文件
//

#pragma once


// CMFCRobotDlg 对话框
class CMFCRobotDlg : public CDialogEx
{
// 构造
public:
	CMFCRobotDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCROBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString IP; //Server IP
	int PORT; //Server Port
	CString state; //Connect State

	//Socket Connection
	WSADATA wsaData;  
    SOCKET mfc_socket;  
    SOCKADDR_IN ServerAddr; 

	afx_msg void OnBnClickedButtonConnectSocket();
	afx_msg void OnBnClickedButtonCloseSocket();
	afx_msg void OnBnClickedButtonStartSerial();
	afx_msg void OnBnClickedButtonCloseSerial();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonBackward();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedCancel();
};
