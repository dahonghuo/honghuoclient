#ifndef __FB_UIHEAD__
#define __FB_UIHEAD__

#include <afxdb.h>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <time.h>
#include <math.h>
#include <string>
#include "json\json.h"
#include "resource.h"		// 主符号
#include "MessageBoxEx.h"
using namespace std;

#define MSG_USER_QUITTHREAD		   WM_USER+1	
#define MSG_USER_MOBILE_STATEUS    WM_USER+2
#define MSG_USER_MOBILE_TIP        WM_USER+3

#define  ININTAL_TYPE          1
#define  BLOCK_CHANGE_TYPE     2
#define  REV_TRANSATION_TYPE   3
#define  APP_TRANSATION_TYPE   4
#define  SERVER_NOTIYF_TYPE    5
#define  SERVER_SYNC_TX        6
#define  WALLET_LOCK           7
#define  WALLET_UNLOCK         8
#define  RELEASE_TX            9
#define  REMOVE_TX            10
#define  CONNECTON_NET        11
#define  SYSTX_HEIGHT         12


//#define
#define LANGUAGE_FILE			"\\Config\\Language.ini"
#define LANGUAGE_FILE_CN		"\\Config\\Language_CN.ini"
#define LANGUAGE_FILE_EN		"\\Config\\Language_EN.ini"

#define MSG_USER_MAIN_UI			        WM_USER+105	    //更新到Mian界面
#define MSG_USER_TRANSRECORD_UI			    WM_USER+106	    //更新到TransRecord界面
#define MSG_USER_GET_UPDATABASE             WM_USER+107     //从数据库中获取数据
#define MSG_USER_SHOW_INIT                  WM_USER+108    //显示服务器初始化 
#define MSG_USER_UP_PROGRESS			    WM_USER+109	    //更新进度条  1131
#define MSG_USER_INSERT_DATA                WM_USER+110    //插入数据到数据库
#define MSG_USER_UPDATA_DATA                WM_USER+111	    //更新数据到数据库
#define MSG_USER_SEND_UI			        WM_USER+112    //更新到转账  1138
#define MSG_USER_RECIVE_UI			        WM_USER+113    //更新到接受页面
#define MSG_USER_STARTPROCESS_UI			WM_USER+114    //更新启动的界面
#define MSG_USER_UPDATA_UI			        WM_USER+115   //更新到接受页面
#define MSG_USER_P2P_UI			            WM_USER+116	    //更新到P2P界面
#define MSG_USER_REDPACKET_UI			    WM_USER+117	    //更新到P2P界面
#define MSG_USER_P2PADDRES			        WM_USER+118	    //更新到P2P界面常用地址
#define MSG_USER_CLOSEPROCESS			    WM_USER+121	    //更新到P2P界面常用地址

#define WM_SHOWTASK                        (WM_USER +119) 
#define WM_POPUPBAR                       (WM_USER +120) 

//#define MSG_USER_QUITTHREAD			        WM_USER+200	    //退出线程
#define MSG_USER_OUT                        WM_USER+201     //退出软件


#define MSG_USER_END			        WM_USER+800	    //退出线程
#define WM_BN_CLICK						WM_USER+801
//enum
enum {
	LANGUAGE_CN = 0x01,
	LANGUAGE_EN ,
} ;
enum {
	MFB_OK        = 0x0001L,         //确认
	MFB_CANCEL    = 0x0002L,         //取消
	MFB_OKCANCEL  = 0x0003L,         //确认 & 取消
	MFB_YES       = 0x0004L,         //是
	MFB_NO        = 0x0008L,         //否
	MFB_YESNO     = 0x000CL,         //是 &　否

	MFB_TIP       = 0x0010L,         //提示
	MFB_ERROR     = 0x0020L,         //错误
	MFB_WARNING   = 0x0040L,         //警告

	MFB_BK_RED    = 0x0100L          //红色背景
} ;


enum cmLOCKSTATUS {
	STATUS_DECRYPTED = 0,             //无加密
	STATUS_UNLOCKED = 1,              //加密解锁状态
	STATUS_LOCKED = 2                 //加密加锁状态             
};

enum cmNETWORKTYPE {
	MAIN = 0,             //主网络
	REGTEST = 1,          //本地局域网络
	TESTNET = 2           //测试状态             
};


