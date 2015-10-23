#pragma once

#define FRAME_INFO_WIDTH 250
#define FONT_SIZE_H1 160
#define FONT_SIZE_H2 120
#define FONT_SIZE_H3 100
#define FONT_SIZE_H4 95
#define HEIGHT_H1 35
#define HEIGHT_H2 25
#define HEIGHT_H3 15
#define HEIGHT_H4 16
#define WIDTH_H4 45
#define COLOR_WHITE RGB(255,255,255)
#define COLOR_PRIMARY RGB(0,255,255)
#define COLOR_RED RGB(255,0,0)
#define COLOR_YELLOW RGB(255, 255, 0)
#define COLOR_PINK RGB(255, 0, 255)
#define COLOR_GREEN RGB(0,255,0)
#define COLOR_FRAME RGB(180,0,0)
#define COLOR_BG RGB(5,5,5)
#define COLOR_RG(v1, v2) ((v1) > (v2)) ? (COLOR_RED) : (((v1) == (v2)) ? (COLOR_WHITE) : (COLOR_GREEN))
#define getPosition(v1, v2, opt1, opt2) ((v1)*(opt2) + (v2)*(opt1)) / ((opt1) + (opt2))

// ChartDlg 对话框

class ChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChartDlg)

public:
	ChartDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChartDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHART_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void paint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void paintInstrumentStatus(CPaintDC *dc);
	void paintTimeLineChart(CPaintDC *dc);
	int paintCandleLineChart(CPaintDC *dc);
	int focusedOrderedInstrumentID = -1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int chartType;
//	int getPosition(int v1, int v2, int opt1, int opt2);
	void drawLine(CPaintDC *dc, int x1, int y1, int x2, int y2);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	double curPrice;
	double curAvgPrice;
	int curPos;
	int curVolume;
//	void setMouseText();
	void setMouseText(CPaintDC *dc);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int focusedInstrumentID;
	virtual BOOL OnInitDialog();
	int converTimeToPixel(int timeIndex);
	int convertPixelToTime(int p);
	int convertPriceToPixel(int lowerPos, int upperPos, double lowerPrice, double upperPrice, double currentPrice);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int beginTime;
	int endTime;
	int kLinePixelToTime(int x);
	int kLineTimeToPixel(int t);
	CString intTimeToStr(int t);
	int candleCount;
};
