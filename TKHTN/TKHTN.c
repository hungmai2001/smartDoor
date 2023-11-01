#include <16f877a.h>
#use delay(clock=12M)
#define SW1    PIN_B1
#define IN1    PIN_C2
#define IN2    PIN_C1
#define SW2    PIN_B2
#define EN    PIN_B7
#define SS    PIN_B0
unsigned int8 t;
void thuan(){
            setup_CCP2(CCP_OFF);
            setup_CCP1(CCP_PWM);
            set_pwm1_duty(50);
            output_high(EN);
         
            }
void nghich(){
            setup_CCP1(CCP_OFF);
            setup_CCP2(CCP_PWM);
            set_pwm2_duty(50);
            output_high(EN);
          
              }
#int_ext
void isrext(){
            //if(EN==0) delay_ms(10000);
                     if (t==0) thuan();
                     if (t==1) {
                           nghich();
                           t=~t;          
                      }
             }
void main(){
            t = 0;
            output_low(EN);
            set_tris_b(0x0F);
            set_tris_c(0x00);
            enable_interrupts(int_ext);
            enable_interrupts(global);
            ext_int_edge(L_TO_H);
            setup_timer_2(T2_DIV_BY_4,74,1);
            while(1){
                     if(input(SW1)==1){
                     output_low(EN);
                     t=~t;
                     delay_ms(10000);
                     nghich();
                     t=~t;
                               }
                     if(input(SW2)==1){
                     output_low(EN);
                                       }
                    }
            }
