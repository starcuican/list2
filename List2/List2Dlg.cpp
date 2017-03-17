
// List2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "List2.h"
#include "List2Dlg.h"
#include "afxdialogex.h"

#include "winsock2.h"
#include "mysql.h"
#include <iostream>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CList2Dlg 对话框



CList2Dlg::CList2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIST2_DIALOG, pParent)
	//, m_listmsg(_T(""))
	//, m_msg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CList2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_MSG, m_msg);
	//  DDX_LBString(pDX, IDC_LIST_MSG, m_listmsg);
	//DDX_Control(pDX, IDC_EDIT_MSG, m_msg);
	DDX_Control(pDX, IDC_EDIT_MSG, m_msg1);
	//  DDX_Control(pDX, IDC_LIST_MSG, m_listmsg);
	//  DDX_Control(pDX, IDC_LIST_MSG, m_listmsg);
	DDX_Control(pDX, IDC_LIST1, m_listmsg);
	DDX_Control(pDX, IDC_EDIT2, M_EDIT);
}

BEGIN_MESSAGE_MAP(CList2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CList2Dlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CList2Dlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_CREATE, &CList2Dlg::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_BTN_FOND, &CList2Dlg::OnBnClickedBtnFond)
	ON_BN_CLICKED(IDC_BTN_SMTING, &CList2Dlg::OnBnClickedBtnSmting)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CList2Dlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_ADD, &CList2Dlg::OnBnClickedBtnAdd)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CList2Dlg::OnEnKillfocusEdit2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CList2Dlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CList2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CList2Dlg 消息处理程序

BOOL CList2Dlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_listmsg.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_listmsg.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100, 0);
	m_listmsg.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100, 1);
	m_listmsg.InsertColumn(2, _T("Num"), LVCFMT_LEFT, 100, 2);
	M_EDIT.ShowWindow(SW_HIDE);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CList2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CList2Dlg::OnPaint()
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
HCURSOR CList2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


MYSQL m_sqlconn;
void CList2Dlg::OnBnClickedBtnConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == mysql_library_init(0, NULL, NULL))
	{
	}
	else
	{
		AfxMessageBox(_T("mysql_library_init() failed"));
		return;
	}

	//初始化数据结构
	if (NULL != mysql_init(&m_sqlconn))
	{
	}
	else
	{
		AfxMessageBox(_T("mysql_init() failed"));
		return;
	}

	//在连接数据库之前，设置额外的连接选项  
	//可以设置的选项很多，这里设置字符集，否则无法处理中文  
	if (0 == mysql_options(&m_sqlconn, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
	}
	else
	{
		AfxMessageBox(_T("mysql_options() failed"));
		return;
	}
	//连接数据库

	if (NULL!=mysql_real_connect(&m_sqlconn, "localhost", "root", "root", "mysql", 3306, NULL, 0))//服务器地址，可以直接填入IP
	{
		AfxMessageBox(_T("连接数据库成功"));
		
	}
	else
	{
		AfxMessageBox(_T("连接数据库失败"));
		CString e = mysql_error(&m_sqlconn);
		AfxMessageBox(e);
		return;
	}
}


void CList2Dlg::OnBnClickedBtnLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString s1;
	CString s2;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(s1);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(s2);
	if (s1 == "root" | s2 == "root")
	{
		AfxMessageBox(_T("登陆成功"));
		//dlg.DoModal();
	}
	else
	{
		AfxMessageBox(_T("登陆失败"));
		return;
	}

}

string sqlstr;
//MYSQL_RES *result = NULL;
//MYSQL_ROW row = NULL;
//string res;
void CList2Dlg::OnBnClickedBtnCreate()
{
	// TODO: 在此添加控件通知处理程序代码
	//创建一个表  

	sqlstr = "CREATE TABLE IF NOT EXISTS sssss";
	sqlstr += "(";
	sqlstr +=
		"user_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'Unique User ID',";
	sqlstr +=
		"user_name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT 'Name Of User',";
	sqlstr +=
		"user_second_sum INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'The Summation Of Using Time'";
	sqlstr += ");";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str())) 
	{
		AfxMessageBox(_T("建表成功"));
	}
	else {
		AfxMessageBox(_T("建表失败"));
		mysql_close(&m_sqlconn);
		return ;
	}

	//向表中插入数据
	sqlstr = "INSERT INTO sssss(user_name) VALUES('学    校'),('年级数量'),('班级数量'),('老师人数'),('学生人数');";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		//AfxMessageBox(_T("插入数据成功"));
	}
	else
	{
		AfxMessageBox(_T("插入数据失败"));
		CString  ee = mysql_error(&m_sqlconn);
		AfxMessageBox(ee);
		mysql_close(&m_sqlconn);
		return;
	}




}

