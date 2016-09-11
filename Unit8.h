//---------------------------------------------------------------------------

#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DBAxisGridsEh.hpp"
#include "DBCtrlsEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "DynVarsEh.hpp"
#include "EhLibVCL.hpp"
#include "GridsEh.hpp"
#include "ToolCtrlsEh.hpp"
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormKomplect : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TADOQuery *ADOall_komplect;
	TDataSource *DataSource_all_K;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label3;
	TDBGridEh *DBGridEh1;
	TShape *Shape1;
	TEdit *DBEditKomplect;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBEditEh1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEh1DblClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFormKomplect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKomplect *FormKomplect;
//---------------------------------------------------------------------------
#endif
