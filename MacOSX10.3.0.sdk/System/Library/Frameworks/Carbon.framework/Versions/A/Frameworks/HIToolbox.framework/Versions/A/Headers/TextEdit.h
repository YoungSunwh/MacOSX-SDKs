/*
     File:       HIToolbox/TextEdit.h
 
     Contains:   TextEdit Interfaces.
 
     Version:    HIToolbox-145.33~1
 
     Copyright:  ? 1985-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TEXTEDIT__
#define __TEXTEDIT__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef struct TERec                    TERec;
typedef TERec *                         TEPtr;
typedef TEPtr *                         TEHandle;
typedef CALLBACK_API( void , HighHookProcPtr )(const Rect *r, TEPtr pTE);
typedef CALLBACK_API( Boolean , EOLHookProcPtr )(char theChar, TEPtr pTE, TEHandle hTE);
typedef CALLBACK_API( void , CaretHookProcPtr )(const Rect *r, TEPtr pTE);
typedef CALLBACK_API( unsigned short , WidthHookProcPtr )(unsigned short textLen, unsigned short textOffset, void *textBufferPtr, TEPtr pTE, TEHandle hTE);
typedef CALLBACK_API( unsigned short , TextWidthHookProcPtr )(unsigned short textLen, unsigned short textOffset, void *textBufferPtr, TEPtr pTE, TEHandle hTE);
typedef CALLBACK_API( unsigned short , NWidthHookProcPtr )(unsigned short styleRunLen, unsigned short styleRunOffset, short slop, short direction, void *textBufferPtr, short *lineStart, TEPtr pTE, TEHandle hTE);
typedef CALLBACK_API( void , DrawHookProcPtr )(unsigned short textOffset, unsigned short drawLen, void *textBufferPtr, TEPtr pTE, TEHandle hTE);
typedef CALLBACK_API( Boolean , HitTestHookProcPtr )(unsigned short styleRunLen, unsigned short styleRunOffset, unsigned short slop, void *textBufferPtr, TEPtr pTE, TEHandle hTE, unsigned short *pixelWidth, unsigned short *charOffset, Boolean *pixelInChar);
typedef CALLBACK_API( void , TEFindWordProcPtr )(unsigned short currentPos, short caller, TEPtr pTE, TEHandle hTE, unsigned short *wordStart, unsigned short *wordEnd);
typedef CALLBACK_API( void , TERecalcProcPtr )(TEPtr pTE, unsigned short changeLength, unsigned short *lineStart, unsigned short *firstChar, unsigned short *lastChar);
typedef CALLBACK_API( void , TEDoTextProcPtr )(TEPtr pTE, unsigned short firstChar, unsigned short lastChar, short selector, GrafPtr *currentGrafPort, short *charPosition);
typedef CALLBACK_API( Boolean , TEClickLoopProcPtr )(TEPtr pTE);
typedef CALLBACK_API( Boolean , WordBreakProcPtr )(Ptr text, short charPos);
/* 
    Important note about TEClickLoopProcPtr and WordBreakProcPtr

    At one point these were defined as returning the function result in the 
    condition code Z-bit.  This was correct, in that it was what the 68K
    implementation of TextEdit actually tested.  But, MixedMode had a different 
    idea of what returning a boolean in the Z-bit meant.  MixedMode was setting
    the Z-bit the complement of what was wanted.  
    
    Therefore, these ProcPtrs have been changed (back) to return the result in
    register D0.  It turns out that for register based routines, 
    MixedMode sets the Z-bit of the 68K emulator based on the contents 
    of the return result register.  Thus we can get the Z-bit set correctly.  
    
    But, when TextEdit is recoded in PowerPC, if it calls a 68K ClickLoop
    or WordBreak routine, register D0 had better have the result (in addition
    to the Z-bit). Therefore all 68K apps should make sure their ClickLoop or
    WordBreak routines set register D0 at the end.
*/

