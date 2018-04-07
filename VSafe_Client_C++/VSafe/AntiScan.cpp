// AntiScan.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VSafe.h"
#include "AntiScan.h"
#include "afxdialogex.h"
#include "Md5.h"

// CAntiScan �Ի���

IMPLEMENT_DYNAMIC(CAntiScan, CDialogEx)

CAntiScan::CAntiScan(CString FilePath, DWORD dwType, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ANTISCAN, pParent)
{
	m_dwScanType = dwType;
	m_FilePath = FilePath;
	m_FolderPath = FilePath;
}

CAntiScan::~CAntiScan()
{
}

void CAntiScan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANTIVIRUS, m_ListAntiScan);
	DDX_Control(pDX, IDC_TEXT_SCANINFO, m_TextScanInfo);
}


BEGIN_MESSAGE_MAP(CAntiScan, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ANTI_PAUSE, &CAntiScan::OnBnClickedButtonAntiPause)
	ON_BN_CLICKED(IDC_BUTTON_ANTI_CANCLE, &CAntiScan::OnBnClickedButtonAntiCancle)
	ON_BN_CLICKED(IDC_BUTTON_ANTI_OK, &CAntiScan::OnBnClickedButtonAntiOk)
END_MESSAGE_MAP()


// CAntiScan ��Ϣ�������


BOOL CAntiScan::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListAntiScan.AddColumn(3, L"·��", 350, L"MD5", 250, L"����", 100);

	//��ȡ���ݿ�
	ReadDataBase();

	//����ɨ���߳�
	hScanThread = AfxBeginThread(MyThreadScan, this);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CAntiScan::AntiScan()
{
	//����ɨ�����ͷַ�
	switch (m_dwScanType)
	{
	case 0:
		//����ɨ��
		FastScan();
		break;
	case 1:
		//ȫ��ɨ��
		ScanAll();
		break;
	case 2:
		//�ļ�ɨ��
		ScanFile();
		break;		
	case 3:
		//����
		break;
	case 4:
		break;
	default:
		break;
	}
}

//����ɨ��
void CAntiScan::FastScan()
{
	//ɨ�����
	ScanProcess();
	//ɨ��ϵͳ�ļ���
	ScanFloder(m_FolderPath);

	m_TextScanInfo.SetWindowTextW(L"ɨ�����");
	MessageBox(L"ɨ�����!\r\n�봦��");
}

//ȫ��ɨ��
void CAntiScan::ScanAll()
{
	//��ȡ�̷�;
	TCHAR szBuf[1024] = {};
	GetLogicalDriveStrings(1024, szBuf);
	TCHAR *pstr = szBuf;

	while (*pstr)
	{		
		m_vecDisk.push_back(pstr);
		//��ȡ��һ���̷�;
		pstr += _tcslen(pstr) + 1;
	}

	//ɨ�����
	ScanProcess();

	//ѭ�������̷�
	for (DWORD i=0;i<m_vecDisk.size();i++)
	{
		ScanFloder(m_vecDisk[i]);
	}

	MessageBox(L"ɨ�����!\r\n�봦��");	
}


//ɨ�赥���ļ�
void CAntiScan::ScanFile()
{

	//ת���ļ���;
	CStringA FinalFileName = CW2A(m_FilePath.GetBuffer(), CP_THREAD_ACP);

	//��ȡMD5
	char* szMD5 = md5FileValue(FinalFileName.GetBuffer());
	m_ScanMd5 = CA2W(szMD5, CP_THREAD_ACP);

	m_TextScanInfo.SetWindowTextW(L"ɨ�����");
	//�Ա�MD5
	if (DataBaseCMP(m_ScanMd5))
	{	
		m_vecFilePath.push_back(m_FilePath);
		m_ListAntiScan.AddItem(3, m_FilePath, m_ScanMd5, L"�����ļ�");
		MessageBox(L"�����ļ�!\r\n�봦��");
	}
	else
	{
		m_ListAntiScan.AddItem(3, m_FilePath, m_ScanMd5, L"�����ļ�");
		MessageBox(L"�����ļ�!");
	}	
}

