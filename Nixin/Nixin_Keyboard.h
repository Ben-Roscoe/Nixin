#ifndef _NIXIN_KEYBOARD_H_
#define _NIXIN_KEYBOARD_H_

#include <stdint.h>
#include <limits>

namespace Nixin
{




	class Keyboard
	{


	public:



		//
		// Key
		// Identifies each key.
		//
		enum class Key
		{
		//  Name						 Value

#ifdef _WIN32
            LEFT_MOUSE_BUTTON_KEY		= 0x01,
            RIGHT_MOUSE_BUTTON_KEY		= 0x02,
            CANCEL						= 0x03,
            MIDDLE_MOUSE_BUTTON_KEY		= 0x04,
			X_BUTTON_1					= 0x05,
			X_BUTTON_2					= 0x06,
			BACK						= 0x08,
			TAB							= 0x09,
			CLEAR						= 0x0D,
			ENTER						= 0x0D,
			SHIFT						= 0x10,
			CONTROL						= 0x11,
			ALT							= 0x12,
			PAUSE						= 0x13,
			CAPS_LOCK					= 0x14,
			KANA						= 0x15,
			JUNJA						= 0x17,
			FINAL						= 0x18,
			HANJA						= 0x19,
			ESCAPE						= 0x1B,
			CONVERT						= 0x1C,
			NONCONVERT					= 0x1D,
			ACCEPT						= 0x1E,
			MODECHANGE					= 0x1F,
			SPACE						= 0x20,
			PAGE_UP						= 0x21,
			PAGE_DOWN					= 0x22,
			END							= 0x23,
			HOME						= 0x24,
			LEFT						= 0x25,
			UP							= 0x26,
			RIGHT						= 0x27,
			DOWN						= 0x28,
			SELECT						= 0x29,
			PRINT						= 0x2A,
			EXECUTE						= 0x2B,
			PRINT_SCREEN				= 0x2c,
			INSERT						= 0x2D,
			DEL							= 0x2E,
			HELP						= 0x2F,
			ZERO						= 0x30,
			ONE							= 0x31,
			TWO							= 0x32,
			THREE						= 0x33,
			FOUR						= 0x34,
			FIVE						= 0x35,
			SIX							= 0x36,
			SEVEN						= 0x37,
			EIGHT						= 0x38,
			NINE						= 0x39,
			A							= 0x41,
			B							= 0x42,
			C							= 0x43,
			D							= 0x44,
			E							= 0x45,
			F							= 0x46,
			G							= 0x47,
			H							= 0x48,
			I							= 0x49,
			J							= 0x4A,
			K							= 0x4B,
			L							= 0x4C,
			M							= 0x4D,
			N							= 0x4E,
			O							= 0x4F,
			P							= 0x50,
			Q							= 0x51,
			R							= 0x52,
			S							= 0x53,
			T							= 0x54,
			U							= 0x55,
			V							= 0x56,
			W							= 0x57,
			X							= 0x58,
			Y							= 0x59,
			Z							= 0x5A,
			LEFT_WINDOWS				= 0x5B,
			RIGHT_WINDOWS				= 0x5C,
			APP							= 0x5D,
			SLEEP						= 0x5F,
			NUM_0						= 0x60,
			NUM_1						= 0x61,
			NUM_2						= 0x62,
			NUM_3						= 0x63,
			NUM_4						= 0x64,
			NUM_5						= 0x65,
			NUM_6						= 0x66,
			NUM_7						= 0x67,
			NUM_8						= 0x68,
			NUM_9						= 0x69,
			MULTIPLY					= 0x6A,
			ADD							= 0x6B,
			SEPARATOR					= 0x6C,
			SUBTRACT					= 0x6D,
			DECIMAL_KEY					= 0x6E,
			DIVIDE						= 0x6F,
			F1							= 0x70,
			F2							= 0x71,
			F3							= 0x72,
			F4							= 0x73,
			F5							= 0x74,
			F6							= 0x75,
			F7							= 0x76,
			F8							= 0x77,
			F9							= 0x78,
			F10							= 0x79,
			F11							= 0x7A,
			F12							= 0x7B,
			F13							= 0x7C,
			F14							= 0x7D,
			F15							= 0x7E,
			F16							= 0x7F,
			F17							= 0x80,
			F18							= 0x81,
			F19							= 0x82,
			F20							= 0x83,
			F21							= 0x84,
			F22							= 0x85,
			F23							= 0x86,
			F24							= 0x87,
			NUM_LOCK					= 0x90,
			SCROLL_LOCK					= 0x91,
			LEFT_SHIFT					= 0xA0,
			RIGHT_SHIFT					= 0xA1,
			LEFT_CONTROL				= 0xA2,
			RIGHT_CONTROL				= 0xA3,
			LEFT_MENU					= 0xA4,
			RIGHT_MENU					= 0xA5,
			BROWSER_BACK				= 0xA6,
			BROWSER_FORWARD				= 0xA7,
			BROWSER_REFRESH				= 0xA8,
			BROWSER_STOP				= 0xA9,
			BROWSER_SEARCH				= 0xAA,
			BROWSER_FAVORITES			= 0xAB,
			BROWSER_HOME				= 0xAC,
			VOLUME_MUTE					= 0xAD,
			VOLUME_DOWN					= 0xAE,
			VOLUME_UP					= 0xAF,
			MEDIA_NEXT_TRACK			= 0xB0,
			MEDIA_PREV_TRACK			= 0xB1,
			MEDIA_STOP					= 0xB2,
			MEDIA_PLAY_PAUSE			= 0xB3,
			LAUNCH_MAIL					= 0xB4,
			LAUNCH_MEDIA_SELECT			= 0xB5,
			LAUNCH_APP1					= 0xB6,
			LAUNCH_APP2					= 0xB7,
			OEM							= 0xBA,
			OEM_PLUS					= 0xBB,
			OEM_COMMA					= 0xBC,
			OEM_MINUS					= 0xBD,
			OEM_PERIOD					= 0xBE,
			OEM_2						= 0xBF,
			OEM_3						= 0xC0,
			OEM_4						= 0xDB,
			OEM_5						= 0xDC,
			OEM_6						= 0xDD,
			OEM_7						= 0xDE,
			OEM_8						= 0xDF,
			OEM_102						= 0xE2,
			PROCESS_KEY					= 0xE5,
			ATTN						= 0xF6,
			CRSEL						= 0xF7,
			EXSEL						= 0xF8,
			EREOF						= 0xF9,
			PLAY						= 0xFA,
			ZOOM						= 0xFB,
			PA1							= 0xFD,
			OEM_CLEAR					= 0XFE,
#endif
#ifdef __linux
             BackSpace                                             =  0xff08,
             Tab                                                   =  0xff09,
             Linefeed                                              =  0xff0a,
             Clear                                                 =  0xff0b,
             Return                                                =  0xff0d,
             Pause                                                 =  0xff13,
             Scroll_Lock                                           =  0xff14,
             Sys_Req                                               =  0xff15,
             Escape                                                =  0xff1b,
             Delete                                                =  0xffff,
             Multi_key                                             =  0xff20,
             Codeinput                                             =  0xff37,
             SingleCandidate                                       =  0xff3c,
             MultipleCandidate                                     =  0xff3d,
             PreviousCandidate                                     =  0xff3e,
             Kanji                                                 =  0xff21,
             Muhenkan                                              =  0xff22,
             Henkan_Mode                                           =  0xff23,
             Henkan                                                =  0xff23,
             Romaji                                                =  0xff24,
             Hiragana                                              =  0xff25,
             Katakana                                              =  0xff26,
             Hiragana_Katakana                                     =  0xff27,
             Zenkaku                                               =  0xff28,
             Hankaku                                               =  0xff29,
             Zenkaku_Hankaku                                       =  0xff2a,
             Touroku                                               =  0xff2b,
             Massyo                                                =  0xff2c,
             Kana_Lock                                             =  0xff2d,
             Kana_Shift                                            =  0xff2e,
             Eisu_Shift                                            =  0xff2f,
             Eisu_toggle                                           =  0xff30,
             Kanji_Bangou                                          =  0xff37,
             Zen_Koho                                              =  0xff3d,
             Mae_Koho                                              =  0xff3e,
             Home                                                  =  0xff50,
             Left                                                  =  0xff51,
             Up                                                    =  0xff52,
             Right                                                 =  0xff53,
             Down                                                  =  0xff54,
             Prior                                                 =  0xff55,
             Page_Up                                               =  0xff55,
             Next                                                  =  0xff56,
             Page_Down                                             =  0xff56,
             End                                                   =  0xff57,
             Begin                                                 =  0xff58,
             Select                                                =  0xff60,
             Print                                                 =  0xff61,
             Execute                                               =  0xff62,
             Insert                                                =  0xff63,
             Undo                                                  =  0xff65,
             Redo                                                  =  0xff66,
             Menu                                                  =  0xff67,
             Find                                                  =  0xff68,
             Cancel                                                =  0xff69,
             Help                                                  =  0xff6a,
             Break                                                 =  0xff6b,
             Mode_switch                                           =  0xff7e,
             script_switch                                         =  0xff7e,
             Num_Lock                                              =  0xff7f,
             KP_Space                                              =  0xff80,
             KP_Tab                                                =  0xff89,
             KP_Enter                                              =  0xff8d,
             KP_F1                                                 =  0xff91,
             KP_F2                                                 =  0xff92,
             KP_F3                                                 =  0xff93,
             KP_F4                                                 =  0xff94,
             KP_Home                                               =  0xff95,
             KP_Left                                               =  0xff96,
             KP_Up                                                 =  0xff97,
             KP_Right                                              =  0xff98,
             KP_Down                                               =  0xff99,
             KP_Prior                                              =  0xff9a,
             KP_Page_Up                                            =  0xff9a,
             KP_Next                                               =  0xff9b,
             KP_Page_Down                                          =  0xff9b,
             KP_End                                                =  0xff9c,
             KP_Begin                                              =  0xff9d,
             KP_Insert                                             =  0xff9e,
             KP_Delete                                             =  0xff9f,
             KP_Equal                                              =  0xffbd,
             KP_Multiply                                           =  0xffaa,
             KP_Add                                                =  0xffab,
             KP_Separator                                          =  0xffac,
             KP_Subtract                                           =  0xffad,
             KP_Decimal                                            =  0xffae,
             KP_Divide                                             =  0xffaf,
             KP_0                                                  =  0xffb0,
             KP_1                                                  =  0xffb1,
             KP_2                                                  =  0xffb2,
             KP_3                                                  =  0xffb3,
             KP_4                                                  =  0xffb4,
             KP_5                                                  =  0xffb5,
             KP_6                                                  =  0xffb6,
             KP_7                                                  =  0xffb7,
             KP_8                                                  =  0xffb8,
             KP_9                                                  =  0xffb9,
             F1                                                    =  0xffbe,
             F2                                                    =  0xffbf,
             F3                                                    =  0xffc0,
             F4                                                    =  0xffc1,
             F5                                                    =  0xffc2,
             F6                                                    =  0xffc3,
             F7                                                    =  0xffc4,
             F8                                                    =  0xffc5,
             F9                                                    =  0xffc6,
             F10                                                   =  0xffc7,
             F11                                                   =  0xffc8,
             L1                                                    =  0xffc8,
             F12                                                   =  0xffc9,
             L2                                                    =  0xffc9,
             F13                                                   =  0xffca,
             L3                                                    =  0xffca,
             F14                                                   =  0xffcb,
             L4                                                    =  0xffcb,
             F15                                                   =  0xffcc,
             L5                                                    =  0xffcc,
             F16                                                   =  0xffcd,
             L6                                                    =  0xffcd,
             F17                                                   =  0xffce,
             L7                                                    =  0xffce,
             F18                                                   =  0xffcf,
             L8                                                    =  0xffcf,
             F19                                                   =  0xffd0,
             L9                                                    =  0xffd0,
             F20                                                   =  0xffd1,
             L10                                                   =  0xffd1,
             F21                                                   =  0xffd2,
             R1                                                    =  0xffd2,
             F22                                                   =  0xffd3,
             R2                                                    =  0xffd3,
             F23                                                   =  0xffd4,
             R3                                                    =  0xffd4,
             F24                                                   =  0xffd5,
             R4                                                    =  0xffd5,
             F25                                                   =  0xffd6,
             R5                                                    =  0xffd6,
             F26                                                   =  0xffd7,
             R6                                                    =  0xffd7,
             F27                                                   =  0xffd8,
             R7                                                    =  0xffd8,
             F28                                                   =  0xffd9,
             R8                                                    =  0xffd9,
             F29                                                   =  0xffda,
             R9                                                    =  0xffda,
             F30                                                   =  0xffdb,
             R10                                                   =  0xffdb,
             F31                                                   =  0xffdc,
             R11                                                   =  0xffdc,
             F32                                                   =  0xffdd,
             R12                                                   =  0xffdd,
             F33                                                   =  0xffde,
             R13                                                   =  0xffde,
             F34                                                   =  0xffdf,
             R14                                                   =  0xffdf,
             F35                                                   =  0xffe0,
             R15                                                   =  0xffe0,
             Shift_L                                               =  0xffe1,
             Shift_R                                               =  0xffe2,
             Control_L                                             =  0xffe3,
             Control_R                                             =  0xffe4,
             Caps_Lock                                             =  0xffe5,
             Shift_Lock                                            =  0xffe6,
             Meta_L                                                =  0xffe7,
             Meta_R                                                =  0xffe8,
             Alt_L                                                 =  0xffe9,
             Alt_R                                                 =  0xffea,
             Super_L                                               =  0xffeb,
             Super_R                                               =  0xffec,
             Hyper_L                                               =  0xffed,
             Hyper_R                                               =  0xffee,
             KB_KEYS                                               =  0xfe01,
             ISO_Lock                                              =  0xfe02,
             ISO_Level2_Latch                                      =  0xfe03,
             ISO_Level3_Shift                                      =  0xfe04,
             ISO_Level3_Latch                                      =  0xfe05,
             ISO_Level3_Lock                                       =  0xfe11,
             ISO_Level5_Shift                                      =  0xfe12,
             ISO_Level5_Latch                                      =  0xfe13,
             ISO_Level5_Lock                                       =  0xff7e,
             ISO_Group_Shift                                       =  0xfe06,
             ISO_Group_Latch                                       =  0xfe07,
             ISO_Group_Lock                                        =  0xfe08,
             ISO_Next_Group                                        =  0xfe09,
             ISO_Next_Group_Lock                                   =  0xfe0a,
             ISO_Prev_Group                                        =  0xfe0b,
             ISO_Prev_Group_Lock                                   =  0xfe0c,
             ISO_First_Group                                       =  0xfe0d,
             ISO_First_Group_Lock                                  =  0xfe0e,
             ISO_Last_Group                                        =  0xfe0f,
             ISO_Last_Group_Lock                                   =  0xfe20,
             ISO_Left_Tab                                          =  0xfe21,
             ISO_Move_Line_Up                                      =  0xfe22,
             ISO_Move_Line_Down                                    =  0xfe23,
             ISO_Partial_Line_Up                                   =  0xfe24,
             ISO_Partial_Line_Down                                 =  0xfe25,
             ISO_Partial_Space_Left                                =  0xfe26,
             ISO_Partial_Space_Right                               =  0xfe27,
             ISO_Set_Margin_Left                                   =  0xfe28,
             ISO_Set_Margin_Right                                  =  0xfe29,
             ISO_Release_Margin_Left                               =  0xfe2a,
             ISO_Release_Margin_Right                              =  0xfe2b,
             ISO_Release_Both_Margins                              =  0xfe2c,
             ISO_Fast_Cursor_Left                                  =  0xfe2d,
             ISO_Fast_Cursor_Right                                 =  0xfe2e,
             ISO_Fast_Cursor_Up                                    =  0xfe2f,
             ISO_Fast_Cursor_Down                                  =  0xfe30,
             ISO_Continuous_Underline                              =  0xfe31,
             ISO_Discontinuous_Underline                           =  0xfe32,
             ISO_Emphasize                                         =  0xfe33,
             ISO_Center_Object                                     =  0xfe34,
             ISO_Enter                                             =  0xfe50,
             dead_grave                                            =  0xfe51,
             dead_acute                                            =  0xfe52,
             dead_circumflex                                       =  0xfe53,
             dead_tilde                                            =  0xfe53,
             dead_perispomeni                                      =  0xfe54,
             dead_macron                                           =  0xfe55,
             dead_breve                                            =  0xfe56,
             dead_abovedot                                         =  0xfe57,
             dead_diaeresis                                        =  0xfe58,
             dead_abovering                                        =  0xfe59,
             dead_doubleacute                                      =  0xfe5a,
             dead_caron                                            =  0xfe5b,
             dead_cedilla                                          =  0xfe5c,
             dead_ogonek                                           =  0xfe5d,
             dead_iota                                             =  0xfe5e,
             dead_voiced_sound                                     =  0xfe5f,
             dead_semivoiced_sound                                 =  0xfe60,
             dead_belowdot                                         =  0xfe61,
             dead_hook                                             =  0xfe62,
             dead_horn                                             =  0xfe63,
             dead_stroke                                           =  0xfe64,
             dead_abovecomma                                       =  0xfe64,
             dead_psili                                            =  0xfe65,
             dead_abovereversedcomma                               =  0xfe65,
             dead_dasia                                            =  0xfe66,
             dead_doublegrave                                      =  0xfe67,
             dead_belowring                                        =  0xfe68,
             dead_belowmacron                                      =  0xfe69,
             dead_belowcircumflex                                  =  0xfe6a,
             dead_belowtilde                                       =  0xfe6b,
             dead_belowbreve                                       =  0xfe6c,
             dead_belowdiaeresis                                   =  0xfe6d,
             dead_invertedbreve                                    =  0xfe6e,
             dead_belowcomma                                       =  0xfe6f,
             dead_currency                                         =  0xfe80,
             dead_a                                                =  0xfe81,
             dead_A                                                =  0xfe82,
             dead_e                                                =  0xfe83,
             dead_E                                                =  0xfe84,
             dead_i                                                =  0xfe85,
             dead_I                                                =  0xfe86,
             dead_o                                                =  0xfe87,
             dead_O                                                =  0xfe88,
             dead_u                                                =  0xfe89,
             dead_U                                                =  0xfe8a,
             dead_small_schwa                                      =  0xfe8b,
             dead_capital_schwa                                    =  0xfe8c,
             dead_greek                                            =  0xfed0,
             First_Virtual_Screen                                  =  0xfed1,
             Prev_Virtual_Screen                                   =  0xfed2,
             Next_Virtual_Screen                                   =  0xfed4,
             Last_Virtual_Screen                                   =  0xfed5,
             Terminate_Server                                      =  0xfe70,
             AccessX_Enable                                        =  0xfe71,
             AccessX_Feedback_Enable                               =  0xfe72,
             RepeatKeys_Enable                                     =  0xfe73,
             SlowKeys_Enable                                       =  0xfe74,
             BounceKeys_Enable                                     =  0xfe75,
             StickyKeys_Enable                                     =  0xfe76,
             MouseKeys_Enable                                      =  0xfe77,
             MouseKeys_Accel_Enable                                =  0xfe78,
             Overlay1_Enable                                       =  0xfe79,
             Overlay2_Enable                                       =  0xfe7a,
             AudibleBell_Enable                                    =  0xfee0,
             Pointer_Left                                          =  0xfee1,
             Pointer_Right                                         =  0xfee2,
             Pointer_Up                                            =  0xfee3,
             Pointer_Down                                          =  0xfee4,
             Pointer_UpLeft                                        =  0xfee5,
             Pointer_UpRight                                       =  0xfee6,
             Pointer_DownLeft                                      =  0xfee7,
             Pointer_DownRight                                     =  0xfee8,
             Pointer_Button_Dflt                                   =  0xfee9,
             Pointer_Button1                                       =  0xfeea,
             Pointer_Button2                                       =  0xfeeb,
             Pointer_Button3                                       =  0xfeec,
             Pointer_Button4                                       =  0xfeed,
             Pointer_Button5                                       =  0xfeee,
             Pointer_DblClick_Dflt                                 =  0xfeef,
             Pointer_DblClick1                                     =  0xfef0,
             Pointer_DblClick2                                     =  0xfef1,
             Pointer_DblClick3                                     =  0xfef2,
             Pointer_DblClick4                                     =  0xfef3,
             Pointer_DblClick5                                     =  0xfef4,
             Pointer_Drag_Dflt                                     =  0xfef5,
             Pointer_Drag1                                         =  0xfef6,
             Pointer_Drag2                                         =  0xfef7,
             Pointer_Drag3                                         =  0xfef8,
             Pointer_Drag4                                         =  0xfefd,
             Pointer_Drag5                                         =  0xfef9,
             Pointer_EnableKeys                                    =  0xfefa,
             Pointer_Accelerate                                    =  0xfefb,
             Pointer_DfltBtnNext                                   =  0xfefc,
             Pointer_DfltBtnPrev                                   =  0xfea0,
             ch                                                    =  0xfea1,
             Ch                                                    =  0xfea2,
             CH                                                    =  0xfea3,
             c_h                                                   =  0xfea4,
             C_h                                                   =  0xfea5,
             C_H                                                   =  0xfd01,
             K3270                                                 =  0xfd02,
             K3270_Duplicate                                       =  0xfd03,
             K3270_FieldMark                                       =  0xfd04,
             K3270_Right2                                          =  0xfd05,
             K3270_Left2                                           =  0xfd06,
             K3270_BackTab                                         =  0xfd07,
             K3270_EraseEOF                                        =  0xfd08,
             K3270_EraseInput                                      =  0xfd09,
             K3270_Reset                                           =  0xfd0a,
             K3270_Quit                                            =  0xfd0b,
             K3270_PA1                                             =  0xfd0c,
             K3270_PA2                                             =  0xfd0d,
             K3270_PA3                                             =  0xfd0e,
             K3270_Test                                            =  0xfd0f,
             K3270_Attn                                            =  0xfd10,
             K3270_CursorBlink                                     =  0xfd11,
             K3270_AltCursor                                       =  0xfd12,
             K3270_KeyClick                                        =  0xfd13,
             K3270_Jump                                            =  0xfd14,
             K3270_Ident                                           =  0xfd15,
             K3270_Rule                                            =  0xfd16,
             K3270_Copy                                            =  0xfd17,
             K3270_Play                                            =  0xfd18,
             K3270_Setup                                           =  0xfd19,
             K3270_Record                                          =  0xfd1a,
             K3270_ChangeScreen                                    =  0xfd1b,
             K3270_DeleteWord                                      =  0xfd1c,
             K3270_ExSelect                                        =  0xfd1d,
             K3270_CursorSelect                                    =  0xfd1e,
             K3270_PrintScreen                                     =  0x0020,
             K3270_Enter                                           =  0x0021,
             space                                                 =  0x0022,
             exclam                                                =  0x0023,
             quotedbl                                              =  0x0024,
             numbersign                                            =  0x0025,
             dollar                                                =  0x0026,
             percent                                               =  0x0027,
             ampersand                                             =  0x0027,
             apostrophe                                            =  0x0028,
             quoteright                                            =  0x0029,
             parenleft                                             =  0x002a,
             parenright                                            =  0x002b,
             asterisk                                              =  0x002c,
             plus                                                  =  0x002d,
             comma                                                 =  0x002e,
             minus                                                 =  0x002f,
             period                                                =  0x0030,
             slash                                                 =  0x0031,
             Num_0                                                 =  0x0032,
             Num_1                                                 =  0x0033,
             Num_2                                                 =  0x0034,
             Num_3                                                 =  0x0035,
             Num_4                                                 =  0x0036,
             Num_5                                                 =  0x0037,
             Num_6                                                 =  0x0038,
             Num_7                                                 =  0x0039,
             Num_8                                                 =  0x003a,
             Num_9                                                 =  0x003b,
             colon                                                 =  0x003c,
             semicolon                                             =  0x003d,
             less                                                  =  0x003e,
             equal                                                 =  0x003f,
             greater                                               =  0x0040,
             question                                              =  0x0041,
             at                                                    =  0x0042,
             A                                                     =  0x0043,
             B                                                     =  0x0044,
             C                                                     =  0x0045,
             D                                                     =  0x0046,
             E                                                     =  0x0047,
             F                                                     =  0x0048,
             G                                                     =  0x0049,
             H                                                     =  0x004a,
             I                                                     =  0x004b,
             J                                                     =  0x004c,
             K                                                     =  0x004d,
             L                                                     =  0x004e,
             M                                                     =  0x004f,
             N                                                     =  0x0050,
             O                                                     =  0x0051,
             P                                                     =  0x0052,
             Q                                                     =  0x0053,
             R                                                     =  0x0054,
             S                                                     =  0x0055,
             T                                                     =  0x0056,
             U                                                     =  0x0057,
             V                                                     =  0x0058,
             W                                                     =  0x0059,
             X                                                     =  0x005a,
             Y                                                     =  0x005b,
             Z                                                     =  0x005c,
             bracketleft                                           =  0x005d,
             backslash                                             =  0x005e,
             bracketright                                          =  0x005f,
             asciicircum                                           =  0x0060,
             underscore                                            =  0x0060,
             grave                                                 =  0x0061,
             quoteleft                                             =  0x0062,
             a                                                     =  0x0063,
             b                                                     =  0x0064,
             c                                                     =  0x0065,
             d                                                     =  0x0066,
             e                                                     =  0x0067,
             f                                                     =  0x0068,
             g                                                     =  0x0069,
             h                                                     =  0x006a,
             i                                                     =  0x006b,
             j                                                     =  0x006c,
             k                                                     =  0x006d,
             l                                                     =  0x006e,
             m                                                     =  0x006f,
             n                                                     =  0x0070,
             o                                                     =  0x0071,
             p                                                     =  0x0072,
             q                                                     =  0x0073,
             r                                                     =  0x0074,
             s                                                     =  0x0075,
             t                                                     =  0x0076,
             u                                                     =  0x0077,
             v                                                     =  0x0078,
             w                                                     =  0x0079,
             x                                                     =  0x007a,
             y                                                     =  0x007b,
             z                                                     =  0x007c,
             braceleft                                             =  0x007d,
             bar                                                   =  0x007e,
             braceright                                            =  0x00a0,
             asciitilde                                            =  0x00a1,
             nobreakspace                                          =  0x00a2,
             exclamdown                                            =  0x00a3,
             cent                                                  =  0x00a4,
             sterling                                              =  0x00a5,
             currency                                              =  0x00a6,
             yen                                                   =  0x00a7,
             brokenbar                                             =  0x00a8,
             section                                               =  0x00a9,
             diaeresis                                             =  0x00aa,
             copyright                                             =  0x00ab,
             ordfeminine                                           =  0x00ac,
             guillemotleft                                         =  0x00ad,
             notsign                                               =  0x00ae,
             hyphen                                                =  0x00af,
             registered                                            =  0x00b0,
             macron                                                =  0x00b1,
             degree                                                =  0x00b2,
             plusminus                                             =  0x00b3,
             twosuperior                                           =  0x00b4,
             threesuperior                                         =  0x00b5,
             acute                                                 =  0x00b6,
             mu                                                    =  0x00b7,
             paragraph                                             =  0x00b8,
             periodcentered                                        =  0x00b9,
             cedilla                                               =  0x00ba,
             onesuperior                                           =  0x00bb,
             masculine                                             =  0x00bc,
             guillemotright                                        =  0x00bd,
             onequarter                                            =  0x00be,
             onehalf                                               =  0x00bf,
             threequarters                                         =  0x00c0,
             questiondown                                          =  0x00c1,
             Agrave                                                =  0x00c2,
             Aacute                                                =  0x00c3,
             Acircumflex                                           =  0x00c4,
             Atilde                                                =  0x00c5,
             Adiaeresis                                            =  0x00c6,
             Aring                                                 =  0x00c7,
             AE                                                    =  0x00c8,
             Ccedilla                                              =  0x00c9,
             Egrave                                                =  0x00ca,
             Eacute                                                =  0x00cb,
             Ecircumflex                                           =  0x00cc,
             Ediaeresis                                            =  0x00cd,
             Igrave                                                =  0x00ce,
             Iacute                                                =  0x00cf,
             Icircumflex                                           =  0x00d0,
             Idiaeresis                                            =  0x00d0,
             ETH                                                   =  0x00d1,
             Eth                                                   =  0x00d2,
             Ntilde                                                =  0x00d3,
             Ograve                                                =  0x00d4,
             Oacute                                                =  0x00d5,
             Ocircumflex                                           =  0x00d6,
             Otilde                                                =  0x00d7,
             Odiaeresis                                            =  0x00d8,
             multiply                                              =  0x00d8,
             Oslash                                                =  0x00d9,
             Ooblique                                              =  0x00da,
             Ugrave                                                =  0x00db,
             Uacute                                                =  0x00dc,
             Ucircumflex                                           =  0x00dd,
             Udiaeresis                                            =  0x00de,
             Yacute                                                =  0x00de,
             THORN                                                 =  0x00df,
             Thorn                                                 =  0x00e0,
             ssharp                                                =  0x00e1,
             agrave                                                =  0x00e2,
             aacute                                                =  0x00e3,
             acircumflex                                           =  0x00e4,
             atilde                                                =  0x00e5,
             adiaeresis                                            =  0x00e6,
             aring                                                 =  0x00e7,
             ae                                                    =  0x00e8,
             ccedilla                                              =  0x00e9,
             egrave                                                =  0x00ea,
             eacute                                                =  0x00eb,
             ecircumflex                                           =  0x00ec,
             ediaeresis                                            =  0x00ed,
             igrave                                                =  0x00ee,
             iacute                                                =  0x00ef,
             icircumflex                                           =  0x00f0,
             idiaeresis                                            =  0x00f1,
             eth                                                   =  0x00f2,
             ntilde                                                =  0x00f3,
             ograve                                                =  0x00f4,
             oacute                                                =  0x00f5,
             ocircumflex                                           =  0x00f6,
             otilde                                                =  0x00f7,
             odiaeresis                                            =  0x00f8,
             division                                              =  0x00f8,
             oslash                                                =  0x00f9,
             ooblique                                              =  0x00fa,
             ugrave                                                =  0x00fb,
             uacute                                                =  0x00fc,
             ucircumflex                                           =  0x00fd,
             udiaeresis                                            =  0x00fe,
             yacute                                                =  0x00ff,
             thorn                                                 =  0x01a1,
             ydiaeresis                                            =  0x01a2,
             Aogonek                                               =  0x01a3,
             breve                                                 =  0x01a5,
             Lstroke                                               =  0x01a6,
             Lcaron                                                =  0x01a9,
             Sacute                                                =  0x01aa,
             Scaron                                                =  0x01ab,
             Scedilla                                              =  0x01ac,
             Tcaron                                                =  0x01ae,
             Zacute                                                =  0x01af,
             Zcaron                                                =  0x01b1,
             Zabovedot                                             =  0x01b2,
             aogonek                                               =  0x01b3,
             ogonek                                                =  0x01b5,
             lstroke                                               =  0x01b6,
             lcaron                                                =  0x01b7,
             sacute                                                =  0x01b9,
             caron                                                 =  0x01ba,
             scaron                                                =  0x01bb,
             scedilla                                              =  0x01bc,
             tcaron                                                =  0x01bd,
             zacute                                                =  0x01be,
             doubleacute                                           =  0x01bf,
             zcaron                                                =  0x01c0,
             zabovedot                                             =  0x01c3,
             Racute                                                =  0x01c5,
             Abreve                                                =  0x01c6,
             Lacute                                                =  0x01c8,
             Cacute                                                =  0x01ca,
             Ccaron                                                =  0x01cc,
             Eogonek                                               =  0x01cf,
             Ecaron                                                =  0x01d0,
             Dcaron                                                =  0x01d1,
             Dstroke                                               =  0x01d2,
             Nacute                                                =  0x01d5,
             Ncaron                                                =  0x01d8,
             Odoubleacute                                          =  0x01d9,
             Rcaron                                                =  0x01db,
             Uring                                                 =  0x01de,
             Udoubleacute                                          =  0x01e0,
             Tcedilla                                              =  0x01e3,
             racute                                                =  0x01e5,
             abreve                                                =  0x01e6,
             lacute                                                =  0x01e8,
             cacute                                                =  0x01ea,
             ccaron                                                =  0x01ec,
             eogonek                                               =  0x01ef,
             ecaron                                                =  0x01f0,
             dcaron                                                =  0x01f1,
             dstroke                                               =  0x01f2,
             nacute                                                =  0x01f5,
             ncaron                                                =  0x01f8,
             odoubleacute                                          =  0x01f9,
             rcaron                                                =  0x01fb,
             uring                                                 =  0x01fe,
             udoubleacute                                          =  0x01ff,
             tcedilla                                              =  0x02a1,
             abovedot                                              =  0x02a6,
             Hstroke                                               =  0x02a9,
             Hcircumflex                                           =  0x02ab,
             Iabovedot                                             =  0x02ac,
             Gbreve                                                =  0x02b1,
             Jcircumflex                                           =  0x02b6,
             hstroke                                               =  0x02b9,
             hcircumflex                                           =  0x02bb,
             idotless                                              =  0x02bc,
             gbreve                                                =  0x02c5,
             jcircumflex                                           =  0x02c6,
             Cabovedot                                             =  0x02d5,
             Ccircumflex                                           =  0x02d8,
             Gabovedot                                             =  0x02dd,
             Gcircumflex                                           =  0x02de,
             Ubreve                                                =  0x02e5,
             Scircumflex                                           =  0x02e6,
             cabovedot                                             =  0x02f5,
             ccircumflex                                           =  0x02f8,
             gabovedot                                             =  0x02fd,
             gcircumflex                                           =  0x02fe,
             ubreve                                                =  0x03a2,
             scircumflex                                           =  0x03a2,
             kra                                                   =  0x03a3,
             kappa                                                 =  0x03a5,
             Rcedilla                                              =  0x03a6,
             Itilde                                                =  0x03aa,
             Lcedilla                                              =  0x03ab,
             Emacron                                               =  0x03ac,
             Gcedilla                                              =  0x03b3,
             Tslash                                                =  0x03b5,
             rcedilla                                              =  0x03b6,
             itilde                                                =  0x03ba,
             lcedilla                                              =  0x03bb,
             emacron                                               =  0x03bc,
             gcedilla                                              =  0x03bd,
             tslash                                                =  0x03bf,
             ENG                                                   =  0x03c0,
             eng                                                   =  0x03c7,
             Amacron                                               =  0x03cc,
             Iogonek                                               =  0x03cf,
             Eabovedot                                             =  0x03d1,
             Imacron                                               =  0x03d2,
             Ncedilla                                              =  0x03d3,
             Omacron                                               =  0x03d9,
             Kcedilla                                              =  0x03dd,
             Uogonek                                               =  0x03de,
             Utilde                                                =  0x03e0,
             Umacron                                               =  0x03e7,
             amacron                                               =  0x03ec,
             iogonek                                               =  0x03ef,
             eabovedot                                             =  0x03f1,
             imacron                                               =  0x03f2,
             ncedilla                                              =  0x03f3,
             omacron                                               =  0x03f9,
             kcedilla                                              =  0x03fd,
             uogonek                                               =  0x03fe,
             utilde
#endif       umacron
        };



        static void						Initialise();												// Initialise the keyboard.
        static void						SetKey( const uint16_t wParam, const bool isDown );         // Sets a key's state.
        static bool						IsKeyDown( const Key key );									// Checks if a certain key is down.
        static bool						IsKeyUp( const Key key );									// Checks if a certain key is up.
        static bool						IsAnyKeyDown();												// Checks if any key is down.



    private:

        static bool						keys[65536];                            					// True if key is down, false otherwise.
		static int						inputs;														// Number of keys being pressed.



	};
}


#endif
















































































































































































































































































































































































































































































































































































































































































