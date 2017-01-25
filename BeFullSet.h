/***************************************************
 BeFullSet.h - by Kevin Field
 ***************************************************/

#ifndef _BEFULLSET_H_
#define _BEFULLSET_H_

#include <PictureButton.h>
#include <Path.h>

class BeFullSet : public BView
{
	public:
							BeFullSet(const BRect wholeThing, const char * label, const char * path, const rgb_color normc);
							~BeFullSet();
		int		 			AddPB(const char * newText);
		virtual void		Draw(BRect updateRect);
		virtual void		MouseMoved(BPoint point, uint32 transit, const BMessage *message);
		virtual void		MouseDown(BPoint point);
	private:
		rgb_color			highlightcolour;
		rgb_color			normalcolour;
		bool				highlighted;
		BPictureButton*		pbs;
		char *				label;
		char *				path;
};

class BeFullLabel : public BView
{
	public:
							BeFullLabel(const BRect wholeThing, const char* label, const rgb_color colour);
//							~BeFullLabel();
		virtual void		Draw(BRect updateRect);
	private:
		rgb_color			colour;
		char*				label;
};

#endif