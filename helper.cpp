#include "helper.h"
#include <vector>
#include <QByteArray>
using std::vector;

Helper::Helper()
{
    InitItemNamesVector ();
}

Helper::~Helper ()
{
    if( ItemNames )
        delete ItemNames;
}

Helper* Helper::_instance = NULL;

int Helper::vnumber = 5;
int Helper::hnumber = 9;

Helper* Helper::Instance ()
{
    if( _instance == NULL )
    {
        _instance = new Helper;
    }
    return _instance;
}

state Helper::GetStateByItemName( QString & itemName )
{               
         if ( itemName ==  "original"      ) return s_original;
    else if ( itemName ==  "bunny"         ) return s_bunny;
    else if ( itemName ==  "active"        ) return s_active;
    else if ( itemName ==  "hex_dynamite"  ) return s_bomb;
    else if ( itemName ==  "hex_fire"      ) return s_fire;
    else if ( itemName ==  "hex_stone"     ) return s_block;
    else if ( itemName ==  "hex_strong"    ) return s_strong;
    else if ( itemName ==  "hex_teleport"  ) return s_teleport;
    else if ( itemName ==  "monster"       ) return s_monster;
		else if ( itemName ==  "invisible"		 ) return s_invisible;
  return s_original;
}

QString& Helper::GetItemNameByState( state st )
{
  switch ( st )
  {
  case s_original : return (*ItemNames)[0];
  case s_bunny    : return (*ItemNames)[1];
  case s_active   : return (*ItemNames)[2];
  case s_bomb     : return (*ItemNames)[3];
  case s_fire     : return (*ItemNames)[4];
  case s_block    : return (*ItemNames)[5];
  case s_strong   : return (*ItemNames)[6];
  case s_teleport : return (*ItemNames)[7];
  case s_monster  : return (*ItemNames)[8];
	case s_invisible	: return (*ItemNames)[9];
  }
  return (*ItemNames)[0];
  }
  QString& Helper::GetItemNameByVisible( bool v, state st )
  {
  if( v )
    return GetItemNameByState( st );
  else
    return (*ItemNames)[9];
}

void Helper::TBInitSequence( std::map< int, vector< state > > & sequence )
{
	sequence.clear();
	sequence[0].push_back( s_original );
	sequence[0].push_back( s_bomb );
	sequence[0].push_back( s_fire );
	sequence[0].push_back( s_block );
	sequence[0].push_back( s_strong );
	sequence[0].push_back( s_teleport );
	sequence[1].push_back( s_active );
	sequence[1].push_back( s_bunny );
	sequence[1].push_back( s_monster );
	sequence[2].push_back( s_invisible );
}

void Helper::InitItemNamesVector ()
{
    ItemNames = new NamesVector;

    ItemNames->push_back ( QString( "original"      ) );
    ItemNames->push_back ( QString( "bunny"         ) );
    ItemNames->push_back ( QString( "active"        ) );
    ItemNames->push_back ( QString( "hex_dynamite"  ) );
    ItemNames->push_back ( QString( "hex_fire"      ) );
    ItemNames->push_back ( QString( "hex_stone"     ) );
    ItemNames->push_back ( QString( "hex_strong"    ) );
    ItemNames->push_back ( QString( "hex_teleport"  ) );
    ItemNames->push_back ( QString( "monster"       ) );
    ItemNames->push_back ( QString( "invisible"     ) );
}

pNamesVector Helper::GetItemNames ()
{
    return ItemNames;
}
