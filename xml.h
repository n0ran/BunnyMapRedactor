#ifndef _XML_PARSER_H__
#define _XML_PARSER_H__

#include <QtCore/QFile>
#include <QtXml/QXmlInputSource>
#include <map>
#include "plist.h"

#define oTag( KEY ) "<" + KEY + ">"
#define cTag( KEY ) "</" + KEY + ">"
#define ocTag( KEY ) "<" + KEY + "/>"
#define Wrap( KEY, VALUE ) oTag( KEY ) + VALUE + cTag( KEY )
#define StreamWrite( out, val ) *out << xmlHelper::getTabByLevel(level) << val << "\n";
#define StreamWriteLevUp( out, val ) StreamWrite( out, val ) level++;
#define StreamWriteLevDown( out, val ) level--; StreamWrite( out, val ) 


enum keyValues {
  kv_True  = 0,
  kv_False,
  kv_Integer,
  kv_hexs  = 10,
  kv_active,
  kv_block,
  kv_bomb,
  kv_bunny,
  kv_fire,
  kv_monster,
  kv_number,
  kv_strong,
  kv_teleport,
  kv_visible,
  kv_parametres = 30,
	kv_steps,
  kv_horizontalNumber,
  kv_verticalNumber,
  kv_Dict = 40,
  kv_Array,
  kv_key = 50,
  kv_unknown = 999
};
class xmlHelper
{
public:
  static xmlHelper* Instance();
  ~xmlHelper();
  keyValues getKeyDefByString( const QString & str );
  QString getStringByKeyDef( keyValues val );

  static QString getTabByLevel( int level );
  static QString wrapKeyValInKeyVal( keyValues inWhat, keyValues what );                 
  static QString wrapStringInKeyVal( keyValues inWhat, QString what );                 
  static QString getStringByBoolean( bool val );
  static QString getStringByInteger( int val );
private:
  xmlHelper();
  void initDictionary();
  static xmlHelper* _instance;
  map< keyValues, QString* > keyDictionary; 
};

class xmlReader : public QXmlDefaultHandler
{
public:
  xmlReader( CPlist * lst );

  virtual bool startElement( 
    const QString &namespaceURI,
    const QString &localName,
    const QString &qName,
    const QXmlAttributes &attributes );

  virtual bool endElement(
    const QString& namespaceURI,
    const QString& localName,
    const QString& qName );

  virtual bool characters( const QString& ch );

  virtual bool fatalError( const QXmlParseException &xcptn );

  virtual bool setValueByLastKey( keyValues val );

	virtual bool setParamsValues( keyValues val );
private:
  QString currentText;
  keyValues lastKey;
  keyValues lastVal;
  CPlist * pplist;
  bool isArray;
  CCell  * pcell;
};

class xmlWriter 
{
public:
  xmlWriter( CPlist * lst, QString filename );
  ~xmlWriter();
  bool SaveFile();

private:
  QFile * file;
  QTextStream * out;
  CPlist * pplist;
};

#endif //_XML_PARSER_H__


