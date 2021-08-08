;*************************************************************
; Cronômetro Com Controle									 *
;															 *
; Autor: Davi Augusto Neves Leite			     			 *			 
; RA: 191027383						     				     *					 
; Data: 08/11/2020					     					 *					 
;*************************************************************

#include <p16f628a.inc>
;-------------------------------------------------------------
; Configuração dos Bits
__CONFIG _BODEN_ON & _CP_OFF & _PWRTE_ON & _WDT_OFF & _LVP_OFF & _MCLRE_ON & _XT_OSC
;-------------------------------------------------------------
;Configuração do endereços para serem os contadores de dígitos do display
		CBLOCK 0x20
			   COUNT_DISPLAY	;Endereço 0x20 para ser contador total do display
			   DIG_DEZENA		;Endereço 0x21 para ser dígito da dezena
			   DIG_UNIDADE		;Endereço 0x22 para ser dígito da unidade
			   AUX				;Endereço 0x23 para ser uma auxiliar na separação de dígitos do contador total
			   AUX2				;Endereço 0x24 para ser uma auxiliar2 na separação de dígitos do contador total
		ENDC
;-------------------------------------------------------------
;Configuração do endereço 0x25 para ser uma auxiliar do Timer
			NUMBER_OF_TIMER 	EQU 	0x25
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
			
			INCF COUNT_DISPLAY, 1 		;Aumenta o contador total do display em 1 -> COUNT_DISPLAY = COUNT_DISPLAY + 1	
	
			;Reinicia a variável auxiliar que conta quantas vezes o PIC acionou a interrupção
			MOVLW D'125'
			MOVWF NUMBER_OF_TIMER

FIM_T0: RETFIE
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para utilizar como Delay de 12ms
DELAY12:
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			GOTO FIM_DELAY12

FIM_DELAY12: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina que separa os dígitos da dezena e unidade do contador total do display
SEPARA_DIG:
			;Realização de um loop de 10 voltas
			MOVLW D'10'				;Move o valor 10 para o registrador W
			MOVWF AUX				;Move o valor de W para AUX
			MOVF COUNT_DISPLAY, 0	;Move o valor do contador total do display para o registrador W
			MOVWF AUX2				;Move o valor de W para a AUX2
			CLRF DIG_DEZENA			;Limpa o contador de dígitos da dezena
LOOP_SEPARA_DIG:
			MOVLW D'10'				;Move o valor 10 para o registrador W
			SUBWF AUX2, 1			;Subtrai 10 de AUX2 e armazena o resultado em AUX2				
			
			BTFSS STATUS, C			;Verifica se a operação de subtração resultou em negativo
			GOTO FIM_LOOP_SEPARA_DIG;Caso tenha sido, vai para o fim do looping
			;Dígito da Dezena
			INCF DIG_DEZENA, 1		;Caso não tenha sido, aumenta a dezena em uma unidade
			
			DECFSZ AUX, 1			;Decrementa AUX em uma unidade e verifica se é zero
			GOTO LOOP_SEPARA_DIG	;Caso não seja 0, volta para o looping
			GOTO FIM_LOOP_SEPARA_DIG;Fim do looping
			
FIM_LOOP_SEPARA_DIG:
			MOVF AUX2, 0			;Move o valor de AUX2 para W
			ADDLW D'10' 			;Adiciona 10 para o valor em W
			;Dígito da Unidade
			MOVWF DIG_UNIDADE
			GOTO FIM_SEPARA_DIG
			
FIM_SEPARA_DIG: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para atualizar os dígitos da dezena e unidade do display com base no contador total
ATUALIZA_DISPLAY:
			CALL SEPARA_DIG			;Chama a sub-rotina de separar os dígitos da dezena e unidade do contador total
			CALL DISPLAY_DEZENA		;Chama a sub-rotina de atualizar o dígito da dezena do display
			CALL DISPLAY_UNIDADE	;Chama a sub-rotina de atualizar o dígito da unidade do display
			GOTO FIM_ATUALIZA_DISPLAY
			
