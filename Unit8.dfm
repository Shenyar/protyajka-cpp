object FormKomplect: TFormKomplect
  Left = 0
  Top = 0
  Caption = #1050#1086#1084#1087#1083#1077#1082#1090#1099' '#1096#1080#1092#1088#1086#1074
  ClientHeight = 662
  ClientWidth = 585
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  DesignSize = (
    585
    662)
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 192
    Height = 23
    Caption = #1064#1080#1092#1088': '#1059'6215-1598'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 37
    Width = 209
    Height = 23
    Caption = #1054#1090#1085#1086#1089#1080#1090#1089#1103' '#1082' '#1082#1086#1084#1087#1083#1077#1082#1090#1091':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 143
    Width = 527
    Height = 23
    Caption = #1055#1077#1088#1077#1095#1077#1085#1100' '#1082#1086#1084#1087#1083#1077#1082#1090#1086#1074' '#1074' '#1082#1086#1090#1086#1088#1099#1093' '#1077#1089#1090#1100' '#1076#1072#1085#1085#1099#1081' '#1096#1080#1092#1088':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Shape1: TShape
    Left = 0
    Top = 124
    Width = 585
    Height = 2
    Anchors = [akLeft, akTop, akRight]
  end
  object Button1: TButton
    Left = 176
    Top = 80
    Width = 113
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 296
    Top = 80
    Width = 113
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 1
    OnClick = Button2Click
  end
  object DBGridEh1: TDBGridEh
    Left = 8
    Top = 172
    Width = 569
    Height = 483
    AllowedSelections = [gstAll]
    Anchors = [akLeft, akTop, akRight, akBottom]
    AutoFitColWidths = True
    DataGrouping.Active = True
    DataGrouping.GroupLevels = <
      item
      end>
    DataSource = DataSource_all_K
    DynProps = <>
    EditActions = [geaCopyEh, geaSelectAllEh]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    IndicatorOptions = [gioShowRowIndicatorEh]
    Options = [dgEditing, dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    OptionsEh = [dghFixed3D, dghHighlightFocus, dghClearSelection, dghAutoSortMarking, dghEnterAsTab, dghRowHighlight, dghDialogFind, dghColumnResize, dghExtendVertLines]
    ParentFont = False
    ReadOnly = True
    SortLocal = True
    TabOrder = 2
    TitleParams.Font.Charset = DEFAULT_CHARSET
    TitleParams.Font.Color = clWindowText
    TitleParams.Font.Height = -13
    TitleParams.Font.Name = 'Tahoma'
    TitleParams.Font.Style = [fsBold]
    TitleParams.MultiTitle = True
    TitleParams.ParentFont = False
    VertScrollBar.VisibleMode = sbAlwaysShowEh
    OnDblClick = DBGridEh1DblClick
    Columns = <
      item
        DynProps = <>
        EditButtons = <>
        EndEllipsis = True
        FieldName = 'komplect'
        Footers = <>
        Title.Caption = #1050#1086#1084#1087#1083#1077#1082#1090
        Width = 100
      end
      item
        DynProps = <>
        EditButtons = <>
        EndEllipsis = True
        FieldName = 'shifr'
        Footers = <>
        Title.Caption = #1064#1080#1092#1088
        Title.TitleButton = True
        Width = 150
      end
      item
        DisplayFormat = '0.##'
        DynProps = <>
        EditButtons = <>
        EndEllipsis = True
        FieldName = 'a_kol_pere'
        Footers = <>
        Title.Caption = #1057#1088#1077#1076#1085#1077#1077' '#1091#1076#1077#1083#1100#1085#1086#1077' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086', '#1096#1090'. |'#1055#1077#1088#1077#1090#1086#1095#1077#1082
        Width = 80
      end
      item
        DisplayFormat = '0.##'
        DynProps = <>
        EditButtons = <>
        EndEllipsis = True
        FieldName = 'a_dse_obr'
        Footers = <>
        Title.Caption = #1057#1088#1077#1076#1085#1077#1077' '#1091#1076#1077#1083#1100#1085#1086#1077' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086', '#1096#1090'. |'#1044#1057#1045
        Width = 80
      end
      item
        DisplayFormat = '0.##'
        DynProps = <>
        EditButtons = <>
        EndEllipsis = True
        FieldName = 's_norm_l'
        Footers = <>
        Title.Caption = 'H./P.|'#1051
        Width = 60
      end
      item
        DisplayFormat = '0.##'
        DynProps = <>
        EditButtons = <>
        EndEllipsis = True
        FieldName = 's_norm_o'
        Footers = <>
        Title.Caption = 'H./P.|'#1054
        Width = 60
      end>
    object RowDetailData: TRowDetailPanelControlEh
    end
  end
  object DBEditKomplect: TEdit
    Left = 223
    Top = 34
    Width = 142
    Height = 31
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Text = 'DBEditKomplect'
    OnKeyDown = DBEditEh1KeyDown
  end
  object ADOall_komplect: TADOQuery
    Connection = Form1.ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'SELECT  s_sum.id,'
      #9's_sum.shifr,'
      #9's_sum.komplect,'
      #9's_sum.s_norm_l,'
      #9's_sum.s_norm_o,'
      #9's_avg.a_kol_pere,'
      #9's_avg.a_dse_obr'
      'FROM ('
      #9'SELECT  shifrs.id,'
      #9#9'shifrs.shifr,'
      #9#9'NR_shifrs.komplect,'
      #9#9'Sum(NR_shifrs.norm_l) AS s_norm_l,'
      #9#9'Sum(NR_shifrs.norm_o) AS s_norm_o'
      
        #9'FROM shifrs INNER JOIN NR_shifrs ON (shifrs.id = NR_shifrs.shif' +
        'r_id)'
      #9'WHERE'
      '    (shifrs.shifr = '#39'U123'#39')'
      
        #9'GROUP BY shifrs.id, shifrs.shifr, NR_shifrs.komplect, NR_shifrs' +
        '.pair'
      #9') AS s_sum'
      'LEFT JOIN ('
      #9'SELECT  shifrs.id,'
      '    spisanie.komplect,'
      #9#9'Avg(spisanie.kol_pere) AS a_kol_pere,'
      #9#9'Avg(spisanie.dse_obr) AS a_dse_obr'
      
        #9'FROM shifrs INNER JOIN spisanie ON (shifrs.id = spisanie.shifr_' +
        'id)'
      '  WHERE'
      '    (shifrs.shifr = '#39'U123'#39')'
      #9'GROUP BY shifrs.id, spisanie.komplect'
      #9') AS s_avg'
      'ON ('
      '  (s_sum.id = s_avg.id)'
      '  AND'
      '  ('
      '    (s_sum.komplect = s_avg.komplect)'
      '    OR'
      '    ( (s_avg.komplect Is Null) AND (s_sum.komplect Is Null))'
      '  )'
      ')'
      'ORDER BY s_sum.komplect;')
    Left = 160
    Top = 351
  end
  object DataSource_all_K: TDataSource
    DataSet = ADOall_komplect
    Left = 248
    Top = 351
  end
end
