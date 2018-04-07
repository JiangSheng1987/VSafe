// PEInfo.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "PEInfo.h"
#include "PERva2Fo.h"
#include "PETimeData.h"
#include "PESectionsInfo.h"
#include "PEDirectory.h"




CPEInfo::CPEInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEINFO_DIALOG, pParent)
	, m_DeleFileName(_T(""))
	, m_AddressOfEntryPoint(_T(""))
	, m_ImageBase(_T(""))
	, m_SizeOfImage(_T(""))
	, m_BaseOfCode(_T(""))
	, m_BaseOfData(_T(""))
	, m_SectionAlignment(_T(""))
	, m_FileAlignment(_T(""))
	, m_Magic(_T(""))
	, m_Subsystem(_T(""))
	, m_NumberOfSections(_T(""))
	, m_TimeDateStamp(_T(""))
	, m_SizeOfHeaders(_T(""))
	, m_DllCharacteristics(_T(""))
	, m_NumberOfRvaAndSizes(_T(""))
	, m_SizeOfOptionalHeader(_T(""))
	, m_CheckSum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OEP, m_AddressOfEntryPoint);
	DDX_Text(pDX, IDC_EDIT_IB, m_ImageBase);
	DDX_Text(pDX, IDC_EDIT_SOI, m_SizeOfImage);
	DDX_Text(pDX, IDC_EDIT_BOC, m_BaseOfCode);
	DDX_Text(pDX, IDC_EDIT_BOD, m_BaseOfData);
	DDX_Text(pDX, IDC_EDIT_SA, m_SectionAlignment);
	DDX_Text(pDX, IDC_EDIT_FA, m_FileAlignment);
	DDX_Text(pDX, IDC_EDIT_MA, m_Magic);
	DDX_Text(pDX, IDC_EDIT_SY, m_Subsystem);
	DDX_Text(pDX, IDC_EDIT_NOS, m_NumberOfSections);
	DDX_Text(pDX, IDC_EDIT_TDS, m_TimeDateStamp);
	DDX_Text(pDX, IDC_EDIT_SOH, m_SizeOfHeaders);
	DDX_Text(pDX, IDC_EDIT_DC, m_DllCharacteristics);
	DDX_Text(pDX, IDC_EDIT_NORAS, m_NumberOfRvaAndSizes);
	DDX_Text(pDX, IDC_EDIT_SOOH, m_SizeOfOptionalHeader);
	DDX_Text(pDX, IDC_EDIT_CS, m_CheckSum);
}

BEGIN_MESSAGE_MAP(CPEInfo, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON10, &CPEInfo::OnBnClickedButtonRVA)
	ON_BN_CLICKED(IDC_BUTTON_TIME, &CPEInfo::OnBnClickedButtonTime)
	ON_BN_CLICKED(IDC_BUTTON_SECTIONS, &CPEInfo::OnBnClickedButtonSections)
	ON_BN_CLICKED(IDC_BUTTON8, &CPEInfo::OnBnClickedButtonDirectory)
	ON_BN_CLICKED(IDC_BUTTON7, &CPEInfo::OnBnClickedButton7)
END_MESSAGE_MAP()


// CPEInfo ��Ϣ�������

