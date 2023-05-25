
// Task-7(animation).h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTask7animationApp:
// Сведения о реализации этого класса: Task-7(animation).cpp
//

class CTask7animationApp : public CWinApp
{
public:
	CTask7animationApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CTask7animationApp theApp;