FIM_ATUALIZA_DISPLAY: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para congelar os dígitos da dezena e unidade do display com base no contador total
CONGELA_DISPLAY:
			CALL DISPLAY_DEZENA		;Chama a sub-rotina de atualizar o dígito da dezena do display
			CALL DISPLAY_UNIDADE	;Chama a sub-rotina de atualizar o dígito da unidade do display
			GOTO FIM_CONGELA_DISPLAY
FIM_CONGELA_DISPLAY: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para mudar o contador e mostrar o respectivo número na dezena do display
DISPLAY_DEZENA:	
			CALL DELAY12			;Chama a sub-rotina de delay de 12ms
			;-------------------------------------------------------------
			;Deixa selecionado o banco do PORTB para alteração dos números no display (RBx)
			BANKSEL PORTB
			;-------------------------------------------------
			; Abaixo, realiza-se uma subtração e verifica se o resultado obtido foi 0 (a partir da flag Z)
			;-------------------------------------------------
			; Número 0
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'0'			  ;Decresce em 0 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER0   ;Caso tenha sido, coloca o número 0 no display
			NOP
			;-------------------------------------------------
			; Número 1
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'1'			  ;Decresce em 1 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER1   ;Caso tenha sido, coloca o número 1 no display
			NOP
			;-------------------------------------------------
			; Número 2
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'2'			  ;Decresce em 2 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER2   ;Caso tenha sido, coloca o número 2 no display
			NOP
			;-------------------------------------------------
			; Número 3
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'3'			  ;Decresce em 3 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER3   ;Caso tenha sido, coloca o número 3 no display
			NOP
			;-------------------------------------------------
			; Número 4
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'4'			  ;Decresce em 4 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER4   ;Caso tenha sido, coloca o número 4 no display
			NOP
			;-------------------------------------------------
			; Número 5
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'5'			  ;Decresce em 5 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER5   ;Caso tenha sido, coloca o número 5 no display
			NOP
			;-------------------------------------------------
			; Número 6
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'6'			  ;Decresce em 6 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER6   ;Caso tenha sido, coloca o número 6 no display
			NOP
			;-------------------------------------------------
			; Número 7
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'7'			  ;Decresce em 7 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER7   ;Caso tenha sido, coloca o número 7 no display
			NOP
			;-------------------------------------------------
			; Número 8
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'8'			  ;Decresce em 8 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER8   ;Caso tenha sido, coloca o número 8 no display
			NOP
			;-------------------------------------------------
			; Número 9
			MOVF DIG_DEZENA, W    ;Move o valor do contador de dezenas pro registrador W
			SUBLW D'9'			  ;Decresce em 9 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DEZENA_NUMBER9   ;Caso tenha sido, coloca o número 9 no display
			NOP
			
			GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;Rotina para mudar o contador e mostrar o respectivo número na unidade do display
DISPLAY_UNIDADE:	
			CALL DELAY12			;Chama a sub-rotina de delay de 12ms
			;-------------------------------------------------------------
			;Deixa selecionado o banco do PORTB para alteração dos números no display (RBx)
			BANKSEL PORTB
			;-------------------------------------------------
			; Abaixo, realiza-se uma subtração e verifica se o resultado obtido foi 0 (a partir da flag Z)
			;-------------------------------------------------
			; Número 0
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'0'			  ;Decresce em 0 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER0  ;Caso tenha sido, coloca o número 0 no display
			NOP
			;-------------------------------------------------
			; Número 1
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'1'			  ;Decresce em 1 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER1  ;Caso tenha sido, coloca o número 1 no display
			NOP
			;-------------------------------------------------
			; Número 2
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'2'			  ;Decresce em 2 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER2  ;Caso tenha sido, coloca o número 2 no display
			NOP
			;-------------------------------------------------
			; Número 3
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'3'			  ;Decresce em 3 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER3  ;Caso tenha sido, coloca o número 3 no display
			NOP
			;-------------------------------------------------
			; Número 4
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'4'			  ;Decresce em 4 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER4  ;Caso tenha sido, coloca o número 4 no display
			NOP
			;-------------------------------------------------
			; Número 5
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'5'			  ;Decresce em 5 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER5  ;Caso tenha sido, coloca o número 5 no display
			NOP
			;-------------------------------------------------
			; Número 6
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'6'			  ;Decresce em 6 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER6  ;Caso tenha sido, coloca o número 6 no display
			NOP
			;-------------------------------------------------
			; Número 7
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'7'			  ;Decresce em 7 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER7  ;Caso tenha sido, coloca o número 7 no display
			NOP
			;-------------------------------------------------
			; Número 8
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'8'			  ;Decresce em 8 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER8  ;Caso tenha sido, coloca o número 8 no display
			NOP
			;-------------------------------------------------
			; Número 9
			MOVF DIG_UNIDADE, W   ;Move o valor do contador de unidades pro registrador W
			SUBLW D'9'			  ;Decresce em 9 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO UNIDADE_NUMBER9  ;Caso tenha sido, coloca o número 9 no display
			NOP
			
			GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Abaixo, ficam as funções para ativar cada número do display de 7 segmentos (config. RBx)