BOOL CPEInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	

	//����ԱȨ��������ҷ�ļ�;
	ChangeWindowMessageFilterEx(this->m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(this->m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEInfo::OnPaint()
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
HCURSOR CPEInfo::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//****************************************************************
// Brief 	: ��ҷ�ļ�����
// Method	: OnDropFiles
// FullName	: CPEInfo::OnDropFiles
// Access	: protected 
// Returns	: void
// Parameter: HDROP hDropInfo
//****************************************************************

void CPEInfo::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��ȡ�ļ�·��
	TCHAR szPatch[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPatch, MAX_PATH);
	m_DeleFileName=szPatch;

	//��ȡ�ļ���Ϣ
	GetFileInfo();

	//ˢ��
	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}

//****************************************************************
// Brief 	: ��ȡ�ļ���Ϣ
// Method	: GetFileInfo
// FullName	: CPEInfo::GetFileInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEInfo::GetFileInfo()
{
	//���ļ�
	m_hFile = CreateFile(
		m_DeleFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwSize = GetFileSize(m_hFile, NULL);
	PBYTE pBuf = new BYTE[dwSize]{};

	//��ȡ
	ReadFile(m_hFile, pBuf, dwSize, &dwSize, NULL);

	//�ж�MZͷ
	m_pDos = (PIMAGE_DOS_HEADER)pBuf;
	if (m_pDos->e_magic!=IMAGE_DOS_SIGNATURE)
	{
		MessageBox(L"������Ч��PE�ļ���\n");
		CloseHandle(m_hFile);
		m_hFile = NULL;
		return;
	}
	//�ж�PE��ʶ
	m_pNTHeader = (PIMAGE_NT_HEADERS)(pBuf + m_pDos->e_lfanew);
	if (m_pNTHeader->Signature!=IMAGE_NT_SIGNATURE)
	{
		MessageBox(L"������Ч��PE�ļ���\n");
		CloseHandle(m_hFile);
		m_hFile = NULL;
		return;
	}

	//��ȡ�ļ�ͷ��Ϣ
	m_pFileHeader = &m_pNTHeader->FileHeader;

	m_NumberOfSections.Format(L"%X", m_pFileHeader->NumberOfSections);
	m_TimeDateStamp.Format(L"%p", m_pFileHeader->TimeDateStamp);
	m_SizeOfOptionalHeader.Format(L"%X", m_pFileHeader->SizeOfOptionalHeader);

	//��չͷ��Ϣ
	m_pOptionalHeader = &m_pNTHeader->OptionalHeader;

	m_AddressOfEntryPoint.Format(L"%p", m_pOptionalHeader->AddressOfEntryPoint);
	m_ImageBase.Format(L"%p", m_pOptionalHeader->ImageBase);
	m_SizeOfImage.Format(L"%X", m_pOptionalHeader->SizeOfImage);
	m_BaseOfCode.Format(L"%p", m_pOptionalHeader->BaseOfCode);
	m_BaseOfData.Format(L"%p", m_pOptionalHeader->BaseOfData);
	m_SectionAlignment.Format(L"%X", m_pOptionalHeader->SectionAlignment);
	m_FileAlignment.Format(L"%X", m_pOptionalHeader->FileAlignment);
	m_Magic.Format(L"%X", m_pOptionalHeader->Magic);
	m_Subsystem.Format(L"%X", m_pOptionalHeader->Subsystem);
	m_SizeOfHeaders.Format(L"%X", m_pOptionalHeader->SizeOfHeaders);
	m_DllCharacteristics.Format(L"%X", m_pOptionalHeader->DllCharacteristics);
	m_NumberOfRvaAndSizes.Format(L"%X", m_pOptionalHeader->NumberOfRvaAndSizes);
	m_CheckSum.Format(L"%X", m_pOptionalHeader->CheckSum);

	
}

//RVA����
void CPEInfo::OnBnClickedButtonRVA()
{
	if (!m_hFile)
	{
		MessageBox(L"��ѡ����Ч���ļ���");
		return;
	}


	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPERva2Fo *RVA = new CPERva2Fo(m_pNTHeader);
	RVA->DoModal();
}

//ʱ��ת��
void CPEInfo::OnBnClickedButtonTime()
{
	if (!m_hFile)
	{
		MessageBox(L"��ѡ����Ч���ļ���");
		return;
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPETimeData * TD = new CPETimeData(m_pFileHeader->TimeDateStamp);
	TD->DoModal();
}

//������Ϣ
void CPEInfo::OnBnClickedButtonSections()
{
	if (!m_hFile)
	{
		MessageBox(L"��ѡ����Ч���ļ���");
		return;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPESectionsInfo * pSI = new CPESectionsInfo(m_pNTHeader);
	pSI->DoModal();
}

//Ŀ¼��Ϣ
void CPEInfo::OnBnClickedButtonDirectory()
{
	if (!m_hFile)
	{
		MessageBox(L"��ѡ����Ч���ļ���");
		return;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEDirectory * pDir = new CPEDirectory(m_pDos,m_pNTHeader);
	pDir->DoModal();
}


void CPEInfo::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T("exe"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("��ִ�г���|*.exe|�����ļ�|*||"));

	int nRet = dlg.DoModal();

	if (nRet == IDOK) {

		m_DeleFileName = dlg.GetPathName();

		//��ȡ�ļ���Ϣ
		GetFileInfo();

		//ˢ��
		UpdateData(FALSE);
	}
}
