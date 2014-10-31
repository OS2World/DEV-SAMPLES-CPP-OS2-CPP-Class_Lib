Thanks for purchasing our book.  If you are one of the unlucky individuals
who waited a long time for the book to appear, we'd sincerely like to
apologize.  We have no good excuses other than the usual limitations of
a 24 hour day.

We hope you find the examples on this disk useful.  When you find the
time, please send us a note and tell us what you think.  We'd love
to hear bug reports, suggestions for more examples, changes to the
existing examples, and whether you have found these examples helpful.
Send your comments to one of the addresses below:
  bill_law@taligent.com
  kevinleong@vnet.ibm.com
  boblove@vnet.ibm.com
  olson@vnet.ibm.com
  htsuji@vnet.ibm.com

INSTALLATION
------------
There is nothing fancy about the installation or use of these
examples.  The code and the executable files are on the disk in a
self extracting zip file.  When you unzip this file according to the
instructions below, you'll find a series of directories whose names
correspond to the chapters in the book.  The examples themselves will
in their own directory below the chapter directories (with one exception).
At the bottom of this file, we have provided a table that describes the
examples, their chapter in the book, and their location after installation.

To install the examples:
  1) Create a directory on a drive with at least 4.7 Meg of available
     space (if you only plan to run the examples and not rebuild them,
     you will only need 2.7 Meg of disk space).  This directory will be
     the root examples directory.  For example:
        d:
        md d:\powergui

  2) Make this new directory the current directory. For example:
        d:
        cd \powergui

  3) Unzip the examples using the following command.
     Note: This assumes you have the example disk in your a: drive.
       a:\powergui /d

Note: The two "Getting Started" examples are not included on the example
disk, because they are dependent on the directory path to the examples.

BUILDING AND USING THE EXAMPLES
-------------------------------
After installation, you'll find the code, resources, and an executable
file for each example, in its directory listed below.  These executable
files have the same file name as the directory it resides in.  You can
run the shipped versions of these executable files, as long as you have
installed C Set ++ Version 2.1. In particular, these examples require
that the files dde4mui.dll, dde4cc.dll, and dde4mbs.dll, be in a
directory found in your LIBPATH.  These DLLs are shipped with C Set ++
Version 2.1.   For best results, install the latest Corrective Service
Disk (CSD) for the C Set ++ Class Libraries.

Each example contains a file, named "makefile," that you can use to rebuild
the program.  You can build any example by making the directory containing
the example, the current directory, and then executing the command "nmake."
You can add the option "/a" to force the examples to be rebuild regardless
of the dependency rules in makefile. For example, to rebuild force the
rebuild of the first "Getting Started" example, issue the following
commands.
   d:
   cd \powergui\getstart\start1
   nmake /a

The makefiles do not build the programs with debugging information.  If
you need this information, the easiest way is by using is to add "-Ti" to the
C Set ++ compiler options environment variable, and then run nmake. The
following commands will rebuild an example with debugging information, if
you run them from one of the example directories.
   set icc=-Ti
   nmake /a

If you plan to build all of the examples with debug information, you
will need a total of 27 Meg of disk space.

In the root example directory (e.g. d:\powergui above). we have included
a simple REXX exec we used to build and test the examples.  You
can use this exec to build all of the examples, to erase the
files generated during a build, and to run one, some, or all of the examples.

To build all of the examples, make the examples root directory the current
directory, and execute the command GUIBUILD.  For example:
  d:
  cd \powergui
  guibuild

