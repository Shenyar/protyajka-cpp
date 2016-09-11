//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAxisGridsEh"
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "DynVarsEh"
#pragma link "EhLibVCL"
#pragma link "GridsEh"
#pragma link "ToolCtrlsEh"
#pragma resource "*.dfm"
TFormKomplect *FormKomplect;
//---------------------------------------------------------------------------
__fastcall TFormKomplect::TFormKomplect(TComponent* Owner)
	: TForm(Owner)
{
	//colored columns
	DBGridEh1->Columns->Items[2]->Color = 0x00C9FCC8;
	DBGridEh1->Columns->Items[3]->Color = 0x00C9FCC8;
	DBGridEh1->Columns->Items[4]->Color = 0x00C8D5FC;
	DBGridEh1->Columns->Items[5]->Color = 0x00C8D5FC;
}
//---------------------------------------------------------------------------
void __fastcall TFormKomplect::Button2Click(TObject *Sender)
{
//discard changes
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormKomplect::Button1Click(TObject *Sender)
{
//accept changes
	AnsiString komplect_new = DBEditKomplect->Text;
	//AnsiString komplect_old = "="+Form2->MemShifrskomplect->AsString;
	if(komplect_new == "") {
		komplect_new = "Null";
	}
	/*if(komplect_old == "=") {
		komplect_old = "Is Null";
	} */
	//change records in 'NR_shifrs'
	Form2->ADOtemp->Close();
	Form2->ADOtemp->SQL->Clear();
	Form2->ADOtemp->SQL->Append("UPDATE NR_shifrs SET NR_shifrs.komplect = " +
		komplect_new + " WHERE (NR_shifrs.shifr_id = " + Form2->MemShifrsid->AsString +
		") ;");
	Form2->ADOtemp->ExecSQL();
	//change records in 'dse'
	Form2->ADOtemp->Close();
	Form2->ADOtemp->SQL->Clear();
	Form2->ADOtemp->SQL->Append("UPDATE dse SET dse.komplect = " +
		komplect_new + " WHERE (dse.shifr_id = " + Form2->MemShifrsid->AsString +
		") ;");
	Form2->ADOtemp->ExecSQL();
	//change records in 'spisanie'
	Form2->ADOtemp->Close();
	Form2->ADOtemp->SQL->Clear();
	Form2->ADOtemp->SQL->Append("UPDATE spisanie SET spisanie.komplect = " +
		komplect_new + " WHERE (spisanie.shifr_id = " + Form2->MemShifrsid->AsString +
		") ;");
	Form2->ADOtemp->ExecSQL();
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormKomplect::FormShow(TObject *Sender)
{
	this->DBEditKomplect->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormKomplect::DBEditEh1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
//accept changes on press enter
	if(Key == 13) {
		Button1Click(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormKomplect::DBGridEh1DblClick(TObject *Sender)
{
//find selected 'komplect' in main table
	Form2->EditKomplect->Text = ADOall_komplect->FieldByName("komplect")->AsString;
	unsigned short key = 13;
	Form2->EditKomplectKeyDown(Sender,key,TShiftState());
	this->Close();
}
//---------------------------------------------------------------------------

