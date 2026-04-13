/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef vrc_irq_h_
#define vrc_irq_h_

void vrc_irq_init();
//all ready for standard initSet
void vrc_irq_setlatch(uint16_t addr, uint8_t val);
void vrc_irq_setlatchLo(uint16_t addr, uint8_t val);
void vrc_irq_setlatchHi(uint16_t addr, uint8_t val);
void vrc_irq_control(uint16_t addr, uint8_t val);
void vrc_irq_ack(uint16_t addr, uint8_t val);
void vrc_irq_cycle();

#endif
