// PETimeData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PETimeData.h"



// CPETimeData �Ի���

IMPLEMENT_DYNAMIC(CPETimeData, CDialogEx)

CPETimeData::CPETimeData(DWORD   TimeDateStamp, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TIME, pParent)
	, m_TimeStamp(_T(""))
	, m_TimeData(_T(""))
{
	m_dwTimeDateStamp = TimeDateStamp;
}

CPETimeData::~CPETimeData()
{
}

void CPETimeData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIMEDSTAMP, m_TimeStamp);
	DDX_Text(pDX, IDC_EDIT_TIMEDATA, m_TimeData);
}


BEGIN_MESSAGE_MAP(CPETimeData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TS2TD, &CPETimeData::OnBnClickedButtonTs2TD)
END_MESSAGE_MAP()


// CPETimeData ��Ϣ�������


BOOL CPETimeData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TimeStamp2TimeData(m_dwTimeDateStamp);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ʱ���ת������ʱ��
// Method	: TimeStamp2TimeData
// FullName	: CPETimeData::TimeStamp2TimeData
// Access	: private 
// Returns	: void
// Parameter: DWORD TimeDateStamp
//****************************************************************

void CPETimeData::TimeStamp2TimeData(DWORD TimeDateStamp)
{
	//��ȡʱ��
	time_t t = TimeDateStamp;
	char buf[65] = {};
	tm* FileTime = new tm{};
	
	//ת��ʱ��
	localtime_s(FileTime,&t);
	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", FileTime);

	//��ʾ
	m_TimeData = buf;
	m_TimeStamp.Format(L"%p",TimeDateStamp);
}


//****************************************************************
// Brief 	: ��Ӧʱ������㰴ť
// Method	: OnBnClickedButtonTs2TD
// FullName	: CPETimeData::OnBnClickedButtonTs2TD
// Access	: protected 
// Returns	: void
//****************************************************************

void CPETimeData::OnBnClickedButtonTs2TD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ʱ��
	m_dwTimeDateStamp = 0;
	m_TimeStamp = "";

	//���»�ȡʱ��
	UpdateData(TRUE);

	//����
	m_dwTimeDateStamp = wcstoll(m_TimeStamp, NULL, 16);
	TimeStamp2TimeData(m_dwTimeDateStamp);

	//ˢ��
	UpdateData(FALSE);
}