;-------------------------------------------------------------
; Número 0 -> Dezena
DEZENA_NUMBER0:
			 MOVLW B'11101110'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 0 -> Unidade
UNIDADE_NUMBER0:
			 MOVLW B'11111110'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 1 -> Dezena
DEZENA_NUMBER1:
			 MOVLW B'00101000'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 1 -> Unidade
UNIDADE_NUMBER1:
			 MOVLW B'00111000'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 2 -> Dezena
DEZENA_NUMBER2:
			 MOVLW B'11001101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 2 -> Unidade
UNIDADE_NUMBER2:
			 MOVLW B'11011101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 3 -> Dezena
DEZENA_NUMBER3:
			 MOVLW B'01101101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 3 -> Unidade
UNIDADE_NUMBER3:
			 MOVLW B'01111101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 4 -> Dezena
DEZENA_NUMBER4:
			 MOVLW B'00101011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 4 -> Unidade
UNIDADE_NUMBER4:
			 MOVLW B'00111011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 5 -> Dezena
DEZENA_NUMBER5:
			 MOVLW B'01100111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 5 -> Unidade
UNIDADE_NUMBER5:
			 MOVLW B'01110111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 6 -> Dezena
DEZENA_NUMBER6:
			 MOVLW B'11100011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 6 -> Unidade
UNIDADE_NUMBER6:
			 MOVLW B'11110011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 7 -> Dezena
DEZENA_NUMBER7:
			 MOVLW B'00101100'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 7 -> Unidade
UNIDADE_NUMBER7:
			 MOVLW B'00111100'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 8 -> Dezena
DEZENA_NUMBER8:
			 MOVLW B'11101111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 8 -> Unidade
UNIDADE_NUMBER8:
			 MOVLW B'11111111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
;-------------------------------------------------------------
; Número 9 -> Dezena
DEZENA_NUMBER9:
			 MOVLW B'00101111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 9 -> Unidade
UNIDADE_NUMBER9:
			 MOVLW B'00111111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
			 
FIM_DISPLAY_NUMBER:	RETURN	
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para verificar se o RA1 está pressionado (a fim de se realizar as devidas operações de congelar ou não o display)
VERIFICA_RA1:
			;Aqui está a condição (if) que diz se o botão RA1 foi pressionado ou não, e chama as funções de controle do do display
			BTFSC PORTA, 1
			GOTO ATUALIZA_DISPLAY 	;Caso NÃO esteja pressionado, chama a função para atualizar o display
			GOTO CONGELA_DISPLAY	;Caso esteja pressionado, não atualiza o display
			GOTO FIM_VERIFICA_RA1
FIM_VERIFICA_RA1: RETURN		  	;Marca o fim da verificação
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para verificar se o RA2 está pressionado (a fim de se realizar as devidas operações de resetar o contador)
VERIFICA_RA2:
			;Aqui está a condição (if) que diz se o botão RA1 foi pressionado ou não, e chama as funções de controle do do display
			BTFSC PORTA, 2
			GOTO FIM_VERIFICA_RA2 	;Caso NÃO esteja pressionado, não reseta o contador
			GOTO RESETAR_COUNT		;Caso esteja pressionado, reseta o contador

