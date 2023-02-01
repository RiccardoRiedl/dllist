//=============================================================================
//
//  Copyright (c) 2004. Riccardo Riedl (www.riccardo-riedl.de)
//
//  Permission to use, copy, modify, distribute and sell this software and its
//  documentation for any purpose is hereby granted without fee, provided that
//  the above copyright notice appears in all copies and that both that
//  copyright notice and this permission notice appear in supporting
//  documentation.
//
//  There are no representations made about the suitability of this software
//  for any purpose. It is provided "as is" without expressed or implied
//  warranty.
//
//=============================================================================


//=============================================================================
//  preprocessor directives
//=============================================================================

//  include this file only once
//
#ifndef DL_CDOUBLELINKEDLIST_INCLUDED__
#define DL_CDOUBLELINKEDLIST_INCLUDED__

//  header file for memmove()
//
#include <string.h>

//  symbol for null-pointer
//
#define DL_NULL ( static_cast< CdlNode<DATATYPE>* >( 0 ) )


//=============================================================================
//  DL_POSITION type definition
//
//  description:    void pointer type to traverse a list sequentially
//                  and as a bookmark to hold the place of an element
//=============================================================================

typedef struct _DL_POSITION_
{
    ;
}
* DL_POSITION;


//=============================================================================
//  CdlNode template class
//
//  description:    The CdlNode template class is the container for elements
//                  of the list
//=============================================================================

//  forward decleration of the CdlList template class,
//  so that it can be declared as friend in CdlNode
//
template <class DATATYPE> class CdlList;


//=============================================================================
//  class decleration
//-----------------------------------------------------------------------------

template <class DATATYPE> class CdlNode
{

    friend class CdlList<DATATYPE>;


    //-------------------------------------------------------------------------
    //  data members
    //-------------------------------------------------------------------------

private:

    //  pointers to the previous and the next
    //  node to link one element to another
    //
    CdlNode *m_pPrev;   //  if DL_NULL this is the last node in the list
    CdlNode *m_pNext;   //  if DL_NULL this is the first node in the list

    //  the data object to be stored in this node
    //
    DATATYPE m_data;

    
    //-------------------------------------------------------------------------
    //  methodes
    //-------------------------------------------------------------------------

private:

    //  the constructor
    //
    CdlNode(const DATATYPE& data);

    //  queries to test if an element is
    //  the first or last one in a list
    //
    inline bool IsLast(void)  const;
    inline bool IsFirst(void) const;

};


//=============================================================================
//  definitions
//-----------------------------------------------------------------------------

//  the constructor initializes the pointers and copies the
//  content of the passed element into the objects data member
//
template <class DATATYPE> CdlNode<DATATYPE>::CdlNode(const DATATYPE& data)
    : m_pPrev (DL_NULL)
    , m_pNext (DL_NULL)
{
    //  copy the data to the elements member
    //
    memmove( &m_data, &data, sizeof(DATATYPE) );
}

//  those members are supposed to make the CdlList implementation
//  more readable. they return true, if the node is either the
//  last or the first element of a list.
//
template <class DATATYPE> bool CdlNode<DATATYPE>::IsLast(void) const
{
    return ( static_cast<bool>(DL_NULL == m_pPrev) );
}

template <class DATATYPE> bool CdlNode<DATATYPE>::IsFirst(void) const
{
    return ( static_cast<bool>(DL_NULL == m_pNext) );
}



//=============================================================================
//  CdlList template class
//
//  description:    simple generic doubly-linked list supporting nonunique
//                  objects accessible sequentially.
//=============================================================================


//=============================================================================
//  class decleration
//-----------------------------------------------------------------------------

