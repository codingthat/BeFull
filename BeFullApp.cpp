/***************************************************
 BeFullApp.cpp - by Kevin Field
 ***************************************************/

#include "BeFullApp.h"
#include "BeFullWindow.h"

int main(int, char**)
{
	BeFullApp* app = new BeFullApp;
	app->Run();
	
	return(0);
}

BeFullApp::BeFullApp() : BApplication("application/x-vnd.Kev-BeFull")
{
}

void BeFullApp::ReadyToRun()
{
	fWindow = new BeFullWindow();
	fWindow->Show();
}