typedef enum tagDialogType{
	DIALOG_MYWALLET     = 0x01,    //我的钱包 
	DIALOG_P2P_BET       ,         //P2p赌约
	DIALOG_GUARANTEE     ,         //担保交易  
	DIALOG_PRESS         ,         //抵压交易
	DIALOG_SIGN_ACCOUNTS ,         //注册帐号
	DIALOG_SIGN_USE      ,         //注册应用
	DIALOG_TRANSFER      ,         //转帐
	DIALOG_TRANSFER_RECORD,        //交易记录
	DIALOG_SEND_RECORD   ,         //发送记录
	DIALOG_ACCEPTBET_RECORD   ,         //发送记录
	DIALOG_SEND_PRESS         ,         //发送抵压交易
	DIALOG_ACCEPT_PRESS         ,         //发送抵压交易
	DIALOG_BLOCK_STATE        ,         //状态
} DialogType ;
 

typedef enum tagUiDataType{
	DATA_MYWALLET     = 0x001,   //我的钱包 
	DATA_P2P_BET       ,         //P2p赌约
	DATA_GUARANTEE     ,         //担保交易  
	DATA_PRESS         ,         //抵压交易
	DATA_SIGN_ACCOUNTS ,         //注册帐号
	DATA_SIGN_USE      ,         //注册应用
	DATA_TRANSFER      ,         //转帐
	DATA_TRANSFER_RECORD,        //交易记录
	DATA_SEND_RECORD   ,         //发送记录
} UiDataType ;

typedef enum tagUiType{
	UI_TRANSIONRECORD     = 0x01,   //交易记录 
	UI_SENDP2P_RECORD       ,       //P2p赌约
	UI_ACCEPTP2P_RECORD     ,       //接受赌约记录  
	UI_READPACKET_RECORD          ,       //抵压交易
} UiType ;

extern CString txTypeArray[];

#pragma pack(push)
#pragma pack(1)
namespace uistruct {
	//listaddr结构
	typedef struct LISTADDR{   
		string    address ;   //address
		string    RegID   ;   //RegID
		double  fMoney      ;   //金额
		int     nColdDig    ;   //是否支持冷挖矿 1:代表支持  ， 0:代表不支持
		int     bSign       ;   //是否注册       1:已注册    ,  0:没注册
		string    Label       ;
		LISTADDR(){
			address="";
			RegID="";
			Label="";
			fMoney = 0.0;
			nColdDig =0;
			bSign = 0;
		}
		string ToJson(){
			Json::Value root;
			root["address"] = address;
			root["RegID"] = RegID;
			root["fMoney"] = fMoney;
			root["nColdDig"] = nColdDig;
			root["bSign"] = bSign;
			root["Label"] = Label;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			address = root["address"].asString();
			
			RegID =  root["RegID"].asString();
			this->fMoney = root["fMoney"].asDouble();
			this->nColdDig = root["nColdDig"].asInt();
			this->bSign = root["bSign"].asInt();

			Label=root["Label"].asString();
			return true;
		}
	}LISTADDR_t;
	typedef std::vector<LISTADDR_t> LISTADDRLIST ;
	//常用listaddr结构
	typedef struct COMMONLISTADDR{   
		string    reg_id ;   //address
		string    app_id   ;   //RegID
		int       keyid   ;   //关系ID
		COMMONLISTADDR(){
			reg_id="";
			app_id="";
			keyid = 0;
		}
		string ToJson(){
			Json::Value root;
			root["reg_id"] = reg_id;
			root["app_id"] = app_id;
			root["keyid"] = keyid;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			reg_id = root["reg_id"].asString();
			
			app_id =  root["app_id"].asString();
			this->keyid = root["keyid"].asInt();
			return true;
		}
	}COMMONLISTADDR_t;
	typedef std::vector<COMMONLISTADDR_t> COMMONADDRLIST ;
	//初始化服务器结构体
	typedef struct INITSERVER{   
		char    sType[32] ;   //类型
		char    msg[1000] ;   //内容
	}INITSERVER_t;

