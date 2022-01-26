//--------------------------------------------------------
// VTSS1.H generated from VTSS.VBX by
// VbxGen 1.0 - Borland International
//--------------------------------------------------------

#ifdef __OWL_OWLDEFS_H
  #include <owl\vbxctl.h>
#endif

//--------------------------------------------------------
// SSEdit (VB1)
//--------------------------------------------------------

// properties
#define Prop_SSEdit_CtlName 0
#define Prop_SSEdit_DragIcon 1
#define Prop_SSEdit_DragMode 2
#define Prop_SSEdit_Enabled 3
#define Prop_SSEdit_Height 4
#define Prop_SSEdit_Index 7
#define Prop_SSEdit_Left 8
#define Prop_SSEdit_Parent 9
#define Prop_SSEdit_TabIndex 10
#define Prop_SSEdit_TabStop 11
#define Prop_SSEdit_Tag 12
#define Prop_SSEdit_Top 13
#define Prop_SSEdit_Visible 14
#define Prop_SSEdit_Width 15
#define Prop_SSEdit_EditName 16

// events
#define Event_SSEdit_Click 0
#define Event_SSEdit_DragDrop 1
#define Event_SSEdit_DragOver 2

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
//   TVbxSSEdit* c = new TVbxSSEdit(..., sizeof(SSEditData), SSEditData);
//
// For C/C++ programs:
//
//   HFORMFILE file = VBXCreateFormFile(sizeof(SSEditData), SSEditData);
//   HCTL c = VBXCreate(..., file);
//   VBXDeleteFormFile(file);
//
// Note that the VBXGEN_DATA or SSEdit_DATA symbol must be
// defined in order to use the default form data.
//
extern BYTE SSEditData[38L];
#if defined(VBXGEN_DATA) || defined(SSEdit_DATA)
  BYTE SSEditData[38L]={
    0x10,0x07,0x53,0x53,0x45,0x64,0x69,0x74,
    0x31,0x00,0x06,0x53,0x53,0x45,0x64,0x69,
    0x74,0x02,0x00,0x03,0xff,0xff,0x07,0x00,
    0x00,0x08,0x0a,0x00,0x00,0x0b,0x00,0x00,
    0x0c,0x00,0x0e,0xff,0xff,0xff,
  };
#endif

#ifdef __OWL_VBXCTL_H

// OWL class
class TVbxSSEdit : public TVbxControl {
  public:

    // constructors
    TVbxSSEdit(TWindow* parent, int id, LPCSTR title,
        int x, int y, int w, int h,
        long initLen=0, void far* initData=0, TModule* module=0) :
      TVbxControl(parent, id, "VTSS.VBX", "SSEdit",
          title, x, y, w, h, initLen, initData, module) {}

    TVbxSSEdit(TWindow* parent, int resourceId, TModule* module=0) :
        TVbxControl(parent, resourceId, module) {}

#if 0
    // event handlers
    void EvClick(VBXEVENT FAR*)
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

#endif

    // enumerations
    enum { // values for property DragMode
      DragMode_0_Manual,
      DragMode_1_Automatic,
    };


    // properties
    BOOL GetPropCtlName(string& v) {return GetProp(0,v);}
    BOOL SetPropCtlName(string& v) {return SetProp(0,v);}

    BOOL GetPropDragIcon(HPIC& v) {return GetProp(1,v);}
    BOOL SetPropDragIcon(HPIC v) {return SetProp(1,v);}

    BOOL GetPropDragMode(ENUM& v) {return GetProp(2,v);}
    BOOL SetPropDragMode(ENUM v) {return SetProp(2,v);}

    BOOL GetPropEnabled(BOOL& v) {return GetProp(3,v);}
    BOOL SetPropEnabled(BOOL v) {return SetProp(3,v);}

    BOOL GetPropHeight(long& v) {return GetProp(4,v);}
    BOOL SetPropHeight(long v) {return SetProp(4,v);}

    BOOL GetPropIndex(int& v) {return GetProp(7,v);}
    BOOL SetPropIndex(int v) {return SetProp(7,v);}

    BOOL GetPropLeft(long& v) {return GetProp(8,v);}
    BOOL SetPropLeft(long v) {return SetProp(8,v);}

    BOOL GetPropParent(int& v) {return GetProp(9,v);}
    BOOL SetPropParent(int v) {return SetProp(9,v);}

    BOOL GetPropTabIndex(int& v) {return GetProp(10,v);}
    BOOL SetPropTabIndex(int v) {return SetProp(10,v);}

    BOOL GetPropTabStop(BOOL& v) {return GetProp(11,v);}
    BOOL SetPropTabStop(BOOL v) {return SetProp(11,v);}

    BOOL GetPropTag(string& v) {return GetProp(12,v);}
    BOOL SetPropTag(string& v) {return SetProp(12,v);}

    BOOL GetPropTop(long& v) {return GetProp(13,v);}
    BOOL SetPropTop(long v) {return SetProp(13,v);}

    BOOL GetPropVisible(BOOL& v) {return GetProp(14,v);}
    BOOL SetPropVisible(BOOL v) {return SetProp(14,v);}

    BOOL GetPropWidth(long& v) {return GetProp(15,v);}
    BOOL SetPropWidth(long v) {return SetProp(15,v);}

    BOOL GetPropEditName(string& v) {return GetProp(16,v);}
    BOOL SetPropEditName(string& v) {return SetProp(16,v);}

#if 0
  DECLARE_RESPONSE_TABLE(TVbxSSEdit);
#endif
};

#if 0
// OWL response table
DEFINE_RESPONSE_TABLE1(TVbxSSEdit, TVbxControl)
  EV_VBXEVENTINDEX( IDC_SSEdit, Event_SSEdit_Click, EvClick ),
  EV_VBXEVENTINDEX( IDC_SSEdit, Event_SSEdit_DragDrop, EvDragDrop ),
  EV_VBXEVENTINDEX( IDC_SSEdit, Event_SSEdit_DragOver, EvDragOver ),
