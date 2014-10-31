/*---------------------------------------------------------*/
/* UIBUILD                                                 */
/*                                                         */
/* A Mom and Pop exec to generate and cleanup the examples */
/* for Power GUI Programming by Law, Leong, Love, Olson,   */
/* and Tsuji. This exec must exist in the root samples     */
/* directory.                                              */
/*                                                         */
/* Invocation:                                             */
/*  guibuild <logFileName> ( <Options>                     */
/*                                                         */
/*   logFileName - The redirection file for commands       */
/*   Options                                               */
/*       none     - All program make files are run.        */
/*       CLEAN    - All .OBJ .RES .HLP .I files deleted.   */
/*       CLEANALL - .EXE and CLEAN files deleted.          */
/*       RUNALL   - All executable programs are run.       */
/*                                                         */
/* Examples:                                               */
/* 1) To build all programs and have output put into the   */
/*    default log file, GUIBUILD.LOG, in the directory you */
/*    start the exec:                                      */
/*                                                         */
/*       guibuild                                          */
/*                                                         */
/* 2) To erase all OBJs, RESs, HLPs, and INFs, but keep    */
/*    the EXEs.                                            */
/*                                                         */
/*       guibuild (clean                                   */
/*                                                         */
/*                                                         */
/*---------------------------------------------------------*/
call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs


/* Save the program name.*/
parse upper source . . uibuildName  .

/* Save the options */
parse upper arg outFile '(' optionsUpper

/* Setup to restore the environment */
n = setlocal()

/* Save the root directory */
currentLocation = directory()
startLocation = currentLocation

/* Determine the options specified  */
/* Note: clean leaves the EXE/DLL, cleanAll removes the EXE/DLL as well */
/*       If clean specified we don't do the make */
clean       = pos("CLEAN", optionsUpper)
cleanAll    = pos("CLEANALL", optionsUpper)
cleanToShip = pos("CLEANTOSHIP", optionsUpper)
runAll      = pos("RUNALL", optionsUpper)
run         = pos("RUN", optionsUpper)

/* Establish the chapter names */
chapters. = 0
chapters.1  = "Getting Started"
chapters.2  = "Object-Oriented User Interface Fundamentals"
chapters.3  = "Tour of the User Interface Library"
chapters.4  = "Windows, Handlers, and Events"
chapters.5  = "Frame Window Basics"
chapters.6  = "Menus and Keyboard Accelerators"
chapters.7  = "Controls"
chapters.8  = "Static Controls"
chapters.9  = "Edit Controls"
chapters.10 = "Button Controls"
chapters.11 = "List Controls"
chapters.12 = "Slider"
chapters.13 = "Container"
chapters.14 = "Notebook"
chapters.15 = "Canvases"
chapters.16 = "Reusable Handlers"
chapters.17 = "Advanced Frame Window Topics"
chapters.18 = "Custom Controls and Handlers"
chapters.19 = "Applications and Threads"
chapters.20 = "Direct Manipulation"
chapters.21 = "Dynamic Data Exchange"
chapters.22 = "Using Help"
chapters.23 = "Using OS/2 Resources"
chapters.24 = "Storing Data in a Profile"
chapters.25 = "Data Types"
chapters.26 = "Error Handling and Reporting"
chapters.27 = "Problem Determination"
chapters.28 = "Packaging and Performance Tuning"

makeErrorList. = ''
makeErrorList.0 = 0


/* Make sure we have a path to the log file since */
/* we execute commands in multiple directories.   */
/* If you don't specify the directory, it goes to */
/* the current directory.                         */
if outFile = "" then
  outFile = currentLocation||"\guibuild.log"
