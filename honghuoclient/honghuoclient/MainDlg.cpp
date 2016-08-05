// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "huobi.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "huobiDlg.h"
#include "Deal.h"
#include <afxinet.h>

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogBar)

CMainDlg::CMainDlg()
{
	m_pBmp = NULL ;
	m_vlinkCtrl1 = NULL;
	m_vlinkCtrl2 = NULL;
	m_vlinkCtrl3 = NULL;
	m_vlinkCtrl4 = NULL;
	m_vlinkCtrlQQ = NULL;
	m_vlinkCtrlBlock = NULL;
}

CMainDlg::~CMainDlg()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}

	if(NULL != m_vlinkCtrl1)
	{
		delete m_vlinkCtrl1;
	}

	if(NULL != m_vlinkCtrl2)
	{
		delete m_vlinkCtrl2;
	}

	if(NULL != m_vlinkCtrl3)
	{
		delete m_vlinkCtrl3;
	}

	if(NULL != m_vlinkCtrl4)
	{
	delete m_vlinkCtrl4;
	}

	if(NULL != m_vlinkCtrlQQ)
	{
		delete m_vlinkCtrlQQ;
	}

	if(NULL != m_vlinkCtrlBlock)
	{
		delete m_vlinkCtrlBlock;
	}
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ST_BALANCE , m_strBalance);
	DDX_Control(pDX, IDC_ST_CONFIRMING , m_strConfirming);
	DDX_Control(pDX, IDC_ST_TRANSACTION_NUMBER , m_strTransactionNumber);

	DDX_Control(pDX, IDC_ST_SRCADDR1 , m_strSrcAddr1);
	DDX_Control(pDX, IDC_ST_DESADDR1 , m_strDesAddr1);
	DDX_Control(pDX, IDC_ST_AMOUNT1 , m_strAmount1);

	DDX_Control(pDX, IDC_ST_SRCADDR2 , m_strSrcAddr2);
	DDX_Control(pDX, IDC_ST_DESADDR2 , m_strDesAddr2);
	DDX_Control(pDX, IDC_ST_AMOUNT2 , m_strAmount2);

	
	DDX_Control(pDX, IDC_ST_SRCADDR3, m_strSrcAddr3);
	DDX_Control(pDX, IDC_ST_DESADDR3, m_strDesAddr3);
	DDX_Control(pDX, IDC_ST_AMOUNT3, m_strAmount3);


	DDX_Control(pDX, IDC_ST_SRCADDR4, m_strSrcAddr4);
	DDX_Control(pDX, IDC_ST_DESADDR4, m_strDesAddr4);
	DDX_Control(pDX, IDC_ST_AMOUNT4, m_strAmount4);

	DDX_Control(pDX, IDC_ST_SRCADDR5, m_strSrcAddr5);
	DDX_Control(pDX, IDC_ST_DESADDR5, m_strDesAddr5);
	DDX_Control(pDX, IDC_ST_AMOUNT5, m_strAmount5);

	DDX_Control(pDX, IDC_ST_SRCADDR6, m_strSrcAddr6);
	DDX_Control(pDX, IDC_ST_DESADDR6, m_strDesAddr6);
	DDX_Control(pDX, IDC_ST_AMOUNT6, m_strAmount6);

	DDX_Control(pDX, IDC_BTN_TXDETAIL, m_rBtnTxdetail);

}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogBar)
	ON_BN_CLICKED(IDC_BTN_TXDETAIL, &CMainDlg::OnBnClickedTxDetail)
	ON_MESSAGE(MSG_USER_MAIN_UI , &CMainDlg::OnShowListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMainDlg 消息处理程序
void CMainDlg::SetBkBmpNid( UINT nBitmapIn ) 
{
	if( NULL != m_pBmp ) {
		::DeleteObject( m_pBmp ) ;
		m_pBmp = NULL ;
	}
	m_pBmp	= NULL ;
	HINSTANCE	hInstResource = NULL;	
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmapIn), RT_BITMAP);
	if( NULL != hInstResource ) {
		m_pBmp = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapIn), IMAGE_BITMAP, 0, 0, 0);
	}
}