template <class DATATYPE> class CdlList
{

    //-------------------------------------------------------------------------
    //  data members
    //-------------------------------------------------------------------------

private:

    CdlNode<DATATYPE>* m_pFirst; //  link to the first node (DL_NULL if list empty)
    CdlNode<DATATYPE>* m_pLast;  //  link to the last node  (DL_NULL if list empty)

    unsigned long m_nCounter;    //  number of elements in the list


    //-------------------------------------------------------------------------
    //  methodes
    //-------------------------------------------------------------------------

public:

    CdlList(void);
    ~CdlList(void);


private:

    //  casting functions
    //
    inline DL_POSITION        PositionFromNode(const CdlNode<DATATYPE>* pNode)    const;
    inline CdlNode<DATATYPE>* NodeFromPosition(const DL_POSITION        position) const;

    
public:

    //  methodes to add new elements to the list. the return-values are the
    //  postition of the new element in the list. AddAfter() and AddBefore()
    //  return DL_NULL on failure (when the 'position' argument is invalid).
    //
    DL_POSITION AddFirst  (const DATATYPE& data);
    DL_POSITION AddLast   (const DATATYPE& data);
    DL_POSITION AddAfter  (const DATATYPE& data, const DL_POSITION position);
    DL_POSITION AddBefore (const DATATYPE& data, const DL_POSITION position);


    //  methodes to get the DL_POSITION value for an element
    //  they return DL_NULL when the list is empty, the last and/or first position in
    //  the list has already been reached or the 'position' argument doesn't
    //  point to a valid node
    //
    DL_POSITION GetFirstPosition    (void);
    DL_POSITION GetLastPosition     (void);
    DL_POSITION GetNextPosition     (const DL_POSITION position);
    DL_POSITION GetPreviousPosition (const DL_POSITION position);


    //  methodes to overwrite the data of an element in the list
    //  they return false when the list is empty or the 'position'
    //  argument doesn't point to a valid node
    //
    bool SetFirst (const DATATYPE& data);
    bool SetLast  (const DATATYPE& data);
    bool SetAt    (const DATATYPE& data, const DL_POSITION position);


    //  methodes to get the data of an element
    //
    bool GetFirst (DATATYPE& rValue);
    bool GetLast  (DATATYPE& rValue);
    bool GetAt    (DATATYPE& rValue, const DL_POSITION position);
    
    
    //  methodes to delete elements from the list
    //  they return false when the list is empty or the 'position' argument
    //  doesn't point to a valid node
    //
    bool DeleteFirst (void);
    bool DeleteLast  (void);
    void DeleteAll   (void);
    bool DeleteAt    (const DL_POSITION position);


    //  queries to retrieve information about the list
    //
    inline unsigned long GetCount(void) const;
    inline bool          IsEmpty (void) const;


    //  verification
    //
    bool IsValidPosition(const DL_POSITION position);
};


//=============================================================================
//  definitions
//-----------------------------------------------------------------------------

//  the constructor initzializes the list as empty
//
template <class DATATYPE> CdlList<DATATYPE>::CdlList(void)
    : m_pFirst   (DL_NULL)
    , m_pLast    (DL_NULL)
    , m_nCounter (0L)
{
    ;   //  intentionally left blank
}


//  the destructor deletes all elements from the list
//
template <class DATATYPE> CdlList<DATATYPE>::~CdlList(void)
{
    DeleteAll();
}


//  creates and adds a new element at the start of the list
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::AddFirst(const DATATYPE& data)
{
    CdlNode<DATATYPE> *pNew = new CdlNode<DATATYPE>(data);
    
    if (DL_NULL != pNew)
    {
        //  when adding a new first node, the original first one will
        //  be the new ones previous node. if the list is empty, it will
        //  be zero, which is okay since the new node simply won't
        //  have a previous one, as it will be the only node in the list
        //
        pNew->m_pPrev = m_pFirst;
        m_pFirst      = pNew;

        //  if the list was not empty, the new first element 
        //  will have to be linked to the original first one
        //  if the list was empty, the first node
        //  will also be the last one
        //
        (DL_NULL != pNew->m_pPrev)
            ? pNew->m_pPrev->m_pNext = pNew
            : m_pLast                = pNew;

        //  update the lists counter
        //
        m_nCounter++;
    }

    //  return the position of the new node or DL_NULL on failure
    //
    return PositionFromNode(pNew);
}