	//发送赌约 和 接收赌约
	typedef struct DB_DATA{
		unsigned char betstate;
		INT64         money;
		unsigned int hight;
		unsigned char dhash[32];//32 + one byte checksum
		unsigned char accepthash[32];//32 + one byte checksum
		char     sendbetid[6];
		char     acceptbetid[6];
		unsigned char acceptebetdata;
	}DB_DATA_t;
	
	typedef struct P2P_QUIZ_RECORD {
		time_t send_time       ;     //发送时间
		time_t recv_time       ;     //接收时间
		int    time_out        ;     //超时
		string   tx_hash    ;      //发赌约hash
		string   left_addr  ;		//发赌约地址
		string   right_addr ;		//接受赌约地址
		double  amount  ;				//金额
		char   content[33]    ;       //明文 
		int    actor  ;               // 0 发起赌约 1 接受赌约 2 即使发起赌约又是接受赌约
		int    confirmed      ;        // 是否已确认
		int    height         ;           //确定高度
		int    state          ;         //0 发起状态 1 接赌状态 2 揭赌状态 3 已经超过揭赌时间 4 正在接赌 5正在揭赌
		string   relate_hash;          //接赌hash
		int    guess_num;      //接猜的数字
		int    deleteflag;      //接猜的数字 0 没有删除 1 删除标志
		double  accept_amount  ;				//金额
		P2P_QUIZ_RECORD(){
			send_time = 0;
			recv_time = 0;
			time_out = 0;
			tx_hash = "";
			left_addr ="";
			right_addr = "";
			amount = 0;
			memset(content, 0, 33);
			actor = 0;
			confirmed =0;
			height = 0;
			state = 0;
			relate_hash = "";
			guess_num = 0;
			deleteflag = 0;
			accept_amount = 0;
		}
		string ToJson(){
			Json::Value root;
			root["send_time"] = send_time;
			root["recv_time"] = recv_time;
			root["time_out"] = time_out;
			root["tx_hash"] = tx_hash;
			root["left_addr"] = left_addr;
			root["right_addr"] = right_addr;
			root["amount"] = amount;
			root["content"] = content;
			root["actor"] = actor;
			root["confirmed"] = confirmed;
			root["height"] = height;
			root["relate_hash"] = relate_hash;
			root["state"] = state;
			root["guess_num"] = guess_num;
			root["deleteflag"] = deleteflag;
			root["accept_amount"] = accept_amount;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;

			this->send_time = root["send_time"].asInt() ;
			this->recv_time = root["recv_time"].asInt();
			this->time_out = root["time_out"].asInt();

			tx_hash = root["tx_hash"].asString();
		
			left_addr = root["left_addr"].asString();
	
			right_addr = root["right_addr"].asString();
	
			this->amount = root["amount"].asDouble();

			CString temp = root["content"].asCString();
			memcpy(content,temp,sizeof(content));
	
			this->actor = root["actor"].asInt();
			this->confirmed = root["confirmed"].asInt();
			this->height = root["height"].asInt();

			relate_hash = root["relate_hash"].asString();
			
		
			this->state = root["state"].asInt();
			this->guess_num = root["guess_num"].asInt() ;
			this->deleteflag=root["deleteflag"].asInt() ;
			this->accept_amount=root["accept_amount"].asDouble() ;
			return true;
		}
	}P2P_QUIZ_RECORD_t;

	typedef std::vector<P2P_QUIZ_RECORD_t> P2PBETRECORDLIST ;

