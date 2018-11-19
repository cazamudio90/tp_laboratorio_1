#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int i;
    if(this != NULL && ll_len(this) > 0 && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        pNode = this->pFirstNode;
        for(i=0;i<nodeIndex;i++)
        {
            pNode = pNode->pNextNode;
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    if(this != NULL && nodeIndex >=0 && nodeIndex <= ll_len(this))
    {
       Node* newNode = malloc(sizeof(Node));
       if(ll_len(this)==0  && nodeIndex == 0)
       {
            newNode->pElement = pElement;
            newNode->pNextNode=NULL;
            this->pFirstNode = newNode;


       }else if(ll_len(this)>0  && nodeIndex == 0)
       {
             newNode->pElement = pElement;
             newNode->pNextNode = this->pFirstNode;
             this->pFirstNode = newNode;

       }
       else if(ll_len(this) > 0  && nodeIndex > 0 && nodeIndex == ll_len(this))
       {
            newNode->pElement =pElement;
            newNode->pNextNode = NULL;
            getNode(this,nodeIndex-1)->pNextNode = newNode;
       }else if(ll_len(this) > 0  && nodeIndex < ll_len(this))
       {
            newNode->pElement = pElement;
            newNode->pNextNode = getNode(this,nodeIndex);
            getNode(this,nodeIndex-1)->pNextNode = newNode;
       }
        this->size += 1;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && ll_len(this)>= 0)
    {
        if (addNode(this,ll_len(this), pElement)==0)
        {
            returnAux = 0;
        }

    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode;
    if(this != NULL && index >= 0 && ll_len(this) >= 0 && index < ll_len(this))
    {
       auxNode = getNode(this,index);
       returnAux = auxNode->pElement;
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node * auxNode = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        auxNode = getNode(this,index);
        if(auxNode != NULL)
        {
            auxNode->pElement = pElement;
        }
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* auxNode;
    if(this!=NULL && index >= 0 && index < ll_len(this) && ll_len(this) >=0)
    {
       auxNode = getNode(this, index);
       if( index == 0)
       {
           this->pFirstNode = auxNode->pNextNode;
       }else if(index >0 && index != (ll_len(this)-1))
       {
           getNode(this, index -1)->pNextNode = auxNode->pNextNode;
       }else if (index >0 && index == (ll_len(this)-1))
       {
           getNode(this,index-1)->pNextNode=NULL;
       }
        this->size=(this->size)-1;
        free(auxNode);
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    Node* auxNode = NULL;
    int i = 0;
    if(this != NULL && ll_len(this)>0)
    {
        for(i=0; i< ll_len(this); i++)
        {
            auxNode = getNode(this,i);
            if (auxNode != NULL)
            {
                ll_remove(this,i);
            }
        }
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    Node* auxNode = NULL;
    int i = 0;
    if(this != NULL && ll_len(this)>0)
    {
        for(i=0; i< ll_len(this); i++)
        {
            auxNode = getNode(this,i);
            if (auxNode != NULL)
            {
                ll_remove(this,i);
            }
        }
        free(this);
        returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* auxNode = NULL;
    int i = 0;
    if(this != NULL && ll_len(this)>0)
    {
        for(i=0; i< ll_len(this); i++)
        {
            auxNode = getNode(this,i);
            if (auxNode->pElement == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL && this->size ==0)
    {
        returnAux=1;
    }
    else if (this != NULL && this->size >0)
    {
        returnAux=0;
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <=ll_len(this))
    {
        addNode(this, index, pElement);
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        returnAux = getNode(this,index)->pElement;
        ll_remove(this,index);
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if( ll_indexOf(this, pElement)> -1)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    int contador=0;
    Node * auxNode = NULL;
    if(this != NULL && this2 != NULL)
    {

        auxNode = this2->pFirstNode;
        for(i=0; i< ll_len(this2); i++)
        {
            if(ll_contains(this,auxNode->pElement)== 1)
            {
                contador++;
            }
             auxNode = auxNode->pNextNode;
        }
        if (contador==ll_len(this2))
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL && from >= 0 && to > from && to <= ll_len(this))
    {
        cloneArray = ll_newLinkedList();
        while(from<= to)
        {
            ll_add(cloneArray,ll_get(this, from));
            from++;
        }
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int i;
    if(this != NULL)
    {
        cloneArray = ll_newLinkedList();
        for(i=0; i< ll_len(this); i++)
        {
            addNode(cloneArray,i,getNode(this,i)->pElement);
        }
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int j;
    Node * auxNode1;
    Node * auxNode2;
    void* element1;
    void* element2;
    int flagNoEstaOrdenado = 1;
    if(this !=  NULL && pFunc!= NULL && (order == 0 || order == 1))
    {
        while (flagNoEstaOrdenado==1)
         {
            flagNoEstaOrdenado = 0;
            for (j = 1; j < ll_len(this); j++)
            {
                auxNode1 = getNode(this,j);
                auxNode2 = getNode(this, j-1);
                element1 = ll_get(this,j);
                element2 = ll_get(this, j - 1);
                if ( order== 1 && pFunc(element1, element2)== -1)
                {
                     auxNode1->pElement = element2;
                     auxNode2->pElement = element1;

                     flagNoEstaOrdenado = 1;
                }else if(order== 0 && pFunc(element1, element2)== 1)
                {
                     auxNode1->pElement = element2;
                     auxNode2->pElement = element1;
                     flagNoEstaOrdenado = 1;
                }
            }
         }
         returnAux = 0;
    }
    return returnAux;

}

/** \brief Filtra los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return  Retorna  (-1) Error: si el puntero a la listas es NULL
                                linkenlist Si ok
 */

 LinkedList * ll_filter(LinkedList* this, int (*pFunc)(void*))
 {
    LinkedList* returnAux = NULL;
    LinkedList * listFilter;
    void * element1;
    int i;
    if(this != NULL && pFunc != NULL)
    {
       listFilter = ll_newLinkedList();
       for(i=0; i< ll_len(this); i++)
       {
            element1 = ll_get(this,i);
            if (pFunc(element1)== 1)
            {
                ll_add(listFilter,element1);
            }
        }
        returnAux =  listFilter;
    }
    return returnAux;
 }

 /** \brief le pasa un a una funcion un cada elemento de la lista como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return  Retorna  (-1) Error: si el puntero a la listas es NULL
                                (0) Si ok
 */
int ll_map(LinkedList * this,  int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;
    void * element1;
    if(this != NULL && pFunc != NULL)
    {
        for ( i= 0; i < ll_len(this); i++)
        {
            element1 = ll_get(this,i);
            if(pFunc(element1)== 0)
            {
                returnAux = 0;
            }
        }
    }
    return returnAux;
}
