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

class CCell
{
public:
  CCell( int ind, state htype = s_original, state unt = s_original, int tmr = -1, bool vsbl = true );
  ~CCell();

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

class CParametres
{
public:
  CParametres();
  bool Serialize( QTextStream * out, int &level );
	void SetHorizontalNumber( int n );
	void SetVerticalNumber( int n );
	void SetSteps( int n );
public:
  int _horizontalNumber;
  int _verticalNumber;
	int _steps;
};

;

class CPlist
{
public:
  CPlist( int w = 9, int h = 5 );
  ~CPlist(void);

  void initArray( QMainWindow * mWnd = NULL );
  void initArray( QMainWindow * mWnd, QString &filename );
  CCell * getItem( int index );
  void addItem( CCell * pcell );
  int GetButtonIndex( QPushButton * button );
  bool Serialize( QTextStream * out, int &level );
  bool SaveInFile( QString filename );
	int	GetWidth();
	int GetHeight();
	int GetSteps();
	void SetWidth( int w );
	void SetHeight( int h );
	void SetSteps( int s );
  void clear();
private:
  map< int, CCell* > arr;
  CParametres params;
};

#endif