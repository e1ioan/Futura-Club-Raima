//--------------------------------------------------------
// TKCHART1.H generated from TKCHART.VBX by
// VbxGen 1.0 - Borland International
//--------------------------------------------------------

#ifdef __OWL_OWLDEFS_H
  #include <owl\vbxctl.h>
#endif

//--------------------------------------------------------
// TKChart (VB2)
//--------------------------------------------------------

// properties
#define Prop_TKChart_CtlName 0
#define Prop_TKChart_Index 1
#define Prop_TKChart_Left 2
#define Prop_TKChart_Top 3
#define Prop_TKChart_Width 4
#define Prop_TKChart_Height 5
#define Prop_TKChart_Visible 6
#define Prop_TKChart_DragMode 7
#define Prop_TKChart_DragIcon 8
#define Prop_TKChart_Tag 9
#define Prop_TKChart_TabIndex 10
#define Prop_TKChart_TabStop 11
#define Prop_TKChart_FontBold 12
#define Prop_TKChart_FontItalic 13
#define Prop_TKChart_FontStrikethru 14
#define Prop_TKChart_FontUnderline 15
#define Prop_TKChart_FontSize 16
#define Prop_TKChart_FontName 17
#define Prop_TKChart_DataType 18
#define Prop_TKChart_AppSendTimer 19
#define Prop_TKChart_DataStart 20
#define Prop_TKChart_MaxCache 21
#define Prop_TKChart_TotalData 22
#define Prop_TKChart_cElement 23
#define Prop_TKChart_ChartType 24
#define Prop_TKChart_iMinVal 25
#define Prop_TKChart_iIncVal 26
#define Prop_TKChart_lMinVal 27
#define Prop_TKChart_lIncVal 28
#define Prop_TKChart_dMinVal 29
#define Prop_TKChart_dIncVal 30
#define Prop_TKChart_Division 31
#define Prop_TKChart_LabelType 32
#define Prop_TKChart_zLabelArr 33
#define Prop_TKChart_xGapStyle 34
#define Prop_TKChart_xIndex 35
#define Prop_TKChart_ChartConfig 36
#define Prop_TKChart_AxisConfig 37
#define Prop_TKChart_iDataArr 38
#define Prop_TKChart_lDataArr 39
#define Prop_TKChart_dDataArr 40
#define Prop_TKChart_AddData 41
#define Prop_TKChart_xLabel 42
#define Prop_TKChart_AxisStyle 43
#define Prop_TKChart_GetDataCount 44
#define Prop_TKChart_SetElementColorArr 45
#define Prop_TKChart_ProjectStyle 46
#define Prop_TKChart_BrushPatternArr 47
#define Prop_TKChart_GridColor 48
#define Prop_TKChart_BorderColor 49
#define Prop_TKChart_LegendAlign 50
#define Prop_TKChart_InsertData 51
#define Prop_TKChart_DeleteData 52
#define Prop_TKChart_DeleteAllData 53
#define Prop_TKChart_ReadData 54
#define Prop_TKChart_WriteData 55
#define Prop_TKChart_GetCachedDataCount 56
#define Prop_TKChart_GetFirstDataCached 57
#define Prop_TKChart_TitleArr 58
#define Prop_TKChart_yMinMax 59
#define Prop_TKChart_PiePosArr 60
#define Prop_TKChart_iMin 61
#define Prop_TKChart_iMax 62
#define Prop_TKChart_lMin 63
#define Prop_TKChart_lMax 64
#define Prop_TKChart_dMin 65
#define Prop_TKChart_dMax 66
#define Prop_TKChart_AxisIndex 67
#define Prop_TKChart_ColorArr 68
#define Prop_TKChart_ChTimer 69
#define Prop_TKChart_SelfRotate 70
#define Prop_TKChart_Redraw 71
#define Prop_TKChart_Rotate 72
#define Prop_TKChart_CopyChart 73
#define Prop_TKChart_iNeedDataArr 74
#define Prop_TKChart_lNeedDataArr 75
#define Prop_TKChart_dNeedDataArr 76
#define Prop_TKChart_NeedDataxLabel 77
#define Prop_TKChart_GetElementColorArr 78
#define Prop_TKChart_GetAxisConfig 79
#define Prop_TKChart_BkColor 80
#define Prop_TKChart_Parent 81
#define Prop_TKChart_DBFrontEnd 82
#define Prop_TKChart_AutoAdjOrigin 83
#define Prop_TKChart_OwnerSupplyLabel 84
#define Prop_TKChart_TrueTypeFont 85
#define Prop_TKChart_NoTitle 86
#define Prop_TKChart_NoRotation 87
#define Prop_TKChart_zGapStyle 88

