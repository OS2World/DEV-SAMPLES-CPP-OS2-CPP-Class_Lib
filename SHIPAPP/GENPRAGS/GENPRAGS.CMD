/*-----------------------------------------------------------*/
/* GENPRAGS - The primary purpose of this exec is to         */
/*    generate the alloc_text pragmas for static functions.  */
/*                                                           */
/*    The exec functions by generating and parsing the       */
/*    assembler code (-Fa) for the entire product.  Static   */
/*    functions are identified because they have a PROC      */
/*    statement with no cooresponding PUBLIC statement.      */
/*    The static functions identified in this manner are     */
/*    searched for various tokens to determine the segment   */
/*    they should be placed in and the appropriate           */
/*    alloc_text pragmas generated.                          */
/*                                                           */
/* Author: Bob Love                                          */
/*                                                           */
/* Requires as inout:                                        */
/*  wildCardFileName   - files to process of the form '*.cpp'*/
/*                                                           */
/* Generates as output:                                      */
/*  initlist.h    - the pragma definitions                   */
/*                                                           */
/*-----------------------------------------------------------*/

call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs

PARSE UPPER ARG wildCardFileName  '(' optionsUpper

'@ECHO OFF'

if wildCardFileName = "" then
  wildCardFileName = "*.CPP"

AssemFile          = 'icltemp.asm'
ObjFile            = 'icltemp.obj'

InitSegment      = "ICLTop"
TermSegment      = "ICLBottom"
ExceptionSegment = "ICLBottom"
StaticSegment    = "ICLStatics"


/* collect the objects in a tree */
rc=SysFileTree(wildCardFileName,cppFiles,'FO','*****')

do fileNumber=1 TO cppFiles.0
  publicList.0 = 0
  procList.0 = 0
  /* Erase the assembler file and create the next */
  if stream(AssemFile,'C','QUERY EXIST')<>'' then
     '@DEL 'AssemFile' >NUL 2>NUL'
  iccOptions = '-c -tdp -O+ -Fd -W2 -Q+'
  'ICC' iccOptions '-Fa'AssemFile '-Fo'ObjFile  cppFiles.fileNumber '> NUL 2>NUL'

  /* Build the list of Public Symbols in the Assembler file */
  call SysFileSearch 'PUBLIC', AssemFile, filePublics, 'C'
  
  /* reduce the contents of the list to the name only */
  do j=1 to filePublics.0
     /* remove tabs */
     filePublics.j = translate(filePublics.j, ' ', '09'x)  
     parse var  filePublics.j publicKeyword function
     if strip(publicKeyword) = "PUBLIC"  then do
        publicList.0 = publicList.0 + 1
        currentPublic = publicList.0
        publicList.currentPublic = strip(function)
     end  
  end 

  /* Build the list of PROCS (public & static)  */
  call SysFileSearch 'PROC', AssemFile, fileProcs, 'C'

  /* reduce the contents of the list to the name only */
  do j=1 to fileProcs.0
     fileProcs.j = translate(fileProcs.j, ' ', '09'x)
     if pos('EXTRN',fileProcs.j) = 0 then do
        parse value fileProcs.j with function 'PROC'
        procList.0 = procList.0 + 1
        currentProc = procList.0
        procList.currentProc = strip(function)
     end  
  end 

  /* Flag the static functions (PROC but not PUBLIC */
  staticsFound = false
  do j=1 to procList.0
     found = false
     do k=1 to publicList.0 while found = false
        if procList.j = publicList.k then do
           found = true
           procList.j.scope = "PUBLIC"
        end
     end 
     /* Not found in public list so must be a static */
     if found = false then do
       procList.j.scope = "STATIC"
       staticsFound = true
       rc = lineOut(STATICFile, '  ' procList.j)
     end 
  end 

  if staticsFound = true then do
    /* Determine the File Name and write an #ifdef for it */
    cppOffset = pos('.', cppFiles.fileNumber)
    lastSlash = lastPos('\', cppFIles.fileNumber)
    cppNameLength = cppOffset - lastSlash -1
    cppFileName = substr(cppFiles.fileNumber, lastSlash+1, cppNameLength)
    say "#ifdef _"||cppFileName||"_CPP_"
  
    /* Now dump out the segment definitions for Statics  */
    do procNumber=1 to procList.0
      if procList.procNumber.scope = "STATIC" then do
         outBuffer = "#pragma alloc_text("
         /* Write out Exception Functions */
         if pos("__dftdt", procList.procNumber) > 0   | ,
            pos("__dftbdt", procList.procNumber) > 0  | ,
            pos("__dftct", procList.procNumber) > 0 then
           outBuffer = outbuffer||ExceptionSegment
         /* Write out Initialization functions */
         else if pos("__sinit", procList.procNumber) > 0  then
           outBuffer = outbuffer||InitSegment
         /* Write out termination functions */
         else if pos("__sterm", procList.procNumber) > 0 then
           outBuffer = outbuffer||TermSegment
         else
           outBuffer = outBuffer||StaticSegment
  
         outBuffer = outBuffer||"," procList.procNumber||")"
         say outBuffer
      end 
    end /* do procNumber */
  
    say "#endif"
    say ""
  end /* do staticsExist */
end /* do fileNumber */

/* cleanup temporary files */
if stream(AssemFile,'C','QUERY EXIST')<>'' then
   '@DEL 'AssemFile' >NUL 2>NUL'
if stream(ObjFile,'C','QUERY EXIST')<>'' then
   '@DEL 'ObjFile' >NUL 2>NUL'

exit 0