else do
  if pos('\', outFile) = 0 then
     outFile = currentLocation||"\"||outFile
end

/* Determine the root samples directory and proceed   */
/* there to start the work,                           */
lastBackSlash = lastpos('\', uibuildName)
uibuildPath = substr(uibuildName, 1, lastBackSlash-1)
currentLocation = directory(uiBuildPath)

/* Name the file containing the list of samples.  */
/* This file is installed in the samples root and */
/* we assume it stays there.                      */
sampleListFile = uibuildPath||'\powergui.lst'
sampleList. = ''

'@echo Output written to file ' translate(outFile) '> CON'
'@echo -------------------------------------------------------------> CON'
/* Reset the output log */
'@echo Started on' date() 'at' time() '> ' outFile



purgeList = ''
purgeDesc = ''
purge = 0
if clean > 0 then do
  purgeList = '*.RES *.OBJ *.I'
  purgeDesc = 'Purging generated files (except EXE/DLL)'
  purge = 1
end

if cleanAll > 0 then do
  purgeList = purgeList '*.EXE *.DLL'
  purgeDesc = 'Purging generated files (including EXE/DLL)'
end

if cleanToShip > 0 then do
  purgeList = purgeList '*ERR *.LAS *.RAM *.BAK *.ZIP *.TRC'
  purgeDesc = 'Purging files '
end




lastChapter=0
chapter=0
if stream(sampleListFile,'C','QUERY EXIST')<>'' then
 do
   /* If only run (and not runAll is specified, we change the */
   /* tag so that we only find the files with the tag--the    */
   /* tag can be just the directory and then we will run      */
   /* all programs in the directory                           */
   if runAll = 0 & run > 0 then do
      fileTag = " garbage xx"
      tagFound = pos("RUN=", optionsUpper)
      if tagFound > 0 then do
         optionsRemaining = substr(optionsUpper, tagFound+4,)
         fileTag = word(optionsRemaining, 1)
      end
   end  /* Do */
   else
      fileTag = ' x '

   /* Get a list of all files with the tag (either all programs */
   /* or programs matching a tag).                              */
   call SysFileSearch fileTag, sampleListFile, sampleList
   if sampleList.0 >  0 then
      do sample=1 TO sampleList.0
        lastChapter = chapter
        parse var sampleList.sample with ' x ' sampleNumber chapter location description
        sampleNumber = strip(sampleNumber)
        chapter = strip(chapter)
        location = strip(location)
        description = strip(description)


        /* Change to the directory */
        newLocation = directory(location)

        /* Clean files if requested */
        if purge > 0 then do
          '@echo' purgeDesc 'in directory:' location '> CON'

          /* Remove tempinc files and directory */
          curMask = newLocation||'\tempinc\*.*'
          rc = SysFileTree(curMask, 'file', 'FO', '***-*')
          if file.0 > 0 then do
            do maskj=1 to file.0
               rc = SysFileDelete(file.maskj)
               if rc <> 0 then
                 '@ECHO Could not delete file' file.maskj '>>' outFile
            end
            rc = SysRmDir(newLocation||'\tempinc')
            if rc <> 0 then
              '@ECHO Could not remove directory' newLocation||'tempinc' '>>' outFile

          end

          fileMasks = purgeList
          do maski=1 to words(fileMasks)
            curMask = word(fileMasks,maski)
            rc = SysFileTree(curMask, 'file', 'FO', '***-*')
            do maskj=1 to file.0
               rc = SysFileDelete(file.maskj)
               if rc <> 0 then
                 '@ECHO Could not delete file' file.maskj '>>' outFile
            end
          end
          /* Need to clean up tempinc still */
        end
        else if run > 0 then do
           /* Build the program string and run the program */
           exeLocation = lastpos('\', location) + 1
           exeName = substr(location, exeLocation)
           exeName
        end
        else do
          if chapter <> lastChapter then
             '@ECHO Building Samples in Chapter' chapter '-' chapters.chapter '> CON'
          '@ECHO ' format(sampleNumber,3)||') "'||description||'" > CON'
          '@ECHO --------------------------------------------------------- >>' outFile
          '@ECHO Running NMAKE in' translate(newLocation) '>>' outFile
          '@nmake >> ' outFile ' 2>>&1'
           if rc <> 0 then do
             makeErrorList.0 = makeErrorList.0 + 1
             makeErrorCount = makeErrorList.0
             makeErrorList.makeErrorCount = description '(' newLocation ')'
             '@ECHO           >>>>>>>>>>>>>>>>>>>>>>> Build failed  > CON'
           end
        end
        newLocation = directory(uibuildPath)
      end
 end
else
   say "Could not find the sample list file -" sampleListFile


/* Reset the output log */
'@echo -------------------------------------------------------------> CON'
'@echo Output written to file ' translate(outFile) '> CON'
if makeErrorList.0 > 0 then do
  '@echo The following examples failed to build correctly:'  '> CON'
   do error=1 to makeErrorList.0
    '@echo   ' makeErrorList.error  '> CON'
   end
end

'@echo Completed on' date() 'at' time() '>>' outFile

n = endlocal()

exit 0
