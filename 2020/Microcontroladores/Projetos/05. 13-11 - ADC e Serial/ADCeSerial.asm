;*************************************************************
; Conversor Anal�gico-Digital (ADC)							 *
;															 *
; Autor: Davi Augusto Neves Leite			     			 *			 
; RA: 191027383						     				     *					 
; Data: 15/11/2020					     					 *					 
;*************************************************************

#INCLUDE <P16F877A.INC>
;-------------------------------------------------------------
; Configura��o dos Bits
__CONFIG _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _BOREN_ON & _LVP_OFF & _CPD_OFF & _WRT_OFF & _CP_OFF
;-------------------------------------------------------------
;-------------------------------------------------------------
		CBLOCK  0x20
				DELAY 		;Configura��o do endere�o 0x21 para ser uma auxiliar para delay
		ENDC
;-------------------------------------------------------------
;-------------------------------------------------------------
		ORG 0x0000
		GOTO INICIO 		;Vai para o bloco INICIO
;-------------------------------------------------------------		
;-------------------------------------------------------------
; Sub-rotina para um delay de 255ms (para ADC)
DELAY255:
		MOVLW D'255'		;Move o valor 255 para W
		MOVWF DELAY			;Move o valor de W para a auxiliar DELAY
		DECFSZ DELAY, 1		;Decrementa em 1 a auxiliar DELAY e verifica se � 0
		GOTO $-1			;Retorna para o LOOP caso n�o seja 0
		NOP
		RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Sub-rotinas de Configura��es Iniciais
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o do registrador INTCON
;-------------------------------------------------------------
CONFIG_INTCON:
			 BANKSEL INTCON
			 MOVLW B'10100000'
			 MOVWF INTCON
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TXSTA para Comunica��o Serial (Transmiss�o de Dados)
;-------------------------------------------------------------
CONFIG_TXSTA:
			 BANKSEL TXSTA
			 MOVLW B'00100110' ;Configura��o do TXSTA para comunica��o serial ass�ncrona de 8 bits
			 MOVWF TXSTA
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador RCSTA para Comunica��o Serial (Recep��o de Dados)
;-------------------------------------------------------------
CONFIG_RCSTA:
			 BANKSEL RCSTA
			 MOVLW B'10010000' ;Configura��o do RCSTA para comunica��o serial ass�ncrona de 8 bits
			 MOVWF RCSTA
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador SPBRSG para Comunica��o Serial (Taxa de Transmiss�o)
;-------------------------------------------------------------
; Clock: 20MHz // BPS: 9600bps // BRGH = 1 -> SPBRGH = 129,2083
;-------------------------------------------------------------
CONFIG_SPBRG:
			 BANKSEL SPBRG
			 MOVLW D'129' 		;Configura��o do SPBRS para taxa de alta velocidade (TXSTA)
			 MOVWF SPBRG
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador PIE1 para Comunica��o Serial
;-------------------------------------------------------------
CONFIG_PIE1:
			 BANKSEL PIE1
			 MOVLW B'00110000'
			 MOVWF PIE1
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador PIR1 para Comunica��o Serial
;-------------------------------------------------------------
CONFIG_PIR1:
			 BANKSEL PIR1
			 MOVLW B'00000000'
			 MOVWF PIR1
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TRISB (PORTB) para Comunica��o Serial
;-------------------------------------------------------------
CONFIG_TRISB_SERIAL:
			 BANKSEL TRISB
			 MOVLW B'00000110' ;Definindo RB1 e RB2 como Input para Comunica��o Serial
			 MOVWF TRISB
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TRISA (PORTA) para ADC
;-------------------------------------------------------------
CONFIG_TRISA_ADC:
			 BANKSEL TRISA
			 MOVLW B'00000010' ;Definindo RA1 como Input (Pot�nciometro)
			 MOVWF TRISA
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador ADCON0 (ADC)
;-------------------------------------------------------------
;GO/DONE = 0 || CHS2:CHS0 = 001 (canal 1 -> RA1/AN1) || ADCS1:ADCS0 = 01 (FOSC/8)
;-------------------------------------------------------------
CONFIG_ADCON0:
			 BANKSEL ADCON0
			 MOVLW B'01001001'	;Configura��o para 8*Tosc e Canal 1 (AN1)
			 MOVWF ADCON0
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador ADCON1 (ADC)
;-------------------------------------------------------------
; PCGG3:PCFG0 = 0000 (RA1 como AD) || ADFM = 1 (Ajuste a Direita)
;-------------------------------------------------------------
CONFIG_ADCON1:
			 BANKSEL ADCON1
			 MOVLW B'10000000'	;Configura��o para Ajuste a Direita (bit 7) e RA1 como AD
			 MOVWF ADCON1
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
INICIO:
		CALL CONFIG_INTCON			;Chama a sub-rotina de programar o INTCON
		CALL CONFIG_TRISB_SERIAL	;Chama a sub-rotina de programar o TRISB para Comunica��o Serial
		CALL CONFIG_TXSTA			;Chama a sub-rotina de programar o TXSTA para Comunica��o Serial (Transmiss�o)
		CALL CONFIG_RCSTA			;Chama a sub-rotina de programar o RCSTA para Comunica��o Serial (Recep��o)
		CALL CONFIG_SPBRG			;Chama a sub-rotina de programar o SPBRG para Comunica��o Serial (Taxa de Transmiss�o)
		CALL CONFIG_PIE1			;Chama a sub-rotina de programar o PIE1 para Comunica��o Serial (Interrup��o)
		CALL CONFIG_PIR1			;Chama a sub-rotina de programar o PIR1 para Comunica��o Serial
		
		CALL CONFIG_TRISA_ADC		;Chama a sub-rotina de programar o TRISA para ADC
		CALL CONFIG_ADCON0			;Chama a sub-rotina de programar o ADCON0 para ADC
		CALL CONFIG_ADCON1			;Chama a sub-rotina de programar o ADCON1 para ADC

