#include "stdafx.h"
#include "ResourcesAndTools.h"


ResourcesAndTools::ResourcesAndTools()
{
}


ResourcesAndTools::~ResourcesAndTools()
{
}

CString ResourcesAndTools::doubleToStr(double n)
{
	CString s;
	s.Format("%.1lf", n);
	return s;
}

CString ResourcesAndTools::intToStr(int n)
{
	CString s;
	s.Format("%d", n);
	return s;
}

CString ResourcesAndTools::intToUnitedStr(int n)
{
	CString s;
	int i = 0;
	while ((n /= 10000) > 100000)
		i++;
	s.Format("%d%s", n, units[i]);
	return s;
}
