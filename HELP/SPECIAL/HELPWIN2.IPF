#include "helpwin2.h"   // For preprocessor substitutions.
// Don't let preprocessor substitute the following in the
// help text.
#undef ID_HELPTABLE
#undef SUBTABLE_SECONDARY
#undef SUBTABLE_PAGE3
#undef SUBTABLE_DIALOG
:userdoc.
:docprof toc=1234.
.*
:h1 res=PANEL_PRIMARY.Primary Window - Help
:i1 id=primary.Help for the Primary Window
:p.This is the help for the sample&apos.s primary window.
.*
:h2 res=PANEL_CONTAINER.Container Object Help
:i2 refid=primary.Help for Container Objects
:p.This is contextual help for a container object.
:p.This is displayed through the
IContainerObject&colon.&colon.helpId function.
:p.Double-click the object or press the Enter key to open
a view of the object.
.*
:h3 res=PANEL_PAGE1.Help for First Canvas Page Window
:p.This is the general help for the first canvas page window.
:p.This is displayed through the
IHelpHandler&colon.&colon.handleError function.
.*
:h3 res=PANEL_PAGE1_TAB.Help for First Notebook Tab
:p.This is help for the first notebook tab.
:p.This is displayed through the
IPageHandler&colon.&colon.help function.
.*
:h4 res=PANEL_ENTRY1.Entry Field Help
:p.This is contextual help for the first entry field
on the first canvas page window.
:p.This is displayed through the SUBTABLE_SECONDARY
help subtable.
.*
:h4 res=PANEL_ENTRY3.Entry Field Help
:p.This is contextual help for the third entry field
on the first canvas page window.
:p.This is displayed through the
IHelpHandler&colon.&colon.subitemNotFound function.
.*
:h3 res=PANEL_PAGE2.Help for Second Canvas Page Window
:p.This is the general help for the second canvas page window.
:p.This is displayed through the
IHelpHandler&colon.&colon.handleError function.
.*
:h3 res=PANEL_PAGE2_TAB.Help for Second Notebook Tab
:p.This is help for the second notebook tab.
:p.This is displayed through the
IPageHandler&colon.&colon.help function.
.*
:h4 res=PANEL_ENTRYA.Entry Field Help
:p.This is contextual help for the first entry field
on the second canvas page window.
:p.This is displayed through the SUBTABLE_SECONDARY
help subtable.
.*
:h4 res=PANEL_ENTRYC.Entry Field Help
:p.This is contextual help for the third entry field
on the second canvas page window.
:p.This is displayed through the
IHelpHandler&colon.&colon.subitemNotFound function.
.*
:h3 res=PANEL_PAGE3.Help for Canvas in Frame Page Window
:p.This is the general help for the frame page window
containing the third canvas.
:p.This is displayed through the ID_HELPTABLE help table.
.*
:h3 res=PANEL_PAGE3_TAB.Help for Third Notebook Tab
:p.This is help for the third notebook tab.
:p.This is displayed through the
IPageHandler&colon.&colon.help function.
.*
:h4 res=PANEL_ENTRYX.Entry Field Help
:p.This is contextual help for the entry field on the
frame page window, containing the third canvas.
:p.This is displayed through the SUBTABLE_PAGE3
help subtable.
.*
:h3 res=PANEL_DIALOG.Help for Dialog Page Window
:p.This is the general help for the dialog page window.
:p.This is displayed through the ID_HELPTABLE help table.
.*
:h3 res=PANEL_DIALOG_TAB.Help for Fourth Notebook Tab
:p.This is help for the fourth notebook tab.
:p.This is displayed through the
IPageHandler&colon.&colon.help function.
.*
:h4 res=PANEL_DIALOG_ENTRY1.Entry Field Help
:p.This is contextual help for the entry field on the
dialog page window.
:p.This is displayed through the SUBTABLE_DIALOG
help subtable.
.*
:h1 res=PANEL_DROP.Help for Drag and Drop
:i1 id=secondary.Help for Drag and Drop
:p.You can only use drag and drop to move a container
object around this container.
:p.This is displayed through the
IDMItemProviderFor<>&colon.&colon.provideHelpFor function.
.*
:euserdoc.
