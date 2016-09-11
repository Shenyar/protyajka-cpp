//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
//save changes
	Form2->ADOshifrs->Edit();
	Form2->ADOshifrs->FieldByName("shifr")->AsString = Edit1->Text;
	Form2->ADOshifrs->Post();
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
//cancel changes
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
//save changes on 'enter'
	if(Key == VK_RETURN) this->Button1Click(Sender);
}
//---------------------------------------------------------------------------