void CMainDlg::ClearCtrlText()
{
	GetDlgItem(IDC_ST_BALANCE)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_TRANSACTION_NUMBER)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR1)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR1)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT1)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR2)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR2)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT2)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR3)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR3)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT3)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR4)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR4)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT4)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR5)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR5)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT5)->SetWindowText(_T(""));

	GetDlgItem(IDC_ST_SRCADDR6)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_DESADDR6)->SetWindowText(_T(""));
	GetDlgItem(IDC_ST_AMOUNT6)->SetWindowText(_T(""));
}

void CMainDlg::InitializeLinkCtrl()
{
	m_vlinkCtrl1->SetWindowText(_T(""));
	m_vlinkCtrl1->EnableWindow(FALSE);
	m_vlinkCtrl2->SetWindowText(_T(""));
	m_vlinkCtrl2->EnableWindow(FALSE);
	m_vlinkCtrl3->SetWindowText(_T(""));
	m_vlinkCtrl3->EnableWindow(FALSE);
	m_vlinkCtrl4->SetWindowText(_T(""));
	m_vlinkCtrl4->EnableWindow(FALSE);
	/*
	m_vlinkCtrlQQ->SetWindowText("官方客服QQ");
	m_vlinkCtrlQQ->SetURL("http://wpa.qq.com/msgrd?v=3&uin=1578215488&site=qq&menu=yes");

	m_vlinkCtrlBlock->SetWindowText("Block chain");
	m_vlinkCtrlBlock->SetURL("http://block.dacrs.com/index");
	*/

	int i = 1;
	map<CString,CString>::iterator it;
	for(it=m_mapUrl.begin();it!=m_mapUrl.end();++it)
	{
		if (i == 1)
		{
			m_vlinkCtrl1->SetWindowText(it->first);
			m_vlinkCtrl1->SetURL(it->second);
			m_vlinkCtrl1->EnableWindow(TRUE);
		}
		if (i == 2)
		{
			m_vlinkCtrl2->SetWindowText(it->first);
			m_vlinkCtrl2->SetURL(it->second);
			m_vlinkCtrl2->EnableWindow(TRUE);
		}
		if (i == 3)
		{
			m_vlinkCtrl3->SetWindowText(it->first);
			m_vlinkCtrl3->SetURL(it->second);
			m_vlinkCtrl3->EnableWindow(TRUE);
		}
		if (i == 4)
		{
			m_vlinkCtrl4->SetWindowText(it->first);
			m_vlinkCtrl4->SetURL(it->second);
			m_vlinkCtrl4->EnableWindow(TRUE);
			break;
		}
		i++;
	}
}


void CMainDlg::OnBnClickedTxDetail()
{
	// TODO: 在此添加控件通知处理程序代码
	ChuobiDlg* pDlg = (ChuobiDlg*)GetParent();
	if ( NULL != pDlg ) {
		pDlg->ShowDialog(CDeal::IDD) ;
		pDlg->ShowStateTip(CDeal::IDD);
	}
}


LRESULT CMainDlg::OnShowListCtrl(WPARAM wParam, LPARAM lParam)
{
	
		//更新数据
		if (wParam == WM_UPWALLET)
		{
			//隐藏"钱包正在同步"static
//			GetDlgItem(IDC_STATIC_WALLET)->ShowWindow(SW_HIDE);
		}else{
			SetCtrlText();
		}
		return 0 ;
}