//ɨ���ļ���
void CAntiScan::ScanFloder(CString FloderPath)
{	
	//ȡ������
	if (m_IsCancle)
	{
		//��������

		return;
	}

	//��ͣ����
	while (m_IsPause)
	{
	}

	//��·���˳�;
	if (FloderPath.IsEmpty())
	{
		m_IsCancle = true;
		return;
	}

	//�򿪼�;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(FloderPath, &wsd);
	FloderPath += L"\\*";
	hFind = FindFirstFile(FloderPath, &wsd);

	if (hFind == INVALID_HANDLE_VALUE)
	{		
		return;
	}

	do
	{
		//���˱������ϼ�;
		if (!wcscmp(wsd.cFileName, L".")
			|| !wcscmp(wsd.cFileName, L".."))
		{
			continue;
		}
		//�ݹ�����ļ���;
		else if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			CString NextDir = FloderPath.Left(FloderPath.GetLength() - 1);
			NextDir += wsd.cFileName;
			ScanFloder(NextDir);
		}
		//ת���ļ�����ʽ;
		TCHAR* szBuff = wsd.cFileName;
		//��ȡ��׺��;
		TCHAR* szExName = PathFindExtension(szBuff);
		//�ԱȺ�׺��;
		
		//�ԱȺ�׺�����˴�Ҳ��ѡ���ļ����ģ���е��ļ����ͶԱ�
		if (!wcscmp(szExName, L".exe")||
			!wcscmp(szExName, L".EXE"))
		{
			//ƴ���ļ���;
			CString m_ScanFileFath = FloderPath.Left(FloderPath.GetLength() - 1);
			m_ScanFileFath += wsd.cFileName;
			CStringA FinalFileName = CW2A(m_ScanFileFath.GetBuffer(), CP_THREAD_ACP);
			
			//��ȡMD5
			char* szMD5= md5FileValue(FinalFileName.GetBuffer());	
			m_ScanMd5 = CA2W(szMD5, CP_THREAD_ACP);

			//����ɨ��״̬
			CString strScanInfo = L"����ɨ�裺";
			strScanInfo += m_ScanFileFath;
			m_TextScanInfo.SetWindowTextW(strScanInfo);
			
			//�Ա�MD5
			if (DataBaseCMP(m_ScanMd5))
			{	
				m_vecFilePath.push_back(m_ScanFileFath);
				m_ListAntiScan.AddItem(3, m_ScanFileFath, m_ScanMd5, L"�����ļ�");
			}
		}

	} while (FindNextFile(hFind, &wsd));

	FindClose(hFind);

	return;
}

//ɨ�����
void CAntiScan::ScanProcess()
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"HELP ��������ʧ�ܣ�");
		return;
	}

	//��ʼ��������Ϣ�ṹ��;
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapShot, &pi))
	{
		MessageBox(L"��ȡ������Ϣʧ��");
		return;
	}
	do
	{
		TCHAR *szBuf[5] = { new TCHAR[MAX_PATH], new TCHAR[6],  new TCHAR[6],  new TCHAR[6], new TCHAR[MAX_PATH], };
		szBuf[0] = pi.szExeFile;

		//��Ҫ��ȡ·���Ľ���
		HANDLE hPro = OpenProcess(PROCESS_QUERY_INFORMATION
			| PROCESS_QUERY_LIMITED_INFORMATION,
			FALSE, pi.th32ProcessID);
		//��ȡ��������·��;
		if (hPro)
		{
			DWORD dwSize = MAX_PATH;
			QueryFullProcessImageName(hPro, NULL, szBuf[4], &dwSize);
			
		}
		else
		{
			szBuf[4] = L"��Ȩ����";
		}

		CString  FileFathW = szBuf[4];
		CStringA FinalFileName = CW2A( szBuf[4],CP_THREAD_ACP);
		//��ȡMD5
		char* szMD5 = md5FileValue(FinalFileName.GetBuffer());
		m_ScanMd5 = CA2W(szMD5, CP_THREAD_ACP);

		CString strScanInfo = L"����ɨ����̣�";
		strScanInfo += FileFathW;
		m_TextScanInfo.SetWindowTextW(strScanInfo);

		//�Ա�MD5
		if (DataBaseCMP(m_ScanMd5))
		{
			
			if (TerminateProcess(hPro, 0))
			{
				MessageBox(L"���ֿ��ɽ���!\r\n�ѽ�������\r\n");
			}
			else
			{
				MessageBox(L"���ֿ��ɽ���!\r\n����ʧ��!\r\n���ֶ�����");
			}			
			m_vecFilePath.push_back(FileFathW);
			m_ListAntiScan.AddItem(3, FileFathW, m_ScanMd5, L"��������");
		}
		CloseHandle(hPro);
		
	} while (Process32Next(hSnapShot, &pi));

}

