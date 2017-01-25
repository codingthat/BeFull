/***************************************************
 DrawCentredText.cpp - by Kevin Field
 ***************************************************/

#ifndef _DRAWCENTREDTEXT_CPP_
#define _DRAWCENTREDTEXT_CPP_

#define HEIGHT_RATIO 1.198730

//	printf("%f\n",(fonth.ascent+fonth.descent)/i);  // i is the font size
//	use this line if you ever change fonts to figure out what HEIGHT_RATIO should be
//  (for be_fixed_font it's 1.156738, and for the other two, it's 1.198730)
//	hard-coded for speed!

#include <Font.h>
#include <View.h>
#include <stdio.h>
#include <string.h>

void DrawCentredText(const char * TextToCentre, BFont * FontWithWhichToDraw, BRect RectInWhichToCentre, BView * ViewInWhichToDraw, bool MaxHeight)
{
	float i=RectInWhichToCentre.Height()/HEIGHT_RATIO;
	FontWithWhichToDraw->SetSize(i);
	
	if (FontWithWhichToDraw->StringWidth(TextToCentre) > RectInWhichToCentre.Width())
	{
		if (MaxHeight)
		{
			char * TextWillCentre = strdup(TextToCentre);

			strcpy(&TextWillCentre[strlen(TextWillCentre)-3], "...");
			int e=strlen(TextWillCentre);
			do
			{
				e--;
				TextWillCentre[e-3]='.';
				TextWillCentre[e]='\0';
			} while (FontWithWhichToDraw->StringWidth(TextWillCentre) > RectInWhichToCentre.Width() && e > 4);
			font_height fonth;
			FontWithWhichToDraw->GetHeight(&fonth);
			ViewInWhichToDraw->SetFont(FontWithWhichToDraw);
			ViewInWhichToDraw->DrawString(TextWillCentre,BPoint(RectInWhichToCentre.left+(RectInWhichToCentre.Width()-FontWithWhichToDraw->StringWidth(TextWillCentre))/2,RectInWhichToCentre.top+(RectInWhichToCentre.Height()-i*HEIGHT_RATIO)/2+fonth.ascent));

			delete TextWillCentre;
		}
		else
		{
			do
			{
				i--;
				FontWithWhichToDraw->SetSize(i);
			} while (FontWithWhichToDraw->StringWidth(TextToCentre) > RectInWhichToCentre.Width());
			FontWithWhichToDraw->SetSize(i++);
			font_height fonth;
			FontWithWhichToDraw->GetHeight(&fonth);
			ViewInWhichToDraw->SetFont(FontWithWhichToDraw);
			ViewInWhichToDraw->DrawString(TextToCentre,BPoint(RectInWhichToCentre.left+(RectInWhichToCentre.Width()-FontWithWhichToDraw->StringWidth(TextToCentre))/2,RectInWhichToCentre.top+(RectInWhichToCentre.Height()-i*HEIGHT_RATIO)/2+fonth.ascent));
		}
	}
	else
	{
		font_height fonth;
		FontWithWhichToDraw->GetHeight(&fonth);
		ViewInWhichToDraw->SetFont(FontWithWhichToDraw);
		ViewInWhichToDraw->DrawString(TextToCentre,BPoint(RectInWhichToCentre.left+(RectInWhichToCentre.Width()-FontWithWhichToDraw->StringWidth(TextToCentre))/2,RectInWhichToCentre.top+(RectInWhichToCentre.Height()-i*HEIGHT_RATIO)/2+fonth.ascent));
	}

}

#endif