// PEDirectory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEDirectory.h"
#include "PEExport.h"
#include "PEImport.h"
#include "PEBaseRlock.h"
#include "PETLS.h"
#include "PEResourceInfo.h"
#include "PEDelay.h"


// CPEDirectory �Ի���

IMPLEMENT_DYNAMIC(CPEDirectory, CDialogEx)

CPEDirectory::CPEDirectory(PIMAGE_DOS_HEADER pDos,PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DIRECTORY, pParent)
	, m_Rva_In(_T(""))
	, m_Rva_Out(_T(""))
	, m_Rva_Resouce(_T(""))
	, m_Rva_Except(_T(""))
	, m_Rva_Security(_T(""))
	, m_Rva_BaseReloc(_T(""))
	, m_Rva_Debug(_T(""))
	, m_Rva_Architecture(_T(""))
	, m_Rva_GlobalPTR(_T(""))
	, m_Rva_TLS(_T(""))
	, m_Rva_load(_T(""))
	, m_Rva_Bound(_T(""))
	, m_Rva_IAT(_T(""))
	, m_Rva_Delay(_T(""))
	, m_Rva_COM(_T(""))
	, m_Rva_OT(_T(""))
	, m_Size_In(_T(""))
	, m_Size_Out(_T(""))
	, m_Size_Resouce(_T(""))
	, m_Size_Except(_T(""))
	, m_Size_Security(_T(""))
	, m_Size_BaseReloc(_T(""))
	, m_Size_Debug(_T(""))
	, m_Size_Architecture(_T(""))
	, m_Size_GlobalPTR(_T(""))
	, m_Size_TLS(_T(""))
	, m_Size_Load(_T(""))
	, m_Size_Bound(_T(""))
	, m_Size_IAT(_T(""))
	, m_Size_Delay(_T(""))
	, m_Size_COM(_T(""))
	, m_Size_OT(_T(""))
{
	m_pDos = pDos;
	m_pNTHeader= pNTHeader;
	m_pDataDir=pNTHeader->OptionalHeader.DataDirectory;
}

CPEDirectory::~CPEDirectory()
{
}

void CPEDirectory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RVA_OUT, m_ArrRva[0]);
	DDX_Text(pDX, IDC_EDIT_RVA_IN, m_ArrRva[1]);
	DDX_Text(pDX, IDC_EDIT_RVA_RESOUCE, m_ArrRva[2]);
	DDX_Text(pDX, IDC_EDIT_RVA_EXCEPTION, m_ArrRva[3]);
	DDX_Text(pDX, IDC_EDIT_RVA_SECURITY, m_ArrRva[4]);
	DDX_Text(pDX, IDC_EDIT_RVA_BASERELOC, m_ArrRva[5]);
	DDX_Text(pDX, IDC_EDIT_RVA_DEBUG, m_ArrRva[6]);
	DDX_Text(pDX, IDC_EDIT_RVA_ARCHITECTURE, m_ArrRva[7]);
	DDX_Text(pDX, IDC_EDIT_RVA_GLOBALPTR, m_ArrRva[8]);
	DDX_Text(pDX, IDC_EDIT_RVA_TLS, m_ArrRva[9]);
	DDX_Text(pDX, IDC_EDIT_RVA_CONFIG, m_ArrRva[10]);
	DDX_Text(pDX, IDC_EDIT_RVA_IMPORT11, m_ArrRva[11]);
	DDX_Text(pDX, IDC_EDIT_RVA_IAT, m_ArrRva[12]);
	DDX_Text(pDX, IDC_EDIT_RVA_DELAY, m_ArrRva[13]);
	DDX_Text(pDX, IDC_EDIT_RVA_COM, m_ArrRva[14]);
	DDX_Text(pDX, IDC_EDIT_RVA_COM2, m_ArrRva[15]);

	DDX_Text(pDX, IDC_EDIT_SIZE_OUT2, m_ArrSize[0]);
	DDX_Text(pDX, IDC_EDIT_SIZE_IN2, m_ArrSize[1]);
	DDX_Text(pDX, IDC_EDIT_SIZE_RESOUCE2, m_ArrSize[2]);
	DDX_Text(pDX, IDC_EDIT_SIZE_EXCEPTION2, m_ArrSize[3]);
	DDX_Text(pDX, IDC_EDIT_SIZE_SECURITY2, m_ArrSize[4]);
	DDX_Text(pDX, IDC_EDIT_SIZE_BASERELOC2, m_ArrSize[5]);
	DDX_Text(pDX, IDC_EDIT_SIZE_DEBUG2, m_ArrSize[6]);
	DDX_Text(pDX, IDC_EDIT_SIZE_ARCHITECTURE2, m_ArrSize[7]);
	DDX_Text(pDX, IDC_EDIT_SIZE_GLOBALPTR2, m_ArrSize[8]);
	DDX_Text(pDX, IDC_EDIT_SIZE_TLS2, m_ArrSize[9]);
	DDX_Text(pDX, IDC_EDIT_SIZE_CONFIG2, m_ArrSize[10]);
	DDX_Text(pDX, IDC_EDIT_SIZE_IMPORT12, m_ArrSize[11]);
	DDX_Text(pDX, IDC_EDIT_SIZE_IAT2, m_ArrSize[12]);
	DDX_Text(pDX, IDC_EDIT_SIZE_DELAY2, m_ArrSize[13]);
	DDX_Text(pDX, IDC_EDIT_SIZE_COM3, m_ArrSize[14]);
	DDX_Text(pDX, IDC_EDIT_SIZE_COM4, m_ArrSize[15]);
}