LOOP:
		CALL DELAY255		;Chama a sub-rotina de delay de 255ms
		;-------------------------------------------------------------
		;-------------------------------------------------------------
		; Recebimento de Dados pela Serial
		;-------------------------------------------------------------
		;-------------------------------------------------------------
		;BANKSEL PIR1
		;BTFSS PIR1, RCIF 	;Verifica se chegou algum byte pela serial
		;GOTO $-1 			;Caso N�O tenha, volta o loop at� chegar
		NOP
		
		;Caso tenha chegado algum dado...
		;BANKSEL RCREG
		;MOVF RCREG, W		;Move o byte do buffer de recep��o e coloca registrador W		
		;-------------------------------------------------------------
		
		;-------------------------------------------------------------
		;-------------------------------------------------------------
		; Convers�o do Sinal Anal�gico para Digital
		;-------------------------------------------------------------
		;-------------------------------------------------------------
		BANKSEL ADCON0		;Seleciona o banco do registrador ASCON0
		BSF ADCON0, 2		;Seta o GO/DONE para 1 para iniciar a convers�o

		BTFSC ADCON0, 2		;Verifica se a convers�o terminou (GO/DONE = 0)
		GOTO $-1			;Caso n�o tenha, volta pro loop
		NOP
		;-------------------------------------------------------------
		
		;-------------------------------------------------------------
		; Leitura dos 2 bits de MSB
		;-------------------------------------------------------------
		BANKSEL ADRESH
		MOVF ADRESH, W		;Move o valor para W
		
		;-------------------------------------------------------------
		; Envio de Dados pela Serial
		;-------------------------------------------------------------
		BANKSEL TXSTA
		BTFSS TXSTA, TRMT 	;Verifica se o buffer de transmiss�o est� vazio
		GOTO $-1			;Caso N�O esteja, verifica novamente (at� conseguir enviar)
		NOP
		
		BANKSEL TXREG		;Ativa o banco do registrador TXREG
		MOVWF TXREG 		;Caso esteja, envia o valor para o Buffer de Transmiss�o
		;-------------------------------------------------------------
		
		;-------------------------------------------------------------
		; Leitura dos outros 8 bits (LSB)
		;-------------------------------------------------------------
		BANKSEL ADRESL
		MOVF ADRESL, W		;Move o valor para W
		
		;-------------------------------------------------------------
		; Envio de Dados pela Serial
		;-------------------------------------------------------------
		BANKSEL TXSTA
		BTFSS TXSTA, TRMT 	;Verifica se o buffer de transmiss�o est� vazio
		GOTO $-1			;Caso N�O esteja, verifica novamente (at� conseguir enviar)
		NOP
		
		BANKSEL TXREG		;Ativa o banco do registrador TXREG
		MOVWF TXREG 		;Caso esteja, envia o valor para o Buffer de Transmiss�o
		
		CALL DELAY255		;Chama a sub-rotina de delay de 255ms
		;-------------------------------------------------------------
		GOTO LOOP			;Retorna para o come�o do Loop
END