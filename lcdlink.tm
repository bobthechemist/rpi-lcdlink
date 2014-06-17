/* To launch this program from within Mathematica use:
 *   In[1]: link = Install@"lcdlink"
 * 
 * To view functionality provided by the package use:
 *   In[1]: ?lcdlink`*
 *
 * To view usage documenation use:
 *   In[1]: ?<func>
 * where <func> is one of the functions shown using ?lcdlink`*
*/


:Evaluate: BeginPackage["lcdlink`"]

:Evaluate: lcdPuts::usage = "lcdPuts[buf] prints buf to the LCD at the current cursor location. lcdPuts[col, row, buf] puts the string at the position {col, row}."
:Evaluate: lcdClear::usage = "lcdClear[] clears the LCD screen"
:Evaluate: lcdColor::usage = "lcdColor[color] changes the backlight of the LCD. Color is an integer from 0 to 7."
:Evaluate: lcdPosition::usage = "lcdPosition[col, row] sets the cursor position on the LCD.  col can be from 1 to 16 and row must be 0 or 1."
:Evaluate: lcdScroll::usage = "lcdScroll[row,buf] scrolls buf across row on the LCD. Press SELECT on the LCD plate to cancel the scroll."
:Evaluate: lcdPutc::usage = "lcdPutc[col, row, charnum] puts the ASCII code character charnum at the position {col, row}."
:Evaluate: lcdCharDef::usage = "lcdCharDef[charnum, charb] defines the custom character charnum as charb.  charnum must be 0 .. 7 and charb is a list of Integers of length 8."




:Evaluate: Begin["`Private`"]

:Begin:
:Function:      mllcdputs
:Pattern:       lcdPuts[buf_String]
:Arguments:     {buf}
:ArgumentTypes: {String}
:ReturnType:    Integer 
:End:

:Begin:
:Function:      mllcdclear
:Pattern:       lcdClear[]
:Arguments:     {}
:ArgumentTypes: {}
:ReturnType:    Integer 
:End:

:Begin:
:Function:      mllcdcolor
:Pattern:       lcdColor[color_Integer]
:Arguments:     {color}
:ArgumentTypes: {Integer}
:ReturnType:    Integer 
:End:

:Begin:
:Function:      mllcdposition
:Pattern:       lcdPosition[col_Integer,row_Integer]
:Arguments:     {col,row}
:ArgumentTypes: {Integer,Integer}
:ReturnType:    Integer 
:End:

:Begin:
:Function:      mllcdscroll
:Pattern:       lcdScroll[row_Integer,buf_String]
:Arguments:     {row,buf}
:ArgumentTypes: {Integer,String}
:ReturnType:    Integer 
:End:

:Begin:
:Function:	mllcdputc
:Pattern:	lcdPutc[col_Integer, row_Integer, charnum_Integer]
:Arguments:	{col, row, charnum}
:ArgumentTypes:	{Integer, Integer, Integer}
:ReturnType:	Integer
:End:

:Begin:
:Function:	mllcdchardef
:Pattern:	lcdCharDef[charnum_Integer, charb_List]
:Arguments:	{charnum, charb}
:ArgumentTypes:	{Integer, IntegerList}
:ReturnType:	Integer
:End:

/*
 * Add to lcdPuts to include position information if desired
*/
:Evaluate: lcdPuts[col_Integer, row_Integer, buf_String]:= Module[{},lcdPosition[col,row];lcdPuts[buf];]


:Evaluate: End[]

:Evaluate: EndPackage[]
