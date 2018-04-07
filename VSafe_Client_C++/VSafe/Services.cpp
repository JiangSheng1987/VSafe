// Services.cpp : ʵ���ļ�
//


#include "stdafx.h"

#include "VSafe.h"
#include "Services.h"
#include "afxdialogex.h"
#include <Winsvc.h>

// CServices �Ի���

IMPLEMENT_DYNAMIC(CServices, CDialogEx)

CServices::CServices(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SERVICES, pParent)
{
	
}

CServices::~CServices()
{
}

void CServices::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVICE, m_ListServices);
}


BEGIN_MESSAGE_MAP(CServices, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SERVICE, &CServices::OnNMRClickListService)
	ON_CONTROL_RANGE(BN_CLICKED, ID_32784, ID_32787, OnMenuService)			//�Ҽ��˵���Ϣ����;
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SERVICE, &CServices::OnLvnColumnclickListService)
END_MESSAGE_MAP()


// CServices ��Ϣ�������


BOOL CServices::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	m_ListServices.AddColumn(4, L"����", 200, L"����", 400, L"״̬", 100, L"����", 100);
	//ˢ�·���
	UpDataService();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//ˢ�·���
void CServices::UpDataService()
{
	m_ListServices.DeleteAllItems();
	GetServices();
}

//��ȡ������Ϣ
void CServices::GetServices()
{
	//�򿪷�����ƹ�����
	SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	//��һ�ε���,��ȡ�����ڴ��С
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	EnumServicesStatusEx(hSCM,SC_ENUM_PROCESS_INFO,	SERVICE_WIN32,
		SERVICE_STATE_ALL,	NULL,0,	&dwSize,&dwServiceNum,NULL, NULL);
	//���������ڴ�
	LPENUM_SERVICE_STATUS_PROCESS pEnumService =(LPENUM_SERVICE_STATUS_PROCESS)new char[dwSize];

	//�ڶ���ö��
	bool bStatus=false;
	bStatus = EnumServicesStatusEx(hSCM,SC_ENUM_PROCESS_INFO,SERVICE_WIN32,
		SERVICE_STATE_ALL,(PBYTE)pEnumService,dwSize,&dwSize,&dwServiceNum,	NULL, NULL);

	//������Ϣ
	for (DWORD i=0;i<dwServiceNum;i++)
	{
		//������
		m_ServiceName = pEnumService[i].lpServiceName;

		//״̬
		DWORD dwStatus = pEnumService[i].ServiceStatusProcess.dwCurrentState;
		m_ServiceStatu = ServiceStatus[dwStatus];

		//��ϸ��Ϣ
		SC_HANDLE hService = OpenService(hSCM,pEnumService[i].lpServiceName,SERVICE_QUERY_CONFIG);

		//��ȡ��������С
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		//�����ڴ�
		LPQUERY_SERVICE_CONFIG pServiceConfig =	(LPQUERY_SERVICE_CONFIG)new char[dwSize];
		//��ȡ��Ϣ
		QueryServiceConfig(hService, pServiceConfig, dwSize, &dwSize);		

		DWORD dwType = pServiceConfig->dwStartType;
		m_ServiceType = ServerStartType[dwType];

		if (dwType>0)
		{	
			//��ȡ������Ϣ��С
			QueryServiceConfig2(hService,SERVICE_CONFIG_DESCRIPTION, NULL, 0, &dwSize);
			LPSERVICE_DESCRIPTION pServiceDesc = (LPSERVICE_DESCRIPTION)new char[dwSize];
			//��ȡ����
			QueryServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, (LPBYTE)pServiceDesc, dwSize, &dwSize);
			m_ServiceDesc = pServiceDesc->lpDescription;
		}
		else
		{
			//����Ȩ�޻�ʲôԭ�򣬿��ܻ�ȡ����ɱ��������Ϣ
			m_ServiceDesc = L" ";
		}
		
		m_ListServices.AddItem(4, m_ServiceName, m_ServiceDesc, m_ServiceStatu, m_ServiceType);
	}
	
}