END_RESPONSE_TABLE;
#endif

#endif

//--------------------------------------------------------
// SSView (VB1)
//--------------------------------------------------------

// properties
#define Prop_SSView_CtlName 0
#define Prop_SSView_Enabled 1
#define Prop_SSView_Height 2
#define Prop_SSView_Index 5
#define Prop_SSView_Left 6
#define Prop_SSView_Parent 7
#define Prop_SSView_TabIndex 8
#define Prop_SSView_TabStop 9
#define Prop_SSView_Tag 10
#define Prop_SSView_Top 11
#define Prop_SSView_Visible 12
#define Prop_SSView_Width 13
#define Prop_SSView_ReadFile 14
#define Prop_SSView_SS 15
#define Prop_SSView_WriteFile 17
#define Prop_SSView_BackColor 18
#define Prop_SSView_BorderStyle 19
#define Prop_SSView_Col 20
#define Prop_SSView_Row 21
#define Prop_SSView_ShowHScrollBar 22
#define Prop_SSView_Text 23
#define Prop_SSView_Number 24
#define Prop_SSView_Formula 25
#define Prop_SSView_FixedCol 26
#define Prop_SSView_FixedCols 27
#define Prop_SSView_FixedRow 28
#define Prop_SSView_FixedRows 29
#define Prop_SSView_ShowGridLines 30
#define Prop_SSView_ShowRowHeading 31
#define Prop_SSView_ShowSelections 32
#define Prop_SSView_LeftCol 33
#define Prop_SSView_MaxCol 34
#define Prop_SSView_MaxRow 35
#define Prop_SSView_TopRow 36
#define Prop_SSView_AllowResize 37
#define Prop_SSView_AllowSelections 38
#define Prop_SSView_AllowFormulas 39
#define Prop_SSView_AllowInCellEditing 40
#define Prop_SSView_ShowVScrollBar 41
#define Prop_SSView_AllowFillRange 42
#define Prop_SSView_AllowMoveRange 43
#define Prop_SSView_SelStartCol 44
#define Prop_SSView_SelStartRow 45
#define Prop_SSView_SelEndCol 46
#define Prop_SSView_SelEndRow 47
#define Prop_SSView_ExtraColor 48
#define Prop_SSView_EditName 49
#define Prop_SSView_FileName 50
#define Prop_SSView_AutoRecalc 51
#define Prop_SSView_AllowAppLaunch 53
#define Prop_SSView_PrintGridLines 54
#define Prop_SSView_PrintRowHeading 55
#define Prop_SSView_PrintHCenter 56
#define Prop_SSView_PrintVCenter 57
#define Prop_SSView_PrintLeftToRight 58
#define Prop_SSView_PrintHeader 59
#define Prop_SSView_PrintFooter 60
#define Prop_SSView_PrintLeftMargin 61
#define Prop_SSView_PrintTopMargin 62
#define Prop_SSView_PrintRightMargin 63
#define Prop_SSView_PrintBottomMargin 64
#define Prop_SSView_PrintArea 65
#define Prop_SSView_PrintTitles 66
#define Prop_SSView_PrintNoColor 67
#define Prop_SSView_Selection 68
#define Prop_SSView_TableName 71
#define Prop_SSView_DoCancelEdit 74
#define Prop_SSView_DoSelChange 75
#define Prop_SSView_DoStartEdit 76
#define Prop_SSView_DoEndEdit 77
#define Prop_SSView_DoStartRecalc 78
#define Prop_SSView_DoEndRecalc 79
#define Prop_SSView_DoClick 80
#define Prop_SSView_DoDblClick 81
#define Prop_SSView_ShowColHeading 89
#define Prop_SSView_PrintColHeading 90
#define Prop_SSView_About_Formula_One 92
#define Prop_SSView_Entry 93
#define Prop_SSView_DataRowsBuffered 94
#define Prop_SSView_DataRowBase 95
#define Prop_SSView_DoDataRowLoad 96
#define Prop_SSView_DoDataNewRow 97
#define Prop_SSView_Repaint 98
#define Prop_SSView_AllowArrows 99
#define Prop_SSView_AllowTabs 100
#define Prop_SSView_FormattedText 101
#define Prop_SSView_MousePointer 102
#define Prop_SSView_RowMode 103
#define Prop_SSView_DataConnected 104
#define Prop_SSView_DataAutoAddNew 105
#define Prop_SSView_AllowDelete 106
#define Prop_SSView_DataHdrField 107
#define Prop_SSView_EnableProtection 108
#define Prop_SSView_WriteExcel4 109
#define Prop_SSView_DataSetColumnFormats 110
#define Prop_SSView_DragIcon 111
#define Prop_SSView_DragMode 112
#define Prop_SSView_MinCol 113
#define Prop_SSView_MinRow 114
#define Prop_SSView_DoTopLeftChanged 115
#define Prop_SSView_AllowEditHeaders 116
#define Prop_SSView_Application_Designer 117

