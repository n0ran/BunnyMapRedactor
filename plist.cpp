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

CPlist::CPlist( int w, int h )
{
	params.SetHorizontalNumber( w );
	params.SetVerticalNumber( h );
}

CPlist::~CPlist(void)
{

}

void CPlist::initArray( QMainWindow * mWnd )
{
  int col = 0;
  for( int i = 0; i < params._verticalNumber * params._horizontalNumber;  )
  {
    int num = (col%2 == 0) ? params._verticalNumber-1 : params._verticalNumber;
    if( num == params._verticalNumber-1 )
      i++;
    for( int k = 0; k < num; k++, i++ )
    {
      int ind = (col+1)*params._verticalNumber - (k + 1);
      CCell * item = new CCell(ind);
      item->initButton( mWnd );
      arr[ind] = item;
    }
    col++;
  }
}

void CPlist::initArray( QMainWindow * mWnd, QString &filename )
{
  QFile file( filename );
  QXmlInputSource inputSource( &file );
  QXmlSimpleReader reader;
  xmlReader handler( this );
  reader.setContentHandler( &handler );
  reader.setErrorHandler( &handler );
  reader.parse( inputSource );

  std::map< int, CCell* >::const_iterator it;
  for( it = arr.begin(); it != arr.end(); ++it )
  {
    it->second->initButton( mWnd );
  }
}

int CPlist::GetButtonIndex( QPushButton * button )
{
  map< int, CCell*>::const_iterator it;
  for( it = arr.begin(); it != arr.end(); ++it )
  {
    if( it->second->button == button )
      return it->first;
  }

  return -1;
}


CCell* CPlist::getItem( int index )
{
  return arr[index];
}

void CPlist::addItem( CCell * pcell )
{
  arr[pcell->index] = pcell;
}

void CPlist::clear()
{
  arr.clear();
}

bool CPlist::Serialize( QTextStream * out, int &level )
{
  xmlHelper * helper = xmlHelper::Instance();
  StreamWrite( out, "<plist version=\"1.0\">" );
  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Dict) ) );
  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, hexs ) );

  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Array) ) );
  map< int, CCell* >::const_iterator it;
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


bool CPlist::SaveInFile( QString filename )
{
  xmlWriter wr( this, filename );
  return wr.SaveFile();
}

int CPlist::GetWidth()
{
	return params._horizontalNumber;
}

int CPlist::GetHeight()
{
	return params._verticalNumber;
}

int CPlist::GetSteps()
{
	return params._steps;
}

void CPlist::SetWidth( int w )
{
	params.SetHorizontalNumber( w );
}

void CPlist::SetHeight( int h )
{
	params.SetVerticalNumber( h );
}

void CPlist::SetSteps( int s )
{
	params.SetSteps( s );
}
///////////////////////////////////////////////////////////////////////////

CCell::CCell( int ind, state htype /* = original */, state unt /* = original */, int tmr /* = -1 */, bool vsbl /* = true */ ) :
    hextype ( htype   ),
		unit	( unt ),
    timer   ( tmr     ),
    index  ( ind     ),
    isVisible ( vsbl    ),
    button  ( NULL    )
{
}

CCell::~CCell()
{
  if( button )
    delete button;
}

void CCell::setState( state ht )
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
	case s_invisible:
		isVisible = !isVisible;
		break;
	default:
		hextype = ht;
	}

}

void CCell::initButton( QMainWindow * mWnd )
{
  Helper * help = Helper::Instance();
  button = new QPushButton( QIcon(":/" + help->GetItemNameByState( hextype )), "",  mWnd );
  button->setFixedWidth( GetButtonWidth() );
  button->setFixedHeight( GetButtonHeight() );
  button->setIconSize( QSize( GetButtonWidth(), GetButtonHeight() ) );
  button->setFlat( true );
  button->setCheckable(true);
}

void CCell::UpdateView()
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
		//button->setText( "1" );
	}
}                                                                           

bool CCell::Serialize( QTextStream * out, int &level )
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

CParametres::CParametres()
{
	SetSteps(0);
	SetHorizontalNumber(9);
	SetVerticalNumber(5);
}
bool CParametres::Serialize( QTextStream * out, int &level )
{
  xmlHelper * helper = xmlHelper::Instance();
  
  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, parametres ) );

  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Dict) ) );

	StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, steps) );
	StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(_steps)) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, horizontalNumber) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(_horizontalNumber)) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, verticalNumber) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(_verticalNumber)) );

  StreamWriteLevDown( out, cTag( helper->getStringByKeyDef(Dict) ) );
  return true;
}

void CParametres::SetHorizontalNumber( int n )
{
	_horizontalNumber = n;
	Helper::hnumber = _horizontalNumber;
}

void CParametres::SetVerticalNumber( int n )
{
	_verticalNumber = n;
	Helper::vnumber = _verticalNumber;
}

void CParametres::SetSteps( int n )
{
	_steps = n;
}