void CMainDlg::SetCtrlText() 
{
	ClearCtrlText();
	CPostMsg postmsg;
	if (!theApp.m_msgUIMainDlgQueue.pop(postmsg))
	{
		LogPrint("INFO","m_UiManDlgQueue Emptry\r\n");
		return ;
	}

	uistruct::MINDLG_T maindlg; 
	string strTemp = postmsg.GetData();
	maindlg.JsonToStruct(strTemp.c_str());


	string strCommand,strShowData;

	string strMoney = "";
	strMoney = strprintf("%s",maindlg.money.c_str());//)= _T(maindlg.money.c_str());
	strMoney = CSoyPayHelp::getInstance()->DisPlayMoney(strMoney);
	GetDlgItem(IDC_ST_BALANCE)->SetWindowText(strMoney.c_str());
	//strMoney = _T(maindlg.unconfirmmoney.c_str());
	strMoney = strprintf("%s",maindlg.unconfirmmoney.c_str());
	strMoney = CSoyPayHelp::getInstance()->DisPlayMoney(strMoney);
	GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(strMoney.c_str());

	m_strTransactionNumber.SetWindowText(maindlg.itemcount.c_str()) ;

	string strDes = "";
	string addr1 = maindlg.addr1;
	uistruct::REVTRANSACTION_t temp;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);

		strCommand =strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR1)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR1)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT1)->SetWindowText(strCommand.c_str()) ;
	}

	addr1 = maindlg.addr2;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);

		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR2)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR2)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT2)->SetWindowText(strCommand.c_str()) ;
	}

	addr1 = maindlg.addr3;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);

		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR3)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR3)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT3)->SetWindowText(strCommand.c_str()) ;
		
	}
	addr1 = maindlg.addr4;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);
		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes =strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR4)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR4)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT4)->SetWindowText(strCommand.c_str()) ;
	}
	addr1 = maindlg.addr5;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);
		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR5)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR5)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT5)->SetWindowText(strCommand.c_str()) ;
	}

	addr1 = maindlg.addr6;
	if (addr1 != "")
	{
		temp.JsonToStruct(addr1);
		strCommand = strprintf("%.4f",temp.money*COIN);
		strShowData = strprintf("%s",temp.addr.c_str());
		strDes = strprintf("%s",temp.desaddr.c_str());

		GetDlgItem(IDC_ST_DESADDR6)->SetWindowText(strDes.c_str()) ;
		GetDlgItem(IDC_ST_SRCADDR6)->SetWindowText(strShowData.c_str()) ;
		GetDlgItem(IDC_ST_AMOUNT6)->SetWindowText(strCommand.c_str()) ;
	}
	Invalidate();
}


bool CMainDlg::GetUrlServer()
{
	m_mapUrl.clear();
	CString url(_T("http://120.76.148.154/UpData/forumupdata.json"));    
	CInternetSession session;


	std::string strHtml;
	try
	{
		CHttpFile* pfile = (CHttpFile*)session.OpenURL(url,1,INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD,NULL,0);

		DWORD dwStatusCode;    
		pfile->QueryInfoStatusCode(dwStatusCode);    
		if(dwStatusCode == HTTP_STATUS_OK)    
		{    
			char strBuff[1025] = {0};
			while ((pfile->Read((void*)strBuff, 1024)) > 0) 
			{ 
				strHtml += strBuff; 
			} 
		}
		else
		{
			return false;
		}

		pfile->Close();    
		delete pfile;    
		session.Close();
	}
	catch (CException* e)
	{
		e;//消除警告
		return false;
	}

	if (strHtml.empty())
	{
		CStdioFile myFile;
		CString strLine; 
		string strpath = theApp.m_strInsPath;
		strpath +="\\honghuoUpdate.json";
		if(myFile.Open((LPCTSTR)(LPSTR)strpath.c_str(), CFile::modeRead))
		{
			while(myFile.ReadString(strLine))
			{
				strHtml +=strprintf("%s",strLine);
			}
			//读取
			myFile.Close();
		}else{
			return false;
		}
	}else{
		//创建
		CStdioFile  File;
		string strpath = theApp.m_strInsPath;
		strpath +="\\honghuoUpdate.json";
		File.Open((LPCTSTR)(LPSTR)strpath.c_str(),CFile::modeWrite | CFile::modeCreate);  
		File.WriteString(strHtml.c_str());
		File.Close();
	}


	Json::Reader reader;  
	Json::Value root; 

	if (reader.parse(strHtml, root))
	{
		if (!root.isObject())
		{
			return false;
		}
		Json::Value rootcn = root["Chinese"];
		if (rootcn.isNull()&& !rootcn.isArray())
		{
			return false;
		}
		int index = rootcn.size();
		for (int i = 0;i <index;i++)
		{
			Json::Value  msgroot = rootcn[i];
			Json::Value value = msgroot["msn"];
			if (value.isNull())
			{
				return false;
			}
			CString key = msgroot["msn"].asCString();
			value = msgroot["url"];
			if (value.isNull())
			{
				return false;
			}
			CString valuetemp = msgroot["url"].asCString();
			m_mapUrl[key] = valuetemp;
		}
		return true;
	}
	return false;
}


