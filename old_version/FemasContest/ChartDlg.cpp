// ChartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "ChartDlg.h"
#include "afxdialogex.h"


// ChartDlg 对话框

IMPLEMENT_DYNAMIC(ChartDlg, CDialogEx)

ChartDlg::ChartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHART_DLG, pParent)
{

	focusedOrderedInstrumentID = -1;
	chartType = 0;
	curPrice = 0.0;
	curAvgPrice = 0.0;
	curPos = 0;
	focusedInstrumentID = -1;
	beginTime = 0;
	endTime = 0;
	candleCount = 100;
}

ChartDlg::~ChartDlg()
{
}

void ChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChartDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// ChartDlg 消息处理程序


void ChartDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	Invalidate();
	paint();
}


void ChartDlg::paint()
{
	CPaintDC dc(this);
	CRect mainRec;
	GetClientRect(mainRec);
	//背景
	CPen backPen;
	backPen.CreatePen(PS_SOLID, 1, COLOR_BG);
	CBrush backBrush(COLOR_BG);
	dc.SelectObject(&backPen);
	dc.SelectObject(&backBrush);
	Rectangle(dc, mainRec.left, mainRec.top, mainRec.right, mainRec.bottom);
	//框架
	CPen framePen;
	framePen.CreatePen(PS_SOLID, 1, COLOR_FRAME);
	dc.SelectObject(&framePen);
	dc.MoveTo(mainRec.right - FRAME_INFO_WIDTH, 0);
	dc.LineTo(mainRec.right - FRAME_INFO_WIDTH, mainRec.bottom);
	dc.MoveTo(mainRec.right - FRAME_INFO_WIDTH, HEIGHT_H1 - 5);
	dc.LineTo(mainRec.right, HEIGHT_H1 - 5);
	CFont titleFont;
	titleFont.CreatePointFont(160, _T("宋体"));
	dc.SelectObject(&titleFont);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 255, 255));
	CString s;
	s.Format("%s %s", g_InstrumentsInfo[focusedInstrumentID].InstrumentName, g_InstrumentsInfo[focusedInstrumentID].InstrumentID);
	dc.DrawText(s, CRect(mainRec.right - FRAME_INFO_WIDTH, 0, mainRec.right, HEIGHT_H1), DT_VCENTER|DT_CENTER);

	paintInstrumentStatus(&dc);
	if (!chartType)
		paintTimeLineChart(&dc);
	else
		paintCandleLineChart(&dc);
}


void ChartDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	Invalidate();
	paint();
	// TODO: 在此处添加消息处理程序代码
}


