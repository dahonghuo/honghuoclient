#pragma once


// CMainDlg �Ի���

class CMainDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg();   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	HBITMAP		     m_pBmp; 
	CStaticTrans     m_strBalance;			//���
	CStaticTrans     m_strConfirming;		//����ȷ��
	CStaticTrans     m_strTransactionNumber; //���ױ���

	CStaticTrans     m_strSrcAddr1;       //�������1Դ��ַ   
	CStaticTrans     m_strSrcAddr2;       //�������2Դ��ַ
	CStaticTrans     m_strSrcAddr3;       //�������3Դ��ַ
	CStaticTrans     m_strSrcAddr4;       //�������4Դ��ַ
	CStaticTrans     m_strSrcAddr5;       //�������5Դ��ַ
	CStaticTrans     m_strSrcAddr6;       //�������6Դ��ַ

	CStaticTrans     m_strAmount1;        //�������1ת�˽��   
	CStaticTrans     m_strAmount2;        //�������2ת�˽��
	CStaticTrans     m_strAmount3;        //�������3ת�˽��
	CStaticTrans     m_strAmount4;        //�������4ת�˽��
	CStaticTrans     m_strAmount5;        //�������5ת�˽��
	CStaticTrans     m_strAmount6;        //�������6ת�˽��

	CStaticTrans     m_strDesAddr1;       //�������1Ŀ�ĵ�ַ    
	CStaticTrans     m_strDesAddr2;       //�������2Ŀ�ĵ�ַ    
	CStaticTrans     m_strDesAddr3;       //�������3Ŀ�ĵ�ַ    
	CStaticTrans     m_strDesAddr4;       //�������4Ŀ�ĵ�ַ    
	CStaticTrans     m_strDesAddr5;       //�������5Ŀ�ĵ�ַ    
	CStaticTrans     m_strDesAddr6;       //�������6Ŀ�ĵ�ַ  

	CMFCLinkCtrl    *m_vlinkCtrl1;         //������̬������1
	CMFCLinkCtrl    *m_vlinkCtrl2;         //������̬������2
	CMFCLinkCtrl    *m_vlinkCtrl3;         //������̬������3
	CMFCLinkCtrl    *m_vlinkCtrl4;		   //������̬������4
	CMFCLinkCtrl    *m_vlinkCtrlQQ;        //�ٷ��ͷ�QQ������
	CMFCLinkCtrl    *m_vlinkCtrlBlock;     //�ٷ����������

	CRoundButton     m_rBtnTxdetail;    //ȫ���������鰴ť

	map<CString, CString> m_mapUrl;     //������̬URL����

	//CStatic          m_stWalletSync;    //Ǯ����δͬ����־

public:
	void  SetBkBmpNid( UINT nBitmapIn );
	void  ClearCtrlText();				//������пؼ�����
	void  InitializeLinkCtrl();			//��ʼ�����ӿؼ�
	bool  GetUrlServer();
	void  OnBnClickedTxDetail();         //��Ӧ����鿴ȫ���������鰴ť
	LRESULT OnShowListCtrl(WPARAM wParam, LPARAM lParam);  //���������ҳ�ռ�ؼ����ݵ���Ϣ
	void SetCtrlText();                  //�������ø��ؼ�������
	void OnInitialCtrlText();            //��ʼ�����пؼ�����

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
