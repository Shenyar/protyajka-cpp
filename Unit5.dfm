object Form_dse_report: TForm_dse_report
  Left = 0
  Top = 0
  ActiveControl = DBGridEh1
  Caption = #1044#1057#1045
  ClientHeight = 662
  ClientWidth = 784
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  DesignSize = (
    784
    662)
  PixelsPerInch = 96
  TextHeight = 19
  object Label1: TLabel
    Left = 24
    Top = 11
    Width = 132
    Height = 19
    Caption = #1054#1090#1095#1077#1090' '#1087#1086' '#1044#1057#1045' '#8470':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 162
    Top = 8
    Width = 140
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnKeyDown = Edit1KeyDown
  end
  object Button1: TButton
    Left = 305
    Top = 8
    Width = 95
    Height = 27
    Caption = #1055#1086#1082#1072#1079#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object DBGridEh1: TDBGridEh
    Left = 8
    Top = 41
    Width = 768
    Height = 613
    Anchors = [akLeft, akTop, akRight, akBottom]
    AutoFitColWidths = True
    DataGrouping.Active = True
    DataGrouping.Color = clSkyBlue
    DataGrouping.GroupLevels = <
      item
        ColumnName = 'Column_0_chex'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      item
        ColumnName = 'Column_1_shifr'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end>
    DataGrouping.Footers = <
      item
        Color = clMoneyGreen
        Visible = True
        ColumnItems = <
          item
          end
          item
          end
          item
            DisplayFormat = 'Sum = '
          end
          item
            DisplayFormat = '0.###'
            ValueType = gfvSumEh
          end
          item
          end
          item
            DisplayFormat = '0.###'
            ValueType = gfvSumEh
          end
          item
          end
          item
          end>
        ParentColor = False
        ShowFunctionName = True
      end>
    DataGrouping.ParentColor = False
    DataGrouping.DefaultStateExpanded = True
    DataSource = DataSource1
    DynProps = <>
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    IndicatorOptions = [gioShowRowIndicatorEh]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
    TitleParams.Font.Charset = DEFAULT_CHARSET
    TitleParams.Font.Color = clWindowText
    TitleParams.Font.Height = -16
    TitleParams.Font.Name = 'Tahoma'
    TitleParams.Font.Style = []
    TitleParams.MultiTitle = True
    TitleParams.ParentFont = False
    Columns = <
      item
        DynProps = <>
        EditButtons = <>
        FieldName = 'chex'
        Footers = <>
        Title.Caption = #1062#1077#1093' '#1087#1086#1090#1088#1077#1073#1080#1090#1077#1083#1100
        Visible = False
      end
      item
        DynProps = <>
        EditButtons = <>
        FieldName = 'shifr'
        Footers = <>
        Title.Caption = #1064#1080#1092#1088
        Visible = False
        Width = 150
      end
      item
        DynProps = <>
        EditButtons = <>
        FieldName = 'num_op'
        Footers = <>
        Title.Caption = #8470' '#1086#1087#1077#1088#1072#1094#1080#1080
        Width = 70
      end
      item
        DisplayFormat = '0.###'
        DynProps = <>
        EditButtons = <>
        FieldName = 'norm_l'
        Footers = <>
        Title.Caption = #1053#1086#1088#1084#1099' '#1088#1072#1089#1093#1086#1076#1072' | '#1051
        Width = 70
        WordWrap = False
      end
      item
        DisplayFormat = '0.###'
        DynProps = <>
        EditButtons = <>
        FieldName = 'norm_o'
        Footers = <>
        Title.Caption = #1053#1086#1088#1084#1099' '#1088#1072#1089#1093#1086#1076#1072' | '#1054
        Width = 70
        WordWrap = False
      end
      item
        DisplayFormat = '0.###'
        DynProps = <>
        EditButtons = <>
        FieldName = 'norm'
        Footers = <>
        Title.Caption = #1053#1086#1088#1084#1099' '#1088#1072#1089#1093#1086#1076#1072' | '#1053'./'#1056'.'
        Width = 70
      end
      item
        DisplayFormat = '0.####'
        DynProps = <>
        EditButtons = <>
        FieldName = 'norm_calc'
        Footers = <>
        Title.Caption = #1053#1086#1088#1084#1099' '#1088#1072#1089#1093#1086#1076#1072' | '#1059#1076#1077#1083#1100#1085#1099#1081
        Width = 100
      end
      item
        DynProps = <>
        EditButtons = <>
        FieldName = 'date_drop'
        Footers = <>
        Title.Caption = #1053#1086#1088#1084#1099' '#1088#1072#1089#1093#1086#1076#1072' | '#1057#1088#1086#1082' '#1076#1077#1081#1089#1090#1074#1080#1103
        Width = 100
      end>
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
  object Button2: TButton
    Left = 681
    Top = 8
    Width = 95
    Height = 27
    Caption = #1055#1077#1095#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button2Click
  end
  object DataSource1: TDataSource
    DataSet = MemTableEh1
    Left = 344
    Top = 208
  end
  object ADOQuery1: TADOQuery
    Connection = Form1.ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      
        'SELECT * FROM shifrs INNER JOIN info ON shifrs.id = info.num_shi' +
        'fr'
      'WHERE info.dse = '#39'0780429023'#39';')
    Left = 200
    Top = 208
  end
  object DataSetDriverEh1: TDataSetDriverEh
    ProviderDataSet = ADOQuery1
    Left = 248
    Top = 208
  end
  object MemTableEh1: TMemTableEh
    Params = <>
    DataDriver = DataSetDriverEh1
    OnCalcFields = MemTableEh1CalcFields
    Left = 296
    Top = 208
    object MemTableEh1norm_calc: TFloatField
      FieldKind = fkCalculated
      FieldName = 'norm_calc'
      Calculated = True
    end
    object MemTableEh1number: TFloatField
      FieldName = 'number'
    end
    object MemTableEh1shifr: TWideStringField
      FieldName = 'shifr'
      Size = 50
    end
    object MemTableEh1num_shifr: TIntegerField
      FieldName = 'num_shifr'
    end
    object MemTableEh1chex: TIntegerField
      FieldName = 'chex'
    end
    object MemTableEh1Nlim_kart: TWideStringField
      FieldName = 'Nlim_kart'
      Size = 15
    end
    object MemTableEh1dse: TWideStringField
      FieldName = 'dse'
      Size = 25
    end
    object MemTableEh1marka: TWideStringField
      FieldName = 'marka'
      Size = 25
    end
    object MemTableEh1num_op: TWideStringField
      FieldName = 'num_op'
      Size = 10
    end
    object MemTableEh1Tmax: TWideStringField
      FieldName = 'Tmax'
      Size = 10
    end
    object MemTableEh1kol_mest: TWideStringField
      FieldName = 'kol_mest'
      Size = 10
    end
    object MemTableEh1kol_plast: TWideStringField
      FieldName = 'kol_plast'
      Size = 10
    end
    object MemTableEh1norm_l: TFloatField
      FieldName = 'norm_l'
    end
    object MemTableEh1norm_o: TFloatField
      FieldName = 'norm_o'
    end
    object MemTableEh1norm: TFloatField
      FieldName = 'norm'
    end
    object MemTableEh1stoikost: TWideStringField
      FieldName = 'stoikost'
      Size = 10
    end
    object MemTableEh1Ku: TFloatField
      FieldName = 'Ku'
    end
    object MemTableEh1date_drop: TWideStringField
      FieldName = 'date_drop'
      Size = 40
    end
    object MemTableEh1srok: TDateTimeField
      FieldName = 'srok'
    end
    object MemTableEh1change_date: TDateTimeField
      FieldName = 'change_date'
    end
    object MemTableEh1infoflag: TWordField
      FieldName = 'info.flag'
    end
  end
  object PrintDBGridEh1: TPrintDBGridEh
    DBGridEh = DBGridEh1
    Options = [pghFitGridToPageWidth, pghColored, pghRowAutoStretch]
    Page.BottomMargin = 1.500000000000000000
    Page.LeftMargin = 1.500000000000000000
    Page.RightMargin = 1.500000000000000000
    Page.TopMargin = 1.500000000000000000
    PageFooter.Font.Charset = DEFAULT_CHARSET
    PageFooter.Font.Color = clWindowText
    PageFooter.Font.Height = -11
    PageFooter.Font.Name = 'Tahoma'
    PageFooter.Font.Style = []
    PageHeader.Font.Charset = DEFAULT_CHARSET
    PageHeader.Font.Color = clWindowText
    PageHeader.Font.Height = -16
    PageHeader.Font.Name = 'Tahoma'
    PageHeader.Font.Style = [fsBold]
    Units = MM
    Left = 688
    Top = 536
  end
  object PrintDialog1: TPrintDialog
    Left = 640
    Top = 528
  end
end
