/***************************************************
 BeFullWindow.cpp - by Kevin Field
 ***************************************************/

#include "BeFullWindow.h"
#include <Screen.h>
#include <Application.h>
#include <Directory.h>
#include <Entry.h>
#include <Path.h>
#include <stdio.h>
#include <string.h>
#include <Query.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

BeFullWindow::BeFullWindow() : BWindow(BRect(0,0,0,0),"BeFull",B_NO_BORDER_WINDOW_LOOK,B_MODAL_ALL_WINDOW_FEEL,B_WILL_DRAW)
//BeFullWindow::BeFullWindow() : BWindow(BRect(0,0,0,0),"BeFull",B_DOCUMENT_WINDOW_LOOK,B_NORMAL_WINDOW_FEEL,B_WILL_DRAW)
{
	BScreen screen;
	display_mode mode;
	if (screen.GetMode(&mode)==B_OK) ResizeTo((float)mode.virtual_width,(float)mode.virtual_height);
	backgroundcolour = new BView(Frame(), "backgroundcolour", B_FOLLOW_NONE, B_WILL_DRAW);
	backgroundcolour->SetViewColor(0,0,0);
	
	remove("/boot/home/config/settings/BeFull colour settings"); // clean up old versions' stuff

	char 	s[4000] = "",
			currentDir[4000] = "",
			currentEntry[4000] = "",
			setFilePath[] = "/boot/home/config/settings/BeFull settings",
			beMenuPath[] = "/boot/home/config/be/";
	FILE *inp = fopen(setFilePath, "r");
	int totalEntries = 0,
		doneEntries = 0,
		defaultHeight = 36,
		columns = 1,
		labelTop = 0,
		columnLeft = 18,
		columnRight,
		entryTop = 0,
		currentColumn = 0;
	bool upcolour = false;
//	BNode curEntry;
//	BDirectory beMenuPath(), curDir;
	BEntry curEntry, curEntryTraversed;
	char label[B_FILE_NAME_LENGTH];
	BPath path;

	rgb_color cur_colour;
	
	srand(time(NULL));
		
	if (inp) fgets(s,4000,inp);
	if (!inp || s[0]=='/' || !strlen(s))
	{
		char sysMsg[4058] = "ls -L -1 -R ";
		fclose(inp);
		strncat(sysMsg, strlen(s)?s:beMenuPath, strlen(s)-2); // get rid of ":\n" at end
		strcat(sysMsg, " > /boot/home/config/settings/BeFull\\ settings");
		system(sysMsg);
		inp = fopen(setFilePath, "r");
	}
	while (inp && fgets(s,4000,inp))
	{
		if (s[0]!='\n')
		{
			s[strlen(s)-1]='\0'; // get rid of '\n' at end
			if (s[0]!='/')
			{
				strcpy(currentEntry,currentDir);
				strcat(currentEntry,"/");
				strcat(currentEntry,s);
				if (curEntry.SetTo(currentEntry)==B_OK && !(curEntry.IsDirectory()))
				{
					totalEntries++;
					printf("%s\n",currentEntry);
				}
			}
			else
			{
				strncpy(currentDir,s,strlen(s)-strlen(strchr(s,':'))); // get rid of ":" at end
				currentDir[strlen(s)-strlen(strchr(s,':'))]='\0';
			}
		}
	}
//	printf("Total entries: %d\n",totalEntries);

	columns=(int)ceil(totalEntries*1/floor(mode.virtual_height/defaultHeight));
	while (0.7 * mode.virtual_width / columns < 150 && defaultHeight > 22)
	{
		columns--;
		defaultHeight = (int)floor(mode.virtual_height)*columns/totalEntries;
	}
	fclose(inp);
	inp = fopen(setFilePath, "r");

	columnRight = (int)(mode.virtual_width / columns);
	if (columns>1) columnRight = (int)(columnRight * (columns-0.7)/(columns-1.0));
//	printf("columnRight: %d\n", mode.virtual_width);
	
	while (inp && fgets(s,4000,inp))
	{
		if (s[0]!='\n')
		{
			s[strlen(s)-1]='\0'; // get rid of '\n' at end
//			printf("%s\n",s);
			if (s[0]=='/')
			{
				if (columnLeft || labelTop || entryTop) AddChild(new BeFullLabel(BRect(columnLeft-18,labelTop,columnLeft,entryTop),label,cur_colour));
				labelTop = entryTop;
				strncpy(currentDir,s,strlen(s)-strlen(strchr(s,':'))); // get rid of ":" at end
				currentDir[strlen(s)-strlen(strchr(s,':'))]='\0';
				strcpy(label,strrchr(s,'/')+1);
				label[strlen(label)-strlen(strchr(label,':'))]='\0';
				if (strlen(strchr(s,':'))>1)
				{
//				printf("New dir: %s\n", s);
					sscanf(strchr(s,':'),":%u %u %u",(int *)&cur_colour.red,(int *)&cur_colour.green,(int *)&cur_colour.blue);
					if (cur_colour.red > 210) cur_colour.red = 210;
					if (cur_colour.green > 210) cur_colour.green = 210;
					if (cur_colour.blue > 210) cur_colour.blue = 210;
				}
				else
				{
					if (strchr(&(s[strlen(beMenuPath)]),'/'))
					{
//						printf("New sub dir: %s\n", s);			
						if (upcolour)
						{
							cur_colour.red = (int)(cur_colour.red + 30);
							cur_colour.green = (int)(cur_colour.green + 30);
							cur_colour.blue = (int)(cur_colour.blue + 30);
							upcolour = false;
						}
						else
						{
							cur_colour.red = (int)(cur_colour.red - 30);
							cur_colour.green = (int)(cur_colour.green - 30);
							cur_colour.blue = (int)(cur_colour.blue - 30);
							upcolour = true;
						}
					}
					else
					{
//					printf("New dir: %s\n", s);
						cur_colour.red = rand()%180+30;
						cur_colour.green = rand()%180+30;
						cur_colour.blue = rand()%180+30;
					}
				}
			}
			else
			{
				strcpy(currentEntry,currentDir);
				strcat(currentEntry,"/");
				strcat(currentEntry,s);
				if (curEntry.SetTo(currentEntry)==B_OK && !(curEntry.IsDirectory()))
				{
					if (entryTop+defaultHeight>mode.virtual_height)
					{
						AddChild(new BeFullLabel(BRect(columnLeft-18,labelTop,columnLeft,mode.virtual_height),label,cur_colour));
						labelTop = 0;
						currentColumn++;
						entryTop = 0;
						columnLeft = columnRight;
						if (columns > currentColumn + 1) columnRight = (int)(columnLeft + mode.virtual_width / columns * ((columns-0.7)/(columns-1.0)));
						else
						{
							columnRight = (int)(mode.virtual_width);
							defaultHeight = (int)(mode.virtual_height/(totalEntries-doneEntries));
						}
						columnLeft+=18;
					}
					curEntry.SetTo(currentEntry);
					curEntry.GetPath(&path);
					curEntryTraversed.SetTo(path.Path(),true);
					// if I went straight to here, it would skip broken symlinks and mess up my labels
					if (curEntryTraversed.Exists()) curEntryTraversed.GetPath(&path);
	
//					printf("Adding %s\n", currentEntry);
					if (entryTop+defaultHeight*2>mode.virtual_height)
					{
						AddChild(new BeFullSet(BRect(columnLeft,entryTop,columnRight,mode.virtual_height),s,path.Path(),cur_colour));
						entryTop = mode.virtual_height;
					}
					else
					{
						AddChild(new BeFullSet(BRect(columnLeft,entryTop,columnRight,entryTop+defaultHeight),s,path.Path(),cur_colour));
						entryTop = entryTop + defaultHeight;
					}
					doneEntries++;
					
//					printf("New item: %s\n", s);
				}
			}
		}
	}
	AddChild(new BeFullLabel(BRect(columnLeft-18,labelTop,columnLeft,mode.virtual_height),label,cur_colour));

//		FILE *outp;
//		if (!(outp = fopen("/boot/home/config/settings/BeFull colour settings", "w"))) printf("Error opening settings file for writing--this is bad news!");
//		uint8 red, green, blue;
//		srand(time(NULL));
//		for (int i=0;i<15;i++)
//		{
//			red = rand()%200;
//			green = rand()%200;
//			blue = rand()%200;
//			fprintf(outp, "%d %d %d\n",red,green,blue);
//		}
//		fclose(outp);
//	}
//	AddRecursively(BDirectory("/boot/home/config/be/"), BDirectory("/boot/home/config/be/"));	

	if (inp) fclose(inp);
//	remove("/boot/home/config/settings/BeFull colour settings"); // debug (or "live"!)
	AddChild(backgroundcolour);
}

BeFullWindow::~BeFullWindow()
{
}

void BeFullWindow::WorkspaceActivated(int32 workspace, bool active)
{
	QuitRequested();
}


bool BeFullWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return (true);
}


void BeFullWindow::MessageReceived(BMessage* message)
{
	uint32 mWhat = message->what;
	switch (mWhat)
	{
		case B_KEY_DOWN:
			QuitRequested();
			break;
		default:
		BWindow::MessageReceived(message);
	}
}