void ChartDlg::paintInstrumentStatus(CPaintDC *dc)
{
	CString cs;
	CRect statusFieldRec;
	GetClientRect(statusFieldRec);
	statusFieldRec.left = statusFieldRec.right - FRAME_INFO_WIDTH;
	statusFieldRec.top = HEIGHT_H1;
	int midSide = (statusFieldRec.left + statusFieldRec.right) / 2;
	CPen framePen;
	framePen.CreatePen(PS_SOLID, 1, RGB(240, 0, 0));
	dc->SelectObject(&framePen);
	CFont statusFont;
	statusFont.CreatePointFont(FONT_SIZE_H2, "宋体");
	dc->SelectObject(&statusFont);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(COLOR_WHITE);
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top, "卖一");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2, "买一");
	dc->MoveTo(statusFieldRec.left, statusFieldRec.top + HEIGHT_H2 * 2 - 5);
	dc->LineTo(statusFieldRec.right, statusFieldRec.top + HEIGHT_H2 * 2 - 5);
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 2, "现价");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 2, "开盘");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 3, "涨跌");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 3, "昨收");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 4, "涨跌幅");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 4, "最高");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 5, "振幅");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 5, "最低");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 6, "总手");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 6, "成交金额");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 7, "均价");
	dc->MoveTo(statusFieldRec.left, statusFieldRec.top + HEIGHT_H2 * 8 - 5);
	dc->LineTo(statusFieldRec.right, statusFieldRec.top + HEIGHT_H2 * 8 - 5);
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 8, "持仓");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 8, "昨持仓");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 9, "日增仓");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 9, "昨结");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 10, "涨停板");
	dc->TextOutA(midSide, statusFieldRec.top + HEIGHT_H2 * 10, "跌停板");
	dc->TextOutA(statusFieldRec.left + 5, statusFieldRec.top + HEIGHT_H2 * 11, "交割月");
	CRect infoOut = statusFieldRec;
	infoOut.right = midSide - 5;

	if (focusedInstrumentID == -1)
		return;
	
	double preSettle = g_InstrumentStatus[focusedInstrumentID].PreSettlementPrice;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].BidPrice1, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].BidPrice1), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].AskPrice1, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].AskPrice1), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].LastPrice, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].LastPrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].LastPrice - g_InstrumentStatus[focusedInstrumentID].PreSettlementPrice), infoOut, DT_RIGHT);//涨跌
	infoOut.top += HEIGHT_H2;
	cs.Format("%.2lf%%", g_InstrumentStatus[focusedInstrumentID].LastPrice / preSettle * 100 - 100);
	dc->DrawText(cs, infoOut, DT_RIGHT);//涨跌幅
	infoOut.top += HEIGHT_H2;
	cs.Format("%.2lf%%", g_InstrumentStatus[focusedInstrumentID].HighestPrice / g_InstrumentStatus[focusedInstrumentID].LowestPrice * 100 - 100);
	dc->SetTextColor(COLOR_PRIMARY);
	dc->DrawText(cs, infoOut, DT_RIGHT);//振幅
	infoOut.top += HEIGHT_H2;
	dc->DrawText(intToStr(g_InstrumentStatus[focusedInstrumentID].Volume), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(pMinuteMarketData[focusedOrderedInstrumentID]->avgPrice, preSettle));
	dc->DrawText(doubleToStr(pMinuteMarketData[focusedOrderedInstrumentID]->avgPrice), infoOut, DT_RIGHT);//均价
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_PRIMARY);
	dc->DrawText(intToStr(g_InstrumentStatus[focusedInstrumentID].OpenInterest), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->DrawText(intToStr(g_InstrumentStatus[focusedInstrumentID].OpenInterest - g_InstrumentStatus[focusedInstrumentID].PreOpenInterest), infoOut, DT_RIGHT);//日增仓
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RED);
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].UpperLimitPrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	cs.Format("%d-%d", g_InstrumentsInfo[focusedInstrumentID].DeliveryYear, g_InstrumentsInfo[focusedInstrumentID].DeliveryMonth);
	dc->DrawText(cs, infoOut, DT_RIGHT);//交割月
	infoOut.top = statusFieldRec.top;
	infoOut.right = statusFieldRec.right - 5;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].BidPrice1, preSettle));
	dc->DrawText(intToStr(g_InstrumentStatus[focusedInstrumentID].BidVolume1), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].AskPrice1, preSettle));
	dc->DrawText(intToStr(g_InstrumentStatus[focusedInstrumentID].AskVolume1), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].OpenPrice, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].OpenPrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].PreClosePrice, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].PreClosePrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].HighestPrice, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].HighestPrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_RG(g_InstrumentStatus[focusedInstrumentID].LowestPrice, preSettle));
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].LowestPrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_PRIMARY);
	dc->DrawText(intToUnitedStr(g_InstrumentStatus[focusedInstrumentID].Turnover), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	infoOut.top += HEIGHT_H2;
	dc->DrawText(intToStr(g_InstrumentStatus[focusedInstrumentID].PreOpenInterest), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_WHITE);
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].PreSettlementPrice), infoOut, DT_RIGHT);
	infoOut.top += HEIGHT_H2;
	dc->SetTextColor(COLOR_GREEN);
	dc->DrawText(doubleToStr(g_InstrumentStatus[focusedInstrumentID].LowerLimitPrice), infoOut, DT_RIGHT);
}


