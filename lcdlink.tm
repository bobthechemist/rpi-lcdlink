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