FIM_VERIFICA_RA2: RETURN		  	;Marca o fim da verificação
;-------------------------------------------------------------
;-------------------------------------------------------------
;Verifica se é necessário setar o contador do display para 0
VERIFICA_RESETAR_COUNT:
			MOVF COUNT_DISPLAY, W 			;Move o valor do contador do display para W
			SUBLW D'100' 		  			;Realiza a subtração de 10 para verificar o carry
			BTFSC STATUS, Z		  			;Setar para 0 se a flag Z estiver com 0
			GOTO RESETAR_COUNT				;Chama a sub-rotina para setar o contador do display para 0
			GOTO FIM_VERIFICA_RESETAR_COUNT ;Retorna em caso de nenhuma alteração
;-------------------------------------------------------------
;Seta o contador do display para 0 (após verificação)
RESETAR_COUNT:
			CLRF COUNT_DISPLAY				;Setando o contador total do display para 0
			GOTO FIM_VERIFICA_RESETAR_COUNT

FIM_VERIFICA_RESETAR_COUNT: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador OPTION_REG
CONFIG_OPTIONREG:
			 BANKSEL OPTION_REG
			 MOVLW B'10000101'
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
; Configuração do registrador TRISA (PORTA)
CONFIG_TRISA:
			 BANKSEL TRISA
			 MOVLW B'00000110' ;Colocando o RA1 e RA2 como input
			 MOVWF TRISA
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
; Configuração do registrador TRISB (PORTB)
CONFIG_TRISB:
			 BANKSEL TRISB
			 MOVLW B'00000000' ;Definindo todos RBx como output (display)
			 MOVWF TRISB
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração inicial da PORTA
CONFIG_PORTA:
			 BANKSEL PORTA
			 CLRF PORTA
			 MOVLW D'7'
			 MOVWF CMCON
			 GOTO FIM_CONFIG	 
;-------------------------------------------------------------
; Configuração inicial da PORTB
CONFIG_PORTB:
			 BANKSEL PORTB
			 MOVLW B'11101110'
			 MOVWF PORTB
			 
			 CALL DELAY12			;Chama a sub-rotina de delay de 12ms
			 
			 MOVLW B'11111110'
			 MOVWF PORTB
			 
			 GOTO FIM_CONFIG
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador TMR0 (Timer0)
CONFIG_TMR0:
			 BANKSEL TMR0
			 MOVLW D'131'
			 MOVWF TMR0
			 
			 MOVLW D'125'
			 MOVWF NUMBER_OF_TIMER
			 
			 GOTO FIM_CONFIG	
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração dos contadores e auxiliares -> Zerar (CLRF)
CONFIG_COUNT_AUX:
			 CLRF COUNT_DISPLAY
			 CLRF DIG_DEZENA
			 CLRF DIG_UNIDADE
			 CLRF AUX
			 
			 GOTO FIM_CONFIG
FIM_CONFIG:	RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
INICIO:
		CALL CONFIG_OPTIONREG  ;Chama a sub-rotina de programar o OPTION_REG
		CALL CONFIG_INTCON	   ;Chama a sub-rotina de programar o INTCON
		
		CALL CONFIG_TRISA	   ;Chama a sub-rotina de programar o TRISA
		CALL CONFIG_TRISB	   ;Chama a sub-rotina de programar o TRISB
		CALL CONFIG_PORTA	   ;Chama a sub-rotina de programar o PORTA
		CALL CONFIG_PORTB	   ;Chama a sub-rotina de programar o PORTB
		
		CALL CONFIG_TMR0	   ;Chama a sub-rotina de programar o TMR0
		CALL CONFIG_COUNT_AUX  ;Chama a sub-rotina de programar os contadores e auxiliares (inicialmente, com valor 0)
;-------------------------------------------------------------
;Rotina de LOOP que faz todas as verificações necessárias do programa
LOOP:
		CALL VERIFICA_RA1			;Chama a sub-rotina para verificar se RA1 está pressionado
		CALL VERIFICA_RA2			;Chama a sub-rotina para verificar se RA2 está pressionado
		CALL VERIFICA_RESETAR_COUNT ;Chama a sub-rotina de verificar se é necessário resetar o contador para 0
		GOTO LOOP	
END
;-------------------------------------------------------------
;-------------------------------------------------------------


