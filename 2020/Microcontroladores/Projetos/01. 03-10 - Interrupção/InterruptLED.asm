;*************************************************************
; Interrupção Externa do PIC16F873			     *			 
; Ligar e Desligar LED no pino R1			     *			 
;							     *
; Autor: Davi Augusto Neves Leite			     *			 
; RA: 191027383						     *					 
; Data: 04/10/2020					     *					 
;*************************************************************

#include <p16F873.inc>
;-------------------------------------------------------------
	CBLOCK	0x20 		;Configuração do endereço 0x20 para ser um contador auxiliar
		AUX
	ENDC
;-------------------------------------------------------------
	ORG 0x0000
	GOTO INICIO		;Vai para o bloco INICIO (main)
;-------------------------------------------------------------
;Bloco da Rotina de Interrupção
	ORG 0x00004
	
	;Looping: 10 vezes (1 para 10)
	MOVLW D'1'
	MOVWF AUX
LOOP:
	CALL CONTROL_LED 	;Chama a rotina de controle do LED
	
	;Verificação do número de voltas
	INCF AUX, 1 		;Aumenta AUX em 1
	MOVF AUX, W  		;Move o valor para o reg. W
	SUBLW D'11' 		;Contador até 10
	BTFSS STATUS, Z		;Verifica a flag
	GOTO LOOP 		;Caso a resposta seja verdadeira
	NOP 			;Sai do Loop

	BCF INTCON, INTF;Desabilitar a flag INTF que indica se uma interrupção ocorreu
	RETFIE 			;Faz o programa voltar a partir do local que foi chamado quando ocorreu a INT
;-------------------------------------------------------------
;Sub-rotina de Programar a Interrupção
PROG_INT:
	;Configuração do registrador OPTION_REG
	BANKSEL OPTION_REG
	BSF OPTION_REG, 7 	;Habilita o bit Pull-Up (ativo em 0)
	BCF OPTION_REG, 6 	;Rampa de Sinal Negativa (verifica INT do alto para baixo)

	;Configuração do registrador INTCON
	BANKSEL INTCON
	BSF INTCON, GIE  	;Deixa ativo todas as INT
	BSF INTCON, INTE 	;Habilita a INT externa
	
	RETURN
;-------------------------------------------------------------
;Sub-rotina de Programar o Pino de Controle do LED (PORTB)
PROG_LED:
	;Configuração do registrador TRISB, em que está contido o pino RB1 (em PORTB)
	BANKSEL TRISB
	MOVLW B'10000101'
	MOVWF TRISB
	
	;Torna ativo o PORTB
	BANKSEL PORTB

	RETURN
;-------------------------------------------------------------
;Sub-rotina para Controle do LED
CONTROL_LED:
	;Habilitar o LED por 3 microssegundos
	BSF PORTB, 1		;PORTB, 1 = Alto (RB1 -> alto)
	NOP	
	NOP
	NOP

	;Desabilitar o LED por 2 microssegundos
	BCF PORTB, 1		;PORTB, 1 = Baixo (RB1 -> baixo)
	NOP
	NOP
	
	RETURN
;-------------------------------------------------------------
INICIO:
	
	CALL PROG_INT 		;Chama a sub-rotina de programar a interrupção (INT)
	CALL PROG_LED 		;Chama a sub-rotina de programar o pino de controle do LED (PORTB/RB1)
	
	GOTO $ 			;Chamada para a mesma linha até que ocorra a interrupção

	END
;-------------------------------------------------------------