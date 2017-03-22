
// List2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CList2Dlg 对话框
class CList2Dlg : public CDialogEx
{
// 构造
public:
	CList2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST2_DIALOG };
#endif

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
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedBtnFond();
//	CListBox m_listmsg;
	//CEdit m_msg;
//	CString m_listmsg;
//	CString m_msg;
	afx_msg void OnBnClickedBtnSmting();
	afx_msg void OnBnClickedBtnDelete();
//	int m_msg;
//	CString m_msg;
	//CEdit m_msg;
	CEdit m_msg1;
//	CListBox m_listmsg;
//	CListCtrl m_listmsg;
	CListCtrl m_listmsg;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnEnKillfocusEdit2();
	CEdit M_EDIT;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnIdok();
	afx_msg void OnBnClickedBtnSelect();
	CListCtrl m_list2;
	CEdit m_xianshi;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio3();
	CButton m_id1;
//	int m_name1;
//	int m_num1;
	CButton m_name1;
	CButton m_num1;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
