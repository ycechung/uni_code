#include "rtx.h"
#include "pcb.h"
#include "process.h"

using namespace rtx_stl;

////////////////
// PCB FUNCTIONS
////////////////

PCB::PCB( Process * pProcess ) : m_id( pProcess->process().id ),
								 m_model( pProcess )//,
								 //m_envelope_inbox( new queue <MsgEnv> )
{

}

PCB::~PCB()
{

}

/////////////////
// UPCB FUNCTIONS
/////////////////

UPCB::UPCB( Process * pProcess ) : PCB( pProcess ),
								   m_priority( pProcess->process().priority ),
								   m_status( READY )
{
	m_stack = ( byte * ) malloc( PROCESS_STACK_SIZE ) + PROCESS_STACK_SIZE - 4;
}

UPCB::~UPCB()
{
	delete m_stack;
}

/////////////////
// IPCB FUNCTIONS
/////////////////

IPCB::IPCB( Process * pProcess ) : PCB( pProcess ),
								   m_signals_handled( pProcess->process().signals_handled )
{

}

IPCB::~IPCB()
{

}