BOOL CMainDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect   rect; 
	GetClientRect(&rect); 

	if(m_pBmp   !=   NULL) { 
		BITMAP   bm; 
		CDC   dcMem; 
		::GetObject(m_pBmp,sizeof(BITMAP),   (LPVOID)&bm); 
		dcMem.CreateCompatibleDC(NULL); 
		HBITMAP     pOldBitmap   =(HBITMAP   )   dcMem.SelectObject(m_pBmp); 
		pDC-> StretchBlt(rect.left,rect.top-1,rect.Width(),rect.Height(),   &dcMem,   0,   0,bm.bmWidth-1,bm.bmHeight-1,   SRCCOPY); 

		dcMem.SelectObject(pOldBitmap);
		dcMem.DeleteDC();
	} else  
		CWnd::OnEraseBkgnd(pDC); 

	return 1;
}

void CMainDlg::OnInitialCtrlText() 
{
	ClearCtrlText();
	string strCommand,strShowData;
	strCommand  = "0";

	double dmoney =  theApp.m_SqliteDeal.GetTableItemSum(_T("t_wallet_address") ,_T("money"), _T(" 1=1 "));

	if (-1 == dmoney)
	{
		m_strBalance.SetWindowText(_T("0.0")) ;
	}else{
		string strMoney;
		strMoney = strprintf("%.3lf", dmoney);
		strMoney = CSoyPayHelp::getInstance()->DisPlayMoney(strMoney);
		m_strBalance.SetWindowText(strMoney.c_str()) ;
	}

	string strCond;
	strCond=" confirm_height = 0 ";

	dmoney =  theApp.m_SqliteDeal.GetTableItemSum("t_transaction" , _T("money") , strCond) ;


	if (dmoney<0)
	{
		GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(_T("0.0")) ;
	}else{
		string strMoney;
		strMoney = strprintf("%.3lf", dmoney);
		GetDlgItem(IDC_ST_CONFIRMING)->SetWindowText(strMoney.c_str()) ;
	}



	int nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction"), _T(" 1=1 ")) ;


	strCommand = strprintf("%d",nItem);
	m_strTransactionNumber.SetWindowText(strCommand.c_str()) ;

	uistruct::TRANSRECORDLIST pTransaction;
	string strSource;
	strCond=" tx_type='COMMON_TX' order by confirmed_time desc limit 6";
	theApp.m_SqliteDeal.GetTransactionList(strCond,&pTransaction);


	int i = 1;
	strCommand=strprintf("IDC_TX%d",nItem);


	int item = IDC_ST_SRCADDR1;
	int item1 = IDC_ST_AMOUNT1;
	int desitem = IDC_ST_DESADDR1;

	string desStr ="";
	if (pTransaction.size() != 0  ) {
		int nSubIdx = 0 , i = 0 ;
		string strShowaddr ;
		std::vector<uistruct::REVTRANSACTION_t>::const_iterator const_it;
		for (const_it = pTransaction.begin() ; const_it != pTransaction.end()&&i<6 ; const_it++ ) {

			strSource = strprintf("%.4f",const_it->money);
			strShowaddr= strprintf("%s",const_it->addr.c_str());
			desStr = strprintf("%s",const_it->desaddr.c_str());
			/*
			if(item <=IDC_ST_SRCADDR6)
				GetDlgItem(item)->SetWindowText(strShowaddr.c_str()) ;
			if(item1 <=IDC_ST_AMOUNT6)
				GetDlgItem(item1)->SetWindowText(strSource.c_str()) ;

			if (desitem <=IDC_ST_DESADDR6)
			{
				GetDlgItem(desitem)->SetWindowText(desStr.c_str());
			}
			item++;
			item1++;
			desitem++;
			*/
			if(item <=IDC_ST_SRCADDR6)
			{
				GetDlgItem(item)->SetWindowText(strShowaddr.c_str()) ;
				GetDlgItem(item + 2)->SetWindowText(strSource.c_str()) ;
				GetDlgItem(item + 1)->SetWindowText(desStr.c_str());
			}
			item += 3;
		}
	}
}