/* 
    There is no function to get/set the low-mem for FindWordHook at 0x07F8.
    This is because it is not a low-mem ProcPtr. That address is the entry
    in the OS TrapTable for trap 0xA0FE.  You can use Get/SetTrapAddress to 
    acccess it. 
*/

/*
    The following ProcPtrs cannot be written in or called from a high-level 
    language without the help of mixed mode or assembly glue because they 
    use the following parameter-passing conventions:

    typedef pascal void (*HighHookProcPtr)(const Rect *r, TEPtr pTE);
    typedef pascal void (*CaretHookProcPtr)(const Rect *r, TEPtr pTE);

        In:
            =>  r                       on stack
            =>  pTE                     A3.L
        Out:
            none

    typedef pascal Boolean (*EOLHookProcPtr)(char theChar, TEPtr pTE, TEHandle hTE);

        In:
            =>  theChar                 D0.B
            =>  pTE                     A3.L
            =>  hTE                     A4.L
        Out:
            <=  Boolean                 Z bit of the CCR

    typedef pascal unsigned short (*WidthHookProcPtr)(unsigned short textLen,
     unsigned short textOffset, void *textBufferPtr, TEPtr pTE, TEHandle hTE);
    typedef pascal unsigned short (*TextWidthHookProcPtr)(unsigned short textLen,
     unsigned short textOffset, void *textBufferPtr, TEPtr pTE, TEHandle hTE);

        In:
            =>  textLen                 D0.W
            =>  textOffset              D1.W
            =>  textBufferPtr           A0.L
            =>  pTE                     A3.L
            =>  hTE                     A4.L
        Out:
            <=  unsigned short          D1.W

    typedef pascal unsigned short (*NWidthHookProcPtr)(unsigned short styleRunLen,
     unsigned short styleRunOffset, short slop, short direction, void *textBufferPtr, 
     short *lineStart, TEPtr pTE, TEHandle hTE);

        In:
            =>  styleRunLen             D0.W
            =>  styleRunOffset          D1.W
            =>  slop                    D2.W (low)
            =>  direction               D2.W (high)
            =>  textBufferPtr           A0.L
            =>  lineStart               A2.L
            =>  pTE                     A3.L
            =>  hTE                     A4.L
        Out:
            <=  unsigned short          D1.W

    typedef pascal void (*DrawHookProcPtr)(unsigned short textOffset, unsigned short drawLen,
     void *textBufferPtr, TEPtr pTE, TEHandle hTE);

        In:
            =>  textOffset              D0.W
            =>  drawLen                 D1.W
            =>  textBufferPtr           A0.L
            =>  pTE                     A3.L
            =>  hTE                     A4.L
        Out:
            none

    typedef pascal Boolean (*HitTestHookProcPtr)(unsigned short styleRunLen,
     unsigned short styleRunOffset, unsigned short slop, void *textBufferPtr,
     TEPtr pTE, TEHandle hTE, unsigned short *pixelWidth, unsigned short *charOffset, 
     Boolean *pixelInChar);

        In:
            =>  styleRunLen             D0.W
            =>  styleRunOffset          D1.W
            =>  slop                    D2.W
            =>  textBufferPtr           A0.L
            =>  pTE                     A3.L
            =>  hTE                     A4.L
        Out:
            <=  pixelWidth              D0.W (low)
            <=  Boolean                 D0.W (high)
            <=  charOffset              D1.W
            <=  pixelInChar             D2.W

    typedef pascal void (*TEFindWordProcPtr)(unsigned short currentPos, short caller, 
     TEPtr pTE, TEHandle hTE, unsigned short *wordStart, unsigned short *wordEnd);

        In:
            =>  currentPos              D0.W
            =>  caller                  D2.W
            =>  pTE                     A3.L
            =>  hTE                     A4.L
        Out:
            <=  wordStart               D0.W
            <=  wordEnd                 D1.W

    typedef pascal void (*TERecalcProcPtr)(TEPtr pTE, unsigned short changeLength,
     unsigned short *lineStart, unsigned short *firstChar, unsigned short *lastChar);

        In:
            =>  pTE                     A3.L
            =>  changeLength            D7.W
        Out:
            <=  lineStart               D2.W
            <=  firstChar               D3.W
            <=  lastChar                D4.W

    typedef pascal void (*TEDoTextProcPtr)(TEPtr pTE, unsigned short firstChar, unsigned short lastChar,
                        short selector, GrafPtr *currentGrafPort, short *charPosition);

        In:
            =>  pTE                     A3.L
            =>  firstChar               D3.W
            =>  lastChar                D4.W
            =>  selector                D7.W
        Out:
            <=  currentGrafPort         A0.L
            <=  charPosition            D0.W
            
*/
typedef STACK_UPP_TYPE(HighHookProcPtr)                         HighHookUPP;
typedef STACK_UPP_TYPE(EOLHookProcPtr)                          EOLHookUPP;
typedef STACK_UPP_TYPE(CaretHookProcPtr)                        CaretHookUPP;
typedef STACK_UPP_TYPE(WidthHookProcPtr)                        WidthHookUPP;
typedef STACK_UPP_TYPE(TextWidthHookProcPtr)                    TextWidthHookUPP;
typedef STACK_UPP_TYPE(NWidthHookProcPtr)                       NWidthHookUPP;
typedef STACK_UPP_TYPE(DrawHookProcPtr)                         DrawHookUPP;
typedef STACK_UPP_TYPE(HitTestHookProcPtr)                      HitTestHookUPP;
typedef STACK_UPP_TYPE(TEFindWordProcPtr)                       TEFindWordUPP;
typedef STACK_UPP_TYPE(TERecalcProcPtr)                         TERecalcUPP;
typedef STACK_UPP_TYPE(TEDoTextProcPtr)                         TEDoTextUPP;
typedef STACK_UPP_TYPE(TEClickLoopProcPtr)                      TEClickLoopUPP;
typedef STACK_UPP_TYPE(WordBreakProcPtr)                        WordBreakUPP;
struct TERec {
  Rect                destRect;
  Rect                viewRect;
  Rect                selRect;
  short               lineHeight;
  short               fontAscent;
  Point               selPoint;
  short               selStart;
  short               selEnd;
  short               active;
  WordBreakUPP        wordBreak;              /* NOTE: This field is ignored on non-Roman systems and on Carbon (see IM-Text 2-60) */
  TEClickLoopUPP      clickLoop;
  long                clickTime;
  short               clickLoc;
  long                caretTime;
  short               caretState;
  short               just;
  short               teLength;
  Handle              hText;
  long                hDispatchRec;           /* added to replace recalBack & recalLines.  it's a handle anyway */
  short               clikStuff;
  short               crOnly;
  short               txFont;
  StyleField          txFace;                 /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               txMode;
  short               txSize;
  GrafPtr             inPort;
  HighHookUPP         highHook;
  CaretHookUPP        caretHook;
  short               nLines;
  short               lineStarts[16001];
};

