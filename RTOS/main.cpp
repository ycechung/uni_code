#include "rtx.h"

#include "process_null.h"
#include "process_a.h"
#include "process_b.h"
#include "process_c.h"
#include "process_cci.h"
#include "process_wallclock.h"
#include "process_welcome.h"
#include "i_process_timer.h"
#include "i_process_keyboard.h"
#include "i_process_crt.h"
#include "i_process_terminate.h"

int main()
{
	Kernel::init();

	// Doug 11/26/2010
	//	The welcome process must be registered before
	//	the CCI process. This is done so that the
	//	welcome message is displayed first.
	PROCESS_REGISTER( ProcessNull );
	PROCESS_REGISTER( ProcessA );
	PROCESS_REGISTER( ProcessB );
	PROCESS_REGISTER( ProcessC );
	PROCESS_REGISTER( ProcessWelcome );
	PROCESS_REGISTER( ProcessWallclock );
	PROCESS_REGISTER( ProcessCCI );
	PROCESS_REGISTER( IProcessTimer );
	PROCESS_REGISTER( IProcessKeyboard );
	PROCESS_REGISTER( IProcessCRT );
	PROCESS_REGISTER( IProcessTerminate );
				
	Kernel::run();
}