// events
#define Event_TKChart_Destroy 0
#define Event_TKChart_DragDrop 1
#define Event_TKChart_DragOver 2
#define Event_TKChart_GetxLabel 3
#define Event_TKChart_HSChanged 4
#define Event_TKChart_HSRequest 5
#define Event_TKChart_NeedData 6

// default form data
//
// Some VBX controls do not operate correctly when created without
// a form file.  This occurs when a program creates a control
// dynamically rather than as part of a dialog resource.  If this
// control exhibits problems in this mode, try creating it with the
// following form data:
//
// For OWL programs:
//
//   TVbxTKChart* c = new TVbxTKChart(..., sizeof(TKChartData), TKChartData);
//
// For C/C++ programs:
//
//   HFORMFILE file = VBXCreateFormFile(sizeof(TKChartData), TKChartData);
//   HCTL c = VBXCreate(..., file);
//   VBXDeleteFormFile(file);
//
// Note that the VBXGEN_DATA or TKChart_DATA symbol must be
// defined in order to use the default form data.
//
extern BYTE TKChartData[142L];
#if defined(VBXGEN_DATA) || defined(TKChart_DATA)
  BYTE TKChartData[142L]={
    0x00,0x07,0x54,0x4b,0x43,0x68,0x61,0x72,
    0x74,0x01,0x00,0x00,0x02,0x06,0xff,0xff,
    0x07,0x00,0x09,0x00,0x0a,0x00,0x00,0x0b,
    0x00,0x00,0x11,0x40,0x01,0x07,0x00,0x00,
    0x00,0x00,0x00,0xbc,0x02,0x00,0x00,0x00,
    0x00,0x01,0x02,0x02,0x22,0x53,0x79,0x73,
    0x74,0x65,0x6d,0x00,0x4f,0x50,0x00,0x3e,
    0x0a,0x50,0x00,0x3e,0x0a,0x37,0x3f,0xe1,
    0x26,0x53,0x19,0xcf,0x4f,0x50,0x00,0x3e,
    0x0a,0x84,0x17,0xac,0x38,0x12,0x00,0x13,
    0x00,0x00,0x14,0x00,0x00,0x00,0x00,0x15,
    0x50,0xc3,0x00,0x00,0x16,0x88,0x13,0x00,
    0x00,0x17,0x05,0x00,0x18,0x04,0x2b,0x00,
    0x2e,0x00,0x30,0x00,0x00,0x00,0x00,0x31,
    0x00,0x00,0x00,0x00,0x32,0x00,0x50,0xff,
    0xff,0xff,0x00,0x52,0x00,0x00,0x53,0x00,
    0x00,0x54,0x00,0x00,0x55,0x00,0x00,0x56,
    0x00,0x00,0x57,0x00,0x00,0xff,
  };
#endif

#ifdef __OWL_VBXCTL_H

// OWL class
class TVbxTKChart : public TVbxControl {
  public:

    // constructors
    TVbxTKChart(TWindow* parent, int id, LPCSTR title,
        int x, int y, int w, int h,
        long initLen=0, void far* initData=0, TModule* module=0) :
      TVbxControl(parent, id, "TKCHART.VBX", "TKChart",
          title, x, y, w, h, initLen, initData, module) {}