enum {
                                        /* Justification (word alignment) styles */
  teJustLeft                    = 0,
  teJustCenter                  = 1,
  teJustRight                   = -1,
  teForceLeft                   = -2,   /* new names for the Justification (word alignment) styles */
  teFlushDefault                = 0,    /*flush according to the line direction */
  teCenter                      = 1,    /*center justify (word alignment) */
  teFlushRight                  = -1,   /*flush right for all scripts */
  teFlushLeft                   = -2    /*flush left for all scripts */
};

enum {
                                        /* Set/Replace style modes */
  fontBit                       = 0,    /*set font*/
  faceBit                       = 1,    /*set face*/
  sizeBit                       = 2,    /*set size*/
  clrBit                        = 3,    /*set color*/
  addSizeBit                    = 4,    /*add size mode*/
  toggleBit                     = 5     /*set faces in toggle mode*/
};

enum {
                                        /* TESetStyle/TEContinuousStyle modes */
  doFont                        = 1,    /* set font (family) number*/
  doFace                        = 2,    /*set character style*/
  doSize                        = 4,    /*set type size*/
  doColor                       = 8,    /*set color*/
  doAll                         = 15,   /*set all attributes*/
  addSize                       = 16,   /*adjust type size*/
  doToggle                      = 32    /*toggle mode for TESetStyle*/
};

