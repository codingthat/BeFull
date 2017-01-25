/***************************************************
 BeFullApp.h - by Kevin Field
 ***************************************************/


#ifndef _BEFULLAPP_H_
#define _BEFULLAPP_H_


#include <Application.h>

#include "BeFullWindow.h"

class BeFullApp : public BApplication
{
	public:
						BeFullApp();
		virtual void	ReadyToRun();

	private:
		BeFullWindow*	fWindow;
};

#endif
