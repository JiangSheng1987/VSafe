// Antivirus.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VSafe.h"
#include "Antivirus.h"
#include "afxdialogex.h"
#include "AntiScan.h"
#include "Md5.h"

// CAntivirus �Ի���

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


// CAntivirus ��Ϣ�������


BOOL CAntivirus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_Brush0.CreateSolidBrush(RGB(255, 255, 255));

	//��������
	m_fBlack00.CreatePointFont(200, L"΢���ź�");
	m_TextVSProtection.SetFont(&m_fBlack00);

	m_fBlack01.CreatePointFont(95, L"΢���ź�");
	m_TextDataBase.SetFont(&m_fBlack01);
	m_TextIsolation.SetFont(&m_fBlack01);
	m_TextTrust.SetFont(&m_fBlack01);
	m_TextCloud.SetFont(&m_fBlack01);

	//��ť
	m_BtPriScan.SetTextFont(120, L"΢���ź�");		   //����
	m_BtPriScan.SetMouseColor(RGB(250, 120, 40));	   //��꾭��
	m_BtPriScan.SetBackColor(RGB(255, 170, 50));	   //����ɫ
	m_BtPriScan.SetTextColor(RGB(255, 255, 255));	   //����ɫ
	m_BtPriScan.SetLockColor(RGB(255, 255, 255));	   //����ɫ

	m_BtAllScan.SetTextFont(120, L"΢���ź�");
	m_BtAllScan.SetMouseColor(RGB(250, 120, 40));
	m_BtAllScan.SetBackColor(RGB(255, 170, 50));
	m_BtAllScan.SetTextColor(RGB(255,255,255));	
	m_BtAllScan.SetLockColor(RGB(255,255, 255));

	m_BtCustomScan.SetTextFont(120, L"΢���ź�");
	m_BtCustomScan.SetMouseColor(RGB(250, 120, 40));
	m_BtCustomScan.SetBackColor(RGB(255, 170, 50));
	m_BtCustomScan.SetTextColor(RGB(255, 255, 255));
	m_BtCustomScan.SetLockColor(RGB(255, 255, 255));

	m_BtCloudScan.SetTextFont(120, L"΢���ź�");
	m_BtCloudScan.SetMouseColor(RGB(250, 120, 40));
	m_BtCloudScan.SetBackColor(RGB(255, 170, 50));
	m_BtCloudScan.SetTextColor(RGB(255, 255, 255));
	m_BtCloudScan.SetLockColor(RGB(255, 255, 255));

	//�����̴߳ӷ���˻�ȡ����
	hUpdataThread = AfxBeginThread(MyThreadUpdata, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//�ػ水ť
HBRUSH CAntivirus::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush0;
	}

	//������������1
	if (IDC_TEXT_VS == pWnd->GetDlgCtrlID()||
		IDC_TEXT_ISOLATION == pWnd->GetDlgCtrlID() ||
		IDC_TEXT_TRUST == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(250, 120, 40));
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}

	//������������2
	if (IDC_TEXT_DATABASE == pWnd->GetDlgCtrlID()||
		IDC_TEXT_CLOUD == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CAntivirus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CClientDC *pDC = new CClientDC(GetDlgItem(IDC_HEART));
	CRect rect;
	GetDlgItem(IDC_HEART)->GetWindowRect(&rect);
	Graphics graphics(pDC->m_hDC);
	Image image(L"res//scan.png");
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	delete pDC;
}

//����ɨ��
void CAntivirus::OnBnClickedButtonScanFast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString FilePath = L"C:\\Windows";
	CAntiScan *pAS = new CAntiScan(FilePath, 0);
	pAS->Create(IDD_DIALOG_ANTISCAN);
	pAS->ShowWindow(SW_NORMAL);
}

//ȫ��ɨ��
void CAntivirus::OnBnClickedButtonScanAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�˴�·��Ϊ����ֵ��ɨ������1�������ٻ�ȡ������Ŀ¼ȫ��ɨ�裻
	CString FilePath = L"D:\\";
	CAntiScan *pAS = new CAntiScan(FilePath, 1);
	pAS->Create(IDD_DIALOG_ANTISCAN);
	pAS->ShowWindow(SW_NORMAL);
	MessageBox(L"ȫ��ɨ��ʱ��ϳ���\n\r������С������\r\n");
}

