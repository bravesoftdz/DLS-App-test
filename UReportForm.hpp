// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Ureportform.pas' rev: 20.00

#ifndef UreportformHPP
#define UreportformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Virtualtrees.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ureportform
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TReportForm;
class PASCALIMPLEMENTATION TReportForm : public Forms::TForm
{
	typedef Forms::TForm inherited;
	
__published:
	Virtualtrees::TVirtualStringTree* VirtualStringTree1;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TReportForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TReportForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TReportForm(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TReportForm(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TReportForm* ReportForm;

}	/* namespace Ureportform */
using namespace Ureportform;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UreportformHPP
