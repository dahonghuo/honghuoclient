// Deal.cpp : 实现文件
//

#include "stdafx.h"
#include "huobi.h"
#include "Deal.h"
#include "afxdialogex.h"
#include "huobiDlg.h"
#include "CApplication.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "TxDetailDlg.h"

// CDeal 对话框

IMPLEMENT_DYNAMIC(CDeal, CDialogBar)

CDeal::CDeal()
{
	m_pBmp = NULL ;
	m_seteditcolor = TRUE;
	m_nConut = 0 ;
	m_pagesize = 14;
	m_offset = 0;
}

CDeal::~CDeal()
{
	if( NULL != m_pBmp ) {
		DeleteObject(m_pBmp) ;
		m_pBmp = NULL ;
	}
}

void CDeal::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
	DDX_Control(pDX, IDC_BUTTON_TXDETAIL, m_rBtnTxdetail);
	DDX_Control(pDX, IDC_EXPORT_EXEL, m_rBtnExportTx);
	DDX_Control(pDX, IDC_COMBO1, m_condition);
	DDX_Control(pDX, IDC_COMBO_TIME, m_time);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_edit);
	DDX_Control(pDX, IDC_UP_PAGE, m_rBtnUp);
	DDX_Control(pDX, IDC_NEXT_PAGE, m_rBtnNext);
	DDX_Control(pDX ,IDC_STATIC_COUNT_PAGE ,m_sCountpage ) ;
	DDX_Control(pDX ,IDC_COMBO_PAGE ,m_pageitem ) ;
}


BEGIN_MESSAGE_MAP(CDeal, CDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_TIME, &CDeal::OnCbnSelchangeComboTime)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDeal::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_PAGE, &CDeal::OnCbnSelchangeComboPage)
	ON_BN_CLICKED(IDC_UP_PAGE, &CDeal::OnBnClickedUpPage)
	ON_BN_CLICKED(IDC_NEXT_PAGE, &CDeal::OnBnClickedNextPage)
	ON_BN_CLICKED(IDC_EXPORT_EXEL, &CDeal::OnBnClickedExportExel)
	ON_BN_CLICKED(IDC_BUTTON_TXDETAIL, &CDeal::OnBnClickedButtonTxdetail)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CDeal::OnNMDblclkList)
	ON_MESSAGE(MSG_USER_TRANSRECORD_UI , &CDeal::OnShowListCtrl )
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDeal 消息处理程序
void CDeal::SetBkBmpNid( UINT nBitmapIn ) 
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

BOOL CDeal::OnEraseBkgnd(CDC* pDC)
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


int CDeal::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetBkBmpNid( IDB_BITMAP_BLACK ) ;
	return 0;
}


void CDeal::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if( NULL != GetSafeHwnd() ) {
		CRect rect ; 
		this->GetWindowRect(rect);

		CWnd *pst = GetDlgItem( IDC_COMBO_TIME ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,15 , 15 , 128, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_COMBO1 ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,15+128+20 , 15 , 128, rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_EDIT_SEARCH ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,15+15+20+128+264 , 15 , 320, 24  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_LIST ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,15 , 15+24+15 , 870, 355  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_STATIC_PAGE ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,544 , 15+24+15+355+15+3 , 30, 24  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_COMBO_PAGE ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,544+30 , 15+24+15+355+15 ,  72, rect.Height() ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_STATIC_TM ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,544+30+72+5 , 15+24+15+355+15+3 , 30, 24  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_UP_PAGE ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,544+30+72+5+30 + 8 , 15+24+15+355+15 , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_EDIT_PAGE ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,544+30+72+5+30+5+30 , 15+24+15+355+15 , 30, 20  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_NEXT_PAGE ) ;
		if ( NULL != pst ) {
			pst->GetClientRect( rect ) ;
			pst->SetWindowPos( NULL ,544+30+72+5+30+5+30+5+30 , 15+24+15+355+15 , rect.Width(), rect.Height()  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_STATIC_SUM ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,544+30+72+5+30+5+30+5+30+30 , 15+24+15+355+15+3 , 30, 24  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_STATIC_COUNT_PAGE ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,544+30+72+5+30+5+30+5+30+30+30 , 15+24+15+355+15+3 , 30, 24  ,SWP_SHOWWINDOW ) ; 
		}

		pst = GetDlgItem( IDC_EXPORT_EXEL ) ;
		if ( NULL != pst ) {
		   pst->SetWindowPos( NULL ,885 - 81 - 81 - 10 ,  15+24+15+355+15+3 + 24 + 5  , 81, 31  ,SWP_SHOWWINDOW ) ; 
		}
		pst = GetDlgItem( IDC_BUTTON_TXDETAIL ) ;
		if ( NULL != pst ) {
			pst->SetWindowPos( NULL ,885 - 81 ,  15+24+15+355+15+3 + 24 + 5  , 81, 31  ,SWP_SHOWWINDOW ) ; 
		}
	}
}