//  creates a new node and appends it to the end of the list
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::AddLast(const DATATYPE& data)
{
    //  create new element
    //
    CdlNode<DATATYPE> *pNew = new CdlNode<DATATYPE>(data);

    if (DL_NULL != pNew)
    {

        //  when adding a new last node, the original last one will
        //  be the new ones next node. if the list is empty, it will
        //  be zero, which is okay since then the new node simply won't
        //  have a next node, as it will be the only node in the list
        //
        pNew->m_pNext = m_pLast;
        m_pLast       = pNew;

        //  if the list was not empty, the new last element 
        //  will have to be linked to the original last one
        //  if the list was empty, the last
        //  node will also be the first one
        //
        (DL_NULL != pNew->m_pNext)
            ? pNew->m_pNext->m_pPrev = pNew
            : m_pFirst               = pNew;

        //  update the list count
        //
        m_nCounter++;
    }

    //  return the position of the new node or DL_NULL on failure
    //
    return PositionFromNode(pNew);
}


//  creates and adds a new element after a given position
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::AddAfter(const DATATYPE& data, const DL_POSITION position)
{
    //  verify, that 'position' points to a valid node
    //
    if (false == IsValidPosition(position))
    {
        return PositionFromNode(DL_NULL);
    }

    //  get a pointer to the node at 'position'
    //
    CdlNode<DATATYPE>* pPosition = NodeFromPosition(position);

    //  if the new node shall be inserted after the
    //  last one, AddLast() can do the job as well
    //
    if (pPosition->IsLast())
    {
        return AddLast(data);
    }

    //  create the new node
    //
    CdlNode<DATATYPE> *pNew = new CdlNode<DATATYPE>(data);

    if (DL_NULL != pNew)
    {

        //  link the new one to the previous one in the list.
        //  it is already verified, that pPosition is not the last node
        //  in the list, so pPosition->m_pPrev is a valid pointer
        //
        pPosition->m_pPrev->m_pNext = pNew;
        pNew->m_pPrev               = pPosition->m_pPrev; 

        //  link it to the node at 'position' as it's previous element
        //
        pPosition->m_pPrev = pNew;
        pNew->m_pNext      = pPosition;

        //  update the number of elements
        //
        m_nCounter++;
    }

    //  return the position of the new node or DL_NULL on failure
    //
    return PositionFromNode(pNew);
}


//  creates a new node and inserts it previous to a given position
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::AddBefore(const DATATYPE& data, const DL_POSITION position)
{
    //  verify, that 'position' points to a valid node
    //
    if (false == IsValidPosition(position))
    {
        return PositionFromNode(DL_NULL);
    }

    //  get a pointer to the node at 'position'
    //
    CdlNode<DATATYPE> *pPosition = NodeFromPosition(position);

    //  if the new node shall be inserted in front of
    //  the first one, AddFirst() can do the job as well
    //
    if (pPosition->IsFirst())
    {
        return AddFirst(data);
    }

    //  create the new node
    //
    CdlNode<DATATYPE> *pNew = new CdlNode<DATATYPE>(data);

    if (DL_NULL != pNew)
    {

        //  link it to the next one in the list
        //  it is already verified, that pPosition is not the first node
        //  in the list, so pPosition->m_pNext is a valid element
        //
        pPosition->m_pNext->m_pPrev = pNew;
        pNew->m_pNext               = pPosition->m_pNext;

        //  link it to the node at 'position' as it's next one
        //
        pPosition->m_pNext = pNew;
        pNew->m_pPrev      = pPosition;

        //  update the number of elements
        //
        m_nCounter++;
    }

    //  return the position of the new node or DL_NULL on failure
    //
    return PositionFromNode(pNew);
}


//  returns a position value for the first element
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::GetFirstPosition(void)
{
    return PositionFromNode(m_pFirst);
}


//  returns a position value for the last element
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::GetLastPosition(void) 
{
    return PositionFromNode(m_pLast);
}


//  returns a position value next to a given one
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::GetNextPosition(const DL_POSITION position)
{
    return (false == IsValidPosition(position))
        ? PositionFromNode(DL_NULL)
        : PositionFromNode((NodeFromPosition(position)->m_pNext));
}


//  returns a position value previous to a given one
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::GetPreviousPosition(const DL_POSITION position)
{
    return (false == IsValidPosition(position))
        ? PositionFromNode(DL_NULL)
        : PositionFromNode((NodeFromPosition(position)->m_pPrev));
}


