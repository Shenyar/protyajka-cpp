//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit5.h"
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
#pragma resource "*.dfm"
TFormInfo *FormInfo;
//---------------------------------------------------------------------------
__fastcall TFormInfo::TFormInfo(TComponent* Owner)
	: TForm(Owner)
{
	//apply color settings
	if(Form1->Cgroup) {
		DBGridEh2->DataGrouping->Color = Form1->Cgroup;
	}
	else {
		DBGridEh2->DataGrouping->Color = clWindow;
	}
	if(Form1->Cfooter) {
		DBGridEh2->DataGrouping->Footers->Items[0]->Color = Form1->Cfooter;
	}
	else {
		DBGridEh2->DataGrouping->Footers->Items[0]->Color = clWindow;
    }

	//load list of 'chex'
	try{
		ComboBox1->Items->LoadFromFile( ExtractFilePath( Application->ExeName ) + "list.txt" );
	} catch(...) {
		ShowMessage("Список цехов не загружен.\nИспользуется стандартный.");
	}
	//resize to full window
	this->Resizing(wsMaximized);

	DBGridShifrs->Columns->Items[2]->Color = 0x00C8D5FC;
	DBGridShifrs->Columns->Items[3]->Color = 0x00C8D5FC;
	DBGridEh2->Columns->Items[10]->Color = 0xffe4ff;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::N4Click(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::MemShifrsCalcFields(TDataSet *DataSet)
{
	MemShifrsnpp->Value = MemShifrs->RecNo;
	MemShifrss_norm_l->Value = MemShifrslimit->AsFloat + 0.0;
	MemShifrss_norm_o->Value = MemShifrsoborot->AsFloat + 0.0;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::MemShifrsAfterScroll(TDataSet *DataSet)
{
//looking for dse of the selected shifr
	MemDse->Close();
	ADOdse->SQL->Strings[1] = "WHERE (dse.shifr_id = "+MemShifrsid->AsString+") ";
	if(ComboBox1->Text == "Все цеха") {
		ADOdse->SQL->Strings[2] = " ";
	} else {
		ADOdse->SQL->Strings[2] = " AND (dse.chex = \'"+ComboBox1->Text+"\') ";
	}
	if( DBGridEh2->DataGrouping->Active ) {
		ADOdse->SQL->Strings[3] = " ORDER BY dse.chex, dse.dse_kod, dse.num_op;";
	}
	else {
		ADOdse->SQL->Strings[3] = " ORDER BY dse.id;";
    }
	MemDse->Open();
	Label3->Caption = "Информация о шифре "+MemShifrs->FieldByName("shifr")->AsString+":";
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::Button2Click(TObject *Sender)
{
//open another information about selected 'shifrs'
	Form2->Edit1->Text = this->Edit1->Text;
	Form2->Edit_dse->Text = this->Edit_dse->Text;
	Form2->ComboBox1->Text = this->ComboBox1->Text;
	Form2->Label3->Caption = "Информация о шифре :";
	Form2->ADOQueryNR->Close();
	Form2->ADOQueryDse->Close();
	Form2->ADOQueryInfo->Close();
	Form2->MemShifrs->Close();
	if(ComboBox1->Text == "Все цеха") {
		Form2->ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = "%";
	} else {
		Form2->ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = ComboBox1->Text;
	}
	if( Edit1->Text == "" ) {
		Form2->ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = "%";
	} else {
		Form2->ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = Edit1->Text;
	}
	if(Edit_dse->Text == "") {
		Form2->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = "%";
	} else {
		Form2->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = Edit_dse->Text;
	}
	Form2->MemShifrs->Open();
	Form2->MemShifrs->RecNo = this->MemShifrs->RecNo;
	Form2->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::FormClose(TObject *Sender, TCloseAction &Action)
{
//close programm
	TIniFile *ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
	ini->WriteInteger("info","chex",ComboBox1->ItemIndex);
	delete ini;
	MemShifrs->Close();
	Form1->ADOConnection1->Close();
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::ComboBox1Change(TObject *Sender)
{
	//find 'shifrs' for the selected 'chex'
	Label3->Caption = "Информация о шифре :";
	MemDse->Close();
	MemShifrs->Close();
	if(ComboBox1->Text == "Все цеха") {
		ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = "%";
	} else {
		ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = ComboBox1->Text;
	}
	MemShifrs->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13) {
		//filter by 'shifr'
		MemShifrs->Close();
		Label3->Caption = "Информация о шифре :";
		MemDse->Close();
		if(Edit1->Text == "") {
			ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = "%";
		} else {
			ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = Edit1->Text;
		}
		MemShifrs->Open();
		//add 'shifr' if we not finded it
		if( MemShifrs->IsEmpty() && (Form2->userRules == 1) && (Edit1->Text != "") ) {
			if(IDYES == Application->MessageBox(L"Данный шифр не найден. Добавить его?", L"Добавление", MB_YESNO)) {
				ADOtemp->Close();
				ADOtemp->SQL->Clear();
				ADOtemp->SQL->Append("SELECT * FROM shifrs WHERE shifr=\'"+Edit1->Text+"\';");
				ADOtemp->Open();
				if( ADOtemp->IsEmpty() ) {
					//add 'shifr'
					ADOtemp->Close();
					ADOtemp->SQL->Clear();
					ADOtemp->SQL->Append("INSERT INTO shifrs (shifr) VALUES (\'"+Edit1->Text+"\');");
					ADOtemp->ExecSQL();
					//find 'id' of the added 'shifr'
					ADOtemp->Close();
					ADOtemp->SQL->Clear();
					ADOtemp->SQL->Append("SELECT id FROM shifrs WHERE shifr = \'"+Edit1->Text+"\';");
					ADOtemp->Open();
				}
				AnsiString shifr_id = ADOtemp->FieldByName("id")->AsString,
					chex = ComboBox1->Text,
					komplect = Form2->EditKomplect->Text;
				if(komplect == "") {
                    komplect = "Null";
				}
				if(chex == "Все цеха") {
					chex = "0";
				}
				//add info about 'shifr' in table 'NR_shifrs'
				ADOtemp->Close();
				ADOtemp->SQL->Clear();
				ADOtemp->SQL->Append("INSERT INTO NR_shifrs (shifr_id, komplect, chex) VALUES ("+
					shifr_id+", "+komplect+", \'"+chex+"\');");
				ADOtemp->ExecSQL();
				//add info about 'shifr' in table 'dse'
				ADOtemp->Close();
				ADOtemp->SQL->Clear();
				ADOtemp->SQL->Append("INSERT INTO dse (shifr_id, komplect, chex) VALUES ("+
					shifr_id+", "+komplect+", \'"+chex+"\');");
				ADOtemp->ExecSQL();
				unsigned short key = 13;
				Edit1KeyDown( Sender,key,TShiftState() );
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::SpeedButton1Click(TObject *Sender)
{
//delete filter by 'shifr'
	Edit1->Text = "";
	unsigned short key=13;
	this->Edit1KeyDown(Sender,key,TShiftState());
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::btnRefreshClick(TObject *Sender)
{
//recalc 'sum' for whole shifrs
	int pos = MemShifrs->RecNo;
	MemShifrs->Close();
	MemShifrs->Open();
	MemShifrs->RecNo = pos;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::Button1Click(TObject *Sender)
{
//on/off grouping in the table
	if(DBGridEh2->DataGrouping->Active == true) {
		DBGridEh2->DataGrouping->Active = false;
		Button1->Caption = "Группировка :Вкл";
		DBGridEh2->Columns->Items[0]->HideDuplicates = false;
		DBGridEh2->Columns->Items[1]->HideDuplicates = false;
		DBGridEh2->Columns->Items[2]->HideDuplicates = false;
		this->MemShifrsAfterScroll(DataSource1->DataSet);
	}
	else {
		DBGridEh2->DataGrouping->Active = true;
		Button1->Caption = "Группировка :Выкл";
		DBGridEh2->Columns->Items[0]->HideDuplicates = true;
		DBGridEh2->Columns->Items[1]->HideDuplicates = true;
		DBGridEh2->Columns->Items[2]->HideDuplicates = true;
		this->MemShifrsAfterScroll(DataSource1->DataSet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::Edit1Enter(TObject *Sender)
{
	//goto russian charset in field " find 'shifr' "
	LoadKeyboardLayout(L"00000419", KLF_ACTIVATE);
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::N7Click(TObject *Sender)
{
//color for 'groups'
	if(ColorDialog1->Execute()) {
		Form1->Cgroup = ColorDialog1->Color;
		DBGridEh2->DataGrouping->Color = ColorDialog1->Color;
	}
	//save to setting file
	TIniFile *ini;
	ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
	ini->WriteInteger("setting","groupColor",Form1->Cgroup);
	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::N8Click(TObject *Sender)
{
//color for 'sum'
	if(ColorDialog1->Execute()) {
		Form1->Cfooter = ColorDialog1->Color;
		DBGridEh2->DataGrouping->Footers->Items[0]->Color = ColorDialog1->Color;
	}
	//save to setting file
	TIniFile *ini;
	ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
	ini->WriteInteger("setting","footerColor",Form1->Cfooter);
	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::N10Click(TObject *Sender)
{
	Form_dse_report->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::Edit_dseKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
//filter by 'dse'
	if(Key == 13) {
		MemShifrs->Close();
		Label3->Caption = "Информация о шифре :";
		MemDse->Close();
		if(Edit_dse->Text == "") {
			FormInfo->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = "%";
		} else {
			FormInfo->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = Edit_dse->Text;
		}
		MemShifrs->Open();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::SpeedButton6Click(TObject *Sender)
{
//delete filter by 'dse'
	Edit_dse->Text = "";
	unsigned short key = 13;
	this->Edit_dseKeyDown(Sender,key,TShiftState());
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::DBGridEh2DblClick(TObject *Sender)
{
//filter by 'dse' by click on 'dse' in the table
	if( DBGridEh2->SelectedIndex == 2 ) {
		Edit_dse->Text = MemDsedse_kod->AsString;
		unsigned short key = 13;
		this->Edit_dseKeyDown(Sender,key,TShiftState());
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::MemDseAfterInsert(TDataSet *DataSet)
{
	//insert 'shifr_id' into the record
	DataSet->FieldByName("shifr_id")->AsInteger = MemShifrsid->AsInteger;
	//insert 'chex' into the record
	if(ComboBox1->Text == "Все цеха") {
		DataSet->FieldByName("chex")->AsString = "0";
	} else {
		DataSet->FieldByName("chex")->AsString = ComboBox1->Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::MemDseBeforePost(TDataSet *DataSet)
{
//field 'dse_kod' is required
	if(MemDsedse_kod->AsString == "") {
		MemDseshifr_id->AsString = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::MemDsePostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
//on error - cancel record`s changes
	Action = daAbort;
	DataSet->Cancel();
}
//---------------------------------------------------------------------------


void __fastcall TFormInfo::btnCopyDseClick(TObject *Sender)
{
//copy all info in 'DSE' table
	DBGridEh2->SetFocus();
	if((MemDse->State == dsInsert) || (MemDse->State == dsEdit)) {
		MemDse->Post();
	}
	DBGridEh2->Selection->SelectAll();
	keybd_event(VK_CONTROL,0,0,0);
	keybd_event(0x43,0,0,0);
	keybd_event(0x43,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::btnPasteDseClick(TObject *Sender)
{
//copy buffer into 'DSE' table
	DBGridShifrs->SetFocus();
	DBGridEh2->SetFocus();
	DBGridEh2->SelectedIndex = 0;
	MemDse->Last();
	MemDse->Insert();
	MemDse->FieldByName("dse_kod")->AsString = "1";
	MemDse->Post();
	keybd_event(VK_CONTROL,0,0,0);
	keybd_event(0x56,0,0,0);
	keybd_event(0x56,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::DBGridEh2MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	this->tmp_copy = DBGridEh2->SelectedField->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::DBGridEh2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(DBGridEh2->SelectedField->AsString != this->tmp_copy) {
		if((MemDse->State != dsInsert) || (MemDse->State != dsEdit)) {
			MemDse->Edit();
		}
		DBGridEh2->SelectedField->AsString = this->tmp_copy;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::DBGridEh2GetCellParams(TObject *Sender, TColumnEh *Column,
		  TFont *AFont, TColor &Background, Gridseh::TGridDrawState State)
{
//if instrument has lifetime - it will be colored
	if( !MemDsesrok->AsString.IsEmpty() ) {
		if( MemDsesrok->AsDateTime > Date() )
			Background = 0xFFE4FF;
		else
			Background = 0x8F95FE;
	}
//if instrument is disable - colored grey
	if( MemDsedate_drop->AsString == "" ) return;
	if( MemDsedate_drop->AsString[1] == '-' ) {
		Background = 0xCCCCCC;
    }
}
//---------------------------------------------------------------------------

