/* FILE NAME   : T02STACK.cpp
 * PURPOSE     : Main start module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 29.09.2020.
 * NOTE        : None.
 */

//#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <windows.h>

#include "STACK.h"

template < typename type_data >
/*! Init part of reallocated memory function.
  * \param[in]  poin to the part of stack             - mk5::stack* thou;
  * \param[in]  size of part stack for initialization - int size;
  * \param[out] none.
  */
void StackPartInit(mk5::stack<type_data>* thou)
{
  for (int i_el = thou->count; i_el < thou->size; i_el++)
    thou->data[i_el] = 0;
}/* End of 'StackPartInit' function */

template < typename type_data >
/*! Reallocated memory of stack function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[out] none.
 */
int StackRealloc(mk5::stack<type_data>* thou)
{
  if (thou->count >= thou->size)
  {
    thou->size *= 2;
    thou->data = (type_data *)realloc(thou->data, sizeof(type_data) * thou->size);

    if (thou->data == NULL)
      return 0xEF;

    StackPartInit(thou);
    return 1;
  }

  if (4 * thou->count < thou->size)
  {
    thou->size /= 2;
    thou->data = (type_data *)realloc(thou->data, sizeof(type_data) * thou->size);

    if (thou->data == NULL)
      return 0xEF;

    StackPartInit(thou);
    return -1;
  }

  return 0;
}/* End of 'StackRealloc' function */

template < typename type_data>
/*! Delete and return last element of stack function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[out] last element.
 */
type_data StackPop(mk5::stack<type_data>* thou)
{
  assert(thou);

  if (thou->count <= 0)
    return NAN;

  type_data el = thou->data[--thou->count];
  thou->data[thou->count] = 0;
  StackRealloc<type_data>(thou);

  return el;
}/* End of 'StackPop' function */

template < typename type_data>
/*! Add element to stack function.
 * \param[in]  point to stack        - mk5::stack* thou;
 * \param[in]  value to add to stack - double value;
 * \param[out] none.
 */
void StackPush(mk5::stack<type_data>* thou, type_data value)
{
  assert(thou);
  if (thou->count >= thou->size)
    StackRealloc<type_data>(thou);

  thou->data[thou->count++] = value;
}/* End of 'StackPush' function */

template < typename type_data>
/*! Deinitialization of stakc function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[out] none.
 */
void StackDestruct(mk5::stack<type_data> *thou)
{
  assert(thou);

  free(thou->data);
  thou->data = nullptr;
  thou->count = -1;
  thou->size = -1;

}/* End of 'StackDestruct' function */

template < typename type_data>
/*! Initialization of stack function.
 * \param[in]  point to stack - mk5::stack* thou;
 * \param[in]  size of stack  - size_t size;
 * \param[out] none.
 */
int StackConstruct(mk5::stack<type_data> *thou, size_t size)
{
  assert(thou);
  if (thou->size > 0)
    free(thou->data), free(thou);

  thou->data = (type_data *)calloc(size, sizeof(type_data));
  thou->size = size;
  thou->count = 0;

  if (thou->data == NULL)
    return 0;

  return 1;
}/* End of 'StackConstruct' function */

/*! Main function.
* \param[in]  none.
* \param[out] none.
*/
int main(void)
{
  mk5::stack<double> stk = {};

  int i = StackConstruct<double>(&stk, 10);
  
  for (int i_el = 0; i_el < 30; i_el++)
    StackPush<double>(&stk, i_el);
  for (int i_el = 0; i_el < 40; i_el++)
    printf("%d - %f \n", i_el, StackPop<double>(&stk));

  StackDestruct<double>(&stk);

  return 0;
}/* End of 'main' function */