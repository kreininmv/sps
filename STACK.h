/* FILE NAME   : STACK.h
 * PURPOSE     : Header module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 29.09.2020.
 * NOTE        : None.
 */
namespace mk5 //IFK namespace
{
  template < typename type_data >
  /* Structure of stack */
  struct stack
  {
    type_data *data;
    size_t count;
    size_t size;
  };
}

template < typename type_data >
/*! Init part of reallocated memory function.
  * \param[in]  poin to the part of stack             - mk5::stack* thou;
  * \param[in]  size of part stack for initialization - int size;
  * \param[out] none.
  */
void StackPartInit(mk5::stack<type_data>* thou);

template < typename type_data >
/*! Reallocated memory of stack function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[out] none.
 */
int StackRealloc(mk5::stack<type_data>* thou);

template < typename type_data>
/*! Delete and return last element of stack function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[out] last element.
 */
type_data StackPop(mk5::stack<type_data>* thou);

template < typename type_data>
/*! Add element to stack function.
 * \param[in]  point to stack        - mk5::stack* thou;
 * \param[in]  value to add to stack - double value;
 * \param[out] none.
 */
void StackPush(mk5::stack<type_data>* thou, type_data value);

template < typename type_data>
/*! Deinitialization of stakc function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[out] none.
 */
void StackDestruct(mk5::stack<type_data> *thou);

template < typename type_data >
/*! Initialization of stack function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[in]  size of stack  - size_t size;
 * \param[out] none.
 */
int StackConstruct(mk5::stack<type_data> *thou, size_t size);
