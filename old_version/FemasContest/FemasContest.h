
// FemasContest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFemasContestApp: 
// �йش����ʵ�֣������ FemasContest.cpp
//

class CFemasContestApp : public CWinApp
{
public:
	CFemasContestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFemasContestApp theApp;