BEGIN_MESSAGE_MAP(CPEDirectory, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CPEDirectory::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CPEDirectory::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_BASERELOC, &CPEDirectory::OnBnClickedButtonBasereloc)
	ON_BN_CLICKED(IDC_BUTTON_TLS, &CPEDirectory::OnBnClickedButtonTls)
	ON_BN_CLICKED(IDC_BUTTON_RESOUCE, &CPEDirectory::OnBnClickedButtonResouce)
	ON_BN_CLICKED(IDC_BUTTON_DELAY, &CPEDirectory::OnBnClickedButtonDelay)
END_MESSAGE_MAP()


// CPEDirectory ��Ϣ�������


BOOL CPEDirectory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	GetDirectoryInfo();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ���Ŀ¼��Ϣ
// Method	: GetDirectoryInfo
// FullName	: CPEDirectory::GetDirectoryInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEDirectory::GetDirectoryInfo()
{	
	//����RVA	����Size
	//�������������ֱ��д��16
	for (int i=0;i<16;i++)
	{
		m_ArrRva[i].Format(L"%p", m_pDataDir[i].VirtualAddress);
		m_ArrSize[i].Format(L"%X", m_pDataDir[i].Size);
	}
}

//������
void CPEDirectory::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEExport *pExp = new CPEExport(m_pDos, m_pNTHeader);
	pExp->DoModal();
}

//�����
void CPEDirectory::OnBnClickedButtonImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEImport * pImport = new CPEImport(m_pDos, m_pNTHeader);
	pImport->DoModal();
}

//�ض�λ��
void CPEDirectory::OnBnClickedButtonBasereloc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEBaseRlock *pRlock = new CPEBaseRlock(m_pDos, m_pNTHeader);
	pRlock->DoModal();
}

//TLS��
void CPEDirectory::OnBnClickedButtonTls()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPETLS* pTLS = new CPETLS(m_pDos, m_pNTHeader);
	pTLS->DoModal();
}

//��Դ��
void CPEDirectory::OnBnClickedButtonResouce()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEResourceInfo *pResInfo = new CPEResourceInfo(m_pDos, m_pNTHeader);
	pResInfo->DoModal();
}

//�ӳٵ����
void CPEDirectory::OnBnClickedButtonDelay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEDelay *pDelayInfo = new CPEDelay(m_pDos, m_pNTHeader);
	pDelayInfo->DoModal();
}
