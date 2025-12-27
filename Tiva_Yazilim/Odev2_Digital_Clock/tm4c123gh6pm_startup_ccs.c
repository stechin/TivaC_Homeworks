//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio and GNU tools.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the interrupt handler used by the application.
//
//*****************************************************************************
extern void SysTick_Handler(void);

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
static uint32_t pui32Stack[128];

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".intvecs")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)pui32Stack + sizeof(pui32Stack)),
    ResetISR,
    NmiSR,
    FaultISR,
    IntDefaultHandler,               // MPU fault
    IntDefaultHandler,               // Bus fault
    IntDefaultHandler,               // Usage fault
    0, 0, 0, 0,                      // Reserved
    IntDefaultHandler,               // SVCall
    IntDefaultHandler,               // Debug monitor
    0,                               // Reserved
    IntDefaultHandler,               // PendSV
    SysTick_Handler,                 // SysTick interrupt
    // External interrupts (IRQ)
    IntDefaultHandler,               // GPIO Port A
    IntDefaultHandler,               // GPIO Port B
    IntDefaultHandler,               // GPIO Port C
    IntDefaultHandler,               // GPIO Port D
    IntDefaultHandler,               // GPIO Port E
    IntDefaultHandler,               // UART0 Rx and Tx
    IntDefaultHandler,               // UART1 Rx and Tx
    IntDefaultHandler,               // SSI0 Rx and Tx
    IntDefaultHandler,               // I2C0 Master and Slave
    IntDefaultHandler,               // PWM Fault
    IntDefaultHandler,               // PWM Generator 0
    IntDefaultHandler,               // PWM Generator 1
    IntDefaultHandler,               // PWM Generator 2
    IntDefaultHandler,               // Quadrature Encoder 0
    IntDefaultHandler,               // ADC Sequence 0
    IntDefaultHandler,               // ADC Sequence 1
    IntDefaultHandler,               // ADC Sequence 2
    IntDefaultHandler,               // ADC Sequence 3
    IntDefaultHandler,               // Watchdog timer
    IntDefaultHandler,               // Timer 0 subtimer A
    IntDefaultHandler,               // Timer 0 subtimer B
    IntDefaultHandler,               // Timer 1 subtimer A
    IntDefaultHandler,               // Timer 1 subtimer B
    IntDefaultHandler,               // Timer 2 subtimer A
    IntDefaultHandler,               // Timer 2 subtimer B
    IntDefaultHandler,               // Analog Comparator 0
    IntDefaultHandler,               // Analog Comparator 1
    IntDefaultHandler,               // Analog Comparator 2
    IntDefaultHandler,               // System Control (PLL, etc.)
    IntDefaultHandler,               // Flash Control
    IntDefaultHandler,               // GPIO Port F
    IntDefaultHandler,               // GPIO Port G
    IntDefaultHandler,               // GPIO Port H
    IntDefaultHandler,               // UART2 Rx and Tx
    IntDefaultHandler,               // SSI1 Rx and Tx
    IntDefaultHandler,               // Timer 3 subtimer A
    IntDefaultHandler,               // Timer 3 subtimer B
    IntDefaultHandler,               // I2C1 Master and Slave
    IntDefaultHandler,               // CAN0
    IntDefaultHandler,               // CAN1
    0, 0, 0, 0, 0,                   // Reserved
    IntDefaultHandler,               // Hibernate
    IntDefaultHandler,               // USB0
    IntDefaultHandler,               // PWM Generator 3
    IntDefaultHandler,               // uDMA Software Transfer
    IntDefaultHandler,               // uDMA Error
    IntDefaultHandler,               // ADC1 Sequence 0
    IntDefaultHandler,               // ADC1 Sequence 1
    IntDefaultHandler,               // ADC1 Sequence 2
    IntDefaultHandler,               // ADC1 Sequence 3
    0, 0, 0, 0,                      // Reserved
    IntDefaultHandler,               // SSI2 Rx and Tx
    IntDefaultHandler,               // SSI3 Rx and Tx
    IntDefaultHandler,               // UART3 Rx and Tx
    IntDefaultHandler,               // UART4 Rx and Tx
    IntDefaultHandler,               // UART5 Rx and Tx
    IntDefaultHandler,               // UART6 Rx and Tx
    IntDefaultHandler,               // UART7 Rx and Tx
    0, 0, 0, 0, 0, 0, 0, 0,          // Reserved
    IntDefaultHandler,               // I2C2 Master and Slave
    IntDefaultHandler,               // I2C3 Master and Slave
    IntDefaultHandler,               // Timer 4 subtimer A
    IntDefaultHandler,               // Timer 4 subtimer B
    IntDefaultHandler,               // Timer 5 subtimer A
    IntDefaultHandler,               // Timer 5 subtimer B
    IntDefaultHandler,               // Wide Timer 0 subtimer A
    IntDefaultHandler,               // Wide Timer 0 subtimer B
    IntDefaultHandler,               // Wide Timer 1 subtimer A
    IntDefaultHandler,               // Wide Timer 1 subtimer B
    IntDefaultHandler,               // Wide Timer 2 subtimer A
    IntDefaultHandler,               // Wide Timer 2 subtimer B
    IntDefaultHandler,               // Wide Timer 3 subtimer A
    IntDefaultHandler,               // Wide Timer 3 subtimer B
    IntDefaultHandler,               // Wide Timer 4 subtimer A
    IntDefaultHandler,               // Wide Timer 4 subtimer B
    IntDefaultHandler,               // Wide Timer 5 subtimer A
    IntDefaultHandler,               // Wide Timer 5 subtimer B
    IntDefaultHandler,               // FPU
    0, 0,                            // Reserved
    IntDefaultHandler,               // PECI 0
    IntDefaultHandler,               // LPC 0
    IntDefaultHandler,               // I2C4 Master and Slave
    IntDefaultHandler,               // I2C5 Master and Slave
    IntDefaultHandler,               // GPIO Port M
    IntDefaultHandler,               // GPIO Port N
    IntDefaultHandler,               // Quadrature Encoder 1
    0, 0,                            // Reserved
    IntDefaultHandler,               // GPIO Port P (Summary or P0)
    IntDefaultHandler,               // GPIO Port P1
    IntDefaultHandler,               // GPIO Port P2
    IntDefaultHandler,               // GPIO Port P3
    IntDefaultHandler,               // GPIO Port P4
    IntDefaultHandler,               // GPIO Port P5
    IntDefaultHandler,               // GPIO Port P6
    IntDefaultHandler,               // GPIO Port P7
    IntDefaultHandler,               // GPIO Port Q
    IntDefaultHandler,               // GPIO Port Q1
    IntDefaultHandler,               // GPIO Port Q2
    IntDefaultHandler,               // GPIO Port Q3
    IntDefaultHandler,               // GPIO Port Q4
    IntDefaultHandler,               // GPIO Port Q5
    IntDefaultHandler,               // GPIO Port Q6
    IntDefaultHandler,               // GPIO Port Q7
    IntDefaultHandler,               // Timer 6 subtimer A
    IntDefaultHandler,               // Timer 6 subtimer B
    IntDefaultHandler,               // Timer 7 subtimer A
    IntDefaultHandler,               // Timer 7 subtimer B
    IntDefaultHandler,               // I2C6 Master and Slave
    IntDefaultHandler,               // I2C7 Master and Slave
    IntDefaultHandler,               // HIMSCAN
    IntDefaultHandler,               // OneWire
    IntDefaultHandler,               // PS2
    IntDefaultHandler,               // LED Seq
    IntDefaultHandler,               // I2C8 Master and Slave
    IntDefaultHandler,               // I2C9 Master and Slave
    IntDefaultHandler                // GPIO Port R
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.
//
//*****************************************************************************
void ResetISR(void)
{
    extern uint32_t _stack_top;
    extern void _c_int00(void);
    _c_int00();
}

//*****************************************************************************
//
// Default exception handlers. Simply loops forever.
//
//*****************************************************************************
static void NmiSR(void) { while(1); }
static void FaultISR(void) { while(1); }
static void IntDefaultHandler(void) { while(1); }