MYSQL_RES *result = NULL;
MYSQL_ROW row;
int m_Row;
int m_Col;
void CList2Dlg::OnBnClickedBtnFond()
{
	// TODO: 在此添加控件通知处理程序代码
	
	sqlstr = "SELECT user_id FROM sssss";
	
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		AfxMessageBox(_T("获取数据成功"));

		//一次性取得数据集
		result = mysql_store_result(&m_sqlconn);

		//取得并打印行数
		int rowcount = mysql_num_rows(result);
		UpdateData(TRUE);

		CString s1;
		s1= "行数：";
		
		GetDlgItem(IDC_EDIT_MSG)->SetWindowTextA(s1);
		m_msg1.SetSel(0, -1);
		SetDlgItemInt(IDC_EDIT_MSG, rowcount, sizeof(rowcount));
		m_msg1.ReplaceSel(s1);

		UpdateData(FALSE);

		//取得并打印各字段名称
		/*unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		for (unsigned int i = 0; i < fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			
		}*/
		
		char * ch_query;
		ch_query = "SELECT * FROM sssss";
		if (mysql_real_query(&m_sqlconn, "SELECT * FROM sssss", (UINT)strlen(ch_query)) != 0)
		{
			AfxMessageBox(_T("读取数据库表失败"));
			return;
		}

		if (!(result = mysql_use_result(&m_sqlconn)))
		{
			AfxMessageBox(_T("读取数据集失败"));
			return;
		}
		
		CString str;
		int i = 0;
		
		while (row = mysql_fetch_row(result))
		{

			str.Format(_T("%s"), row[0]);
			m_listmsg.InsertItem(i, str);
			str.Format(_T("%s"), row[1]);
			int j = 1;
			m_listmsg.SetItemText(i, j, str);
			str.Format(_T("%s"), row[2]);
			int k = 2;
			m_listmsg.SetItemText(i, k, str);
			i++;
			/*str.Format(_T("%s"), row[1]);
			m_listmsg.InsertItem(i,str);
			m_listmsg.SetItemText(1, 1, str);*/
			/*str.Format(_T("%s"), row[2]);
			m_listmsg.InsertItem(i, str);
			m_listmsg.SetItemText(0, 2, str);*/
			
			//j++;

		}

		//rowcount = GetDlgItemInt(IDC_EDIT_MSG);
		//GetDlgItemInt(m_msg, rowcount, sizeof(rowcount));
		//GetDlgItem(IDC_EDIT_MSG)->SetWindowTextA(rowcount);
		/*UpdateData(TRUE);
		CString s1;
		s1 = "shanchu chenggong";
		GetDlgItem(IDC_EDIT_MSG)->SetWindowTextA(s1);*/
		


	}
	else
	{
		AfxMessageBox(_T("获取数据失败"));
		CString  eee = mysql_error(&m_sqlconn);
		AfxMessageBox(eee);
		return;
	}
}





void CList2Dlg::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码

	/*UpdateData(TRUE);
	CString s1;
	s1 = "shanchu chenggong";
	GetDlgItem(IDC_EDIT_MSG)->SetWindowTextA(s1);
	//UpdateData(FALSE);*/
	//m_listmsg.SetWindowText(s1);
	//删除刚才建的表  
	sqlstr = "DROP TABLE sssss";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		AfxMessageBox(_T("删除成功"));
	}
	else {
		AfxMessageBox(_T("删除失败"));
		mysql_close(&m_sqlconn);
		return ;
	}
	mysql_free_result(result);
	mysql_close(&m_sqlconn);
	mysql_server_end();


	m_listmsg.DeleteAllItems();
	//system("pause");
	return;
}