void  CDeal::OninitializeList()
{
	ShowComboxCotent();
}

void    CDeal::ShowComboxCotent()
{
	int operate = 0;
	string condtion = GetConditonStr(operate);
	uistruct::TRANSRECORDLIST pListInfo;

	string strCond0 =  condtion;

	string tempConditon = "confirm_height=0 and ";
	tempConditon +=strCond0;
	strCond0 = tempConditon;

	theApp.m_SqliteDeal.GetTransactionList(strCond0, &pListInfo); 

	/*
	std::vector<uistruct::REVTRANSACTION_t>::const_iterator const_it;
	int i = 1;
	TRACE("1111111111111111111\n");
	for ( const_it = pListInfo.begin() ; const_it != pListInfo.end() ; const_it++ ) {
		TRACE("item:%d, id:%s\n", i, const_it->txhash.c_str());
		i++;
	}*/

	uistruct::TRANSRECORDLIST pListInfo1;
	string strCond = " confirm_height!=0 and "+ condtion;// + _T(" LIMIT 17 OFFSET 0") ;
	strCond += strprintf(" LIMIT %d OFFSET 0",(m_pagesize-pListInfo.size()));
	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo1); 

	/*
	i = 1;
	TRACE("2222222222222222222\n");
	for ( const_it = pListInfo1.begin() ; const_it != pListInfo1.end() ; const_it++ ) {
		TRACE("item:%d, id:%s\n", i, const_it->txhash.c_str());
		i++;
	}
	*/
	m_offset = pListInfo.size();
	pListInfo.insert(pListInfo.end(),pListInfo1.begin(),pListInfo1.end());

	int nPage = 0 ;
	int nItem =  theApp.m_SqliteDeal.GetTableCountItem("t_transaction",strCond);
	//	if ( nItem == 0 ) return ;
	if ( nItem%m_pagesize != 0  ) {
		nPage = nItem/m_pagesize + 1 ;
	}else {
		nPage =  nItem/m_pagesize ;
	}
	string temp;
	temp =strprintf("%s%d",_T("共:") ,nPage );
	GetDlgItem(IDC_STATIC_COUNT_PAGE)->SetWindowText(temp.c_str());
	if (nPage > 0)
	{
		GetDlgItem(IDC_EDIT_PAGE)->SetWindowText(_T("1"));
	}else{
		GetDlgItem(IDC_EDIT_PAGE)->SetWindowText(_T("0"));
	}
	Invalidate();

	OnShowListCtrl(pListInfo);
}

void CDeal::OnShowListCtrl(uistruct::TRANSRECORDLIST pListInfo){

	m_listCtrl.DeleteAllItems();
	if (pListInfo.size() == 0)
	{
		return;
	}

	m_pListInfo.clear();
	m_pListInfo.insert(m_pListInfo.begin(),pListInfo.begin(),pListInfo.end());

	int count = (m_nConut)*m_pagesize+1;
	int nSubIdx = 0 , i = 0 ;
	string strShowData = "";
	//TRACE("333333333333333333333\n");
	std::vector<uistruct::REVTRANSACTION_t>::const_iterator const_it;
	for ( const_it = pListInfo.begin() ; const_it != pListInfo.end() ; const_it++ ) {

		nSubIdx = 0;
		strShowData = strprintf("%d", count++);
		m_listCtrl.InsertItem(i, strShowData.c_str());					//序号

		string txtype = const_it->txtype;
		if (!strcmp(txtype.c_str(),"REWARD_TX"))
		{
			strShowData = _T("挖矿");
		}else if (!strcmp(txtype.c_str(),"REG_ACCT_TX"))
		{
			strShowData= _T("激活") ;
		}else if (!strcmp(txtype.c_str(),"COMMON_TX"))
		{
			if (const_it->state == 3)
			{
				strShowData= _T("转账<平>");
			}else if (const_it->state == 2)
			{
				strShowData= _T("转账<收>");
			}else if (const_it->state == 1)
			{
				strShowData= _T("转账<发>") ;
			}else
			{
				strShowData= _T("转账") ;
			}
		}else if (!strcmp(txtype.c_str(),"CONTRACT_TX"))
		{
			strShowData= _T("合约");
		}else if (!strcmp(txtype.c_str(),"REG_APP_TX"))
		{
			strShowData= _T("注册") ;
		}
		m_listCtrl.SetItemText( i , ++nSubIdx, strShowData.c_str());   //交易类型


		m_listCtrl.SetItemText(i , ++nSubIdx , const_it->addr.c_str() );   //源地址

		strShowData= strprintf("%.2f" , const_it->money ) ;
		m_listCtrl.SetItemText(i , ++nSubIdx , strShowData.c_str() );   //交易金额

		m_listCtrl.SetItemText(i , ++nSubIdx , const_it->desaddr.c_str() );   //目的地址


		string txhash= const_it->txhash.substr(0,25)+"...";
		strShowData = strprintf("%s", txhash.c_str()); 
		m_listCtrl.SetItemText(i , ++nSubIdx , strShowData.c_str() );  //交易hash

		//TRACE("item:%d, id:%s\n", i, const_it->txhash.c_str());

		i++;
	}
}

