
// Drawer.cpp: файл реализации
//

#include "pch.h"
#include "Task-7(animation)Dlg.h"
#include "Drawer.h"

IMPLEMENT_DYNAMIC(Drawer, CStatic)

Drawer::Drawer()
{
	GdiplusStartupInput si;
	GdiplusStartup(&token, &si, NULL);
}

Drawer::~Drawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(Drawer, CStatic)	
END_MESSAGE_MAP()

void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{	
	wchar_t str[15];
	friq->GetWindowTextW(str, friq->GetWindowTextLengthW() + 1);
	f = wcstod(str, NULL);
	phase->GetWindowTextW(str, phase->GetWindowTextLengthW() + 1);
	df =  wcstod(str, NULL);

	//параметры графика в мировых координатах
	top = 2;
	bottom = -2;
	left = 0;
	right = 12;
	xPadding = (right - left) / 10;
	yPadding = (top - bottom) / 10;	
	steplenY = (top - bottom) / 10,
	steplenX = (right - left) / 10;
	xScale = ItemWidth / (right + xPadding - (left - xPadding));
	yScale = -ItemHeight / (top + yPadding - (bottom - yPadding));
	
	//параметры контекста рисования
	ItemWidth = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left,
	ItemHeight = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;	

	Bitmap Image(ItemWidth, ItemHeight);
	Graphics gr(&Image);
	gr.Clear(Color::White);	
	//сглаживание
	gr.SetSmoothingMode(SmoothingModeAntiAlias);	
	
	//преобразование мира(переход к координатам самого графика
	Matrix matr;
	matr.Scale(xScale, yScale + 1); //маштабирование
	matr.Translate(xPadding, -(top + yPadding - (bottom - yPadding)) / 2); //перенос начала координат
	gr.SetTransform(&matr);

	
	Pen BackGroundPen(Color::DarkGray, 0.005);
	Pen pen(Color::Black, 0.02);
	Pen DataPen(Color::DarkBlue, 0.01);
	SolidBrush brush(Color::Black);	
	Gdiplus::Font font((L"Times New Roman"), 14, FontStyle::FontStyleRegular, UnitPixel);	

	//Оси
	gr.DrawLine(&pen, PointF(left, top), PointF(left, bottom));
	gr.DrawLine(&pen, PointF(left, bottom), PointF(right, bottom));
	
	//Разметка
	for (int i = 0; i < 10; i++)
	{		
		//горизонтальная
		gr.DrawLine(&BackGroundPen, PointF(left, top - i * steplenY), PointF(right, top - i * steplenY));

		//вертикальная
		gr.DrawLine(&BackGroundPen, PointF(i * steplenX, top), PointF(i * steplenX, bottom));
	}

	gr.ResetTransform();

	//подписи к осям
	for (int i = 0; i < 11; i++)
	{
		CString str;
		
		//по Y
		str.Format(L"%.2f", top - i * steplenY);
		PointF strPoint(left - steplenX / 1.5, top - (i - 0.125) * steplenY);
		matr.TransformPoints(&strPoint);
		gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);

		//по X
		str.Format(L"%.2f", right - i * steplenX);
		strPoint.X = right - (i + 0.25) * steplenX;
		strPoint.Y = bottom - steplenY / 2.;
		matr.TransformPoints(&strPoint);
		gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);
	}
	
	gr.SetTransform(&matr);


	//Отрисовка графика
	double N = 1000;
	steplenX = (right - left) / N;

	PointF p1, p2;
	p1 = PointF(left, func(0));	
	
	for (int i = 1; i < N + 1; i++)
	{
		p2 = PointF(i * steplenX, func(i * steplenX));
		gr.DrawLine(&DataPen, p1, p2);
		p1 = p2;
	}

	Graphics grnew(lpDrawItemStruct->hDC);
	grnew.DrawImage(&Image, 0, 0);
}

double Drawer::func(double x) {
	return sin(f * x  + phaseapd) + sin((f+df) * x +  + phaseapd);
}