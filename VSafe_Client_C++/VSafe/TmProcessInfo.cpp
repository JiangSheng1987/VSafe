#include "stdafx.h"

#include "TmProcessInfo.h"
#include <TlHelp32.h>
#include <tchar.h>

// CTmProcessInfo �Ի���

IMPLEMENT_DYNAMIC(CTmProcessInfo, CDialogEx)

CTmProcessInfo::CTmProcessInfo(CWnd* pParent, int nMID, int nPID)
	: CDialogEx(IDD_DIALOG_PROCESS_INFO, pParent)
{
	this->m_nMenuID = nMID;
	this->m_nPID = nPID;
	m_bFlag = false;
}


CTmProcessInfo::~CTmProcessInfo()
{
}

void CTmProcessInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POPLIST1, m_PopList);
}


//****************************************************************
// Brief 	: ��ʾģ��;
// Method	: ShowModule
// FullName	: CTmProcessInfo::ShowModule
// Access	: public 
// Returns	: void
// Parameter: int nPid
//****************************************************************

void CTmProcessInfo::ShowModule(int nPid)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, nPid);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"�򿪽�����Ϣʧ�ܣ�");
		return;
	}
	MODULEENTRY32 me = { sizeof(MODULEENTRY32) };
	if (!Module32First(hSnapShot, &me))
	{
		MessageBox(L"��ȡģ����Ϣʧ�ܣ�");
		return;
	}
	m_PopList.AddColumn(3, L"ģ������", 100, L"ģ���С", 100, L"ģ��·��", 290);
	do
	{
		TCHAR* SizeBuf=new TCHAR[11];
		_stprintf_s(SizeBuf, 10, L"%d",me.modBaseSize);
		m_PopList.AddItem(3, me.szModule, SizeBuf,me.szExePath);
	} while (Module32Next(hSnapShot, &me));

	return;
}

//****************************************************************
// Brief 	: �����߳�;
// Method	: ShowThread
// FullName	: CTmProcessInfo::ShowThread
// Access	: public 
// Returns	: void
// Parameter: int nPid
//****************************************************************

void CTmProcessInfo::ShowThread(int nPid)
{
	//��������;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);

	//���������Ϣ�ṹ��;
	THREADENTRY32 ThreadInfo = { sizeof(THREADENTRY32) };
	
	//��������;
	if (Thread32First(hSnapShot,&ThreadInfo))
	{
		m_PopList.AddColumn(3, L"�߳�ID", 160, L"���ȼ�", 160, L"״̬", 170);
		do
		{
			//��ʾ�����������߳�;
			if (ThreadInfo.th32OwnerProcessID==m_nPID)
			{
				CString PID, Levele, State;
				PID.Format(L"%d", ThreadInfo.th32ThreadID);
				Levele.Format(L"%d", ThreadInfo.tpBasePri);

				//��ȡ�߳̾��;
				DWORD dwState = 0;
				HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION |
					THREAD_QUERY_LIMITED_INFORMATION, FALSE, ThreadInfo.th32ThreadID);

					//�ж��߳�״̬;
				GetExitCodeThread(hThread, &dwState);
				if (dwState ==STILL_ACTIVE)
				{
					State = L"������";
				}
				else
				{
					State = L"����";
				}
				CloseHandle(hThread);
				m_PopList.AddItem(3, PID, Levele, State);
			}

		} while (Thread32Next(hSnapShot, &ThreadInfo));
	}
	else
	{
		MessageBox(L"��ȡ�߳���Ϣʧ�ܣ�");
	}
}


//****************************************************************
// Brief 	: ������;
// Method	: ShowHeap
// FullName	: CTmProcessInfo::ShowHeap
// Access	: public 
// Returns	: void
// Parameter: int nPid
//****************************************************************

