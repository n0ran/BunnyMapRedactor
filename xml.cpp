#include "xml.h"

#include <QtCore/QFile>
#include <QtXml/QXmlInputSource>


xmlHelper::xmlHelper()
{
  initDictionary();
}

xmlHelper::~xmlHelper()
{
  if( _instance ) 
    delete _instance;
}

xmlHelper* xmlHelper::_instance = NULL;

xmlHelper* xmlHelper::Instance()
{
  if( !_instance )
  {
    _instance = new xmlHelper;
  }
  return _instance;
}

void xmlHelper::initDictionary()
{
  keyDictionary[True            ] = new QString( "true"             );
  keyDictionary[False           ] = new QString( "false"            );
  keyDictionary[Integer         ] = new QString( "integer"          );
  keyDictionary[hexs            ] = new QString( "hexs"             );
  keyDictionary[active          ] = new QString( "active"           );
  keyDictionary[block           ] = new QString( "block"            );
  keyDictionary[bomb            ] = new QString( "bomb"             );
  keyDictionary[bunny           ] = new QString( "bunny"            );
  keyDictionary[fire            ] = new QString( "fire"             );
  keyDictionary[monster         ] = new QString( "monster"          );
  keyDictionary[number          ] = new QString( "number"           );
  keyDictionary[strong          ] = new QString( "strong"           );
  keyDictionary[teleport        ] = new QString( "teleport"         );
  keyDictionary[visible         ] = new QString( "visible"          );
  keyDictionary[parametres      ] = new QString( "parametres"       );
  keyDictionary[horizontalNumber] = new QString( "horizontalNumber" );
  keyDictionary[verticalNumber  ] = new QString( "verticalNumber"   );
  keyDictionary[Dict            ] = new QString( "dict"             );
  keyDictionary[Array           ] = new QString( "array"            );
  keyDictionary[key             ] = new QString( "key"              );
}

keyValues xmlHelper::getKeyDefByString( const QString & str )
{
  map< keyValues, QString* >::const_iterator it;
  for( it = keyDictionary.begin(); it != keyDictionary.end(); ++it )
  {
    if( it->second == str )
    {
      return it->first;
    }
  }
  return unknown;
}

QString xmlHelper::getStringByKeyDef( keyValues val )
{
  map< keyValues, QString* >::const_iterator it;
  return *keyDictionary[val];
}

QString xmlHelper::getTabByLevel( int level )
{
  QString result = "";
  for( int i = 0; i < level; i++ )
  {
    result += "\t";
  }
  return result;
}
QString xmlHelper::wrapKeyValInKeyVal( keyValues inWhat, keyValues what  )
{
  xmlHelper * helper = xmlHelper::Instance();
  QString whatStr = helper->getStringByKeyDef( what );
  QString inWhatStr = helper->getStringByKeyDef( inWhat );

  QString result = Wrap( inWhatStr, whatStr );

  return result;
}
QString xmlHelper::wrapStringInKeyVal( keyValues inWhat, QString what )
{
  xmlHelper * helper = xmlHelper::Instance();
  QString inWhatStr = helper->getStringByKeyDef( inWhat );

  QString result = Wrap( inWhatStr, what );

  return result;
}

QString xmlHelper::getStringByBoolean( bool val )
{
  xmlHelper * helper = xmlHelper::Instance();
  if( val )
    return QString(helper->getStringByKeyDef(True));

  return QString(helper->getStringByKeyDef(False));
}
QString xmlHelper::getStringByInteger( int val )
{
  return QString::number( val );
}

///////////////////////////////////////////////////////////////////////////

xmlReader::xmlReader( plist * plst):
pplist( plst ),
  isArray( false ),
  pcell( NULL )
{
}

bool xmlReader::startElement(
  const QString &namespaceURI, 
  const QString &localName, 
  const QString &qName, 
  const QXmlAttributes &attributes )
{
  xmlHelper * help = xmlHelper::Instance();
  keyValues val = help->getKeyDefByString( qName );

  switch( val )
  {
  case Array:
    isArray = true;
    break;
  case Dict:
    if( isArray )
      pcell = new cell(-1);
    break;
  }

  currentText.clear();

  return true;
}

bool xmlReader::endElement( 
  const QString& namespaceURI, 
  const QString& localName, 
  const QString& qName )
{
  xmlHelper * help = xmlHelper::Instance();
  keyValues val = help->getKeyDefByString( currentText );

  switch( val )
  {

  case unknown:
    break;
  default:   
    lastKey = val;
  }

  val = help->getKeyDefByString( qName );

  if( isArray )
  {
    switch( val )
    {
    case True:
      lastVal = val;
      setValueByLastKey( lastKey );
      break;
    case False:
      //doNothing
      break;
    case Integer:
      lastVal = val;
      setValueByLastKey( lastKey );
      break;
    case Array:
      isArray = false;
      break;
    case Dict:
      pplist->addItem( pcell );
      pcell = NULL;
      break;
      //case unknown:
      //case True:
      //case False:
      //  break;

    }
  }
  //  QMessageBox::information(NULL, "text" , currentText + " " + QString::number((int)val), QMessageBox::Ok);

  return true;
}

bool xmlReader::characters( const QString& ch )
{
  currentText += ch;
  return true;
}

bool xmlReader::fatalError( const QXmlParseException &xcptn )
{


  return true;
}

bool xmlReader::setValueByLastKey( keyValues val )
{
  if( !pcell )
    return true;
  switch( val )
  {
  case active:
    pcell->hextype = s_active;
    break;
  case block:
    pcell->hextype = s_block;
    break;
  case bomb:
    pcell->timer = currentText.toInt();
    if( pcell->timer >= 0 )
      pcell->hextype = s_bomb;
    break;
  case bunny:
    pcell->hextype = s_bunny;
    break;
  case fire:
    pcell->hextype = s_fire;
    break;
  case monster:
    pcell->hextype = s_monster;
    break;
  case number:
    pcell->index = currentText.toInt();
    break;
  case strong:
    pcell->hextype = s_strong;
    break;
  case teleport:
    pcell->hextype = s_teleport;
    break;
  case visible:
    if( lastVal == True )
      pcell->isVisible = true;
    else if( lastVal == False )
      pcell->isVisible = false;
    break;
    //  case parametres:
    //  case horizontalNumber:
    //  case verticalNumber:
    //    break;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////

xmlWriter::xmlWriter( plist * lst, QString filename ):
  pplist( lst ),
  out( NULL )
{
  file = new QFile(filename);
}

xmlWriter::~xmlWriter()
{
  delete file;
  if( out )
    delete out;
}

bool xmlWriter::SaveFile()
{

  file->open(QIODevice::WriteOnly | QIODevice::Text);
  out = new QTextStream( file );
  out->setCodec("UTF-8");
  int level = 0;
  StreamWrite( out, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
  StreamWrite( out, "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" );

  pplist->Serialize( out, level );

  file->close();

  return true;
}