void CList2Dlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	/*CString strUsername, strList, strRemark, strSQL; strSQL.Format("insert into sssss(user_id,user_name,user_second_sum) values(/'%s/',/'%s/',/'%s/')", strUsername, strList, strRemark);
	if (mysql_real_query(&m_sqlconn, (char*)(LPCTSTR)strSQL, (UINT)strSQL.GetLength()) != 0) 
	{ ，sssss(user_id)VALUES('6'),sssss(user_second_sum)VALUES('6')
		AfxMessageBox("增添失败");
		return;
	}*/

	sqlstr = "INSERT INTO sssss(user_name,user_second_sum) VALUES('0',0) ;";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		AfxMessageBox(_T("添加数据成功"));
	}
	else
	{
		AfxMessageBox(_T("添加数据失败"));
		CString  ee = mysql_error(&m_sqlconn);
		AfxMessageBox(ee);
		mysql_close(&m_sqlconn);
		return;
	}
}

CString tem;
char cBuf[1024];
void CList2Dlg::OnEnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	M_EDIT.GetWindowText(tem);//得到用户输入的新内容
	m_listmsg.SetItemText(m_Row, m_Col, tem);//设置编辑框新内容
	M_EDIT.ShowWindow(SW_HIDE);
	
	
}


void CList2Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW*pNMlistview = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMlistview->iItem;//获取选中的行
	m_Col = pNMlistview->iSubItem;//获取选中列

	if (pNMlistview->iSubItem != 0)//如果选择的是子项
	{
		m_listmsg.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获取子项的rect
		M_EDIT.SetParent(&m_listmsg);//转换坐标为列表框坐标
		M_EDIT.MoveWindow(rc);//移动edit控件到rect所在位置；
		M_EDIT.SetWindowText(m_listmsg.GetItemText(m_Row, m_Col));//将该子项中的值放置在edit控件中
		M_EDIT.ShowWindow(SW_SHOW);//显示edit控件
		M_EDIT.SetFocus();//设置edit控件焦点
		M_EDIT.ShowCaret();//显示光标
		M_EDIT.SetSel(-1);
	}
	*pResult = 0;
}


void CList2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listmsg.DeleteAllItems();
}


void CList2Dlg::OnBnClickedBtnSmting()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_listmsg.GetItemCount() == 0)
	{
		AfxMessageBox(_T("没有数据要保存"));
		return;
	}

	sprintf_s(cBuf, "update sssss set user_second_sum = '%s' where user_id = '%d'", tem, m_Row + 1);
	if (0 == mysql_query(&m_sqlconn, cBuf))
	{
		AfxMessageBox(_T("修改数据成功"));
	}
	else
	{
		AfxMessageBox(_T("修改数据失败"));
		CString  ee = mysql_error(&m_sqlconn);
		AfxMessageBox(ee);
		mysql_close(&m_sqlconn);
		return;
	}
	/*string strSql;
	//const char * buf= strSql.data();
	//sprintf_s(buf,_T(" update sssss set user_second_sum = '%s' where user_id = '%s'"),);
	char cBuf[1024];
	sprintf_s(cBuf, "update sssss set user_second_sum = '%d' where user_id = '%d'", 1, 1);
	if (0 == mysql_query(&m_sqlconn, cBuf))
	{
		AfxMessageBox(_T("修改数据成功"));
	}
	else
	{
		AfxMessageBox(_T("修改数据失败"));
		CString  ee = mysql_error(&m_sqlconn);
		AfxMessageBox(ee);
		mysql_close(&m_sqlconn);
		return;
	}*/
	//string strSql = (_T(" update sssss set user_second_sum = '1' where user_id = '2'"),1,2);

	/*string strSql;
	strSql = (_T(" update sssss set user_second_sum = '%d' where user_id = '%d'",1,5));
	if (0 == mysql_query(&m_sqlconn, strSql.c_str()))
	{
	AfxMessageBox(_T("修改数据成功"));
	}
	else
	{
	AfxMessageBox(_T("修改数据失败"));
	CString  ee = mysql_error(&m_sqlconn);
	AfxMessageBox(ee);
	mysql_close(&m_sqlconn);
	return;
	}*/
}