//�Զ���ɨ��
void CAntivirus::OnBnClickedButtonScanDiy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ļ���·������
	TCHAR szDir[MAX_PATH];
	
	//�����ʼ��
	BROWSEINFO bfi = {};		//�����Ϣ
	ITEMIDLIST *pidl;			//�ļ��б�ʶ���б�
	bfi.hwndOwner = this->m_hWnd;
	bfi.pszDisplayName = szDir;
	bfi.lpszTitle = _T("��ѡ���ļ���");
	bfi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	pidl = SHBrowseForFolder(&bfi);

	//����ȡ����������Ч�ļ��з���NULL  
	if (pidl == NULL)
		return;

	//��ȡ�ļ���·��
	if (SHGetPathFromIDList(pidl, szDir))
	{
		CString FilePath = szDir;	
		CAntiScan *pAS = new CAntiScan(FilePath, 0);
		pAS->Create(IDD_DIALOG_ANTISCAN);
		pAS->ShowWindow(SW_NORMAL);
	}
}

//�Ʋ�ɱ����
void CAntivirus::OnBnClickedButtonCloud()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T("exe"), NULL, 	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,	_T("��ִ�г���|*.exe|�����ļ�|*||"));
	if (dlg.DoModal() == IDOK) {

		//��ȡ�ļ�·��
		CString FilePath = dlg.GetPathName();

		CStringA aPath = CW2A(FilePath.GetBuffer(), CP_THREAD_ACP);
		//��ȡMD5ֵ
		
		CHAR* szMd5 = md5FileValue(aPath.GetBuffer());

		if (!m_Socket.ConnectServer("127.0.0.1", 1234))
		{
			MessageBox(L"���ӷ�����ʧ�ܣ�\r\n����תΪ���ز�ɱ!\r\n", L"Error", MB_OK | MB_ICONWARNING);

			CAntiScan *pAS = new CAntiScan(FilePath, 2);
			pAS->Create(IDD_DIALOG_ANTISCAN);
			pAS->ShowWindow(SW_NORMAL);			
			return;
		}
		//������Ϣ
		m_Socket.Send(QUERY, szMd5, sizeof(szMd5)+1);

		//�ȴ�������Ϣ
		CHATSEND ct = {};
		recv(m_Socket.m_sClient, (char*)&ct, sizeof(CHATSEND), NULL);
		m_Socket.Close();

		if (ct.m_content.buf[0]=='1')
		{
			MessageBox(L"�����ļ�����");						
		
		}
		else
		{
			MessageBox(L"�ļ���������");
		}
		return;
		
	}
}

//�������ݿ�
void CAntivirus::UpdataDataBase(DWORD dwType)
{

	//��������dwType���͹̶����������д 
	m_Socket.Send((DATAPURPOSE)dwType, "cloud", dwType);

	//������Ϣ;
	CHATSEND ct = {};
	//ѭ������
	while (true)
	{
		if (SOCKET_ERROR == recv(m_Socket.m_sClient, (char*)&ct, sizeof(CHATSEND), NULL))
		{			
			break;
		}	
		//���ս�����־
		if (!strcmp(ct.m_content.buf, "~~~end~~~"))
		{
			break;
		}
		m_MD5 = ct.m_content.buf;
		m_vecMD5.push_back(m_MD5);
	}

	//д���ļ�
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

//��ȡ����������߳�
UINT CAntivirus::MyThreadUpdata(LPVOID lpParam)
{
	CAntivirus* pAntivirus = (CAntivirus*)lpParam;

	if (!pAntivirus->m_Socket.ConnectServer("127.0.0.1", 1234))
	{
		pAntivirus->m_TextCloud.SetWindowTextW(L"�����Ʒ����ʧ�ܣ�");
		return 0;
	}

	pAntivirus->UpdataDataBase(3);	
	Sleep(100);
	pAntivirus->UpdataDataBase(2);	
	Sleep(100);
	pAntivirus->UpdataDataBase(1);	

	pAntivirus->m_Socket.Close();

	pAntivirus->m_TextCloud.SetWindowTextW(L"�����Ʒ���˳ɹ���");
	return 0;
}
