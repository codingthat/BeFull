/***************************************************
 BeFullWindow.h - by Kevin Field
 ***************************************************/

#ifndef _BEFULLWINDOW_H_
#define _BEFULLWINDOW_H_

#include <Window.h>
#include <vector>
#include "BeFullSet.h"

class BeFullWindow : public BWindow
{
	public:
						BeFullWindow();
						~BeFullWindow();
		virtual void	WorkspaceActivated(int32 workspace, bool active);
		virtual bool	QuitRequested();
		virtual void	MessageReceived(BMessage* message);
	private:
			BView *		backgroundcolour;
};


#endif
