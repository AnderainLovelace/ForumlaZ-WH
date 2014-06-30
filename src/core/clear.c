#include "stdafx.h"
#include "defs.h"

#ifndef ARM9
void
eval_clear(void)
{
	clear_symbols();
	defn();
	push(symbol(NIL));
}
#endif
// clear from application GUI code


void
clear(void)
{
	run("clear");
}
