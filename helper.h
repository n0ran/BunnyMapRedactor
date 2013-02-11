#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <vector>
#include <map>
using std::vector;

#define GetVarName(var) #var

typedef vector<QString> * pNamesVector;
typedef vector<QString> NamesVector;

enum state { 
  s_original, 
  s_active, 
  s_block, 
  s_bomb, 
  s_bunny, 
  s_fire, 
  s_monster, 
  s_strong, 
  s_teleport,
	s_invisible
};
class Helper
{
public:
    static Helper* Instance();
    ~Helper();

    state GetStateByItemName( QString & itemName );
    QString& GetItemNameByState( state st );
    QString& GetItemNameByVisible( bool v, state st );
    pNamesVector GetItemNames();
		static void TBInitSequence( std::map< int, vector< state > > & sequence );
		static int vnumber;
		static int hnumber;
protected:
    Helper();
    void InitItemNamesVector();
private:
    static Helper* _instance;
    
    pNamesVector ItemNames;
};

bool GetIndexVector( int vertical, int horizontal, std::vector<long> & indexes );

#endif // HELPER_H
