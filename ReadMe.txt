//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//  filename:       ReadMe.txt
//  org. location:  http://www.riccardo-riedl.de/content/source/CdlList/ReadMe.txt
//  last update:    06-16-2004
//
//  author:         riccardo riedl
//  contact:        http://www.riccardo-riedl.de/mail.php
//
//  description:    documenation to the c++ template class 'CdlList'
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

=========================
DL_POSITION
=========================

     Type to denote the position of an element in the list for iterating or
     bookmarking.


=========================
template <class DATATYPE>
class CdlList
=========================

    Parameters:
    ===========

        DATATYPE

            Type of the objects to be stored in the list.
            The type doesn't need to have any operators, but a
            standard constuctor.

    data members:
    =============

          type            name         describtion
        +---------------+------------+--------------------------------------+
        | CdlNode*      | m_pFirst   | Pointer to the first Element.        |
        +---------------+------------+--------------------------------------+ 
        | CdlNode*      | m_pLast    | Pointer to the last Element.         |
        +---------------+------------+--------------------------------------+
        | unsigned long | m_nCounter | Number of Elements in the List.      |
        +---------------+------------+--------------------------------------+

    Construction:
    =============

          return value   function / describtion
        +--------------+----------------------------------------------------+
        |              | CdlList(void)                                      |
        |              | Creates an empty list.                             |
        +--------------+----------------------------------------------------+

    Adding Elements:
    ================

          return value   function / describtion
        +--------------+----------------------------------------------------+
        | DL_POSITION  | AddFirst (const DATATYPE&)                         |
        |              | Adds a new element to the start of the list.       |
        |              | Returns the new elements position.                 |
        +--------------+----------------------------------------------------+
        | DL_POSITION  | AddLast  (const DATATYPE&)                         |
        |              | Adds a new element to the end of the list          |
        |              | Returns the new elements position.                 |
        +--------------+----------------------------------------------------+
        | DL_POSITION  | AddAfter (const DATATYPE&, const DL_POSITION)      |
        |              | Adds a new element after the given position        |
        |              | Returns the new elements position of DL_NULL       |
        |              | when the DL_POSITION parameter was invalid.        |
        +--------------+----------------------------------------------------+
        | DL_POSITION  | AddBefore(const DATATYPE&, const DL_POSITION)      |
        |              | Adds a new element in front of the given position  |
        |              | Returns the new elements position of DL_NULL       |
        |              | when the DL_POSITION parameter was invalid.        |
        +--------------+----------------------------------------------------+


    Iteration:
    ==========

          return value   function / describtion
        +--------------+----------------------------------------------------+
        | DL_POSITION  | GetFirstPosition (void)                            |
        |              | Returns the position of the first element.         |
        +--------------+----------------------------------------------------+
        | DL_POSITION  | GetLastPosition (void)                             |
        |              | Returns the position of the last element.          |
        +--------------+----------------------------------------------------+
        | DL_POSITION  | GetNextPosition (const DL_POSITION)                |
        |              | Returns the position next to the given one.        |
        |              | Retruns 0 when the given position points to the    |
        |              | last Element, or when the list is empty.           |
        +--------------+----------------------------------------------------+
        | DL_POSITION  | GetPreviousPosition (const DL_POSITION)            |
        |              | Returns the position previous to the given one.    |
        |              | Retruns 0 when the given position points to the    |
        |              | first Element, or when the list is empty.          |
        +--------------+----------------------------------------------------+
        

    Setting the data:
    =================

          return value   function / describtion
        +--------------+----------------------------------------------------+
        | bool         | SetFirst (const DATATYPE&)                         |
        |              | Sets the data for the first Node in the list.      |
        |              | Returns false, if the list is empty.               |
        +--------------+----------------------------------------------------+
        | bool         | SetLast (const DATATYPE&)                          |
        |              | Sets the data for the last Node in the list.       |
        |              | Returns false, if the list is empty.               |
        +--------------+----------------------------------------------------+
        | bool         | SetAt (const DATATYPE&, const DL_POSITION)         |
        |              | Sets the data for a Node at a given position.      |
        |              | Returns false, if the List is empty, or when the   |
        |              | given position is not valid.                       |
        +--------------+----------------------------------------------------+
    
    
    Getting the data:
    =================
    
          return value   function / describtion
        +--------------+----------------------------------------------------+
        | bool         | GetFirst (DATATYPE&)                               |
        |              | Gets the first nodes data.                         |
        |              | It MUST be verified, that the List is not empty(*).|
        +--------------+----------------------------------------------------+
        | bool         | GetLast (DATATYPE&)                                |
        |              | Gets the first nodes data.                         |
        |              | It MUST be verified, that the List is not empty(*).|
        +--------------+----------------------------------------------------+
        | bool         | GetAt (DATATYPE&, const DL_POSITION)               |
        |              | Gets the data at a given position data.            |
        |              | It MUST be verified, that the List is not empty    |
        |              | and that the parameter points to a valid           |
        |              | position(*).                                       |
        +--------------+----------------------------------------------------+
                        (*) If the list is empty of the position parameter
                            is invalid, a dummy value will be returned.


    Deleting Elements:
    ==================
    
          return value   function / describtion
        +--------------+----------------------------------------------------+
        | bool         | DeleteFirst (void)                                 |
        |              | Deletes the first Node from the List.              |
        |              | Returns false when the list is empty.              |
        +--------------+----------------------------------------------------+
        | bool         | DeleteLast (void)                                  |
        |              | Deletes the last Node from the List.               |
        |              | Returns false when the list is empty.              |
        +--------------+----------------------------------------------------+
        | bool         | DeleteAt (const DL_POSITION)                       |
        |              | Deletes a Node at a given position from the List.  |
        |              | Returns false, when the list is empty or the given |
        |              | position is not valid.                             |
        +--------------+----------------------------------------------------+
        | void         | DeleteAll (void)                                   |
        |              | Deletes all nodes from the list.                   |
        +--------------+----------------------------------------------------+
        

    Query:
    ======
    
          return value   function / describtion
        +--------------+----------------------------------------------------+
        | unsigned long| GetCount(void) const                               |
        |              | Returns the number of elements in the list.        |
        +--------------+----------------------------------------------------+
        | bool         | IsEmpty(void) const                                |
        |              | Returns true, when the list is empty.              |
        +--------------+----------------------------------------------------+


    Verification (Debug):
    =====================

        Remark:
        -------
 
        This methode will only be effective in debug mode. It might iterate
        through the whole list, so it would slow down to much in release.

          return value   function / describtion
        +--------------+----------------------------------------------------+
        | bool         | IsValidPosition (const DL_POSITION position)       |
        |              | Verifies, if a given position is valid.            |
        +--------------+----------------------------------------------------+
        
