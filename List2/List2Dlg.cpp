
// List2Dlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CList2Dlg �Ի���



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


// CList2Dlg ��Ϣ�������

BOOL CList2Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_listmsg.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_listmsg.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100, 0);
	m_listmsg.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100, 1);
	m_listmsg.InsertColumn(2, _T("Num"), LVCFMT_LEFT, 100, 2);
	M_EDIT.ShowWindow(SW_HIDE);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CList2Dlg::OnPaint()
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
HCURSOR CList2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


MYSQL m_sqlconn;
void CList2Dlg::OnBnClickedBtnConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (0 == mysql_library_init(0, NULL, NULL))
	{
	}
	else
	{
		AfxMessageBox(_T("mysql_library_init() failed"));
		return;
	}

	//��ʼ�����ݽṹ
	if (NULL != mysql_init(&m_sqlconn))
	{
	}
	else
	{
		AfxMessageBox(_T("mysql_init() failed"));
		return;
	}

	//���������ݿ�֮ǰ�����ö��������ѡ��  
	//�������õ�ѡ��ܶ࣬���������ַ����������޷���������  
	if (0 == mysql_options(&m_sqlconn, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
	}
	else
	{
		AfxMessageBox(_T("mysql_options() failed"));
		return;
	}
	//�������ݿ�

	if (NULL!=mysql_real_connect(&m_sqlconn, "localhost", "root", "root", "mysql", 3306, NULL, 0))//��������ַ������ֱ������IP
	{
		AfxMessageBox(_T("�������ݿ�ɹ�"));
		
	}
	else
	{
		AfxMessageBox(_T("�������ݿ�ʧ��"));
		CString e = mysql_error(&m_sqlconn);
		AfxMessageBox(e);
		return;
	}
}


void CList2Dlg::OnBnClickedBtnLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString s1;
	CString s2;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(s1);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(s2);
	if (s1 == "root" | s2 == "root")
	{
		AfxMessageBox(_T("��½�ɹ�"));
		//dlg.DoModal();
	}
	else
	{
		AfxMessageBox(_T("��½ʧ��"));
		return;
	}

}

string sqlstr;
//MYSQL_RES *result = NULL;
//MYSQL_ROW row = NULL;
//string res;
void CList2Dlg::OnBnClickedBtnCreate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����һ����  

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
		AfxMessageBox(_T("����ɹ�"));
	}
	else {
		AfxMessageBox(_T("����ʧ��"));
		mysql_close(&m_sqlconn);
		return ;
	}

	//����в�������
	sqlstr = "INSERT INTO sssss(user_name) VALUES('ѧ    У'),('�꼶����'),('�༶����'),('��ʦ����'),('ѧ������');";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		//AfxMessageBox(_T("�������ݳɹ�"));
	}
	else
	{
		AfxMessageBox(_T("��������ʧ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	sqlstr = "SELECT user_id FROM sssss";
	
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		AfxMessageBox(_T("��ȡ���ݳɹ�"));

		//һ����ȡ�����ݼ�
		result = mysql_store_result(&m_sqlconn);

		//ȡ�ò���ӡ����
		int rowcount = mysql_num_rows(result);
		UpdateData(TRUE);

		CString s1;
		s1= "������";
		
		GetDlgItem(IDC_EDIT_MSG)->SetWindowTextA(s1);
		m_msg1.SetSel(0, -1);
		SetDlgItemInt(IDC_EDIT_MSG, rowcount, sizeof(rowcount));
		m_msg1.ReplaceSel(s1);

		UpdateData(FALSE);

		//ȡ�ò���ӡ���ֶ�����
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
			AfxMessageBox(_T("��ȡ���ݿ��ʧ��"));
			return;
		}

		if (!(result = mysql_use_result(&m_sqlconn)))
		{
			AfxMessageBox(_T("��ȡ���ݼ�ʧ��"));
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
		AfxMessageBox(_T("��ȡ����ʧ��"));
		CString  eee = mysql_error(&m_sqlconn);
		AfxMessageBox(eee);
		return;
	}
}





void CList2Dlg::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*UpdateData(TRUE);
	CString s1;
	s1 = "shanchu chenggong";
	GetDlgItem(IDC_EDIT_MSG)->SetWindowTextA(s1);
	//UpdateData(FALSE);*/
	//m_listmsg.SetWindowText(s1);
	//ɾ���ղŽ��ı�  
	sqlstr = "DROP TABLE sssss";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		AfxMessageBox(_T("ɾ���ɹ�"));
	}
	else {
		AfxMessageBox(_T("ɾ��ʧ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*CString strUsername, strList, strRemark, strSQL; strSQL.Format("insert into sssss(user_id,user_name,user_second_sum) values(/'%s/',/'%s/',/'%s/')", strUsername, strList, strRemark);
	if (mysql_real_query(&m_sqlconn, (char*)(LPCTSTR)strSQL, (UINT)strSQL.GetLength()) != 0) 
	{ ��sssss(user_id)VALUES('6'),sssss(user_second_sum)VALUES('6')
		AfxMessageBox("����ʧ��");
		return;
	}*/

	sqlstr = "INSERT INTO sssss(user_name,user_second_sum) VALUES('0',0) ;";
	if (0 == mysql_query(&m_sqlconn, sqlstr.c_str()))
	{
		AfxMessageBox(_T("������ݳɹ�"));
	}
	else
	{
		AfxMessageBox(_T("�������ʧ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	M_EDIT.GetWindowText(tem);//�õ��û������������
	m_listmsg.SetItemText(m_Row, m_Col, tem);//���ñ༭��������
	M_EDIT.ShowWindow(SW_HIDE);
	
	
}


void CList2Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW*pNMlistview = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMlistview->iItem;//��ȡѡ�е���
	m_Col = pNMlistview->iSubItem;//��ȡѡ����

	if (pNMlistview->iSubItem != 0)//���ѡ���������
	{
		m_listmsg.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//��ȡ�����rect
		M_EDIT.SetParent(&m_listmsg);//ת������Ϊ�б������
		M_EDIT.MoveWindow(rc);//�ƶ�edit�ؼ���rect����λ�ã�
		M_EDIT.SetWindowText(m_listmsg.GetItemText(m_Row, m_Col));//���������е�ֵ������edit�ؼ���
		M_EDIT.ShowWindow(SW_SHOW);//��ʾedit�ؼ�
		M_EDIT.SetFocus();//����edit�ؼ�����
		M_EDIT.ShowCaret();//��ʾ���
		M_EDIT.SetSel(-1);
	}
	*pResult = 0;
}


void CList2Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listmsg.DeleteAllItems();
}


void CList2Dlg::OnBnClickedBtnSmting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_listmsg.GetItemCount() == 0)
	{
		AfxMessageBox(_T("û������Ҫ����"));
		return;
	}

	sprintf_s(cBuf, "update sssss set user_second_sum = '%s' where user_id = '%d'", tem, m_Row + 1);
	if (0 == mysql_query(&m_sqlconn, cBuf))
	{
		AfxMessageBox(_T("�޸����ݳɹ�"));
	}
	else
	{
		AfxMessageBox(_T("�޸�����ʧ��"));
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
		AfxMessageBox(_T("�޸����ݳɹ�"));
	}
	else
	{
		AfxMessageBox(_T("�޸�����ʧ��"));
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
	AfxMessageBox(_T("�޸����ݳɹ�"));
	}
	else
	{
	AfxMessageBox(_T("�޸�����ʧ��"));
	CString  ee = mysql_error(&m_sqlconn);
	AfxMessageBox(ee);
	mysql_close(&m_sqlconn);
	return;
	}*/
}