#pragma once
#include<gdiplus.h>
using namespace Gdiplus;

// Drawer

class Drawer : public CStatic
{
	DECLARE_DYNAMIC(Drawer)

public:
	Drawer();
	virtual ~Drawer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	ULONG_PTR token;
	double func(double x);

	double 
		f,
		df,
		top,
		bottom,
		left,
		right,
		xPadding,
		yPadding,	
		steplenY,
		steplenX,
		ItemWidth,
		ItemHeight,
		xScale,
	    yScale,
		phaseapd = 0;
	
	CEdit* friq;
	CEdit* phase;
};