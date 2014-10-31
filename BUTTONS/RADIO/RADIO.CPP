//************************************************************
// Button Controls - Radio Button Select Handler                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iradiobt.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <icombobx.hpp>
#include <ipushbut.hpp>
#include <isetcv.hpp>
#include <iapp.hpp>
#include <iselhdr.hpp>
#include "radio.h"

// Radio Button Select Handler
class SelectHandler : public ISelectHandler
{
public:
  SelectHandler ( ISetCanvas& canvas)
      : _canvas(canvas)  {}

protected:
virtual Boolean
  selected   ( IControlEvent& event );

private:
ISetCanvas
 &_canvas;
SelectHandler& operator=(const SelectHandler&);
};

void main()
{
IFrameWindow
  frame ("Radio Button Select Handler Example");
IMultiCellCanvas 
  client(0x8008, &frame, &frame);

// Set1 for radio buttons; set2 for bitmap name
ISetCanvas 
  set1(ID_SET1, &client, &client),
  set2(ID_SET2, &client, &client);

// Set1 buttons
IRadioButton
  image(ID_IMAGE, &set1, &set1),
  color(ID_COLOR, &set1, &set1);
IPushButton
  changeColor(ID_CHANGECOLOR, &set1, &set2);

set1.setText("Background type");
set2.setText("Image");
image.setText("~Image");
color.setText("C~olor");
changeColor.setText("C~hange Color...");

// Set2 text and combo box
IStaticText
  fileLeader (ID_FILESTATIC, &set2, &set2);
IComboBox
  fileName   (ID_FILENAME, &set2, &set2, IRectangle(0,0,0,0),
              IComboBox::dropDownType | IWindow::visible);

fileLeader.setText("File:");
fileName.setText("os2.bmp");

// enable tab stops
image.enableTabStop();
fileName.enableTabStop();

// Select the color choice
image.select();

// Add the sets to the client canvas
client
 .addToCell(&set1, 2, 2, 3, 1)
 .addToCell(&set2, 2, 3, 3, 1);

// Allow for some growth in the canvas
client
 .setRowHeight   (4, 10, true);

// Create and energize the Select Handler
SelectHandler selectHandler(set2);
selectHandler.handleEventsFor(&set1);

// Put the canvas in the client and show the app
frame
  .setClient(&client)
  .setFocus()
  .show();
IApplication::current().run();

}

Boolean SelectHandler::selected ( IControlEvent& event )
{

   switch(event.controlId())
   {
     case ID_IMAGE :
     case ID_COLOR :
     {
        // Test to see if we should enable or disable
        Boolean enable =  (event.controlId() == ID_IMAGE);

        // If image button selected, Enable the canvas and its 
        // children, otherwise disable the canvas and its 
        // children.  Even though disabling the canvas disables
        // the children, they don't "look" disabled unless 
        // we explicitly disable them.
        IRadioButton* button = 
                       (IRadioButton*)event.controlWindow();
        if (button && button->isSelected())
        {
          _canvas.enable(enable);
          IWindow::ChildCursor cursor(_canvas);
          for(cursor.setToFirst(); 
              cursor.isValid(); 
              cursor.setToNext())
          {
             IWindow* child = IWindow::windowWithHandle(
                               _canvas.childAt(cursor));
             child->enable(enable);
          }
        }
        break;
     }
   }
   return false;
}