enum {
                                        /* offsets into TEDispatchRec */
  EOLHook                       = 0,    /*[UniversalProcPtr] TEEOLHook*/
  DRAWHook                      = 4,    /*[UniversalProcPtr] TEWidthHook*/
  WIDTHHook                     = 8,    /*[UniversalProcPtr] TEDrawHook*/
  HITTESTHook                   = 12,   /*[UniversalProcPtr] TEHitTestHook*/
  nWIDTHHook                    = 24,   /*[UniversalProcPtr] nTEWidthHook*/
  TextWidthHook                 = 28    /*[UniversalProcPtr] TETextWidthHook*/
};

enum {
                                        /* selectors for TECustomHook */
  intEOLHook                    = 0,    /*TEIntHook value*/
  intDrawHook                   = 1,    /*TEIntHook value*/
  intWidthHook                  = 2,    /*TEIntHook value*/
  intHitTestHook                = 3,    /*TEIntHook value*/
  intNWidthHook                 = 6,    /*TEIntHook value for new version of WidthHook*/
  intTextWidthHook              = 7,    /*TEIntHook value for new TextWidthHook*/
  intInlineInputTSMTEPreUpdateHook = 8, /*TEIntHook value for TSMTEPreUpdateProcPtr callback*/
  intInlineInputTSMTEPostUpdateHook = 9 /*TEIntHook value for TSMTEPostUpdateProcPtr callback*/
};

enum {
                                        /* feature or bit definitions for TEFeatureFlag */
  teFAutoScroll                 = 0,    /*00000001b*/
  teFTextBuffering              = 1,    /*00000010b*/
  teFOutlineHilite              = 2,    /*00000100b*/
  teFInlineInput                = 3,    /*00001000b */
  teFUseWhiteBackground         = 4,    /*00010000b */
  teFUseInlineInput             = 5,    /*00100000b */
  teFInlineInputAutoScroll      = 6     /*01000000b */
};

enum {
                                        /* feature or bit definitions for TEFeatureFlag -- Carbon only                */
                                        /* To avoid having to call TEIdle in Carbon apps, automatic idling can be activated   */
                                        /* via the following feature flag, but you must ensure that the destRect and/or     */
                                        /* GrafPort's origin be setup properly for drawing in a given TERec when       */
                                        /* the timer fires.    When this feature flag is set, TEIdle is a noop.          */
                                        /* Activate this feature flag before calling TEActivate.                 */
  teFIdleWithEventLoopTimer     = 7     /*10000000b */
};

enum {
                                        /* action for the new "bit (un)set" interface, TEFeatureFlag */
  teBitClear                    = 0,
  teBitSet                      = 1,    /*set the selector bit*/
  teBitTest                     = -1    /*no change; just return the current setting*/
};

enum {
                                        /*constants for identifying the routine that called FindWord */
  teWordSelect                  = 4,    /*clickExpand to select word*/
  teWordDrag                    = 8,    /*clickExpand to drag new word*/
  teFromFind                    = 12,   /*FindLine called it ($0C)*/
  teFromRecal                   = 16    /*RecalLines called it ($10)      obsolete */
};

enum {
                                        /*constants for identifying TEDoText selectors */
  teFind                        = 0,    /*TEDoText called for searching*/
  teHighlight                   = 1,    /*TEDoText called for highlighting*/
  teDraw                        = -1,   /*TEDoText called for drawing text*/
  teCaret                       = -2    /*TEDoText called for drawing the caret*/
};