//  overwrites the data of the first element
//
template <class DATATYPE>
bool CdlList<DATATYPE>::SetFirst(const DATATYPE& data)
{
    return (false == IsEmpty())
        ? memmove(&m_pFirst->m_data, &data, sizeof(DATATYPE)), true
        ; false;
}


//  overwrites the data of the last element
//
template <class DATATYPE>
bool CdlList<DATATYPE>::SetLast(const DATATYPE& data)
{
    return (false == IsEmpty())
        ? memmove(&m_pLast->m_data, &data, sizeof(DATATYPE)), true
        : false;
}


//  overwrites the data of an element given by its position
//
template <class DATATYPE>
bool CdlList<DATATYPE>::SetAt(const DATATYPE& data, const DL_POSITION position)
{
    return (false == IsValidPosition(position))
        ? memmove(&NodeFromPosition(position)->m_data, &data, sizeof(DATATYPE)), true
        : false;
}


//  copies the data of the first element into a given reference
//  returns false when the list is empty
//
template <class DATATYPE>
bool CdlList<DATATYPE>::GetFirst(DATATYPE& rValue)
{
    return (false == IsEmpty())
        ? memmove(&rValue, &m_pFirst->m_data, sizeof(DATATYPE)), true
        : false;
}


//  copies the data of the last element into a given reference
//  returns false when the list is empty
//
template <class DATATYPE>
bool CdlList<DATATYPE>::GetLast(DATATYPE& rValue)
{
    return (false == IsEmpty())
        ? memmove(&rValue, &m_pLast->m_data, sizeof(DATATYPE)), true
        : false;
}


//  copies the data of an element give by its position into a reference
//  returns false when the passed position is invalid
//
template <class DATATYPE>
bool CdlList<DATATYPE>::GetAt(DATATYPE& rValue, const DL_POSITION position)
{
    return (true == IsValidPosition(position))
        ? memmove(&rValue, &NodeFromPosition(position)->m_data, sizeof(DATATYPE)), true
        : false;
}


//  deletes the first node of the list
//  returns false when list is empty
//
template <class DATATYPE>
bool CdlList<DATATYPE>::DeleteFirst(void)
{
    //  temporary save a pointer to the node to delete
    //  this is zero in an empty list
    //
    CdlNode<DATATYPE> *pDelete = m_pFirst;

    switch (GetCount())
    {
    case 0:     //  if the list is empty, return 'false'
                //  returing is important here, because the function would
                //  crash from trying to delete by a null pointer
        return false;
        break;

    case 1:     //  if this was the only node of the list, it'll be empty
                //  after the only node got deleted
        m_pFirst = DL_NULL;
        m_pLast  = DL_NULL;
        break;

    default:    //  make the previous node the new first one
        m_pFirst          = m_pFirst->m_pPrev;
        m_pFirst->m_pNext = DL_NULL;
        break;
    }

    //  the node to delete has been cut out from the list,
    //  so it's safe now to delete it and decrease the counter
    //
    delete pDelete; //  at this stage it must not be empty
    m_nCounter--;

    return true;
}


//  deletes the last node of the list
//  returns false when list is empty
//
template <class DATATYPE>
bool CdlList<DATATYPE>::DeleteLast(void)
{
    //  temporary save a pointer to the node to delete
    //
    CdlNode<DATATYPE> *pDelete = m_pLast;

    switch (GetCount())
    {
    case 0:     //  if the list is empty, return 'false'
                //  returing is important here, because the function would
                //  crash from trying to delete by a null pointer
        return false;
        break;

    case 1:     //  if this was the only node of the list, it'll be empty
                //  after the only node got deleted
        m_pFirst = DL_NULL;
        m_pLast  = DL_NULL;
        break;

    default:    //  make the previous node the new first one
        m_pLast          = m_pLast->m_pNext;
        m_pLast->m_pPrev = DL_NULL;
        break;
    }

    //  the node to delete has been cut out from the list,
    //  so it's safe now to delete it and decrease the counter
    //
    delete pDelete;
    m_nCounter--;

    return true;
}


