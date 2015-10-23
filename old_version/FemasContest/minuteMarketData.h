#pragma once

//the show the price&volume information of every minute
struct MINUTE_MARKET_DATA_TYPE
{
	//��߼�/��ͼ�
	double highestPrice, lowestPrice;
	//�ֲ���
	int position;
	//�������/���ɽ���
	double firstPrice, lastPrice;
	//��������ʱ�̾���
	double avgPrice;
	int firstVolume, lastVolume;
};

class minuteMarketData
{
public:
	//���к�Լ�е�id
	int m_InstrumentID;
	minuteMarketData();
	~minuteMarketData();
	//ȡ����
	MINUTE_MARKET_DATA_TYPE& operator[](int n);
	//ȡ����һ���ӵ�״̬
	MINUTE_MARKET_DATA_TYPE& latestMinute();
	//ȡǰһ����״̬
	MINUTE_MARKET_DATA_TYPE& previousMinute();
private:
	//�������
	MINUTE_MARKET_DATA_TYPE data[271];
public:
	//һ��ľ���
	double avgPrice;
	//����������
	double maxChg;
	//�������ֲ�
	int maxPosition;
	//������С�ֲ�
	int minPosition;
	//������״̬�����ڷ��ӵ�id
	int lastIndex;
	//���������Ƿ��ѵ�һ�θ�ֵ
	bool isInit;
	//����һ�������ɽ���
	int maxVolume;
};