typedef char                            Chars[32001];
typedef char *                          CharsPtr;
typedef CharsPtr *                      CharsHandle;
struct StyleRun {
  short               startChar;              /*starting character position*/
  short               styleIndex;             /*index in style table*/
};
typedef struct StyleRun                 StyleRun;
struct STElement {
  short               stCount;                /*number of runs in this style*/
  short               stHeight;               /*line height*/
  short               stAscent;               /*font ascent*/
  short               stFont;                 /*font (family) number*/
  StyleField          stFace;                 /*StyleField occupies 16-bits, but only first 8-bits are used */
  short               stSize;                 /*size in points*/
  RGBColor            stColor;                /*absolute (RGB) color*/
};
typedef struct STElement                STElement;
typedef STElement                       TEStyleTable[1777];
typedef STElement *                     STPtr;
typedef STPtr *                         STHandle;
struct LHElement {
  short               lhHeight;               /*maximum height in line*/
  short               lhAscent;               /*maximum ascent in line*/
};
typedef struct LHElement                LHElement;
typedef LHElement                       LHTable[8001];
typedef LHElement *                     LHPtr;
typedef LHPtr *                         LHHandle;
struct ScrpSTElement {
  long                scrpStartChar;          /*starting character position*/
  short               scrpHeight;
  short               scrpAscent;
  short               scrpFont;
  StyleField          scrpFace;               /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               scrpSize;
  RGBColor            scrpColor;
};
typedef struct ScrpSTElement            ScrpSTElement;
/* ARRAY [0..1600] OF ScrpSTElement */
typedef ScrpSTElement                   ScrpSTTable[1601];
struct StScrpRec {
  short               scrpNStyles;            /*number of styles in scrap*/
  ScrpSTTable         scrpStyleTab;           /*table of styles for scrap*/
};
typedef struct StScrpRec                StScrpRec;
typedef StScrpRec *                     StScrpPtr;
typedef StScrpPtr *                     StScrpHandle;
struct NullStRec {
  long                teReserved;             /*reserved for future expansion*/
  StScrpHandle        nullScrap;              /*handle to scrap style table*/
};
typedef struct NullStRec                NullStRec;
typedef NullStRec *                     NullStPtr;
typedef NullStPtr *                     NullStHandle;
struct TEStyleRec {
  short               nRuns;                  /*number of style runs*/
  short               nStyles;                /*size of style table*/
  STHandle            styleTab;               /*handle to style table*/
  LHHandle            lhTab;                  /*handle to line-height table*/
  long                teRefCon;               /*reserved for application use*/
  NullStHandle        nullStyle;              /*Handle to style set at null selection*/
  StyleRun            runs[8001];             /*ARRAY [0..8000] OF StyleRun*/
};
typedef struct TEStyleRec               TEStyleRec;
typedef TEStyleRec *                    TEStylePtr;
typedef TEStylePtr *                    TEStyleHandle;
struct TextStyle {
  short               tsFont;                 /*font (family) number*/
  StyleField          tsFace;                 /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               tsSize;                 /*size in point*/
  RGBColor            tsColor;                /*absolute (RGB) color*/
};
typedef struct TextStyle                TextStyle;
typedef TextStyle *                     TextStylePtr;
typedef TextStylePtr *                  TextStyleHandle;
typedef short                           TEIntHook;
/*
 *  NewHighHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HighHookUPP
NewHighHookUPP(HighHookProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewEOLHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern EOLHookUPP
NewEOLHookUPP(EOLHookProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewCaretHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CaretHookUPP
NewCaretHookUPP(CaretHookProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern WidthHookUPP
NewWidthHookUPP(WidthHookProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTextWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TextWidthHookUPP
NewTextWidthHookUPP(TextWidthHookProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewNWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NWidthHookUPP
NewNWidthHookUPP(NWidthHookProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDrawHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DrawHookUPP
NewDrawHookUPP(DrawHookProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewHitTestHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern HitTestHookUPP
NewHitTestHookUPP(HitTestHookProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTEFindWordUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TEFindWordUPP
NewTEFindWordUPP(TEFindWordProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTERecalcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TERecalcUPP
NewTERecalcUPP(TERecalcProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTEDoTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TEDoTextUPP
NewTEDoTextUPP(TEDoTextProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTEClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TEClickLoopUPP
NewTEClickLoopUPP(TEClickLoopProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewWordBreakUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeHighHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHighHookUPP(HighHookUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeEOLHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeEOLHookUPP(EOLHookUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCaretHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCaretHookUPP(CaretHookUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeWidthHookUPP(WidthHookUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTextWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTextWidthHookUPP(TextWidthHookUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNWidthHookUPP(NWidthHookUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDrawHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDrawHookUPP(DrawHookUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeHitTestHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeHitTestHookUPP(HitTestHookUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTEFindWordUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTEFindWordUPP(TEFindWordUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTERecalcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTERecalcUPP(TERecalcUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTEDoTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTEDoTextUPP(TEDoTextUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTEClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTEClickLoopUPP(TEClickLoopUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeWordBreakUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeHighHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeHighHookUPP(
  const Rect *  r,
  TEPtr         pTE,
  HighHookUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeEOLHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeEOLHookUPP(
  char        theChar,
  TEPtr       pTE,
  TEHandle    hTE,
  EOLHookUPP  userUPP)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCaretHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeCaretHookUPP(
  const Rect *  r,
  TEPtr         pTE,
  CaretHookUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern unsigned short
InvokeWidthHookUPP(
  unsigned short  textLen,
  unsigned short  textOffset,
  void *          textBufferPtr,
  TEPtr           pTE,
  TEHandle        hTE,
  WidthHookUPP    userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTextWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern unsigned short
InvokeTextWidthHookUPP(
  unsigned short    textLen,
  unsigned short    textOffset,
  void *            textBufferPtr,
  TEPtr             pTE,
  TEHandle          hTE,
  TextWidthHookUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNWidthHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern unsigned short
InvokeNWidthHookUPP(
  unsigned short  styleRunLen,
  unsigned short  styleRunOffset,
  short           slop,
  short           direction,
  void *          textBufferPtr,
  short *         lineStart,
  TEPtr           pTE,
  TEHandle        hTE,
  NWidthHookUPP   userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDrawHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDrawHookUPP(
  unsigned short  textOffset,
  unsigned short  drawLen,
  void *          textBufferPtr,
  TEPtr           pTE,
  TEHandle        hTE,
  DrawHookUPP     userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeHitTestHookUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeHitTestHookUPP(
  unsigned short    styleRunLen,
  unsigned short    styleRunOffset,
  unsigned short    slop,
  void *            textBufferPtr,
  TEPtr             pTE,
  TEHandle          hTE,
  unsigned short *  pixelWidth,
  unsigned short *  charOffset,
  Boolean *         pixelInChar,
  HitTestHookUPP    userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTEFindWordUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeTEFindWordUPP(
  unsigned short    currentPos,
  short             caller,
  TEPtr             pTE,
  TEHandle          hTE,
  unsigned short *  wordStart,
  unsigned short *  wordEnd,
  TEFindWordUPP     userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTERecalcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeTERecalcUPP(
  TEPtr             pTE,
  unsigned short    changeLength,
  unsigned short *  lineStart,
  unsigned short *  firstChar,
  unsigned short *  lastChar,
  TERecalcUPP       userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTEDoTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeTEDoTextUPP(
  TEPtr           pTE,
  unsigned short  firstChar,
  unsigned short  lastChar,
  short           selector,
  GrafPtr *       currentGrafPort,
  short *         charPosition,
  TEDoTextUPP     userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTEClickLoopUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeTEClickLoopUPP(
  TEPtr           pTE,
  TEClickLoopUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeWordBreakUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

enum {
                                        /* feature bit 4 for TEFeatureFlag no longer in use */
  teFUseTextServices            = 4     /*00010000b */
};


