// PETimeData.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PETimeData.h"



// CPETimeData 对话框

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


// CPETimeData 消息处理程序


BOOL CPETimeData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	TimeStamp2TimeData(m_dwTimeDateStamp);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//****************************************************************
// Brief 	: 时间戳转换日期时间
// Method	: TimeStamp2TimeData
// FullName	: CPETimeData::TimeStamp2TimeData
// Access	: private 
// Returns	: void
// Parameter: DWORD TimeDateStamp
//****************************************************************

void CPETimeData::TimeStamp2TimeData(DWORD TimeDateStamp)
{
	//获取时间
	time_t t = TimeDateStamp;
	char buf[65] = {};
	tm* FileTime = new tm{};
	
	//转换时间
	localtime_s(FileTime,&t);
	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", FileTime);

	//显示
	m_TimeData = buf;
	m_TimeStamp.Format(L"%p",TimeDateStamp);
}


//****************************************************************
// Brief 	: 响应时间戳计算按钮
// Method	: OnBnClickedButtonTs2TD
// FullName	: CPETimeData::OnBnClickedButtonTs2TD
// Access	: protected 
// Returns	: void
//****************************************************************

void CPETimeData::OnBnClickedButtonTs2TD()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空时间
	m_dwTimeDateStamp = 0;
	m_TimeStamp = "";

	//重新获取时间
	UpdateData(TRUE);

	//计算
	m_dwTimeDateStamp = wcstoll(m_TimeStamp, NULL, 16);
	TimeStamp2TimeData(m_dwTimeDateStamp);

	//刷新
	UpdateData(FALSE);
}
