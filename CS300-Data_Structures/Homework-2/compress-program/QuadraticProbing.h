#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int nextPrime( int n );


template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }
    
    
    bool containss( const HashedObj & x ) const
    {
        return isActive(findPos( x )) ;
    }
    
    int contains( const HashedObj & x ) const
    {
        return findPos( x ) ;
    }
    
    int isIndexActive(int code){
        if (array[code].info ==ACTIVE){
            return 1;
        }
        return 0;
    }
    
    string stringInIndex(int code){
        if (isIndexActive(code)){
            return array[code].element;
        }
        return "";
    }
    

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;
        
        array[ currentPos ].code = findPos(x);


        return true;
        
        
    }
    
    bool insert( HashedObj && x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;


        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }
    bool  operator==( const HashedObj & rhs );
    bool  operator!=( const HashedObj & rhs );

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        int code;
        
        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
        
//        bool operator==( const HashedObj & rhs){
//            if(rhs.element == *this.element)
//                return true;
//            return false;
//        }
//
//        bool operator!=( const HashedObj & rhs){
//             if(rhs.element != *this.element)
//                 return true;
//            return false;
//        }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        int i = 0;
        while( array[ i ].info != EMPTY && array[ i ].element != x ) {
            i++;
        }
        return i;
    }

};

#endif
