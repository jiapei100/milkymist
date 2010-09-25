/*
 * Milkymist VJ SoC (Software)
 * Copyright (C) 2007, 2008, 2009 Sebastien Bourdeauducq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <hw/sysctl.h>
#include <hw/gpio.h>
#include <stdlib.h>
#include <board.h>

static const struct board_desc boards[1] = {
	{
		.id = 0x4D4F4E45, /* MONE */
		.name = "Milkymist One",
		.clk_frequency = 80000000,
		.ethernet_phyadr = 1
	},
};

const struct board_desc *get_board_desc_id(unsigned int id)
{
	unsigned int i;
	
	for(i=0;i<sizeof(boards)/sizeof(boards[0]);i++)
		if(boards[i].id == id)
			return &boards[i];
	return NULL;
}

const struct board_desc *get_board_desc()
{
	return get_board_desc_id(CSR_SYSTEM_ID);
}

int get_pcb_revision()
{
	int r;
	unsigned int io;
	
	io = CSR_GPIO_IN;
	r = 0;
	if(io & GPIO_PCBREV0)
		r |= 0x1;
	if(io & GPIO_PCBREV1)
		r |= 0x2;
	if(io & GPIO_PCBREV2)
		r |= 0x4;
	if(io & GPIO_PCBREV3)
		r |= 0x8;
	return r;
}
