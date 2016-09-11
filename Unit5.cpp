//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DataDriverEh"
#pragma link "DBAxisGridsEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "DBGridEhToolCtrls"
#pragma link "DynVarsEh"
#pragma link "EhLibVCL"
#pragma link "GridsEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "ToolCtrlsEh"
#pragma link "PrnDbgeh"
#pragma resource "*.dfm"
TForm_dse_report *Form_dse_report;
//---------------------------------------------------------------------------
__fastcall TForm_dse_report::TForm_dse_report(TComponent* Owner)
	: TForm(Owner)
{
	//applying settings
	if(Form1->Cgroup)	DBGridEh1->DataGrouping->Color = Form1->Cgroup;
	else DBGridEh1->DataGrouping->Color = clWindow;
	if(Form1->Cfooter) DBGridEh1->DataGrouping->Footers->Items[0]->Color = Form1->Cfooter;
	else DBGridEh1->DataGrouping->Footers->Items[0]->Color = clWindow;

	this->DBGridEh1->DataGrouping->Footers->Items[0]->Color = 0xFFE4FF;
}
//---------------------------------------------------------------------------
void __fastcall TForm_dse_report::Button1Click(TObject *Sender)
{
	this->MemTableEh1->Close();
	this->ADOQuery1->SQL->Strings[1] = "WHERE info.dse = \'"+Edit1->Text+"\';";
	this->MemTableEh1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TForm_dse_report::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13) {
		this->Button1Click(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_dse_report::MemTableEh1CalcFields(TDataSet *DataSet)
{
	//autocalculate 'limits if detail'
	if( (MemTableEh1->FieldByName("Tmax")->AsString != "") &&
		(MemTableEh1->FieldByName("stoikost")->AsString != "") &&
		(MemTableEh1->FieldByName("Ku")->AsString != "") ) {
			float Tmax, stoikost, Ku;
			Ku = MemTableEh1->FieldByName("Ku")->AsFloat;
			try{
				Tmax = StringReplace(MemTableEh1->FieldByName("Tmax")->AsString,".",",",TReplaceFlags()<<rfReplaceAll).ToDouble();
				stoikost = StringReplace(MemTableEh1->FieldByName("stoikost")->AsString,".",",",TReplaceFlags()<<rfReplaceAll).ToDouble();
			}
			catch(EConvertError &e) {
				try{
					//if we have '.' -> replace this on ','
					Tmax = StringReplace(MemTableEh1->FieldByName("Tmax")->AsString,",",".",TReplaceFlags()<<rfReplaceAll).ToDouble();
					stoikost = StringReplace(MemTableEh1->FieldByName("stoikost")->AsString,",",".",TReplaceFlags()<<rfReplaceAll).ToDouble();
				}
				catch(...) {
					ShowMessage("��������� ���� ����, ���������, ��\n��� ������ ���� ������ �����");
					return;
				}
			}
			float calc = Tmax;
			calc /= (60 * stoikost);
			calc *= Ku;
			MemTableEh1->FieldByName("norm_calc")->AsFloat = calc;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_dse_report::Button2Click(TObject *Sender)
{
//print
	if(PrintDialog1->Execute()) {
        Printer()->Canvas->Font->Name = "Courier new";
		Printer()->Canvas->Font->Size = 10;
		Printer()->Orientation = poPortrait;
		PrintDBGridEh1->PageHeader->CenterText->Clear();
		PrintDBGridEh1->PageHeader->CenterText->Add("����� �� ���: "+Edit1->Text);
		PrintDBGridEh1->Print();
    }
}
//---------------------------------------------------------------------------

