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

volatile void *ADC_0;
volatile void *ADC_1;
volatile void *ADC_2;
volatile void *ADC_3;
volatile void *ADC_4;
volatile void *ADC_5;
volatile void *ADC_6;
volatile void *ADC_7;


#define ADC0_base (0x20)
#define ADC1_base (0x40)
#define ADC2_base (0x40)
#define ADC3_base (0x40)
#define ADC4_base (0x40)
#define ADC5_base (0x40)
#define ADC6_base (0x40)
#define ADC7_base (0x40)

int Addressing::get_address_of_peripherals()
{
    // map the address space for the LED registers into user space so we can interact with them.
    // we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

    // map the address space for the LED registers into user space so we can interact with them.
        // we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span


    return -1;

    /*
        if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
            printf( "ERROR: could not open \"/dev/mem\"...\n" );
            return -1;
        }
        virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );
        if( virtual_base == MAP_FAILED ) {
            printf( "ERROR: mmap() failed...\n" ); close( fd );
            return -1;
        }
        ADC_0 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC0_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_1 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC1_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_2 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC2_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_3 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC3_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_4 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC4_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_5 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC5_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_6 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC6_base) & ( unsigned long)( HW_REGS_MASK ) );
        ADC_7 = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + ADC7_base) & ( unsigned long)( HW_REGS_MASK ) );
        */

        return 0;
}


int32_t* Addressing::givemeaddr(int a)
{
   if (a == 0) return (int32_t*)ADC_0;
   else if (a == 1) return (int32_t*)ADC_1;
   else if (a == 2) return (int32_t*)ADC_2;
   else if (a == 3) return (int32_t*)ADC_3;
   else if (a == 4) return (int32_t*)ADC_4;
   else if (a == 5) return (int32_t*)ADC_5;
   else if (a == 6) return (int32_t*)ADC_6;
   else if (a == 7) return (int32_t*)ADC_7;
   else return (int32_t*)ADC_0;
}