#if OLDROUTINENAMES
/* action for the old C "bit (un)set" interface, TEFeatureFlag */
#define TEBitClear  teBitClear
#define TEBitSet    teBitSet
#define TEBitTest   teBitTest
#define teFAutoScr  teFAutoScroll
#define toglBit     toggleBit
#endif  /* OLDROUTINENAMES */

/*
 *  TEScrapHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
TEScrapHandle(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TEGetScrapLength()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
TEGetScrapLength(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#define TEGetScrapLength() ((long) * (unsigned short *) 0x0AB0)
#endif
/*
 *  TEInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  TENew()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern TEHandle 
TENew(
  const Rect *  destRect,
  const Rect *  viewRect)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEDispose()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEDispose(TEHandle hTE)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetText(
  const void *  text,
  long          length,
  TEHandle      hTE)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern CharsHandle 
TEGetText(TEHandle hTE)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEIdle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEIdle(TEHandle hTE)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetSelect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetSelect(
  long       selStart,
  long       selEnd,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEActivate()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEActivate(TEHandle hTE)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEDeactivate()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEDeactivate(TEHandle hTE)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEKey()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEKey(
  CharParameter   key,
  TEHandle        hTE)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECut()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TECut(TEHandle hTE)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECopy()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TECopy(TEHandle hTE)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEPaste()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEPaste(TEHandle hTE)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEDelete()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEDelete(TEHandle hTE)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEInsert()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEInsert(
  const void *  text,
  long          length,
  TEHandle      hTE)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetAlignment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetAlignment(
  short      just,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEUpdate()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEUpdate(
  const Rect *  rUpdate,
  TEHandle      hTE)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TETextBox()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TETextBox(
  const void *  text,
  long          length,
  const Rect *  box,
  short         just)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEScroll()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEScroll(
  short      dh,
  short      dv,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESelView()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESelView(TEHandle hTE)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEPinScroll()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEPinScroll(
  short      dh,
  short      dv,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEAutoView()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEAutoView(
  Boolean    fAuto,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECalText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TECalText(TEHandle hTE)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetOffset()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
TEGetOffset(
  Point      pt,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetPoint()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Point 
TEGetPoint(
  short      offset,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEClick()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEClick(
  Point      pt,
  Boolean    fExtend,
  TEHandle   h)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEStyleNew()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern TEHandle 
TEStyleNew(
  const Rect *  destRect,
  const Rect *  viewRect)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetStyleHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetStyleHandle(
  TEStyleHandle   theHandle,
  TEHandle        hTE)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetStyleHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern TEStyleHandle 
TEGetStyleHandle(TEHandle hTE)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEGetStyle(
  short        offset,
  TextStyle *  theStyle,
  short *      lineHeight,
  short *      fontAscent,
  TEHandle     hTE)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEStylePaste()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEStylePaste(TEHandle hTE)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetStyle(
  short              mode,
  const TextStyle *  newStyle,
  Boolean            fRedraw,
  TEHandle           hTE)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEReplaceStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEReplaceStyle(
  short              mode,
  const TextStyle *  oldStyle,
  const TextStyle *  newStyle,
  Boolean            fRedraw,
  TEHandle           hTE)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetStyleScrapHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StScrpHandle 
TEGetStyleScrapHandle(TEHandle hTE)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEStyleInsert()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEStyleInsert(
  const void *   text,
  long           length,
  StScrpHandle   hST,
  TEHandle       hTE)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
TEGetHeight(
  long       endLine,
  long       startLine,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEContinuousStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
TEContinuousStyle(
  short *      mode,
  TextStyle *  aStyle,
  TEHandle     hTE)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEUseStyleScrap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TEUseStyleScrap(
  long           rangeStart,
  long           rangeEnd,
  StScrpHandle   newStyles,
  Boolean        fRedraw,
  TEHandle       hTE)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECustomHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TECustomHook(
  TEIntHook           which,
  UniversalProcPtr *  addr,
  TEHandle            hTE)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TENumStyles()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
TENumStyles(
  long       rangeStart,
  long       rangeEnd,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEFeatureFlag()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
TEFeatureFlag(
  short      feature,
  short      action,
  TEHandle   hTE)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetHiliteRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DragLib 1.1 and later
 */
