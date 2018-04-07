// Antivirus.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "Antivirus.h"
#include "afxdialogex.h"
#include "AntiScan.h"
#include "Md5.h"

// CAntivirus 对话框

IMPLEMENT_DYNAMIC(CAntivirus, CDialogEx)

CAntivirus::CAntivirus(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG0, pParent)
{

}

CAntivirus::~CAntivirus()
{
}

void CAntivirus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_VS, m_TextVSProtection);
	DDX_Control(pDX, IDC_TEXT_DATABASE, m_TextDataBase);
	DDX_Control(pDX, IDC_TEXT_ISOLATION, m_TextIsolation);
	DDX_Control(pDX, IDC_TEXT_TRUST, m_TextTrust);
	DDX_Control(pDX, IDC_BUTTON_01, m_BtAllScan);
	DDX_Control(pDX, IDC_BUTTON_02, m_BtPriScan);
	DDX_Control(pDX, IDC_BUTTON_03, m_BtCustomScan);
	DDX_Control(pDX, IDC_BUTTON_04, m_BtCloudScan);
	DDX_Control(pDX, IDC_TEXT_CLOUD, m_TextCloud);
}


BEGIN_MESSAGE_MAP(CAntivirus, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SCAN_FAST, &CAntivirus::OnBnClickedButtonScanFast)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_ALL, &CAntivirus::OnBnClickedButtonScanAll)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_DIY, &CAntivirus::OnBnClickedButtonScanDiy)
	ON_BN_CLICKED(IDC_BUTTON_CLOUD, &CAntivirus::OnBnClickedButtonCloud)
END_MESSAGE_MAP()


// CAntivirus 消息处理程序


BOOL CAntivirus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Brush0.CreateSolidBrush(RGB(255, 255, 255));

	//加载文字
	m_fBlack00.CreatePointFont(200, L"微软雅黑");
	m_TextVSProtection.SetFont(&m_fBlack00);

	m_fBlack01.CreatePointFont(95, L"微软雅黑");
	m_TextDataBase.SetFont(&m_fBlack01);
	m_TextIsolation.SetFont(&m_fBlack01);
	m_TextTrust.SetFont(&m_fBlack01);
	m_TextCloud.SetFont(&m_fBlack01);

	//按钮
	m_BtPriScan.SetTextFont(120, L"微软雅黑");		   //字体
	m_BtPriScan.SetMouseColor(RGB(250, 120, 40));	   //鼠标经过
	m_BtPriScan.SetBackColor(RGB(255, 170, 50));	   //背景色
	m_BtPriScan.SetTextColor(RGB(255, 255, 255));	   //文字色
	m_BtPriScan.SetLockColor(RGB(255, 255, 255));	   //锁定色

	m_BtAllScan.SetTextFont(120, L"微软雅黑");
	m_BtAllScan.SetMouseColor(RGB(250, 120, 40));
	m_BtAllScan.SetBackColor(RGB(255, 170, 50));
	m_BtAllScan.SetTextColor(RGB(255,255,255));	
	m_BtAllScan.SetLockColor(RGB(255,255, 255));

	m_BtCustomScan.SetTextFont(120, L"微软雅黑");
	m_BtCustomScan.SetMouseColor(RGB(250, 120, 40));
	m_BtCustomScan.SetBackColor(RGB(255, 170, 50));
	m_BtCustomScan.SetTextColor(RGB(255, 255, 255));
	m_BtCustomScan.SetLockColor(RGB(255, 255, 255));

	m_BtCloudScan.SetTextFont(120, L"微软雅黑");
	m_BtCloudScan.SetMouseColor(RGB(250, 120, 40));
	m_BtCloudScan.SetBackColor(RGB(255, 170, 50));
	m_BtCloudScan.SetTextColor(RGB(255, 255, 255));
	m_BtCloudScan.SetLockColor(RGB(255, 255, 255));

	//创建线程从服务端获取数据
	hUpdataThread = AfxBeginThread(MyThreadUpdata, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//重绘按钮
HBRUSH CAntivirus::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush0;
	}

	//更改文字属性1
	if (IDC_TEXT_VS == pWnd->GetDlgCtrlID()||
		IDC_TEXT_ISOLATION == pWnd->GetDlgCtrlID() ||
		IDC_TEXT_TRUST == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(250, 120, 40));
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}

	//更改文字属性2
	if (IDC_TEXT_DATABASE == pWnd->GetDlgCtrlID()||
		IDC_TEXT_CLOUD == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CAntivirus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CClientDC *pDC = new CClientDC(GetDlgItem(IDC_HEART));
	CRect rect;
	GetDlgItem(IDC_HEART)->GetWindowRect(&rect);
	Graphics graphics(pDC->m_hDC);
	Image image(L"res//scan.png");
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	delete pDC;
}

//快速扫描
void CAntivirus::OnBnClickedButtonScanFast()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePath = L"C:\\Windows";
	CAntiScan *pAS = new CAntiScan(FilePath, 0);
	pAS->Create(IDD_DIALOG_ANTISCAN);
	pAS->ShowWindow(SW_NORMAL);
}

