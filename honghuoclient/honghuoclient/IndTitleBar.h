#pragma once
#include "MainDlg.h"
#include "Send.h"
#include "Rece.h"
#include "Deal.h"
#include "Ipo.h"
#include "Set.h"

// CIndTitleBar 对话框

class CIndTitleBar : public CDialogBar
{
	DECLARE_DYNAMIC(CIndTitleBar)

public:
	CIndTitleBar();   // 标准构造函数
	virtual ~CIndTitleBar();

// 对话框数据
	enum { IDD = IDD_DIALOGBAR_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HBITMAP		     m_pBmp; 
public:
	CRoundButton     m_rBtnMain;
	CRoundButton     m_rBtnSend;
	CRoundButton     m_rBtnRece;
	CRoundButton     m_rBtnDeal;
	CRoundButton     m_rBtnApp;
	CRoundButton     m_rBtnSet;
	CRoundButton     m_rBtnClose;
	CRoundButton     m_rBtnMin;
public:
	UINT             m_nButtonID                   ; //当前点击的button
	void             MobileTip(UINT nButtonID , BOOL bFlag );
public:
	afx_msg LRESULT OnShowStateTip(  WPARAM wParam	, LPARAM lParam ) ;
public:
	void		  SetBkBmpNid( UINT nBitmapIn ) ;
	afx_msg BOOL  OnEraseBkgnd(CDC* pDC);
	afx_msg int   OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void  OnSize(UINT nType, int cx, int cy);
	virtual BOOL  Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	//afx_msg void OnBnClickedButtonMin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
