;*************************************************************
; Motor de Passo								   *
;											   *
; Autor: Davi Augusto Neves Leite			     	   *			 
; RA: 191027383						     		   *					 
; Data: 10/12/2021					     		   *					 
;*************************************************************
#include <p16f628a.inc>
;-------------------------------------------------------------
; Configuração dos Bits
__CONFIG _BODEN_ON & _CP_OFF & _PWRTE_ON & _WDT_OFF & _LVP_OFF & _MCLRE_ON & _XT_OSC
;-------------------------------------------------------------
;Configuração do endereço 0x25 para ser uma auxiliar do Timer
			NUMBER_OF_TIMER 	EQU 0x25
;-------------------------------------------------------------
;-------------------------------------------------------------
			ORG 0x0000
			GOTO INICIO	   ;Vai para o bloco INICIO (main)
;-------------------------------------------------------------
;-------------------------------------------------------------
;Bloco da Rotina de Interrupção do TMR0
			ORG 0x0004
			
			;Nesta primeira etapa, reseta a flag do TMR0 e compara o valor do TMR0 com uma auxiliar que conta quantas vezes o PIC acionou a interrupção
			BANKSEL INTCON
			BCF INTCON, T0IF
			
			BANKSEL TMR0
			MOVLW D'131'
			MOVWF TMR0
			DECFSZ NUMBER_OF_TIMER, 1	;Subtrai o valor de F (TMR0) da auxiliar que conta quantas vezes o PIC acionou a interrupção (esperar até 1s)
			GOTO FIM_T0					;Retorna para o início
			;-------------------------------------------------------------
			;-------------------------------------------------------------
			;Reinicia a variável auxiliar que conta quantas vezes o PIC acionou a interrupção
			MOVLW D'125'
			MOVWF NUMBER_OF_TIMER
			;-------------------------------------------------------------
			;-------------------------------------------------------------
			;Ao chegar aqui, significa que passou um segundo (1000ms dado pela contagem de quantas interrupções de 8ms deu...)
			;Desta forma, realizar a rotação da variável auxiliar (AUX)
			BTFSC PORTB, 4		;Verifica se o pino RB4 esta ativo
			GOTO CONFIG_INICIAL_PORTB	;Reiniciar o looping reconfigurando a PORTB se o pino RB4 estiver ativo
			GOTO ROTACAO_MOTOR		;Rotina que move o valor da rotacao para a direita (RB7 até RB4)
			;-------------------------------------------------------------
			;-------------------------------------------------------------

FIM_T0: RETFIE
;-------------------------------------------------------------
;-------------------------------------------------------------
; Rotina de Rotação do Motor de Passo (por meio: mover um bit à direita)
ROTACAO_MOTOR:
			RRF PORTB, 1	;Move um bit à direita da PORTB
			RETFIE
;-------------------------------------------------------------
;-------------------------------------------------------------
; Rotina para reconfigurar o PORTB para o valor inicial (causar looping setando a RB7 com 1 e as outras com 0)
CONFIG_INICIAL_PORTB:
			MOVLW B'10000000'
			MOVWF PORTB
			RETFIE
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador OPTION_REG
CONFIG_OPTIONREG:
			 BANKSEL OPTION_REG
			 MOVLW B'00000101'
			 MOVWF OPTION_REG
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador INTCON
CONFIG_INTCON:
			 BANKSEL INTCON
			 MOVLW B'10100000'
			 MOVWF INTCON
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador TRISB (PORTB) para os LED's (OUTPUT)
CONFIG_TRISB:
			 BANKSEL TRISB
			 MOVLW B'00000000' ;Definindo RB7, RB6, RB5, RB4 como OUTPUT
			 MOVWF TRISB
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração inicial da PORTB
CONFIG_PORTB:
			 BANKSEL PORTB
			 MOVLW B'10000000'		;Valor inicial da PORTB para o Motor de Passo...
			 MOVWF PORTB
			 
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador TMR0 (Timer0) para 1s
CONFIG_TMR0:
			 BANKSEL TMR0
			 MOVLW D'131'
			 MOVWF TMR0				  ;Move o valor inicial 131 para o TMR0, para fins de comparação com a auxiliar
			 
			 MOVLW D'125'
			 MOVWF NUMBER_OF_TIMER  ;Move o valor 125 para a auxiliar que conta quantas vezes o PIC acionou a interrupção
			 
			 GOTO FIM_CONFIG	
;-------------------------------------------------------------
;-------------------------------------------------------------
FIM_CONFIG:	RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
INICIO:
		CALL CONFIG_OPTIONREG 	 ;Chama a sub-rotina de programar o OPTION_REG
		CALL CONFIG_INTCON	  	 ;Chama a sub-rotina de programar o INTCON
		
		CALL CONFIG_TRISB		;Chama a sub-rotina de programar o TRISB
		CALL CONFIG_PORTB	  	;Chama a sub-rotina de programar o PORTB (Inicial)
		
		CALL CONFIG_TMR0	   		;Chama a sub-rotina de programar o TMR0
		
		GOTO $ ;O programa executa essa linha indefinidamente ficando “preso” na mesma. Porém a cada 8ms ele irá para o endereço 0x04 e retornar assim que encontrar o RETFIE. Ou seja, ele irá 125 vezes por segundo para o endereço 0x4, que vai dar 1000ms para a execução da rotina do Motor de Passo...
END
;-------------------------------------------------------------
;-------------------------------------------------------------



