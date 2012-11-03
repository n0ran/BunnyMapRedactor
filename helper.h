#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <vector>
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
  s_teleport  };
class Helper
{
public:
    static Helper* Instance();
    ~Helper();

    state GetStateByItemName( QString & itemName );
    QString& GetItemNameByState( state st );
    QString& GetItemNameByVisible( bool v, state st );
    pNamesVector GetItemNames();

protected:
    Helper();
    void InitItemNamesVector();
private:
    static Helper* _instance;
    
    pNamesVector ItemNames;
};

#endif // HELPER_H
