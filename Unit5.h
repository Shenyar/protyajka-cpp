//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DataDriverEh.hpp"
#include "DBAxisGridsEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "DBGridEhToolCtrls.hpp"
#include "DynVarsEh.hpp"
#include "EhLibVCL.hpp"
#include "GridsEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include "ToolCtrlsEh.hpp"
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include "PrnDbgeh.hpp"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm_dse_report : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
	TDBGridEh *DBGridEh1;
	TDataSource *DataSource1;
	TADOQuery *ADOQuery1;
	TDataSetDriverEh *DataSetDriverEh1;
	TMemTableEh *MemTableEh1;
	TFloatField *MemTableEh1norm_calc;
	TFloatField *MemTableEh1number;
	TWideStringField *MemTableEh1shifr;
	TIntegerField *MemTableEh1num_shifr;
	TIntegerField *MemTableEh1chex;
	TWideStringField *MemTableEh1Nlim_kart;
	TWideStringField *MemTableEh1dse;
	TWideStringField *MemTableEh1marka;
	TWideStringField *MemTableEh1num_op;
	TWideStringField *MemTableEh1Tmax;
	TWideStringField *MemTableEh1kol_mest;
	TWideStringField *MemTableEh1kol_plast;
	TFloatField *MemTableEh1norm_l;
	TFloatField *MemTableEh1norm_o;
	TFloatField *MemTableEh1norm;
	TWideStringField *MemTableEh1stoikost;
	TFloatField *MemTableEh1Ku;
	TWideStringField *MemTableEh1date_drop;
	TDateTimeField *MemTableEh1srok;
	TDateTimeField *MemTableEh1change_date;
	TWordField *MemTableEh1infoflag;
	TButton *Button2;
	TPrintDBGridEh *PrintDBGridEh1;
	TPrintDialog *PrintDialog1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MemTableEh1CalcFields(TDataSet *DataSet);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_dse_report(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_dse_report *Form_dse_report;
//---------------------------------------------------------------------------
#endif