void ChartDlg::paintTimeLineChart(CPaintDC *dc)
{
	if (focusedInstrumentID == -1)
		return;
	double preSettle = g_InstrumentStatus[focusedInstrumentID].PreSettlementPrice;
	double unitPrice = pMinuteMarketData[focusedOrderedInstrumentID]->maxChg / 7;
	double unitChg = unitPrice / preSettle * 100;
	int maxVolume = pMinuteMarketData[focusedOrderedInstrumentID]->maxVolume * 3 / 2 + 10;
	int maxPosition = pMinuteMarketData[focusedOrderedInstrumentID]->maxPosition, minPosition = pMinuteMarketData[focusedOrderedInstrumentID]->minPosition;
	//frame
	CString cs;
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	Rectangle(*dc, chart.left + WIDTH_H4, chart.top, chart.right - WIDTH_H4, chart.bottom - HEIGHT_H4);
	CFont h4;
	h4.CreatePointFont(FONT_SIZE_H4, "宋体");
	dc->SelectObject(&h4);
	cs.Format("%s  成交价：%.1lf  均价：%.1lf", g_InstrumentsInfo[focusedInstrumentID].InstrumentName, curPrice, curAvgPrice);
	dc->TextOutA(chart.left + WIDTH_H4 + 3, chart.top + 2, cs);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	CRect tmp2 = tmp;
	tmp2.top = tmp.bottom + HEIGHT_H4;
	tmp2.bottom = chart.bottom - HEIGHT_H4;
	//horizental line
	drawLine(dc, tmp.left, tmp.top, tmp.right, tmp.top);
	drawLine(dc, tmp.left, tmp.bottom, tmp.right, tmp.bottom);
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 1, 13), tmp.right, getPosition(tmp.top, tmp.bottom, 1, 13));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 1, 6), tmp.right, getPosition(tmp.top, tmp.bottom, 1, 6));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 3, 11), tmp.right, getPosition(tmp.top, tmp.bottom, 3, 11));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 2, 5), tmp.right, getPosition(tmp.top, tmp.bottom, 2, 5));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 5, 9), tmp.right, getPosition(tmp.top, tmp.bottom, 5, 9));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 3, 4), tmp.right, getPosition(tmp.top, tmp.bottom, 3, 4));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 4, 3), tmp.right, getPosition(tmp.top, tmp.bottom, 4, 3));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 9, 5), tmp.right, getPosition(tmp.top, tmp.bottom, 9, 5));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 5, 2), tmp.right, getPosition(tmp.top, tmp.bottom, 5, 2));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 11, 3), tmp.right, getPosition(tmp.top, tmp.bottom, 11, 3));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 6, 1), tmp.right, getPosition(tmp.top, tmp.bottom, 6, 1));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 13, 1), tmp.right, getPosition(tmp.top, tmp.bottom, 13, 1));
	drawLine(dc, tmp2.left, tmp2.top, tmp2.right, tmp2.top);
	drawLine(dc, tmp2.left, getPosition(tmp2.top, tmp2.bottom, 2, 1), tmp2.right, getPosition(tmp2.top, tmp2.bottom, 2, 1));
	drawLine(dc, tmp2.left, getPosition(tmp2.top, tmp2.bottom, 1, 2), tmp2.right, getPosition(tmp2.top, tmp2.bottom, 1, 2));
	//vertical line
	drawLine(dc, getPosition(tmp.left, tmp.right, 1, 17), tmp.top, getPosition(tmp.left, tmp.right, 1, 17), tmp.bottom);
	drawLine(dc, getPosition(tmp.left, tmp.right, 17, 1), tmp.top, getPosition(tmp.left, tmp.right, 17, 1), tmp.bottom);
	drawLine(dc, getPosition(tmp.left, tmp.right, 5, 13), tmp.top, getPosition(tmp.left, tmp.right, 5, 13), tmp.bottom);
	drawLine(dc, getPosition(tmp.left, tmp.right, 13, 5), tmp.top, getPosition(tmp.left, tmp.right, 13, 5), tmp.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 1, 17), tmp2.top, getPosition(tmp2.left, tmp2.right, 1, 17), tmp2.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 17, 1), tmp2.top, getPosition(tmp2.left, tmp2.right, 17, 1), tmp2.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 5, 13), tmp2.top, getPosition(tmp2.left, tmp2.right, 5, 13), tmp2.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 13, 5), tmp2.top, getPosition(tmp2.left, tmp2.right, 13, 5), tmp2.bottom);
	CPen pen;
	CPen *pOldPen;
	pen.CreatePen(PS_DOT, 1, COLOR_FRAME);
	pOldPen = dc->SelectObject(&pen);
	drawLine(dc, getPosition(tmp.left, tmp.right, 1, 5), tmp.top, getPosition(tmp.left, tmp.right, 1, 5), tmp.bottom);
	drawLine(dc, getPosition(tmp.left, tmp.right, 5, 1), tmp.top, getPosition(tmp.left, tmp.right, 5, 1), tmp.bottom);
	drawLine(dc, getPosition(tmp.left, tmp.right, 7, 11), tmp.top, getPosition(tmp.left, tmp.right, 7, 11), tmp.bottom);
	drawLine(dc, getPosition(tmp.left, tmp.right, 11, 7), tmp.top, getPosition(tmp.left, tmp.right, 11, 7), tmp.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 1, 5), tmp2.top, getPosition(tmp2.left, tmp2.right, 1, 5), tmp2.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 5, 1), tmp2.top, getPosition(tmp2.left, tmp2.right, 5, 1), tmp2.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 7, 11), tmp2.top, getPosition(tmp2.left, tmp2.right, 7, 11), tmp2.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 11, 7), tmp2.top, getPosition(tmp2.left, tmp2.right, 11, 7), tmp2.bottom);
	dc->SelectObject(pOldPen);
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 3, COLOR_FRAME);
	pOldPen = dc->SelectObject(&pen);
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 1, 1), tmp.right, getPosition(tmp.top, tmp.bottom, 1, 1));
	drawLine(dc, getPosition(tmp.left, tmp.right, 1, 1), tmp.top, getPosition(tmp.left, tmp.right, 1, 1), tmp.bottom);
	drawLine(dc, getPosition(tmp2.left, tmp2.right, 1, 1), tmp2.top, getPosition(tmp2.left, tmp2.right, 1, 1), tmp2.bottom);
	dc->SelectObject(pOldPen);
	pen.DeleteObject();
	dc->SetTextColor(COLOR_FRAME);
	dc->TextOutA(tmp2.left, tmp2.bottom, "9:15");
	dc->TextOutA(getPosition(tmp2.left, tmp2.right, 1, 17), tmp2.bottom, "9:30");
	dc->TextOutA(getPosition(tmp2.left, tmp2.right, 5, 13), tmp2.bottom, "10:30");
	dc->TextOutA(getPosition(tmp2.left, tmp2.right, 1, 1), tmp2.bottom, "11:30");
	dc->TextOutA(getPosition(tmp2.left, tmp2.right, 13, 5), tmp2.bottom, "14:00");
	dc->TextOutA(getPosition(tmp2.left, tmp2.right, 17, 1), tmp2.bottom, "15:00");
	
	dc->SetTextColor(COLOR_WHITE);
	setMouseText(dc);
	CRect sideValue;
	sideValue.SetRect(0, getPosition(tmp.top, tmp.bottom, 1, 1) - 7, tmp.left - 3, chart.bottom);
	dc->DrawText(doubleToStr(preSettle), sideValue, DT_RIGHT);
	dc->TextOutA(tmp.right + 3, getPosition(tmp.top, tmp.bottom, 1, 1) - 7, "0.00%");
	dc->SetTextColor(COLOR_RED);
	for (int i = 1; i <= 7; i++)
	{
		sideValue.top = getPosition(tmp.top, tmp.bottom, 7 - i, 7 + i) - 6;
		dc->DrawText(doubleToStr(preSettle + unitPrice * i), sideValue, DT_RIGHT);
		cs.Format("%.2lf%%", unitChg * i);
		dc->TextOutA(tmp.right + 3, sideValue.top, cs);
	}
	sideValue.top = tmp2.top - 6;
	dc->DrawText(intToStr(maxPosition), sideValue, DT_RIGHT);
	dc->TextOutA(tmp2.right + 3, sideValue.top, intToStr(maxVolume));
	sideValue.top = getPosition(tmp2.top, tmp2.bottom, 1, 2) - 6;
	dc->DrawText(intToStr(getPosition(maxPosition, minPosition, 1, 2)), sideValue, DT_RIGHT);
	cs.Format("%d", maxVolume * 2 / 3);
	dc->TextOutA(tmp2.right + 3, sideValue.top, cs);
	sideValue.top = getPosition(tmp2.top, tmp2.bottom, 2, 1) - 6;
	dc->DrawText(intToStr(getPosition(maxPosition, minPosition, 2, 1)), sideValue, DT_RIGHT);
	cs.Format("%d", maxVolume / 3);
	dc->TextOutA(tmp2.right + 3, sideValue.top, cs);
	dc->SetTextColor(COLOR_GREEN);
	for (int i = 1; i <= 7; i++)
	{
		sideValue.top = getPosition(tmp.top, tmp.bottom, 7 + i, 7 - i) - 7;
		dc->DrawText(doubleToStr(preSettle - unitPrice * i), sideValue, DT_RIGHT);
		cs.Format("%.2lf%%", unitChg * i);
		dc->TextOutA(tmp.right + 3, sideValue.top, cs);
	}

	//drawline
	minuteMarketData & mmd = *pMinuteMarketData[focusedOrderedInstrumentID];
	//avg price line
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 1, COLOR_YELLOW);
	dc->SelectObject(&pen);
	for (int i = 0; i < mmd.lastIndex; i++)
	{
		drawLine(dc,
			converTimeToPixel(i),
			convertPriceToPixel(tmp.bottom, tmp.top, preSettle - mmd.maxChg, preSettle + mmd.maxChg, mmd[i].avgPrice),
			converTimeToPixel(i + 1),
			convertPriceToPixel(tmp.bottom, tmp.top, preSettle - mmd.maxChg, preSettle + mmd.maxChg, mmd[i + 1].avgPrice)
			);
	}
	//time line
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 1, COLOR_WHITE);
	pOldPen = dc->SelectObject(&pen);
	for (int i = 0; i <= mmd.lastIndex; i++)
	{
		drawLine(dc,
			converTimeToPixel(i),
			convertPriceToPixel(tmp.bottom, tmp.top, preSettle - mmd.maxChg, preSettle + mmd.maxChg, mmd[i].firstPrice),
			converTimeToPixel(i + 1),
			convertPriceToPixel(tmp.bottom, tmp.top, preSettle - mmd.maxChg, preSettle + mmd.maxChg, mmd[i].lastPrice)
			);
	}
	//position line
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 1, COLOR_PINK);
	dc->SelectObject(&pen);
	for (int i = 0; i < mmd.lastIndex; i++)
	{
		drawLine(dc,
			converTimeToPixel(i),
			convertPriceToPixel(tmp2.bottom, tmp2.top, minPosition, maxPosition, mmd[i].position),
			converTimeToPixel(i + 1),
			convertPriceToPixel(tmp2.bottom, tmp2.top, minPosition, maxPosition, mmd[i + 1].position)
			);
	}
	//volume chart
	CPen pr, pg;
	pr.CreatePen(PS_SOLID, 2, COLOR_RED);
	pg.CreatePen(PS_SOLID, 2, COLOR_GREEN);
	for (int i = 0; i <= mmd.lastIndex; i++)
	{
		int volume = mmd[i].lastVolume - mmd[i].firstVolume;
		if (volume == 0)
			continue;
		int tmpx = converTimeToPixel(i) + 2;
		dc->SelectObject((mmd[i].firstPrice < mmd[i].lastPrice) ? (&pr) : (&pg));
		drawLine(dc,
			tmpx,
			tmp2.bottom - 1,
			tmpx,
			convertPriceToPixel(tmp2.bottom, tmp2.top, 0.0, maxVolume, volume)
			);
	}
}