string CDeal::GetConditonStr(int &operate)
{
	string condtion ="";
	string temp ="";

	temp = GetConditonTxType(operate);
	if (temp !="")
	{
		condtion = GetConditonTxType(operate);
	}

	if (condtion !="")
	{
		temp = GetConditonTime();
		if (temp !=_T(""))
		{
			condtion+=strprintf( " and %s",temp.c_str());
		}


	}else{
		temp = GetConditonTime();
		if (temp != _T(""))
		{
			condtion += strprintf( " %s",temp.c_str());
		}
	}

	if (condtion !=_T(""))
	{
		temp = Getaddr();
		if (temp != _T(""))
		{
			if (operate == 1)   ///  接收钱的地址
			{
				condtion+=strprintf( " and des_addr = '%s'",temp.c_str());
			}else if (operate == 2)
			{
				condtion+=strprintf( " and src_addr = '%s'",temp.c_str());
			}else{
				condtion+=strprintf( " and (src_addr = '%s' or des_addr = '%s')",temp.c_str(),temp.c_str());
			}

		}

	}else{
		temp = Getaddr();
		if (temp != "")
		{
			if (operate == 1)
			{
				condtion+=strprintf( "des_addr = '%s'",temp.c_str());
			}else if (operate == 2)
			{
				condtion+=strprintf( "src_addr = '%s'",temp.c_str());
			}else{
				condtion+=strprintf( " src_addr = '%s' or des_addr = '%s'",temp.c_str(),temp.c_str());
			}
		}

	}
	if (condtion =="")
	{
		condtion ="1=1";
	}
	condtion+=" order by confirmed_time DESC";
	return condtion;
}

string CDeal::GetConditonTime(){
	SYSTEMTIME curTime ;
	memset( &curTime , 0 , sizeof(SYSTEMTIME) ) ;
	GetLocalTime( &curTime ) ;
	string strSendTime;
	strSendTime = strprintf("%04d-%02d-%02d %02d:%02d:%02d",curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);
	INT64 maxcurtime = UiFun::SystemTimeToTimet(curTime);

	CString text;
	int sel = m_time.GetCurSel();
	if (sel < 0)
	{
		return _T("");
	}
	m_time.GetLBText(sel,text);
	uistruct::TRANSRECORDLIST pListInfo;

	string conditon;

	if (strcmp(text,  _T("全部") ) == 0)
	{
		return _T("");
	}else if (strcmp(text, _T("今天") ) == 0)
	{
		curTime.wHour = 0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon = strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon += strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text, _T("本周") ) == 0)
	{
		curTime.wHour = 0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = 0;
		if (curTime.wDayOfWeek == 0)
		{
			mincurtime = UiFun::SystemTimeToTimet(curTime);
		}else{
			INT64 differ = 86400*curTime.wDayOfWeek;
			mincurtime = UiFun::SystemTimeToTimet(curTime);
			mincurtime = maxcurtime -mincurtime;
			mincurtime = maxcurtime - (differ+mincurtime);
		}

		conditon =strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("本月")) == 0)
	{
		curTime.wDay =1;
		curTime.wHour = 0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon = strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("上月")) == 0)
	{
		INT64 maxcurtime = 0;
		INT64 mincurtime = 0;
		curTime.wDay =1;
		curTime.wHour=0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		maxcurtime = UiFun::SystemTimeToTimet(curTime);
		if (curTime.wMonth == 1)
		{
			curTime.wMonth = 12;
			curTime.wYear -=1;

		}else{
			curTime.wMonth -= 1;
		}
		mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon= strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("今年")) == 0)
	{
		curTime.wMonth =1;
		curTime.wDay=1;
		curTime.wHour=0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 mincurtime = UiFun::SystemTimeToTimet(curTime);

		conditon =strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon+=strprintf("%d",maxcurtime);
		return conditon;
	}else if (strcmp(text,_T("昨天")) == 0)
	{
		curTime.wHour=0;
		curTime.wMinute = 0;
		curTime.wSecond = 0;
		curTime.wMilliseconds = 0;
		INT64 maxcurtime = UiFun::SystemTimeToTimet(curTime);
		INT64 mincurtime = maxcurtime - 24*60*60;

		conditon=strprintf(" confirmed_time>=%d and confirmed_time<=",mincurtime);
		conditon +=strprintf("%d",maxcurtime);
		return conditon;
	}
	return _T("");
}

