/***************************************************************************
**                                                                        **
**  App Name     : PAKVENT-1                                              **
**  Project Name : Ventilator_V1                                          **
**                                                                        **
**  This program is developed in the hope that it will be useful in the   **
**  fight against COVID-19, but WITHOUT ANY WARRANTY; without even the    **
**  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       **
**  PURPOSE.  See the GNU General Public License for more details.        **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**          Authors: AM Humayun, JCM Mubashir Iqbal                       **
****************************************************************************/

#include "addressing.h"

Addressing::Addressing()
{

}
//volatile void *led_addr;
volatile void *virtual_base;
int fd;
volatile void *h2p_lw_led_addr;
int LEDs = 0x00;

volatile void *FPGA_MAIN;
volatile void *LED_ADDR;


#define FPGA_base (0x400)
#define LED_base (0x00)

int Addressing::get_address_of_peripherals()
{
    // map the address space for the LED registers into user space so we can interact with them.
    // we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span
    // map the address space for the LED registeFPGA_basers into user space so we can interact with them.
    // we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

    if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
        printf( "ERROR: could not open \"/dev/mem\"...\n" );
        return -1;
    }
    virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );
    if( virtual_base == MAP_FAILED ) {
        printf( "ERROR: mmap() failed...\n" ); close( fd );
        return -2;
    }
    FPGA_MAIN = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + FPGA_base) & ( unsigned long)( HW_REGS_MASK ) );
    LED_ADDR = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + LED_base) & ( unsigned long)( HW_REGS_MASK ) );

    return 1;
}


uint32_t* Addressing::givemeaddr(int a)
{
   if (a == 0) return (uint32_t*)FPGA_MAIN;
   else if (a == 1) return (uint32_t*)LED_ADDR;

   else return (uint32_t*)FPGA_MAIN;
}