int ChartDlg::paintCandleLineChart(CPaintDC *dc)
{
	/*
	minuteMarketData mmd;
	mmd.lastIndex = 2;
	mmd.maxVolume = 500;
	mmd[0].firstPrice = 2993;
	mmd[0].lastPrice = 2993;
	mmd[0].firstVolume = 1999;
	mmd[0].lastVolume = 2333;
	mmd[0].highestPrice = 3320;
	mmd[0].lowestPrice = 1500;
	mmd[1].firstPrice = 2000;
	mmd[1].lastPrice = 2600;
	mmd[1].firstVolume = 2333;
	mmd[1].lastVolume = 2400;
	mmd[1].highestPrice = 2800;
	mmd[1].lowestPrice = 1800;
	mmd[2].firstPrice = 2600;
	mmd[2].lastPrice = 1700;
	mmd[2].firstVolume = 2400;
	mmd[2].lastVolume = 2800;
	mmd[2].highestPrice = 2600;
	mmd[2].lowestPrice = 1600;
	*/
	minuteMarketData &mmd = *pMinuteMarketData[focusedOrderedInstrumentID];
	int lastTime = mmd.lastIndex;
	int maxVolume = mmd.maxVolume * 3 / 2 + 10;
	endTime = max(lastTime + 1, candleCount);
	beginTime = (lastTime >= candleCount) ? (lastTime - candleCount) : 0;
	double maxPrice = mmd[beginTime].highestPrice;
	double minPrice = mmd[beginTime].lowestPrice;
	for (int i = beginTime; i <= lastTime; i++)
	{
		maxPrice = max(maxPrice, mmd[i].highestPrice);
		minPrice = min(minPrice, mmd[i].lowestPrice);
	}
	if (maxPrice == minPrice)
	{
		maxPrice += 200;
		minPrice -= 200;
	}
	//frame
	CString cs;
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	Rectangle(*dc, chart.left + WIDTH_H4, chart.top, chart.right - WIDTH_H4, chart.bottom - HEIGHT_H4);
	CFont h4;
	h4.CreatePointFont(FONT_SIZE_H4, "宋体");
	dc->SelectObject(&h4);
	cs.Format("%s  成交价：%.1lf  均价：%.1lf", g_InstrumentsInfo[focusedInstrumentID].InstrumentName, curPrice, curAvgPrice);
	dc->TextOutA(chart.left + WIDTH_H4 + 3, chart.top + 2, cs);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	CRect tmp2 = tmp;
	tmp2.top = tmp.bottom + HEIGHT_H4;
	tmp2.bottom = chart.bottom - HEIGHT_H4;
	drawLine(dc, tmp.left, tmp.top, tmp.right, tmp.top);
	drawLine(dc, tmp.left, tmp.bottom, tmp.right, tmp.bottom);
	drawLine(dc, tmp2.left, tmp2.top, tmp2.right, tmp2.top);
	CPen pen;
	pen.CreatePen(PS_DOT, 1, COLOR_FRAME);
	dc->SelectObject(&pen);
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 1, 1), tmp.right, getPosition(tmp.top, tmp.bottom, 1, 1));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 3, 1), tmp.right, getPosition(tmp.top, tmp.bottom, 3, 1));
	drawLine(dc, tmp.left, getPosition(tmp.top, tmp.bottom, 1, 3), tmp.right, getPosition(tmp.top, tmp.bottom, 1, 3));
	//sideText
	dc->SetTextColor(COLOR_WHITE);
	CRect sideRec;
	sideRec.SetRect(0, tmp.top - 6, tmp.left - 2, tmp2.bottom);
	dc->DrawText(doubleToStr(maxPrice), sideRec, DT_RIGHT);
	sideRec.top = getPosition(tmp.top, tmp.bottom, 1, 3) - 6;
	dc->DrawText(doubleToStr(getPosition(maxPrice, minPrice, 1, 3)), sideRec, DT_RIGHT);
	sideRec.top = getPosition(tmp.top, tmp.bottom, 1, 1) - 6;
	dc->DrawText(doubleToStr(getPosition(maxPrice, minPrice, 1, 1)), sideRec, DT_RIGHT);
	sideRec.top = getPosition(tmp.top, tmp.bottom, 3, 1) - 6;
	dc->DrawText(doubleToStr(getPosition(maxPrice, minPrice, 3, 1)), sideRec, DT_RIGHT);
	sideRec.top = tmp.bottom - 6;
	dc->DrawText(doubleToStr(minPrice), sideRec, DT_RIGHT);
	sideRec.top = tmp2.top - 6;
	dc->DrawText(intToStr(maxVolume), sideRec, DT_RIGHT);
	setMouseText(dc);

	//draw k-line;

	dc->SetTextColor(COLOR_FRAME);
	dc->TextOutA(tmp2.left, tmp2.bottom + 2, intTimeToStr(beginTime));
	dc->TextOutA(kLineTimeToPixel(getPosition(beginTime, endTime, 1, 3)), tmp2.bottom + 2, intTimeToStr(getPosition(beginTime, endTime, 1, 3)));
	dc->TextOutA(kLineTimeToPixel(getPosition(beginTime, endTime, 1, 1)), tmp2.bottom + 2, intTimeToStr(getPosition(beginTime, endTime, 1, 1)));
	dc->TextOutA(kLineTimeToPixel(getPosition(beginTime, endTime, 3, 1)), tmp2.bottom + 2, intTimeToStr(getPosition(beginTime, endTime, 3, 1)));
	for (int i = beginTime; i <= lastTime; i++)
	{
		//judge if is upper
		MINUTE_MARKET_DATA_TYPE &mt = mmd[i];
		CPen pr;
		CBrush br((mt.lastPrice >= mt.firstPrice) ? (COLOR_RED) : (COLOR_GREEN));
		pr.CreatePen(PS_SOLID, 1, (mt.lastPrice >= mt.firstPrice) ? (COLOR_RED) : (COLOR_GREEN));
		dc->SelectObject(&pr);
		dc->SelectObject(&br);
		int leftPixel = kLineTimeToPixel(i) + 1;
		int rightPixel = kLineTimeToPixel(i + 1) - 1;
		int midPixel = getPosition(leftPixel, rightPixel, 1, 1);
		int upperPrice = max(mt.firstPrice, mt.lastPrice);
		int lowerPrice = min(mt.firstPrice, mt.lastPrice);
		int volume = mt.lastVolume - mt.firstVolume;
		Rectangle(
			*dc, 
			leftPixel, 
			convertPriceToPixel(tmp.bottom, tmp.top, minPrice, maxPrice, upperPrice),
			rightPixel,
			convertPriceToPixel(tmp.bottom, tmp.top, minPrice, maxPrice, lowerPrice) + 1
			);
		drawLine(
			dc,
			midPixel,
			convertPriceToPixel(tmp.bottom, tmp.top, minPrice, maxPrice, upperPrice),
			midPixel,
			convertPriceToPixel(tmp.bottom, tmp.top, minPrice, maxPrice, mt.highestPrice)
			);
		drawLine(
			dc,
			midPixel,
			convertPriceToPixel(tmp.bottom, tmp.top, minPrice, maxPrice, lowerPrice),
			midPixel,
			convertPriceToPixel(tmp.bottom, tmp.top, minPrice, maxPrice, mt.lowestPrice)
			);
		Rectangle(
			*dc,
			leftPixel,
			convertPriceToPixel(tmp2.bottom, tmp2.top, 0, maxVolume, volume),
			rightPixel,
			tmp2.bottom - 1
			);
	}
	return 0;
}