string CDeal::GetConditonTxType(int &operate){
	CString text;
	int sel = m_condition.GetCurSel();
	if (sel < 0)
	{
		return _T("");
	}
	m_condition.GetLBText(sel,text);
	uistruct::TRANSRECORDLIST pListInfo;

	string conditon;

	if (strcmp(text,_T("全部")) == 0)
	{
		return _T("");
	}else if (strcmp(text,"接收") == 0)
	{
		operate = 1;

		conditon=" tx_type='COMMON_TX' and (state =2 or state =3)";
		return conditon;
	}else if (strcmp(text,_T("发送")) == 0)
	{
		operate = 2;
		conditon=" tx_type='COMMON_TX' and (state =1 or state =3)";
		return conditon;
	}else if (strcmp(text,_T("挖矿所得")) == 0)
	{
		conditon=" tx_type='REWARD_TX'";
		return conditon;
	}else if (strcmp(text,_T("合约")) == 0)
	{
		conditon=" tx_type='CONTRACT_TX'";
		return conditon;
	}else if (strcmp(text,_T("激活")) == 0)
	{
		conditon=" tx_type='REG_ACCT_TX'";
		return conditon;
	}
	return "";
}

string CDeal::Getaddr(){

	CString ret = _T("");
	GetDlgItem(IDC_EDIT_SEARCH)->GetWindowText(ret);
	if (strcmp(ret,_T("请输入地址进行搜索")) == 0)
	{
		ret = "";
	}
	string stret =strprintf("%s",ret);
	return stret;
}

BOOL CDeal::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类

	BOOL bRes = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if ( bRes ) {
		UpdateData(FALSE);
		struct LISTCol {
			CString		name ;
			UINT		size ;
		} listcol[5]  = {
			{"序号" ,      50},
			{"交易类型" ,      100},
			{"源地址" ,      290},
			{"金额" ,      119}, 
			{"目的地址" ,       290}
			//{"交易ID" ,      168}
		};
		m_listCtrl.SetBkColor(RGB(240,240,240));       
		m_listCtrl.SetRowHeigt(23);               
		m_listCtrl.SetHeaderHeight(1.5);         
		m_listCtrl.SetHeaderFontHW(15,0);
		m_listCtrl.SetHeaderBKColor(224,65,18,0); 
		m_listCtrl.SetHeaderTextColor(RGB(255,255,255)); 
		m_listCtrl.SetTextColor(RGB(0,0,0));  
		for( int i = 0 ; i <5 ; i++  ) {
			m_listCtrl.InsertColumn(i,listcol[i].name,LVCFMT_CENTER,listcol[i].size);
		}
		m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP );// |LVS_SINGLESEL  );

		m_rBtnTxdetail.SetBitmaps( IDB_BITMAP_BUTTON , RGB(255, 255, 0) , IDB_BITMAP_BUTTON , RGB(255, 255, 255) );
		m_rBtnTxdetail.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnTxdetail.SetWindowText("查看详情") ;
		m_rBtnTxdetail.SetFontEx(20 , _T("微软雅黑"));
		m_rBtnTxdetail.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
		m_rBtnTxdetail.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnTxdetail.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255,255));
		m_rBtnTxdetail.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
		m_rBtnTxdetail.SizeToContent();

		m_rBtnExportTx.SetBitmaps( IDB_BITMAP_BUTTON , RGB(255, 255, 0) , IDB_BITMAP_BUTTON , RGB(255, 255, 255) );
		m_rBtnExportTx.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnExportTx.SetWindowText("导出Excel") ;
		m_rBtnExportTx.SetFontEx(20 , _T("微软雅黑"));
		m_rBtnExportTx.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255,255,255));
		m_rBtnExportTx.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnExportTx.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255,255));
		m_rBtnExportTx.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255,255,255));
		m_rBtnExportTx.SizeToContent();

		m_rBtnUp.SetBitmaps( IDB_TRADE_UP , RGB(255, 255, 0) , IDB_TRADE_UP , RGB(255, 255, 255) );
		m_rBtnUp.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnUp.SetWindowText("") ;
		m_rBtnUp.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
		m_rBtnUp.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnUp.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
		m_rBtnUp.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
		m_rBtnUp.SizeToContent();

		m_rBtnNext.SetBitmaps( IDB_TRADE_NEXT , RGB(255, 255, 0) , IDB_TRADE_NEXT , RGB(255, 255, 255) );
		m_rBtnNext.SetAlign(CButtonST::ST_ALIGN_OVERLAP);
		m_rBtnNext.SetWindowText("") ;
		m_rBtnNext.SetColor(CButtonST::BTNST_COLOR_FG_OUT , RGB(255, 255, 255));
		m_rBtnNext.SetColor(CButtonST::BTNST_COLOR_FG_IN , RGB(200, 75, 60));
		m_rBtnNext.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, RGB(255, 255, 255));
		m_rBtnNext.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(255, 255, 255));
		m_rBtnNext.SizeToContent();

		m_condition.InsertString(0,_T("全部"));
		m_condition.InsertString(1,_T("接收"));
		m_condition.InsertString(2,_T("发送"));
		m_condition.InsertString(3,_T("挖矿所得"));
		m_condition.InsertString(4,_T("合约"));
		m_condition.InsertString(5,_T("激活"));
		//m_condition.AddString(_T("全部"));
		//m_condition.AddString(_T("接收"));
		//m_condition.AddString(_T("发送"));
		//m_condition.AddString(_T("挖矿所得"));

		m_time.InsertString(0,_T("全部"));
		m_time.InsertString(1,_T("今天"));
		m_time.InsertString(2,_T("本周"));
		m_time.InsertString(3,_T("本月"));
		m_time.InsertString(4,_T("上月"));
		m_time.InsertString(5,_T("今年"));
		m_time.InsertString(6,_T("昨天"));

		m_pageitem.InsertString(0,_T("14"));
		m_pageitem.InsertString(1,_T("20"));
		m_pageitem.InsertString(2,_T("30"));
		m_pageitem.InsertString(3,_T("50"));
		m_pageitem.InsertString(4,_T("100"));


		m_edit.SetWindowText(_T("请输入地址进行搜索"));

		GetDlgItem(IDC_STATIC_PAGE)->SetWindowText(_T("每页"));
		GetDlgItem(IDC_STATIC_TM)->SetWindowText(_T("条"));

		m_condition.SetCurSel(0);
		m_time.SetCurSel(0);
		m_pageitem.SetCurSel(0);

		m_colorEditText = RGB(159,161,164);

		OninitializeList();

		theApp.SubscribeMsg( theApp.GetMtHthrdId() , GetSafeHwnd() , MSG_USER_TRANSRECORD_UI ) ;
	}
	return bRes ;
}