//全盘扫描
void CAntivirus::OnBnClickedButtonScanAll()
{
	// TODO: 在此添加控件通知处理程序代码
	//此处路径为任意值，扫描类型1，类内再获取驱动器目录全盘扫描；
	CString FilePath = L"D:\\";
	CAntiScan *pAS = new CAntiScan(FilePath, 1);
	pAS->Create(IDD_DIALOG_ANTISCAN);
	pAS->ShowWindow(SW_NORMAL);
	MessageBox(L"全盘扫描时间较长！\n\r可先最小化程序！\r\n");
}

//自定义扫描
void CAntivirus::OnBnClickedButtonScanDiy()
{
	// TODO: 在此添加控件通知处理程序代码

	//文件夹路径缓存
	TCHAR szDir[MAX_PATH];
	
	//必须初始化
	BROWSEINFO bfi = {};		//浏览信息
	ITEMIDLIST *pidl;			//文件夹标识符列表
	bfi.hwndOwner = this->m_hWnd;
	bfi.pszDisplayName = szDir;
	bfi.lpszTitle = _T("请选择文件夹");
	bfi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	pidl = SHBrowseForFolder(&bfi);

	//点了取消，或者无效文件夹返回NULL  
	if (pidl == NULL)
		return;

	//获取文件夹路径
	if (SHGetPathFromIDList(pidl, szDir))
	{
		CString FilePath = szDir;	
		CAntiScan *pAS = new CAntiScan(FilePath, 0);
		pAS->Create(IDD_DIALOG_ANTISCAN);
		pAS->ShowWindow(SW_NORMAL);
	}
}

//云查杀服务
void CAntivirus::OnBnClickedButtonCloud()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("exe"), NULL, 	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,	_T("可执行程序|*.exe|所有文件|*||"));
	if (dlg.DoModal() == IDOK) {

		//获取文件路径
		CString FilePath = dlg.GetPathName();

		CStringA aPath = CW2A(FilePath.GetBuffer(), CP_THREAD_ACP);
		//获取MD5值
		
		CHAR* szMd5 = md5FileValue(aPath.GetBuffer());

		if (!m_Socket.ConnectServer("127.0.0.1", 1234))
		{
			MessageBox(L"连接服务器失败！\r\n即将转为本地查杀!\r\n", L"Error", MB_OK | MB_ICONWARNING);

			CAntiScan *pAS = new CAntiScan(FilePath, 2);
			pAS->Create(IDD_DIALOG_ANTISCAN);
			pAS->ShowWindow(SW_NORMAL);			
			return;
		}
		//发送消息
		m_Socket.Send(QUERY, szMd5, sizeof(szMd5)+1);

		//等待接收消息
		CHATSEND ct = {};
		recv(m_Socket.m_sClient, (char*)&ct, sizeof(CHATSEND), NULL);
		m_Socket.Close();

		if (ct.m_content.buf[0]=='1')
		{
			MessageBox(L"病毒文件！！");						
		
		}
		else
		{
			MessageBox(L"文件正常！！");
		}
		return;
		
	}
}

//更新数据库
void CAntivirus::UpdataDataBase(DWORD dwType)
{

	//发送请求；dwType类型固定，内容随便写 
	m_Socket.Send((DATAPURPOSE)dwType, "cloud", dwType);

	//接收消息;
	CHATSEND ct = {};
	//循环接收
	while (true)
	{
		if (SOCKET_ERROR == recv(m_Socket.m_sClient, (char*)&ct, sizeof(CHATSEND), NULL))
		{			
			break;
		}	
		//接收结束标志
		if (!strcmp(ct.m_content.buf, "~~~end~~~"))
		{
			break;
		}
		m_MD5 = ct.m_content.buf;
		m_vecMD5.push_back(m_MD5);
	}

	//写入文件
	CString sFile = szFileName[dwType];
	CStdioFile sfFile;
	if (sfFile.Open(sFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		for (DWORD i=0;i<m_vecMD5.size();i++)
		{
			m_vecMD5[i] += L"\n\r";
			sfFile.WriteString(m_vecMD5[i]);
		}
		sfFile.Close();
	}

	
}

//获取服务端数据线程
UINT CAntivirus::MyThreadUpdata(LPVOID lpParam)
{
	CAntivirus* pAntivirus = (CAntivirus*)lpParam;

	if (!pAntivirus->m_Socket.ConnectServer("127.0.0.1", 1234))
	{
		pAntivirus->m_TextCloud.SetWindowTextW(L"连接云服务端失败！");
		return 0;
	}

	pAntivirus->UpdataDataBase(3);	
	Sleep(100);
	pAntivirus->UpdataDataBase(2);	
	Sleep(100);
	pAntivirus->UpdataDataBase(1);	

	pAntivirus->m_Socket.Close();

	pAntivirus->m_TextCloud.SetWindowTextW(L"连接云服务端成功！");
	return 0;
}
