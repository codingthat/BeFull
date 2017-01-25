/***************************************************
 BeFullSet.cpp - by Kevin Field
 ***************************************************/

#include <Font.h>
#include <Entry.h>
#include "BeFullSet.h"
#include "BeFullWindow.h"
#include "BeFullApp.h"
#include <stdio.h>
#include <string.h>
#include <Roster.h>
#include <Bitmap.h>
#include <NodeInfo.h>
#include <Node.h>

#include "DrawCentredText.cpp"

BeFullSet::BeFullSet(const BRect wholeThing, const char* label, const char * path, const rgb_color normc) : BView(wholeThing, label, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE)
{
	BeFullSet::label = strdup(label);
	BeFullSet::path = strdup(path);
/*	BeFullSet::label.SetTo(label);
	int i;
	for (i=strlen(label);label[i-1]!='/';i--) if (i==1) break;
	name = new char[strlen(label)-i+1];
	strncpy(name,&label[i],strlen(label)-i);
	name[strlen(label)-i]='\0';
*/	
	highlighted=false;
//	highlightcolour=highc;
//	highlightcolour.red=255;
//	highlightcolour.green=255;
//	highlightcolour.blue=255;
	normalcolour=normc;

}

BeFullSet::~BeFullSet()
{
//	if (pbs) delete pbs;
}

BeFullLabel::BeFullLabel(const BRect wholeThing, const char * label, const rgb_color colour) : BView(wholeThing, label, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE)
{
	BeFullLabel::label = strdup(label);
//	highlightcolour=highc;
//	highlightcolour.red=255;
//	highlightcolour.green=255;
//	highlightcolour.blue=255;
	BeFullLabel::colour=colour;

}

void BeFullLabel::Draw(BRect updateRect)
{
	float	fh=Frame().Height(),
			fw=Frame().Width();	
	BFont font(be_bold_font);
	font.SetRotation(90.0);
	font_height fonth;
	font.SetSize(12.0);
	SetFont(&font);
	font.GetHeight(&fonth);
	SetHighColor(colour);
	SetLowColor(0,0,0);
	StrokeLine(BPoint(15.0,3.0),BPoint(9.0,3.0));
	StrokeLine(BPoint(9.0,fh-4.0));
	StrokeLine(BPoint(15.0,fh-4.0));
	StrokeLine(BPoint(9.0,(fh-font.StringWidth(label))/2-3.0),BPoint(9.0,(fh-font.StringWidth(label))/2+font.StringWidth(label)+1.0),B_SOLID_LOW);
	SetHighColor(255,255,255);
	DrawString(label,BPoint((fw-fonth.descent+fonth.ascent)/2,(fh-font.StringWidth(label))/2+font.StringWidth(label)));
}


void BeFullSet::Draw(BRect updateRect)
{
	status_t err;
	float	fh=Frame().Height(),
			fw=Frame().Width();	
	BFont font(be_bold_font);
	font_height fonth;
	font.SetSize(20.0);
	SetFont(&font);
	font.GetHeight(&fonth);
	rgb_color white;
	white.red=255;white.green=255;white.blue=255;
	SetLowColor(highlighted?white:normalcolour);
	FillRoundRect(BRect(1.0,1.0,fw-2,fh-2),2.0,2.0,B_SOLID_LOW);
	// next line sucks, change it
	SetHighColor(highlighted?0:255,highlighted?0:255,highlighted?0:255);
//	DrawString(name,BPoint((fw+fh-4.0-font.StringWidth(name))/2,(fh-fonth.descent+fonth.ascent)/2));
	DrawCentredText(label,&font,BRect(fh-2.0,2.0,fw-4.0,fh-2.0),this,false);
	
	BEntry entry(path, true);
	if (entry.Exists())
	{
		BBitmap bb(BRect(0.0,0.0,31.0,31.0),B_CMAP8);
		BNodeInfo bni;
		BNode bn(path);
		err=bn.InitCheck();
		if (err==B_OK) err=bni.SetTo(&bn);
		else printf("InitCheck: B_NO_INIT\n");
		if (err==B_BAD_VALUE) printf("SetTo: B_BAD_VALUE\n");
		SetDrawingMode(B_OP_OVER);
		err=bni.GetIcon(&bb);
		if (err==B_OK) DrawBitmap(&bb,BRect(2.0,2.0,fh-3.0,fh-3.0));
		else switch (err)
		{
			case B_BAD_VALUE:
				printf("GetIcon: B_BAD_VALUE\n");
				break;
			case B_NO_INIT:
				printf("GetIcon: B_NO_INIT\n");
				break;
		}
		SetDrawingMode(B_OP_COPY);
	}
	else
	{
		SetHighColor(255,50,50);
		SetPenSize(2.0);
		MovePenTo((fw+fh-4.0-font.StringWidth(label))/2, fh/2);
		StrokeLine(BPoint((fw+fh-4.0-font.StringWidth(label))/2.0+font.StringWidth(label),fh/2.0),B_SOLID_HIGH);
		font.SetSize(10.0);
		SetFont(&font);
		SetHighColor(255,0,0);
		font.GetHeight(&fonth);
		DrawString("toast",BPoint((fh-font.StringWidth("toast"))/2,(fh-fonth.descent+fonth.ascent)/2));
	}
}

void BeFullSet::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	switch (transit)
	{
		case B_ENTERED_VIEW:
			highlighted=true;
			Draw(Frame());
			break;
		case B_EXITED_VIEW:
			highlighted=false;
			Draw(Frame());
			break;
	}
}

void BeFullSet::MouseDown(BPoint point)
{
	entry_ref ref; 
	if (get_ref_for_path(path, &ref) != B_OK) printf("Error converting %s", path);
	else if (be_roster->Launch(&ref) != B_NO_ERROR) printf("Error launching %s", path);
	
	(BeFullApp*)be_app->PostMessage(B_QUIT_REQUESTED); // in any case
}

int BeFullSet::AddPB(const char* newText)
{
	return 0;
}