void  CDeal::ShowPageCotent(int pageIndex)
{
	if ( 0 > pageIndex ){
		UiFun::MessageBoxEx(_T("已经是最开始页了!") ,_T("提示") ,MFB_OK|MFB_TIP );
		return ;
	} 
	if (pageIndex == 0)
	{
		ShowComboxCotent();
		return;
	}
	string strCond ;
	uistruct::TRANSRECORDLIST pListInfo;
	int num = (pageIndex * m_pagesize - m_offset)<0?0:(pageIndex * m_pagesize - m_offset);
	std::stringstream strTemp;  
	string str;
	strTemp<< num;
	strTemp>>str;
	int operate = 0;
	string condtion = GetConditonStr(operate);
	strCond =  condtion + strprintf(" LIMIT %d OFFSET ",m_pagesize) + str ;
	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo); 
	if ( 0 == pListInfo.size() ) {
		m_nConut -= 1 ;
		UiFun::MessageBoxEx(_T("已经是最后页了!") , _T("提示") ,MFB_OK|MFB_TIP );
		string strpage;
		strpage = strprintf("%d",m_nConut + 1);
		GetDlgItem(IDC_EDIT_PAGE)->SetWindowText(strpage.c_str());
		Invalidate();
		return ;
	}
	int nPage = 0 ;
	int nItem =  theApp.m_SqliteDeal.GetTableCountItem(_T("t_transaction") , condtion );
	if ( nItem == 0 ) return ;
	if ( nItem%m_pagesize != 0  ) {
		nPage = nItem/m_pagesize + 1 ;
	}else {
		nPage =  nItem/m_pagesize ;
	}
	string temp;
	temp =strprintf("%s%d",_T("共:") ,nPage);
	GetDlgItem(IDC_STATIC_COUNT_PAGE)->SetWindowText(temp.c_str());
	GetDlgItem(IDC_EDIT_PAGE)->SetWindowText(_T(""));

	string strpage;
	strpage = strprintf("%d",m_nConut + 1);
	GetDlgItem(IDC_EDIT_PAGE)->SetWindowText(strpage.c_str());

	Invalidate();

	OnShowListCtrl(pListInfo);
}


