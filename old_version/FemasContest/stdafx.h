
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#include <string.h>
#include <map>
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif
#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持



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

//公有变量
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
//共有方法

//工具
CString doubleToStr(double n);
CString intToStr(int n);
CString intToUnitedStr(int n);
void printLog(char *);
//通过mdUserSpi回调添加合约信息
void addInstrument(CUstpFtdcRspInstrumentField pRspInstrument);
//刷新账户信息
void refreshInvestorAccountInfo();
//回调调用设置界面内容
void setAccountInfo(CUstpFtdcRspInvestorAccountField *s);
//设置列表控件中的信息
void setListContract(CUstpFtdcDepthMarketDataField * pDepthMarketData);
//保存历史数据（暂无作用）
void saveContractHistory(CUstpFtdcDepthMarketDataField * pDepthMarketData);
//清空所有订阅信息
void clearSubcribedContracts();
//重新开启订阅
void reSubcribeContracts();
//插入限价报价单
void insertLimitOrder(CUstpFtdcInputOrderField *pInputOrder, int type, int count);
//插入市场报价单
void insertMarketOrder(CUstpFtdcInputOrderField *pInputOrder, int type);

void addPositionRecord(CUstpFtdcRspInvestorPositionField *s);
void addOrderRecord(CUstpFtdcOrderField *s);
void addTradeRecord(CUstpFtdcTradeField *s);
void refreshOrderInfo();
void refreshTradeInfo();
void refreshPositionInfo();
void reqOrderAction(TUstpFtdcOrderSysIDType s);