HBRUSH ChartDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


//int ChartDlg::getPosition(int v1, int v2, int opt1, int opt2)
//{
//	return (v1*opt2 + v2*opt1) / (opt1 + opt2);
//}

void ChartDlg::drawLine(CPaintDC * dc, int x1, int y1, int x2, int y2)
{
	dc->MoveTo(x1, y1);
	dc->LineTo(x2, y2);
}



void ChartDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (focusedInstrumentID == -1)
		return;
	CPaintDC dc(this);
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	tmp.top = tmp.bottom;
	tmp.bottom += HEIGHT_H4;

	minuteMarketData & mmd = *pMinuteMarketData[focusedOrderedInstrumentID];
	int curTime = (chartType) ? (kLinePixelToTime(point.x)) : getPosition(0, 270, (point.x - tmp.left), (tmp.right - point.x));
	if (curTime < 0 || curTime >269)
		return;
	if (curTime > mmd.lastIndex)
		curTime = mmd.lastIndex;
	curPos = mmd[curTime].position;
	curPrice = mmd[curTime].lastPrice;
	curAvgPrice = mmd[curTime].avgPrice;
	curVolume = mmd[curTime].lastVolume - mmd[curTime].firstVolume;
	InvalidateRect(tmp, 1);
	tmp.top = chart.top;
	tmp.bottom = chart.top + HEIGHT_H4;
	InvalidateRect(tmp, 1);
	paint();
	CDialogEx::OnMouseMove(nFlags, point);
}