To erase all of the files generated during the build, make the samples
root directory the current directory, and execute the command:
  d:
  cd \powergui
  guibuild (cleanall

To erase all of the generated files except for the files needed to run
the examples, execute the command:
  guibuild (clean

Although it might not be that useful to you, you can execute all of
the examples, one at a time, by executing the following command.  There
are over 100 examples, so do not try this unless you have a few minutes.
  guibuild (runall

Finally, you can execute one or more programs specifying a search string
to identify the program.  If the file, powergui.lst, contains the string
you specify on the line used to identify the example programs, the exec will
run the program.  This file contains essentially the same information which
we present below, to identify the examples.

For example, to run all of the container examples, enter:
  guibuild (run=cnr

To run just the program in the directory, cnr\treedet, enter:
  guibuild (run=\treedet

And to run all programs with "string" in their title or name, enter:
  guibuild (run=string

By default, guibuild redirects its output, such as compiler and linker
messages, into the file guibuild.log.  This file is generated in the
directory where you issued the guibuild request.

EXAMPLE PROGRAMS
-----------------------

  #    Chapter    Sample Location        Sample Description
-----  -------    --------------------   ------------------------------
  1        1       getstart\start1        Simple Example - Version 1
  2        1       getstart\start2        Simple Example - Version 2
  3        3       latour\shopping        Shopping List
  4        5       frame1\dialog          Frame Window From Dialog Template
  5        5       frame1\modal           Modal Frame Window
  6        5       frame1\minmax          Minimize/Maximize Handler
  7        5       frame1\ok2close        Confirm Frame Window Closing
  8        5       frame1\dstrycls        Defer Destroy On Closing Frame Window
  9        5       frame1\frmextns        Frame Extension Sampler
 10        6       menus\menures          Defining A Menu Resource
 11        6       menus\menubar          Using an IMenuBar
 12        6       menus\txtpopup         Pop Up Menu Sample
 13        6       menus\accel            Accelerator Table Loading
 14        6       menus\dynpopup         Dynamically Created Pop Up Menus
 15        6       menus\sysmenu          Accessing the System Menu
 16        6       menus\titlebmp         Title Bar Bitmaps
 17        6       menus\addsubmn         Loading a Resource Submenus
 18        6       menus\cursor           Using a Menu Cursor
 19        6       menus\dynsubmn         Dynamic Submenus
 20        6       menus\drawmenu         Drawing Menu Items
 21        7       controls               Control Constructor and Color Example
 22        8       static\textstyl        Static Text Style Sample
 23        8       static\textclr         Static Text Color Example
 24        8       static\textcv          Static Text and Canvas Example
 25        8       static\iconbmp         Icon and Bitmap Example
 26        8       static\boxes           Group Box and Outline Box Example
 27       10       buttons\pushbut        Push Button Example
 28       10       buttons\titlebut       Title Bar Bitmap Example
 29       10       buttons\radio          Radio Button Select Handler Example
 30       11       listctls\drawlist      List Box Custom Drawing Example
 31       11       listctls\spinbut       Spin Button Date Control Example
 32       12       slider\progind         Progress Indicator Custom Drawing Example
 33       12       slider\slider          Slider Example
 34       13       cnr\treetxtv           Container Tree Text View (fig)
 35       13       cnr\treeicov           Container Tree Text View (fig)
 36       13       cnr\treenamv           Container Tree Name View (fig)
 37       13       cnr\textview           Container Text View with Multiple Lines (fig)
 38       13       cnr\cdate              Dates and Times using CDATE/CTIME
 39       13       cnr\uidate             Dates and Times using IDate/ITime
 40       13       cnr\help               Using Help in the Container
 41       13       cnr\edithdr            Container MLE Edit Handler
 42       13       cnr\popup              Container Popup Menus
 43       13       cnr\dynobj             Dynamic Creation of Objects
 44       13       cnr\minicnr            Using Mini-Icons in the Container
 45       13       cnr\spreadsh           SpreadSheet Behavior in the Details View
 46       13       cnr\treedet            Combining the Tree and Details View
 47       14       notebook\simple        Simple Client Notebook
 48       14       notebook\default       Default Notebook (pic)
 49       14       notebook\addpages      Adding Notebook Pages
 50       14       notebook\vportdlg      Using a View Port on a Notebook Page
 51       14       notebook\select        Delayed Addition of Pages
 52       15       canvas\lunchdlg        Using Dialogs in a Canvas (fig)
 53       15       canvas\cvsimple        Simple ICanvas Example
 54       15       canvas\cvtab           Nested Canvas Tabbing Example
 55       15       canvas\setlunch        Lunch Dialog using a Set Canvas
 56       15       canvas\setdecks        Decks in a Set Canvas
 57       15       canvas\setpack         Deck Packing and Alignment in a Set Canvas
 58       15       canvas\mcsimple        Simple Multi-Cell Canvas
 59       15       canvas\mclunch         Lunch Dialog using a Multi-Cell Canvas
 60       15       canvas\splittxt        Simple Split-Canvas Example
 61       15       canvas\splitprb        Split Canvas with Problem Windows
 62       15       canvas\vportbmp        View Port for Scrolling a Bitmap
 63       15       canvas\vportlog        View Port with Logically Sized Windows
 64       15       canvas\complex         Complex Canvas Example  (bonus sample)
 65       16       genhdrs\cmdhdrs        Simple Command Handler Example
 66       16       genhdrs\keybd          Keyboard Handler Example
 67       16       genhdrs\mouseclk       Mouse Click Handler Example
 68       17       advframe\fstyle        Frame Window Style Example
 69       17       advframe\drawextn      Derived Frame Extension Example
 70       17       advframe\framesav      Frame Window Position Save Handler Example
 71       17       advframe\tstdlg        Dialog Window Example
 72       17       advframe\profile       Profile Viewer Example
 73       18       extlib\valueset        Creating a Value Set Class
 74       19       thread\simple          Simple Multi-threaded Example
 75       19       thread\system          Starting Threads with _System Linkage
 76       19       thread\optlink         Starting Threads with _OptLink Linkage
 77       20       dm\menudrag            Menu Drag Example
 78       20       dm\spindrag            Spin Button Drag Example
 79       20       dm\lboxdrag            List Box Drag Example
 80       22       help\basic             Basic Help Example
 81       22       help\special           Extended Help Example
 82       23       reslib\dlltext         Building a Resource DLL
 83       23       reslib\exetext         Using Resource in the EXE
 84       23       reslib\stattxt         Switching Resources Dynamically
 85       23       reslib\procaddr        Using IProcedureAddress
 86       24       profile\viewprof       Profile Dumper Application
 87       25       data\cipher            Using an IString as a Buffer
 88       25       data\igrep             Using IString::isLike
 89       25       data\strngtst          Using IStringTest
 90       25       data\convert           Using IString Conversion Functions
 91       25       data\mybuffer          Replacing IBuffer With Your Own Class
 92       25       data\str2date          Creating Dates and Times from Strings
 93       26       exceptns\newexcp       Deriving a New Exception Class
 94       26       exceptns\exviewer      An Exception Viewer
 95       27       debug\trace            Simple Trace Example
 96       27       debug\prtque           Trace Queue Browser Program
 97       27       debug\zeroptr          Debugging a Zero Pointer
 98       27       debug\excdisp          Displaying an Exception in a Message Box
 99       27       debug\invisibl         Finding Why a Window is not Visible
 100      27       debug\sigterm          Building a Termination Signal Handler
 101      28       shipapp\hello1         Changes to Hello1 for Start-Up Tuning
 102      28       shipapp\appstat        Using Static Object Functions instead of Static Objects
  *       28       shipapp\genprags       A Command File to Generate alloc_text for Static Functions