void CDeal::OnCbnSelchangeComboTime()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nConut = 0;
	ShowComboxCotent();
}


void CDeal::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nConut = 0;
	ShowComboxCotent();
}


void CDeal::OnCbnSelchangeComboPage()
{
	// TODO: 在此添加控件通知处理程序代码
	int cursel = m_pageitem.GetCurSel();
	switch(cursel)
	{
	case 0:
		{
			m_pagesize = 13;
		}
		break;
	case 1:
		{
			m_pagesize = 20;
		}
		break;
	case 2:
		{
			m_pagesize = 30;
		}
		break;
	case 3:
		{
			m_pagesize = 50;
		}
		break;
	case 4:
		{
			m_pagesize = 100;
		}
		break;
	default:
		break;
	}
	m_nConut = 0 ;
	ShowComboxCotent();
}


void CDeal::OnBnClickedUpPage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nConut -= 1 ;
	ShowPageCotent(m_nConut);
}


void CDeal::OnBnClickedNextPage()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nConut += 1 ;
	ShowPageCotent(m_nConut);
}

void CDeal:: GetExportCol(int index,map<int,string> &item,uistruct::REVTRANSACTION_t const_it)
{
	string strShowData = "";
	string txtype = const_it.txtype;

	int i = 0;
	//strShowData= strprintf("%d" , index) ;
	//item[i++] =strShowData;
	if (!strcmp(txtype.c_str(),"REWARD_TX"))
	{
		strShowData = _T("挖矿") ;
	}else if (!strcmp(txtype.c_str(),"REG_ACCT_TX"))
	{
		strShowData= _T("激活") ;
	}else if (!strcmp(txtype.c_str(),"COMMON_TX"))
	{
		if (const_it.state == 3)
		{
			strShowData= _T("转账<平>");
		}else if (const_it.state == 2)
		{
			strShowData= _T("转账<收>");
		}else if (const_it.state == 1)
		{
			strShowData= _T("转账<发>") ;
		}else
		{
			strShowData= _T("转账") ;
		}
	}else if (!strcmp(txtype.c_str(),"CONTRACT_TX"))
	{
		strShowData= _T("合约");
	}else if (!strcmp(txtype.c_str(),"REG_APP_TX"))
	{
		strShowData= _T("注册") ;
	}
	item[i++] =strShowData;
	item[i++] =const_it.addr;
	strShowData= strprintf("%.8f" , const_it.money ) ;
	item[i++] =strShowData;
	item[i++] =const_it.desaddr;
	item[i++] =const_it.txhash;
}