int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetBkBmpNid( IDB_BITMAP_MAIN);		

	m_strBalance.SetFont(90, _T("Arial"));				//设置显示字体和大小
	m_strConfirming.SetFont(90, _T("Arial"));	   
	m_strTransactionNumber.SetFont(90, _T("Arial"));	
	if (m_vlinkCtrl1 == NULL)
	{
		m_vlinkCtrl1 = new CMFCLinkCtrl;
		m_vlinkCtrl1->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK1);
	}

	if (m_vlinkCtrl2 == NULL)
	{
		m_vlinkCtrl2 = new CMFCLinkCtrl;
		m_vlinkCtrl2->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK2);
	}

	if (m_vlinkCtrl3 == NULL)
	{
		m_vlinkCtrl3 = new CMFCLinkCtrl;
		m_vlinkCtrl3->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 80, 50), 
			this, 
			IDC_MFCLINK3);
	}

	if (m_vlinkCtrl4 == NULL)
	{
	m_vlinkCtrl4 = new CMFCLinkCtrl;
	m_vlinkCtrl4->Create(_T(""), 
	WS_VISIBLE, 
	CRect(5, 5, 80, 50), 
	this, 
	IDC_MFCLINK4);
	}
	/*
	if (m_vlinkCtrlQQ == NULL)
	{
		m_vlinkCtrlQQ = new CMFCLinkCtrl;
		m_vlinkCtrlQQ->Create(_T(""), 
			WS_CHILD, 
			CRect(5, 5, 30, 50), 
			this, 
			IDC_MFCLINK_QQ);
	}

	if (m_vlinkCtrlBlock == NULL)
	{
		m_vlinkCtrlBlock = new CMFCLinkCtrl;
		m_vlinkCtrlBlock->Create(_T(""), 
			WS_VISIBLE, 
			CRect(5, 5, 30, 50), 
			this, 
			IDC_MFCLINK_BLOCK);
	}
	*/
	return 0;
}


