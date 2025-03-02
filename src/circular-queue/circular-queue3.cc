
/**
 * @file circular-queue3.cc
 * @brief The classical FIFO implemantation utilizing a circular buffer
 * technique
 *
 * Implementing a FIFO utilizing a circular buffer technique. For this exercise
 * it is utilizing a fixed buffer size defined as a template parameter.
 *
 * Note that it uses two indixes to indicate the current "slot" for income value
 * and current "slot" for outcome value. See the illustration below:
 *
 * Suppose a BUFFER_SIZE = 5
 *
 * Empty:
 *     Buffer: [ _ ] [ _ ] [ _ ] [ _ ] [ _ ]
 *               ↑
 *              head, tail (Both point to the same empty slot)
 *
 * Note: Since we are defining the condition for "Empty" is head == tail.
 * The condition for "Full" cannot be the same.
 *
 * First insertion:
 *     Buffer: [ 10 ] [ _ ] [ _ ] [ _ ] [ _ ]
 *               ↑      ↑
 *             tail    head
 *
 * More Insertions:
 *     Buffer: [ 10 ] [ 20 ] [ 30 ] [ _ ] [ _ ]
 *               ↑                    ↑
 *             tail                  head
 *
 * After removing two items:
 *     Buffer: [ _ ] [ _ ] [ 30 ] [ _ ] [ _ ]
 *                           ↑      ↑
 *                          tail  head
 *
 * Full:
 *     Buffer: [ 23 ] [ 24 ] [ 30 ] [ 12 ] [ 17 ]
 *                      ↑      ↑
 *                    head   tail
 *
 * Note: We cannot use head == tail as a definition of full buffer
 * since that was used as a definition for empty already.
 * Options to solve this:
 *  A. Use a count variable.
 *    Pros are 1.Explicity tracking 2.Easy to understand
 *    Cons are 1. Requires extra storage. 2. Requires update on every operation
 *  B. Keep One slot empty; Define full as next(head) == tail
 *    Pros are 1. No extra storage needed 2. Simple verification
 *    Cons is that is wastes one slot, reduces the usable capacity by 1.
 *
 * In this implementation, it is using option A (Use count). The Option B
 * was also implemented. @see circular.cc
 *
 */

#include "circular-queue3.h"
