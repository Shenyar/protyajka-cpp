//---------------------------------------------------------------------------

#ifndef Unit9H
#define Unit9H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
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
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormInfo : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label5;
	TEdit *Edit1;
	TSpeedButton *SpeedButton1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N4;
	TMenuItem *N2;
	TMenuItem *N5;
	TMenuItem *N3;
	TMenuItem *N6;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *ComboBox1;
	TADOQuery *ADOshifrs;
	TDataSource *DataSource1;
	TMemTableEh *MemShifrs;
	TDataSetDriverEh *DataSetDriverEh1;
	TDBGridEh *DBGridShifrs;
	TDBNavigator *DBNavigator1;
	TShape *Shape2;
	TButton *Button1;
	TLabel *Label3;
	TDBGridEh *DBGridEh2;
	TDBNavigator *DBNavigator2;
	TDataSource *DataSource2;
	TMemTableEh *MemDse;
	TDataSetDriverEh *DataSetDriverEh2;
	TADOQuery *ADOdse;
	TAutoIncField *MemDseid;
	TIntegerField *MemDseshifr_id;
	TIntegerField *MemDsekomplect;
	TWideStringField *MemDsechex;
	TWideStringField *MemDseNlim_kart;
	TWideStringField *MemDsedse_kod;
	TWideStringField *MemDsenum_op;
	TWideStringField *MemDseTmax;
	TWideStringField *MemDsekol_mest;
	TWideStringField *MemDsekol_plast;
	TWideStringField *MemDsemarka;
	TFloatField *MemDsenorm_l;
	TFloatField *MemDsenorm_o;
	TDateTimeField *MemDsesrok;
	TWideStringField *MemDsestoikost;
	TFloatField *MemDseKu;
	TWideStringField *MemDseact;
	TWideStringField *MemDsedate_drop;
	TWideStringField *MemDsenew_plast;
	TDateTimeField *MemDsechange_date;
	TButton *Button2;
	TSpeedButton *btnRefresh;
	TADOQuery *ADOtemp;
	TColorDialog *ColorDialog1;
	TMenuItem *N7;
	TMenuItem *N8;
	TSpeedButton *SpeedButton6;
	TEdit *Edit_dse;
	TLabel *Label6;
	TShape *Shape1;
	TMenuItem *N9;
	TMenuItem *N10;
	TAutoIncField *MemShifrsid;
	TWideStringField *MemShifrsshifr;
	TFloatField *MemShifrslimit;
	TFloatField *MemShifrsoborot;
	TIntegerField *MemShifrsnpp;
	TFloatField *MemShifrss_norm_l;
	TFloatField *MemShifrss_norm_o;
	TSpeedButton *btnCopyDse;
	TSpeedButton *btnPasteDse;
	void __fastcall N4Click(TObject *Sender);
	void __fastcall MemShifrsCalcFields(TDataSet *DataSet);
	void __fastcall MemShifrsAfterScroll(TDataSet *DataSet);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall btnRefreshClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1Enter(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall Edit_dseKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall DBGridEh2DblClick(TObject *Sender);
	void __fastcall MemDseAfterInsert(TDataSet *DataSet);
	void __fastcall MemDseBeforePost(TDataSet *DataSet);
	void __fastcall MemDsePostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action);
	void __fastcall btnCopyDseClick(TObject *Sender);
	void __fastcall btnPasteDseClick(TObject *Sender);
	void __fastcall DBGridEh2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DBGridEh2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DBGridEh2GetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
		  TColor &Background, Gridseh::TGridDrawState State);




private:	// User declarations
public:		// User declarations
	__fastcall TFormInfo(TComponent* Owner);
	UnicodeString tmp_copy;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInfo *FormInfo;
//---------------------------------------------------------------------------
#endif
