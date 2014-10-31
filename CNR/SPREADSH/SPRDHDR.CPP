//************************************************************
// Container Control - Spreadsheet Behavior
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "sprdhdr.hpp"

// SpreadSheetHandler
// The handler fully implements the spreadsheet-like behavior.
// On creation, we post an SPD_OPEN so we initally have an
// edit field open on the container.
CnrSpreadSheetHandler::CnrSpreadSheetHandler( 
                         IContainerControl& container)
                 : cnrctl(container),
                   accel(SPD_ACCELERATOR, container.owner()) {
  container.owner()->postEvent(IWindow::command, SPD_OPEN);
}

IContainerControl& CnrSpreadSheetHandler::container( ) {
  return cnrctl;
}

Boolean CnrSpreadSheetHandler:: command(ICommandEvent& cmdevt) {
  Boolean processed =false;

  switch (cmdevt.commandId())
  {
    // Forward Tab - right and possibly down
    case  SPD_TAB :
    {
      IContainerControl::ColumnCursor colCursor(container());
      IContainerControl::ObjectCursor objCursor(container(),
                                 IContainerObject::none,
                                 IContainerControl::itemOrder);
      IContainerColumn* pcnrcol = container().currentEditColumn();
      IContainerObject* pcnrobj = container().currentEditObject();

      if(pcnrcol) {
         colCursor.setCurrent(pcnrcol);

         // See if there is a next column in this row for edit.
         // If not move to the next row, first column.         
         if ((pcnrcol=colCursor.next())== 0)
         {
            objCursor.setCurrent(pcnrobj);
            pcnrobj = objCursor.next();
            pcnrcol = colCursor.first();

         }
         // Scroll to the object and open the edit field.
         if(pcnrobj) {
           container().closeEdit();
           container().scrollToObject(pcnrobj, pcnrcol, false);
           container().editObject(pcnrobj, pcnrcol);
         }
      }
      processed = true;
      break;
    }
    // Back Tab Left and possibly up
    case  SPD_BACKTAB :
    {
      IContainerControl::ColumnCursor colCursor(container());
      IContainerControl::ObjectCursor objCursor(container(),
                                IContainerObject::none,
                                IContainerControl::itemOrder);
      IContainerColumn* pcnrcol = container().currentEditColumn();
      IContainerObject* pcnrobj = container().currentEditObject();

      if(pcnrcol) {
     
         colCursor.setCurrent(pcnrcol);
         // See if there is a previous column in this row for  
         // edit, If not move to the prior row, first column.  
         if ((pcnrcol=colCursor.previous())== 0)
         {
            objCursor.setCurrent(pcnrobj);
            pcnrobj = objCursor.previous();
            pcnrcol = colCursor.last();
     
         }
         if(pcnrobj) {
           container().closeEdit();
           container().scrollToObject(pcnrobj, pcnrcol, false);
           container().editObject(pcnrobj, pcnrcol);
         }
      }
      processed = true;
      break;
    }
    // Up - Go to prior record; stop at first
    case  SPD_UP :
    {
      IContainerControl::ColumnCursor colCursor(container());
      IContainerControl::ObjectCursor objCursor(container(),
                                 IContainerObject::none,
                                 IContainerControl::itemOrder);
      IContainerColumn* pcnrcol = container().currentEditColumn();
      IContainerObject* pcnrobj = container().currentEditObject();
      if(pcnrcol) {
        if(pcnrobj) {
          objCursor.setCurrent(pcnrobj);
          pcnrobj = objCursor.previous();
        }
        else
          pcnrobj = objCursor.first();
     
        if (pcnrobj) {
           container().closeEdit();
           container().scrollToObject(pcnrobj, pcnrcol, false);
           container().editObject(pcnrobj, pcnrcol);
     
        }
      }
      processed = true;
      break;
    }
    case  SPD_DOWN :
    // Up - Go to next record; stop at last
    {
      IContainerControl::ColumnCursor colCursor(container());
      IContainerControl::ObjectCursor objCursor(container(),
                                 IContainerObject::none,
                                 IContainerControl::itemOrder);
      IContainerColumn* pcnrcol = container().currentEditColumn();
      IContainerObject* pcnrobj = container().currentEditObject();
      if(pcnrcol) {
        if(pcnrobj) {
          objCursor.setCurrent(pcnrobj);
          pcnrobj = objCursor.next();
        }
        else
          pcnrobj = objCursor.last();
     
        if (pcnrobj) {
           container().closeEdit();
           container().scrollToObject(pcnrobj, pcnrcol, false);
           container().editObject(pcnrobj, pcnrcol);
        }
      }
      processed = true;
      break;
    }
    // Initial Open
    case  SPD_OPEN :
    {
      IContainerControl::ColumnCursor colCursor(container());
      IContainerControl::ObjectCursor objCursor(container(),
                                 IContainerObject::none,
                                 IContainerControl::itemOrder);
      colCursor.setToFirst();
      objCursor.setToFirst();
      if(colCursor.isValid() && objCursor.isValid()) {
           container().scrollToObject(container().objectAt(objCursor));
           container().editObject(container().objectAt(objCursor), 
                                  container().columnAt(colCursor));
      }


      processed = true;
      break;
    }
 }
 return processed;
}