void CTmProcessInfo::ShowHeap(int nPid)
{
	//��ȡ����;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, nPid);
	if (!hSnapShot)
	{
		MessageBox(L"��ȡ��Ϣʧ��");
		return;
	}

	//������Ϣ;
	HEAPLIST32 HeapListInfo = { 0 };
	HeapListInfo.dwSize = sizeof(HEAPLIST32);

	//��ȡ��һ��������Ϣ;
	if (Heap32ListFirst(hSnapShot,&HeapListInfo))
	{
		m_PopList.AddColumn(4, L"��ID", 120, L"��С", 120, L"��ʼ��ַ", 120, L"״̬", 130);
		do 
		{
			//�ѿ���Ϣ;
			HEAPENTRY32 HeapInfo = { 0 };
			HeapInfo.dwSize = sizeof(HEAPENTRY32);

			//��ȡ�ѿ���Ϣ;
			if (Heap32First(&HeapInfo, nPid, HeapListInfo.th32HeapID))
			{
				do 
				{
					CString HID, BlockSize, Address, Flags;
					HID.Format(L"%d", HeapInfo.th32HeapID);
					BlockSize.Format(L"%d", HeapInfo.dwBlockSize);
					Address.Format(L"0x%x", HeapInfo.dwAddress);
					if (HeapInfo.dwFlags==LF32_FIXED)
					{
						Flags = L"��ʹ��";
					}
					else if (HeapInfo.dwFlags == LF32_MOVEABLE)
					{
						Flags = L"���ƶ�";
					}
					else
					{
						Flags = L"����";
					}
					m_PopList.AddItem(4, HID, BlockSize, Address, Flags);
				} while (Heap32Next(&HeapInfo));
			}		
		} while (Heap32ListNext(hSnapShot,&HeapListInfo));
	}
	else
	{
		MessageBox(L"��ȡ��Ϣʧ��");
	}
}


BEGIN_MESSAGE_MAP(CTmProcessInfo, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_POPLIST1, &CTmProcessInfo::OnRclickPoplist1)
	ON_CONTROL_RANGE(BN_CLICKED, ID_32791, ID_32793, &CTmProcessInfo::OnMenuThread)	//����˵���;
END_MESSAGE_MAP()


// CTmProcessInfo ��Ϣ�������


BOOL CTmProcessInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	switch (m_nMenuID)
	{
	case ID_32781:
		m_bFlag = true;
		ShowThread(m_nPID);
		break;
	case ID_32782:		
		ShowModule(m_nPID);
		break;
	case ID_32783:
		ShowHeap(m_nPID);
		break;
	default:
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


//****************************************************************
// Brief 	: �߳��б����Ҽ��˵�;
// Method	: OnRclickPoplist1
// FullName	: CTmProcessInfo::OnRclickPoplist1
// Access	: public 
// Returns	: void
// Parameter: NMHDR * pNMHDR
// Parameter: LRESULT * pResult
//****************************************************************

void CTmProcessInfo::OnRclickPoplist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���߳��б����;
	if (!m_bFlag)
	{
		return;
	}

	//�߳��б�����ʾ�˵�;

	//��ȡ�����˵�;
	CMenu* pMenuThread = new CMenu;
	pMenuThread->LoadMenuW(IDR_MENU2);

	CMenu* pSubThread = pMenuThread->GetSubMenu(1);

	//��ȡ���λ��;
	CPoint point;
	GetCursorPos(&point);

	//����;
	pSubThread->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}

//****************************************************************
// Brief 	: ��Ӧ�Ҽ��˵�;
// Method	: OnMenuThread
// FullName	: CTmProcessInfo::OnMenuThread
// Access	: public 
// Returns	: void
// Parameter: UINT id
//****************************************************************

void CTmProcessInfo::OnMenuThread(UINT id)
{
	int nSel = m_PopList.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	int PID = _wtoi(m_PopList.GetItemText(nSel, 0));

	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, PID);
	switch (id)
	{
	case  ID_32791:
		if (SuspendThread(hThread)== -1)
		{
			MessageBox(L"�����߳�ʧ�ܣ�");
		}
		else
		{
			MessageBox(L"�����̳߳ɹ���");
		}
		break;
	case ID_32792:
		if (ResumeThread(hThread)== -1)
		{
			MessageBox(L"�ָ��߳�ʧ�ܣ�");
		}
		else
		{
			MessageBox(L"�ָ��̳߳ɹ���");
		}
		break;
	case ID_32793:
		if (!TerminateThread(hThread,0))
		{
			MessageBox(L"�����߳�ʧ�ܣ�");
		}
		else
		{
			MessageBox(L"�����̳߳ɹ���");
		}
		break;
	default:
		break;
	}


}