//��������
void CServices::StartAndStopService(bool IsStart)
{
	//��ȡѡ����
	int nSel = m_ListServices.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	//��ȡ������
	CString strServiceName = m_ListServices.GetItemText(nSel, 0);


	//�򿪷�����ƹ�����
	SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	
	if (hSCM==NULL)
	{
		MessageBox(L"��ȡ���������Ϣʧ�ܣ�");
		return;
	}

	//�򿪷���
	SC_HANDLE hService = OpenService(hSCM, strServiceName, 
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);

	if (hService==NULL)
	{
		MessageBox(L"�򿪷���ʧ�ܣ�");
		CloseServiceHandle(hSCM);
		return;
	}

	//��ȡ����״̬
	SERVICE_STATUS Status;
	if (QueryServiceStatus(hService,&Status)==FALSE)
	{
		MessageBox(L"��ȡ����״̬ʧ�ܣ�");
		CloseServiceHandle(hSCM);
		CloseServiceHandle(hService);
		return;
	}
	//��������ѡ��
	if (IsStart)
	{

			if (StartService(hService,NULL,NULL)==FALSE)
			{
				MessageBox(L"��������ʧ�ܣ�");
				CloseServiceHandle(hSCM);
				CloseServiceHandle(hService);
				return;
			}
			//�ȴ������������
			while (QueryServiceStatus(hService, &Status) == TRUE)
			{
				Sleep(Status.dwWaitHint);
				if (Status.dwCurrentState==SERVICE_RUNNING)
				{
					MessageBox(L"��������ɹ���");
					CloseServiceHandle(hSCM);
					CloseServiceHandle(hService);
					return;
				}
			}

		

	}
	else
	{

			if (ControlService(hService,SERVICE_CONTROL_STOP,&Status)==FALSE)
			{
				MessageBox(L"ֹͣ����ʧ�ܣ�");
				CloseServiceHandle(hSCM);
				CloseServiceHandle(hService);
				return;
			}
			//�ȴ�����ֹͣ
			while (QueryServiceStatus(hService,&Status)==TRUE)
			{
				Sleep(Status.dwWaitHint);
				if (Status.dwCurrentState== SERVICE_STOPPED)
				{
					MessageBox(L"ֹͣ����ɹ���");
					CloseServiceHandle(hSCM);
					CloseServiceHandle(hService);
					return;
				}
			}
	
	}

}

//�Ҽ��˵�
void CServices::OnNMRClickListService(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡѡ����
	int nSel = m_ListServices.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	//��ȡ������
	CString strServiceStatu = m_ListServices.GetItemText(nSel, 2);

	//��ȡ�����˵�;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU2);
	CMenu* pSub = pMenu->GetSubMenu(5);

	//���Ĳ˵�ѡ��
	//�ж�����״̬
	if (strServiceStatu == L"��������")
	{
		::EnableMenuItem(pSub->m_hMenu,ID_32784, MF_BYCOMMAND  | MF_GRAYED);
	}
	//����ָ��ѡ��
	else if (strServiceStatu==L"��ֹͣ")
	{
		::EnableMenuItem(pSub->m_hMenu, ID_32786, MF_BYCOMMAND |  MF_GRAYED);
	}

	//��ȡ���λ��;
	CPoint point;
	GetCursorPos(&point);

	//����;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}

//��Ӧ�˵�
void CServices::OnMenuService(UINT uID)
{
	switch (uID)
	{
	case ID_32784:	
		StartAndStopService(true);
		break;
	case ID_32786:		
		StartAndStopService(false);
		break;
	default:
		break;
	}
	UpDataService();
}

//�����ͷ����
void CServices::OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ�����;
	int Sort_Colum = pNMLV->iSubItem;		
	m_ListServices.SortItemsPlus(Sort_Colum, false);

	*pResult = 0;
}
