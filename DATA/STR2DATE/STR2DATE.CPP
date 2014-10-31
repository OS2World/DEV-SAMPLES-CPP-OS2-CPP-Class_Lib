//************************************************************
// Data Types - Creating Dates and Times from IStrings
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//                                                                              
// DESCRIPTION:                                                                 
//   This program implements a simplistic file encryption/decryption scheme.    
//   It simply XORs the contents of cin using the argument "key" string and     
//   writes the result to cout.                                                 
//                                                                              
//   Usage:      str2date "secret key" < input > output                         
//                                                                              
//
//************************************************************
#include <istring.hpp>
#include <idate.hpp>
#include <iostream.h>

IDate
  dateFrom( const IString &dateString, const IString &formatString );

int main ( int argc, char *argv[] )
  {
  int
    result = 0;

  /*----------------------------------------------------------------------------
  | Get input and format strings.                                              |
  ----------------------------------------------------------------------------*/
  if ( argc < 2 )
    {
    cerr << "Input date string required.\a" << endl;
    return 1;
    }
  IString
    date  ( argv[1] ),
    format( argv[2] );

  /*----------------------------------------------------------------------------
  | Display date obtained from input.                                          |
  ----------------------------------------------------------------------------*/
  IDate
    fromInput = dateFrom( date, format );
  IString
    check;
  if ( argc == 2 )
    check = fromInput.asString();
  else
    check = fromInput.asString( format );
  if ( check != date )
    cout << '\a';
  cout << "Date appears to be: " << fromInput.asString( "%B %d %Y" ) << endl 
       << "fromInput.asString( \"" << format << "\" ) -> \"" 
       << check << "\"" << endl;

  return result;
  }

