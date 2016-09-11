//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
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
#pragma link "DBCtrlsEh"
#pragma link "DBLookupEh"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
// h = {0 to 360}; s,b = {0 to 100}
int HSBtoRGB(double H, double S, double V)
{
	double red = 0;
	double green = 0;
	double blue = 0;

	if(S == 0)
    {
		red = green = blue = V;
	}
    else
	{
        // цветовой круг состоит из 6 секторов. Выяснить, в каком секторе
		// находится.
		double sectorPos = H / 60.0;
		int sectorNumber = (int)(Math::Floor(sectorPos));
        // получить дробную часть сектора
		double fractionalSector = sectorPos - sectorNumber;

		// вычислить значения для трех осей цвета.
		double Vmin = ((100 - S) * V) / 100;
		double a = (V - Vmin) * fractionalSector;
		double Vinc = Vmin + a;
		double Vdec = V - a;

		// присвоить дробные цвета r, g и b на основании сектора
		// угол равняется.
        switch(sectorNumber)
        {
            case 0:
				red = V;
				green = Vinc;
				blue = Vmin;
                break;
			case 1:
				red = Vdec;
				green = V;
				blue = Vmin;
                break;
            case 2:
				red = Vmin;
				green = V;
				blue = Vinc;
                break;
			case 3:
				red = Vmin;
				green = Vdec;
				blue = V;
                break;
            case 4:
				red = Vinc;
				green = Vmin;
				blue = V;
                break;
            case 5:
				red = V;
				green = Vmin;
				blue = Vdec;
				break;
		}
	}
	red = red/100*256;
	green = green/100*256;
	blue = blue/100*256;

	return ( ((int)blue*256*256) + ((int)green*256) + ((int)red) );
}

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	print = 0;
	//load list of 'chex'
	try{
		ComboBox1->Items->LoadFromFile( ExtractFilePath( Application->ExeName ) + "list.txt" );
	} catch(...) {
		ShowMessage("Список цехов не загружен.\nИспользуется стандартный.");
	}
	//colored columns
	DBGridEh1->Columns->Items[2]->Color = 0x00C9FCC8;
	DBGridEh1->Columns->Items[3]->Color = 0x00C9FCC8;
	DBGridEh1->Columns->Items[4]->Color = 0x00C8D5FC;
	DBGridEh1->Columns->Items[5]->Color = 0x00C8D5FC;
	DBGridInfo->Columns->Items[2]->Color = 0x00FCDDC8;
	DBGridInfo->Columns->Items[3]->Color = 0x00FCDDC8;
	//resize to full window
	this->Resizing(wsMaximized);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TForm2::ADOshifrsCalcFields(TDataSet *DataSet)
{
//calculate record`s number
	MemShifrsnpp->Value = DataSet->RecNo;
	if(MemShifrsnpp->Value == -1) MemShifrsnpp->Value = 1;
	MemShifrslimit_fix->AsFloat = MemShifrslimit->AsFloat + 0.0;
	MemShifrsoborot_fix->AsFloat = MemShifrsoborot->AsFloat + 0.0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ADOshifrsAfterScroll(TDataSet *DataSet)
{
	if(( DBGridEh1->Selection->SelectionType == gstAll ) || ( print == 1 )) return;
//looking for details of the selected shifr
	ADOQueryDse->Close();
	ADOQueryInfo->Close();
	ADOQueryNR->Close();
	if((MemShifrs->State == dsInsert) || (MemShifrs->State == dsEdit)) {
		Label3->Caption = "Информация о шифре :";
		return;
	}
	//condition for 'shifr'
	ADOQueryDse->SQL->Strings[2] = " WHERE (shifr_id = " + MemShifrsid->AsString + ") ";
	ADOQueryInfo->SQL->Strings[2] = " WHERE (shifr_id = " + MemShifrsid->AsString + ") ";
	ADOQueryNR->SQL->Strings[2] = " WHERE (shifr_id = " + MemShifrsid->AsString + ") ";
	//condition for 'komplect'
	/*if( MemShifrskomplect->AsString != "" ) {
		ADOQueryDse->SQL->Strings[3] = " AND (komplect = " + MemShifrskomplect->AsString + ") ";
		ADOQueryInfo->SQL->Strings[3] = " AND (komplect = " + MemShifrskomplect->AsString + ") ";
		ADOQueryNR->SQL->Strings[3] = " AND (komplect = " + MemShifrskomplect->AsString + ") ";
	}
	else {
		ADOQueryDse->SQL->Strings[3] = " AND (komplect Is Null) ";
		ADOQueryInfo->SQL->Strings[3] = " AND (komplect Is Null) ";
		ADOQueryNR->SQL->Strings[3] = " AND (komplect Is Null) ";
	}  */
	//condition for 'chex'
	if( ComboBox1->Text != "Все цеха" ) {
		ADOQueryDse->SQL->Strings[4] = " AND (chex = \'" + ComboBox1->Text + "\') ";
		ADOQueryInfo->SQL->Strings[4] = " AND (chex = \'" + ComboBox1->Text + "\') ";
		ADOQueryNR->SQL->Strings[4] = " AND (chex = \'" + ComboBox1->Text + "\') ";
	}
	else {
		ADOQueryDse->SQL->Strings[4] = " ";
		ADOQueryInfo->SQL->Strings[4] = " ";
		ADOQueryNR->SQL->Strings[4] = " ";
    }
	ADOQueryDse->Open();
	ADOQueryInfo->Open();
	ADOQueryNR->Open();
	Label3->Caption = "Информация о шифре "+MemShifrs->FieldByName("shifr")->AsString+":";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridEh1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumnEh *Column, Gridseh::TGridDrawState State)
{
//move arrow
	if(State.Contains(Gridseh::gdSelected)) Label1->Top = DBGridEh1->Top + Rect.top - 16;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13) {
		//filter by 'shifr'
		MemShifrs->Close();
		Label3->Caption = "Информация о шифре :";
		ADOQueryNR->Close();
		ADOQueryDse->Close();
		ADOQueryInfo->Close();
		if(Edit1->Text == "") {
			ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = "%";
		}
		else {
			ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = Edit1->Text;
		}
		MemShifrs->Open();
		//add 'shifr' if we not finded it
		if( MemShifrs->IsEmpty() && (userRules == 1) && (Edit1->Text != "") ) {
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
					komplect = EditKomplect->Text;
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
void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
//delete filter by 'shifr'
	Edit1->Text = "";
	unsigned short key=13;
	this->Edit1KeyDown(Sender,key,TShiftState());
//delete filter by 'komplect'
	/*EditKomplect->Text = "";
	this->EditKomplectKeyDown(Sender,key,TShiftState()); */
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1Enter(TObject *Sender)
{
	//goto russian charset in field " find 'shifr' "
	LoadKeyboardLayout(L"00000419", KLF_ACTIVATE);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::N4Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ADOQueryInfoAfterInsert(TDataSet *DataSet)
{
	//insert 'shifr_id' into the record
	DataSet->FieldByName("shifr_id")->AsInteger = MemShifrsid->AsInteger;
	//insert 'chex' into the record
	if(ComboBox1->Text == "Все цеха") {
		DataSet->FieldByName("chex")->AsString = "0";
	} else {
		DataSet->FieldByName("chex")->AsString = ComboBox1->Text;
	}
	//insert 'komplect' into the record
	//DataSet->FieldByName("komplect")->AsString = MemShifrskomplect->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridInfoExit(TObject *Sender)
{
//if we go out from the table with 'info' - post all changes
	if((ADOQueryInfo->State == dsInsert) || (ADOQueryInfo->State == dsEdit))
		ADOQueryInfo->Post();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridDseExit(TObject *Sender)
{
//if we go out from the table with 'dse' - post all changes
	if((ADOQueryDse->State == dsInsert) || (ADOQueryDse->State == dsEdit))
		ADOQueryDse->Post();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormResize(TObject *Sender)
{
//resize window with increase width of every table
	float res = this->ClientWidth - 1024;
	DBGridInfo->Width = 274 + res*0.3;
	DBGridInfo->Left = 742 + res*0.7;
	DBGridDse->Width = 130 + res*0.2;
	DBGridDse->Left = 606 + res*0.5;
	DBGridNR->Width = 154 + res*0.1;
	DBGridNR->Left = 446 + res*0.4;
	DBGridEh1->Width = 390 + res*0.4;
	Label1->Left = 398 + res*0.4;
	Label3->Left = 464 + res*0.4;
	DBNavigator4->Left = 454 + res*0.4;
	DBNavigator3->Left = 614 + res*0.5;
	btnCopyDse->Left = 745 + res*0.5;
	btnPasteDse->Left = 777 + res*0.5;
	btnPair->Left = 362 + res*0.4;
	DBNavigator2->Left = 750 + res*0.7;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::N5Click(TObject *Sender)
{
//open form for correcting mistake
	Form3->Edit1->Text = MemShifrsshifr->AsString;
	Form3->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
	//find 'shifrs' for the selected 'chex'
	Label3->Caption = "Информация о шифре :";
	ADOQueryNR->Close();
	ADOQueryDse->Close();
	ADOQueryInfo->Close();
	MemShifrs->Close();
	if(ComboBox1->Text == "Все цеха") {
		ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = "%";
	} else {
		ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = ComboBox1->Text;
	}
	MemShifrs->Open();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridNRExit(TObject *Sender)
{
//if we go out from the table with 'norm' - post all changes
	if((ADOQueryNR->State == dsInsert) || (ADOQueryNR->State == dsEdit))
		ADOQueryNR->Post();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::N6Click(TObject *Sender)
{
	Form7->Memo1->Lines->LoadFromFile(ExtractFilePath( Application->ExeName ) + "list.txt");
	Form7->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnCopyNameClick(TObject *Sender)
{
//copy Main table to clipboard
	DBGridEh1->SetFocus();
	DBGridEh1->Selection->SelectAll();

	keybd_event(VK_CONTROL,0,0,0);
	keybd_event(0x43,0,0,0);
	keybd_event(0x43,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPrintMainClick(TObject *Sender)
{
//print Main table
	if(Form2->PrintDialog1->Execute()) {
		print = 1;
		Printer()->Canvas->Font->Name = "Courier new";
		Printer()->Canvas->Font->Size = 10;
		PrintDBGridEh1->PageHeader->CenterText->Clear();
		PrintDBGridEh1->PageHeader->CenterText->Add("Результативность использования сложнофасонного инструмента в цехe: "+ComboBox1->Text);
		Printer()->Orientation = poPortrait;
		PrintDBGridEh1->Options = TPrintDBGridEhOptions(0x7);
		PrintDBGridEh1->Print();
		print = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::MemShifrsPostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
//on error - cancel record`s changes
	Action = daAbort;
	DataSet->Cancel();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridEh1DblClick(TObject *Sender)
{
//open form for edit 'komplect' of 'shifr'
	FormKomplect->Label1->Caption = "Шифр: " + MemShifrsshifr->AsString;
	//FormKomplect->DBEditKomplect->Text = MemShifrskomplect->AsString;

	//select all 'komplect' where is selected 'shifr'
	FormKomplect->ADOall_komplect->Close();
	FormKomplect->ADOall_komplect->SQL->Strings[15] = " shifrs.shifr = \'"+MemShifrsshifr->AsString+"\' ";
	FormKomplect->ADOall_komplect->SQL->Strings[25] = " shifrs.shifr = \'"+MemShifrsshifr->AsString+"\' ";
	FormKomplect->ADOall_komplect->Open();
	FormKomplect->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ADOQueryNRBeforePost(TDataSet *DataSet)
{
//if no 'limits' discard all changes
	if( (ADOQueryNR->FieldByName("norm_l")->IsNull) && (ADOQueryNR->FieldByName("norm_o")->IsNull) ) {
		DataSet->Cancel();
		return;
    }
//save date when record was changed
	ADOQueryNR->FieldByName("date_in")->AsDateTime = Date();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridNRHintShowPause(TCustomDBGridEh *Sender, TPoint &CursorPos,
          Gridseh::TGridCoord &Cell, TPoint &InCellCursorPos, TColumnEh *Column, int &HintPause,
          bool &Processed)
{
//show in hint when record was changed
	//DBGridNR->Hint = "Дата изменения: "+ADOQueryNR->FieldByName("date_in")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnCopyDseClick(TObject *Sender)
{
//copy all info in 'DSE' table
	DBGridDse->SetFocus();
	if((ADOQueryDse->State == dsInsert) || (ADOQueryDse->State == dsEdit)) {
		ADOQueryDse->Post();
    }
	DBGridDse->Selection->SelectAll();
	keybd_event(VK_CONTROL,0,0,0);
	keybd_event(0x43,0,0,0);
	keybd_event(0x43,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPasteDseClick(TObject *Sender)
{
//copy buffer into 'DSE' table
	DBGridEh1->SetFocus();
	DBGridDse->SetFocus();
	DBGridDse->SelectedIndex = 0;
	ADOQueryDse->Last();
	ADOQueryDse->Insert();
	ADOQueryDse->FieldByName("dse_kod")->AsString = "1";
	ADOQueryDse->Post();
	keybd_event(VK_CONTROL,0,0,0);
	keybd_event(0x56,0,0,0);
	keybd_event(0x56,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::EditKomplectKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13) {
		//filter by 'komplect'
		MemShifrs->Close();
		if(EditKomplect->Text == "") {
		  ADOshifrs->SQL->Strings[18] = " ";
		  ADOshifrs->SQL->Strings[29] = " ";
		}
		else {
		  ADOshifrs->SQL->Strings[18] = " AND (NR_shifrs.komplect = "+EditKomplect->Text+") ";
		  ADOshifrs->SQL->Strings[29] = " AND (spisanie.komplect = "+EditKomplect->Text+") ";
		}
		MemShifrs->Open();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPairClick(TObject *Sender)
{
//join selected 'shifrs' in one pair
	if( DBGridEh1->SelectedRows->Count < 2 ) return;

	double pair = Now().operator double();
	AnsiString pair_str = StringReplace(AnsiString(pair),",",".",TReplaceFlags(rfReplaceAll));
	for(int i=0; i < DBGridEh1->SelectedRows->Count; i++) {
		TDataSet *mem = DBGridEh1->DataSource->DataSet;
		mem->GotoBookmark(DBGridEh1->SelectedRows->Items[i]);
		//unset 'pair' if it`s has value not null
		if(MemShifrspair->AsString != "") {
			pair_str = "Null";
        }
		//set 'pair' to every selected 'shifr'
		ADOtemp->Close();
		ADOtemp->SQL->Clear();
		//AnsiString komplect = "="+MemShifrskomplect->AsString;
		/*if( komplect == "=" ) {
			komplect = "Is Null";
		} */
		AnsiString update = "UPDATE NR_shifrs SET NR_shifrs.pair = "+pair_str+
			" WHERE (NR_shifrs.shifr_id = "+MemShifrsid->AsString+") ;";
		ADOtemp->SQL->Append(update);
		ADOtemp->ExecSQL();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnRefreshClick(TObject *Sender)
{
//recalc 'average' for whole shifrs
	int pos = MemShifrs->RecNo;
	MemShifrs->Close();
	MemShifrs->Open();
	MemShifrs->RecNo = pos;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnComplectClick(TObject *Sender)
{
//calculate next number of 'komplect' for insert new 'shifr'
	ADOtemp->Close();
	ADOtemp->SQL->Clear();
	ADOtemp->SQL->Append("SELECT komplect FROM NR_shifrs ORDER BY komplect DESC;");
	ADOtemp->Open();
	EditKomplect->Text = AnsiString( ADOtemp->FieldByName("komplect")->AsInteger + 1 );
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column,
		  TFont *AFont, TColor &Background, Gridseh::TGridDrawState State)
{
//'shifrs' which have pair are colored
	if( /*(Column->FieldName != "shifr") &&*/ (Column->FieldName != "npp") ) return;
	if( ! MemShifrspair->IsNull ) {
		double id_pair = MemShifrspair->AsFloat * 10000000;
		id_pair -= (int)(id_pair);
		int hue = (id_pair*1000);
		int H = hue % 359;
		Background = HSBtoRGB( H, 29, 98 );
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ADOQueryDseBeforePost(TDataSet *DataSet)
{
	if( ADOQueryDse->FieldByName("dse_kod")->AsString == "" ) {
		DataSet->Cancel();
	} else {
		ADOQueryDse->FieldByName("dse_kod")->AsString = ADOQueryDse->FieldByName("dse_kod")->AsString.Trim();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
//open another information about selected 'shifrs'
	FormInfo->Edit1->Text = this->Edit1->Text;
	FormInfo->Edit_dse->Text = this->Edit_dse->Text;
	FormInfo->ComboBox1->Text = this->ComboBox1->Text;
	FormInfo->Label3->Caption = "Информация о шифре :";
	FormInfo->MemDse->Close();
	FormInfo->MemShifrs->Close();
	if(ComboBox1->Text == "Все цеха") {
		FormInfo->ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = "%";
	} else {
		FormInfo->ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = ComboBox1->Text;
	}
	if( Edit1->Text == "" ) {
		FormInfo->ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = "%";
	} else {
		FormInfo->ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = Edit1->Text;
	}
	if(Edit_dse->Text == "") {
		FormInfo->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = "%";
	} else {
		FormInfo->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = Edit_dse->Text;
	}
	FormInfo->MemShifrs->Open();
	FormInfo->MemShifrs->RecNo = this->MemShifrs->RecNo;
	FormInfo->Show();
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit_dseKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
//filter by 'dse'
	if(Key == 13) {
		MemShifrs->Close();
		Label3->Caption = "Информация о шифре :";
		ADOQueryNR->Close();
		ADOQueryDse->Close();
		ADOQueryInfo->Close();
		if(Edit_dse->Text == "") {
			ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = "%";
		}
		else {
			ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = Edit_dse->Text;
		}
		MemShifrs->Open();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton6Click(TObject *Sender)
{
//delete filter by 'dse'
	Edit_dse->Text = "";
	unsigned short key = 13;
	this->Edit_dseKeyDown(Sender,key,TShiftState());
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DBGridDseDblClick(TObject *Sender)
{
//filter by 'dse' by click on 'dse' in the table
	if( DBGridDse->SelectedIndex == 0 ) {
		Edit_dse->Text = ADOQueryDse->FieldByName("dse_kod")->AsString;
		unsigned short key = 13;
		this->Edit_dseKeyDown(Sender,key,TShiftState());
	}
}
//---------------------------------------------------------------------------
