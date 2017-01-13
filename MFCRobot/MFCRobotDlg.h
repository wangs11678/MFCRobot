
// MFCRobotDlg.h : ͷ�ļ�
//

#pragma once


// CMFCRobotDlg �Ի���
class CMFCRobotDlg : public CDialogEx
{
// ����
public:
	CMFCRobotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCROBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
