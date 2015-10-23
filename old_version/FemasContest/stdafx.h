
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
#include <string.h>
#include <map>
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif
#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include "FemasContest.h"
#include "FemasContestDlg.h"
#include "LoginDialog.h"
#include "InsertLimitPage.h"
#include "InsertMarketPage.h"
#include "PageOrderInfo.h"
#include "PagePositionInfo.h"
#include "PageTradeInfo.h"
#include "ChartDlg.h"
#include "ConsoleDialog.h"
#include "ContractsSubcribeDlg.h"
#include "ContractsDialog.h"
#include "minuteMarketData.h"
#include "lastMarketData.h"
#include "TradeExcecutor.h"
#include "StrategyManager.h"
#include "TradeStrategy.h"

#include "TraderHandler.h"
#include "MdUserHandler.h"

//���б���
static int g_nOrLocalID = 0; //var
extern CUstpFtdcTraderApi *traderUserApi;
extern CUstpFtdcMduserApi *mdUserApi;
extern MdUserHandler mdSpi;
extern UstpTraderHandler tdSpi;

extern bool g_Connection; //status
extern TUstpFtdcDateType g_TradingDay; //status
extern TUstpFtdcUserIDType g_UserID; //user
extern TUstpFtdcBrokerIDType g_BrokerID; //user
extern TUstpFtdcExchangeIDType g_ExchangeID; //user
extern TUstpFtdcPasswordType g_Password; //user
extern TUstpFtdcProductInfoType g_ProductInfo; //user
extern char *mdFrontAddress; //setting
extern char *tdFrontAddress;//setting
extern CLoginDialog dlg;
extern CFemasContestDlg mainDlg;
extern ConsoleDialog consoleDlg;
extern ContractsDialog contractsDlg;
extern ChartDlg chartDlg;
extern TUstpFtdcInvestorIDType g_InvestorID; //user
extern CUstpFtdcDepthMarketDataField g_InstrumentStatus[1000];
extern CUstpFtdcRspInstrumentField g_InstrumentsInfo[1000];
extern bool isOrdered[1000];
extern int g_InstrumentCount;
extern int g_OrderedInstrumentCount;
extern minuteMarketData *pMinuteMarketData[60];
extern lastMarketData *pLastMarketData[60];
extern CUstpFtdcOrderField g_Orders[10000];
extern CUstpFtdcTradeField g_Trades[10000];
extern CUstpFtdcRspInvestorPositionField g_Positions[1000];
extern int g_OrderCount;
extern int g_TradeCount;
extern int g_PositionCount;
extern int g_OrderLocalId; //status

extern InsertLimitPage pageInsertLimitOrder;
extern InsertMarketPage pageInsertMarketOrder;
extern PageOrderInfo pageOrderInfo;
extern PagePositionInfo pagePositionInfo;
extern PageTradeInfo pageTradeInfo;
extern CDialog* pageTabOrder[2];
extern CDialog* pageTabInfo[3];
extern int pageTabOrderIndex;
extern int pageTabInfoIndex;
//���з���

//����
CString doubleToStr(double n);
CString intToStr(int n);
CString intToUnitedStr(int n);
void printLog(char *);
//ͨ��mdUserSpi�ص���Ӻ�Լ��Ϣ
void addInstrument(CUstpFtdcRspInstrumentField pRspInstrument);
//ˢ���˻���Ϣ
void refreshInvestorAccountInfo();
//�ص��������ý�������
void setAccountInfo(CUstpFtdcRspInvestorAccountField *s);
//�����б�ؼ��е���Ϣ
void setListContract(CUstpFtdcDepthMarketDataField * pDepthMarketData);
//������ʷ���ݣ��������ã�
void saveContractHistory(CUstpFtdcDepthMarketDataField * pDepthMarketData);
//������ж�����Ϣ
void clearSubcribedContracts();
//���¿�������
void reSubcribeContracts();
//�����޼۱��۵�
void insertLimitOrder(CUstpFtdcInputOrderField *pInputOrder, int type, int count);
//�����г����۵�
void insertMarketOrder(CUstpFtdcInputOrderField *pInputOrder, int type);

void addPositionRecord(CUstpFtdcRspInvestorPositionField *s);
void addOrderRecord(CUstpFtdcOrderField *s);
void addTradeRecord(CUstpFtdcTradeField *s);
void refreshOrderInfo();
void refreshTradeInfo();
void refreshPositionInfo();
void reqOrderAction(TUstpFtdcOrderSysIDType s);