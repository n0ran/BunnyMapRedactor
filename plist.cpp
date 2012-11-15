#include "plist.h"

#include <QtCore/QFile>
#include <QtXml/QXmlInputSource>
#include <QMessageBox>
#include "xml.h"
#include <QPainter>

const int pictureWidth  = 100;
const int pictureHeight = 100;

const int def_vnumber = 5;
const int def_hnumber = 9;

int GetButtonWidth()
{
	double val = ( 1.0 * def_hnumber / Helper::hnumber )*pictureWidth + 4; 
	return (int)val;
}

int GetButtonHeight()
{
	double val = ( 1.0 * def_vnumber / Helper::vnumber )*pictureHeight + 4;
	return (int)val;
}

plist::plist( int w, int h )
{
	params.SetHorizontalNumber( w );
	params.SetVerticalNumber( h );
}

plist::~plist(void)
{

}

void plist::initArray( QMainWindow * mWnd )
{
  int col = 0;
  for( int i = 0; i < params.verticalNumber * params.horizontalNumber;  )
  {
    int num = (col%2 == 0) ? params.verticalNumber-1 : params.verticalNumber;
    if( num == params.verticalNumber-1 )
      i++;
    for( int k = 0; k < num; k++, i++ )
    {
      int ind = (col+1)*params.verticalNumber - (k + 1);
      cell * item = new cell(ind);
      item->initButton( mWnd );
      arr[ind] = item;
    }
    col++;
  }
}

void plist::initArray( QMainWindow * mWnd, QString &filename )
{
  QFile file( filename );
  QXmlInputSource inputSource( &file );
  QXmlSimpleReader reader;
  xmlReader handler( this );
  reader.setContentHandler( &handler );
  reader.setErrorHandler( &handler );
  reader.parse( inputSource );

  std::map< int, cell* >::const_iterator it;
  for( it = arr.begin(); it != arr.end(); ++it )
  {
    it->second->initButton( mWnd );
  }
}

int plist::GetButtonIndex( QPushButton * button )
{
  map< int, cell*>::const_iterator it;
  for( it = arr.begin(); it != arr.end(); ++it )
  {
    if( it->second->button == button )
      return it->first;
  }

  return -1;
}


cell* plist::getItem( int index )
{
  return arr[index];
}

void plist::addItem( cell * pcell )
{
  arr[pcell->index] = pcell;
}

void plist::clear()
{
  arr.clear();
}

bool plist::Serialize( QTextStream * out, int &level )
{
  xmlHelper * helper = xmlHelper::Instance();
  StreamWrite( out, "<plist version=\"1.0\">" );
  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Dict) ) );
  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, hexs ) );

  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Array) ) );
  map< int, cell* >::const_iterator it;
  for( it = arr.begin(); it != arr.end(); ++it )
  {
    it->second->Serialize( out, level );
  }

  StreamWriteLevDown( out, cTag( helper->getStringByKeyDef(Array) ) );

  params.Serialize( out, level );

  StreamWriteLevDown( out, cTag( helper->getStringByKeyDef(Dict) ) );
  StreamWriteLevDown( out, "</plist>" );

  return true;
}


bool plist::SaveInFile( QString filename )
{
  xmlWriter wr( this, filename );
  return wr.SaveFile();
}

int plist::GetWidth()
{
	return params.horizontalNumber;
}

int plist::GetHeight()
{
	return params.verticalNumber;
}

void plist::SetWidth( int w )
{
	params.SetHorizontalNumber( w );
}

void plist::SetHeight( int h )
{
	params.SetVerticalNumber( h );
}
///////////////////////////////////////////////////////////////////////////

cell::cell( int ind, state htype /* = original */, state unt /* = original */, int tmr /* = -1 */, bool vsbl /* = true */ ) :
    hextype ( htype   ),
		unit	( unt ),
    timer   ( tmr     ),
    index  ( ind     ),
    isVisible ( vsbl    ),
    button  ( NULL    )
{
}

cell::~cell()
{
  if( button )
    delete button;
}

void cell::setState( state ht )
{
	switch( ht )
	{
	case s_bunny:
	case s_active:
	case s_monster:
		if( unit != ht )
			unit = ht;
		else
			unit = s_original;
		break;
	default:
		hextype = ht;
	}

}

void cell::initButton( QMainWindow * mWnd )
{
  Helper * help = Helper::Instance();
  button = new QPushButton( QIcon(":/" + help->GetItemNameByState( hextype )), "",  mWnd );
  button->setFixedWidth( GetButtonWidth() );
  button->setFixedHeight( GetButtonHeight() );
  button->setIconSize( QSize( GetButtonWidth(), GetButtonHeight() ) );
  button->setFlat( true );
  button->setCheckable(true);
}

void cell::UpdateView()
{
  Helper * help = Helper::Instance();

	if( isVisible && unit != s_original )
	{
		QImage source( ":/" + help->GetItemNameByState( hextype ) );
		QImage destination( ":/" + help->GetItemNameByState( unit ) );
		//destination = destination.scaled( button->width(), button->height() );
		QPainter resultPainter(&source);

		resultPainter.setCompositionMode( QPainter::CompositionMode_SourceOver );
		resultPainter.drawImage( 0, 0, destination );
		resultPainter.end();    

		button->setIcon( QIcon( QPixmap::fromImage( source ) ) );
	}
	else
	{
		button->setIcon( QIcon(":/" + help->GetItemNameByVisible( isVisible, hextype ) ) );
	}
}                                                                           

bool cell::Serialize( QTextStream * out, int &level )
{
  xmlHelper * helper = xmlHelper::Instance();
  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Dict) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, active ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( unit == s_active ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, block ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_block ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, bomb) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(timer)) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, bunny ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( unit == s_bunny ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, fire ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_fire ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, monster ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( unit == s_monster ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, number) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(index)) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, strong ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_strong ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, teleport ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_teleport ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, visible ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( isVisible ) ) );
  StreamWriteLevDown( out, cTag( helper->getStringByKeyDef(Dict) ) );
  return true;
}

///////////////////////////////////////////////////////////////////////////

parametres::parametres()
{
}
bool parametres::Serialize( QTextStream * out, int &level )
{
  xmlHelper * helper = xmlHelper::Instance();
  
  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, keyValues::parametres ) );

  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Dict) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, keyValues::horizontalNumber) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(horizontalNumber)) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, keyValues::verticalNumber) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(verticalNumber)) );

  StreamWriteLevDown( out, cTag( helper->getStringByKeyDef(Dict) ) );
  return true;
}

void parametres::SetHorizontalNumber( int n )
{
	horizontalNumber = n;
	Helper::hnumber = horizontalNumber;
}

void parametres::SetVerticalNumber( int n )
{
	verticalNumber = n;
	Helper::vnumber = verticalNumber;
}