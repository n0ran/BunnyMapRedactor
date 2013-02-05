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
  keyDictionary[kv_True            ] = new QString( "true"             );
  keyDictionary[kv_False           ] = new QString( "false"            );
  keyDictionary[kv_Integer         ] = new QString( "integer"          );
  keyDictionary[kv_hexs            ] = new QString( "hexs"             );
  keyDictionary[kv_active          ] = new QString( "active"           );
  keyDictionary[kv_block           ] = new QString( "block"            );
  keyDictionary[kv_bomb            ] = new QString( "bomb"             );
  keyDictionary[kv_bunny           ] = new QString( "bunny"            );
  keyDictionary[kv_fire            ] = new QString( "fire"             );
  keyDictionary[kv_monster         ] = new QString( "monster"          );
  keyDictionary[kv_number          ] = new QString( "number"           );
  keyDictionary[kv_strong          ] = new QString( "strong"           );
  keyDictionary[kv_teleport        ] = new QString( "teleport"         );
  keyDictionary[kv_visible         ] = new QString( "visible"          );
	keyDictionary[kv_steps						] = new QString( "steps"						);
  keyDictionary[kv_parametres      ] = new QString( "parametres"       );
  keyDictionary[kv_horizontalNumber] = new QString( "horizontalNumber" );
  keyDictionary[kv_verticalNumber  ] = new QString( "verticalNumber"   );
  keyDictionary[kv_Dict            ] = new QString( "dict"             );
  keyDictionary[kv_Array           ] = new QString( "array"            );
  keyDictionary[kv_key             ] = new QString( "key"              );
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
  return kv_unknown;
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
    return QString(helper->getStringByKeyDef(kv_True));

  return QString(helper->getStringByKeyDef(kv_False));
}
QString xmlHelper::getStringByInteger( int val )
{
  return QString::number( val );
}

///////////////////////////////////////////////////////////////////////////

xmlReader::xmlReader( CPlist * plst):
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
  case kv_Array:
    isArray = true;
    break;
  case kv_Dict:
    if( isArray )
      pcell = new CCell(-1);
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

  case kv_unknown:
    break;
  default:   
    lastKey = val;
  }

  val = help->getKeyDefByString( qName );

  if( isArray )
  {
    switch( val )
    {
    case kv_True:
      lastVal = val;
      setValueByLastKey( lastKey );
      break;
    case kv_False:
      //doNothing
      break;
    case kv_Integer:
      lastVal = val;
      setValueByLastKey( lastKey );
      break;
    case kv_Array:
      isArray = false;
      break;
    case kv_Dict:
      pplist->addItem( pcell );
      pcell = NULL;
      break;
      //case unknown:
      //case True:
      //case False:
      //  break;

    }
  }
	else
	{
		switch( val )
		{
		case kv_Integer:
			lastVal = val;
			setParamsValues( lastKey );
			break;
		}
	}

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

bool xmlReader::setParamsValues( keyValues val )
{
	switch( val )
	{
	case kv_verticalNumber:
		pplist->SetHeight( currentText.toInt() );
		break;
	case kv_horizontalNumber:
		pplist->SetWidth( currentText.toInt() );
		break;
	case kv_steps:
		pplist->SetSteps( currentText.toInt() );
	/*default:
		break;*/
	}
	return true;
}

bool xmlReader::setValueByLastKey( keyValues val )
{
  if( !pcell )
    return true;
	state st = s_original;
  switch( val )
  {
  case kv_active:
    pcell->setState( s_active );
    break;
  case kv_block:
    pcell->setState( s_block );
    break;
  case kv_bomb:
    pcell->timer = currentText.toInt();
    if( pcell->timer >= 0 )
      pcell->setState( s_bomb );
    break;
  case kv_bunny:
    pcell->setState( s_bunny );
    break;
  case kv_fire:
    pcell->setState( s_fire );
    break;
  case kv_monster:
    pcell->setState( s_monster );
    break;
  case kv_number:
    pcell->index = currentText.toInt();
    break;
  case kv_strong:
    pcell->setState( s_strong );
    break;
  case kv_teleport:
    pcell->setState( s_teleport );
    break;
  case kv_visible:
    if( lastVal == kv_True )
      pcell->isVisible = true;
    else if( lastVal == kv_False )
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

xmlWriter::xmlWriter( CPlist * lst, QString filename ):
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