	typedef struct {                 //赌约应用数据库结构
		unsigned char betstate;        //00未接赌 01接赌
		INT64         money;
		unsigned short hight;
		unsigned char dhash[32];//32 + one byte checksum
		unsigned char accepthash[32];//32 + one byte checksum
		unsigned char sendbetid[6];
		unsigned char acceptbetid[6];
		unsigned char acceptebetdata;
		INT64         accept_money;

	}DBBET_DATA;
	typedef std::vector<DBBET_DATA> DBBETDATALIST ;
	//交易记录
	typedef struct REVTRANSACTION{
		string    txhash  ;   //hash
		string    txtype ;  //类型
		int       ver;
		string    addr   ;  //
		string    pubkey;
		string	  miner_pubkey;
		double    fees       ;
		int       height     ;  // 
		string    desaddr   ;
		double   money        ;
		string   Contract  ;
		int      confirmedHeight ; //确认时间
		int      confirmedtime ; //确认时间
		string     blockhash      ;  //1:为确认状态   0:为未为确认状态
		int       state;      ///3 平账 1 扣钱 2加钱
		string   regid;
		string   desregid;
		string ToJson(){
			Json::Value root;
			root["hash"] = txhash;
			root["txtype"] = txtype;
			root["ver"] = ver;
			root["addr"] = addr;
			root["pubkey"] = pubkey;
			root["miner_pubkey"] = miner_pubkey;
			root["fees"] = fees;
			root["height"] = height;
			root["desaddr"] = desaddr;
			root["money"] = money;
			root["Contract"] = Contract;
			root["confirmHeight"] = confirmedHeight;
			root["confirmedtime"] = confirmedtime;
			root["blockhash"] = blockhash;
			root["state"] = state;
			root["regid"] = regid;
			root["desregid"] = desregid;
			return root.toStyledString();
		}

		REVTRANSACTION(){
			txhash = _T("")  ;   
			txtype = "";  //类型
			ver = 0;
			addr  = "" ;  //
			 pubkey  = "";
			  miner_pubkey  = "";
			  fees = 0.0      ;
			 height = 0    ;  // 
			desaddr  = ""   ;
			 money =0.0       ;
			 Contract  = ""  ;
			confirmedHeight = 0 ; //确认时间
			confirmedtime = 0; //确认时间
			blockhash  = ""      ;  //1:为确认状态   0:为未为确认状态
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;

			this->txhash = root["hash"].asString() ;  
			this->txtype = root["txtype"].asString(); 
			this->ver = root["ver"].asInt();
			this->addr = root["addr"].asString()  ;
			this->height  =root["height"].asInt()   ;

			int pos = -1;
			pos = json.find("money"); 
			if( pos>=0)
			{
				this->money = (root["money"].asDouble()*1.0)/100000000 ;
			}
			
			pos = json.find("pubkey"); 
			if(pos>=0)
			this->pubkey = root["pubkey"].asString();

			pos = json.find("miner_pubkey") ;
			if(pos >=0)
			this->miner_pubkey = root["miner_pubkey"].asString();

			pos = json.find("fees") ;
			if(pos >=0)
			{
				this->fees = (root["fees"].asDouble()*1.0)/100000000 ;
			}
			
			pos = json.find("desaddr") ;
			if(pos >=0)
			this->desaddr =root["desaddr"].asString()  ;

			pos = json.find("Contract") ;
			if(pos >=0)
			this->Contract = root["Contract"] .asString() ;

			pos = json.find("confirmHeight") ;
			if(pos >=0)
			this->confirmedHeight = root["confirmHeight"].asInt() ; 

			pos = json.find("confirmedtime") ;
			if(pos >=0)
			this->confirmedtime = root["confirmedtime"].asInt();  

			pos = json.find("blockhash") ;
			if(pos >=0)
			this->blockhash = root["blockhash"].asString()     ;

			pos = json.find("state") ;
			if(pos >=0)
			this->state = root["state"].asInt();

			pos = json.find("regid");
			if(pos >=0)
				this->regid = root["regid"].asString();

			 pos = json.find("desregid");
			if(pos >=0)
				this->desregid = root["desregid"].asString();

			return true;
		}
	}REVTRANSACTION_t;
	typedef std::vector<REVTRANSACTION_t> TRANSRECORDLIST ;

	//// 接受抵押交易记录
	typedef struct {
		time_t sendtime       ;     //发送时间
		time_t recvtime       ;     //接收时间
		char   tx_hash[64+1]    ;      //发送抵押hash
		char   left_addr[34+1]  ;		//发送抵押地址
		char   right_addr[34+1] ;		//接受抵押地址
		INT64  amount  ;				//金额
		int    actor  ;               // 0 发抵押 1 接受抵押 2 即使发抵押 又是接受抵押
		int    comfirmed      ;        // 是否已确认 00 没有确认 01 已确认
		int    state          ;         //0 发起状态 1 接抵押状态 2 确认状态 3 已经取消订单 4 正在接抵押 5 正在确认 6 正在取消订单
		char   relate_hash[64+1];          //接抵押hash 
	}DARK_RECORD;