// events
#define Event_SSView_Click 0
#define Event_SSView_DblClick 1
#define Event_SSView_DragDrop 2
#define Event_SSView_DragOver 3
#define Event_SSView_GotFocus 4
#define Event_SSView_KeyDown 5
#define Event_SSView_KeyPress 6
#define Event_SSView_KeyUp 7
#define Event_SSView_LostFocus 8
#define Event_SSView_CancelEdit 9
#define Event_SSView_SelChange 10
#define Event_SSView_StartEdit 11
#define Event_SSView_EndEdit 12
#define Event_SSView_StartRecalc 13
#define Event_SSView_EndRecalc 14
#define Event_SSView_DataRowLoad 15
#define Event_SSView_DataNewRow 16
#define Event_SSView_TopLeftChanged 17

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
//   TVbxSSView* c = new TVbxSSView(..., sizeof(SSViewData), SSViewData);
//
// For C/C++ programs:
//
//   HFORMFILE file = VBXCreateFormFile(sizeof(SSViewData), SSViewData);
//   HCTL c = VBXCreate(..., file);
//   VBXDeleteFormFile(file);
//
// Note that the VBXGEN_DATA or SSView_DATA symbol must be
// defined in order to use the default form data.
//
extern BYTE SSViewData[1547L];
#if defined(VBXGEN_DATA) || defined(SSView_DATA)
  BYTE SSViewData[1547L]={
    0x47,0x05,0x53,0x68,0x65,0x65,0x74,0x00,
    0x05,0x53,0x68,0x65,0x65,0x74,0x01,0xff,
    0xff,0x05,0x00,0x00,0x06,0x08,0x00,0x00,
    0x09,0x00,0x00,0x0a,0x00,0x0c,0xff,0xff,
    0x13,0x01,0x31,0x07,0x53,0x53,0x45,0x64,
    0x69,0x74,0x31,0x32,0x00,0x00,0x09,0x04,
    0x06,0x00,0x00,0x00,0x10,0x00,0x00,0x00,
    0x00,0x78,0x18,0x00,0x92,0x00,0xff,0x4c,
    0xff,0xff,0xff,0x00,0xc0,0xc0,0xc0,0x00,
    0xff,0x00,0xff,0x3f,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x05,0x78,0x10,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
    0x01,0x78,0x0a,0x00,0x15,0x00,0x15,0x00,
    0x15,0x00,0xff,0x00,0x40,0x06,0x5c,0x00,
    0x20,0x00,0x00,0x00,0x10,0x00,0x00,0x00,
    0x13,0x41,0x75,0x74,0x68,0x6f,0x72,0x69,
    0x7a,0x65,0x64,0x20,0x4c,0x69,0x63,0x65,
    0x6e,0x73,0x65,0x65,0x20,0x20,0x20,0x20,
    0x20,0x20,0x42,0x00,0x02,0x00,0xe4,0x04,
    0x0c,0x00,0x02,0x00,0x64,0x00,0x0d,0x00,
    0x02,0x00,0x01,0x00,0x0f,0x00,0x02,0x00,
    0x01,0x00,0x10,0x00,0x08,0x00,0xfc,0xa9,
    0xf1,0xd2,0x4d,0x62,0x50,0x3f,0x11,0x00,
    0x02,0x00,0x00,0x00,0x22,0x00,0x02,0x00,
    0x00,0x00,0x2a,0x00,0x02,0x00,0x00,0x00,
    0x2b,0x00,0x02,0x00,0x01,0x00,0x25,0x02,
    0x04,0x00,0x01,0x00,0xff,0x00,0x8c,0x00,
    0x04,0x00,0x01,0x00,0x01,0x00,0x31,0x02,
    0x14,0x00,0xc8,0x00,0x00,0x00,0x08,0x00,
    0x0d,0x4d,0x53,0x20,0x53,0x61,0x6e,0x73,
    0x20,0x53,0x65,0x72,0x69,0x66,0x31,0x02,
    0x14,0x00,0xc8,0x00,0x01,0x00,0x08,0x00,
    0x0d,0x4d,0x53,0x20,0x53,0x61,0x6e,0x73,
    0x20,0x53,0x65,0x72,0x69,0x66,0x31,0x02,
    0x14,0x00,0xc8,0x00,0x02,0x00,0x08,0x00,
    0x0d,0x4d,0x53,0x20,0x53,0x61,0x6e,0x73,
    0x20,0x53,0x65,0x72,0x69,0x66,0x31,0x02,
    0x14,0x00,0xc8,0x00,0x03,0x00,0x08,0x00,
    0x0d,0x4d,0x53,0x20,0x53,0x61,0x6e,0x73,
    0x20,0x53,0x65,0x72,0x69,0x66,0x31,0x02,
    0x14,0x00,0xc8,0x00,0x00,0x00,0x08,0x00,
    0x0d,0x4d,0x53,0x20,0x53,0x61,0x6e,0x73,
    0x20,0x53,0x65,0x72,0x69,0x66,0x14,0x00,
    0x03,0x00,0x02,0x26,0x46,0x15,0x00,0x08,
    0x00,0x07,0x50,0x61,0x67,0x65,0x20,0x26,
    0x50,0x83,0x00,0x02,0x00,0x00,0x00,0x84,
    0x00,0x02,0x00,0x00,0x00,0x26,0x00,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe8,
    0x3f,0x27,0x00,0x08,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xe8,0x3f,0x28,0x00,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,
    0x3f,0x29,0x00,0x08,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xf0,0x3f,0xa1,0x00,0x0c,
    0x00,0x01,0x00,0x64,0x00,0x01,0x00,0x01,
    0x00,0x01,0x00,0x06,0x00,0x56,0x00,0x02,
    0x00,0x1b,0x00,0x1e,0x04,0x0a,0x00,0x00,
    0x00,0x07,0x47,0x65,0x6e,0x65,0x72,0x61,
    0x6c,0x1e,0x04,0x04,0x00,0x01,0x00,0x01,
    0x30,0x1e,0x04,0x07,0x00,0x01,0x01,0x04,
    0x30,0x2e,0x30,0x30,0x1e,0x04,0x08,0x00,
    0x01,0x02,0x05,0x23,0x2c,0x23,0x23,0x30,
    0x1e,0x04,0x0b,0x00,0x01,0x03,0x08,0x23,
    0x2c,0x23,0x23,0x30,0x2e,0x30,0x30,0x1e,
    0x04,0x14,0x00,0x01,0x04,0x11,0x23,0x2c,
    0x23,0x23,0x30,0x5f,0x29,0x3b,0x5c,0x28,
    0x23,0x2c,0x23,0x23,0x30,0x5c,0x29,0x1e,
    0x04,0x19,0x00,0x01,0x05,0x16,0x23,0x2c,
    0x23,0x23,0x30,0x5f,0x29,0x3b,0x5b,0x52,
    0x65,0x64,0x5d,0x5c,0x28,0x23,0x2c,0x23,
    0x23,0x30,0x5c,0x29,0x1e,0x04,0x1a,0x00,
    0x01,0x06,0x17,0x23,0x2c,0x23,0x23,0x30,
    0x2e,0x30,0x30,0x5f,0x29,0x3b,0x5c,0x28,
    0x23,0x2c,0x23,0x23,0x30,0x2e,0x30,0x30,
    0x5c,0x29,0x1e,0x04,0x1f,0x00,0x01,0x07,
    0x1c,0x23,0x2c,0x23,0x23,0x30,0x2e,0x30,
    0x30,0x5f,0x29,0x3b,0x5b,0x52,0x65,0x64,
    0x5d,0x5c,0x28,0x23,0x2c,0x23,0x23,0x30,
    0x2e,0x30,0x30,0x5c,0x29,0x1e,0x04,0x1a,
    0x00,0x02,0x00,0x17,0x22,0x24,0x22,0x23,
    0x2c,0x23,0x23,0x30,0x5f,0x29,0x3b,0x5c,
    0x28,0x22,0x24,0x22,0x23,0x2c,0x23,0x23,
    0x30,0x5c,0x29,0x1e,0x04,0x1f,0x00,0x02,
    0x01,0x1c,0x22,0x24,0x22,0x23,0x2c,0x23,
    0x23,0x30,0x5f,0x29,0x3b,0x5b,0x52,0x65,
    0x64,0x5d,0x5c,0x28,0x22,0x24,0x22,0x23,
    0x2c,0x23,0x23,0x30,0x5c,0x29,0x1e,0x04,
    0x20,0x00,0x02,0x02,0x1d,0x22,0x24,0x22,
    0x23,0x2c,0x23,0x23,0x30,0x2e,0x30,0x30,
    0x5f,0x29,0x3b,0x5c,0x28,0x22,0x24,0x22,
    0x23,0x2c,0x23,0x23,0x30,0x2e,0x30,0x30,
    0x5c,0x29,0x1e,0x04,0x25,0x00,0x02,0x03,
    0x22,0x22,0x24,0x22,0x23,0x2c,0x23,0x23,
    0x30,0x2e,0x30,0x30,0x5f,0x29,0x3b,0x5b,
    0x52,0x65,0x64,0x5d,0x5c,0x28,0x22,0x24,
    0x22,0x23,0x2c,0x23,0x23,0x30,0x2e,0x30,
    0x30,0x5c,0x29,0x1e,0x04,0x05,0x00,0x05,
    0x00,0x02,0x30,0x25,0x1e,0x04,0x08,0x00,
    0x05,0x01,0x05,0x30,0x2e,0x30,0x30,0x25,
    0x1e,0x04,0x0b,0x00,0x07,0x00,0x08,0x30,
    0x2e,0x30,0x30,0x45,0x2b,0x30,0x30,0x1e,
    0x04,0x09,0x00,0x06,0x00,0x06,0x23,0x5c,
    0x20,0x3f,0x2f,0x3f,0x1e,0x04,0x0b,0x00,
    0x06,0x01,0x08,0x23,0x5c,0x20,0x3f,0x3f,
    0x2f,0x3f,0x3f,0x1e,0x04,0x09,0x00,0x03,
    0x00,0x06,0x6d,0x2f,0x64,0x2f,0x79,0x79,
    0x1e,0x04,0x0d,0x00,0x03,0x01,0x0a,0x64,
    0x5c,0x2d,0x6d,0x6d,0x6d,0x5c,0x2d,0x79,
    0x79,0x1e,0x04,0x09,0x00,0x03,0x02,0x06,
    0x64,0x5c,0x2d,0x6d,0x6d,0x6d,0x1e,0x04,
    0x0a,0x00,0x03,0x03,0x07,0x6d,0x6d,0x6d,
    0x5c,0x2d,0x79,0x79,0x1e,0x04,0x0e,0x00,
    0x04,0x00,0x0b,0x68,0x3a,0x6d,0x6d,0x5c,
    0x20,0x41,0x4d,0x2f,0x50,0x4d,0x1e,0x04,
    0x11,0x00,0x04,0x01,0x0e,0x68,0x3a,0x6d,
    0x6d,0x3a,0x73,0x73,0x5c,0x20,0x41,0x4d,
    0x2f,0x50,0x4d,0x1e,0x04,0x07,0x00,0x04,
    0x02,0x04,0x68,0x3a,0x6d,0x6d,0x1e,0x04,
    0x0a,0x00,0x04,0x03,0x07,0x68,0x3a,0x6d,
    0x6d,0x3a,0x73,0x73,0x1e,0x04,0x0f,0x00,
    0x04,0x04,0x0c,0x6d,0x2f,0x64,0x2f,0x79,
    0x79,0x5c,0x20,0x68,0x3a,0x6d,0x6d,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0x00,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x01,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x01,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x02,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x02,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0xf5,0xff,0x20,
    0xc4,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x00,0x00,0x01,0x00,0x20,
    0x00,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x05,0x08,0xf5,0xff,0x20,
    0xc8,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x05,0x06,0xf5,0xff,0x20,
    0xc8,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x05,0x0c,0xf5,0xff,0x20,
    0xc8,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x05,0x0a,0xf5,0xff,0x20,
    0xc8,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x05,0x0d,0xf5,0xff,0x20,
    0xc8,0x00,0xce,0x00,0x00,0x00,0x00,0x43,
    0x04,0x0c,0x00,0x04,0x00,0xf0,0xff,0x12,
    0x48,0x80,0x45,0x00,0x00,0x00,0x00,0x93,
    0x02,0x04,0x00,0x10,0x80,0x03,0xff,0x93,
    0x02,0x04,0x00,0x11,0x80,0x06,0xff,0x93,
    0x02,0x04,0x00,0x12,0x80,0x04,0xff,0x93,
    0x02,0x04,0x00,0x13,0x80,0x07,0xff,0x93,
    0x02,0x04,0x00,0x00,0x80,0x00,0xff,0x93,
    0x02,0x04,0x00,0x14,0x80,0x05,0xff,0x55,
    0x00,0x02,0x00,0x08,0x00,0x00,0x02,0x0a,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3d,0x00,0x0a,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x1d,0x00,0x0f,0x00,0x03,0x00,0x00,
    0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x3e,0x02,0x0a,0x00,
    0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xab,0x00,0x22,0x00,0x20,0x00,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0x99,0x00,0x02,0x00,0x26,0x09,0x0a,0x00,
    0x00,0x00,0x35,0xff,0xff,0x4a,0xff,0xff,
    0x4b,0xff,0xff,0x4c,0xff,0xff,0x4d,0xff,
    0xff,0x4e,0xff,0xff,0x4f,0xff,0xff,0x50,
    0xff,0xff,0x51,0xff,0xff,0x5e,0x40,0x00,
    0x00,0x00,0x60,0xff,0xff,0x61,0xff,0xff,
    0x66,0x00,0x68,0xff,0xff,0x69,0xff,0xff,
    0x6b,0x00,0x6e,0xff,0xff,0x70,0x00,0x73,
    0xff,0xff,0xff,
  };
