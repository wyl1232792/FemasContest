#pragma once
class ResourcesAndTools
{
public:
	ResourcesAndTools();
	~ResourcesAndTools();
	CString doubleToStr(double n);
	CString intToStr(int n);
	CString intToUnitedStr(int n);
	char *strNetworkStatus[3] = { "δ����", "�����ӷ�����", "�ѵ�¼" };
	char *strDirection[2] = { "����", "����" };
	char *strOrderType[5] = { "", "�����", "�޼�" , "���ż�" , "�嵵��" };
	char *strOffsetType[5] = { "����","ƽ��","ǿƽ","ƽ��","ƽ��" };
	char *strOrderStatus[7] = { "ȫ���ɽ�","���ֳɽ�","���ֳɽ����ڶ���","δ�ɽ�","δ�ɽ����ڶ���","�ѳ���","��Ӧ��" };
	char *units[4] = { "��", "��", "����", "��" };
private:
};