	typedef std::vector<DARK_RECORD> DARKRECORDLIST ;
	typedef struct  {
		bool flag;                          // 00 抵押交易为接受 01抵押交易已经接受
		char 	buyer[6];						//!<买家ID（采用6字节的账户ID）
		char seller[6];       //!<卖家ID（采用6字节的账户ID）
		INT64 nPayMoney;
	}DARK_DATA_DB;

	typedef struct BLOCKCHANGED  {
		string  type ;
		int    tips ;
		INT64  high  ;
		string   hash;
		int connections;
		int time;
		int fuelrate;
		string ToJson(){
			Json::Value root;
			root["type"] = type;
			root["tips"] = tips;
			root["high"] = high;
			root["hash"] = hash;
			root["connections"] = connections;
			root["fuelrate"] = fuelrate;
			root["time"] = time;
			return root.toStyledString();
		}
	bool JsonToStruct(string json){
		Json::Reader reader;  
		Json::Value root; 
		if (!reader.parse(json, root)) 
			return false ;

		this->type = root["type"].asString();
		this->tips = root["tips"].asInt();
		this->high = root["high"].asInt64();
		this->hash = root["hash"].asString();
		this->connections = root["connections"].asInt();
		this->fuelrate = root["fuelrate"].asInt();
		if (json.find("time") >=0)
		{
			this->time =root["time"].asInt();
		}
		return true;
	}
	}BLOCKCHANGED_t;

	typedef struct DATABASEINFO  {
		string strSource ;
		string strWhere  ;
		string  strTabName  ;
		string  strcutjson ;
		string ToJson(){
			Json::Value root;
			root["strSource"] = strSource;
			root["strWhere"] = strWhere;
			root["strTabName"] = strTabName;
			root["strcutjson"] = strcutjson;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			int pos = json.find("strSource");
			if (pos >= 0)
			this->strSource = root["strSource"].asString();

			this->strWhere = root["strWhere"].asString();
			this->strTabName = root["strTabName"].asString();
			this->strcutjson = root["strcutjson"].asString();
			return true;
		}
	}DATABASEINFO_t;

	typedef struct LISTP2POOL{   
		string   hash ;   //address
		string   sendbetid ;   //RegID
		INT64   nPayMoney;
		int     outheight;
		string  acceptid;
		string  accepthash;
		int     guess;
		int     state;
		INT64   nAcceptMoney;
		int    award_rate;
		string ToJson(){
			Json::Value root;
			root["hash"] = hash;
			root["sendbetid"] = sendbetid;
			root["money"] = nPayMoney;
			root["height"] = outheight;
			root["acceptid"] = acceptid;
			root["accepthash"] = accepthash;
			root["guess"] = guess;
			root["state"] = state;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;

			this->hash = root["hash"].asString();
			this->sendbetid = root["sendbetid"].asString();
			this->nPayMoney = root["money"].asInt64();
			this->outheight=root["height"].asInt();
			this->acceptid = root["acceptid"].asString();
			this->accepthash  = root["accepthash"].asString();
			this->state = root["state"].asInt();
			this->guess = root["guess"].asInt();
			return true;
		}
	}LISTP2POOL_T;
	typedef std::vector<LISTP2POOL_T> P2PLIST ;

	typedef struct MINDLG{   
		string   money ;			//余额
		string   unconfirmmoney ;   //待确认金额
		string   itemcount;			//交易笔数
		string   addr1;				//最近转账交易1
		string   addr2;				//最近转账交易2
		string   addr3;				//最近转账交易3
		string   addr4;				//最近转账交易4
		string   addr5;				//最近转账交易5
		string   addr6;				//最近转账交易6
		MINDLG(){
			money = "" ;		   
			unconfirmmoney = "";
			itemcount = "";
			addr1 = "";
			addr2 = "";
			addr3 = "";
			addr4 = "";
			addr5 = "";
			addr6 = "";
		}
		string ToJson(){
			Json::Value root;
			root["money"] = money;
			root["unconfirmmoney"] = unconfirmmoney;
			root["itemcount"] = itemcount;
			root["addr1"] = addr1;
			root["addr2"] = addr2;
			root["addr3"] = addr3;
			root["addr4"] = addr4;
			root["addr5"] = addr5;
			root["addr6"] = addr6;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;

			this->money = root["money"].asString();
			this->unconfirmmoney = root["unconfirmmoney"].asString();
			this->itemcount = root["itemcount"].asString();
			this->addr1 = root["addr1"].asString();
			this->addr2 = root["addr2"].asString();
			this->addr3 = root["addr3"].asString();
			this->addr4 = root["addr4"].asString();
			this->addr5 = root["addr5"].asString();
			this->addr6 = root["addr6"].asString();
			return true;
		}
	}MINDLG_T;