//void ChartDlg::setMouseText()
//{
//}


void ChartDlg::setMouseText(CPaintDC *dc)
{
	CString cs;
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	tmp.top = tmp.bottom;
	tmp.bottom += HEIGHT_H4;
	cs.Format("持仓量：%d  成交量：%d", curPos, curVolume);
	dc->TextOutA(chart.left + WIDTH_H4 + 3, tmp.top + 2, cs);
}


void ChartDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//填信息
	if (nIDEvent == 1)
	{
		CRect statusFieldRec;
		GetClientRect(statusFieldRec);
		statusFieldRec.left = statusFieldRec.right - FRAME_INFO_WIDTH;
		statusFieldRec.top = HEIGHT_H1;
		InvalidateRect(statusFieldRec);
		paint();
	}
	//画图
	if (nIDEvent == 2)
	{
		CRect chart;
		GetClientRect(chart);
		chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
		InvalidateRect(chart);
		paint();
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL ChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 500, NULL);
	SetTimer(2, 5000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


int ChartDlg::converTimeToPixel(int timeIndex)
{
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	tmp.top = tmp.bottom;
	tmp.bottom += HEIGHT_H4;
	return getPosition(tmp.left, tmp.right, timeIndex, 270 - timeIndex);
}


int ChartDlg::convertPixelToTime(int p)
{
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	tmp.top = tmp.bottom;
	tmp.bottom += HEIGHT_H4;

	return getPosition(0, 270, (p - tmp.left), (tmp.right - p));
	return 0;
}

int ChartDlg::convertPriceToPixel(int lowerPos, int upperPos, double lowerPrice, double upperPrice, double currentPrice)
{
	return getPosition(lowerPos, upperPos, currentPrice - lowerPrice, upperPrice - currentPrice);
	return 0;
}


void ChartDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == 73) 
	{
		chartType = 1 - chartType;
		Invalidate();
		paint();
	}
	if (nChar == 74 && chartType == 1 && candleCount > 10)
	{
		candleCount -= 10;
		Invalidate();
		paint();
	}
	if (nChar == 75 && chartType == 1)
	{
		candleCount += 10;
		Invalidate();
		paint();
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


int ChartDlg::kLinePixelToTime(int x)
{
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	tmp.top = tmp.bottom;
	tmp.bottom += HEIGHT_H4;
	
	return getPosition(beginTime, endTime, x - tmp.left, tmp.right - x);
	return 0;
}


int ChartDlg::kLineTimeToPixel(int t)
{
	CRect chart;
	GetClientRect(chart);
	chart.SetRect(10, 2, chart.right - FRAME_INFO_WIDTH, chart.bottom - 10);
	CRect tmp(chart);
	tmp.left += WIDTH_H4;
	tmp.top += HEIGHT_H4;
	tmp.right -= WIDTH_H4;
	tmp.bottom = getPosition(tmp.top, tmp.bottom - HEIGHT_H4, 3, 1);
	tmp.top = tmp.bottom;
	tmp.bottom += HEIGHT_H4;

	return getPosition(tmp.left, tmp.right, t - beginTime, endTime - t);
	return 0;
}


CString ChartDlg::intTimeToStr(int t)
{
	CString cs;
	t %= 270;
	int h, m;
	if (t < 135)
	{
		h = 9 + (t + 15) / 60;
		m = (t + 15) % 60;
	}
	else
	{
		h = 13 + (t - 135) / 60;
		m = (t - 135) % 60;
	}

	cs.Format((m > 9) ? "%d:%d" : "%d:0%d", h, m);
	return cs;
}