//��ȡ�������ݿ�
void CAntiScan::ReadDataBase()
{
	//��ȡ������
	CString strDatabase = szFileName[0];
	CStdioFile sfDatabase;
	if (sfDatabase.Open(strDatabase, CFile::modeRead))
	{		
		CString temp;
		//ѭ����ȡ
		while (sfDatabase.ReadString(temp))
		{
			m_vecVirusDatabase.push_back(temp);
		}
		sfDatabase.Close();
	}
	else
	{
		MessageBox(L"��ȡ���ز�����ʧ�ܣ�");
		m_dwScanType = 4;
		return;
	}

	//��ȡ������
	CString strWhite = szFileName[1];
	CStdioFile sfWhite;
	if (sfWhite.Open(strWhite, CFile::modeRead))
	{
		CString temp;
		//ѭ����ȡ
		while (sfWhite.ReadString(temp))
		{
			m_vecWhite.push_back(temp);
		}
		sfWhite.Close();
	}

	//��ȡ������
	CString strBlack = szFileName[2];
	CStdioFile sfBlack;
	if (sfBlack.Open(strBlack, CFile::modeRead))
	{
		CString temp;
		//ѭ����ȡ
		while (sfBlack.ReadString(temp))
		{
			m_vecBlack.push_back(temp);
		}
		sfBlack.Close();
	}
}

//�Ա����ݿ�
bool CAntiScan::DataBaseCMP(CString strMD5)
{
	//�ԱȰ�����
	for (DWORD i = 0; i < m_vecWhite.size(); i++)
	{
		if (strMD5==m_vecWhite[i])
		{
			return false;
		}
	}

	//�ԱȺ�����
	for (DWORD i = 0; i < m_vecBlack.size(); i++)
	{
		if (strMD5 == m_vecBlack[i])
		{
			return true;
		}
	}

	//�ԱȲ�����
	for (DWORD i = 0; i < m_vecVirusDatabase.size(); i++)
	{
		if (strMD5 == m_vecVirusDatabase[i])
		{
			return true;
		}
	}
	return false;
}


//ȫ��ɨ���߳�
UINT CAntiScan::MyThreadScan(LPVOID lpParam)
{
	CAntiScan* pAntiScan = (CAntiScan*)lpParam;

	pAntiScan->AntiScan();		

	pAntiScan->hScanThread = NULL;

	return 0;
}


//��ͣ����
void CAntiScan::OnBnClickedButtonAntiPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//����δ��ʼ������ͣ
	if (!hScanThread)
	{
		MessageBox(L"ɨ�������ѽ�����");
	}


	m_IsPause = !m_IsPause;

	//���İ�ť״̬
	if (m_IsPause)
	{
		GetDlgItem(IDC_BUTTON_ANTI_PAUSE)->SetWindowTextW(L"����ɨ��");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ANTI_PAUSE)->SetWindowTextW(L"��ͣɨ��");
	}

	
}

//ȡ��ɨ��
void CAntiScan::OnBnClickedButtonAntiCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_IsCancle = true;
}

//������
void CAntiScan::OnBnClickedButtonAntiOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//δ������Ҫ������Ŀ
	if (m_vecFilePath.size()==0)
	{
		MessageBox(L"���޿ɴ�����Ŀ��");
		return;
	}

	//ɾ������
	for (DWORD i=0;i<m_vecFilePath.size();i++)
	{
		DeleteFile(m_vecFilePath[0]);
	}
	MessageBox(L"������ɣ�");
}
