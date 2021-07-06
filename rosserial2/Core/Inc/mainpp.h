/*
 * mainpp.h
 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */

#ifndef MAINPP_H_
#define MAINPP_H_

#ifdef __cplusplus
extern "C" {
#endif

void roslog();
void rosserial_init(void);
void rosserial_task(void);

#ifdef __cplusplus
}
#endif

#endif /* MAINPP_H_ */