	typedef struct ADDRBOOK{   
		string    label;   //address
		string    address  ;   //RegID
		ADDRBOOK(){
			label = _T("");
			address = _T("");
		}
		string ToJson(){
			Json::Value root;
			root["address"] = address;
			root["label"] = label;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			this->label = root["label"].asString();
			this->address = root["address"].asString();
			return true;
		}
	}ADDRBOOK_t;
	typedef std::vector<ADDRBOOK_t> ADDRBOOKLIST ;

	typedef struct REDPACKETSEND{   
		string    send_hash;   //address
		int        send_time;   //RegID
		double     amount  ;				//金额
		int        packet_num;
		string    send_acc_id;
		int        confirm_height;
		int        packet_type;       //1:普通红包  2:接龙红包
		REDPACKETSEND(){
			send_hash ="";   //address
			send_time = 0;;   //RegID
			amount = 0.0  ;				//金额
			packet_num = 0;
			send_acc_id = "";
			confirm_height = 0;
			packet_type = 0;  
		}
		string ToJson(){
			Json::Value root;
			root["send_hash"] = send_hash;
			root["send_time"] = send_time;
			root["amount"] = amount;
			root["packet_num"] = packet_num;
			root["send_acc_id"] = send_acc_id;
			root["confirm_height"] = confirm_height;
			root["packet_type"] = packet_type;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			this->send_hash = root["send_hash"].asString();
			this->send_time = root["send_time"].asInt();
			this->amount = root["amount"].asDouble();
			this->packet_num = root["packet_num"].asInt();
			this->send_acc_id = root["send_acc_id"].asString();
			this->confirm_height = root["confirm_height"].asInt();
			this->packet_type = root["packet_type"].asInt();
			return true;
		}
	}REDPACKETSEND_t;
	typedef std::vector<REDPACKETSEND_t> REDPACKETSENDLIST ;

	typedef struct REDPACKETGRAB{   
		string    send_hash;   //address
		string    grab_hash;
		int        grab_time;   //RegID
		double     lucky_amount  ;				//金额
		string    send_acc_id;
		string    grab_acct_id;
		int        confirm_height;
		int        packet_type;       //1:普通红包  2:接龙红包
		int        lucky_fortune;     /// 1 普通 2 运气王
		double     total_amount;
		int         total_num;
		REDPACKETGRAB(){
			send_hash ="";   //address
			grab_hash = "";
			grab_time = 0;;   //RegID
			lucky_amount = 0.0  ;				//金额
			send_acc_id = "";
			confirm_height = 0;
			packet_type = 0;  
			total_amount = 0.0;
			total_num = 0;
		}
		string ToJson(){
			Json::Value root;
			root["send_hash"] = send_hash;
			root["grab_hash"] = grab_hash;
			root["grab_time"] = grab_time;
			root["lucky_amount"] = lucky_amount;
			root["send_acc_id"] = send_acc_id;
			root["grab_acct_id"] = grab_acct_id;
			root["confirm_height"] = confirm_height;
			root["packet_type"] = packet_type;
			root["lucky_fortune"] = lucky_fortune;
			root["total_amount"] = total_amount;
			root["total_num"] = total_num;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			this->send_hash = root["label"].asString();
			this->grab_hash = root["grab_hash"].asString();
			this->grab_time = root["address"].asInt();
			this->lucky_amount = root["lucky_amount"].asDouble();
			this->send_acc_id = root["send_acc_id"].asString();
			this->grab_acct_id = root["grab_acct_id"].asString();
			this->confirm_height = root["confirm_height"].asInt();
			this->packet_type = root["packet_type"].asInt();
			this->lucky_fortune = root["lucky_fortune"].asInt();
			this->total_amount = root["total_amount"].asDouble();
			this->total_num = root["total_amount"].asInt();
			return true;
		}
	}REDPACKETGRAB_t;
	typedef std::vector<REDPACKETGRAB_t> REDPACKETGRABLIST ;

