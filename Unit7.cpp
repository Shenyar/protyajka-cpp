//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button2Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1Click(TObject *Sender)
{
//apply changes in the list of 'chex'
	Memo1->Lines->SaveToFile(ExtractFilePath( Application->ExeName ) + "list.txt");
	Form2->ComboBox1->Items->LoadFromFile(ExtractFilePath( Application->ExeName ) + "list.txt");
	Form2->ComboBox1->ItemIndex = 0;
	this->Close();
}
//---------------------------------------------------------------------------
