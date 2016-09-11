//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
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
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include "PrnDbgeh.hpp"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "DBCtrlsEh.hpp"
#include <Vcl.Mask.hpp>
#include "DBLookupEh.hpp"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *ADOshifrs;
	TDBGridEh *DBGridEh1;
	TDataSource *DataSource1;
	TDBNavigator *DBNavigator1;
	TDBNavigator *DBNavigator2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TToolBar *ToolBar1;
	TLabel *Label4;
	TEdit *EditKomplect;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N4;
	TDBGridEh *DBGridDse;
	TDBGridEh *DBGridInfo;
	TADOQuery *ADOQueryDse;
	TDataSource *DataSourceDse;
	TADOQuery *ADOQueryInfo;
	TDataSource *DataSourceInfo;
	TDBNavigator *DBNavigator3;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N5;
	TMenuItem *N6;
	TComboBox *ComboBox1;
	TADOQuery *ADOQueryNR;
	TDataSource *DataSourceNR;
	TDBNavigator *DBNavigator4;
	TDBGridEh *DBGridNR;
	TSpeedButton *btnComplect;
	TSpeedButton *btnCopyName;
	TSpeedButton *btnPrintMain;
	TPrintDialog *PrintDialog1;
	TPrintDBGridEh *PrintDBGridEh1;
	TMemTableEh *MemShifrs;
	TDataSetDriverEh *DataSetDriverEh1;
	TSpeedButton *btnCopyDse;
	TSpeedButton *btnPasteDse;
	TLabel *Label5;
	TEdit *Edit1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *btnPair;
	TADOQuery *ADOtemp;
	TSpeedButton *btnRefresh;
	TButton *Button1;
	TSpeedButton *SpeedButton6;
	TEdit *Edit_dse;
	TLabel *Label6;
	TShape *Shape1;
	TAutoIncField *MemShifrsid;
	TWideStringField *MemShifrsshifr;
	TFloatField *MemShifrspair;
	TFloatField *MemShifrslimit;
	TFloatField *MemShifrsoborot;
	TFloatField *MemShifrsperetochek;
	TFloatField *MemShifrskol_dse;
	TIntegerField *MemShifrsnpp;
	TFloatField *MemShifrslimit_fix;
	TFloatField *MemShifrsoborot_fix;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ADOshifrsCalcFields(TDataSet *DataSet);
	void __fastcall ADOshifrsAfterScroll(TDataSet *DataSet);
	void __fastcall DBGridEh1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumnEh *Column, Gridseh::TGridDrawState State);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Edit1Enter(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall ADOQueryInfoAfterInsert(TDataSet *DataSet);
	void __fastcall DBGridInfoExit(TObject *Sender);
	void __fastcall DBGridDseExit(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall DBGridNRExit(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall btnCopyNameClick(TObject *Sender);
	void __fastcall btnPrintMainClick(TObject *Sender);
	void __fastcall MemShifrsPostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action);
	void __fastcall DBGridEh1DblClick(TObject *Sender);
	void __fastcall ADOQueryNRBeforePost(TDataSet *DataSet);
	void __fastcall DBGridNRHintShowPause(TCustomDBGridEh *Sender, TPoint &CursorPos,
          Gridseh::TGridCoord &Cell, TPoint &InCellCursorPos, TColumnEh *Column, int &HintPause,
          bool &Processed);
	void __fastcall btnCopyDseClick(TObject *Sender);
	void __fastcall btnPasteDseClick(TObject *Sender);
	void __fastcall EditKomplectKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnPairClick(TObject *Sender);
	void __fastcall btnRefreshClick(TObject *Sender);
	void __fastcall btnComplectClick(TObject *Sender);
	void __fastcall DBGridEh1GetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont,
          TColor &Background, Gridseh::TGridDrawState State);
	void __fastcall ADOQueryDseBeforePost(TDataSet *DataSet);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit_dseKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall DBGridDseDblClick(TObject *Sender);







private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	int userRules, print;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
