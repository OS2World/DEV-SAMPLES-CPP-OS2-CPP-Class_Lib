#ifndef _DECKCV_
#define _DECKCV_
//************************************************************
// Canvas - ISetCanvas decks example.
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <iseq.h>

class DeckCanvas : public ISetCanvas {
public:
  DeckCanvas     ( unsigned long id,
                   IWindow* parentAndOwner,
                   IWindow* frameOrClient );
virtual
 ~DeckCanvas     ( );
unsigned long
  childCount     ( ) const;
DeckCanvas
 &setChildCount  ( unsigned long count ),
 &setUpChild     ( IStaticText* child ),
 &addAsFirst     ( ),
 &addAsLast      ( ),
 &removeFirst    ( ),
 &removeLast     ( ),
 &makeHorizontal ( ),
 &makeVertical   ( );
#if IC_MAJOR_VERSION < 201
DeckCanvas
 &setLayoutDistorted ( unsigned long flagsOn,
                       unsigned long flagsOff );
#endif

private:
class DeckCommandHandler : public ICommandHandler {
  public:
    DeckCommandHandler ( DeckCanvas* canvas );
  protected:
  virtual Boolean
    command            ( ICommandEvent& event );
  private:
  DeckCanvas
   *deckCanvas;
  };
DeckCommandHandler
  cmdHandler;
class ChildList : public ISequence< IStaticText* > {
  public:
    ChildList ( )
      : ISequence< IStaticText* >( 10 )
    { };
  };
ChildList
  children;
unsigned long
  childrenCreated;
friend Boolean
  ChildDeleter ( IStaticText* const& element,
                 void* anything )
  {
    delete element;
    return true;
  }
DeckCanvas( const DeckCanvas&);
DeckCanvas operator=( const DeckCanvas&);
};

#endif // _DECKCV_