	typedef struct REDPACKETPOOL{   
		string    send_hash;   //address
		double     total_amount  ;				//金额
		string    send_acc_id;
		int        packets_num;
		int        packet_type;       //1:普通红包  2:接龙红包
		string    message;
		double     average_amout;
		REDPACKETPOOL(){
			send_hash ="";   //address
			total_amount = 0.0  ;				//金额
			send_acc_id = "";
			packet_type = 0;  
			average_amout =0.0;
		}
		string ToJson(){
			Json::Value root;
			root["send_hash"] = send_hash;
			root["total_amount"] = total_amount;
			root["send_acc_id"] = send_acc_id;
			root["packets_num"] = packets_num;
			root["packet_type"] = packet_type;
			root["message"] = message;
			root["average_amout"] = average_amout;
			return root.toStyledString();
		}
		bool JsonToStruct(string json){
			Json::Reader reader;  
			Json::Value root; 
			if (!reader.parse(json, root)) 
				return false ;
			this->send_hash = root["label"].asString();
			this->total_amount = root["address"].asDouble();
			this->send_acc_id = root["send_acc_id"].asString();
			this->packets_num = root["packets_num"].asInt();
			this->packet_type = root["packet_type"].asInt();
			this->message = root["message"].asString();
			this->average_amout = root["average_amout"].asDouble();
			return true;
		}
	}REDPACKETPOOL_t;
	typedef std::vector<REDPACKETPOOL_t> REDPACKETPOOLLIST ;

	typedef struct CHAIN_TIP{
		string blockhash;         //block hash
		int block_height;        //确认高度
		int confired_time;      // 确认时间
		int fuelrate;
		int lock;
	}CHAIN_TIP_T;

	typedef struct {
		char          sendRedid[6] ;        //// 发起钱包的id
		INT64         amount;                     //发起钱包的金额
		short           number;                       /// 发起钱包的个数
		char          type;                        /// 红包类型
		int          timeout;                       //红包超时时间
		bool          fover;                        // 表示是否抢完
		unsigned char message[200];                 //广告语
		short           takennum;                       // 表示第几个红包
	}RED_PACKETDB;

	typedef struct {
		char regid[6];
		INT64 amount;
	}USER_INFO;

	#define MAX_COUNT       100
	typedef struct {
		RED_PACKETDB dbdata;
		USER_INFO userinfo[MAX_COUNT];
	}RED_DATA;
	typedef std::vector<RED_DATA> RED_DATALIST ;
}



typedef struct CONFIG_APP{
	string   appname;  
	string   appnameen; 
	string     appid;         
	CONFIG_APP(){
		appname ="";   //address
		appid ="";
	}
}CONFIG_APP_DATA;

#pragma pack(pop)
//UiFun
namespace UiFun 
{
	UINT    MallocP( void * * p , UINT size );
	void    ReleaseP( void * p ) ;
	CString Rnd32() ;
	time_t  SystemTimeToTimet(const SYSTEMTIME& st) ;
	SYSTEMTIME Time_tToSystemTime(time_t t);
	int     RandNumber();   //生成一个1-6的随机数
	int    MessageBoxEx(CString strText , CString strCaption , UINT uType); //自定义MessageBox对话框
	CString UI_LoadString( CString secID , CString szID , UINT language ) ;  //根据字符串ID加载字符串

	HBITMAP GlobalBkgndBMP(UINT nIDBitmap);

	CString MbcsToUtf8(const char *file) ;


	std::string& trimleft(std::string &s) ;

	std::string& trimright(std::string &s) ;
	
	bool IsCurrentAppId(string Curappid,string useAppid,string strShow);
	void  GetCellName(int nRow, int nCol, CString &strName);
	int   GetBmpId(int bmpCn,int bmpEn,int language);
	void  WriteClosConfig(bool tips,string path);
	void Setlanguage(int index);
}
#endif