void CDeal::OnBnClickedExportExel()
{
	// TODO: 在此添加控件通知处理程序代码
	int operate = 0;
	string condtion = GetConditonStr(operate);
	uistruct::TRANSRECORDLIST pListInfo;
	string strCond =  condtion;
	theApp.m_SqliteDeal.GetTransactionList(strCond, &pListInfo); 
	if (pListInfo.size() == 0)
	{
		UiFun::MessageBoxEx(_T("没有记录可以导出！") ,_T("提示") ,MFB_OK|MFB_TIP );
		return;
	}
	CFileDialog dlg(FALSE,NULL,_T("交易记录"),OFN_HIDEREADONLY|OFN_FILEMUSTEXIST ,"文件 (*.xls)|*.xls||");
	if (IDOK != dlg.DoModal())
	{
		return;
	}

	CString strFile = dlg.GetPathName();
	if (!((ChuobiDlg*)(theApp.m_pMainWnd))->GetFileName(strFile,_T(".xls")))
	{
		return;
	}

	struct LISTCol {
		string		name ;
		UINT		size ;
	} listheadr[5]  = {
		//{UiFun::UI_LoadString("TRAD_MODULE" , "TRAD_SERIAL_NUMBER" ,theApp.gsLanguage) ,    10},
		{_T("交易类型") ,    30},
		{_T("源地址") ,    40},
		{_T("金额") ,    10},
		{_T("目的地址") ,  40}, 
		{_T("交易ID") ,100}
	};

	COleVariant

		covTrue((short)TRUE),

		covFalse((short)FALSE),

		covOptional((long)DISP_E_PARAMNOTFOUND,   VT_ERROR);

	CApplication   app;

	CWorkbooks   books;

	CWorkbook   book;

	CWorksheets   sheets;

	CWorksheet   sheet;

	CRange   range;

	CFont0   font;



	if (!app.CreateDispatch(_T("Excel.Application")))

	{

		UiFun::MessageBoxEx(_T("可能是没有装office 导致创建失败！") , _T("提示") ,MFB_OK|MFB_TIP );
		return;

	}



	//Get   a   new   workbook.

	books = app.get_Workbooks();

	book = books.Add(covOptional);



	sheets = book.get_Worksheets();

	sheet = sheets.get_Item(COleVariant((short)1));



	////////////////////////////////////CListCtrl控件report风格//////////////////////////////////////////////////////////

	//CHeaderCtrl   *pmyHeaderCtrl;

	//pmyHeaderCtrl = m_listCtrl.GetHeaderCtrl();//此句取得CListCtrl控件的列表頭



	int   iRow,iCol;

	int   m_cols   =   5;

	int   m_rows = pListInfo.size();

	HDITEM   hdi;

	TCHAR     lpBuffer[256];

	bool       fFound   =   false;



	hdi.mask   =   HDI_TEXT;

	hdi.pszText   =   lpBuffer;

	hdi.cchTextMax   =   256;

	CString   colname;

	CString strTemp;

	for(iCol=0;   iCol <m_cols;   iCol++)//将列表的标题头写入EXCEL

	{

		UiFun::GetCellName(1 ,iCol + 1, colname);

		range   =   sheet.get_Range(COleVariant(colname),COleVariant(colname));

		//pmyHeaderCtrl-> GetItem(iCol,   &hdi);

		range.put_Value2(COleVariant(listheadr[iCol].name.c_str()));

		int   nWidth   = listheadr[iCol].size;  //m_listCtrl.GetColumnWidth(iCol)/6;

		//得到第iCol+1列  

		range.AttachDispatch(range.get_Item(_variant_t((long)(iCol+1)),vtMissing).pdispVal,true);  

		//设置列宽 

		range.put_ColumnWidth(_variant_t((long)nWidth));

	}

	range   =   sheet.get_Range(COleVariant( _T("A1 ")),   COleVariant(colname));

	range.put_RowHeight(_variant_t((long)50));//设置行的高度

	font = range.get_Font();

	font.put_Bold(covTrue);

	range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108



	COleSafeArray   saRet;

	DWORD   numElements[]={m_rows,m_cols};       //5x2   element   array

	saRet.Create(VT_BSTR,   2,   numElements);

	range   =   sheet.get_Range(COleVariant( _T("A2 ")),covOptional);

	range = range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols));

	long   index[2];

	range   =   sheet.get_Range(COleVariant( _T("A2 ")),covOptional);

	range   =   range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols));


	int iLine = 0;
	iRow   =   1;
	iCol   =   1;
	int ncount =1;
	std::vector<uistruct::REVTRANSACTION_t>::const_iterator pitem = pListInfo.begin();
	for(;pitem != pListInfo.end();pitem++,iRow++)
	{
		map<int,string> item;
		GetExportCol(ncount,item,*pitem);
		ncount++;
		for   (   iCol   =   1;   iCol   <=   m_cols;   iCol++)  

		{

			index[0]=iRow-1;

			index[1]=iCol-1;
			string strTemp =  item[iCol-1];
			CString   szTemp = strTemp.c_str();

			BSTR   bstr   =   szTemp.AllocSysString();

			saRet.PutElement(index,bstr);

			SysFreeString(bstr);

		}
	}


	range.put_Value2(COleVariant(saRet));


	saRet.Detach();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	book.SaveCopyAs(COleVariant(strFile));

	//       cellinterior.ReleaseDispatch();

	book.put_Saved(true);

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();

	//book.ReleaseDispatch();  

	//books.ReleaseDispatch();  
	book.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	books.Close(); 
	app.Quit();

	app.ReleaseDispatch();
}


void CDeal::OnBnClickedButtonTxdetail()
{
	// TODO: 在此添加控件通知处理程序代码
	CString StrShow;
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition() ;
	if ( pos ) {
		int nRow = m_listCtrl.GetNextSelectedItem(pos) ;
		//CString strtxhash = m_listCtrl.GetItemText(nRow, 5);

		if (nRow <0 || nRow > (int)m_pListInfo.size())
		{
			return ;
		}
		uistruct::REVTRANSACTION_t  txdetail =m_pListInfo.at(nRow);
		string strCond;
		strCond = strprintf(" hash='%s' ", txdetail.txhash);
		int nItem =  theApp.m_SqliteDeal.GetTransactionItem( strCond ,&txdetail ) ;
		if (txdetail.txhash != _T(""))
		{
			theApp.m_strAddress.Format(_T("%s") ,txdetail.ToJson().c_str() ) ;
		}else
		{		
			theApp.m_strAddress =_T("");
		}
		CTxDetailDlg dlg;
		dlg.DoModal();

	}else{
		StrShow.Format(_T("请选择地址!"));
		UiFun::MessageBoxEx(StrShow , _T("Error") ,MFB_OK|MFB_ERROR );
	}
}