#endif

#ifdef __OWL_VBXCTL_H

// OWL class
class TVbxSSView : public TVbxControl {
  public:

    // constructors
    TVbxSSView(TWindow* parent, int id, LPCSTR title,
        int x, int y, int w, int h,
        long initLen=0, void far* initData=0, TModule* module=0) :
      TVbxControl(parent, id, "VTSS.VBX", "SSView",
          title, x, y, w, h, initLen, initData, module) {}

    TVbxSSView(TWindow* parent, int resourceId, TModule* module=0) :
        TVbxControl(parent, resourceId, module) {}

#if 0
    // event handlers
    void EvClick(VBXEVENT FAR*)
    {
      // nRow As Long, nCol As Long
    }

    void EvDblClick(VBXEVENT FAR*)
    {
      // nRow As Long, nCol As Long
    }

    void EvDragDrop(VBXEVENT FAR*)
    {
      // Source As Control,X As Integer,Y As Integer
    }

    void EvDragOver(VBXEVENT FAR*)
    {
      // Source As Control,X As Integer,Y As Integer,State As Integer
    }

    void EvGotFocus(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvKeyDown(VBXEVENT FAR*)
    {
      // KeyCode As Integer, Shift As Integer
    }

    void EvKeyPress(VBXEVENT FAR*)
    {
      // KeyAscii As Integer
    }

    void EvKeyUp(VBXEVENT FAR*)
    {
      // KeyCode As Integer, Shift As Integer
    }

    void EvLostFocus(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvCancelEdit(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvSelChange(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvStartEdit(VBXEVENT FAR*)
    {
      // EditString As String, Cancel As Integer
    }

    void EvEndEdit(VBXEVENT FAR*)
    {
      // EditString As String, Cancel As Integer
    }

    void EvStartRecalc(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvEndRecalc(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvDataRowLoad(VBXEVENT FAR*)
    {
      // nRow As Long
    }

    void EvDataNewRow(VBXEVENT FAR*)
    {
      // nRow As Long
    }

    void EvTopLeftChanged(VBXEVENT FAR*)
    {
      // no arguments
    }

#endif

    // enumerations
    enum { // values for property BorderStyle
      BorderStyle_0_None,
      BorderStyle_1_Fixed_Single,
    };

    enum { // values for property ShowHScrollBar
      ShowHScrollBar_Off,
      ShowHScrollBar_On,
      ShowHScrollBar_Automatic,
    };

    enum { // values for property ShowSelections
      ShowSelections_Off,
      ShowSelections_On,
      ShowSelections_Automatic,
    };

    enum { // values for property ShowVScrollBar
      ShowVScrollBar_Off,
      ShowVScrollBar_On,
      ShowVScrollBar_Automatic,
    };

    enum { // values for property MousePointer
      MousePointer_0_Default,
      MousePointer_1_Arrow,
      MousePointer_2_Cross,
      MousePointer_3_IBeam,
      MousePointer_4_Icon,
      MousePointer_5_Size,
      MousePointer_6_Size_NE_SW,
      MousePointer_7_Size_NS,
      MousePointer_8_Size_NW_SE,
      MousePointer_9_Size_WE,
      MousePointer_10_Up_Arrow,
      MousePointer_11_Hourglass,
      MousePointer_12_No_Drop,
    };

    enum { // values for property DragMode
      DragMode_0_Manual,
      DragMode_1_Automatic,
    };


    // properties
    BOOL GetPropCtlName(string& v) {return GetProp(0,v);}
    BOOL SetPropCtlName(string& v) {return SetProp(0,v);}

    BOOL GetPropEnabled(BOOL& v) {return GetProp(1,v);}
    BOOL SetPropEnabled(BOOL v) {return SetProp(1,v);}

    BOOL GetPropHeight(long& v) {return GetProp(2,v);}
    BOOL SetPropHeight(long v) {return SetProp(2,v);}

    BOOL GetPropIndex(int& v) {return GetProp(5,v);}
    BOOL SetPropIndex(int v) {return SetProp(5,v);}

    BOOL GetPropLeft(long& v) {return GetProp(6,v);}
    BOOL SetPropLeft(long v) {return SetProp(6,v);}

    BOOL GetPropParent(int& v) {return GetProp(7,v);}
    BOOL SetPropParent(int v) {return SetProp(7,v);}

    BOOL GetPropTabIndex(int& v) {return GetProp(8,v);}
    BOOL SetPropTabIndex(int v) {return SetProp(8,v);}

    BOOL GetPropTabStop(BOOL& v) {return GetProp(9,v);}
    BOOL SetPropTabStop(BOOL v) {return SetProp(9,v);}

    BOOL GetPropTag(string& v) {return GetProp(10,v);}
    BOOL SetPropTag(string& v) {return SetProp(10,v);}

    BOOL GetPropTop(long& v) {return GetProp(11,v);}
    BOOL SetPropTop(long v) {return SetProp(11,v);}

    BOOL GetPropVisible(BOOL& v) {return GetProp(12,v);}
    BOOL SetPropVisible(BOOL v) {return SetProp(12,v);}

    BOOL GetPropWidth(long& v) {return GetProp(13,v);}
    BOOL SetPropWidth(long v) {return SetProp(13,v);}

    BOOL GetPropReadFile(string& v) {return GetProp(14,v);}
    BOOL SetPropReadFile(string& v) {return SetProp(14,v);}

    BOOL GetPropSS(long& v) {return GetProp(15,v);}
    BOOL SetPropSS(long v) {return SetProp(15,v);}

    BOOL GetPropWriteFile(string& v) {return GetProp(17,v);}
    BOOL SetPropWriteFile(string& v) {return SetProp(17,v);}

    BOOL GetPropBackColor(COLORREF& v) {return GetProp(18,v);}
    BOOL SetPropBackColor(COLORREF v) {return SetProp(18,v);}

    BOOL GetPropBorderStyle(ENUM& v) {return GetProp(19,v);}
    BOOL SetPropBorderStyle(ENUM v) {return SetProp(19,v);}

    BOOL GetPropCol(long& v) {return GetProp(20,v);}
    BOOL SetPropCol(long v) {return SetProp(20,v);}

    BOOL GetPropRow(long& v) {return GetProp(21,v);}
    BOOL SetPropRow(long v) {return SetProp(21,v);}

    BOOL GetPropShowHScrollBar(ENUM& v) {return GetProp(22,v);}
    BOOL SetPropShowHScrollBar(ENUM v) {return SetProp(22,v);}

    BOOL GetPropText(string& v) {return GetProp(23,v);}
    BOOL SetPropText(string& v) {return SetProp(23,v);}

    BOOL GetPropNumber(float& v) {return GetProp(24,v);}
    BOOL SetPropNumber(float v) {return SetProp(24,v);}

    BOOL GetPropFormula(string& v) {return GetProp(25,v);}
    BOOL SetPropFormula(string& v) {return SetProp(25,v);}

    BOOL GetPropFixedCol(long& v) {return GetProp(26,v);}
    BOOL SetPropFixedCol(long v) {return SetProp(26,v);}

    BOOL GetPropFixedCols(long& v) {return GetProp(27,v);}
    BOOL SetPropFixedCols(long v) {return SetProp(27,v);}

    BOOL GetPropFixedRow(long& v) {return GetProp(28,v);}
    BOOL SetPropFixedRow(long v) {return SetProp(28,v);}

    BOOL GetPropFixedRows(long& v) {return GetProp(29,v);}
    BOOL SetPropFixedRows(long v) {return SetProp(29,v);}

    BOOL GetPropShowGridLines(BOOL& v) {return GetProp(30,v);}
    BOOL SetPropShowGridLines(BOOL v) {return SetProp(30,v);}

    BOOL GetPropShowRowHeading(BOOL& v) {return GetProp(31,v);}
    BOOL SetPropShowRowHeading(BOOL v) {return SetProp(31,v);}

    BOOL GetPropShowSelections(ENUM& v) {return GetProp(32,v);}
    BOOL SetPropShowSelections(ENUM v) {return SetProp(32,v);}

    BOOL GetPropLeftCol(long& v) {return GetProp(33,v);}
    BOOL SetPropLeftCol(long v) {return SetProp(33,v);}

    BOOL GetPropMaxCol(long& v) {return GetProp(34,v);}
    BOOL SetPropMaxCol(long v) {return SetProp(34,v);}

    BOOL GetPropMaxRow(long& v) {return GetProp(35,v);}
    BOOL SetPropMaxRow(long v) {return SetProp(35,v);}

    BOOL GetPropTopRow(long& v) {return GetProp(36,v);}
    BOOL SetPropTopRow(long v) {return SetProp(36,v);}

    BOOL GetPropAllowResize(BOOL& v) {return GetProp(37,v);}
    BOOL SetPropAllowResize(BOOL v) {return SetProp(37,v);}

    BOOL GetPropAllowSelections(BOOL& v) {return GetProp(38,v);}
    BOOL SetPropAllowSelections(BOOL v) {return SetProp(38,v);}

    BOOL GetPropAllowFormulas(BOOL& v) {return GetProp(39,v);}
    BOOL SetPropAllowFormulas(BOOL v) {return SetProp(39,v);}

    BOOL GetPropAllowInCellEditing(BOOL& v) {return GetProp(40,v);}
    BOOL SetPropAllowInCellEditing(BOOL v) {return SetProp(40,v);}

    BOOL GetPropShowVScrollBar(ENUM& v) {return GetProp(41,v);}
    BOOL SetPropShowVScrollBar(ENUM v) {return SetProp(41,v);}

    BOOL GetPropAllowFillRange(BOOL& v) {return GetProp(42,v);}
    BOOL SetPropAllowFillRange(BOOL v) {return SetProp(42,v);}

    BOOL GetPropAllowMoveRange(BOOL& v) {return GetProp(43,v);}
    BOOL SetPropAllowMoveRange(BOOL v) {return SetProp(43,v);}

    BOOL GetPropSelStartCol(long& v) {return GetProp(44,v);}
    BOOL SetPropSelStartCol(long v) {return SetProp(44,v);}

    BOOL GetPropSelStartRow(long& v) {return GetProp(45,v);}
    BOOL SetPropSelStartRow(long v) {return SetProp(45,v);}

    BOOL GetPropSelEndCol(long& v) {return GetProp(46,v);}
    BOOL SetPropSelEndCol(long v) {return SetProp(46,v);}

    BOOL GetPropSelEndRow(long& v) {return GetProp(47,v);}
    BOOL SetPropSelEndRow(long v) {return SetProp(47,v);}

    BOOL GetPropExtraColor(COLORREF& v) {return GetProp(48,v);}
    BOOL SetPropExtraColor(COLORREF v) {return SetProp(48,v);}

    BOOL GetPropEditName(string& v) {return GetProp(49,v);}
    BOOL SetPropEditName(string& v) {return SetProp(49,v);}

    BOOL GetPropFileName(string& v) {return GetProp(50,v);}
    BOOL SetPropFileName(string& v) {return SetProp(50,v);}

    BOOL GetPropAutoRecalc(BOOL& v) {return GetProp(51,v);}
    BOOL SetPropAutoRecalc(BOOL v) {return SetProp(51,v);}

    BOOL GetPropAllowAppLaunch(BOOL& v) {return GetProp(53,v);}
    BOOL SetPropAllowAppLaunch(BOOL v) {return SetProp(53,v);}

    BOOL GetPropPrintGridLines(BOOL& v) {return GetProp(54,v);}
    BOOL SetPropPrintGridLines(BOOL v) {return SetProp(54,v);}

    BOOL GetPropPrintRowHeading(BOOL& v) {return GetProp(55,v);}
    BOOL SetPropPrintRowHeading(BOOL v) {return SetProp(55,v);}

    BOOL GetPropPrintHCenter(BOOL& v) {return GetProp(56,v);}
    BOOL SetPropPrintHCenter(BOOL v) {return SetProp(56,v);}

    BOOL GetPropPrintVCenter(BOOL& v) {return GetProp(57,v);}
    BOOL SetPropPrintVCenter(BOOL v) {return SetProp(57,v);}

    BOOL GetPropPrintLeftToRight(BOOL& v) {return GetProp(58,v);}
    BOOL SetPropPrintLeftToRight(BOOL v) {return SetProp(58,v);}

    BOOL GetPropPrintHeader(string& v) {return GetProp(59,v);}
    BOOL SetPropPrintHeader(string& v) {return SetProp(59,v);}

    BOOL GetPropPrintFooter(string& v) {return GetProp(60,v);}
    BOOL SetPropPrintFooter(string& v) {return SetProp(60,v);}

    BOOL GetPropPrintLeftMargin(float& v) {return GetProp(61,v);}
    BOOL SetPropPrintLeftMargin(float v) {return SetProp(61,v);}

    BOOL GetPropPrintTopMargin(float& v) {return GetProp(62,v);}
    BOOL SetPropPrintTopMargin(float v) {return SetProp(62,v);}

    BOOL GetPropPrintRightMargin(float& v) {return GetProp(63,v);}
    BOOL SetPropPrintRightMargin(float v) {return SetProp(63,v);}

    BOOL GetPropPrintBottomMargin(float& v) {return GetProp(64,v);}
    BOOL SetPropPrintBottomMargin(float v) {return SetProp(64,v);}

    BOOL GetPropPrintArea(string& v) {return GetProp(65,v);}
    BOOL SetPropPrintArea(string& v) {return SetProp(65,v);}

    BOOL GetPropPrintTitles(string& v) {return GetProp(66,v);}
    BOOL SetPropPrintTitles(string& v) {return SetProp(66,v);}

    BOOL GetPropPrintNoColor(BOOL& v) {return GetProp(67,v);}
    BOOL SetPropPrintNoColor(BOOL v) {return SetProp(67,v);}

    BOOL GetPropSelection(string& v) {return GetProp(68,v);}
    BOOL SetPropSelection(string& v) {return SetProp(68,v);}

    BOOL GetPropTableName(string& v) {return GetProp(71,v);}
    BOOL SetPropTableName(string& v) {return SetProp(71,v);}

    BOOL GetPropDoCancelEdit(BOOL& v) {return GetProp(74,v);}
    BOOL SetPropDoCancelEdit(BOOL v) {return SetProp(74,v);}

    BOOL GetPropDoSelChange(BOOL& v) {return GetProp(75,v);}
    BOOL SetPropDoSelChange(BOOL v) {return SetProp(75,v);}

    BOOL GetPropDoStartEdit(BOOL& v) {return GetProp(76,v);}
    BOOL SetPropDoStartEdit(BOOL v) {return SetProp(76,v);}

    BOOL GetPropDoEndEdit(BOOL& v) {return GetProp(77,v);}
    BOOL SetPropDoEndEdit(BOOL v) {return SetProp(77,v);}

    BOOL GetPropDoStartRecalc(BOOL& v) {return GetProp(78,v);}
    BOOL SetPropDoStartRecalc(BOOL v) {return SetProp(78,v);}

    BOOL GetPropDoEndRecalc(BOOL& v) {return GetProp(79,v);}
    BOOL SetPropDoEndRecalc(BOOL v) {return SetProp(79,v);}

    BOOL GetPropDoClick(BOOL& v) {return GetProp(80,v);}
    BOOL SetPropDoClick(BOOL v) {return SetProp(80,v);}

    BOOL GetPropDoDblClick(BOOL& v) {return GetProp(81,v);}
    BOOL SetPropDoDblClick(BOOL v) {return SetProp(81,v);}

    BOOL GetPropShowColHeading(BOOL& v) {return GetProp(89,v);}
    BOOL SetPropShowColHeading(BOOL v) {return SetProp(89,v);}

    BOOL GetPropPrintColHeading(BOOL& v) {return GetProp(90,v);}
    BOOL SetPropPrintColHeading(BOOL v) {return SetProp(90,v);}

    BOOL GetPropAbout_Formula_One(string& v) {return GetProp(92,v);}
    BOOL SetPropAbout_Formula_One(string& v) {return SetProp(92,v);}

    BOOL GetPropEntry(string& v) {return GetProp(93,v);}
    BOOL SetPropEntry(string& v) {return SetProp(93,v);}

    BOOL GetPropDataRowsBuffered(long& v) {return GetProp(94,v);}
    BOOL SetPropDataRowsBuffered(long v) {return SetProp(94,v);}

    BOOL GetPropDataRowBase(long& v) {return GetProp(95,v);}
    BOOL SetPropDataRowBase(long v) {return SetProp(95,v);}

    BOOL GetPropDoDataRowLoad(BOOL& v) {return GetProp(96,v);}
    BOOL SetPropDoDataRowLoad(BOOL v) {return SetProp(96,v);}

    BOOL GetPropDoDataNewRow(BOOL& v) {return GetProp(97,v);}
    BOOL SetPropDoDataNewRow(BOOL v) {return SetProp(97,v);}

    BOOL GetPropRepaint(BOOL& v) {return GetProp(98,v);}
    BOOL SetPropRepaint(BOOL v) {return SetProp(98,v);}

    BOOL GetPropAllowArrows(BOOL& v) {return GetProp(99,v);}
    BOOL SetPropAllowArrows(BOOL v) {return SetProp(99,v);}

    BOOL GetPropAllowTabs(BOOL& v) {return GetProp(100,v);}
    BOOL SetPropAllowTabs(BOOL v) {return SetProp(100,v);}

    BOOL GetPropFormattedText(string& v) {return GetProp(101,v);}
    BOOL SetPropFormattedText(string& v) {return SetProp(101,v);}

    BOOL GetPropMousePointer(ENUM& v) {return GetProp(102,v);}
    BOOL SetPropMousePointer(ENUM v) {return SetProp(102,v);}

    BOOL GetPropRowMode(BOOL& v) {return GetProp(103,v);}
    BOOL SetPropRowMode(BOOL v) {return SetProp(103,v);}

    BOOL GetPropDataConnected(BOOL& v) {return GetProp(104,v);}
    BOOL SetPropDataConnected(BOOL v) {return SetProp(104,v);}

    BOOL GetPropDataAutoAddNew(BOOL& v) {return GetProp(105,v);}
    BOOL SetPropDataAutoAddNew(BOOL v) {return SetProp(105,v);}

    BOOL GetPropAllowDelete(BOOL& v) {return GetProp(106,v);}
    BOOL SetPropAllowDelete(BOOL v) {return SetProp(106,v);}

    BOOL GetPropDataHdrField(string& v) {return GetProp(107,v);}
    BOOL SetPropDataHdrField(string& v) {return SetProp(107,v);}

    BOOL GetPropEnableProtection(BOOL& v) {return GetProp(108,v);}
    BOOL SetPropEnableProtection(BOOL v) {return SetProp(108,v);}

    BOOL GetPropWriteExcel4(string& v) {return GetProp(109,v);}
    BOOL SetPropWriteExcel4(string& v) {return SetProp(109,v);}

    BOOL GetPropDataSetColumnFormats(BOOL& v) {return GetProp(110,v);}
    BOOL SetPropDataSetColumnFormats(BOOL v) {return SetProp(110,v);}

    BOOL GetPropDragIcon(HPIC& v) {return GetProp(111,v);}
    BOOL SetPropDragIcon(HPIC v) {return SetProp(111,v);}

    BOOL GetPropDragMode(ENUM& v) {return GetProp(112,v);}
    BOOL SetPropDragMode(ENUM v) {return SetProp(112,v);}

    BOOL GetPropMinCol(long& v) {return GetProp(113,v);}
    BOOL SetPropMinCol(long v) {return SetProp(113,v);}

    BOOL GetPropMinRow(long& v) {return GetProp(114,v);}
    BOOL SetPropMinRow(long v) {return SetProp(114,v);}

    BOOL GetPropDoTopLeftChanged(BOOL& v) {return GetProp(115,v);}
    BOOL SetPropDoTopLeftChanged(BOOL v) {return SetProp(115,v);}

    BOOL GetPropAllowEditHeaders(BOOL& v) {return GetProp(116,v);}
    BOOL SetPropAllowEditHeaders(BOOL v) {return SetProp(116,v);}

    BOOL GetPropApplication_Designer(string& v) {return GetProp(117,v);}
    BOOL SetPropApplication_Designer(string& v) {return SetProp(117,v);}

#if 0
  DECLARE_RESPONSE_TABLE(TVbxSSView);
#endif
};

#if 0
// OWL response table
DEFINE_RESPONSE_TABLE1(TVbxSSView, TVbxControl)
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_Click, EvClick ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_DblClick, EvDblClick ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_DragDrop, EvDragDrop ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_DragOver, EvDragOver ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_GotFocus, EvGotFocus ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_KeyDown, EvKeyDown ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_KeyPress, EvKeyPress ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_KeyUp, EvKeyUp ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_LostFocus, EvLostFocus ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_CancelEdit, EvCancelEdit ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_SelChange, EvSelChange ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_StartEdit, EvStartEdit ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_EndEdit, EvEndEdit ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_StartRecalc, EvStartRecalc ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_EndRecalc, EvEndRecalc ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_DataRowLoad, EvDataRowLoad ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_DataNewRow, EvDataNewRow ),
  EV_VBXEVENTINDEX( IDC_SSView, Event_SSView_TopLeftChanged, EvTopLeftChanged ),
END_RESPONSE_TABLE;
#endif

#endif