//  deletes a node given by position from the list
//  returns false when list is empty or on an invalid position
//
template <class DATATYPE>
bool CdlList<DATATYPE>::DeleteAt(const DL_POSITION position)
{
    //  the position must be valid in order to delete the node
    //
    if (false == IsValidPosition(position))
    {
        return false;
    }

    //  temporary save a pointer to the node to delete
    //
    CdlNode<DATATYPE> *pDelete = NodeFromPosition(position);


    //  if this is the first or the last node,
    //  there are already methodes to handle that
    //
    if (pDelete->IsFirst())
    {
        return DeleteFirst();
    }

    else if (pDelete->IsLast())
    {
        return DeleteLast();
    }

    //  at this stage it must not be empty
    //  and must a next and a previous node
    //  but since IsValidPosition is not 100% safe
    //  it must be tested
    //
    if ( DL_NULL == pDelete || DL_NULL == pDelete->m_pNext ||  DL_NULL == pDelete->m_pPrev)
    {
        return false;
    }

    //  the previous and the next of this element have
    //  to get linked togheter in order to cut this one out
    //
    pDelete->m_pNext->m_pPrev = pDelete->m_pPrev;
    pDelete->m_pPrev->m_pNext = pDelete->m_pNext;

    //  it's safe now to delete it and update the list count.
    //
    delete pDelete;
    m_nCounter--;

    return true;
}


//  this needs to be a little bit faster than the rest
//  because it'll be called at least one time (by the destructor)
//  for every object. so the iterator methodes aren't used here
//
template <class DATATYPE>
void CdlList<DATATYPE>::DeleteAll(void)
{
    if (!IsEmpty())
    {
        CdlNode<DATATYPE> *pDelete = m_pFirst;

        while (pDelete->m_pPrev)
        {
            pDelete = pDelete->m_pPrev;
            delete pDelete->m_pNext;
        }

        delete pDelete;

        //  reset the list
        //
        m_pFirst   = DL_NULL;
        m_pLast    = DL_NULL;
        m_nCounter = 0L;
    }
}


//  returns the number of elements in the list
//
template <class DATATYPE>
unsigned long CdlList<DATATYPE>::GetCount(void) const
{
    return m_nCounter;
}


//  returns true when the list is empty
//
template <class DATATYPE>
bool CdlList<DATATYPE>::IsEmpty(void) const
{
    return static_cast<bool>( !GetCount() );
}


//  tests if a position is valid
//
template <class DATATYPE>
bool CdlList<DATATYPE>::IsValidPosition(const DL_POSITION position)
{
    //  if the list is empty, or position is zero, return false
    //
    if ( (true == IsEmpty()) || (PositionFromNode(DL_NULL) == position) )
    {
        return false;
    }

    //  in release mode, there not much to do to verify if 'position'
    //  is valid. it would be to costly to run
    //  through the whole list and compare pointers
    //
    #ifndef _DEBUG

        return true;

    #else

        //  this is looking for the position in the whole list, so this
        //  will take a lot of time, when the list is big
        //
        CdlNode<DATATYPE> *pTest     = NodeFromPosition(position);
        CdlNode<DATATYPE> *pIterator = m_pFirst;

        if ( (DL_NULL == pTest) || (DL_NULL == pIterator) )
        {
            return false;
        }

        while (DL_NULL != pIterator)
        {
            //  when the position was found return true
            //
            if (pIterator == pTest)
            {
                return true;
            }

            pIterator = pIterator->m_pPrev;
        }

        //  the position is not in the list, so its invalid
        //
        return false;

    #endif  //	_DEBUG

}


//  casts an elements pointer to a DL_POSITION pointer
//
template <class DATATYPE>
DL_POSITION CdlList<DATATYPE>::PositionFromNode(const CdlNode<DATATYPE>* pNode) const
{
    return (DL_POSITION)(pNode);
}


//  casts a DL_POSITION pointer to an element pointer
//
template <class DATATYPE>
CdlNode<DATATYPE>* CdlList<DATATYPE>::NodeFromPosition(const DL_POSITION position) const
{
    return (CdlNode<DATATYPE>*)(position);
}

#endif  //  __CDOUBLELINKEDLIST_INCLUDED__

//  end of file