    TVbxTKChart(TWindow* parent, int resourceId, TModule* module=0) :
        TVbxControl(parent, resourceId, module) {}

#if 0
    // event handlers
    void EvDestroy(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvDragDrop(VBXEVENT FAR*)
    {
      // Source As Control,X As Integer,Y As Integer
    }

    void EvDragOver(VBXEVENT FAR*)
    {
      // Source As Control,X As Integer,Y As Integer,State As Integer
    }

    void EvGetxLabel(VBXEVENT FAR*)
    {
      // xIndex As Long, xLabel As String, size As Integer
    }

    void EvHSChanged(VBXEVENT FAR*)
    {
      // OldPos As Integer, NewPos As Integer
    }

    void EvHSRequest(VBXEVENT FAR*)
    {
      // OldPos AS Integer, NewPos As Integer, Continue As Integer
    }

    void EvNeedData(VBXEVENT FAR*)
    {
      // BegIndex As Long, EndIndex As Long
    }

#endif

    // enumerations
    enum { // values for property DragMode
      DragMode_0_Manual,
      DragMode_1_Automatic,
    };

    enum { // values for property DataType
      DataType_Integer,
      DataType_Long,
      DataType_Single,
    };

    enum { // values for property ChartType
      ChartType_3D_area_separateno_frame,
      ChartType_3D_area_separatewith_frame,
      ChartType_3D_area_stackedno_frame,
      ChartType_3D_area_stackedwith_frame,
      ChartType_3D_column_separate,
      ChartType_3D_column_stacked,
      ChartType_3D_column_alternate,
      ChartType_3D_line,
      ChartType_3D_area_userdefined_x_data,
      ChartType_3D_pie,
      ChartType_2D_area_stackedno_frame,
      ChartType_2D_area_stackedwith_frame,
      ChartType_2D_bar_stacked,
      ChartType_2D_bar_alternate,
      ChartType_2D_bar_overlap,
      ChartType_2D_column_stacked,
      ChartType_2D_column_alternate,
      ChartType_2D_column_overlap,
      ChartType_2D_line_dot,
      ChartType_2D_line_line,
      ChartType_2D_line_dotline,
      ChartType_2D_line_chain,
      ChartType_2D_area_userdefined_x_data,
      ChartType_2D_combo_area_and_column,
      ChartType_2D_combo_area_and_line,
      ChartType_2D_combo_area_and_dotline,
      ChartType_2D_combo_column_and_line,
      ChartType_2D_combo_column_and_dotline,
      ChartType_2D_pie,
      ChartType_2D_hiloclose,
      ChartType_2D_combo_hiloclose_and_dotline,
      ChartType_2D_combo_hiloclose_and_line,
    };

    enum { // values for property xGapStyle
      xGapStyle_No_gap,
      xGapStyle_Thin,
      xGapStyle_Medium,
      xGapStyle_Thick,
    };

    enum { // values for property AxisStyle
      AxisStyle_Axis_only,
      AxisStyle_Side,
      AxisStyle_Bottom,
      AxisStyle_All,
    };

    enum { // values for property ProjectStyle
      ProjectStyle_Oblique,
      ProjectStyle_Perspective_Low,
      ProjectStyle_Perspective_High,
    };

    enum { // values for property LegendAlign
      LegendAlign_Auto,
      LegendAlign_No_legend,
      LegendAlign_Left,
      LegendAlign_Right,
    };

    enum { // values for property InsertData
      InsertData_Insert_by_index,
      InsertData_Insert_by_value,
    };

    enum { // values for property DeleteData
      DeleteData_Delete_by_index,
      DeleteData_Delete_by_value,
    };

    enum { // values for property ReadData
      ReadData_Retrieve_by_index,
      ReadData_Retrieve_by_value,
    };

    enum { // values for property WriteData
      WriteData_Update_by_index,
      WriteData_Update_by_value,
    };

    enum { // values for property zGapStyle
      zGapStyle_No_gap,
      zGapStyle_Thin,
      zGapStyle_Medium,
      zGapStyle_Thick,
    };


    // properties
    BOOL GetPropCtlName(string& v) {return GetProp(0,v);}
    BOOL SetPropCtlName(string& v) {return SetProp(0,v);}

    BOOL GetPropIndex(int& v) {return GetProp(1,v);}
    BOOL SetPropIndex(int v) {return SetProp(1,v);}

    BOOL GetPropLeft(long& v) {return GetProp(2,v);}
    BOOL SetPropLeft(long v) {return SetProp(2,v);}

    BOOL GetPropTop(long& v) {return GetProp(3,v);}
    BOOL SetPropTop(long v) {return SetProp(3,v);}

    BOOL GetPropWidth(long& v) {return GetProp(4,v);}
    BOOL SetPropWidth(long v) {return SetProp(4,v);}

    BOOL GetPropHeight(long& v) {return GetProp(5,v);}
    BOOL SetPropHeight(long v) {return SetProp(5,v);}

    BOOL GetPropVisible(BOOL& v) {return GetProp(6,v);}
    BOOL SetPropVisible(BOOL v) {return SetProp(6,v);}

    BOOL GetPropDragMode(ENUM& v) {return GetProp(7,v);}
    BOOL SetPropDragMode(ENUM v) {return SetProp(7,v);}

    BOOL GetPropDragIcon(HPIC& v) {return GetProp(8,v);}
    BOOL SetPropDragIcon(HPIC v) {return SetProp(8,v);}

    BOOL GetPropTag(string& v) {return GetProp(9,v);}
    BOOL SetPropTag(string& v) {return SetProp(9,v);}

    BOOL GetPropTabIndex(int& v) {return GetProp(10,v);}
    BOOL SetPropTabIndex(int v) {return SetProp(10,v);}

    BOOL GetPropTabStop(BOOL& v) {return GetProp(11,v);}
    BOOL SetPropTabStop(BOOL v) {return SetProp(11,v);}

    BOOL GetPropFontBold(BOOL& v) {return GetProp(12,v);}
    BOOL SetPropFontBold(BOOL v) {return SetProp(12,v);}

    BOOL GetPropFontItalic(BOOL& v) {return GetProp(13,v);}
    BOOL SetPropFontItalic(BOOL v) {return SetProp(13,v);}

    BOOL GetPropFontStrikethru(BOOL& v) {return GetProp(14,v);}
    BOOL SetPropFontStrikethru(BOOL v) {return SetProp(14,v);}

    BOOL GetPropFontUnderline(BOOL& v) {return GetProp(15,v);}
    BOOL SetPropFontUnderline(BOOL v) {return SetProp(15,v);}

    BOOL GetPropFontSize(float& v) {return GetProp(16,v);}
    BOOL SetPropFontSize(float v) {return SetProp(16,v);}

    BOOL GetPropFontName(string& v) {return GetProp(17,v);}
    BOOL SetPropFontName(string& v) {return SetProp(17,v);}

    BOOL GetPropDataType(ENUM& v) {return GetProp(18,v);}
    BOOL SetPropDataType(ENUM v) {return SetProp(18,v);}

    BOOL GetPropAppSendTimer(BOOL& v) {return GetProp(19,v);}
    BOOL SetPropAppSendTimer(BOOL v) {return SetProp(19,v);}

    BOOL GetPropDataStart(long& v) {return GetProp(20,v);}
    BOOL SetPropDataStart(long v) {return SetProp(20,v);}

    BOOL GetPropMaxCache(long& v) {return GetProp(21,v);}
    BOOL SetPropMaxCache(long v) {return SetProp(21,v);}

    BOOL GetPropTotalData(long& v) {return GetProp(22,v);}
    BOOL SetPropTotalData(long v) {return SetProp(22,v);}

    BOOL GetPropcElement(int& v) {return GetProp(23,v);}
    BOOL SetPropcElement(int v) {return SetProp(23,v);}

    BOOL GetPropChartType(ENUM& v) {return GetProp(24,v);}
    BOOL SetPropChartType(ENUM v) {return SetProp(24,v);}

    BOOL GetPropiMinVal(int& v) {return GetProp(25,v);}
    BOOL SetPropiMinVal(int v) {return SetProp(25,v);}

    BOOL GetPropiIncVal(int& v) {return GetProp(26,v);}
    BOOL SetPropiIncVal(int v) {return SetProp(26,v);}

    BOOL GetProplMinVal(long& v) {return GetProp(27,v);}
    BOOL SetProplMinVal(long v) {return SetProp(27,v);}

    BOOL GetProplIncVal(long& v) {return GetProp(28,v);}
    BOOL SetProplIncVal(long v) {return SetProp(28,v);}

    BOOL GetPropdMinVal(float& v) {return GetProp(29,v);}
    BOOL SetPropdMinVal(float v) {return SetProp(29,v);}

    BOOL GetPropdIncVal(float& v) {return GetProp(30,v);}
    BOOL SetPropdIncVal(float v) {return SetProp(30,v);}

    BOOL GetPropDivision(int& v) {return GetProp(31,v);}
    BOOL SetPropDivision(int v) {return SetProp(31,v);}

    BOOL GetPropLabelType(int& v) {return GetProp(32,v);}
    BOOL SetPropLabelType(int v) {return SetProp(32,v);}

    BOOL GetPropzLabelArr(string& v, int i) {return GetProp(33,v,i);}
    BOOL SetPropzLabelArr(string& v, int i) {return SetProp(33,v,i);}

    BOOL GetPropxGapStyle(ENUM& v) {return GetProp(34,v);}
    BOOL SetPropxGapStyle(ENUM v) {return SetProp(34,v);}

    BOOL GetPropxIndex(int& v) {return GetProp(35,v);}
    BOOL SetPropxIndex(int v) {return SetProp(35,v);}

    BOOL GetPropChartConfig(int& v) {return GetProp(36,v);}
    BOOL SetPropChartConfig(int v) {return SetProp(36,v);}

    BOOL GetPropAxisConfig(int& v) {return GetProp(37,v);}
    BOOL SetPropAxisConfig(int v) {return SetProp(37,v);}

    BOOL GetPropiDataArr(int& v, int i) {return GetProp(38,v,i);}
    BOOL SetPropiDataArr(int v, int i) {return SetProp(38,v,i);}

    BOOL GetProplDataArr(long& v, int i) {return GetProp(39,v,i);}
    BOOL SetProplDataArr(long v, int i) {return SetProp(39,v,i);}

    BOOL GetPropdDataArr(float& v, int i) {return GetProp(40,v,i);}
    BOOL SetPropdDataArr(float v, int i) {return SetProp(40,v,i);}

    BOOL GetPropAddData(int& v) {return GetProp(41,v);}
    BOOL SetPropAddData(int v) {return SetProp(41,v);}

    BOOL GetPropxLabel(string& v) {return GetProp(42,v);}
    BOOL SetPropxLabel(string& v) {return SetProp(42,v);}

    BOOL GetPropAxisStyle(ENUM& v) {return GetProp(43,v);}
    BOOL SetPropAxisStyle(ENUM v) {return SetProp(43,v);}

    BOOL GetPropGetDataCount(int& v) {return GetProp(44,v);}
    BOOL SetPropGetDataCount(int v) {return SetProp(44,v);}

    BOOL GetPropSetElementColorArr(int& v, int i) {return GetProp(45,v,i);}
    BOOL SetPropSetElementColorArr(int v, int i) {return SetProp(45,v,i);}

    BOOL GetPropProjectStyle(ENUM& v) {return GetProp(46,v);}
    BOOL SetPropProjectStyle(ENUM v) {return SetProp(46,v);}

    BOOL GetPropBrushPatternArr(int& v, int i) {return GetProp(47,v,i);}
    BOOL SetPropBrushPatternArr(int v, int i) {return SetProp(47,v,i);}

    BOOL GetPropGridColor(COLORREF& v) {return GetProp(48,v);}
    BOOL SetPropGridColor(COLORREF v) {return SetProp(48,v);}

    BOOL GetPropBorderColor(COLORREF& v) {return GetProp(49,v);}
    BOOL SetPropBorderColor(COLORREF v) {return SetProp(49,v);}

    BOOL GetPropLegendAlign(ENUM& v) {return GetProp(50,v);}
    BOOL SetPropLegendAlign(ENUM v) {return SetProp(50,v);}

    BOOL GetPropInsertData(ENUM& v) {return GetProp(51,v);}
    BOOL SetPropInsertData(ENUM v) {return SetProp(51,v);}

    BOOL GetPropDeleteData(ENUM& v) {return GetProp(52,v);}
    BOOL SetPropDeleteData(ENUM v) {return SetProp(52,v);}

    BOOL GetPropDeleteAllData(int& v) {return GetProp(53,v);}
    BOOL SetPropDeleteAllData(int v) {return SetProp(53,v);}

    BOOL GetPropReadData(ENUM& v) {return GetProp(54,v);}
    BOOL SetPropReadData(ENUM v) {return SetProp(54,v);}

    BOOL GetPropWriteData(ENUM& v) {return GetProp(55,v);}
    BOOL SetPropWriteData(ENUM v) {return SetProp(55,v);}

    BOOL GetPropGetCachedDataCount(int& v) {return GetProp(56,v);}
    BOOL SetPropGetCachedDataCount(int v) {return SetProp(56,v);}

    BOOL GetPropGetFirstDataCached(int& v) {return GetProp(57,v);}
    BOOL SetPropGetFirstDataCached(int v) {return SetProp(57,v);}

    BOOL GetPropTitleArr(string& v, int i) {return GetProp(58,v,i);}
    BOOL SetPropTitleArr(string& v, int i) {return SetProp(58,v,i);}

    BOOL GetPropyMinMax(int& v) {return GetProp(59,v);}
    BOOL SetPropyMinMax(int v) {return SetProp(59,v);}

    BOOL GetPropPiePosArr(int& v, int i) {return GetProp(60,v,i);}
    BOOL SetPropPiePosArr(int v, int i) {return SetProp(60,v,i);}

    BOOL GetPropiMin(int& v) {return GetProp(61,v);}
    BOOL SetPropiMin(int v) {return SetProp(61,v);}

    BOOL GetPropiMax(int& v) {return GetProp(62,v);}
    BOOL SetPropiMax(int v) {return SetProp(62,v);}

    BOOL GetProplMin(long& v) {return GetProp(63,v);}
    BOOL SetProplMin(long v) {return SetProp(63,v);}

    BOOL GetProplMax(long& v) {return GetProp(64,v);}
    BOOL SetProplMax(long v) {return SetProp(64,v);}

    BOOL GetPropdMin(float& v) {return GetProp(65,v);}
    BOOL SetPropdMin(float v) {return SetProp(65,v);}

    BOOL GetPropdMax(float& v) {return GetProp(66,v);}
    BOOL SetPropdMax(float v) {return SetProp(66,v);}

    BOOL GetPropAxisIndex(int& v) {return GetProp(67,v);}
    BOOL SetPropAxisIndex(int v) {return SetProp(67,v);}

    BOOL GetPropColorArr(long& v, int i) {return GetProp(68,v,i);}
    BOOL SetPropColorArr(long v, int i) {return SetProp(68,v,i);}

    BOOL GetPropChTimer(int& v) {return GetProp(69,v);}
    BOOL SetPropChTimer(int v) {return SetProp(69,v);}

    BOOL GetPropSelfRotate(int& v) {return GetProp(70,v);}
    BOOL SetPropSelfRotate(int v) {return SetProp(70,v);}

    BOOL GetPropRedraw(int& v) {return GetProp(71,v);}
    BOOL SetPropRedraw(int v) {return SetProp(71,v);}

    BOOL GetPropRotate(int& v) {return GetProp(72,v);}
    BOOL SetPropRotate(int v) {return SetProp(72,v);}

    BOOL GetPropCopyChart(int& v) {return GetProp(73,v);}
    BOOL SetPropCopyChart(int v) {return SetProp(73,v);}

    BOOL GetPropiNeedDataArr(int& v, int i) {return GetProp(74,v,i);}
    BOOL SetPropiNeedDataArr(int v, int i) {return SetProp(74,v,i);}

    BOOL GetProplNeedDataArr(long& v, int i) {return GetProp(75,v,i);}
    BOOL SetProplNeedDataArr(long v, int i) {return SetProp(75,v,i);}

    BOOL GetPropdNeedDataArr(float& v, int i) {return GetProp(76,v,i);}
    BOOL SetPropdNeedDataArr(float v, int i) {return SetProp(76,v,i);}

    BOOL GetPropNeedDataxLabel(string& v) {return GetProp(77,v);}
    BOOL SetPropNeedDataxLabel(string& v) {return SetProp(77,v);}

    BOOL GetPropGetElementColorArr(int& v, int i) {return GetProp(78,v,i);}
    BOOL SetPropGetElementColorArr(int v, int i) {return SetProp(78,v,i);}

    BOOL GetPropGetAxisConfig(int& v) {return GetProp(79,v);}
    BOOL SetPropGetAxisConfig(int v) {return SetProp(79,v);}

    BOOL GetPropBkColor(COLORREF& v) {return GetProp(80,v);}
    BOOL SetPropBkColor(COLORREF v) {return SetProp(80,v);}

    BOOL GetPropParent(int& v) {return GetProp(81,v);}
    BOOL SetPropParent(int v) {return SetProp(81,v);}

    BOOL GetPropDBFrontEnd(BOOL& v) {return GetProp(82,v);}
    BOOL SetPropDBFrontEnd(BOOL v) {return SetProp(82,v);}

    BOOL GetPropAutoAdjOrigin(BOOL& v) {return GetProp(83,v);}
    BOOL SetPropAutoAdjOrigin(BOOL v) {return SetProp(83,v);}

    BOOL GetPropOwnerSupplyLabel(BOOL& v) {return GetProp(84,v);}
    BOOL SetPropOwnerSupplyLabel(BOOL v) {return SetProp(84,v);}

    BOOL GetPropTrueTypeFont(BOOL& v) {return GetProp(85,v);}
    BOOL SetPropTrueTypeFont(BOOL v) {return SetProp(85,v);}

    BOOL GetPropNoTitle(BOOL& v) {return GetProp(86,v);}
    BOOL SetPropNoTitle(BOOL v) {return SetProp(86,v);}

    BOOL GetPropNoRotation(BOOL& v) {return GetProp(87,v);}
    BOOL SetPropNoRotation(BOOL v) {return SetProp(87,v);}

    BOOL GetPropzGapStyle(ENUM& v) {return GetProp(88,v);}
    BOOL SetPropzGapStyle(ENUM v) {return SetProp(88,v);}

#if 0
  DECLARE_RESPONSE_TABLE(TVbxTKChart);
#endif
};

#if 0
// OWL response table
DEFINE_RESPONSE_TABLE1(TVbxTKChart, TVbxControl)
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_Destroy, EvDestroy ),
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_DragDrop, EvDragDrop ),
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_DragOver, EvDragOver ),
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_GetxLabel, EvGetxLabel ),
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_HSChanged, EvHSChanged ),
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_HSRequest, EvHSRequest ),
  EV_VBXEVENTINDEX( IDC_TKChart, Event_TKChart_NeedData, EvNeedData ),
END_RESPONSE_TABLE;
#endif

#endif