BOOL CMainDlg::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL bRet = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if (bRet) {
		m_rBtnTxdetail.LoadBitmaps(IDB_BITMAP_ALLTRADE, IDB_BITMAP_ALLTRADE, IDB_BITMAP_ALLTRADE, IDB_BITMAP_ALLTRADE);
		UpdateData(FALSE);
		OnInitialCtrlText();
		GetUrlServer();
		InitializeLinkCtrl();

		m_strBalance.SetFont(120, _T("黑体"));
		m_strConfirming.SetFont(120, _T("黑体"));
		m_strTransactionNumber.SetFont(120, _T("黑体"));
		m_strBalance.SetTextColor(RGB(255, 0, 0));
		m_strConfirming.SetTextColor(RGB(255, 0, 0));
		m_strTransactionNumber.SetTextColor(RGB(255, 0, 0));

		m_strAmount1.SetFont(120, _T("Calibri"));
		m_strAmount2.SetFont(120, _T("Calibri"));
		m_strAmount3.SetFont(120, _T("Calibri"));
		m_strAmount4.SetFont(120, _T("Calibri"));
		m_strAmount5.SetFont(120, _T("Calibri"));
		m_strAmount6.SetFont(120, _T("Calibri"));

		m_strDesAddr1.SetFont(110, _T("Calibri"));
		m_strDesAddr2.SetFont(110, _T("Calibri"));
		m_strDesAddr3.SetFont(110, _T("Calibri"));
		m_strDesAddr4.SetFont(110, _T("Calibri"));
		m_strDesAddr5.SetFont(110, _T("Calibri"));
		m_strDesAddr6.SetFont(110, _T("Calibri"));

		m_strSrcAddr1.SetFont(110, _T("Calibri"));
		m_strSrcAddr2.SetFont(110, _T("Calibri"));
		m_strSrcAddr3.SetFont(110, _T("Calibri"));
		m_strSrcAddr4.SetFont(110, _T("Calibri")); 
		m_strSrcAddr5.SetFont(110, _T("Calibri")); 
		m_strSrcAddr6.SetFont(110, _T("Calibri")); 

		//加载指定位图资源 Bmp图片ID
		//HBITMAP hBitmap; 
		//hBitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_WALLET_SYNC)); 
		//m_sysWallet.SetBitmap(hBitmap);

		theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_MAIN_UI );
	}
	return bRet;
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {
		const int div = 100 ;

		CRect rc ;
		GetClientRect( rc ) ;
		//设置余额位置
		CWnd *pst = GetDlgItem( IDC_ST_BALANCE ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*17 ,(rc.Height()/100)*13-2, rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置确认余额位置
		pst = GetDlgItem( IDC_ST_CONFIRMING ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*17 ,(rc.Height()/100)*22  , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置交易数
		pst = GetDlgItem( IDC_ST_TRANSACTION_NUMBER) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*17 ,(rc.Height()/100)*31+1  , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////设置社区动态超链接位置/////////////////////////////////
		pst = GetDlgItem( IDC_MFCLINK1 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*64 ,(rc.Height()/100)*12  , 294, 20  ,SWP_SHOWWINDOW ) ; 
		}


		pst = GetDlgItem( IDC_MFCLINK2 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*64 ,(rc.Height()/100)*20 , 294, 20  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_MFCLINK3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*64 ,(rc.Height()/100)*27, 294, 20  ,SWP_SHOWWINDOW ) ; 
		}


		pst = GetDlgItem( IDC_MFCLINK4 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*64 ,(rc.Height()/100)*35, 294, 20 ,SWP_SHOWWINDOW ) ; 
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	 
		//设置最近交易1相关内容位置
		pst = GetDlgItem( IDC_ST_SRCADDR1 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*8 ,(rc.Height()/100)*69  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		
		pst = GetDlgItem( IDC_ST_DESADDR1 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*44 ,(rc.Height()/100)*69  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		
		pst = GetDlgItem( IDC_ST_AMOUNT1) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*84 ,(rc.Height()/100)*69  , rc.Width()/100*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置最近交易2相关内容位置
		pst = GetDlgItem( IDC_ST_SRCADDR2 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*8 ,(rc.Height()/100)*77 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_DESADDR2) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*44 ,(rc.Height()/100)*77  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_AMOUNT2 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*84 ,(rc.Height()/100)*77  , rc.Width()/100*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置最近交易3相关内容位置
		pst = GetDlgItem( IDC_ST_SRCADDR3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*8 ,(rc.Height()/100)*85-1 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_DESADDR3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*44 ,(rc.Height()/100)*85-1  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_ST_AMOUNT3 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*84 ,(rc.Height()/100)*85-1  , (rc.Width()/100)*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置最近交易4相关内容位置
		pst = GetDlgItem( IDC_ST_SRCADDR4 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*8 ,rc.Height()-125 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_ST_DESADDR4 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*44 ,rc.Height()-125  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_ST_AMOUNT4 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*84 ,rc.Height()-125 ,  (rc.Width()/100)*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置最近交易5相关内容位置
		pst = GetDlgItem( IDC_ST_SRCADDR5 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*8 ,rc.Height()-95 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_ST_DESADDR5 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*44 ,rc.Height()-95  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_ST_AMOUNT5 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*84 ,rc.Height()-95 ,  (rc.Width()/100)*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		//设置最近交易6相关内容位置
		pst = GetDlgItem( IDC_ST_SRCADDR6 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*8 ,rc.Height()-65 , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_ST_DESADDR6 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*44 ,rc.Height()-65  , (rc.Width()/100)*40, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_ST_AMOUNT6 ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*84 ,rc.Height()-65 ,  (rc.Width()/100)*30, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}

		//设置官方客户QQ链接位置
		pst = GetDlgItem( IDC_MFCLINK_QQ ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,rc.Width()-100 ,rc.Height()-30, 80, 20, SWP_SHOWWINDOW ) ; 
		}
		//设置区块浏览器链接位置
		pst = GetDlgItem( IDC_MFCLINK_BLOCK ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,rc.Width()-180 ,rc.Height()-30, 80, 20, SWP_SHOWWINDOW ) ; 
		}
		//设置跳转全部交易链接位置	
		pst = GetDlgItem( IDC_BTN_TXDETAIL ) ;
		if ( NULL != pst ) {
			CRect rect ;
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,(rc.Width()/100)*91 - 8, rc.Height()/100*60 - 3, rect.Width(), rect.Height(), SWP_SHOWWINDOW ) ; 
		}

	}
}


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN) 
	{  

		switch(pMsg->wParam) 
		{  

		case VK_RETURN: //回车   
			return TRUE;  

		case VK_ESCAPE: //ESC  
			return TRUE;  

		}  

	}  
	return CDialogBar::PreTranslateMessage(pMsg);
}
