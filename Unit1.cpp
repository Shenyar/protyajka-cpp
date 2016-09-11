//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

TDateTime FileTimeToDateTime(FILETIME *lpftime)
{
	FILETIME localfiletime;
	SYSTEMTIME systime;
	FileTimeToLocalFileTime(lpftime,&localfiletime);
	FileTimeToSystemTime(&localfiletime,&systime);
	return(TDateTime(systime.wYear, systime.wMonth, systime.wDay,systime.wHour, systime.wMinute,systime.wSecond, systime.wMilliseconds));
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
//connect to database
	UnicodeString op,conn,user,t,newVer,Log,Pass,Serv;
	try {   TIniFile *ini;
		ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
		//connect to server
		Log = ini->ReadString("server","login","");
		Pass = ini->ReadString("server","pass","");
		Serv = ini->ReadString("server","serv_path","");
		if(Log != "") {
			AnsiString command = "net use "+Serv+" "+Pass+" /USER:"+Log;
			system(command.c_str());
		}
		//apply settings
		chex = ini->ReadInteger("info","chex",0);
		user = ini->ReadString("info","user","");
		op = ini->ReadString("path","mdb","");
		t = ini->ReadString("setting","groupColor","");
		if( ! t.IsEmpty() ) {Cgroup = t.ToInt();}
		t = ini->ReadString("setting","footerColor","");
		if( ! t.IsEmpty() ) {Cfooter = t.ToInt();}
        if((op=="") || (!FileExists(op))) throw op;
		newVer = ini->ReadString("path","new_version","");
		if( FileExists(newVer) ) updateProgram(&newVer);//copy new version of program
	} catch(...) {
		if(op.IsEmpty()) {
			ShowMessage("Не указан путь к серверу.");
			Application->Terminate();
		}
		else {
			ShowMessage("Нет файла "+op);
			Application->Terminate();
		}
	}
	conn = "Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=";
	conn += op;
	conn += ";Mode=Share Deny None;Jet OLEDB:System database="";Jet OLEDB:Registry Path=\"\"";
	conn += ";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database ";
	conn += "Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk ";
	conn += "Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False";
	conn += ";Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:";
	conn += "Compact Without Replica Repair=False;Jet OLEDB:SFP=False;";
	this->ADOConnection1->Connected=false;
    this->ADOConnection1->ConnectionString = conn;
	this->ADOConnection1->Connected=true;
    if( !user.IsEmpty() ) {
        Edit1->Text = user;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13) Edit2->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 13) this->Button1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
//test for the correct login and password
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add("select * from users where users.login = \'"+Edit1->Text+"\';");
	ADOQuery1->Open();
	if((ADOQuery1->IsEmpty()) || (ADOQuery1->FieldByName("pass")->AsString != Edit2->Text)) {
		ShowMessage("Неправильно введен логин или пароль.");
		Edit2->Text="";
		return;
	}

	//write login for the next enter in the program
	TIniFile *ini;
	ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
	ini->WriteString("info","user",Edit1->Text);
	delete ini;

//set level of user`s rights
	//read only
	if(( ADOQuery1->FieldByName("rules")->AsString == "0" ))  {
		Form2->DBGridDse->ReadOnly = true;
		Form2->DBGridInfo->ReadOnly = true;
		Form2->DBGridNR->ReadOnly = true;
		Form2->N5->Enabled = false;
		Form2->N6->Enabled = false;
		Form2->DBNavigator2->VisibleButtons = TNavButtonSet(9);
		Form2->DBNavigator3->VisibleButtons = TNavButtonSet(9);
		Form2->DBNavigator4->VisibleButtons = TNavButtonSet(9);
		Form2->DBNavigator2->Width = 62;
		Form2->DBNavigator3->Width = 62;
		Form2->DBNavigator4->Width = 62;
		Form2->btnPasteDse->Enabled = false;
		Form2->userRules = 0;
	} //users of 'БКЭО'
	else {
		Form2->userRules = 1;
	}

//open database with shifrs
	Form2->ComboBox1->ItemIndex = chex;
	Form2->MemShifrs->Close();
	Form2->ADOshifrs->Parameters->ParamByName("[paramShifr]")->Value = "%";
	Form2->ADOshifrs->Parameters->ParamByName("[paramDse]")->Value = "%";
	if(Form2->ComboBox1->Text == "Все цеха") {
		Form2->ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = "%";
	} else {
		Form2->ADOshifrs->Parameters->ParamByName("[paramChex]")->Value = Form2->ComboBox1->Text;
	}
	Form2->MemShifrs->Open();
	Form2->Show();
	this->Hide();
	Form2->DBGridEh1->SetFocus();
}
//---------------------------------------------------------------------------
void TForm1::updateProgram(UnicodeString *newVer)
{
//update new version of file with 'list of chex'
	TWin32FileAttributeData list_old,list_new;
	UnicodeString path_new = ExtractFilePath(newVer->c_str()) + "list.txt";
	UnicodeString path_old = ExtractFilePath(Application->ExeName) + "list.txt";
	//get last write time for both files
	GetFileAttributesEx(path_new.c_str(),GetFileExInfoStandard,&list_new);
	GetFileAttributesEx(path_old.c_str(),GetFileExInfoStandard,&list_old);
	//if we have new version of file with 'list of chex'
	if(FileTimeToDateTime(&list_new.ftLastWriteTime) > FileTimeToDateTime(&list_old.ftLastWriteTime)) {
		//copy new 'list of chex'
		CopyFile(path_new.c_str(),path_old.c_str(),false);
	}

//copy new version of this program
	TWin32FileAttributeData fold,fnew;
	TFileTime ft1;
	TSystemTime st;
	//get last write time for both files
	GetFileAttributesEx(newVer->c_str(),GetFileExInfoStandard,&fnew);
	GetFileAttributesEx(Application->ExeName.c_str(),GetFileExInfoStandard,&fold);
	//if we have new version of our program
	if(FileTimeToDateTime(&fnew.ftLastWriteTime) > FileTimeToDateTime(&fold.ftLastWriteTime)) {
		//copy new version of program
		DeleteFile((Application->ExeName+".bak").c_str());
		RenameFile(Application->ExeName.c_str(),(Application->ExeName+".bak").c_str());
		CopyFile(newVer->c_str(),Application->ExeName.c_str(),false);
		//run new version
		ShellExecute(Handle, L"open", Application->ExeName.c_str(), NULL, NULL, SW_NORMAL);
		Application->Terminate();
	}
}