extern OSErr 
TEGetHiliteRgn(
  RgnHandle   region,
  TEHandle    hTE)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetInlineInputContextPtr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  TEConfirmInlineInput()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  TESetScrapLength()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetScrapLength(long length)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEFromScrap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
TEFromScrap(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEToScrap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
TEToScrap(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetClickLoop()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TESetClickLoop(
  TEClickLoopUPP   clikProc,
  TEHandle         hTE)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetWordBreak()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */









/*
 *  TEGetDoTextHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern TEDoTextUPP 
TEGetDoTextHook(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetDoTextHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TESetDoTextHook(TEDoTextUPP value)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetRecalcHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern TERecalcUPP 
TEGetRecalcHook(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetRecalcHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TESetRecalcHook(TERecalcUPP value)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetFindWordHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern TEFindWordUPP 
TEGetFindWordHook(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetFindWordHook()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TESetFindWordHook(TEFindWordUPP value)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TEGetScrapHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Handle 
TEGetScrapHandle(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TESetScrapHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TESetScrapHandle(Handle value)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* LMGetWordRedraw and LMSetWordRedraw were previously in LowMem.h  */
/* Deprecated for Carbon on MacOS X                                 */
/* This lomem is no longer used by the implementation of TextEdit   */
/* on MacOS X, so setting it will have no effect.                   */
/*
 *  LMGetWordRedraw()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetWordRedraw(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetWordRedraw()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWordRedraw(UInt8 value)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  teclick()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#if OLDROUTINENAMES
#if CALL_NOT_IN_CARBON
#define TESetJust(just, hTE) TESetAlignment(just, hTE)
#define TextBox(text, length, box, just) TETextBox(text, length, box, just)
#define TEStylNew(destRect, viewRect) TEStyleNew(destRect, viewRect)
#define SetStylHandle(theHandle, hTE) TESetStyleHandle(theHandle, hTE)
#define SetStyleHandle(theHandle, hTE) TESetStyleHandle (theHandle, hTE)
#define GetStylHandle(hTE) TEGetStyleHandle(hTE)
#define GetStyleHandle(hTE) TEGetStyleHandle(hTE)
#define TEStylPaste(hTE) TEStylePaste(hTE)
#define GetStylScrap(hTE) TEGetStyleScrapHandle(hTE)
#define GetStyleScrap(hTE) TEGetStyleScrapHandle(hTE)
#define SetStylScrap(rangeStart, rangeEnd, newStyles, redraw, hTE) TEUseStyleScrap(rangeStart, rangeEnd, newStyles, redraw, hTE)
#define SetStyleScrap(rangeStart, rangeEnd, newStyles, redraw, hTE)  TEUseStyleScrap(rangeStart, rangeEnd, newStyles, redraw, hTE)
#define TEStylInsert(text, length, hST, hTE) TEStyleInsert(text, length, hST, hTE)
#define TESetScrapLen(length) TESetScrapLength(length)
#define TEGetScrapLen() TEGetScrapLength()
#define SetClikLoop(clikProc, hTE) TESetClickLoop(clikProc, hTE)
#define SetWordBreak(wBrkProc, hTE) TESetWordBreak(wBrkProc, hTE)
#endif  /* CALL_NOT_IN_CARBON */
#endif  /* OLDROUTINENAMES */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TEXTEDIT__ */

