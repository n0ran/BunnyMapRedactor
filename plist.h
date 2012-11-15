#ifndef __PLIST_H__
#define __PLIST_H__
#pragma once
#include <map>
#include "helper.h"
#include <QPushButton>
#include <QtXml/QXmlDefaultHandler>
#include <QMainWindow>
#include <QFile>
using std::map;

class cell
{
public:
  cell( int ind, state htype = s_original, state unt = s_original, int tmr = -1, bool vsbl = true );
  ~cell();

  void setState( state ht );
  void UpdateView();
  void initButton( QMainWindow * mWnd );
  bool Serialize( QTextStream * out, int &level );
public:
  state hextype;
	state unit;
  int   timer;
  int   index;
  bool  isVisible;

  QPushButton * button;
};

class parametres
{
public:
  parametres();
  bool Serialize( QTextStream * out, int &level );
	void SetHorizontalNumber( int n );
	void SetVerticalNumber( int n );
public:
  int horizontalNumber;
  int verticalNumber;
};

;

class plist
{
public:
  plist( int w = 9, int h = 5 );
  ~plist(void);

  void initArray( QMainWindow * mWnd = NULL );
  void initArray( QMainWindow * mWnd, QString &filename );
  cell * getItem( int index );
  void addItem( cell * pcell );
  int GetButtonIndex( QPushButton * button );
  bool Serialize( QTextStream * out, int &level );
  bool SaveInFile( QString filename );
	int	GetWidth();
	int GetHeight();
	void SetWidth( int w );
	void SetHeight( int h );
  void clear();
private:
  map< int, cell* > arr;
  parametres params;
};

#endif