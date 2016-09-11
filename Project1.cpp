//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Unit7.cpp", Form7);
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit9.cpp", FormInfo);
USEFORM("Unit8.cpp", FormKomplect);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit1.cpp", Form1);
USEFORM("..\(tnadzor)Plastin-RAD-XE5\Unit5.cpp", Form_dse_report);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		//Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->CreateForm(__classid(TForm7), &Form7);
		Application->CreateForm(__classid(TFormKomplect), &FormKomplect);
		Application->CreateForm(__classid(TFormInfo), &FormInfo);
		Application->CreateForm(__classid(TForm_dse_report), &Form_dse_report);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
