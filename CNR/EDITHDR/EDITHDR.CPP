//************************************************************
// Container - Keyboard Handler for MLE
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <icnrctl.hpp>
#include <icnrobj.hpp>
#include <icnrhdr.hpp>
#include <icnrehdr.hpp>
#include "keyhdr.hpp"

void main()
{
// Create the frame and a container.
IFrameWindow frame("Container Keyboard Edit Handler");
IContainerControl cnr(0x8008, &frame, &frame);

// Create and attach the Container handlers.
ICnrEditHandler editHandler;
ICnrHandler cnrHandler;
editHandler.handleEventsFor(&cnr);
cnrHandler.handleEventsFor(&cnr);

// Create the keyboard handler and pass it to
// the Container's edit handler to use whenever
// an MLE is created.
KeyboardHandler keyHandler;
editHandler.setMLEHandler(&keyHandler);

// Add an object for editing.
IContainerObject* object;
object = new IContainerObject("Object 1");
cnr
  .addObject(object)
  .enableDataUpdate(object);

// Put the container into the text view and
// give it the focus.
cnr
  .showTextView()
  .setFocus();

// Put the container in the client and
// show the frame.
frame
 .setClient(&cnr)
 .show();

// Start processing messages
IApplication::current().run();
}
