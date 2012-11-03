#include "plist.h"

#include <QtCore/QFile>
#include <QtXml/QXmlInputSource>
#include <QMessageBox>
#include "xml.h"

const int pictureWidth  = 64;
const int pictureHeight = 64;

plist::plist(void)
{

  
}

plist::~plist(void)
{

}

void plist::initArray( QMainWindow * mWnd )
{
  int col = 0;
  for( int i = 0; i < 45;  )
  {
    int num = (col%2 == 0) ? 4 : 5;
    if( num == 4 )
      i++;
    for( int k = 0; k < num; k++, i++ )
    {
      int ind = (col+1)*5 - (k + 1);
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

///////////////////////////////////////////////////////////////////////////

cell::cell( int ind, state htype /* = original */, int tmr /* = -1 */, bool vsbl /* = true */ ) :
    hextype ( htype   ),
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
  hextype = ht;
}

void cell::initButton( QMainWindow * mWnd )
{
  Helper * help = Helper::Instance();
  button = new QPushButton( QIcon(":/" + help->GetItemNameByState( hextype )), "",  mWnd );
  button->setFixedWidth( pictureWidth+4 );
  button->setFixedHeight( pictureHeight+4 );
  button->setIconSize( QSize( pictureWidth, pictureHeight ) );
  button->setFlat( true );
  button->setCheckable(true);
}

void cell::UpdateView()
{
  Helper * help = Helper::Instance();
  button->setIcon( QIcon(":/" + help->GetItemNameByVisible( isVisible, hextype ) ) );
}                                                                           

bool cell::Serialize( QTextStream * out, int &level )
{
  xmlHelper * helper = xmlHelper::Instance();
  StreamWriteLevUp( out, oTag( helper->getStringByKeyDef(Dict) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, active ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_active ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, block ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_block ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, bomb) );
  StreamWrite( out, xmlHelper::wrapStringInKeyVal( Integer, xmlHelper::getStringByInteger(timer)) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, bunny ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_bunny ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, fire ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_fire ) ) );

  StreamWrite( out, xmlHelper::wrapKeyValInKeyVal( key, monster ) );
  StreamWrite( out, ocTag( xmlHelper::getStringByBoolean( hextype == s_monster ) ) );

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
  horizontalNumber = 9;
  verticalNumber = 5;
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