void CDeal::ShowAddrConditon()
{
	m_nConut = 0;
	int operate;
	string condtion = GetConditonStr(operate);

	uistruct::TRANSRECORDLIST pListInfo;
	theApp.m_SqliteDeal.GetTransactionList(condtion, &pListInfo); 
	OnShowListCtrl(pListInfo);
}

void CDeal::ShowPageDataInfo(int nConut)
{
	nConut -=  1 ;
	m_nConut = nConut ;
	ShowPageCotent(nConut);
	return ;
}

BOOL CDeal::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)  
	{   
		if (GetDlgItem(IDC_EDIT_SEARCH) == this->GetFocus())
		{
			ShowAddrConditon();
			return TRUE;
		}else  if (GetDlgItem(IDC_EDIT_PAGE) == this->GetFocus()) {
			CString nConut;
			GetDlgItem(IDC_EDIT_PAGE)->GetWindowText(nConut);
			if (IsAllDigtal(nConut)) {
				ShowPageDataInfo(atoi(nConut));
				return TRUE;
			}else {
				GetDlgItem(IDC_EDIT_PAGE)->SetWindowText(_T(""));
				UiFun::MessageBoxEx(_T("输入有误,请输入数字") ,_T("提示") ,MFB_OK|MFB_TIP );
			}
		}  
	}  
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SEARCH);
	ASSERT(pEdit && pEdit->GetSafeHwnd());
	if(WM_LBUTTONDOWN == pMsg->message && pEdit->GetSafeHwnd() == pMsg->hwnd)
	{
		CString strTemp = _T("");
		m_edit.GetWindowText(strTemp);
		if (strcmp(strTemp, _T("请输入地址进行搜索")) == 0)
		{
			pEdit->SetFocus();
			pEdit->SetSel(1,1,FALSE);
			return TRUE;
		}

	}
	if (pMsg->message == WM_KEYDOWN &&pEdit->GetSafeHwnd() == pMsg->hwnd &&(pMsg->wParam != VK_RETURN))
	{
		CString strTemp = _T("");
		m_edit.GetWindowText(strTemp);
		if (((pMsg->wParam >=48 && pMsg->wParam <=57) 
			|| (pMsg->wParam >=65 && pMsg->wParam <=90)
			|| (pMsg->wParam >=0x60 && pMsg->wParam <=0x69)) && strcmp(strTemp,_T("请输入地址进行搜索")) == 0)
		{
			m_edit.SetWindowText(_T(""));
			m_seteditcolor = FALSE;
		}
	}

	if ( pMsg->message == WM_KEYDOWN &&pEdit->GetSafeHwnd() == pMsg->hwnd &&(pMsg->wParam == VK_BACK) )
	{
		CString strTemp = _T("");
		m_edit.GetWindowText(strTemp);
		if (strTemp.GetLength() ==  1)
		{
			m_edit.SetWindowText(_T("请输入地址进行搜索"));
			m_seteditcolor = TRUE;
		}
	}

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


void CDeal::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(-1 != pNMItemActivate->iItem) 
	{  
		int nRow = pNMItemActivate->iItem;

		if (nRow <0 || nRow > (int)m_pListInfo.size())
		{
			return ;
		}
		uistruct::REVTRANSACTION_t  txdetail =m_pListInfo.at(nRow);

		if (txdetail.txhash != _T(""))
		{
			theApp.m_strAddress.Format(_T("%s") ,txdetail.ToJson().c_str() ) ;
		}else
		{		
			theApp.m_strAddress =_T("");
		}
		CTxDetailDlg dlg;
		dlg.DoModal();
	}  
	*pResult = 0;
}


HBRUSH CDeal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (CTLCOLOR_EDIT == nCtlColor && m_seteditcolor && pWnd->GetDlgCtrlID() == IDC_EDIT_SEARCH)
	{
		pDC->SetTextColor(m_colorEditText);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

LRESULT CDeal::OnShowListCtrl(  WPARAM wParam, LPARAM lParam )
{
	int type = (int)wParam;
	switch(type)
	{
	case WM_INSERT:
		{
			//InsertItemData();
			if ( 0 == m_nConut ) {   //只有当前是首页 , 才去显示
				m_listCtrl.DeleteAllItems();
				OninitializeList();
			}
		}
		break;
	case WM_REMOVETX:
		{
			if ( 0 == m_nConut ) {   //只有当前是首页 , 才去显示
				m_listCtrl.DeleteAllItems();
				OninitializeList();
			}
		}
		break;
	default:
		break;
	}
	return 0;
}