IDate dateFrom ( const IString &dateString, const IString &formatString )
  {
  IDate
    result;

  /*----------------------------------------------------------------------------
  | Allocate arrays of strings to hold day and month names.                    |
  ----------------------------------------------------------------------------*/
  IString
    dayNames[ 7 ],
    dNames  [ 7 ],
    monNames[ 12 ],
    mNames  [ 12 ];
 
  /*----------------------------------------------------------------------------
  | Allocte private format string for use by this function.                    |
  ----------------------------------------------------------------------------*/
  IString
    fmtString( formatString );

  /*----------------------------------------------------------------------------
  | If no format string is specified, use the default.  The default is the     |
  | system-specified format.  We deduce it by formating some specified date    |
  | and seeing how it is layed out.                                            |
  ----------------------------------------------------------------------------*/
  if ( fmtString.length() == 0 )
    {
    IString
      test = IDate( IDate::November, 23, 1984 ).asString();
    if ( test.indexOf( "11" ) == 1 )
      fmtString = test.overlayWith( "%m", 1 ).overlayWith( "%d", 4 );
    else
      fmtString = test.overlayWith( "%m", 4 ).overlayWith( "%d", 1 );
    fmtString.overlayWith( "%y", 7 );
    }
  else
    /*--------------------------------------------------------------------------
    | Format string might contain month/day name specifiers, so build arrays.  |
    --------------------------------------------------------------------------*/
    {
    if ( fmtString.includes( "%a" ) || fmtString.includes( "%A" ) )
      {
      IDate
        aDay( IDate::October, 4, 1985 );
      for ( int i = 0; i < 7; i++ )
        {
        dNames[ i ] = (aDay+i).asString( "%a" );
        dayNames[ i ] = (aDay+i).asString( "%A" );
        }
      }
    if ( fmtString.includes( "%b" ) || fmtString.includes( "%B" ) )
      {
      IDate
        aDay( IDate::January, 1, 1994 );
      for ( int i = 0; i < 12; i++ )
        {
        mNames[ i ] = aDay.asString( "%b" );
        monNames[ i ] = aDay.asString( "%B" );
        aDay += IDate::daysInMonth( aDay.monthOfYear(), aDay.year() );
        }
      }
    }
cerr << "fmtString=" << fmtString << endl;
  /*----------------------------------------------------------------------------
  | Set indices into source and format strings.                                |
  ----------------------------------------------------------------------------*/
  unsigned
    srcIndex = 1,
    fmtIndex = 1;

  /*----------------------------------------------------------------------------
  | Allocate placeholders for parsed month, day, year.                         |
  ----------------------------------------------------------------------------*/
  int
    month = 0,
    day   = 0,
    year  = 0;

  /*----------------------------------------------------------------------------
  | Parse out conversion specifiers in fmtString.                              |
  ----------------------------------------------------------------------------*/
  while ( fmtIndex <= fmtString.length() )
    {
cerr << IString( '|' ).rightJustify( fmtIndex ) << endl;
cerr << fmtString << endl;
cerr << IString( '|' ).rightJustify( srcIndex ) << endl;
cerr << dateString << endl;
    /*--------------------------------------------------------------------------
    | Find the next conversion specifier.                                      |
    --------------------------------------------------------------------------*/
    unsigned
      next = fmtString.indexOf( '%', fmtIndex );
    if ( !next )
      next = fmtString.length();

    /*--------------------------------------------------------------------------
    | Skip over literal text in the source string.                             |
    --------------------------------------------------------------------------*/
    srcIndex += next - fmtIndex;

    /*--------------------------------------------------------------------------
    | Switch on next conversion specifier (if there is one).                   |
    --------------------------------------------------------------------------*/
    if ( next < fmtString.length() )
      {
      IString
        remainder = dateString.subString( srcIndex );
cerr << "remainder=" << remainder << endl;
      switch ( fmtString[ next+1 ] )
        {
        /*----------------------------------------------------------------------
        | Source string contents will be something like Fri or Friday.         |
        | Step through days of the week, looking for a match.                  |
        ----------------------------------------------------------------------*/
        case 'a': 
          {
          for ( unsigned i = 0; i < 7; i++ )
            {
            if ( dNames[ i ].isAbbreviationFor( remainder ) )
              {
              srcIndex += dNames[ i ].length();
              break;
              }
            }
          if ( i == 7 )
            cerr << "Source string doesn't match format string.\a" << endl;
          break;
          }
        case 'A':
          {
          for ( unsigned i = 0; i < 7; i++ )
            {
            if ( dayNames[ i ].isAbbreviationFor( remainder ) )
              {
              srcIndex += dayNames[ i ].length();
              break;
              }
            }
          if ( i == 7 )
            cerr << "Source string doesn't match format string.\a" << endl;
          break;
          }
        /*----------------------------------------------------------------------
        | Source string contents will be something like Apr or April.          |
        | Step through month names, looking for a match.  If one is found,     |
        | then remember what month it was as this is useful information when   |
        | it comes time to figure out what the IDate result should be.         |
        ----------------------------------------------------------------------*/
        case 'b':
          {
          for ( unsigned i = 0; i < 12; i++ )
            {
            if ( mNames[ i ].isAbbreviationFor( remainder ) )
              {
              month = i + (int)IDate::January;
              srcIndex += mNames[ i ].length();
              break;
              }
            }
          if ( i == 12 )
            cerr << "Source string doesn't match format string.\a" << endl;
          break;
          }
        case 'B':
          {
          for ( unsigned i = 0; i < 12; i++ )
            {
            if ( monNames[ i ].isAbbreviationFor( remainder ) )
              {
              month = i + (int)IDate::January;
              srcIndex += monNames[ i ].length();
              break;
              }
            }
          if ( i == 12 )
            cerr << "Source string doesn't match format string.\a" << endl;
          break;
          }
        case 'c':
          /*--------------------------------------------------------------------
          | Source string has the full-blown date in form 90/11/24.            |
          --------------------------------------------------------------------*/
          year = 1900 + remainder.asInt();
          month = remainder.subString( 4 ).asInt() - 1 + (int)IDate::January;
          day  = remainder.subString( 7 ).asInt();
          next = fmtString.length();
          break;
        case 'd':
          /*--------------------------------------------------------------------
          | Source string has the day number as a two-digit value.             |
          --------------------------------------------------------------------*/
          day = remainder.subString( 1, 2 ).asInt();
          srcIndex += 2;
          break;
        case 'j':
          /*--------------------------------------------------------------------
          | Source string has the day of the year as a 3 digit number.         |
          --------------------------------------------------------------------*/
          day = 0 - remainder.subString( 1, 3 ).asInt();
          srcIndex += 3;
          break;
        case 'm':
          /*--------------------------------------------------------------------
          | Source string has month as a 2 digit number.                       |
          --------------------------------------------------------------------*/
          month = remainder.subString( 1, 2 ).asInt() - 1 + (int)IDate::January;
          srcIndex += 2;
          break;
        case 'U':
          /*--------------------------------------------------------------------
          | Source string has week number as a two digit number.               |
          --------------------------------------------------------------------*/
          srcIndex += 2;
          break;
        case 'w':
          /*--------------------------------------------------------------------
          | Source string has day of the week as a one digit number.           |
          --------------------------------------------------------------------*/
          srcIndex += 1;
          break;
        case 'W':
          /*--------------------------------------------------------------------
          | Source string has week number as two digit number.                 |
          --------------------------------------------------------------------*/
          srcIndex += 2;
          break;
        case 'x':
          /*--------------------------------------------------------------------
          | Source string has date in form mm/dd/yy.                           |
          --------------------------------------------------------------------*/
          month = remainder.asInt() - 1 + (int)IDate::January;
          day  = remainder.subString( 4 ).asInt();
          year = 1900 + remainder.subString( 7 ).asInt();
          next = fmtString.length();
          break;
        case 'y':
          /*--------------------------------------------------------------------
          | Source string has year (since 1900) as 2 digit string.             |
          --------------------------------------------------------------------*/
          year = 1900 + remainder.subString( 1, 2 ).asInt();
          srcIndex += 2;
          break;
        case 'Y':
          /*--------------------------------------------------------------------
          | Source string has year (since 1900) as 2 digit string.             |
          --------------------------------------------------------------------*/
          year = remainder.subString( 1, 4 ).asInt();
          srcIndex += 4;
          break;
        default:
          /*--------------------------------------------------------------------
          | Unknown specifier, ignore it.                                      |
          --------------------------------------------------------------------*/
          cerr << "Unknwn specifier %" << fmtString[ next+1 ] << endl;
          srcIndex += 1;
          break;
        }
      }

    /*--------------------------------------------------------------------------
    | Advance fmtString index.                                                 |
    --------------------------------------------------------------------------*/
    fmtIndex = next + 2;
    }

cerr << "month=" << month << endl;
cerr << "day  =" << day   << endl;
cerr << "year =" << year  << endl;

  if ( day < 0 )
    /*--------------------------------------------------------------------------
    | We got day as the day within the year.                                   |
    --------------------------------------------------------------------------*/
    result = IDate( year, -day );
  else
    /*--------------------------------------------------------------------------
    | Construct result from month/day/year.                                    |
    --------------------------------------------------------------------------*/
    result = IDate( (IDate::Month)month, day, year );
 
  return result;
  }
